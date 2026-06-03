#include "query_preprocessor.h"

#include <any>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "exceptions/exceptions.h"
#include "query/parser/logical_plan/expr/expr_plans.h"
#include "query/parser/logical_plan/plans.h"
#include "relational_model/schema.h"
#include "system/system.h"

Constant get_constant(IIC3413DBParser::ConstantContext* ctx) {
  if (ctx->STRING() != nullptr) {
    auto string = ctx->STRING()->getText();
    string = string.substr(1, string.size() - 2);
    if (string.size() > Value::MAX_STRLEN) {
      throw QueryException(
          "String \"" + string + "\" is too long (" + std::to_string(string.size()) + " > " +
          std::to_string(Value::MAX_STRLEN) + ")"
      );
    }
    return string;
  } else if (ctx->INTEGER() != nullptr) {
    try {
      return std::stoll(ctx->INTEGER()->getText());
    } catch (std::out_of_range& e) {
      throw QueryException("Integer " + ctx->INTEGER()->getText() + " is out of range");
    }
  } else {
    throw NotImplementedException("Unhandled Constant: " + ctx->getText());
  }
}

Value get_value(IIC3413DBParser::ConstantContext* ctx) {
  const auto result = get_constant(ctx);
  if (std::holds_alternative<int64_t>(result)) {
    return Value(std::get<int64_t>(result));
  }
  return Value(std::get<std::string>(result));
}

std::any QueryPreprocessor::visitRoot(IIC3413DBParser::RootContext* ctx) {
  visitChildren(ctx);
  return 0;
}

std::any QueryPreprocessor::visitQuery(IIC3413DBParser::QueryContext* ctx) {
  visitChildren(ctx);
  return 0;
}

std::any QueryPreprocessor::visitCreateQuery(IIC3413DBParser::CreateQueryContext* ctx) {
  auto table_name = ctx->identifier()->getText();
  if (catalog.table_exists(table_name, tx_id)) {
    throw QueryException("Table " + table_name + " already exists");
  }

  std::vector<ColumnInfo> columns;
  for (const auto& schema : ctx->schema()) {
    const auto column_name = schema->identifier()->getText();
    const auto column_datatype = schema->datatype();
    if (column_datatype->STR() != nullptr) {
      columns.push_back({column_name, DataType::STR});
    } else if (column_datatype->INT() != nullptr) {
      columns.push_back({column_name, DataType::INT});
    } else {
      throw NotImplementedException("Unhandled DataType:" + column_datatype->getText());
    }
  }

  Schema schema = Schema(columns);
  current_logical_plan = std::make_unique<CreationPlan>(table_name, std::move(schema));

  return 0;
}

std::any QueryPreprocessor::visitInsertQuery(IIC3413DBParser::InsertQueryContext* ctx) {
  auto table_name = ctx->identifier()->getText();
  if (!catalog.table_exists(table_name, tx_id)) {
    throw QueryException("Table " + table_name + " does not exist");
  }

  const auto& table_info = catalog.get_table_info(table_name, tx_id);
  if (table_info == nullptr) {
    throw QueryException("Table " + table_name + " does not exist");
  }
  const auto& columns = table_info->schema->columns;
  if (columns.size() - 1 != ctx->constant().size()) { // -1 to ignore RID column
    throw QueryException(
        "Table " + table_name + " has " + std::to_string(columns.size() - 1) + " columns, but " +
        std::to_string(ctx->constant().size()) + " values were provided"
    );
  }

  std::vector<Constant> values;
  for (size_t i = 0; i < columns.size() - 1; i++) {
    const auto result = get_constant(ctx->constant(i));
    switch (columns[i].datatype) {
    case DataType::INT: {
      if (!std::holds_alternative<int64_t>(result)) {
        throw QueryException("Value for " + table_name + "." + columns[i].name + " must be INT");
      }
      break;
    }
    case DataType::STR: {
      if (!std::holds_alternative<std::string>(result))
        throw QueryException("Values for " + table_name + "." + columns[i].name + " must be STRING");
      break;
    }
    default: {
      throw NotImplementedException(
          "Unhandled DataType: " + std::to_string(static_cast<int>(columns[i].datatype))
      );
    }
    }
    values.emplace_back(result);
  }

  current_logical_plan = std::make_unique<InsertionPlan>(table_name, std::move(values));
  return 0;
}

