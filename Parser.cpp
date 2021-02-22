#include "Parser.h"

DatalogProgram Parser::parseProgram(queue<Token> Tokens) {
  tokenQueue = Tokens;
  vector<Predicate> schemes;
  parseCheck(SCHEMES);
  parseCheck(COLON);
  schemes.push_back(parseScheme());
  schemes = parseSchemeList(schemes);
  if (canInterpret == false) {
    program.setSchemes(schemes);
  } else {
    return program;
  }

  if(canInterpret == false) {
    parseCheck(FACTS);
    parseCheck(COLON);
    vector<Predicate> pFacts;
    pFacts = parseFactList(pFacts);
    if (canInterpret == false) {
      program.setFacts(pFacts);
      program.setDomain(domain);
    } else {
      return program;
    }
  } else {
    return program;
  }

  if(canInterpret == false) {
    vector<Rule> rules;
    parseCheck(RULES);
    parseCheck(COLON);
    rules = parseRuleList(rules);
    if (canInterpret == false) {
      program.setRules(rules);
    } else {
      return program;
    }
  } else {
    return program;
  }
  if (canInterpret == false) {
    vector<Predicate> queries;
    parseCheck(QUERIES);
    parseCheck(COLON);
    queries.push_back(parseQuery());
    queries = parseQueryList(queries);
    if ( canInterpret == false) {
      program.setQueries(queries);
    } else {
      return program;
    }
  } else {
    return program;
  }
  if (canInterpret == false) {
    if (next.getType() == EOFa) {
      return program;
    } else {
      while (next.getType() != EOFa) {
        parse = tokenQueue.front();
        tokenQueue.pop();
        next = tokenQueue.front();
      }
      printErr(parse.getLineNumber());
      return program;
    }
  } else {
    return program;
  }
}

Predicate Parser::parseQuery() {
  Predicate query;
  if (canInterpret == false) {
    query = parsePredicate();
    parseCheck(Q_MARK);
    return query;
  } else {
    return query;
  }
}

vector<Predicate> Parser::parseQueryList(vector<Predicate> queries) {
  if (canInterpret == false) {
    if (next.getType() != ID) {
      return queries;
    } else {
      queries.push_back(parseQuery());
      queries = parseQueryList(queries);
      return queries;
    }
  } else {
    return queries;
  }
}

vector<Rule> Parser::parseRuleList(vector<Rule> ruleList) {
  if(canInterpret == false) {
    if (next.getType() == QUERIES) {
      return ruleList;
    } else {
      ruleList.push_back(parseRules());
      ruleList = parseRuleList(ruleList);
      return ruleList;
    }
  } else {
    return ruleList;
  }
}

Rule Parser::parseRules() {
  Rule tRule;
  vector<Predicate> listOfRules;
  Predicate rule;
  if (canInterpret == false) {
    tRule.setHeadPredicate(parseHeadPredicate());
    parseCheck(COLON_DASH);
    rule = parsePredicate();
    listOfRules.push_back(rule);
    listOfRules = parsePredicateList(listOfRules);
    parseCheck(PERIOD);
    tRule.setRule(listOfRules);
    return tRule;
  } else {
    return tRule;
  }
}

vector<Predicate> Parser::parseFactList(vector<Predicate> facts) {
  Predicate tFact;
  if (canInterpret == false) {
    if (next.getType() == RULES) {
      return facts;
    } else {
      tFact = parseFact();
      facts.push_back(tFact);
      vector<Parameter> parameterList;
      parameterList = tFact.returnVector();
      for (unsigned int i = 0; i < parameterList.size(); i++) {
        domain.insert(parameterList.at(i).toString());
      }
      facts = parseFactList(facts);
      return facts;
    }
  } else {
    return facts;
  }
}

Predicate Parser::parseFact() {
  Predicate facts;
  if (canInterpret == false) {
    parameterList.clear();
    parseCheck(ID);
    facts.setName(parse.getValue());
    parseCheck(LEFT_PAREN);
    parseCheck(STRING);
    appendParameter(parse.getValue(), true);
    domain.insert(parse.getValue());
    parseStringList();
    parseCheck(RIGHT_PAREN);
    parseCheck(PERIOD);
    for (unsigned int i = 0; i < parameterList.size(); i++) {
      facts.pushPredicate(parameterList.at(i));
    }
    return facts;
  } else {
    return facts;
  }
}

void Parser::parseStringList() {
  if (canInterpret == false) {
    if (next.getType() == COMMA) {
      parseCheck(COMMA);
      parseCheck(STRING);
      appendParameter(parse.getValue(), true);
      parseStringList();
    }
  }
}

Predicate Parser::parseScheme() {
  Predicate schemes;
  if (canInterpret == false) {
    parameterList.clear();
    parseCheck(ID);
    schemes.setName(parse.getValue());
    parseCheck(LEFT_PAREN);
    parseCheck(ID);
    appendParameter(parse.getValue(), false);
    parseIDList();
    parseCheck(RIGHT_PAREN);
    for (unsigned int i = 0; i < parameterList.size(); i++) {
      schemes.pushPredicate(parameterList.at(i));
    }
    return schemes;
  } else {
    return schemes;
  }
}

