#ifndef INC_236_PROJ5_DATALOGPROGRAM_H
#define INC_236_PROJ5_DATALOGPROGRAM_H
#pragma once
#include <set>
#include "Rules.h"

enum PredicateType{ Facts, Queries, Schemes };

class DatalogProgram {
private:
  // Private Variables
  vector<Rule> rules;
  vector<Predicate> facts;
  vector<Predicate> queries;
  vector<Predicate> schemes;
  set<string> domain;
public:
  // Public Functions
  void setFacts(vector<Predicate>);
  void setQueries(vector<Predicate>);
  void setSchemes(vector<Predicate>);
  void setRules(vector<Rule>);
  void setDomain(set<string>);
  vector<Rule> getRules();
  vector<Predicate> getQueries();
  vector<Predicate> getFacts();
  vector<Predicate> getSchemes();
  string toString();
};


#endif //INC_236_PROJ5_DATALOGPROGRAM_H
