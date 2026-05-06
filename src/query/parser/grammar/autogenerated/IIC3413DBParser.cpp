
// Generated from IIC3413DBParser.g4 by ANTLR 4.13.1


#include "IIC3413DBParserVisitor.h"

#include "IIC3413DBParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct IIC3413DBParserStaticData final {
  IIC3413DBParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IIC3413DBParserStaticData(const IIC3413DBParserStaticData&) = delete;
  IIC3413DBParserStaticData(IIC3413DBParserStaticData&&) = delete;
  IIC3413DBParserStaticData& operator=(const IIC3413DBParserStaticData&) = delete;
  IIC3413DBParserStaticData& operator=(IIC3413DBParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag iic3413dbparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
IIC3413DBParserStaticData *iic3413dbparserParserStaticData = nullptr;

void iic3413dbparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (iic3413dbparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(iic3413dbparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IIC3413DBParserStaticData>(
    std::vector<std::string>{
      "root", "query", "createQuery", "createTable", "createIndex", "insertQuery", 
      "selectQuery", "schema", "datatype", "selectStatement", "columnList", 
      "fromStatement", "tableList", "table", "whereStatement", "andExpr", 
      "simpleExpr", "comparisonExpr", "likeExpr", "betweenExpr", "columnOrConstant", 
      "column", "constant", "identifier", "limitStatement", "keyword"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "';'", "'=='", "'!='", 
      "'>'", "'<'", "'>='", "'<='", "'='", "','", "'*'", "'-'", "'/'", "'%'", 
      "'+'", "'.'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "AND", "AS", "BETWEEN", "CREATE", "DISTINCT", "DELETE", "FROM", 
      "INDEX", "INSERT", "INTO", "INT", "LIKE", "LIMIT", "OR", "SELECT", 
      "STR", "TABLE", "VALUES", "VACUUM", "WHERE", "LEFT", "FULL", "OUTER", 
      "JOIN", "ON", "UPDATE", "SET", "EC", "EQ", "NE", "GT", "LT", "GE", 
      "LE", "ASSIGN", "COMMA", "ASTERISK", "MINUS", "SLASH", "MODULO", "PLUS", 
      "DOT", "L_PAR", "R_PAR", "INTEGER", "STRING", "IDENTIFIER", "WHITE_SPACE", 
      "COMMENT_INPUT", "LINE_COMMENT", "UNRECOGNIZED"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,198,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,1,0,1,0,1,1,1,1,1,1,3,
  	1,59,8,1,1,2,1,2,3,2,63,8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,72,8,3,10,
  	3,12,3,75,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,5,5,95,8,5,10,5,12,5,98,9,5,1,5,1,5,1,6,1,6,1,6,3,6,105,
  	8,6,1,6,3,6,108,8,6,1,7,1,7,1,7,1,8,1,8,1,9,1,9,3,9,117,8,9,1,9,1,9,3,
  	9,121,8,9,1,10,1,10,1,10,5,10,126,8,10,10,10,12,10,129,9,10,1,11,1,11,
  	1,11,1,12,1,12,1,12,5,12,137,8,12,10,12,12,12,140,9,12,1,13,1,13,1,13,
  	3,13,145,8,13,1,14,1,14,1,14,1,15,1,15,1,15,5,15,153,8,15,10,15,12,15,
  	156,9,15,1,16,1,16,1,16,3,16,161,8,16,1,17,1,17,1,17,3,17,166,8,17,1,
  	18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,3,20,180,8,
  	20,1,21,1,21,1,21,3,21,185,8,21,1,22,1,22,1,23,1,23,3,23,191,8,23,1,24,
  	1,24,1,24,1,25,1,25,1,25,0,0,26,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,0,4,2,0,11,11,16,16,1,0,29,34,1,0,
  	45,46,3,0,1,18,20,20,26,27,190,0,52,1,0,0,0,2,58,1,0,0,0,4,62,1,0,0,0,
  	6,64,1,0,0,0,8,78,1,0,0,0,10,86,1,0,0,0,12,101,1,0,0,0,14,109,1,0,0,0,
  	16,112,1,0,0,0,18,114,1,0,0,0,20,122,1,0,0,0,22,130,1,0,0,0,24,133,1,
  	0,0,0,26,141,1,0,0,0,28,146,1,0,0,0,30,149,1,0,0,0,32,160,1,0,0,0,34,
  	162,1,0,0,0,36,167,1,0,0,0,38,171,1,0,0,0,40,179,1,0,0,0,42,181,1,0,0,
  	0,44,186,1,0,0,0,46,190,1,0,0,0,48,192,1,0,0,0,50,195,1,0,0,0,52,53,3,
  	2,1,0,53,54,5,0,0,1,54,1,1,0,0,0,55,59,3,4,2,0,56,59,3,10,5,0,57,59,3,
  	12,6,0,58,55,1,0,0,0,58,56,1,0,0,0,58,57,1,0,0,0,59,3,1,0,0,0,60,63,3,
  	6,3,0,61,63,3,8,4,0,62,60,1,0,0,0,62,61,1,0,0,0,63,5,1,0,0,0,64,65,5,
  	4,0,0,65,66,5,17,0,0,66,67,3,46,23,0,67,68,5,43,0,0,68,73,3,14,7,0,69,
  	70,5,36,0,0,70,72,3,14,7,0,71,69,1,0,0,0,72,75,1,0,0,0,73,71,1,0,0,0,
  	73,74,1,0,0,0,74,76,1,0,0,0,75,73,1,0,0,0,76,77,5,44,0,0,77,7,1,0,0,0,
  	78,79,5,4,0,0,79,80,5,8,0,0,80,81,5,25,0,0,81,82,3,26,13,0,82,83,5,43,
  	0,0,83,84,3,42,21,0,84,85,5,44,0,0,85,9,1,0,0,0,86,87,5,9,0,0,87,88,5,
  	10,0,0,88,89,3,46,23,0,89,90,5,18,0,0,90,91,5,43,0,0,91,96,3,44,22,0,
  	92,93,5,36,0,0,93,95,3,44,22,0,94,92,1,0,0,0,95,98,1,0,0,0,96,94,1,0,
  	0,0,96,97,1,0,0,0,97,99,1,0,0,0,98,96,1,0,0,0,99,100,5,44,0,0,100,11,
  	1,0,0,0,101,102,3,18,9,0,102,104,3,22,11,0,103,105,3,28,14,0,104,103,
  	1,0,0,0,104,105,1,0,0,0,105,107,1,0,0,0,106,108,3,48,24,0,107,106,1,0,
  	0,0,107,108,1,0,0,0,108,13,1,0,0,0,109,110,3,46,23,0,110,111,3,16,8,0,
  	111,15,1,0,0,0,112,113,7,0,0,0,113,17,1,0,0,0,114,116,5,15,0,0,115,117,
  	5,5,0,0,116,115,1,0,0,0,116,117,1,0,0,0,117,120,1,0,0,0,118,121,5,37,
  	0,0,119,121,3,20,10,0,120,118,1,0,0,0,120,119,1,0,0,0,121,19,1,0,0,0,
  	122,127,3,42,21,0,123,124,5,36,0,0,124,126,3,42,21,0,125,123,1,0,0,0,
  	126,129,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,21,1,0,0,0,129,127,
  	1,0,0,0,130,131,5,7,0,0,131,132,3,24,12,0,132,23,1,0,0,0,133,138,3,26,
  	13,0,134,135,5,36,0,0,135,137,3,26,13,0,136,134,1,0,0,0,137,140,1,0,0,
  	0,138,136,1,0,0,0,138,139,1,0,0,0,139,25,1,0,0,0,140,138,1,0,0,0,141,
  	144,3,46,23,0,142,143,5,2,0,0,143,145,3,46,23,0,144,142,1,0,0,0,144,145,
  	1,0,0,0,145,27,1,0,0,0,146,147,5,20,0,0,147,148,3,30,15,0,148,29,1,0,
  	0,0,149,154,3,32,16,0,150,151,5,1,0,0,151,153,3,32,16,0,152,150,1,0,0,
  	0,153,156,1,0,0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,31,1,0,0,0,156,
  	154,1,0,0,0,157,161,3,34,17,0,158,161,3,36,18,0,159,161,3,38,19,0,160,
  	157,1,0,0,0,160,158,1,0,0,0,160,159,1,0,0,0,161,33,1,0,0,0,162,165,3,
  	40,20,0,163,164,7,1,0,0,164,166,3,40,20,0,165,163,1,0,0,0,165,166,1,0,
  	0,0,166,35,1,0,0,0,167,168,3,42,21,0,168,169,5,12,0,0,169,170,5,46,0,
  	0,170,37,1,0,0,0,171,172,3,42,21,0,172,173,5,3,0,0,173,174,3,44,22,0,
  	174,175,5,1,0,0,175,176,3,44,22,0,176,39,1,0,0,0,177,180,3,42,21,0,178,
  	180,3,44,22,0,179,177,1,0,0,0,179,178,1,0,0,0,180,41,1,0,0,0,181,184,
  	3,46,23,0,182,183,5,42,0,0,183,185,3,46,23,0,184,182,1,0,0,0,184,185,
  	1,0,0,0,185,43,1,0,0,0,186,187,7,2,0,0,187,45,1,0,0,0,188,191,5,47,0,
  	0,189,191,3,50,25,0,190,188,1,0,0,0,190,189,1,0,0,0,191,47,1,0,0,0,192,
  	193,5,13,0,0,193,194,5,45,0,0,194,49,1,0,0,0,195,196,7,3,0,0,196,51,1,
  	0,0,0,17,58,62,73,96,104,107,116,120,127,138,144,154,160,165,179,184,
  	190
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  iic3413dbparserParserStaticData = staticData.release();
}

}

IIC3413DBParser::IIC3413DBParser(TokenStream *input) : IIC3413DBParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

IIC3413DBParser::IIC3413DBParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  IIC3413DBParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *iic3413dbparserParserStaticData->atn, iic3413dbparserParserStaticData->decisionToDFA, iic3413dbparserParserStaticData->sharedContextCache, options);
}

IIC3413DBParser::~IIC3413DBParser() {
  delete _interpreter;
}

const atn::ATN& IIC3413DBParser::getATN() const {
  return *iic3413dbparserParserStaticData->atn;
}

std::string IIC3413DBParser::getGrammarFileName() const {
  return "IIC3413DBParser.g4";
}

const std::vector<std::string>& IIC3413DBParser::getRuleNames() const {
  return iic3413dbparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& IIC3413DBParser::getVocabulary() const {
  return iic3413dbparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IIC3413DBParser::getSerializedATN() const {
  return iic3413dbparserParserStaticData->serializedATN;
}


//----------------- RootContext ------------------------------------------------------------------

IIC3413DBParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::QueryContext* IIC3413DBParser::RootContext::query() {
  return getRuleContext<IIC3413DBParser::QueryContext>(0);
}

tree::TerminalNode* IIC3413DBParser::RootContext::EOF() {
  return getToken(IIC3413DBParser::EOF, 0);
}


size_t IIC3413DBParser::RootContext::getRuleIndex() const {
  return IIC3413DBParser::RuleRoot;
}


std::any IIC3413DBParser::RootContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitRoot(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::RootContext* IIC3413DBParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, IIC3413DBParser::RuleRoot);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    query();
    setState(53);
    match(IIC3413DBParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryContext ------------------------------------------------------------------

IIC3413DBParser::QueryContext::QueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::CreateQueryContext* IIC3413DBParser::QueryContext::createQuery() {
  return getRuleContext<IIC3413DBParser::CreateQueryContext>(0);
}

IIC3413DBParser::InsertQueryContext* IIC3413DBParser::QueryContext::insertQuery() {
  return getRuleContext<IIC3413DBParser::InsertQueryContext>(0);
}

IIC3413DBParser::SelectQueryContext* IIC3413DBParser::QueryContext::selectQuery() {
  return getRuleContext<IIC3413DBParser::SelectQueryContext>(0);
}


size_t IIC3413DBParser::QueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleQuery;
}


std::any IIC3413DBParser::QueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::QueryContext* IIC3413DBParser::query() {
  QueryContext *_localctx = _tracker.createInstance<QueryContext>(_ctx, getState());
  enterRule(_localctx, 2, IIC3413DBParser::RuleQuery);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(58);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::CREATE: {
        enterOuterAlt(_localctx, 1);
        setState(55);
        createQuery();
        break;
      }

      case IIC3413DBParser::INSERT: {
        enterOuterAlt(_localctx, 2);
        setState(56);
        insertQuery();
        break;
      }

      case IIC3413DBParser::SELECT: {
        enterOuterAlt(_localctx, 3);
        setState(57);
        selectQuery();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateQueryContext ------------------------------------------------------------------

IIC3413DBParser::CreateQueryContext::CreateQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::CreateTableContext* IIC3413DBParser::CreateQueryContext::createTable() {
  return getRuleContext<IIC3413DBParser::CreateTableContext>(0);
}

IIC3413DBParser::CreateIndexContext* IIC3413DBParser::CreateQueryContext::createIndex() {
  return getRuleContext<IIC3413DBParser::CreateIndexContext>(0);
}


size_t IIC3413DBParser::CreateQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleCreateQuery;
}


std::any IIC3413DBParser::CreateQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitCreateQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::CreateQueryContext* IIC3413DBParser::createQuery() {
  CreateQueryContext *_localctx = _tracker.createInstance<CreateQueryContext>(_ctx, getState());
  enterRule(_localctx, 4, IIC3413DBParser::RuleCreateQuery);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(62);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(60);
      createTable();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(61);
      createIndex();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateTableContext ------------------------------------------------------------------

IIC3413DBParser::CreateTableContext::CreateTableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::CreateTableContext::CREATE() {
  return getToken(IIC3413DBParser::CREATE, 0);
}

tree::TerminalNode* IIC3413DBParser::CreateTableContext::TABLE() {
  return getToken(IIC3413DBParser::TABLE, 0);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::CreateTableContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

tree::TerminalNode* IIC3413DBParser::CreateTableContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::SchemaContext *> IIC3413DBParser::CreateTableContext::schema() {
  return getRuleContexts<IIC3413DBParser::SchemaContext>();
}

IIC3413DBParser::SchemaContext* IIC3413DBParser::CreateTableContext::schema(size_t i) {
  return getRuleContext<IIC3413DBParser::SchemaContext>(i);
}

tree::TerminalNode* IIC3413DBParser::CreateTableContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::CreateTableContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::CreateTableContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::CreateTableContext::getRuleIndex() const {
  return IIC3413DBParser::RuleCreateTable;
}


std::any IIC3413DBParser::CreateTableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitCreateTable(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::CreateTableContext* IIC3413DBParser::createTable() {
  CreateTableContext *_localctx = _tracker.createInstance<CreateTableContext>(_ctx, getState());
  enterRule(_localctx, 6, IIC3413DBParser::RuleCreateTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(IIC3413DBParser::CREATE);
    setState(65);
    match(IIC3413DBParser::TABLE);
    setState(66);
    identifier();
    setState(67);
    match(IIC3413DBParser::L_PAR);
    setState(68);
    schema();
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(69);
      match(IIC3413DBParser::COMMA);
      setState(70);
      schema();
      setState(75);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(76);
    match(IIC3413DBParser::R_PAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateIndexContext ------------------------------------------------------------------

IIC3413DBParser::CreateIndexContext::CreateIndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::CreateIndexContext::CREATE() {
  return getToken(IIC3413DBParser::CREATE, 0);
}

tree::TerminalNode* IIC3413DBParser::CreateIndexContext::INDEX() {
  return getToken(IIC3413DBParser::INDEX, 0);
}

tree::TerminalNode* IIC3413DBParser::CreateIndexContext::ON() {
  return getToken(IIC3413DBParser::ON, 0);
}

IIC3413DBParser::TableContext* IIC3413DBParser::CreateIndexContext::table() {
  return getRuleContext<IIC3413DBParser::TableContext>(0);
}

tree::TerminalNode* IIC3413DBParser::CreateIndexContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::CreateIndexContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::CreateIndexContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}


size_t IIC3413DBParser::CreateIndexContext::getRuleIndex() const {
  return IIC3413DBParser::RuleCreateIndex;
}


std::any IIC3413DBParser::CreateIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitCreateIndex(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::CreateIndexContext* IIC3413DBParser::createIndex() {
  CreateIndexContext *_localctx = _tracker.createInstance<CreateIndexContext>(_ctx, getState());
  enterRule(_localctx, 8, IIC3413DBParser::RuleCreateIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(IIC3413DBParser::CREATE);
    setState(79);
    match(IIC3413DBParser::INDEX);
    setState(80);
    match(IIC3413DBParser::ON);
    setState(81);
    table();
    setState(82);
    match(IIC3413DBParser::L_PAR);
    setState(83);
    column();
    setState(84);
    match(IIC3413DBParser::R_PAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertQueryContext ------------------------------------------------------------------

IIC3413DBParser::InsertQueryContext::InsertQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::INSERT() {
  return getToken(IIC3413DBParser::INSERT, 0);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::INTO() {
  return getToken(IIC3413DBParser::INTO, 0);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::InsertQueryContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::VALUES() {
  return getToken(IIC3413DBParser::VALUES, 0);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::ConstantContext *> IIC3413DBParser::InsertQueryContext::constant() {
  return getRuleContexts<IIC3413DBParser::ConstantContext>();
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::InsertQueryContext::constant(size_t i) {
  return getRuleContext<IIC3413DBParser::ConstantContext>(i);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::InsertQueryContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::InsertQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleInsertQuery;
}


std::any IIC3413DBParser::InsertQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitInsertQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::InsertQueryContext* IIC3413DBParser::insertQuery() {
  InsertQueryContext *_localctx = _tracker.createInstance<InsertQueryContext>(_ctx, getState());
  enterRule(_localctx, 10, IIC3413DBParser::RuleInsertQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(IIC3413DBParser::INSERT);
    setState(87);
    match(IIC3413DBParser::INTO);
    setState(88);
    identifier();
    setState(89);
    match(IIC3413DBParser::VALUES);
    setState(90);
    match(IIC3413DBParser::L_PAR);
    setState(91);
    constant();
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(92);
      match(IIC3413DBParser::COMMA);
      setState(93);
      constant();
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(99);
    match(IIC3413DBParser::R_PAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectQueryContext ------------------------------------------------------------------

IIC3413DBParser::SelectQueryContext::SelectQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::SelectStatementContext* IIC3413DBParser::SelectQueryContext::selectStatement() {
  return getRuleContext<IIC3413DBParser::SelectStatementContext>(0);
}

IIC3413DBParser::FromStatementContext* IIC3413DBParser::SelectQueryContext::fromStatement() {
  return getRuleContext<IIC3413DBParser::FromStatementContext>(0);
}

IIC3413DBParser::WhereStatementContext* IIC3413DBParser::SelectQueryContext::whereStatement() {
  return getRuleContext<IIC3413DBParser::WhereStatementContext>(0);
}

IIC3413DBParser::LimitStatementContext* IIC3413DBParser::SelectQueryContext::limitStatement() {
  return getRuleContext<IIC3413DBParser::LimitStatementContext>(0);
}


size_t IIC3413DBParser::SelectQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSelectQuery;
}


std::any IIC3413DBParser::SelectQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSelectQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SelectQueryContext* IIC3413DBParser::selectQuery() {
  SelectQueryContext *_localctx = _tracker.createInstance<SelectQueryContext>(_ctx, getState());
  enterRule(_localctx, 12, IIC3413DBParser::RuleSelectQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    selectStatement();
    setState(102);
    fromStatement();
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::WHERE) {
      setState(103);
      whereStatement();
    }
    setState(107);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::LIMIT) {
      setState(106);
      limitStatement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaContext ------------------------------------------------------------------

IIC3413DBParser::SchemaContext::SchemaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::SchemaContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

IIC3413DBParser::DatatypeContext* IIC3413DBParser::SchemaContext::datatype() {
  return getRuleContext<IIC3413DBParser::DatatypeContext>(0);
}


size_t IIC3413DBParser::SchemaContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSchema;
}


std::any IIC3413DBParser::SchemaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSchema(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SchemaContext* IIC3413DBParser::schema() {
  SchemaContext *_localctx = _tracker.createInstance<SchemaContext>(_ctx, getState());
  enterRule(_localctx, 14, IIC3413DBParser::RuleSchema);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    identifier();
    setState(110);
    datatype();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DatatypeContext ------------------------------------------------------------------

IIC3413DBParser::DatatypeContext::DatatypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::DatatypeContext::STR() {
  return getToken(IIC3413DBParser::STR, 0);
}

tree::TerminalNode* IIC3413DBParser::DatatypeContext::INT() {
  return getToken(IIC3413DBParser::INT, 0);
}


size_t IIC3413DBParser::DatatypeContext::getRuleIndex() const {
  return IIC3413DBParser::RuleDatatype;
}


std::any IIC3413DBParser::DatatypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitDatatype(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::DatatypeContext* IIC3413DBParser::datatype() {
  DatatypeContext *_localctx = _tracker.createInstance<DatatypeContext>(_ctx, getState());
  enterRule(_localctx, 16, IIC3413DBParser::RuleDatatype);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112);
    _la = _input->LA(1);
    if (!(_la == IIC3413DBParser::INT

    || _la == IIC3413DBParser::STR)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectStatementContext ------------------------------------------------------------------

IIC3413DBParser::SelectStatementContext::SelectStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::SelectStatementContext::SELECT() {
  return getToken(IIC3413DBParser::SELECT, 0);
}

tree::TerminalNode* IIC3413DBParser::SelectStatementContext::ASTERISK() {
  return getToken(IIC3413DBParser::ASTERISK, 0);
}

IIC3413DBParser::ColumnListContext* IIC3413DBParser::SelectStatementContext::columnList() {
  return getRuleContext<IIC3413DBParser::ColumnListContext>(0);
}

tree::TerminalNode* IIC3413DBParser::SelectStatementContext::DISTINCT() {
  return getToken(IIC3413DBParser::DISTINCT, 0);
}


size_t IIC3413DBParser::SelectStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSelectStatement;
}


std::any IIC3413DBParser::SelectStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSelectStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SelectStatementContext* IIC3413DBParser::selectStatement() {
  SelectStatementContext *_localctx = _tracker.createInstance<SelectStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, IIC3413DBParser::RuleSelectStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(IIC3413DBParser::SELECT);
    setState(116);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(115);
      match(IIC3413DBParser::DISTINCT);
      break;
    }

    default:
      break;
    }
    setState(120);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::ASTERISK: {
        setState(118);
        match(IIC3413DBParser::ASTERISK);
        break;
      }

      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::DELETE:
      case IIC3413DBParser::FROM:
      case IIC3413DBParser::INDEX:
      case IIC3413DBParser::INSERT:
      case IIC3413DBParser::INTO:
      case IIC3413DBParser::INT:
      case IIC3413DBParser::LIKE:
      case IIC3413DBParser::LIMIT:
      case IIC3413DBParser::OR:
      case IIC3413DBParser::SELECT:
      case IIC3413DBParser::STR:
      case IIC3413DBParser::TABLE:
      case IIC3413DBParser::VALUES:
      case IIC3413DBParser::WHERE:
      case IIC3413DBParser::UPDATE:
      case IIC3413DBParser::SET:
      case IIC3413DBParser::IDENTIFIER: {
        setState(119);
        columnList();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnListContext ------------------------------------------------------------------

IIC3413DBParser::ColumnListContext::ColumnListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::ColumnContext *> IIC3413DBParser::ColumnListContext::column() {
  return getRuleContexts<IIC3413DBParser::ColumnContext>();
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::ColumnListContext::column(size_t i) {
  return getRuleContext<IIC3413DBParser::ColumnContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::ColumnListContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::ColumnListContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::ColumnListContext::getRuleIndex() const {
  return IIC3413DBParser::RuleColumnList;
}


std::any IIC3413DBParser::ColumnListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitColumnList(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ColumnListContext* IIC3413DBParser::columnList() {
  ColumnListContext *_localctx = _tracker.createInstance<ColumnListContext>(_ctx, getState());
  enterRule(_localctx, 20, IIC3413DBParser::RuleColumnList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    column();
    setState(127);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(123);
      match(IIC3413DBParser::COMMA);
      setState(124);
      column();
      setState(129);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromStatementContext ------------------------------------------------------------------

IIC3413DBParser::FromStatementContext::FromStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::FromStatementContext::FROM() {
  return getToken(IIC3413DBParser::FROM, 0);
}

IIC3413DBParser::TableListContext* IIC3413DBParser::FromStatementContext::tableList() {
  return getRuleContext<IIC3413DBParser::TableListContext>(0);
}


size_t IIC3413DBParser::FromStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleFromStatement;
}


std::any IIC3413DBParser::FromStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitFromStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::FromStatementContext* IIC3413DBParser::fromStatement() {
  FromStatementContext *_localctx = _tracker.createInstance<FromStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, IIC3413DBParser::RuleFromStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(IIC3413DBParser::FROM);
    setState(131);
    tableList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableListContext ------------------------------------------------------------------

IIC3413DBParser::TableListContext::TableListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::TableContext *> IIC3413DBParser::TableListContext::table() {
  return getRuleContexts<IIC3413DBParser::TableContext>();
}

IIC3413DBParser::TableContext* IIC3413DBParser::TableListContext::table(size_t i) {
  return getRuleContext<IIC3413DBParser::TableContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::TableListContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::TableListContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::TableListContext::getRuleIndex() const {
  return IIC3413DBParser::RuleTableList;
}


std::any IIC3413DBParser::TableListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitTableList(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::TableListContext* IIC3413DBParser::tableList() {
  TableListContext *_localctx = _tracker.createInstance<TableListContext>(_ctx, getState());
  enterRule(_localctx, 24, IIC3413DBParser::RuleTableList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    table();
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(134);
      match(IIC3413DBParser::COMMA);
      setState(135);
      table();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableContext ------------------------------------------------------------------

IIC3413DBParser::TableContext::TableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::IdentifierContext *> IIC3413DBParser::TableContext::identifier() {
  return getRuleContexts<IIC3413DBParser::IdentifierContext>();
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::TableContext::identifier(size_t i) {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(i);
}

tree::TerminalNode* IIC3413DBParser::TableContext::AS() {
  return getToken(IIC3413DBParser::AS, 0);
}


size_t IIC3413DBParser::TableContext::getRuleIndex() const {
  return IIC3413DBParser::RuleTable;
}


std::any IIC3413DBParser::TableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitTable(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::TableContext* IIC3413DBParser::table() {
  TableContext *_localctx = _tracker.createInstance<TableContext>(_ctx, getState());
  enterRule(_localctx, 26, IIC3413DBParser::RuleTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    identifier();
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::AS) {
      setState(142);
      match(IIC3413DBParser::AS);
      setState(143);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhereStatementContext ------------------------------------------------------------------

IIC3413DBParser::WhereStatementContext::WhereStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::WhereStatementContext::WHERE() {
  return getToken(IIC3413DBParser::WHERE, 0);
}

IIC3413DBParser::AndExprContext* IIC3413DBParser::WhereStatementContext::andExpr() {
  return getRuleContext<IIC3413DBParser::AndExprContext>(0);
}


size_t IIC3413DBParser::WhereStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleWhereStatement;
}


std::any IIC3413DBParser::WhereStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitWhereStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::WhereStatementContext* IIC3413DBParser::whereStatement() {
  WhereStatementContext *_localctx = _tracker.createInstance<WhereStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, IIC3413DBParser::RuleWhereStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(IIC3413DBParser::WHERE);
    setState(147);
    andExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExprContext ------------------------------------------------------------------

IIC3413DBParser::AndExprContext::AndExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::SimpleExprContext *> IIC3413DBParser::AndExprContext::simpleExpr() {
  return getRuleContexts<IIC3413DBParser::SimpleExprContext>();
}

IIC3413DBParser::SimpleExprContext* IIC3413DBParser::AndExprContext::simpleExpr(size_t i) {
  return getRuleContext<IIC3413DBParser::SimpleExprContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::AndExprContext::AND() {
  return getTokens(IIC3413DBParser::AND);
}

tree::TerminalNode* IIC3413DBParser::AndExprContext::AND(size_t i) {
  return getToken(IIC3413DBParser::AND, i);
}


size_t IIC3413DBParser::AndExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleAndExpr;
}


std::any IIC3413DBParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::AndExprContext* IIC3413DBParser::andExpr() {
  AndExprContext *_localctx = _tracker.createInstance<AndExprContext>(_ctx, getState());
  enterRule(_localctx, 30, IIC3413DBParser::RuleAndExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    simpleExpr();
    setState(154);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::AND) {
      setState(150);
      match(IIC3413DBParser::AND);
      setState(151);
      simpleExpr();
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleExprContext ------------------------------------------------------------------

IIC3413DBParser::SimpleExprContext::SimpleExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ComparisonExprContext* IIC3413DBParser::SimpleExprContext::comparisonExpr() {
  return getRuleContext<IIC3413DBParser::ComparisonExprContext>(0);
}

IIC3413DBParser::LikeExprContext* IIC3413DBParser::SimpleExprContext::likeExpr() {
  return getRuleContext<IIC3413DBParser::LikeExprContext>(0);
}

IIC3413DBParser::BetweenExprContext* IIC3413DBParser::SimpleExprContext::betweenExpr() {
  return getRuleContext<IIC3413DBParser::BetweenExprContext>(0);
}


size_t IIC3413DBParser::SimpleExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSimpleExpr;
}


std::any IIC3413DBParser::SimpleExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSimpleExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SimpleExprContext* IIC3413DBParser::simpleExpr() {
  SimpleExprContext *_localctx = _tracker.createInstance<SimpleExprContext>(_ctx, getState());
  enterRule(_localctx, 32, IIC3413DBParser::RuleSimpleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(160);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(157);
      comparisonExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(158);
      likeExpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(159);
      betweenExpr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonExprContext ------------------------------------------------------------------

IIC3413DBParser::ComparisonExprContext::ComparisonExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::ColumnOrConstantContext *> IIC3413DBParser::ComparisonExprContext::columnOrConstant() {
  return getRuleContexts<IIC3413DBParser::ColumnOrConstantContext>();
}

IIC3413DBParser::ColumnOrConstantContext* IIC3413DBParser::ComparisonExprContext::columnOrConstant(size_t i) {
  return getRuleContext<IIC3413DBParser::ColumnOrConstantContext>(i);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::EQ() {
  return getToken(IIC3413DBParser::EQ, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::NE() {
  return getToken(IIC3413DBParser::NE, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::LT() {
  return getToken(IIC3413DBParser::LT, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::GT() {
  return getToken(IIC3413DBParser::GT, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::LE() {
  return getToken(IIC3413DBParser::LE, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::GE() {
  return getToken(IIC3413DBParser::GE, 0);
}


size_t IIC3413DBParser::ComparisonExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleComparisonExpr;
}


std::any IIC3413DBParser::ComparisonExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitComparisonExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ComparisonExprContext* IIC3413DBParser::comparisonExpr() {
  ComparisonExprContext *_localctx = _tracker.createInstance<ComparisonExprContext>(_ctx, getState());
  enterRule(_localctx, 34, IIC3413DBParser::RuleComparisonExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    columnOrConstant();
    setState(165);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 33822867456) != 0)) {
      setState(163);
      antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 33822867456) != 0))) {
        antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(164);
      columnOrConstant();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LikeExprContext ------------------------------------------------------------------

IIC3413DBParser::LikeExprContext::LikeExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::LikeExprContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::LikeExprContext::LIKE() {
  return getToken(IIC3413DBParser::LIKE, 0);
}

tree::TerminalNode* IIC3413DBParser::LikeExprContext::STRING() {
  return getToken(IIC3413DBParser::STRING, 0);
}


size_t IIC3413DBParser::LikeExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleLikeExpr;
}


std::any IIC3413DBParser::LikeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitLikeExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::LikeExprContext* IIC3413DBParser::likeExpr() {
  LikeExprContext *_localctx = _tracker.createInstance<LikeExprContext>(_ctx, getState());
  enterRule(_localctx, 36, IIC3413DBParser::RuleLikeExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    column();
    setState(168);
    match(IIC3413DBParser::LIKE);
    setState(169);
    match(IIC3413DBParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BetweenExprContext ------------------------------------------------------------------

IIC3413DBParser::BetweenExprContext::BetweenExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::BetweenExprContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::BetweenExprContext::BETWEEN() {
  return getToken(IIC3413DBParser::BETWEEN, 0);
}

std::vector<IIC3413DBParser::ConstantContext *> IIC3413DBParser::BetweenExprContext::constant() {
  return getRuleContexts<IIC3413DBParser::ConstantContext>();
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::BetweenExprContext::constant(size_t i) {
  return getRuleContext<IIC3413DBParser::ConstantContext>(i);
}

tree::TerminalNode* IIC3413DBParser::BetweenExprContext::AND() {
  return getToken(IIC3413DBParser::AND, 0);
}


size_t IIC3413DBParser::BetweenExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleBetweenExpr;
}


std::any IIC3413DBParser::BetweenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitBetweenExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::BetweenExprContext* IIC3413DBParser::betweenExpr() {
  BetweenExprContext *_localctx = _tracker.createInstance<BetweenExprContext>(_ctx, getState());
  enterRule(_localctx, 38, IIC3413DBParser::RuleBetweenExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(171);
    column();
    setState(172);
    match(IIC3413DBParser::BETWEEN);
    setState(173);
    constant();
    setState(174);
    match(IIC3413DBParser::AND);
    setState(175);
    constant();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnOrConstantContext ------------------------------------------------------------------

IIC3413DBParser::ColumnOrConstantContext::ColumnOrConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::ColumnOrConstantContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::ColumnOrConstantContext::constant() {
  return getRuleContext<IIC3413DBParser::ConstantContext>(0);
}


size_t IIC3413DBParser::ColumnOrConstantContext::getRuleIndex() const {
  return IIC3413DBParser::RuleColumnOrConstant;
}


std::any IIC3413DBParser::ColumnOrConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitColumnOrConstant(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ColumnOrConstantContext* IIC3413DBParser::columnOrConstant() {
  ColumnOrConstantContext *_localctx = _tracker.createInstance<ColumnOrConstantContext>(_ctx, getState());
  enterRule(_localctx, 40, IIC3413DBParser::RuleColumnOrConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(179);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::DELETE:
      case IIC3413DBParser::FROM:
      case IIC3413DBParser::INDEX:
      case IIC3413DBParser::INSERT:
      case IIC3413DBParser::INTO:
      case IIC3413DBParser::INT:
      case IIC3413DBParser::LIKE:
      case IIC3413DBParser::LIMIT:
      case IIC3413DBParser::OR:
      case IIC3413DBParser::SELECT:
      case IIC3413DBParser::STR:
      case IIC3413DBParser::TABLE:
      case IIC3413DBParser::VALUES:
      case IIC3413DBParser::WHERE:
      case IIC3413DBParser::UPDATE:
      case IIC3413DBParser::SET:
      case IIC3413DBParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(177);
        column();
        break;
      }

      case IIC3413DBParser::INTEGER:
      case IIC3413DBParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(178);
        constant();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnContext ------------------------------------------------------------------

IIC3413DBParser::ColumnContext::ColumnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::IdentifierContext *> IIC3413DBParser::ColumnContext::identifier() {
  return getRuleContexts<IIC3413DBParser::IdentifierContext>();
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::ColumnContext::identifier(size_t i) {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(i);
}

tree::TerminalNode* IIC3413DBParser::ColumnContext::DOT() {
  return getToken(IIC3413DBParser::DOT, 0);
}


size_t IIC3413DBParser::ColumnContext::getRuleIndex() const {
  return IIC3413DBParser::RuleColumn;
}


std::any IIC3413DBParser::ColumnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitColumn(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::column() {
  ColumnContext *_localctx = _tracker.createInstance<ColumnContext>(_ctx, getState());
  enterRule(_localctx, 42, IIC3413DBParser::RuleColumn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    identifier();
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::DOT) {
      setState(182);
      match(IIC3413DBParser::DOT);
      setState(183);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

IIC3413DBParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::ConstantContext::INTEGER() {
  return getToken(IIC3413DBParser::INTEGER, 0);
}

tree::TerminalNode* IIC3413DBParser::ConstantContext::STRING() {
  return getToken(IIC3413DBParser::STRING, 0);
}


size_t IIC3413DBParser::ConstantContext::getRuleIndex() const {
  return IIC3413DBParser::RuleConstant;
}


std::any IIC3413DBParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 44, IIC3413DBParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    _la = _input->LA(1);
    if (!(_la == IIC3413DBParser::INTEGER

    || _la == IIC3413DBParser::STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

IIC3413DBParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::IdentifierContext::IDENTIFIER() {
  return getToken(IIC3413DBParser::IDENTIFIER, 0);
}

IIC3413DBParser::KeywordContext* IIC3413DBParser::IdentifierContext::keyword() {
  return getRuleContext<IIC3413DBParser::KeywordContext>(0);
}


size_t IIC3413DBParser::IdentifierContext::getRuleIndex() const {
  return IIC3413DBParser::RuleIdentifier;
}


std::any IIC3413DBParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 46, IIC3413DBParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(190);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(188);
        match(IIC3413DBParser::IDENTIFIER);
        break;
      }

      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::DELETE:
      case IIC3413DBParser::FROM:
      case IIC3413DBParser::INDEX:
      case IIC3413DBParser::INSERT:
      case IIC3413DBParser::INTO:
      case IIC3413DBParser::INT:
      case IIC3413DBParser::LIKE:
      case IIC3413DBParser::LIMIT:
      case IIC3413DBParser::OR:
      case IIC3413DBParser::SELECT:
      case IIC3413DBParser::STR:
      case IIC3413DBParser::TABLE:
      case IIC3413DBParser::VALUES:
      case IIC3413DBParser::WHERE:
      case IIC3413DBParser::UPDATE:
      case IIC3413DBParser::SET: {
        enterOuterAlt(_localctx, 2);
        setState(189);
        keyword();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LimitStatementContext ------------------------------------------------------------------

IIC3413DBParser::LimitStatementContext::LimitStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::LimitStatementContext::LIMIT() {
  return getToken(IIC3413DBParser::LIMIT, 0);
}

tree::TerminalNode* IIC3413DBParser::LimitStatementContext::INTEGER() {
  return getToken(IIC3413DBParser::INTEGER, 0);
}


size_t IIC3413DBParser::LimitStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleLimitStatement;
}


std::any IIC3413DBParser::LimitStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitLimitStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::LimitStatementContext* IIC3413DBParser::limitStatement() {
  LimitStatementContext *_localctx = _tracker.createInstance<LimitStatementContext>(_ctx, getState());
  enterRule(_localctx, 48, IIC3413DBParser::RuleLimitStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    match(IIC3413DBParser::LIMIT);
    setState(193);
    match(IIC3413DBParser::INTEGER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeywordContext ------------------------------------------------------------------

IIC3413DBParser::KeywordContext::KeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::AND() {
  return getToken(IIC3413DBParser::AND, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::AS() {
  return getToken(IIC3413DBParser::AS, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::BETWEEN() {
  return getToken(IIC3413DBParser::BETWEEN, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::CREATE() {
  return getToken(IIC3413DBParser::CREATE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::DELETE() {
  return getToken(IIC3413DBParser::DELETE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::DISTINCT() {
  return getToken(IIC3413DBParser::DISTINCT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::FROM() {
  return getToken(IIC3413DBParser::FROM, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::INDEX() {
  return getToken(IIC3413DBParser::INDEX, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::INSERT() {
  return getToken(IIC3413DBParser::INSERT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::INTO() {
  return getToken(IIC3413DBParser::INTO, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::INT() {
  return getToken(IIC3413DBParser::INT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::LIKE() {
  return getToken(IIC3413DBParser::LIKE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::LIMIT() {
  return getToken(IIC3413DBParser::LIMIT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::OR() {
  return getToken(IIC3413DBParser::OR, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::SELECT() {
  return getToken(IIC3413DBParser::SELECT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::SET() {
  return getToken(IIC3413DBParser::SET, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::STR() {
  return getToken(IIC3413DBParser::STR, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::TABLE() {
  return getToken(IIC3413DBParser::TABLE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::UPDATE() {
  return getToken(IIC3413DBParser::UPDATE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::VALUES() {
  return getToken(IIC3413DBParser::VALUES, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::WHERE() {
  return getToken(IIC3413DBParser::WHERE, 0);
}


size_t IIC3413DBParser::KeywordContext::getRuleIndex() const {
  return IIC3413DBParser::RuleKeyword;
}


std::any IIC3413DBParser::KeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitKeyword(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::KeywordContext* IIC3413DBParser::keyword() {
  KeywordContext *_localctx = _tracker.createInstance<KeywordContext>(_ctx, getState());
  enterRule(_localctx, 50, IIC3413DBParser::RuleKeyword);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 202899454) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void IIC3413DBParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  iic3413dbparserParserInitialize();
#else
  ::antlr4::internal::call_once(iic3413dbparserParserOnceFlag, iic3413dbparserParserInitialize);
#endif
}
