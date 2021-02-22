#ifndef INC_236_PROJ5_PARAMETER_H
#define INC_236_PROJ5_PARAMETER_H
#pragma once
#include "string"
using namespace std;

class Parameter {
public:
  // Public Variables
  string tParameter;
  bool checkStr;

  // Public Functions
  void setParam(string parameter) {
    tParameter = parameter;
  }
  string toString() {
    return tParameter;
  }
  void setBool(bool isSet) {
    checkStr = isSet;
  }
  bool isString() {
    return checkStr;
  }
};


#endif //INC_236_PROJ5_PARAMETER_H
