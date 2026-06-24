
// Generated from IIC3413DBLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  IIC3413DBLexer : public antlr4::Lexer {
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
    WS_CHANNEL = 2
  };

  explicit IIC3413DBLexer(antlr4::CharStream *input);

  ~IIC3413DBLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

