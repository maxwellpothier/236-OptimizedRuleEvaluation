#ifndef INC_236_PROJ5_INTERPRETER_H
#define INC_236_PROJ5_INTERPRETER_H
#pragma once
#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"

class Interpreter {
private:
  // Private Variables
  Database db;
  DatalogProgram interpretProgram;
public:
  // Public Functions
  void setDatalogProgram(DatalogProgram);
  void schemesToDB(vector<Predicate>);
  void factsToDB(vector<Predicate>);
  void relationQueries(vector<Predicate>);
  void relationRules(vector<Rule>, bool);
  void optimizeRule(vector<Rule>);
  Relation predicateEvaluation(Predicate);
  string toString();
};


#endif //INC_236_PROJ5_INTERPRETER_H
