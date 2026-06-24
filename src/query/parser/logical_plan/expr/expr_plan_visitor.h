#pragma once

class ExprPlanArithmetic;
class ExprPlanBetween;
class ExprPlanColumn;
class ExprPlanEquals;
class ExprPlanLess;
class ExprPlanLike;
class ExprPlanLessOrEquals;
class ExprPlanNotEquals;
class ExprPlanTerm;

class ExprPlanVisitor {
public:
  virtual ~ExprPlanVisitor() = default;

  virtual void visit(ExprPlanColumn&) = 0;

  virtual void visit(ExprPlanTerm&) = 0;

  virtual void visit(ExprPlanEquals&) = 0;

  virtual void visit(ExprPlanNotEquals&) = 0;

  virtual void visit(ExprPlanLess&) = 0;

  virtual void visit(ExprPlanLessOrEquals&) = 0;

  virtual void visit(ExprPlanBetween&) = 0;

  virtual void visit(ExprPlanLike&) = 0;

  virtual void visit(ExprPlanArithmetic&) = 0;
};
