# Transaction System Summary

## 1. MVCC in the Heap File

Every record on the heap is a **tuple version**. Each physical slot stores a tuple header alongside the column data:

| Field | Type | Meaning |
|---|---|---|
| `t_min` | `uint64_t` | tx_id that **created** this version |
| `t_max` | `uint64_t` | tx_id that **superseded** this version; `0` = still live |
| `next` | `RID` | RID of the **next (newer) version**; `RID(-1,-1)` = logically deleted |
| `first` | `RID` | RID of the **chain head** (the original insert slot) — same for every version in a chain |

**Version chain:** when a row is updated, a new physical slot is inserted with `t_min = tx_id` and `first = original_RID`. The old version gets `t_max = tx_id` and `next = new_RID`. The chain is singly-linked forward from oldest to newest via `next`; all versions share the same `first` pointer.

**Logical deletion** stamps the last version with `t_max = tx_id` and `next = RID(-1,-1)`, marking the chain end as deleted without removing the bytes.

**Physical deletion** sets the directory slot to `-2`. It is used only during undo (abort) and vacuum, never directly by a live write operation.

**Clean-up on abort** is **immediate and synchronous** — `undo()` runs as part of the abort path before locks are released, so aborted versions are never visible to any other transaction. There are no "aborted" entries sitting in the heap.

tx_ids are assigned starting at 1 by a global atomic counter. tx_id 0 is a reserved sentinel: `t_max == 0` means "this version has never been superseded".

---

## 2. Visibility Rules

`is_visible(header, tx_id)` answers: *should this specific version be returned to transaction `tx_id`?*

### Read Committed

A version is visible if:
- Its **creator committed** (or it was created by this transaction), AND
- Its **deletion has not yet committed** (i.e., `t_max == 0`, or the deleter is still active)

Concretely:

```
t_min ACTIVE, t_min == tx_id:
    t_max == 0 → visible   (own new/last version)
    t_max != 0 → invisible (own superseded version)

t_min ACTIVE, t_min != tx_id:
    → invisible            (dirty read blocked)

t_min COMMITTED:
    t_max == 0             → visible   (live committed version)
    t_max ACTIVE == tx_id  → invisible (we deleted/updated it)
    t_max ACTIVE != tx_id  → visible   (another tx's uncommitted delete — pre-delete version survives)
    t_max COMMITTED        → invisible (delete committed)
```

RC evaluates visibility dynamically using the most up-to-date active/committed statuses of `t_min` and `t_max` on every row read. It does not use a snapshot (`snapshot` is empty). Because of this dynamic check, non-repeatable reads and phantom reads are possible if concurrent transactions commit intermediate changes.

### Snapshot Isolation

A snapshot is taken at `start_transaction` time: the set of all currently-ACTIVE tx_ids is stored in `tx.snapshot`. A version is visible if:

**Creator check (`t_min`):** either `t_min == tx_id` (own write), or all of:
- `t_min` is committed (not currently active)
- `t_min ∉ snapshot` (was not still running when we started)
- `t_min < tx_id` (started before us)

Together these mean: *the creator committed before my snapshot was taken*.

**Deletion check (`t_max`):** the version is still "live" from our snapshot if any of:
- `t_max == 0` — not deleted
- `t_max == tx_id` — own transaction deleted it → invisible
- `t_max` is currently ACTIVE — deletion uncommitted
- `t_max ∈ snapshot` — deleter was still running when we started
- `t_max > tx_id` — deleter started after us

If none of these apply: the deletion committed before our snapshot → not visible.

Both states are fetched under a single `shared_lock` via `get_states(t_min, t_max)` to avoid a TOCTOU race between the two checks.

---

## 3. Updates

Both RC and SI follow the same structural steps; they differ in how conflicts are detected.

**RC update:**
1. Read the header of the passed RID.
2. Acquire a **write lock** on `header.first` (the chain head).
3. Walk `get_last_version(first)` — follow `next` pointers until `t_max == 0`.
4. If the last version is physically or logically deleted, return the appropriate sentinel.
5. **Insert a new version** with `t_min = tx_id`, `first = first_rid` via `insert_record`.
6. On the old last version, write `t_max = tx_id` and `next = new_RID` (`update_record_header`).

**SI update** — same as above except after acquiring the lock:
- Check that the last version **is visible** to this transaction.
- If not visible (another committed transaction already modified it — write-write conflict): immediately **self-abort** and throw `TransactionAbortException`.

The check is `!is_visible(latest_header) || latest_header.next == RID(-1,-1)` — the version is either invisible (someone else committed a new version after our snapshot) or the chain ends in a logical delete.

---

## 4. Aborts and Undo

`_abort_transaction` calls:
1. `transaction->abort()` — walks `first_rids` (the write set) and calls `heap_file->undo(first_rid, tx_id)` on each entry.
2. `catalog.abort_in_progress_tables(tx_id)` — drops any tables created by this transaction.
3. `transaction->state = COMMITTED` — marks as done (COMMITTED is the terminal state for both commit and abort).
4. `lock_mgr.release_all_locks(*transaction)` — releases all held locks last.

**`HeapFile::undo(first_rid, tx_id)`** walks the version chain forward from the head:

```
t_min == tx_id:             → physically delete (dir slot = -2); continue to next
t_min != tx_id, t_max == tx_id → reset_update: clear t_max and next,
                                  restoring the previous version to live; continue
t_min != tx_id, t_max == 0  → live version not ours; stop
```

This handles both insert-undo (physically remove) and update/delete-undo (restore the old version header). After undo, the heap looks as if the aborted transaction never ran.

