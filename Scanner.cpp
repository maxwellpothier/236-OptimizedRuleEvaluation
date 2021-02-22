#include "Scanner.h"
#include "Token.h"
#include <cctype>
#include <cstdio>
#include <sstream>

Scanner::Scanner(string fileName) {
  file = fileName;
  parse = '=';
  next = '=';
  line = 1;
  currentstate = init;
  inFile.open(file);
  facts = "==";
}

Scanner::~Scanner() {
  inFile.close();
}

bool Scanner::isWhiteSpace() {
  if (parse == ' ' || parse == '\t' || parse == '\n' || parse == '\r') {
    return true;
  }
  else {
    return false;
  }
}


string Scanner::wordExtractor() {
  string newWord;
  char wordChar;
  newWord += parse;
  wordChar = inFile.get();
  while(isalpha(wordChar)||isdigit(wordChar)) {
    newWord = newWord + wordChar;
    wordChar = inFile.get();
  }
  if (!(isalpha(wordChar)) && !isdigit(wordChar)) {
    peekChar = true;
    next = wordChar;
  }
  return newWord;
}

void Scanner::tokenize() {
  while (inFile.good()) {
    Token newToken;
    if (peekChar == true) {
      parse = next;
      peekChar = false;
    } else {
      parse = inFile.get();
    }
    newToken = stateMachine();
    if (!(isWhiteSpace())) {
      if (newToken.getType() == COMMENT) {
        continue;
      } else {
        tokenList.push(newToken);
      }
    } else if (parse == EOF) {
      tokenList.push(newToken);
    }
  }
  return;
}

