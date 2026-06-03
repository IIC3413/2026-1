
// Generated from IIC3413DBParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  IIC3413DBParser : public antlr4::Parser {
public:
  enum {
    AND = 1, AS = 2, BETWEEN = 3, CREATE = 4, DISTINCT = 5, DELETE = 6, 
    FROM = 7, INSERT = 8, INTO = 9, INT = 10, LIKE = 11, LIMIT = 12, OR = 13, 
    SELECT = 14, STR = 15, TABLE = 16, VALUES = 17, VACUUM = 18, WHERE = 19, 
    LEFT = 20, FULL = 21, OUTER = 22, JOIN = 23, ON = 24, UPDATE = 25, SET = 26, 
    EC = 27, EQ = 28, NE = 29, GT = 30, LT = 31, GE = 32, LE = 33, ASSIGN = 34, 
    COMMA = 35, ASTERISK = 36, MINUS = 37, SLASH = 38, MODULO = 39, PLUS = 40, 
    DOT = 41, L_PAR = 42, R_PAR = 43, INTEGER = 44, STRING = 45, IDENTIFIER = 46, 
    WHITE_SPACE = 47, COMMENT_INPUT = 48, LINE_COMMENT = 49, UNRECOGNIZED = 50
  };

  enum {
    RuleRoot = 0, RuleQuery = 1, RuleCreateQuery = 2, RuleInsertQuery = 3, 
    RuleSelectQuery = 4, RuleUpdateQuery = 5, RuleDeleteQuery = 6, RuleSchema = 7, 
    RuleDatatype = 8, RuleSelectStatement = 9, RuleColumnList = 10, RuleFromStatement = 11, 
    RuleTableList = 12, RuleTableListItem = 13, RuleLeftOuterJoin = 14, 
    RuleFullOuterJoin = 15, RuleOuterJoinOn = 16, RuleOuterJoinComp = 17, 
    RuleTable = 18, RuleWhereStatement = 19, RuleAndExpr = 20, RuleSimpleExpr = 21, 
    RuleComparisonExpr = 22, RuleLikeExpr = 23, RuleBetweenExpr = 24, RuleAdditiveExpr = 25, 
    RuleMultiplicativeExpr = 26, RuleUnaryExpr = 27, RuleAtomicExpr = 28, 
    RuleAssignmentList = 29, RuleAssignment = 30, RuleColumnOrConstant = 31, 
    RuleColumn = 32, RuleConstant = 33, RuleIdentifier = 34, RuleLimitStatement = 35, 
    RuleKeyword = 36
  };

  explicit IIC3413DBParser(antlr4::TokenStream *input);

  IIC3413DBParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~IIC3413DBParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RootContext;
  class QueryContext;
  class CreateQueryContext;
  class InsertQueryContext;
  class SelectQueryContext;
  class UpdateQueryContext;
  class DeleteQueryContext;
  class SchemaContext;
  class DatatypeContext;
  class SelectStatementContext;
  class ColumnListContext;
  class FromStatementContext;
  class TableListContext;
  class TableListItemContext;
  class LeftOuterJoinContext;
  class FullOuterJoinContext;
  class OuterJoinOnContext;
  class OuterJoinCompContext;
  class TableContext;
  class WhereStatementContext;
  class AndExprContext;
  class SimpleExprContext;
  class ComparisonExprContext;
  class LikeExprContext;
  class BetweenExprContext;
  class AdditiveExprContext;
  class MultiplicativeExprContext;
  class UnaryExprContext;
  class AtomicExprContext;
  class AssignmentListContext;
  class AssignmentContext;
  class ColumnOrConstantContext;
  class ColumnContext;
  class ConstantContext;
  class IdentifierContext;
  class LimitStatementContext;
  class KeywordContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QueryContext *query();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RootContext* root();

  class  QueryContext : public antlr4::ParserRuleContext {
  public:
    QueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CreateQueryContext *createQuery();
    InsertQueryContext *insertQuery();
    SelectQueryContext *selectQuery();
    UpdateQueryContext *updateQuery();
    DeleteQueryContext *deleteQuery();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QueryContext* query();

  class  CreateQueryContext : public antlr4::ParserRuleContext {
  public:
    CreateQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *TABLE();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *L_PAR();
    std::vector<SchemaContext *> schema();
    SchemaContext* schema(size_t i);
    antlr4::tree::TerminalNode *R_PAR();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateQueryContext* createQuery();

  class  InsertQueryContext : public antlr4::ParserRuleContext {
  public:
    InsertQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    antlr4::tree::TerminalNode *INTO();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *VALUES();
    antlr4::tree::TerminalNode *L_PAR();
    std::vector<ConstantContext *> constant();
    ConstantContext* constant(size_t i);
    antlr4::tree::TerminalNode *R_PAR();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertQueryContext* insertQuery();

  class  SelectQueryContext : public antlr4::ParserRuleContext {
  public:
    SelectQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectStatementContext *selectStatement();
    FromStatementContext *fromStatement();
    WhereStatementContext *whereStatement();
    LimitStatementContext *limitStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectQueryContext* selectQuery();

  class  UpdateQueryContext : public antlr4::ParserRuleContext {
  public:
    UpdateQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UPDATE();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *SET();
    AssignmentListContext *assignmentList();
    WhereStatementContext *whereStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UpdateQueryContext* updateQuery();

  class  DeleteQueryContext : public antlr4::ParserRuleContext {
  public:
    DeleteQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *FROM();
    IdentifierContext *identifier();
    WhereStatementContext *whereStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeleteQueryContext* deleteQuery();

  class  SchemaContext : public antlr4::ParserRuleContext {
  public:
    SchemaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    DatatypeContext *datatype();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaContext* schema();

  class  DatatypeContext : public antlr4::ParserRuleContext {
  public:
    DatatypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STR();
    antlr4::tree::TerminalNode *INT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DatatypeContext* datatype();

  class  SelectStatementContext : public antlr4::ParserRuleContext {
  public:
    SelectStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *ASTERISK();
    ColumnListContext *columnList();
    antlr4::tree::TerminalNode *DISTINCT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectStatementContext* selectStatement();

  class  ColumnListContext : public antlr4::ParserRuleContext {
  public:
    ColumnListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ColumnContext *> column();
    ColumnContext* column(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnListContext* columnList();

  class  FromStatementContext : public antlr4::ParserRuleContext {
  public:
    FromStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    TableListContext *tableList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FromStatementContext* fromStatement();

  class  TableListContext : public antlr4::ParserRuleContext {
  public:
    TableListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TableListItemContext *> tableListItem();
    TableListItemContext* tableListItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableListContext* tableList();

  class  TableListItemContext : public antlr4::ParserRuleContext {
  public:
    TableListItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LeftOuterJoinContext *leftOuterJoin();
    FullOuterJoinContext *fullOuterJoin();
    TableContext *table();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableListItemContext* tableListItem();

  class  LeftOuterJoinContext : public antlr4::ParserRuleContext {
  public:
    LeftOuterJoinContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAR();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *LEFT();
    antlr4::tree::TerminalNode *OUTER();
    antlr4::tree::TerminalNode *JOIN();
    antlr4::tree::TerminalNode *ON();
    OuterJoinOnContext *outerJoinOn();
    antlr4::tree::TerminalNode *R_PAR();
    antlr4::tree::TerminalNode *AS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LeftOuterJoinContext* leftOuterJoin();

  class  FullOuterJoinContext : public antlr4::ParserRuleContext {
  public:
    FullOuterJoinContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAR();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *FULL();
    antlr4::tree::TerminalNode *OUTER();
    antlr4::tree::TerminalNode *JOIN();
    antlr4::tree::TerminalNode *ON();
    OuterJoinOnContext *outerJoinOn();
    antlr4::tree::TerminalNode *R_PAR();
    antlr4::tree::TerminalNode *AS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FullOuterJoinContext* fullOuterJoin();

  class  OuterJoinOnContext : public antlr4::ParserRuleContext {
  public:
    OuterJoinOnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<OuterJoinCompContext *> outerJoinComp();
    OuterJoinCompContext* outerJoinComp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OuterJoinOnContext* outerJoinOn();

  class  OuterJoinCompContext : public antlr4::ParserRuleContext {
  public:
    OuterJoinCompContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ColumnContext *> column();
    ColumnContext* column(size_t i);
    antlr4::tree::TerminalNode *EQ();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OuterJoinCompContext* outerJoinComp();

  class  TableContext : public antlr4::ParserRuleContext {
  public:
    TableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *AS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableContext* table();

  class  WhereStatementContext : public antlr4::ParserRuleContext {
  public:
    WhereStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHERE();
    AndExprContext *andExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhereStatementContext* whereStatement();

  class  AndExprContext : public antlr4::ParserRuleContext {
  public:
    AndExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimpleExprContext *> simpleExpr();
    SimpleExprContext* simpleExpr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AndExprContext* andExpr();

  class  SimpleExprContext : public antlr4::ParserRuleContext {
  public:
    SimpleExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ComparisonExprContext *comparisonExpr();
    LikeExprContext *likeExpr();
    BetweenExprContext *betweenExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleExprContext* simpleExpr();

  class  ComparisonExprContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *op = nullptr;
    ComparisonExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ColumnOrConstantContext *> columnOrConstant();
    ColumnOrConstantContext* columnOrConstant(size_t i);
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NE();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *GE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComparisonExprContext* comparisonExpr();

  class  LikeExprContext : public antlr4::ParserRuleContext {
  public:
    LikeExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColumnContext *column();
    antlr4::tree::TerminalNode *LIKE();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LikeExprContext* likeExpr();

  class  BetweenExprContext : public antlr4::ParserRuleContext {
  public:
    BetweenExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColumnContext *column();
    antlr4::tree::TerminalNode *BETWEEN();
    std::vector<ConstantContext *> constant();
    ConstantContext* constant(size_t i);
    antlr4::tree::TerminalNode *AND();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BetweenExprContext* betweenExpr();

  class  AdditiveExprContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *s40 = nullptr;
    std::vector<antlr4::Token *> op;
    antlr4::Token *s37 = nullptr;
    antlr4::Token *_tset404 = nullptr;
    AdditiveExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExprContext *> multiplicativeExpr();
    MultiplicativeExprContext* multiplicativeExpr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveExprContext* additiveExpr();

  class  MultiplicativeExprContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *s36 = nullptr;
    std::vector<antlr4::Token *> op;
    antlr4::Token *s38 = nullptr;
    antlr4::Token *s39 = nullptr;
    antlr4::Token *_tset427 = nullptr;
    MultiplicativeExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExprContext *> unaryExpr();
    UnaryExprContext* unaryExpr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ASTERISK();
    antlr4::tree::TerminalNode* ASTERISK(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SLASH();
    antlr4::tree::TerminalNode* SLASH(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MODULO();
    antlr4::tree::TerminalNode* MODULO(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeExprContext* multiplicativeExpr();

  class  UnaryExprContext : public antlr4::ParserRuleContext {
  public:
    UnaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AtomicExprContext *atomicExpr();
    antlr4::tree::TerminalNode *PLUS();
    UnaryExprContext *unaryExpr();
    antlr4::tree::TerminalNode *MINUS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryExprContext* unaryExpr();

  class  AtomicExprContext : public antlr4::ParserRuleContext {
  public:
    AtomicExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantContext *constant();
    antlr4::tree::TerminalNode *L_PAR();
    AdditiveExprContext *additiveExpr();
    antlr4::tree::TerminalNode *R_PAR();
    ColumnContext *column();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AtomicExprContext* atomicExpr();

  class  AssignmentListContext : public antlr4::ParserRuleContext {
  public:
    AssignmentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssignmentContext *> assignment();
    AssignmentContext* assignment(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentListContext* assignmentList();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *ASSIGN();
    AdditiveExprContext *additiveExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentContext* assignment();

  class  ColumnOrConstantContext : public antlr4::ParserRuleContext {
  public:
    ColumnOrConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColumnContext *column();
    ConstantContext *constant();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnOrConstantContext* columnOrConstant();

  class  ColumnContext : public antlr4::ParserRuleContext {
  public:
    ColumnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnContext* column();

  class  ConstantContext : public antlr4::ParserRuleContext {
  public:
    ConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantContext* constant();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    KeywordContext *keyword();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  LimitStatementContext : public antlr4::ParserRuleContext {
  public:
    LimitStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIMIT();
    antlr4::tree::TerminalNode *INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LimitStatementContext* limitStatement();

  class  KeywordContext : public antlr4::ParserRuleContext {
  public:
    KeywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *BETWEEN();
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *DISTINCT();
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *INSERT();
    antlr4::tree::TerminalNode *INTO();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *LIKE();
    antlr4::tree::TerminalNode *LIMIT();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *STR();
    antlr4::tree::TerminalNode *TABLE();
    antlr4::tree::TerminalNode *UPDATE();
    antlr4::tree::TerminalNode *VALUES();
    antlr4::tree::TerminalNode *WHERE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeywordContext* keyword();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

