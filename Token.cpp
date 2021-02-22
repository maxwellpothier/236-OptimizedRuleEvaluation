#include "Token.h"

Token::Token() {
  tokenValue = "";
  lineNumber = -1;
  tokenType = ERR;
}

Token::~Token() { }

int Token::getLineNumber(){
  return lineNumber;
}

TokenType Token::getType() {
  return tokenType;
}

string Token::getValue() {
  return tokenValue;
}

string Token::toString() {
  string currentToken;
  string type = "ERR";
  switch (tokenType) {
    case COMMA:
      type = "COMMA";
      break;
    case PERIOD:
      type = "PERIOD";
      break;
    case Q_MARK:
      type = "Q_MARK";
      break;
    case LEFT_PAREN:
      type = "LEFT_PAREN";
      break;
    case RIGHT_PAREN:
      type = "RIGHT_PAREN";
      break;
    case COLON:
      type = "COLON";
      break;
    case COLON_DASH:
      type = "COLON_DASH";
      break;
    case MULTIPLY:
      type = "MULTIPLY";
      break;
    case ADD:
      type = "ADD";
      break;
    case SCHEMES:
      type = "SCHEMES";
      break;
    case FACTS:
      type = "FACTS";
      break;
    case RULES:
      type = "RULES";
      break;
    case QUERIES:
      type = "QUERIES";
      break;
    case ID:
      type = "ID";
      break;
    case STRING:
      type = "STRING";
      break;
    case COMMENT:
      type = "COMMENT";
      break;
    case UNDEFINED:
      type = "UNDEFINED";
      break;
    case EOFa:
      type = "EOF";
      break;
    case ERR:
      type = "ERROR";
  }
  currentToken = "(" + type + ",\"" + tokenValue + "\"," + to_string(lineNumber) + ")";
  return currentToken;
}

void Token::setValues(string str ,int lineNum) {
  lineNumber = lineNum;
  tokenValue = str;
  if (str == ",") {
    tokenType = COMMA;
  }
  else if (str == ".") {
    tokenType = PERIOD;
  }
  else if (str == "?") {
    tokenType = Q_MARK;
  }
  else if (str == "(") {
    tokenType = LEFT_PAREN;
  }
  else if (str == ")") {
    tokenType = RIGHT_PAREN;
  }
  else if (str == ":-") {
    tokenType = COLON_DASH;
  }
  else if (str == ":") {
    tokenType = COLON;
  }
  else if (str == "*") {
    tokenType = MULTIPLY;
  }
  else if (str == "+") {
    tokenType = ADD;
  }
  else if (str == "Schemes") {
    tokenType = SCHEMES;
  }
  else if (str == "Facts") {
    tokenType = FACTS;
  }
  else if (str == "Queries") {
    tokenType = QUERIES;
  }
  else if (str == "Rules") {
    tokenType = RULES;
  }
  else if (str == "EOF") {
    tokenType = EOFa;
    tokenValue = "";
  }
  else {
    tokenType = UNDEFINED;
  }

}

void Token::setSchemeValues (string type, string token, int lineNum) {
  if (type == "ID") {
    tokenType = ID;
    tokenValue = token;
    lineNumber = lineNum;
  }
  else if ( type == "COMMENT") {
    tokenType = COMMENT;
    tokenValue = token;
    lineNumber = lineNum;
  }
  else if (type == "STRING") {
    tokenType = STRING;
    tokenValue = token;
    lineNumber = lineNum;

  }
  else if (type == "UNDEFINED") {
    tokenType = UNDEFINED;
    tokenValue = token;
    lineNumber = lineNum;

  }
}

string Token::typeString() {
  string type = "ERR";
  switch (tokenType) {
    case COMMA:
      type = "COMMA";
      break;
    case PERIOD:
      type = "PERIOD";
      break;
    case Q_MARK:
      type = "Q_MARK";
      break;
    case LEFT_PAREN:
      type = "LEFT_PAREN";
      break;
    case RIGHT_PAREN:
      type = "RIGHT_PAREN";
      break;
    case COLON:
      type = "COLON";
      break;
    case COLON_DASH:
      type = "COLON_DASH";
      break;
    case MULTIPLY:
      type = "MULTIPLY";
      break;
    case ADD:
      type = "ADD";
      break;
    case SCHEMES:
      type = "SCHEMES";
      break;
    case FACTS:
      type = "FACTS";
      break;
    case RULES:
      type = "RULES";
      break;
    case QUERIES:
      type = "QUERIES";
      break;
    case ID:
      type = "ID";
      break;
    case STRING:
      type = "STRING";
      break;
    case COMMENT:
      type = "COMMENT";
      break;
    case UNDEFINED:
      type = "UNDEFINED";
      break;
    case EOFa:
      type = "EOF";
      break;
    case ERR:
      type = "ERROR";
      break;
  }
  return type;
}
