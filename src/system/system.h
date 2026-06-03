#pragma once

#include "system/buffer_manager.h"
#include "system/catalog.h"
#include "system/file_manager.h"
#include "system/lock_manager.h"
#include "system/transaction_manager.h"

class System {
public:
  static const int64_t default_buffer_size = 1024 * 1024 * 1024;

  System(const std::string& db_folder, int64_t buffer_size = default_buffer_size);
  ~System();

};

// global objects
extern FileManager& file_mgr;
extern BufferManager& buffer_mgr;
extern TransactionManager& transaction_mgr;
extern Catalog& catalog;
extern LockManager& lock_mgr;
