
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
      "root", "query", "createQuery", "insertQuery", "selectQuery", "updateQuery", 
      "deleteQuery", "schema", "datatype", "selectStatement", "columnList", 
      "fromStatement", "tableList", "tableListItem", "leftOuterJoin", "fullOuterJoin", 
      "outerJoinOn", "outerJoinComp", "table", "whereStatement", "andExpr", 
      "simpleExpr", "comparisonExpr", "likeExpr", "betweenExpr", "additiveExpr", 
      "multiplicativeExpr", "unaryExpr", "atomicExpr", "assignmentList", 
      "assignment", "columnOrConstant", "column", "constant", "identifier", 
      "limitStatement", "keyword"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "';'", "'=='", "'!='", "'>'", 
      "'<'", "'>='", "'<='", "'='", "','", "'*'", "'-'", "'/'", "'%'", "'+'", 
      "'.'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "AND", "AS", "BETWEEN", "CREATE", "DISTINCT", "DELETE", "FROM", 
      "INSERT", "INTO", "INT", "LIKE", "LIMIT", "OR", "SELECT", "STR", "TABLE", 
      "VALUES", "VACUUM", "WHERE", "LEFT", "FULL", "OUTER", "JOIN", "ON", 
      "UPDATE", "SET", "EC", "EQ", "NE", "GT", "LT", "GE", "LE", "ASSIGN", 
      "COMMA", "ASTERISK", "MINUS", "SLASH", "MODULO", "PLUS", "DOT", "L_PAR", 
      "R_PAR", "INTEGER", "STRING", "IDENTIFIER", "WHITE_SPACE", "COMMENT_INPUT", 
      "LINE_COMMENT", "UNRECOGNIZED"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,50,309,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,3,1,83,8,1,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,5,2,92,8,2,10,2,12,2,95,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,5,3,107,8,3,10,3,12,3,110,9,3,1,3,1,3,1,4,1,4,1,4,3,4,117,
  	8,4,1,4,3,4,120,8,4,1,5,1,5,1,5,1,5,1,5,3,5,127,8,5,1,6,1,6,1,6,1,6,3,
  	6,133,8,6,1,7,1,7,1,7,1,8,1,8,1,9,1,9,3,9,142,8,9,1,9,1,9,3,9,146,8,9,
  	1,10,1,10,1,10,5,10,151,8,10,10,10,12,10,154,9,10,1,11,1,11,1,11,1,12,
  	1,12,1,12,5,12,162,8,12,10,12,12,12,165,9,12,1,13,1,13,1,13,3,13,170,
  	8,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,
  	5,16,199,8,16,10,16,12,16,202,9,16,1,17,1,17,1,17,1,17,1,18,1,18,1,18,
  	3,18,211,8,18,1,19,1,19,1,19,1,20,1,20,1,20,5,20,219,8,20,10,20,12,20,
  	222,9,20,1,21,1,21,1,21,3,21,227,8,21,1,22,1,22,1,22,3,22,232,8,22,1,
  	23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,5,25,247,
  	8,25,10,25,12,25,250,9,25,1,26,1,26,1,26,5,26,255,8,26,10,26,12,26,258,
  	9,26,1,27,1,27,1,27,1,27,1,27,1,27,3,27,266,8,27,1,28,1,28,1,28,1,28,
  	1,28,1,28,1,28,3,28,275,8,28,1,29,1,29,1,29,5,29,280,8,29,10,29,12,29,
  	283,9,29,1,30,1,30,1,30,1,30,1,31,1,31,3,31,291,8,31,1,32,1,32,1,32,3,
  	32,296,8,32,1,33,1,33,1,34,1,34,3,34,302,8,34,1,35,1,35,1,35,1,36,1,36,
  	1,36,0,0,37,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
  	42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,0,6,2,0,10,10,15,15,1,
  	0,28,33,2,0,37,37,40,40,2,0,36,36,38,39,1,0,44,45,4,0,1,5,7,17,19,19,
  	25,26,305,0,74,1,0,0,0,2,82,1,0,0,0,4,84,1,0,0,0,6,98,1,0,0,0,8,113,1,
  	0,0,0,10,121,1,0,0,0,12,128,1,0,0,0,14,134,1,0,0,0,16,137,1,0,0,0,18,
  	139,1,0,0,0,20,147,1,0,0,0,22,155,1,0,0,0,24,158,1,0,0,0,26,169,1,0,0,
  	0,28,171,1,0,0,0,30,183,1,0,0,0,32,195,1,0,0,0,34,203,1,0,0,0,36,207,
  	1,0,0,0,38,212,1,0,0,0,40,215,1,0,0,0,42,226,1,0,0,0,44,228,1,0,0,0,46,
  	233,1,0,0,0,48,237,1,0,0,0,50,243,1,0,0,0,52,251,1,0,0,0,54,265,1,0,0,
  	0,56,274,1,0,0,0,58,276,1,0,0,0,60,284,1,0,0,0,62,290,1,0,0,0,64,292,
  	1,0,0,0,66,297,1,0,0,0,68,301,1,0,0,0,70,303,1,0,0,0,72,306,1,0,0,0,74,
  	75,3,2,1,0,75,76,5,0,0,1,76,1,1,0,0,0,77,83,3,4,2,0,78,83,3,6,3,0,79,
  	83,3,8,4,0,80,83,3,10,5,0,81,83,3,12,6,0,82,77,1,0,0,0,82,78,1,0,0,0,
  	82,79,1,0,0,0,82,80,1,0,0,0,82,81,1,0,0,0,83,3,1,0,0,0,84,85,5,4,0,0,
  	85,86,5,16,0,0,86,87,3,68,34,0,87,88,5,42,0,0,88,93,3,14,7,0,89,90,5,
  	35,0,0,90,92,3,14,7,0,91,89,1,0,0,0,92,95,1,0,0,0,93,91,1,0,0,0,93,94,
  	1,0,0,0,94,96,1,0,0,0,95,93,1,0,0,0,96,97,5,43,0,0,97,5,1,0,0,0,98,99,
  	5,8,0,0,99,100,5,9,0,0,100,101,3,68,34,0,101,102,5,17,0,0,102,103,5,42,
  	0,0,103,108,3,66,33,0,104,105,5,35,0,0,105,107,3,66,33,0,106,104,1,0,
  	0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,1,0,0,0,109,111,1,0,0,0,110,
  	108,1,0,0,0,111,112,5,43,0,0,112,7,1,0,0,0,113,114,3,18,9,0,114,116,3,
  	22,11,0,115,117,3,38,19,0,116,115,1,0,0,0,116,117,1,0,0,0,117,119,1,0,
  	0,0,118,120,3,70,35,0,119,118,1,0,0,0,119,120,1,0,0,0,120,9,1,0,0,0,121,
  	122,5,25,0,0,122,123,3,68,34,0,123,124,5,26,0,0,124,126,3,58,29,0,125,
  	127,3,38,19,0,126,125,1,0,0,0,126,127,1,0,0,0,127,11,1,0,0,0,128,129,
  	5,6,0,0,129,130,5,7,0,0,130,132,3,68,34,0,131,133,3,38,19,0,132,131,1,
  	0,0,0,132,133,1,0,0,0,133,13,1,0,0,0,134,135,3,68,34,0,135,136,3,16,8,
  	0,136,15,1,0,0,0,137,138,7,0,0,0,138,17,1,0,0,0,139,141,5,14,0,0,140,
  	142,5,5,0,0,141,140,1,0,0,0,141,142,1,0,0,0,142,145,1,0,0,0,143,146,5,
  	36,0,0,144,146,3,20,10,0,145,143,1,0,0,0,145,144,1,0,0,0,146,19,1,0,0,
  	0,147,152,3,64,32,0,148,149,5,35,0,0,149,151,3,64,32,0,150,148,1,0,0,
  	0,151,154,1,0,0,0,152,150,1,0,0,0,152,153,1,0,0,0,153,21,1,0,0,0,154,
  	152,1,0,0,0,155,156,5,7,0,0,156,157,3,24,12,0,157,23,1,0,0,0,158,163,
  	3,26,13,0,159,160,5,35,0,0,160,162,3,26,13,0,161,159,1,0,0,0,162,165,
  	1,0,0,0,163,161,1,0,0,0,163,164,1,0,0,0,164,25,1,0,0,0,165,163,1,0,0,
  	0,166,170,3,28,14,0,167,170,3,30,15,0,168,170,3,36,18,0,169,166,1,0,0,
  	0,169,167,1,0,0,0,169,168,1,0,0,0,170,27,1,0,0,0,171,172,5,42,0,0,172,
  	173,3,68,34,0,173,174,5,20,0,0,174,175,5,22,0,0,175,176,5,23,0,0,176,
  	177,3,68,34,0,177,178,5,24,0,0,178,179,3,32,16,0,179,180,5,43,0,0,180,
  	181,5,2,0,0,181,182,3,68,34,0,182,29,1,0,0,0,183,184,5,42,0,0,184,185,
  	3,68,34,0,185,186,5,21,0,0,186,187,5,22,0,0,187,188,5,23,0,0,188,189,
  	3,68,34,0,189,190,5,24,0,0,190,191,3,32,16,0,191,192,5,43,0,0,192,193,
  	5,2,0,0,193,194,3,68,34,0,194,31,1,0,0,0,195,200,3,34,17,0,196,197,5,
  	1,0,0,197,199,3,34,17,0,198,196,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,
  	0,200,201,1,0,0,0,201,33,1,0,0,0,202,200,1,0,0,0,203,204,3,64,32,0,204,
  	205,5,28,0,0,205,206,3,64,32,0,206,35,1,0,0,0,207,210,3,68,34,0,208,209,
  	5,2,0,0,209,211,3,68,34,0,210,208,1,0,0,0,210,211,1,0,0,0,211,37,1,0,
  	0,0,212,213,5,19,0,0,213,214,3,40,20,0,214,39,1,0,0,0,215,220,3,42,21,
  	0,216,217,5,1,0,0,217,219,3,42,21,0,218,216,1,0,0,0,219,222,1,0,0,0,220,
  	218,1,0,0,0,220,221,1,0,0,0,221,41,1,0,0,0,222,220,1,0,0,0,223,227,3,
  	44,22,0,224,227,3,46,23,0,225,227,3,48,24,0,226,223,1,0,0,0,226,224,1,
  	0,0,0,226,225,1,0,0,0,227,43,1,0,0,0,228,231,3,62,31,0,229,230,7,1,0,
  	0,230,232,3,62,31,0,231,229,1,0,0,0,231,232,1,0,0,0,232,45,1,0,0,0,233,
  	234,3,64,32,0,234,235,5,11,0,0,235,236,5,45,0,0,236,47,1,0,0,0,237,238,
  	3,64,32,0,238,239,5,3,0,0,239,240,3,66,33,0,240,241,5,1,0,0,241,242,3,
  	66,33,0,242,49,1,0,0,0,243,248,3,52,26,0,244,245,7,2,0,0,245,247,3,52,
  	26,0,246,244,1,0,0,0,247,250,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,
  	249,51,1,0,0,0,250,248,1,0,0,0,251,256,3,54,27,0,252,253,7,3,0,0,253,
  	255,3,54,27,0,254,252,1,0,0,0,255,258,1,0,0,0,256,254,1,0,0,0,256,257,
  	1,0,0,0,257,53,1,0,0,0,258,256,1,0,0,0,259,266,1,0,0,0,260,266,3,56,28,
  	0,261,262,5,40,0,0,262,266,3,54,27,0,263,264,5,37,0,0,264,266,3,54,27,
  	0,265,259,1,0,0,0,265,260,1,0,0,0,265,261,1,0,0,0,265,263,1,0,0,0,266,
  	55,1,0,0,0,267,275,1,0,0,0,268,275,3,66,33,0,269,270,5,42,0,0,270,271,
  	3,50,25,0,271,272,5,43,0,0,272,275,1,0,0,0,273,275,3,64,32,0,274,267,
  	1,0,0,0,274,268,1,0,0,0,274,269,1,0,0,0,274,273,1,0,0,0,275,57,1,0,0,
  	0,276,281,3,60,30,0,277,278,5,35,0,0,278,280,3,60,30,0,279,277,1,0,0,
  	0,280,283,1,0,0,0,281,279,1,0,0,0,281,282,1,0,0,0,282,59,1,0,0,0,283,
  	281,1,0,0,0,284,285,3,68,34,0,285,286,5,34,0,0,286,287,3,50,25,0,287,
  	61,1,0,0,0,288,291,3,64,32,0,289,291,3,66,33,0,290,288,1,0,0,0,290,289,
  	1,0,0,0,291,63,1,0,0,0,292,295,3,68,34,0,293,294,5,41,0,0,294,296,3,68,
  	34,0,295,293,1,0,0,0,295,296,1,0,0,0,296,65,1,0,0,0,297,298,7,4,0,0,298,
  	67,1,0,0,0,299,302,5,46,0,0,300,302,3,72,36,0,301,299,1,0,0,0,301,300,
  	1,0,0,0,302,69,1,0,0,0,303,304,5,12,0,0,304,305,5,44,0,0,305,71,1,0,0,
  	0,306,307,7,5,0,0,307,73,1,0,0,0,25,82,93,108,116,119,126,132,141,145,
  	152,163,169,200,210,220,226,231,248,256,265,274,281,290,295,301
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
    setState(74);
    query();
    setState(75);
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

