#ifndef INC_236_PROJ5_DATABASE_H
#define INC_236_PROJ5_DATABASE_H
#pragma once
#include "Relation.h"
#include <map>
#include <sstream>

class Database {
public:
  // Public Variable
  map<string, Relation> databaseMap;

  // Public Functions
  void addRelation(string tempName, Relation tempRelation) {
    databaseMap.insert({tempName, tempRelation});
  }
  void addTuplesToRelation(string tempName, Tuple tempTuple) {
    databaseMap.at(tempName).addTuple(tempTuple);
  }
  Relation getRelation(string tempName) {
    return databaseMap.at(tempName);
  }
  string toString() {
    stringstream oss;
    map<string, Relation> tempMap;
    for (auto i: databaseMap) {
      cout  <<  i.first << ": \n";
      i.second.toString();
    }
    return oss.str();
  }
};


#endif //INC_236_PROJ5_DATABASE_H
