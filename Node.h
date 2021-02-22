#ifndef INC_236_PROJ5_NODE_H
#define INC_236_PROJ5_NODE_H
#pragma once
#include <set>


class Node {
public:
  std::set<int> adjacencies;
  int id;
  bool isVisited;
  bool isSelfDependent;
  Node() {
    isVisited = false;
  }
};


#endif //INC_236_PROJ5_NODE_H
