#ifndef INC_236_PROJ5_RULES_H
#define INC_236_PROJ5_RULES_H
#pragma once
#include "Predicate.h"

class Rule {
public:
  // Public Variables
  Predicate head;
  vector<Predicate> ruleList;

  // Public Functions
  void setHeadPredicate(Predicate tHead) {
    head = tHead;
  }
  void setRule(vector<Predicate> tempRuleList) {
    for (unsigned int i = 0; i < tempRuleList.size(); i++) {
      ruleList.push_back(tempRuleList.at(i));
    }
  }
  string toString() {
    string tempRule;
    tempRule = head.toString() + " :- ";
    for (unsigned int i = 0; i < ruleList.size(); i++) {
      if (i == 0) {
        tempRule = tempRule + ruleList.at(i).toString();
      } else {
        tempRule = tempRule + "," + ruleList.at(i).toString();
      }
    }
    tempRule += ".";
    return tempRule;
  }
};

#endif //INC_236_PROJ5_RULES_H
