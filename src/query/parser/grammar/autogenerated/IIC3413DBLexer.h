
// Generated from IIC3413DBLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  IIC3413DBLexer : public antlr4::Lexer {
public:
  enum {
    AND = 1, AS = 2, BETWEEN = 3, CREATE = 4, DISTINCT = 5, DELETE = 6, 
    FROM = 7, INDEX = 8, INSERT = 9, INTO = 10, INT = 11, LIKE = 12, LIMIT = 13, 
    OR = 14, SELECT = 15, STR = 16, TABLE = 17, VALUES = 18, VACUUM = 19, 
    WHERE = 20, LEFT = 21, FULL = 22, OUTER = 23, JOIN = 24, ON = 25, UPDATE = 26, 
    SET = 27, EC = 28, EQ = 29, NE = 30, GT = 31, LT = 32, GE = 33, LE = 34, 
    ASSIGN = 35, COMMA = 36, ASTERISK = 37, MINUS = 38, SLASH = 39, MODULO = 40, 
    PLUS = 41, DOT = 42, L_PAR = 43, R_PAR = 44, INTEGER = 45, STRING = 46, 
    IDENTIFIER = 47, WHITE_SPACE = 48, COMMENT_INPUT = 49, LINE_COMMENT = 50, 
    UNRECOGNIZED = 51
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

