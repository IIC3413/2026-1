# IIC3413-DB

## Project Build

Install Dependencies:

--------------------------------------------------------------------------------
MillenniumDB needs the following dependencies:

- GCC >= 8.1
- CMake >= 3.12

On recent Debian and Ubuntu based distributions they can be installed by running:

```bash
sudo apt update && sudo apt install g++ cmake
```

For Mac you need to install the **Xcode Command Line Tools** and [Homebrew](https://brew.sh/). After installing homebrew you can install cmake:

```bash
brew install cmake
```

Build the Project:

--------------------------------------------------------------------------------
Open a terminal in the project root directory, then execute the commands:

For the Release version:

```bash
cmake -Bbuild/Release -DCMAKE_BUILD_TYPE=Release && cmake --build build/Release/
```

For the Debug Version:

```bash
cmake -Bbuild/Debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/Debug/
```

To use multiple cores during compilation (much faster) add `-j n` at the end of the previous commands, replacing `n` with the desired number of threads. Example for 8 threads:

```bash
cmake -Bbuild/Debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/Debug/ -j 8
```

--------------------------------------------------------------------------------
## Testing

Run the following commands from the project root directory.


### 1. Create Database

```bash
./build/Debug/bin/create_db
```
> If you built the project in **Release** mode, replace `Debug` with `Release` in all commands.

> :warning: To overwrite the database, you must delete the following files located in `data/example_db/`:
>
> * `catalog.data`
> * All table files with format: `n_tablename.tbl`

### 2. Test `HashIndex::insert_record(...)`:

```bash
./build/Debug/bin/test_index_insertion
```
> :warning: To test your implementation, you have to create an overflow chain and try insert some records

### 3. Test `BucketPage::delete_record(...)`:

```bash
./build/Debug/bin/test_index_deletion
```
> :warning: This test requires the index to be already created.
> Run the insertion test first, as it creates the required index.

### 4. Test `HashIndex::redistribute(...)`:

```bash
./build/Debug/bin/test_redistribute
```
> Without implementation of insert will be in an infinite loop

---

### 5. Print table:
```bash
./build/Debug/bin/print_table "table_name"
```

### 6. Print index:
```bash
./build/Debug/bin/print_index "table_name"
```
---

### Notes

* You **do not need to delete any files** to rerun the tests (except when recreating the database).
* Always run the build command after modifying code or tests