std::any QueryPreprocessor::visitSelectQuery(IIC3413DBParser::SelectQueryContext* ctx) {
  if (ctx->limitStatement()) {
    try {
      limit = std::stoll(ctx->limitStatement()->INTEGER()->getText());
    } catch (std::out_of_range& e) {
      throw QueryException("Integer " + ctx->limitStatement()->INTEGER()->getText() + " is out of range");
    }

    if (limit <= 0) {
      throw QueryException("Invalid LIMIT " + std::to_string(limit));
    }
  }
  visit(ctx->fromStatement());
  if (ctx->whereStatement() != nullptr) {
    visit(ctx->whereStatement());
  }
  visit(ctx->selectStatement());
  return 0;
}

std::any QueryPreprocessor::visitDeleteQuery(IIC3413DBParser::DeleteQueryContext* ctx) {
  auto table_name = ctx->identifier()->getText();

  const auto table_info = catalog.get_table_info(table_name, tx_id);
  if (table_info == nullptr) {
    throw QueryException("Table " + table_name + " does not exist");
  }

  from_tables[table_name] = table_name;

  current_logical_plan = std::make_unique<RelationPlan>(table_name, table_name);

  if (ctx->whereStatement() != nullptr) {
    visit(ctx->whereStatement());
  }

  current_logical_plan = std::make_unique<DeletionPlan>(*table_info, std::move(current_logical_plan));

  return 0;
}

std::any QueryPreprocessor::visitUpdateQuery(IIC3413DBParser::UpdateQueryContext* ctx) {
  auto table_name = ctx->identifier()->getText();
  if (!catalog.table_exists(table_name, tx_id)) {
    throw QueryException("Table " + table_name + " does not exist");
  }

  const auto table_info = catalog.get_table_info(table_name, tx_id);
  if (table_info == nullptr) {
    throw QueryException("Table " + table_name + " does not exist");
  }
  const auto& columns = table_info->schema->columns;

  // added to from_tables so the get_column can find the table used in the update statement
  from_tables[table_name] = table_name;

  std::vector<std::pair<int, std::unique_ptr<ExprPlan>>> assignments;
  for (const auto& assignment_ctx : ctx->assignmentList()->assignment()) {
    auto column_name = assignment_ctx->identifier()->getText();
    int column_idx = -1;
    for (size_t i = 0; i < columns.size(); i++) {
      if (columns[i].name == column_name) {
        column_idx = i;
        break;
      }
    }
    if (column_idx == -1) {
      throw QueryException("Column " + column_name + " does not exist in table " + table_name);
    }

    assignment_ctx->additiveExpr()->accept(this);

    assignments.emplace_back(column_idx, std::move(current_expr));
  }
  current_logical_plan = std::make_unique<RelationPlan>(table_name, table_name);

  if (ctx->whereStatement() != nullptr) {
    visit(ctx->whereStatement());
  }
  current_logical_plan =
      std::make_unique<UpdatePlan>(*table_info, std::move(assignments), std::move(current_logical_plan));

  from_tables.clear();
  return 0;
}

std::any QueryPreprocessor::visitSelectStatement(IIC3413DBParser::SelectStatementContext* ctx) {
  std::vector<Column> projection;
  if (ctx->ASTERISK() != nullptr) {
    for (auto&& [alias, table_name] : from_tables) {
      auto table_info = catalog.get_table_info(table_name, tx_id);
      if (table_info == nullptr)
        throw QueryException("Table " + table_name + " does not exist");
      for (const auto& column : table_info->schema->columns) {
        if (column.datatype != DataType::RID) {
          projection.emplace_back(alias, table_name, column);
        }
      }
    }
    for (auto&& [alias, table_names] : from_outer_join_tables) {
      auto table_info = catalog.get_table_info(table_names.first, tx_id);
      if (table_info == nullptr)
        throw QueryException("Table " + table_names.first + " does not exist");
      for (const auto& column : table_info->schema->columns) {
        projection.emplace_back(alias, table_names.first, column);
      }
      table_info = catalog.get_table_info(table_names.second, tx_id);
      if (table_info == nullptr)
        throw QueryException("Table " + table_names.second + " does not exist");
      for (const auto& column : table_info->schema->columns) {
        projection.emplace_back(alias, table_names.second, column);
      }
    }
  } else {
    for (const auto& column_ctx : ctx->columnList()->column()) {
      auto column = get_column(column_ctx);
      projection.emplace_back(column);
    }
  }
  current_logical_plan = std::make_unique<ProjectionPlan>(
      std::move(current_logical_plan), ctx->DISTINCT() != nullptr, limit, std::move(projection)
  );
  return 0;
}

