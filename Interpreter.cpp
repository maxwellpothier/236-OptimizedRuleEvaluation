#include "Interpreter.h"

void Interpreter::setDatalogProgram(DatalogProgram tProgram){
  interpretProgram = tProgram;
  schemesToDB(interpretProgram.getSchemes());
  factsToDB(interpretProgram.getFacts());
  optimizeRule(interpretProgram.getRules());
  cout << endl << "Query Evaluation" << endl;
  relationQueries(interpretProgram.getQueries());
}

void Interpreter::schemesToDB(vector<Predicate> predicates) {
  for(unsigned int i = 0; i < predicates.size(); i++) {
    string tempName = predicates.at(i).getName();
    Scheme tempScheme;
    for (unsigned int j = 0; j < predicates.at(i).returnVector().size(); j++) {
      tempScheme.pushScheme(predicates.at(i).returnVector().at(j).toString());
    }
    Relation tempRelation;
    tempRelation.setName(tempName);
    tempRelation.setScheme(tempScheme);
    db.addRelation(tempName, tempRelation);
  }
}

void Interpreter::factsToDB(vector<Predicate> facts) {
  for (unsigned int j = 0; j < facts.size(); j++) {
    string tempName;
    tempName = facts.at(j).getName();
    Tuple tempTuple;
    for(unsigned int i = 0; i < facts.at(j).returnVector().size(); i++) {
      tempTuple.push_back(facts.at(j).returnVector().at(i).toString());
    }
    db.addTuplesToRelation(tempName, tempTuple);
  }
}

void Interpreter::relationQueries(vector<Predicate> queries){
  for (unsigned int i = 0; i < queries.size(); i++) {
    Relation tempRelation = predicateEvaluation(queries.at(i));
    cout << queries.at(i).toString() << "? ";
    if (tempRelation.relationTuples.size() == 0) {
      cout << "No\n";
    } else {
      cout << "Yes(" << tempRelation.relationTuples.size() <<")\n";
      tempRelation.toString();
    }
  }
}

Relation Interpreter::predicateEvaluation(Predicate queries) {
  string tempName = queries.getName();
  vector<int> integers;
  vector<string> stringVector;
  Relation tempRelation = db.databaseMap.at(tempName);
  for (unsigned int j = 0; j < queries.returnVector().size(); j++) {
    Parameter currentParameter = queries.returnVector().at(j);
    if (currentParameter.isString() == true) {
      string x = currentParameter.tParameter;
      tempRelation = tempRelation.select(j, x);
    } else {
      bool duplicate = false;
      for (unsigned int k = 0; k < stringVector.size(); k++) {
        if (stringVector.at(k) == currentParameter.tParameter) {
          duplicate = true;
          tempRelation = tempRelation.select(j, k);
        }
      }
      if(duplicate == false) {
        stringVector.push_back(currentParameter.tParameter);
        integers.push_back(j);
      }
    }
  }
  tempRelation = tempRelation.project(integers);
  tempRelation = tempRelation.rename(stringVector);
  return tempRelation;
}


void Interpreter::relationRules(vector<Rule> rules, bool isCounting){
  bool tuples = true;
  int count = 0;
  while (tuples) {
    tuples = false;
    vector<bool> willContinue;
    count++;
    for (unsigned int i = 0; i < rules.size(); i ++) {
      cout << rules.at(i).toString()<< endl;
      vector<Relation> tempRelations;
      for (unsigned int j = 0; j < rules.at(i).ruleList.size(); j ++ ) {
        Relation tempRelation = predicateEvaluation(rules.at(i).ruleList.at(j));
        tempRelations.push_back(tempRelation);
      }
      Relation tempRelation;
      if (tempRelations.size() > 1) {
        tempRelation = tempRelations.at(0);
        for (unsigned int j = 0; j < tempRelations.size()-1; j++ ) {
          tempRelation = tempRelation.join(tempRelations.at(j+1));
        }
      } else {
        tempRelation = tempRelations.at(0);
      }
      vector<int> points;
      for (unsigned int j = 0; j < rules.at(i).head.parameterList.size(); j++) {
        for (unsigned int k = 0; k < tempRelation.relationScheme.schemeSize(); k++) {
          if (rules.at(i).head.parameterList.at(j).tParameter == tempRelation.relationScheme.At(k)) {
            points.push_back(k);
          }
        }
      }
      tempRelation = tempRelation.project(points);
      tempRelation.name = rules.at(i).head.name;
      if (db.databaseMap.at(tempRelation.name).relationScheme.values.size() == tempRelation.relationScheme.values.size()) {
        tempRelation.relationScheme = db.databaseMap.at(tempRelation.name).relationScheme;
      }
      willContinue.push_back(db.databaseMap.at(tempRelation.name).unite(tempRelation));
    }
    for (unsigned int a = 0; a < willContinue.size(); a++) {
      if (willContinue.at(a)) {
        tuples = true;
      }
    }
    if (!isCounting) {
      tuples = false;
    }
  }
  cout << count << " passes: ";
}

void Interpreter::optimizeRule(vector<Rule> rules) {
  Graph forward, backward;
  vector<string> test;
  int c = (int) rules.size();
  for (int i = 0; i < c; i ++) {
    Node tempNode;
    tempNode.id = i;
    tempNode.isSelfDependent = false;
    forward.nodeMap.insert({i, tempNode});
    backward.nodeMap.insert({i, tempNode});
  }
  for ( int i = 0; i < c; i++) {
    int c1 = (int) rules.at(i).ruleList.size();
    for (int j = 0; j < c1; j++) {
      for (int k = 0; k < c; k++) {
        if (rules.at(i).ruleList.at(j).name == rules.at(k).head.name) {
          bool dependent = false;
          if (i == k){
            dependent = true;
          }
          if(forward.nodeMap[i].isSelfDependent) {
            dependent = true;
          }
          forward.addEdge(i,k, dependent);
          backward.addEdge(k,i, dependent);
        }
      }
    }
  }
  forward.toString();
  backward.dfsForest();
  forward.topSearch = backward.topSearch;
  forward.dfsForestForward();
  cout << endl << "Rule Evaluation" << endl;
  for(unsigned int i = 0; i < forward.scc.size(); i ++) {
    vector<Rule> tRules;
    string outStr;
    unsigned int k = 0;
    bool isCounting;
    for(auto j : forward.scc.at(i)) {
      tRules.push_back(rules.at(j));
      string x = to_string(j);
      outStr = outStr + "R" + x;
      if (k != forward.scc.at(i).size() - 1) {
        outStr = outStr + ",";
      }
      k++;
      isCounting = forward.nodeMap[j].isSelfDependent;
    }

    if (forward.scc.at(i).size() != 1) {
      isCounting = true;
    }

    cout << "SCC: " << outStr << endl;
    relationRules(tRules, isCounting);
    cout << outStr << endl;
  }

  return;

}

string Interpreter::toString() {
  return db.toString();
}
