#ifndef INC_236_PROJ5_TOKEN_H
#define INC_236_PROJ5_TOKEN_H
#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
  MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFa, ERR
};

class Token {
protected:
  string tokenValue;
  int lineNumber;
  TokenType tokenType;
public:
  Token();
  ~Token();
  string toString();
  string typeString();
  string getValue();
  TokenType getType();
  int getLineNumber();
  void setValues(string, int);
  void setSchemeValues(string, string, int);
};


#endif //INC_236_PROJ5_TOKEN_H