std::any QueryPreprocessor::visitFromStatement(IIC3413DBParser::FromStatementContext* ctx) {
  visitChildren(ctx);
  return 0;
};

std::any QueryPreprocessor::visitTableList(IIC3413DBParser::TableListContext* ctx) {
  if (ctx->tableListItem().size() == 1) {
    visit(ctx->tableListItem(0));
    return 0;
  }
  std::vector<std::unique_ptr<LogicalPlan>> relations;
  for (const auto& item_ctx : ctx->tableListItem()) {
    visit(item_ctx);
    relations.push_back(std::move(current_logical_plan));
  }
  current_logical_plan = std::make_unique<CartesianProductPlan>(std::move(relations));
  return 0;
}

std::any QueryPreprocessor::visitTableListItem(IIC3413DBParser::TableListItemContext* ctx) {
  auto table_ctx = ctx->table();
  if (table_ctx != nullptr) {
    visit(table_ctx);
    return 0;
  }
  auto left_outer_join_ctx = ctx->leftOuterJoin();
  if (left_outer_join_ctx != nullptr) {
    visit(left_outer_join_ctx);
    return 0;
  }
  visit(ctx->fullOuterJoin());
  return 0;
}

std::any QueryPreprocessor::visitTable(IIC3413DBParser::TableContext* ctx) {
  auto table_name = ctx->identifier(0)->getText();
  if (!catalog.table_exists(table_name, tx_id)) {
    throw QueryException("Table " + table_name + " does not exist");
  }
  std::string alias;
  if (ctx->AS() != nullptr) {
    alias = ctx->identifier(1)->getText();
  } else {
    alias = table_name;
  }
  if (!from_tables.insert({alias, table_name}).second) {
    throw QueryException("Table " + alias + " should only appear once in the FROM clause");
  }
  current_logical_plan = std::make_unique<RelationPlan>(alias, table_name);
  return 0;
}

bool QueryPreprocessor::table_has_column(const std::string& table, const std::string& column_name) const {
  const auto& table_info = catalog.get_table_info(table, tx_id);
  for (const auto& column : table_info->schema->columns) {
    if (column.name == column_name) {
      return true;
    }
  }
  return false;
}

Column
QueryPreprocessor::get_outer_join_table_column(IIC3413DBParser::ColumnContext* ctx, std::string alias) {
  if (ctx->identifier().size() != 2) {
    throw QueryException("Invalid call of column getter with implicit column");
  }
  auto table_name = ctx->identifier(0)->getText();
  auto column_name = ctx->identifier(1)->getText();
  if (!table_has_column(table_name, column_name)) {
    throw QueryException("Table " + table_name + " does not have column " + column_name);
  }
  auto table_info = catalog.get_table_info(table_name, tx_id);
  DataType datatype = DataType::INVALID;
  for (const auto& column : table_info->schema->columns) {
    if (column.name == column_name) {
      datatype = column.datatype;
    }
  }
  return Column(alias, table_name, {column_name, datatype, table_info->table_id});
}

