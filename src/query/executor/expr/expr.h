#pragma once

#include <ostream>

#include "relational_model/record.h"
#include "relational_model/value.h"

class Expr {
public:
  virtual ~Expr() = default;

  virtual Value eval(const Record&) = 0;

  virtual std::ostream& print_to_ostream(std::ostream& os) const = 0;

  friend std::ostream& operator<<(std::ostream& os, const Expr& node) {
    return node.print_to_ostream(os);
  }
};
