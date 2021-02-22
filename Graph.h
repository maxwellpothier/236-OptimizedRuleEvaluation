#ifndef INC_236_PROJ5_GRAPH_H
#define INC_236_PROJ5_GRAPH_H
#pragma once
#include "Node.h"
#include <map>
#include <stack>
#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
  // Public Variables
  map<int, Node> nodeMap;
  stack<int> topSearch;
  vector<set<int>> scc;
  set<int> local;

  // Public Functions
  void dfs(Node theNode) {
    if (theNode.isVisited == true) {
      return;
    } else {
      nodeMap.at(theNode.id).isVisited = true;
      for (auto i : theNode.adjacencies) {
        if (nodeMap[i].isVisited == false) {
          dfs(nodeMap[i]);
        }
      }
      topSearch.push(theNode.id);
    }
  }

  void dfsForest() {
    for (auto i : nodeMap) {
      if (i.second.isVisited == false) {
        dfs(i.second);
      }
    }
  }

  void dfsForestForward() {
    while (topSearch.size() != 0) {
      if (!nodeMap[topSearch.top()].isVisited) {
        dfsSCC(nodeMap[topSearch.top()]);
      } else {
        if (local.size() != 0) {
          scc.push_back(local);
          local.clear();
        }
        topSearch.pop();
      }
    }
  }

  void dfsSCC(Node theNode) {
    if (theNode.isVisited == true) {
      return;
    } else {
      nodeMap.at(theNode.id).isVisited = true;
      local.insert(theNode.id);
      for (auto i: theNode.adjacencies) {
        if (nodeMap[i].isVisited == false) {
          dfsSCC(nodeMap[i]);
        }
      }
    }
  }

  void addEdge(int from, int to, bool dependent) {
    nodeMap[from].adjacencies.insert(to);
    nodeMap[from].isSelfDependent = dependent;
  }

  void toString() {
    cout << "Dependency Graph" << endl;
    for(auto i : nodeMap) {
      cout << "R" << i.first << ":";
      int x = i.second.adjacencies.size();
      int y = 0;
      for (auto j : i.second.adjacencies) {
        if (y != x - 1) {
          cout << "R" << j <<",";
        } else {
          cout << "R" << j;
        }
        y++;
      }
      cout << endl;
    }
  }
};

#endif //INC_236_PROJ5_GRAPH_H
