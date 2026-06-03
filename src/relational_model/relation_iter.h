#pragma once

#include "relational_model/record.h"

class RelationIter {
public:
  virtual ~RelationIter() = default;

  virtual void begin() = 0;

  virtual Record next() = 0;

  virtual void reset() = 0;
};
