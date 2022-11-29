
#ifndef _GRAPH_H_
#define _GRAPH_H_


#include <iostream>
#include <list>
#include <random>
#include <algorithm>
#include <vector>

class Graph {
private:
  int numNodes;
  int numEdges;
  // Lista de adyacencia
  // vector de listas ligadas de enteros
  std::vector<std::list<int>> adjList;
  // Solucion potencial
  std::vector<int> solution;

  void split(std::string line, std::vector<int> &res);

public:
  Graph();
  ~Graph();
  void readGraph(std::istream &input);
  void print();
  void localSearch();

};

#endif // _GRAPH_H_
