#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <queue>
#include "NodeBB.h"

#define INF 0x3f3f3f3f

class Graph {
private:
  int numNodes;
  int numEdges;
  bool directedGraph;
  int start;
  int end;
  // Lista de adyacencia -- MST
  // vector de listas de pares (vertice, peso)
  std::vector<std::list<std::pair<int, int>>> adjList;
  // Matriz de adyacencia  -- TSP
  std::vector<std::vector<int>> adjMatrix;
    
  void split(std::string line, std::vector<int> &res);
  void calculaCostoPosible(NodeBB &nodoActual);

  // Funciones para MaximumFlow
  bool buildResidualGraph(std::vector<int> &levels, std::vector<std::vector<int>> &residualGraph);
  int sendFlow(std::vector<std::vector<int>> &residualGraph, std::vector<int> levels, std::vector<int> &counts, int currentNode, int flow);
  
public:
  Graph();
  ~Graph();
  void initUndirectedGraph(int n, int m, int s, int e, std::vector<std::string> aristas);
  void initDirectedGraph(int n, int m, int s, int e, std::vector<std::string> aristas);
  void print();
  void BranchAndBoundTSP();
  void MaximumFlow();
};


#endif // _GRAPH_H_