Token Scanner::stateMachine() {
  Token newToken;
  currentstate = init;
  while (currentstate != sFinal) {
    switch(currentstate) {
      case (init):
        if(parse == EOF){
          currentstate = sEOF;
        } else if (parse == ','|| parse == '.'|| parse == '?'|| parse == '('|| parse == ')'|| parse == '*'|| parse == '+'|| parse == ':') {
          currentstate = sChar;
        } else if (isWhiteSpace()) {
          if (parse == '\n'|| parse == '\r') {
            line++;
            currentstate = sWhiteSpace;
          } else if (parse == '\t') {
            currentstate = sWhiteSpace;
          }
          currentstate = sWhiteSpace;
        } else if (parse == '#') {
          currentstate = sComment;
        } else if (parse == '\'') {
          currentstate = sString;
        } else if (isalpha(parse)) {
          currentstate = sSpecial;
        } else {
          string t;
          t += parse;
          newToken.setSchemeValues("UNDEFINED", t, line);
          return newToken;
        }
        break;

      case (sChar):
        if (parse == ':') {
          next = inFile.get();
          if (next == '-') {
            newToken.setValues(":-", line);
            return newToken;
          } else {
            newToken.setValues(":", line);
            peekChar = true;
            return newToken;
          }
        } else {
          string tStr;
          tStr += parse;
          newToken.setValues(tStr, line);
          return newToken;
        }

      case (sSpecial):
        facts = wordExtractor();
        if (parse == 'F') {
          if (facts == "Facts") {
            newToken.setValues(facts, line);
            return newToken;
          } else {
            currentstate = sID;
          }
        } else if (parse == 'S') {
          if (facts == "Schemes") {
            newToken.setValues(facts, line);
            return newToken;
          } else {
            currentstate = sID;
          }
        } else if (parse == 'Q') {
          if (facts == "Queries") {
            newToken.setValues(facts, line);
            return newToken;
          } else {
            currentstate = sID;
          }
        } else if (parse == 'R') {
          if (facts == "Rules") {
            newToken.setValues(facts, line);
            return newToken;
          } else {
            currentstate = sID;
          }
        } else {
          currentstate = sID;
        }
        break;

      case (sComment):
        next = inFile.get();
        parse = next;
        if (parse == '|') {
          int otherlines = 0;
          bool isEOF = false;
          string bcom;
          bcom = "#|";
          parse = inFile.get();
          next = inFile.peek();
          while (parse != EOF || next != EOF) {
            if (next == '#' && parse == '|') {
              bcom += "|#";
              inFile.get();
              newToken.setSchemeValues("COMMENT", bcom, line);
              line =  line + otherlines;
              return newToken;
            } else if (next == EOF) {
              isEOF = true;
            }

            if (parse == '\r' || parse == '\n'){
              otherlines = otherlines + 1;
              bcom.append("\n");
            } else {
              string cool;
              cool += parse;
              bcom.append(cool);
            }
            parse = inFile.get();
            next = inFile.peek();
          }
          if (isEOF) {
            newToken.setSchemeValues("UNDEFINED", bcom, line);
            tokenList.push(newToken);
            newToken.setValues("EOF", line + otherlines);
            parse = EOF;
            return newToken;
          } else {
            newToken.setSchemeValues("COMMENT", bcom, line);
            line = line + otherlines;
            newToken.toString();
            return newToken;
          }
          parse = inFile.get();
        } else {
          string comment = "#";
          comment = comment + parse;
          next = inFile.peek();
          while (next != '\n') {
            parse = inFile.get();
            comment = comment + parse;
            next = inFile.peek();
            if (next == '\r' || next =='\n') {
              break;
            }
          }
          newToken.setSchemeValues("COMMENT", comment, line);
          return newToken;
        }


        break;
      case (sString):
        parse = inFile.get();
        if (parse == '\'') {
          string t = "\'";
          int otherlines = 0;
          while (parse != EOF) {
            if (parse == '\r' || parse == '\n') {
              otherlines++;
            }
            next = inFile.peek();
            if (parse == '\'' && next == '\'') {
              parse = inFile.get();
              next = inFile.peek();
              t = t + parse + "\'";

            } else if (parse == '\'' && next != '\''){
              t = t + "\'";
              newToken.setSchemeValues("STRING", t, line);
              line = line + otherlines;
              return newToken;
              break;
            } else if (next == EOF) {
              newToken.setSchemeValues("UNDEFINED", t, line);
              tokenList.push(newToken);
              newToken.setValues("EOF", line + otherlines);
              parse = EOF;
              return newToken;
            } else {
              t = t + parse;
            }
            parse = inFile.get();
          }
        } else if (parse == '\'') {
          newToken.setSchemeValues("STRING", "\'\'", line);
          return newToken;
        } else {
          string t = "\'";
          int otherlines = 0;
          while (parse != EOF) {
            if (parse == '\r' || parse == '\n') {
              otherlines++;
            }
            next = inFile.peek();
            if (parse == '\'' && next == '\'') {
              parse = inFile.get();
              next = inFile.peek();
              t = t + parse + "\'";
            } else if (parse == '\'' && next != '\''){
              t = t + "\'";
              newToken.setSchemeValues("STRING", t, line);
              line = line + otherlines;
              return newToken;
              break;
            } else if (next == EOF) {
              t += parse;
              newToken.setSchemeValues("UNDEFINED", t, line);
              tokenList.push(newToken);
              newToken.setValues("EOF", line + otherlines);
              parse = EOF;
              return newToken;
              break;
            } else {
              t = t + parse;
            }
            parse = inFile.get();
          }
        }
        break;
      case (sID):
        newToken.setSchemeValues("ID", facts, line);
        return newToken;
        break;
      case (sEOF):
        newToken.setValues("EOF", line);
        return newToken;
        break;
      case (sWhiteSpace):
        currentstate = sFinal;
        break;
      case (sFinal):
        return newToken;
        break;
      default:
        newToken.setSchemeValues("UNDEFINED", "UNDEFINED", line);
    }
  }
  newToken.setSchemeValues("UNDEFINED", "UNDEFINED", line);
  return newToken;
}

queue <Token> Scanner::getList() {
  return tokenList;
}