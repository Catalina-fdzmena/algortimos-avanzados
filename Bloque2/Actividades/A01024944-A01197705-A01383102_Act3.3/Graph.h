#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <limits.h>
#include <iomanip>


class Graph {
private:
  int numNodes;
  int numEdges;
  // Lista de adyacencia para grafo no dirijido
  std::vector<std::list<int>> adjList;
  std::vector<int> colores;
  void split(std::string line, std::vector<int> &res);
  
public:
  Graph();
  ~Graph();
  void readGraph(std::istream &input);
  void print();
  void DFS(int v);
  void BFS(int v);
  void shortestPath(int src);
  void floydWarshall();
  bool colorBipartiteGraph(int vertex, int color);
};

Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  adjList.clear();
  numNodes = 0;
  numEdges = 0;
}

void Graph::split(std::string line, std::vector<int> &res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::readGraph(std::istream &input) {
  std::string line;
  int i = 1;
  while (std::getline(input, line)) {
    if (i == 1) {
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[2];
      // Reservar memoria para los renglones 
      // de la lista de adyacencia (renglon 0 no utilizado) 
      adjList.resize(numNodes + 1);
      colores.resize(numNodes + 1);
      // Declara una lista vacia para cada renglon y 
      // la almacena en el vector
      for (int k = 1; k <= numNodes; k++) {
        std::list<int> tmpList;
        adjList[k] = tmpList;
        colores[k] = -1;
      }
      i++;
      continue; 
    }

    std::vector<int> res;
    split(line, res);
    int u = res[0];
    int v = res[1];
    adjList[u].push_back(v);
    adjList[v].push_back(u);

    i++;
  }
}

void Graph::print() {
  std::cout << "Adjacency List" << std::endl;
  for (int u = 1; u <= numNodes; u++){
    std::cout << "vertex " << u << ":";
    std::list<int> g = adjList[u];
    std::list<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      int verticeAdyacente = *it;
      std::cout << '\t' << verticeAdyacente;
    }
    std::cout << std::endl;
  }
}

// Complejidad de tiempo: O(V + E)
// Complejidad de espacio: O(V)
bool Graph::colorBipartiteGraph(int vertex, int color) {
  if (colores[vertex] != -1 && colores[vertex] != color)
    return false;

  colores[vertex] = color;
  bool answer = true;

  std::list<int> g = adjList[vertex];
  std::list<int>::iterator it;
  for (it = g.begin(); it != g.end(); ++it) {
    int verticeAdyacente = *it;
    if (colores[verticeAdyacente] == -1)
      answer = colorBipartiteGraph(verticeAdyacente, 1 - color);
    if (colores[verticeAdyacente] != -1 && colores[verticeAdyacente] != 1 - color)
      return false;
    if (!answer)
      return false;
  }

  return true;
}

#endif // _GRAPH_H_