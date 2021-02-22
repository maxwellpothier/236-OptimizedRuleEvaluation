#ifndef INC_236_PROJ5_RELATION_H
#define INC_236_PROJ5_RELATION_H
#pragma once
#include "Scheme.h"
#include "Tuple.h"
#include <set>


class Relation {
public:
  // Constructor
  Relation() { }

  // Public Variables
  set<Tuple> relationTuples;
  string name;
  Scheme relationScheme;
  bool BeenOutPutted;

  // Public Functions
  Relation select(int, string);
  Relation select(int, int);
  Relation project(vector<int>);
  Relation rename(vector<string>);
  Relation join(Relation);
  bool unite(Relation);
  bool isJoinable(Tuple, Tuple, Scheme, Scheme);
  void addTuple(Tuple);
  void setScheme(Scheme);
  void setName(string);
  Scheme getScheme() {
    return relationScheme;
  }
  set<Tuple> getTuple() {
    return relationTuples;
  }
  int getTupleSize() {
    return relationTuples.size();
  }
  void toString();
};
#endif //INC_236_PROJ5_RELATION_H
