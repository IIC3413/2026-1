#pragma once

#include "query/executor/expr/expr.h"

#include <memory>

// Wildcard matching for SQL LIKE without regex.
//
// Pattern metacharacters (in the stored pattern string):
//   %    — matches any sequence of zero or more characters
//   _    — matches exactly one character
//   \%   — matches a literal '%'  (write \% in the SQL LIKE string)
//   \_   — matches a literal '_'  (write \_ in the SQL LIKE string)
//   \\   — matches a literal '\'  (write \\ in the SQL LIKE string)
//   \x   — matches literal 'x' for any other x
static bool like_match(const char* t, const char* te) {
  // TODO: LAB5 Problem 1
}

class ExprLike : public Expr {
public:
  ExprLike(std::unique_ptr<Expr> child, std::string&& _pattern)
      : child(std::move(child)),
        pattern(std::move(_pattern)),
        res((int64_t)0) {}

  Value eval(const Record& record) override {
    auto val = child->eval(record);
    const std::string text = val.as_string();
    bool matches =
        like_match(text.data(), pattern.data()); // Extend the arguments if convenient
    res.value = static_cast<int64_t>(matches);
    return res;
  }

  std::ostream& print_to_ostream(std::ostream& os) const override {
    os << *child << " LIKE \"" << pattern << '"';
    return os;
  }

private:
  std::unique_ptr<Expr> child;
  std::string pattern; // standard escapes already resolved by the preprocessor
  Value res;
};
