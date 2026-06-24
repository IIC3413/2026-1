#include "system.h"

#include <cstdlib>
#include <iostream>
#include <type_traits>

// memory for the global objects
static typename std::aligned_storage<sizeof(BufferManager), alignof(BufferManager)>::type buffer_mgr_buf;
static typename std::aligned_storage<sizeof(FileManager), alignof(FileManager)>::type file_mgr_buf;
static typename std::aligned_storage<sizeof(Catalog), alignof(Catalog)>::type catalog_buf;
static typename std::aligned_storage<sizeof(TransactionManager), alignof(TransactionManager)>::type
    transaction_mgr_buf;
static typename std::aligned_storage<sizeof(LockManager), alignof(LockManager)>::type lock_mgr_buf;

BufferManager& buffer_mgr = reinterpret_cast<BufferManager&>(buffer_mgr_buf);
FileManager& file_mgr = reinterpret_cast<FileManager&>(file_mgr_buf);
Catalog& catalog = reinterpret_cast<Catalog&>(catalog_buf);
TransactionManager& transaction_mgr = reinterpret_cast<TransactionManager&>(transaction_mgr_buf);
LockManager& lock_mgr = reinterpret_cast<LockManager&>(lock_mgr_buf);

System::System(const std::string& db_folder, int64_t buffer_size) {
  new (&file_mgr) FileManager(db_folder);
  new (&buffer_mgr) BufferManager(buffer_size);
  new (&lock_mgr) LockManager();

  try {
    new (&catalog) Catalog("catalog.dat");
  } catch (...) {
    std::cerr << "Error reading catalog. Make sure the database was not created with a previous version."
              << std::endl;
    exit(EXIT_FAILURE);
  }
  new (&transaction_mgr) TransactionManager();
}

System::~System() {
  transaction_mgr.~TransactionManager();
  catalog.~Catalog();
  lock_mgr.~LockManager();
  buffer_mgr.~BufferManager();
  file_mgr.~FileManager();
}