---

## 5. Deletion

Deletion is **logical first, physical later**.

**Why two kinds of delete?**

A user DELETE cannot immediately remove the bytes from the heap because other concurrent transactions may still need to read the old version — either because they are RC transactions that haven't reached that row yet, or because they are SI transactions whose snapshot pre-dates the delete. Immediately erasing the slot would make those reads return garbage.

Instead, the delete is recorded as a metadata change only (`t_max` + `next = RID(-1,-1)`), leaving the data bytes intact. The visibility rules then gate each reader: a transaction that should not see the delete will still read the version as live; one that should see it will find the chain terminated. This is the same mechanism used for updates — a logical delete is simply an update that inserts no new version.

Physical removal is deferred to a point where it is safe: either immediately on abort (the deleting transaction never committed, so no one will ever need to see the version it wrote) or during `full_vacuum` (which runs when no concurrent operations can safely observe the old state).

### Garbage Collection and Vacuum

The system performs garbage collection in two distinct operations:

1. **`full_vacuum()`**: Scans every version chain starting from `header.first`. It traverses the chain via `next` until it finds the last active version (`t_max == 0`) or a logical delete (`next == RID(-1,-1)`). It flags older superseded versions with `-2` (physical delete), updates `first` pointers, and truncates trailing empty pages.
2. **`page.vacuum()`**: Runs per-page (often invoked by `full_vacuum`). It locks the page exclusively, scans for slots marked `-2`, permanently frees those physical slots by repacking the bytes toward the end of the page, and updates directory offsets.

**Logical delete path** (both RC and SI):
1. Read the header of the passed RID.
2. Acquire write lock on `header.first`.
3. Walk to the last version.
4. Under SI: check for write-write conflict (same as update).
5. Call `delete_record_logically(dir_slot, tx_id)`: sets `t_max = tx_id` and `next = RID(-1,-1)` on the last version.

The logically deleted version remains in the heap until **vacuum** removes it. Other transactions see the version as deleted only once the deleting transaction commits (visibility rules apply).

**Physical deletion** happens in two places:
- **`undo`**: reverting an insert done by the aborting transaction — slot immediately set to `-2`.
- **`vacuum` / `full_vacuum`**: after all transactions that could see a version have completed, dead slots are compacted out.

---

## 6. Lock Acquisition

The system uses **strict 2PL with tuple-granularity write locks**. Only write locks are used; read operations under MVCC are lock-free.

Lock key: `TupleKey { table_id, first_rid }` — keyed on the **chain head (`header.first`)**. By using the first RID in the chain for locking, all versions of the same logical row effectively share the same lock. This statically prevents write-write conflicts across different versions of the same tuple.

`LockManager::try_acquire_lock(tx_id, table_id, first_rid)`:
- Spins with a 100 ms sleep between attempts.
- If the key is absent → insert entry, call `add_to_write_set`, return `true`.
- If the key is present and the holder is this transaction → already held, return `true`.
- If the key is present and held by another transaction → keep waiting.
- After **10 seconds**: call `abort_transaction(tx_id)` on the waiter, then throw `TransactionAbortException`.

On first successful grant, `add_to_write_set(table_id, first_rid, tx_id)` records the `TupleKey` in the transaction's `first_rids` set. This set is later used by both `undo` (to know which chains to walk) and `release_all_locks` (to know which lock entries to erase).

**Fresh inserts** bypass `try_acquire_lock` (there is no existing chain head to lock against). `add_to_write_set` is called manually after the insert returns the new RID.

Locks are **never released early** — strict 2PL holds all locks until `release_all_locks` is called at the very end of commit or abort.

---

## 7. Transaction Lifecycle

```
start_transaction(isolation_level)
  ├─ acquire active_transaction_mutex (exclusive)
  ├─ fetch-add global transaction_count → tx_id (≥ 1)
  ├─ create Transaction{tx_id, isolation_level, state=ACTIVE}
  ├─ if SI: snapshot = {all currently ACTIVE tx_ids in active_transactions}
  ├─ insert into active_transactions
  └─ return tx_id
```

**Session states:**
- `state == 0` (autocommit): every query calls `start_transaction`, executes, then commits immediately via `execute_query(..., commit_at_end=true)`.
- `state == 1` (explicit transaction): started by `BEGIN TRANSACTION`, persists across queries until `COMMIT` or `ABORT`.

**Normal commit path:**
1. `catalog.commit_in_progress_tables(tx_id)` — finalises any schema changes.
2. `transaction->state = COMMITTED` (atomic write).
3. `lock_mgr.release_all_locks(*transaction)` — other waiters can now proceed.
4. Erase from `active_transactions` under exclusive lock.

**Abort path** (from `abort_transaction` or a system abort triggered by lock timeout or SI write-write conflict):
1. `transaction->abort()` → `undo()` on every chain in the write set.
2. `catalog.abort_in_progress_tables(tx_id)`.
3. `transaction->state = COMMITTED`.
4. `lock_mgr.release_all_locks(*transaction)`.
5. Erase from `active_transactions`.

**Session-level error handling** in `process_query`:
- `TransactionAbortException` → `handle_system_abort()`: if in explicit-tx mode (`state == 1`), sets `state = 0`; the transaction was already aborted by the thrower.
- `IIC3413DBException` → reported as `"Error running query:"` — transaction remains open if in explicit-tx mode.
- Disconnect (EOF) → `handle_abort()`: if `state == 1`, calls `abort_transaction(tx_id)` before the session is destroyed.