std::any QueryPreprocessor::visitLeftOuterJoin(IIC3413DBParser::LeftOuterJoinContext* ctx) {
  std::string alias = ctx->identifier(2)->getText();
  std::string l_table_name = ctx->identifier(0)->getText();
  if (!catalog.table_exists(l_table_name, tx_id)) {
    throw QueryException("Table " + l_table_name + " does not exist");
  }
  std::string r_table_name = ctx->identifier(1)->getText();
  if (!catalog.table_exists(r_table_name, tx_id)) {
    throw QueryException("Table " + r_table_name + " does not exist");
  }

  if (!from_outer_join_tables.insert({alias, {l_table_name, r_table_name}}).second) {
    throw QueryException("Table " + alias + " should only appear once in the FROM clause");
  }

  std::vector<std::pair<Column, Column>> columns;
  for (auto& join_on : ctx->outerJoinOn()->outerJoinComp()) {
    auto l_column = get_outer_join_table_column(join_on->column(0), alias);
    auto r_column = get_outer_join_table_column(join_on->column(1), alias);
    if (l_column.info.datatype != r_column.info.datatype) {
      throw QueryException("Cannot compare different DataTypes: " + join_on->getText());
    }
    columns.emplace_back(l_column, r_column);
  }
  current_logical_plan = std::make_unique<LeftOuterJoinPlan>(
      alias, std::make_unique<RelationPlan>(alias, l_table_name),
      std::make_unique<RelationPlan>(alias, r_table_name), std::move(columns)
  );
  return 0;
}

std::any QueryPreprocessor::visitFullOuterJoin(IIC3413DBParser::FullOuterJoinContext* ctx) {
  std::string alias = ctx->identifier(2)->getText();
  std::string l_table_name = ctx->identifier(0)->getText();
  if (!catalog.table_exists(l_table_name, tx_id)) {
    throw QueryException("Table " + l_table_name + " does not exist");
  }
  std::string r_table_name = ctx->identifier(1)->getText();
  if (!catalog.table_exists(r_table_name, tx_id)) {
    throw QueryException("Table " + r_table_name + " does not exist");
  }
  if (!from_outer_join_tables.insert({alias, {l_table_name, r_table_name}}).second) {
    throw QueryException("Table " + alias + " should only appear once in the FROM clause");
  }

  std::vector<std::pair<Column, Column>> columns;
  for (auto& join_on : ctx->outerJoinOn()->outerJoinComp()) {
    auto l_column = get_outer_join_table_column(join_on->column(0), alias);
    auto r_column = get_outer_join_table_column(join_on->column(1), alias);
    if (l_column.info.datatype != r_column.info.datatype) {
      throw QueryException("Cannot compare different DataTypes: " + join_on->getText());
    }
    columns.emplace_back(l_column, r_column);
  }
  current_logical_plan = std::make_unique<FullOuterJoinPlan>(
      alias, std::make_unique<RelationPlan>(alias, l_table_name),
      std::make_unique<RelationPlan>(alias, r_table_name), std::move(columns)
  );
  return 0;
}

std::any QueryPreprocessor::visitWhereStatement(IIC3413DBParser::WhereStatementContext* ctx) {
  visitChildren(ctx);
  return 0;
}

std::any QueryPreprocessor::visitAdditiveExpr(IIC3413DBParser::AdditiveExprContext* ctx) {
  auto mult_exprs = ctx->multiplicativeExpr();
  if (mult_exprs.size() == 1) {
    mult_exprs[0]->accept(this);
    return 0;
  }

  std::unique_ptr<ExprPlan> final_expr;

  for (size_t i = 1; i < mult_exprs.size(); i++) {
    if (i == 1) {
      mult_exprs[0]->accept(this);
      auto lhs = std::move(current_expr);
      mult_exprs[1]->accept(this);
      auto rhs = std::move(current_expr);
      final_expr =
          std::make_unique<ExprPlanArithmetic>(std::move(lhs), ctx->op[0]->getText(), std::move(rhs));
      continue;
    }

    mult_exprs[i]->accept(this);
    auto rhs = std::move(current_expr);

    auto op_text = ctx->op[i - 1]->getText();

    final_expr = std::make_unique<ExprPlanArithmetic>(std::move(final_expr), op_text, std::move(rhs));
  }
  current_expr = std::move(final_expr);
  return 0;
}

std::any QueryPreprocessor::visitMultiplicativeExpr(IIC3413DBParser::MultiplicativeExprContext* ctx) {
  auto unary_exprs = ctx->unaryExpr();
  if (unary_exprs.size() == 1) {
    unary_exprs[0]->accept(this);
    return 0;
  }

  std::unique_ptr<ExprPlan> final_expr;

  for (size_t i = 1; i < unary_exprs.size(); i++) {
    if (i == 1) {
      unary_exprs[0]->accept(this);
      auto lhs = std::move(current_expr);
      unary_exprs[1]->accept(this);
      auto rhs = std::move(current_expr);
      final_expr =
          std::make_unique<ExprPlanArithmetic>(std::move(lhs), ctx->op[0]->getText(), std::move(rhs));
      continue;
    }

    unary_exprs[i]->accept(this);
    auto rhs = std::move(current_expr);

    auto op_text = ctx->op[i - 1]->getText();

    final_expr = std::make_unique<ExprPlanArithmetic>(std::move(final_expr), op_text, std::move(rhs));
  }
  current_expr = std::move(final_expr);
  return 0;
}

