#pragma once

#include "system/tx_id.h"

class CartesianProductPlan;
class JoinPlan;
class LeftOuterJoinPlan;
class FullOuterJoinPlan;
class ProjectionPlan;
class RelationPlan;
class CreationPlan;
class InsertionPlan;
class SelectionPlan;
class IndexCreationPlan;

class LogicalPlanVisitor {
public:
  LogicalPlanVisitor(TxID tx_id)
      : tx_id{tx_id} {};

  TxID tx_id;

  virtual void visit(CartesianProductPlan&) = 0;

  virtual void visit(ProjectionPlan&) = 0;

  virtual void visit(CreationPlan&) = 0;

  virtual void visit(InsertionPlan&) = 0;

  virtual void visit(SelectionPlan&) = 0;

  virtual void visit(RelationPlan&) = 0;

  virtual void visit(JoinPlan&) = 0;

  virtual void visit(LeftOuterJoinPlan&) = 0;

  virtual void visit(FullOuterJoinPlan&) = 0;

  virtual void visit(IndexCreationPlan&) = 0;
};
