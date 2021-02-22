#include "DatalogProgram.h"
#include <sstream>

vector<Rule> DatalogProgram::getRules() {
  return rules;
}
vector<Predicate> DatalogProgram::getQueries() {
  return queries;
}
vector<Predicate> DatalogProgram::getFacts() {
  return facts;
}
vector<Predicate> DatalogProgram::getSchemes() {
  return schemes;
}
void DatalogProgram::setDomain(set<string> set) {
  domain = set;
}
void DatalogProgram::setFacts(vector<Predicate> fact) {
  for (unsigned int i = 0; i < fact.size(); i++) {
    facts.push_back(fact.at(i));
  }
}
void DatalogProgram::setQueries(vector<Predicate> query) {
  for (unsigned int i = 0; i < query.size(); i++) {
    queries.push_back(query.at(i));
  }
}
void DatalogProgram::setSchemes(vector<Predicate> scheme) {
  for (unsigned int i = 0; i < scheme.size(); i++) {
    schemes.push_back(scheme.at(i));
  }
}
void DatalogProgram::setRules(vector<Rule> rule) {
  for (unsigned int i = 0; i < rule.size(); i++) {
    rules.push_back(rule.at(i));
  }
}
string DatalogProgram::toString() {
  stringstream oss;
  oss << "Schemes(" << schemes.size() << "):\n";
  for (unsigned int i = 0; i< schemes.size();i++) {
    oss << "  " << schemes.at(i).toString() << "\n";
  }
  oss << "Facts(" << facts.size() << "):\n";
  for (unsigned int i = 0; i< facts.size();i++) {
    oss << "  " << facts.at(i).toString() << ".\n";
  }
  oss << "Rules(" << rules.size() << "):\n";
  for (unsigned int i = 0; i < rules.size();i++) {
    oss << "  " << rules.at(i).toString() << "\n";
  }
  oss << "Queries(" << queries.size() << "):\n";
  for (unsigned int i = 0; i< queries.size();i++) {
    oss << "  " << queries.at(i).toString() << "?\n";
  }
  oss << "Domain(" << domain.size() << "):\n";
  set<string>::iterator it;
  for (it = domain.begin(); it != domain.end(); it++) {
    oss << "  " << *it << "\n";
  }

  string thing = oss.str();
  return thing;
}