std::any QueryPreprocessor::visitUnaryExpr(IIC3413DBParser::UnaryExprContext* ctx) {
  if (ctx->atomicExpr()) {
    ctx->atomicExpr()->accept(this);
  } else if (ctx->unaryExpr()) {
    ctx->unaryExpr()->accept(this);
    if (ctx->MINUS()) {
      current_expr = std::make_unique<ExprPlanArithmetic>("-", std::move(current_expr));
    }
  }
  return 0;
}

std::any QueryPreprocessor::visitAtomicExpr(IIC3413DBParser::AtomicExprContext* ctx) {
  if (ctx->constant()) {
    current_expr = std::make_unique<ExprPlanTerm>(get_value(ctx->constant()));
  } else if (ctx->column()) {
    current_expr = std::make_unique<ExprPlanColumn>(get_column(ctx->column()));
  } else if (ctx->additiveExpr()) {
    ctx->additiveExpr()->accept(this);
  }
  return 0;
}

std::any QueryPreprocessor::visitAndExpr(IIC3413DBParser::AndExprContext* ctx) {
  std::vector<std::unique_ptr<ExprPlan>> expressions;
  for (const auto& simpleExpr : ctx->simpleExpr()) {
    simpleExpr->accept(this);
    expressions.emplace_back(std::move(current_expr));
  }
  current_logical_plan =
      std::make_unique<SelectionPlan>(std::move(current_logical_plan), std::move(expressions));
  return 0;
}

std::any QueryPreprocessor::visitSimpleExpr(IIC3413DBParser::SimpleExprContext* ctx) {
  visitChildren(ctx);
  return 0;
}

std::any QueryPreprocessor::visitComparisonExpr(IIC3413DBParser::ComparisonExprContext* ctx) {
  ctx->columnOrConstant(0)->accept(this);
  auto lhs = std::move(current_expr);
  auto lhs_type = lhs->get_datatype();

  ctx->columnOrConstant(1)->accept(this);
  auto rhs = std::move(current_expr);
  auto rhs_type = rhs->get_datatype();

  if (lhs_type != rhs_type) {
    throw QueryException("Cannot compare different DataTypes: " + ctx->getText());
  }

  auto op = ctx->op->getText();
  if (op == "==") {
    current_expr = std::make_unique<ExprPlanEquals>(std::move(lhs), std::move(rhs));
  } else if (op == "!=") {
    current_expr = std::make_unique<ExprPlanNotEquals>(std::move(lhs), std::move(rhs));
  } else if (op == "<") {
    current_expr = std::make_unique<ExprPlanLess>(std::move(lhs), std::move(rhs));
  } else if (op == "<=") {
    current_expr = std::make_unique<ExprPlanLessOrEquals>(std::move(lhs), std::move(rhs));
  } else if (op == ">=") {
    current_expr = std::make_unique<ExprPlanLessOrEquals>(std::move(rhs), std::move(lhs));
  } else if (op == ">") {
    current_expr = std::make_unique<ExprPlanLess>(std::move(rhs), std::move(lhs));
  } else {
    throw std::invalid_argument(op + " not recognized as a valid ComparisonExpr operator");
  }
  return 0;
}

std::any QueryPreprocessor::visitLikeExpr(IIC3413DBParser::LikeExprContext* ctx) {
  auto col_expr = std::make_unique<ExprPlanColumn>(get_column(ctx->column()));
  if (col_expr->column.info.datatype != DataType::STR) {
    throw QueryException("LIKE can only be applied to strings");
  }
  auto pattern = ctx->STRING()->getText();
  pattern = pattern.substr(1, pattern.size() - 2); // remove double quotes
  current_expr = std::make_unique<ExprPlanLike>(std::move(col_expr), std::move(pattern));
  return 0;
}