vector<Predicate> Parser::parseSchemeList(vector<Predicate> schemes) {
  Predicate tScheme;
  if (canInterpret == false) {
    if (next.getType() == FACTS) {
      return schemes;
    } else {
      tScheme = parseScheme();
      schemes.push_back(tScheme);
      schemes = parseSchemeList(schemes);
      return schemes;
    }
  } else {
    return schemes;
  }
}

void Parser::parseIDList() {
  if (canInterpret == false) {
    if (next.getType() == COMMA) {
      parseCheck(COMMA);
      parseCheck(ID);
      appendParameter(parse.getValue(), false);
      parseIDList();
    }
  }
}

bool Parser::peekNext(TokenType type) {
  if (canInterpret == false) {
    if (next.getType() == type) {
      return true;
    } else {
      printErr(next.getLineNumber());
      return false;
    }
  } else {
    return false;
  }
}

bool Parser::parseCheck(TokenType type) {
  if (canInterpret == false) {
    if (next.getType() != EOFa) {
      parse = tokenQueue.front();
      tokenQueue.pop();
      next = tokenQueue.front();
      if (parse.getType() == type) {
        return true;
      } else {
        printErr(parse.getLineNumber());
        return false;
      }
    } else {
      parse = tokenQueue.front();
      return true;
    }
  } else {
    if (next.getType() != EOFa) {
      parse = tokenQueue.front();
      tokenQueue.pop();
      next = tokenQueue.front();
    } else {
      parse = tokenQueue.front();
    }
    return false;
  }
}

void Parser::printErr(int i) {
  cout << "Failure!" << "\n  (" << parse.typeString() << ",\"" <<parse.getValue() <<"\"," << i << ")" << endl;
  canInterpret = true;
  return;
}

Predicate Parser::parseHeadPredicate() {
  Predicate headPredicate;
  if (canInterpret == false) {
    parameterList.clear();
    parseCheck(ID);
    headPredicate.setName(parse.getValue());
    parseCheck(LEFT_PAREN);
    parseCheck(ID);
    appendParameter(parse.getValue(), false);
    parseIDList();
    parseCheck(RIGHT_PAREN);
    for (unsigned int i = 0; i < parameterList.size(); i++) {
      headPredicate.pushPredicate(parameterList.at(i));
    }
  }
  return headPredicate;
}

vector<Predicate> Parser::parsePredicateList(vector<Predicate> tList) {
  if (canInterpret == false) {
    if (next.getType() == COMMA) {
      parseCheck(COMMA);
      tList.push_back(parsePredicate());
      tList = parsePredicateList(tList);
    }
  }
  return tList;
}

Predicate Parser::parsePredicate(){
  Predicate predicates;
  Parameter tParameter;
  if (canInterpret == false) {
    parameterList.clear();
    parseCheck(ID);
    predicates.setName(parse.getValue());
    parseCheck(LEFT_PAREN);
    tParameter = parseParameter();
    appendParameter(tParameter.toString(), tParameter.isString());
    parseParameterList();
    parseCheck(RIGHT_PAREN);
    for (unsigned int i = 0; i < parameterList.size(); i++) {
      predicates.pushPredicate(parameterList.at(i));
    }
  }
  return predicates;
}

void Parser::appendParameter(string currentToken, bool str) {
  Parameter tParameter;
  if (parse.getValue() != "") {
    tParameter.setParam(currentToken);
    tParameter.setBool(str);
    parameterList.push_back(tParameter);
  }
}

Parameter Parser::parseParameter() {
  Parameter tParameter;
  if (canInterpret == false) {
    Token toSend = next;
    if (next.getType() == STRING) {
      parseCheck(STRING);
      tParameter.setParam(parse.getValue());
      tParameter.setBool(true);
    } else if (next.getType() == ID) {
      parseCheck(ID);
      tParameter.setParam(parse.getValue());
      tParameter.setBool(false);
    } else if (next.getType() == LEFT_PAREN) {
      string stringy;
      stringy = parseExpression();
      stringy = "(" + stringy + ")";
      tParameter.setParam(stringy);
    } else {
      parse = next;
      peekNext(ERR);
    }
  }
  return tParameter;
}

void Parser::parseParameterList() {
  if (canInterpret == false) {
    if (next.getType() == RIGHT_PAREN) {
      return;
    }
    else {
      Parameter tParameter;
      parseCheck(COMMA);
      tParameter = parseParameter();
      appendParameter(tParameter.toString(), tParameter.isString());
      parseParameterList();
    }
  }
}

string Parser::parseExpression() {
  Expression expression;

  if (canInterpret == false) {
    Parameter tParameter;
    parseCheck(LEFT_PAREN);
    tParameter = parseParameter();
    expression.setRight(tParameter);
    tParameter.setParam(parseOperator().getValue());
    expression.setOperator(tParameter);
    tParameter = parseParameter();
    expression.setLeft(tParameter);
    parseCheck(RIGHT_PAREN);
  }
  return expression.GetExpression();
}

Token Parser::parseOperator() {
  if (canInterpret == false) {
    if (next.getType() == ADD) {
      parseCheck(ADD);
    } else {
      parseCheck(MULTIPLY);
    }
  }
  return parse;
}

DatalogProgram Parser::getProgram() {
  return program;
}

bool Parser::initTokenParse(queue<Token> tokens) {
  parseProgram(tokens);
  return canInterpret;
}

void Parser::toString() {
  if (canInterpret != true) {
    cout << program.toString();
  }
}
