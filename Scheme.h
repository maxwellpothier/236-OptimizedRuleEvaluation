#ifndef INC_236_PROJ5_SCHEME_H
#define INC_236_PROJ5_SCHEME_H
#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Scheme {
public:
  // Public Variable
  vector<string> values;

  // Public Functions
  unsigned int schemeSize() {
    return values.size();
  }
  void pushScheme(string toAdd) {
    values.push_back(toAdd);
    return;
  }
  void getScheme(vector<string> tVector) {
    values = tVector;
  }
  string At(int i) {
    return values.at(i);
  }
};


#endif //INC_236_PROJ5_SCHEME_H