std::any QueryPreprocessor::visitBetweenExpr(IIC3413DBParser::BetweenExprContext* ctx) {
  auto col_expr = std::make_unique<ExprPlanColumn>(get_column(ctx->column()));

  auto lower_bound = get_value(ctx->constant(0));
  auto upper_bound = get_value(ctx->constant(1));

  if (!((lower_bound.is_int() && upper_bound.is_int()) ||
        (lower_bound.is_string() && upper_bound.is_string()))) {
    throw QueryException("BETWEEN bounds must have the same type");
  }
  if (!((lower_bound.is_int() && col_expr->column.info.datatype == DataType::INT) ||
        (lower_bound.is_string() && col_expr->column.info.datatype == DataType::STR))) {
    throw QueryException("BETWEEN bounds must have the same type as the column used");
  }

  current_expr =
      std::make_unique<ExprPlanBetween>(std::move(col_expr), std::move(lower_bound), std::move(upper_bound));
  return 0;
}

std::any QueryPreprocessor::visitColumnOrConstant(IIC3413DBParser::ColumnOrConstantContext* ctx) {
  if (ctx->column()) {
    current_expr = std::make_unique<ExprPlanColumn>(get_column(ctx->column()));
    return 0;
  }
  current_expr = std::make_unique<ExprPlanTerm>(get_value(ctx->constant()));
  return 0;
}

Column QueryPreprocessor::get_column(IIC3413DBParser::ColumnContext* ctx) const {
  if (ctx->identifier().size() == 2) {
    auto alias = ctx->identifier(0)->getText();
    auto column_name = ctx->identifier(1)->getText();

    auto iot = from_outer_join_tables.find(alias);
    if (iot != from_outer_join_tables.end()) {
      std::string table;
      DataType datatype = DataType::INVALID;
      const TableInfo* table_info;
      if (table_has_column(iot->second.first, column_name)) {
        table = iot->second.first;
        table_info = catalog.get_table_info(table, tx_id);
        for (const auto& column : table_info->schema->columns) {
          if (column.name == column_name) {
            datatype = column.datatype;
          }
        }
      } else if (table_has_column(iot->second.second, column_name)) {
        table = iot->second.second;
        table_info = catalog.get_table_info(table, tx_id);
        for (const auto& column : table_info->schema->columns) {
          if (column.name == column_name) {
            datatype = column.datatype;
          }
        }
      } else {
        throw QueryException("Column " + column_name + " not present in " + alias + " outer join");
      }
      return Column(alias, table, {column_name, datatype, table_info->table_id});
    }

    auto it = from_tables.find(alias);
    if (it == from_tables.end()) {
      throw QueryException("Table " + alias + ", not present in FROM");
    }
    auto table = it->second;
    auto table_info = catalog.get_table_info(table, tx_id);
    DataType datatype = DataType::INVALID;
    for (const auto& column : table_info->schema->columns) {
      if (column.name == column_name) {
        datatype = column.datatype;
      }
    }
    return Column(alias, table, {column_name, datatype, table_info->table_id});
  }

  // Only column name.
  auto column_name = ctx->identifier(0)->getText();
  // try to infer the table from catalog from tables named in FROM.
  const std::string* found_table = nullptr;
  for (auto&& [alias, table_name] : from_tables) {
    if (alias != table_name) {
      continue; // skip from tables with aliases
    }

    auto& schema = catalog.get_table_info(table_name, tx_id)->schema;
    for (size_t i = 0; i < schema->columns.size(); i++) {
      if (schema->columns[i].name == column_name) {
        if (found_table == nullptr) {
          found_table = &table_name;
        } else {
          throw QueryException(
              "Ambiguous column `" + column_name + "`, present in tables `" + *found_table + "` and `" +
              table_name + "`"
          );
        }
      }
    }
  }
  if (found_table == nullptr) {
    throw QueryException("Could not infer the table where column `" + column_name + "` belongs");
  }
  auto table_info = catalog.get_table_info(*found_table, tx_id);
  DataType datatype = DataType::INVALID;
  for (const auto& column : table_info->schema->columns) {
    if (column.name == column_name) {
      datatype = column.datatype;
    }
  }
  return Column(*found_table, *found_table, {column_name, datatype, table_info->table_id});
}
