#pragma once

#include <memory>

#include "relational_model/relation_iter.h"
#include "storage/heap_file/heap_file_page.h"
#include "storage/rid.h"
#include "system/tx_id.h"

class HeapFile;

class HeapFileIter : public RelationIter {
public:
  HeapFileIter(const HeapFile& heap_file, TxID tx_id);

  virtual void begin() override;

  virtual Record next() override;

  virtual void reset() override;

  RID get_current_RID() const;

private:
  const HeapFile& heap_file;

  std::unique_ptr<HeapFilePage> current_page;

  int64_t total_pages;

  int64_t current_page_number;

  int64_t current_page_record_pos;

  TxID tx_id;
};
