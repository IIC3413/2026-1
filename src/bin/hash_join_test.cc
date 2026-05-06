#include <filesystem>
#include <iostream>

#include "query/optimizer/optimizer.h"
#include "query/parser/parser.h"
#include "storage/linear_hash_index/hash_index.h"
#include "system/system.h"

/*
Output esperado:

0:(1,"zanahoria",10,"zanahoria","raiz")
1:(3,"papa",11,"papa","tuberculo")
2:(2,"papa",11,"papa","tuberculo")
3:(0,"papa",11,"papa","tuberculo")*/

void process_query(std::unique_ptr<LogicalPlan> logical_plan, bool explain, TxID tx_id, std::ostream& out) {
  Optimizer optimizer(tx_id);
  auto physical_plan = optimizer.create_physical_plan(std::move(logical_plan));

  if (std::holds_alternative<std::unique_ptr<QueryAction>>(physical_plan)) {
    auto action = std::move(std::get<std::unique_ptr<QueryAction>>(physical_plan));
    action->execute();
  } else if (std::holds_alternative<std::unique_ptr<QueryIter>>(physical_plan)) {
    auto query_iter = std::move(std::get<std::unique_ptr<QueryIter>>(physical_plan));

    if (explain) {
      std::cout << "\n=== Physical Plan ===\n";
      query_iter->print_to_ostream(std::cout, 0);
      std::cout << std::endl;
    }

    query_iter->begin();
    Record record = query_iter->next();

    int record_count = 0;
    while (!record.invalid()) {
      out << record_count << ":(" << record.to_string() << ")\n";
      record = query_iter->next();
      ++record_count;
    }
  }
}

int main() {
  std::filesystem::remove_all("data/example_db");

  auto system = System("data/example_db");

  Transaction tx = transaction_mgr.start_transaction(IsolationLevel::READ_COMMITTED);
  auto txid = tx.get_id();

  Schema schema_a({{"id", DataType::INT}, {"vegetal", DataType::STR}});
  std::string table_a = "vegetales_a";

  if (!catalog.table_exists(table_a, txid)) {
    catalog.create_table(table_a, schema_a, txid);
  }

  std::vector<Record> a_records = {
      {{0, Value("papa")}},
      {{1, Value("zanahoria")}},
      {{2, Value("papa")}},
      {{3, Value("papa")}},
      {{4, Value("choclo")}}
  };

  for (auto& r : a_records) {
    catalog.insert_record(table_a, r, txid);
  }

  Schema schema_b({{"id", DataType::INT}, {"vegetal", DataType::STR}, {"color", DataType::STR}});
  std::string table_b = "vegetales_b";

  if (!catalog.table_exists(table_b, txid)) {
    catalog.create_table(table_b, schema_b, txid);
  }

  std::vector<Record> b_records = {
      {{10, Value("zanahoria"), Value("raiz")}},
      {{11, Value("papa"), Value("tuberculo")}},
      {{12, Value("tomate"), Value("fruta")}}
  };

  for (auto& r : b_records) {
    catalog.insert_record(table_b, r, txid);
  }

  std::string query = "SELECT * FROM vegetales_a, vegetales_b "
                      "WHERE vegetales_a.vegetal == vegetales_b.vegetal";

  bool explain = false;
  auto logical_plan = Parser::parse(query, explain, txid);
  process_query(std::move(logical_plan), explain, txid, std::cout);

  transaction_mgr.commit_transaction(txid);

  return EXIT_SUCCESS;
}