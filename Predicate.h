#ifndef INC_236_PROJ5_PREDICATE_H
#define INC_236_PROJ5_PREDICATE_H
#pragma once
#include "Parameter.h"
#include <vector>

class Predicate {
public:
  // Public Variables
  vector<Parameter> parameterList;
  string name;

  // Public Functions
  void setName(string tName) {
    name = tName;
  }
  vector<Parameter> returnVector() {
    return parameterList;
  }
  void pushPredicate(Parameter tParameter) {
    parameterList.push_back(tParameter);
  }
  string getName() {
    return name;
  }
  string toString() {
    string tempStr = name + "(";
    for (unsigned int i = 0; i < parameterList.size(); i++) {
      if (i ==0 ){
        tempStr = tempStr + parameterList.at(i).toString();
      }
      else {
        tempStr = tempStr + "," + parameterList.at(i).toString();
      }
    }
    tempStr = tempStr + ")";
    return tempStr;
  }
};


#endif //INC_236_PROJ5_PREDICATE_H
