#ifndef INC_236_PROJ5_PARSER_H
#define INC_236_PROJ5_PARSER_H
#pragma once
#include "Token.h"
#include "DatalogProgram.h"
#include "Expression.h"
#include <queue>

class Parser {
protected:
  // Protected Variables
  vector<Parameter> parameterList;
  queue<Token> tokenQueue;
  Token parse;
  Token next;
  bool canInterpret = false;
  DatalogProgram program;
  set<string> domain;

  // Protected Functions
  void printErr(int);
  bool peekNext(TokenType);
  DatalogProgram parseProgram(queue<Token>);
  bool parseCheck(TokenType);
  Predicate parseScheme();
  vector<Predicate> parseSchemeList(vector<Predicate>);
  void parseIDList();
  vector<Predicate> parseFactList(vector<Predicate>);
  Predicate parseFact();
  void parseStringList();
  vector<Rule> parseRuleList(vector<Rule>);
  Rule parseRules();
  Predicate parseQuery();
  vector<Predicate> parseQueryList(vector<Predicate>);
  Predicate parseHeadPredicate();
  Predicate parsePredicate();
  vector<Predicate> parsePredicateList(vector<Predicate>);
  Parameter parseParameter();
  void parseParameterList();
  string parseExpression();
  Token parseOperator();
  void appendParameter(string, bool);

public:
  // Constructor and Destructor
  Parser() { };
  ~Parser() { };

  // Public Functions
  bool initTokenParse(queue<Token> Tokens);
  void toString();
  DatalogProgram getProgram();
};

#endif //INC_236_PROJ5_PARSER_H
