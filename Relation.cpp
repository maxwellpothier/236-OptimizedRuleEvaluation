#include "Relation.h"

Relation Relation::join(Relation relationToJoin) {
  Relation tempRelation;
  vector <int> relationInts, toAddInts;
  tempRelation.relationScheme = relationScheme;

  for (unsigned int i = 0; i < relationToJoin.relationScheme.schemeSize(); i++) {
    bool alreadyProcessed = false;
    for (unsigned int j = 0; j < relationScheme.schemeSize(); j++) {
      if (!alreadyProcessed) {
        if (relationScheme.At(j) != relationToJoin.relationScheme.At(i)) {
          alreadyProcessed = false;
        }
        else {
          alreadyProcessed = true;
        }
      }

    }
    if (!alreadyProcessed) {
      tempRelation.relationScheme.pushScheme(relationToJoin.relationScheme.At(i));
      toAddInts.push_back(i);
    }
  }
  for (auto i: relationTuples) {
    for (auto j: relationToJoin.relationTuples) {
      if (isJoinable(i, j, relationScheme, relationToJoin.relationScheme)) {
        Tuple newTuple = i;
        for(unsigned int k = 0; k < toAddInts.size(); k++) {
          newTuple.push_back(j.at(toAddInts.at(k)));
        }
        tempRelation.addTuple(newTuple);
      }
    }
  }

  return tempRelation;
}

bool Relation::isJoinable(Tuple tuple1, Tuple tuple2, Scheme scheme1, Scheme scheme2) {
  for (unsigned int i = 0; i < scheme1.schemeSize(); i++) {
    for (unsigned int j = 0; j < scheme2.schemeSize(); j++) {
      if (scheme1.At(i) == scheme2.At(j)) {
        if (tuple1.at(i)!= tuple2.at(j)) {
          return false;
        }
      }
    }
  }
  return true;
}

bool Relation::unite(Relation toUnite){
  bool willReturn = false;
  for (auto i : toUnite.relationTuples) {
    if(relationTuples.insert(i).second) {
      willReturn = true;
      if (relationScheme.schemeSize() != 0) {
        cout << "  ";
      }
      for (unsigned int j = 0; j < relationScheme.schemeSize(); j++) {
        cout << relationScheme.At(j) + "=" + i.at(j);
        if (j < relationScheme.schemeSize() - 1) {
          cout << ", ";
        }
      }
      if (relationScheme.schemeSize() != 0) {
        cout << "\n";
      }
    }
  }
  return willReturn;
}

void Relation::addTuple(Tuple tuples) {
  relationTuples.insert(tuples);
}
void Relation::setScheme(Scheme tempSchemes) {
  relationScheme = tempSchemes;
}
void Relation::setName(string tempName){
  name = tempName;
}

Relation Relation::select(int index, string value) {
  Relation tempRelation;
  tempRelation.setName(name);
  tempRelation.setScheme(relationScheme);

  for (auto i: relationTuples) {
    if (i.at(index) == value) {
      tempRelation.addTuple(i);
    }
  }
  return tempRelation;
}


Relation Relation::select(int i1, int i2){
  Relation tempRelation, tempRelation1;
  tempRelation.setName(name);
  tempRelation.setScheme(relationScheme);

  for (auto i: relationTuples) {
    if (i.at(i1) == i.at(i2)) {
      tempRelation.addTuple(i);
    }
  }
  return tempRelation;
}

Relation Relation::project(vector<int> points){

  Relation tempRelation;
  tempRelation.setName(name);
  for (auto i : relationTuples){
    Tuple tempTuple;
    for(unsigned j = 0; j < points.size(); j++) {
      tempTuple.push_back(i.at(points.at(j)));
    }
    tempRelation.addTuple(tempTuple);
  }
  Scheme tempScheme;
  for (unsigned int i = 0; i < points.size(); i++ ){
    tempScheme.pushScheme(relationScheme.At(points.at(i)));
  }
  tempRelation.setScheme(tempScheme);
  return tempRelation;
}

Relation Relation::rename(vector<string> names){
  Scheme tScheme;
  tScheme.getScheme(names);
  Relation tempRelation;
  tempRelation.setName(name);
  tempRelation.setScheme(tScheme);
  for (auto i : relationTuples) {
    tempRelation.addTuple(i);
  }
  return tempRelation;
}

void Relation::toString() {

  for (auto i : relationTuples) {
    if (relationScheme.schemeSize() != 0) {
      cout << "  ";
    }
    for (unsigned int j = 0; j < relationScheme.schemeSize(); j++) {
      cout << relationScheme.At(j) + "=" + i.at(j);
      if (j < relationScheme.schemeSize()-1) {
        cout << ", ";
      }
    }
    if (relationScheme.schemeSize() != 0) {
      cout << "\n";
    }
  }
  return;
}
