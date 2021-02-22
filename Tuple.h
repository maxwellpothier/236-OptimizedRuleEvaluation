#ifndef INC_236_PROJ5_TUPLE_H
#define INC_236_PROJ5_TUPLE_H
#pragma once
using namespace std;
#include <string>
#include <vector>
#include <iostream>

class Tuple : public vector<string> {
  vector<string> values;
  string At (int num) {
    return values.at(num);
  }
};

#endif //INC_236_PROJ5_TUPLE_H