IIC3413DBParser::UpdateQueryContext* IIC3413DBParser::QueryContext::updateQuery() {
  return getRuleContext<IIC3413DBParser::UpdateQueryContext>(0);
}

IIC3413DBParser::DeleteQueryContext* IIC3413DBParser::QueryContext::deleteQuery() {
  return getRuleContext<IIC3413DBParser::DeleteQueryContext>(0);
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
    setState(82);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::CREATE: {
        enterOuterAlt(_localctx, 1);
        setState(77);
        createQuery();
        break;
      }

      case IIC3413DBParser::INSERT: {
        enterOuterAlt(_localctx, 2);
        setState(78);
        insertQuery();
        break;
      }

      case IIC3413DBParser::SELECT: {
        enterOuterAlt(_localctx, 3);
        setState(79);
        selectQuery();
        break;
      }

      case IIC3413DBParser::UPDATE: {
        enterOuterAlt(_localctx, 4);
        setState(80);
        updateQuery();
        break;
      }

      case IIC3413DBParser::DELETE: {
        enterOuterAlt(_localctx, 5);
        setState(81);
        deleteQuery();
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

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::CREATE() {
  return getToken(IIC3413DBParser::CREATE, 0);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::TABLE() {
  return getToken(IIC3413DBParser::TABLE, 0);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::CreateQueryContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::SchemaContext *> IIC3413DBParser::CreateQueryContext::schema() {
  return getRuleContexts<IIC3413DBParser::SchemaContext>();
}

IIC3413DBParser::SchemaContext* IIC3413DBParser::CreateQueryContext::schema(size_t i) {
  return getRuleContext<IIC3413DBParser::SchemaContext>(i);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::CreateQueryContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
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
    setState(84);
    match(IIC3413DBParser::CREATE);
    setState(85);
    match(IIC3413DBParser::TABLE);
    setState(86);
    identifier();
    setState(87);
    match(IIC3413DBParser::L_PAR);
    setState(88);
    schema();
    setState(93);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(89);
      match(IIC3413DBParser::COMMA);
      setState(90);
      schema();
      setState(95);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(96);
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
  enterRule(_localctx, 6, IIC3413DBParser::RuleInsertQuery);
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
    setState(98);
    match(IIC3413DBParser::INSERT);
    setState(99);
    match(IIC3413DBParser::INTO);
    setState(100);
    identifier();
    setState(101);
    match(IIC3413DBParser::VALUES);
    setState(102);
    match(IIC3413DBParser::L_PAR);
    setState(103);
    constant();
    setState(108);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(104);
      match(IIC3413DBParser::COMMA);
      setState(105);
      constant();
      setState(110);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(111);
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
  enterRule(_localctx, 8, IIC3413DBParser::RuleSelectQuery);
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
    setState(113);
    selectStatement();
    setState(114);
    fromStatement();
    setState(116);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::WHERE) {
      setState(115);
      whereStatement();
    }
    setState(119);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::LIMIT) {
      setState(118);
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

//----------------- UpdateQueryContext ------------------------------------------------------------------

IIC3413DBParser::UpdateQueryContext::UpdateQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::UpdateQueryContext::UPDATE() {
  return getToken(IIC3413DBParser::UPDATE, 0);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::UpdateQueryContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

tree::TerminalNode* IIC3413DBParser::UpdateQueryContext::SET() {
  return getToken(IIC3413DBParser::SET, 0);
}

IIC3413DBParser::AssignmentListContext* IIC3413DBParser::UpdateQueryContext::assignmentList() {
  return getRuleContext<IIC3413DBParser::AssignmentListContext>(0);
}

IIC3413DBParser::WhereStatementContext* IIC3413DBParser::UpdateQueryContext::whereStatement() {
  return getRuleContext<IIC3413DBParser::WhereStatementContext>(0);
}


size_t IIC3413DBParser::UpdateQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleUpdateQuery;
}


std::any IIC3413DBParser::UpdateQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitUpdateQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::UpdateQueryContext* IIC3413DBParser::updateQuery() {
  UpdateQueryContext *_localctx = _tracker.createInstance<UpdateQueryContext>(_ctx, getState());
  enterRule(_localctx, 10, IIC3413DBParser::RuleUpdateQuery);
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
    setState(121);
    match(IIC3413DBParser::UPDATE);
    setState(122);
    identifier();
    setState(123);
    match(IIC3413DBParser::SET);
    setState(124);
    assignmentList();
    setState(126);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::WHERE) {
      setState(125);
      whereStatement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteQueryContext ------------------------------------------------------------------

IIC3413DBParser::DeleteQueryContext::DeleteQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::DeleteQueryContext::DELETE() {
  return getToken(IIC3413DBParser::DELETE, 0);
}

tree::TerminalNode* IIC3413DBParser::DeleteQueryContext::FROM() {
  return getToken(IIC3413DBParser::FROM, 0);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::DeleteQueryContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

IIC3413DBParser::WhereStatementContext* IIC3413DBParser::DeleteQueryContext::whereStatement() {
  return getRuleContext<IIC3413DBParser::WhereStatementContext>(0);
}


size_t IIC3413DBParser::DeleteQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleDeleteQuery;
}


std::any IIC3413DBParser::DeleteQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitDeleteQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::DeleteQueryContext* IIC3413DBParser::deleteQuery() {
  DeleteQueryContext *_localctx = _tracker.createInstance<DeleteQueryContext>(_ctx, getState());
  enterRule(_localctx, 12, IIC3413DBParser::RuleDeleteQuery);
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
    setState(128);
    match(IIC3413DBParser::DELETE);
    setState(129);
    match(IIC3413DBParser::FROM);
    setState(130);
    identifier();
    setState(132);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::WHERE) {
      setState(131);
      whereStatement();
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
    setState(134);
    identifier();
    setState(135);
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
    setState(137);
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
    setState(139);
    match(IIC3413DBParser::SELECT);
    setState(141);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(140);
      match(IIC3413DBParser::DISTINCT);
      break;
    }

    default:
      break;
    }
    setState(145);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::ASTERISK: {
        setState(143);
        match(IIC3413DBParser::ASTERISK);
        break;
      }

      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::FROM:
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
        setState(144);
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
    setState(147);
    column();
    setState(152);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(148);
      match(IIC3413DBParser::COMMA);
      setState(149);
      column();
      setState(154);
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
    setState(155);
    match(IIC3413DBParser::FROM);
    setState(156);
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

std::vector<IIC3413DBParser::TableListItemContext *> IIC3413DBParser::TableListContext::tableListItem() {
  return getRuleContexts<IIC3413DBParser::TableListItemContext>();
}

IIC3413DBParser::TableListItemContext* IIC3413DBParser::TableListContext::tableListItem(size_t i) {
  return getRuleContext<IIC3413DBParser::TableListItemContext>(i);
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
    setState(158);
    tableListItem();
    setState(163);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(159);
      match(IIC3413DBParser::COMMA);
      setState(160);
      tableListItem();
      setState(165);
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

//----------------- TableListItemContext ------------------------------------------------------------------

IIC3413DBParser::TableListItemContext::TableListItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::LeftOuterJoinContext* IIC3413DBParser::TableListItemContext::leftOuterJoin() {
  return getRuleContext<IIC3413DBParser::LeftOuterJoinContext>(0);
}

IIC3413DBParser::FullOuterJoinContext* IIC3413DBParser::TableListItemContext::fullOuterJoin() {
  return getRuleContext<IIC3413DBParser::FullOuterJoinContext>(0);
}

IIC3413DBParser::TableContext* IIC3413DBParser::TableListItemContext::table() {
  return getRuleContext<IIC3413DBParser::TableContext>(0);
}


size_t IIC3413DBParser::TableListItemContext::getRuleIndex() const {
  return IIC3413DBParser::RuleTableListItem;
}


std::any IIC3413DBParser::TableListItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitTableListItem(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::TableListItemContext* IIC3413DBParser::tableListItem() {
  TableListItemContext *_localctx = _tracker.createInstance<TableListItemContext>(_ctx, getState());
  enterRule(_localctx, 26, IIC3413DBParser::RuleTableListItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(169);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(166);
      leftOuterJoin();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(167);
      fullOuterJoin();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(168);
      table();
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

//----------------- LeftOuterJoinContext ------------------------------------------------------------------

IIC3413DBParser::LeftOuterJoinContext::LeftOuterJoinContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::IdentifierContext *> IIC3413DBParser::LeftOuterJoinContext::identifier() {
  return getRuleContexts<IIC3413DBParser::IdentifierContext>();
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::LeftOuterJoinContext::identifier(size_t i) {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(i);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::LEFT() {
  return getToken(IIC3413DBParser::LEFT, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::OUTER() {
  return getToken(IIC3413DBParser::OUTER, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::JOIN() {
  return getToken(IIC3413DBParser::JOIN, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::ON() {
  return getToken(IIC3413DBParser::ON, 0);
}

IIC3413DBParser::OuterJoinOnContext* IIC3413DBParser::LeftOuterJoinContext::outerJoinOn() {
  return getRuleContext<IIC3413DBParser::OuterJoinOnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::AS() {
  return getToken(IIC3413DBParser::AS, 0);
}


size_t IIC3413DBParser::LeftOuterJoinContext::getRuleIndex() const {
  return IIC3413DBParser::RuleLeftOuterJoin;
}


std::any IIC3413DBParser::LeftOuterJoinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitLeftOuterJoin(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::LeftOuterJoinContext* IIC3413DBParser::leftOuterJoin() {
  LeftOuterJoinContext *_localctx = _tracker.createInstance<LeftOuterJoinContext>(_ctx, getState());
  enterRule(_localctx, 28, IIC3413DBParser::RuleLeftOuterJoin);

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
    match(IIC3413DBParser::L_PAR);
    setState(172);
    identifier();
    setState(173);
    match(IIC3413DBParser::LEFT);
    setState(174);
    match(IIC3413DBParser::OUTER);
    setState(175);
    match(IIC3413DBParser::JOIN);
    setState(176);
    identifier();
    setState(177);
    match(IIC3413DBParser::ON);
    setState(178);
    outerJoinOn();
    setState(179);
    match(IIC3413DBParser::R_PAR);
    setState(180);
    match(IIC3413DBParser::AS);
    setState(181);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FullOuterJoinContext ------------------------------------------------------------------

IIC3413DBParser::FullOuterJoinContext::FullOuterJoinContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::FullOuterJoinContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::IdentifierContext *> IIC3413DBParser::FullOuterJoinContext::identifier() {
  return getRuleContexts<IIC3413DBParser::IdentifierContext>();
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::FullOuterJoinContext::identifier(size_t i) {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(i);
}

tree::TerminalNode* IIC3413DBParser::FullOuterJoinContext::FULL() {
  return getToken(IIC3413DBParser::FULL, 0);
}

tree::TerminalNode* IIC3413DBParser::FullOuterJoinContext::OUTER() {
  return getToken(IIC3413DBParser::OUTER, 0);
}

tree::TerminalNode* IIC3413DBParser::FullOuterJoinContext::JOIN() {
  return getToken(IIC3413DBParser::JOIN, 0);
}

tree::TerminalNode* IIC3413DBParser::FullOuterJoinContext::ON() {
  return getToken(IIC3413DBParser::ON, 0);
}

IIC3413DBParser::OuterJoinOnContext* IIC3413DBParser::FullOuterJoinContext::outerJoinOn() {
  return getRuleContext<IIC3413DBParser::OuterJoinOnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::FullOuterJoinContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

tree::TerminalNode* IIC3413DBParser::FullOuterJoinContext::AS() {
  return getToken(IIC3413DBParser::AS, 0);
}


size_t IIC3413DBParser::FullOuterJoinContext::getRuleIndex() const {
  return IIC3413DBParser::RuleFullOuterJoin;
}


std::any IIC3413DBParser::FullOuterJoinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitFullOuterJoin(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::FullOuterJoinContext* IIC3413DBParser::fullOuterJoin() {
  FullOuterJoinContext *_localctx = _tracker.createInstance<FullOuterJoinContext>(_ctx, getState());
  enterRule(_localctx, 30, IIC3413DBParser::RuleFullOuterJoin);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(IIC3413DBParser::L_PAR);
    setState(184);
    identifier();
    setState(185);
    match(IIC3413DBParser::FULL);
    setState(186);
    match(IIC3413DBParser::OUTER);
    setState(187);
    match(IIC3413DBParser::JOIN);
    setState(188);
    identifier();
    setState(189);
    match(IIC3413DBParser::ON);
    setState(190);
    outerJoinOn();
    setState(191);
    match(IIC3413DBParser::R_PAR);
    setState(192);
    match(IIC3413DBParser::AS);
    setState(193);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OuterJoinOnContext ------------------------------------------------------------------

IIC3413DBParser::OuterJoinOnContext::OuterJoinOnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::OuterJoinCompContext *> IIC3413DBParser::OuterJoinOnContext::outerJoinComp() {
  return getRuleContexts<IIC3413DBParser::OuterJoinCompContext>();
}

IIC3413DBParser::OuterJoinCompContext* IIC3413DBParser::OuterJoinOnContext::outerJoinComp(size_t i) {
  return getRuleContext<IIC3413DBParser::OuterJoinCompContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::OuterJoinOnContext::AND() {
  return getTokens(IIC3413DBParser::AND);
}

tree::TerminalNode* IIC3413DBParser::OuterJoinOnContext::AND(size_t i) {
  return getToken(IIC3413DBParser::AND, i);
}


size_t IIC3413DBParser::OuterJoinOnContext::getRuleIndex() const {
  return IIC3413DBParser::RuleOuterJoinOn;
}


std::any IIC3413DBParser::OuterJoinOnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitOuterJoinOn(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::OuterJoinOnContext* IIC3413DBParser::outerJoinOn() {
  OuterJoinOnContext *_localctx = _tracker.createInstance<OuterJoinOnContext>(_ctx, getState());
  enterRule(_localctx, 32, IIC3413DBParser::RuleOuterJoinOn);
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
    outerJoinComp();
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::AND) {
      setState(196);
      match(IIC3413DBParser::AND);
      setState(197);
      outerJoinComp();
      setState(202);
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

//----------------- OuterJoinCompContext ------------------------------------------------------------------

IIC3413DBParser::OuterJoinCompContext::OuterJoinCompContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::ColumnContext *> IIC3413DBParser::OuterJoinCompContext::column() {
  return getRuleContexts<IIC3413DBParser::ColumnContext>();
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::OuterJoinCompContext::column(size_t i) {
  return getRuleContext<IIC3413DBParser::ColumnContext>(i);
}

tree::TerminalNode* IIC3413DBParser::OuterJoinCompContext::EQ() {
  return getToken(IIC3413DBParser::EQ, 0);
}


size_t IIC3413DBParser::OuterJoinCompContext::getRuleIndex() const {
  return IIC3413DBParser::RuleOuterJoinComp;
}


std::any IIC3413DBParser::OuterJoinCompContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitOuterJoinComp(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::OuterJoinCompContext* IIC3413DBParser::outerJoinComp() {
  OuterJoinCompContext *_localctx = _tracker.createInstance<OuterJoinCompContext>(_ctx, getState());
  enterRule(_localctx, 34, IIC3413DBParser::RuleOuterJoinComp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    column();
    setState(204);
    match(IIC3413DBParser::EQ);
    setState(205);
    column();
   
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
  enterRule(_localctx, 36, IIC3413DBParser::RuleTable);
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
    setState(207);
    identifier();
    setState(210);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::AS) {
      setState(208);
      match(IIC3413DBParser::AS);
      setState(209);
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
  enterRule(_localctx, 38, IIC3413DBParser::RuleWhereStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    match(IIC3413DBParser::WHERE);
    setState(213);
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
  enterRule(_localctx, 40, IIC3413DBParser::RuleAndExpr);
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
    setState(215);
    simpleExpr();
    setState(220);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::AND) {
      setState(216);
      match(IIC3413DBParser::AND);
      setState(217);
      simpleExpr();
      setState(222);
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
  enterRule(_localctx, 42, IIC3413DBParser::RuleSimpleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(226);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(223);
      comparisonExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(224);
      likeExpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(225);
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
  enterRule(_localctx, 44, IIC3413DBParser::RuleComparisonExpr);
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
    setState(228);
    columnOrConstant();
    setState(231);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16911433728) != 0)) {
      setState(229);
      antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 16911433728) != 0))) {
        antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(230);
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
  enterRule(_localctx, 46, IIC3413DBParser::RuleLikeExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(233);
    column();
    setState(234);
    match(IIC3413DBParser::LIKE);
    setState(235);
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
  enterRule(_localctx, 48, IIC3413DBParser::RuleBetweenExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    column();
    setState(238);
    match(IIC3413DBParser::BETWEEN);
    setState(239);
    constant();
    setState(240);
    match(IIC3413DBParser::AND);
    setState(241);
    constant();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExprContext ------------------------------------------------------------------

IIC3413DBParser::AdditiveExprContext::AdditiveExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::MultiplicativeExprContext *> IIC3413DBParser::AdditiveExprContext::multiplicativeExpr() {
  return getRuleContexts<IIC3413DBParser::MultiplicativeExprContext>();
}

IIC3413DBParser::MultiplicativeExprContext* IIC3413DBParser::AdditiveExprContext::multiplicativeExpr(size_t i) {
  return getRuleContext<IIC3413DBParser::MultiplicativeExprContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::AdditiveExprContext::PLUS() {
  return getTokens(IIC3413DBParser::PLUS);
}

tree::TerminalNode* IIC3413DBParser::AdditiveExprContext::PLUS(size_t i) {
  return getToken(IIC3413DBParser::PLUS, i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::AdditiveExprContext::MINUS() {
  return getTokens(IIC3413DBParser::MINUS);
}

tree::TerminalNode* IIC3413DBParser::AdditiveExprContext::MINUS(size_t i) {
  return getToken(IIC3413DBParser::MINUS, i);
}


size_t IIC3413DBParser::AdditiveExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleAdditiveExpr;
}


std::any IIC3413DBParser::AdditiveExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::AdditiveExprContext* IIC3413DBParser::additiveExpr() {
  AdditiveExprContext *_localctx = _tracker.createInstance<AdditiveExprContext>(_ctx, getState());
  enterRule(_localctx, 50, IIC3413DBParser::RuleAdditiveExpr);
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
    setState(243);
    multiplicativeExpr();
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::MINUS

    || _la == IIC3413DBParser::PLUS) {
      setState(244);
      antlrcpp::downCast<AdditiveExprContext *>(_localctx)->_tset404 = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == IIC3413DBParser::MINUS

      || _la == IIC3413DBParser::PLUS)) {
        antlrcpp::downCast<AdditiveExprContext *>(_localctx)->_tset404 = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      antlrcpp::downCast<AdditiveExprContext *>(_localctx)->op.push_back(antlrcpp::downCast<AdditiveExprContext *>(_localctx)->_tset404);
      setState(245);
      multiplicativeExpr();
      setState(250);
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

//----------------- MultiplicativeExprContext ------------------------------------------------------------------

IIC3413DBParser::MultiplicativeExprContext::MultiplicativeExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::UnaryExprContext *> IIC3413DBParser::MultiplicativeExprContext::unaryExpr() {
  return getRuleContexts<IIC3413DBParser::UnaryExprContext>();
}

IIC3413DBParser::UnaryExprContext* IIC3413DBParser::MultiplicativeExprContext::unaryExpr(size_t i) {
  return getRuleContext<IIC3413DBParser::UnaryExprContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::MultiplicativeExprContext::ASTERISK() {
  return getTokens(IIC3413DBParser::ASTERISK);
}

tree::TerminalNode* IIC3413DBParser::MultiplicativeExprContext::ASTERISK(size_t i) {
  return getToken(IIC3413DBParser::ASTERISK, i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::MultiplicativeExprContext::SLASH() {
  return getTokens(IIC3413DBParser::SLASH);
}

tree::TerminalNode* IIC3413DBParser::MultiplicativeExprContext::SLASH(size_t i) {
  return getToken(IIC3413DBParser::SLASH, i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::MultiplicativeExprContext::MODULO() {
  return getTokens(IIC3413DBParser::MODULO);
}

tree::TerminalNode* IIC3413DBParser::MultiplicativeExprContext::MODULO(size_t i) {
  return getToken(IIC3413DBParser::MODULO, i);
}


size_t IIC3413DBParser::MultiplicativeExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleMultiplicativeExpr;
}


std::any IIC3413DBParser::MultiplicativeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::MultiplicativeExprContext* IIC3413DBParser::multiplicativeExpr() {
  MultiplicativeExprContext *_localctx = _tracker.createInstance<MultiplicativeExprContext>(_ctx, getState());
  enterRule(_localctx, 52, IIC3413DBParser::RuleMultiplicativeExpr);
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
    setState(251);
    unaryExpr();
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 893353197568) != 0)) {
      setState(252);
      antlrcpp::downCast<MultiplicativeExprContext *>(_localctx)->_tset427 = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 893353197568) != 0))) {
        antlrcpp::downCast<MultiplicativeExprContext *>(_localctx)->_tset427 = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      antlrcpp::downCast<MultiplicativeExprContext *>(_localctx)->op.push_back(antlrcpp::downCast<MultiplicativeExprContext *>(_localctx)->_tset427);
      setState(253);
      unaryExpr();
      setState(258);
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

//----------------- UnaryExprContext ------------------------------------------------------------------

IIC3413DBParser::UnaryExprContext::UnaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::AtomicExprContext* IIC3413DBParser::UnaryExprContext::atomicExpr() {
  return getRuleContext<IIC3413DBParser::AtomicExprContext>(0);
}

tree::TerminalNode* IIC3413DBParser::UnaryExprContext::PLUS() {
  return getToken(IIC3413DBParser::PLUS, 0);
}

IIC3413DBParser::UnaryExprContext* IIC3413DBParser::UnaryExprContext::unaryExpr() {
  return getRuleContext<IIC3413DBParser::UnaryExprContext>(0);
}

tree::TerminalNode* IIC3413DBParser::UnaryExprContext::MINUS() {
  return getToken(IIC3413DBParser::MINUS, 0);
}


size_t IIC3413DBParser::UnaryExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleUnaryExpr;
}


std::any IIC3413DBParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::UnaryExprContext* IIC3413DBParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 54, IIC3413DBParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(265);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(260);
      atomicExpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(261);
      match(IIC3413DBParser::PLUS);
      setState(262);
      unaryExpr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(263);
      match(IIC3413DBParser::MINUS);
      setState(264);
      unaryExpr();
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

//----------------- AtomicExprContext ------------------------------------------------------------------

IIC3413DBParser::AtomicExprContext::AtomicExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::AtomicExprContext::constant() {
  return getRuleContext<IIC3413DBParser::ConstantContext>(0);
}

tree::TerminalNode* IIC3413DBParser::AtomicExprContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

IIC3413DBParser::AdditiveExprContext* IIC3413DBParser::AtomicExprContext::additiveExpr() {
  return getRuleContext<IIC3413DBParser::AdditiveExprContext>(0);
}

tree::TerminalNode* IIC3413DBParser::AtomicExprContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::AtomicExprContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}


size_t IIC3413DBParser::AtomicExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleAtomicExpr;
}


std::any IIC3413DBParser::AtomicExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitAtomicExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::AtomicExprContext* IIC3413DBParser::atomicExpr() {
  AtomicExprContext *_localctx = _tracker.createInstance<AtomicExprContext>(_ctx, getState());
  enterRule(_localctx, 56, IIC3413DBParser::RuleAtomicExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(274);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);

      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(268);
      constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(269);
      match(IIC3413DBParser::L_PAR);
      setState(270);
      additiveExpr();
      setState(271);
      match(IIC3413DBParser::R_PAR);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(273);
      column();
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

//----------------- AssignmentListContext ------------------------------------------------------------------

IIC3413DBParser::AssignmentListContext::AssignmentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::AssignmentContext *> IIC3413DBParser::AssignmentListContext::assignment() {
  return getRuleContexts<IIC3413DBParser::AssignmentContext>();
}

IIC3413DBParser::AssignmentContext* IIC3413DBParser::AssignmentListContext::assignment(size_t i) {
  return getRuleContext<IIC3413DBParser::AssignmentContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::AssignmentListContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::AssignmentListContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::AssignmentListContext::getRuleIndex() const {
  return IIC3413DBParser::RuleAssignmentList;
}


std::any IIC3413DBParser::AssignmentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitAssignmentList(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::AssignmentListContext* IIC3413DBParser::assignmentList() {
  AssignmentListContext *_localctx = _tracker.createInstance<AssignmentListContext>(_ctx, getState());
  enterRule(_localctx, 58, IIC3413DBParser::RuleAssignmentList);
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
    setState(276);
    assignment();
    setState(281);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(277);
      match(IIC3413DBParser::COMMA);
      setState(278);
      assignment();
      setState(283);
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

//----------------- AssignmentContext ------------------------------------------------------------------

IIC3413DBParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::AssignmentContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

tree::TerminalNode* IIC3413DBParser::AssignmentContext::ASSIGN() {
  return getToken(IIC3413DBParser::ASSIGN, 0);
}

IIC3413DBParser::AdditiveExprContext* IIC3413DBParser::AssignmentContext::additiveExpr() {
  return getRuleContext<IIC3413DBParser::AdditiveExprContext>(0);
}


size_t IIC3413DBParser::AssignmentContext::getRuleIndex() const {
  return IIC3413DBParser::RuleAssignment;
}


std::any IIC3413DBParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::AssignmentContext* IIC3413DBParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 60, IIC3413DBParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(284);
    identifier();
    setState(285);
    match(IIC3413DBParser::ASSIGN);
    setState(286);
    additiveExpr();
   
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
  enterRule(_localctx, 62, IIC3413DBParser::RuleColumnOrConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(290);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::FROM:
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
        setState(288);
        column();
        break;
      }

      case IIC3413DBParser::INTEGER:
      case IIC3413DBParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(289);
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
  enterRule(_localctx, 64, IIC3413DBParser::RuleColumn);
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
    setState(292);
    identifier();
    setState(295);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::DOT) {
      setState(293);
      match(IIC3413DBParser::DOT);
      setState(294);
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
  enterRule(_localctx, 66, IIC3413DBParser::RuleConstant);
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
    setState(297);
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
  enterRule(_localctx, 68, IIC3413DBParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(301);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(299);
        match(IIC3413DBParser::IDENTIFIER);
        break;
      }

      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::FROM:
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
        setState(300);
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
  enterRule(_localctx, 70, IIC3413DBParser::RuleLimitStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(303);
    match(IIC3413DBParser::LIMIT);
    setState(304);
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

tree::TerminalNode* IIC3413DBParser::KeywordContext::DISTINCT() {
  return getToken(IIC3413DBParser::DISTINCT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::FROM() {
  return getToken(IIC3413DBParser::FROM, 0);
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
  enterRule(_localctx, 72, IIC3413DBParser::RuleKeyword);
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
    setState(306);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 101449662) != 0))) {
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
