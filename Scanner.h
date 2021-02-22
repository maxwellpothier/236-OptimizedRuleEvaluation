#ifndef INC_236_PROJ5_SCANNER_H
#define INC_236_PROJ5_SCANNER_H
#pragma once
#include "Token.h"
#include <fstream>
#include <queue>

enum state {
  init, sChar, sSpecial, sFinal, sEOF, sID, sComment, sString, sWhiteSpace
};

class Scanner {
protected:
  // Protected Variables
  ifstream inFile;
  string file;
  string facts;
  state currentstate;
  char parse;
  char next;
  bool peekChar;
  int line;

  // Protected Functions
  Token stateMachine();
  string wordExtractor();
  bool isWhiteSpace();

public:
  // Public Variables
  queue <Token> tokenList;

  // Public Functions
  Scanner(string);
  ~Scanner();
  void tokenize();
  queue <Token> getList();
};



#endif //INC_236_PROJ5_SCANNER_H
