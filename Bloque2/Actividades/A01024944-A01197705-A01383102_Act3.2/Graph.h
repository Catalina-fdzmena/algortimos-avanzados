#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <list>
#
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

class Graph {
private:
  int numNodes;
  int numEdges;
  // Lista de adyacencia
  // vector de listas ligadas de pares (vertice, peso)
  std::vector<std::list<std::pair<int, int>>> adjList;
  
  void split(std::string line, std::vector<int> &res);
  
public:
  Graph();
  ~Graph();
  void readGraph(std::istream &input);
  void print();
  void DFS(int v);
  void BFS(int v);
};


#endif // _GRAPH_H_
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

class Graph {
private:
  int numNodes;
  int numEdges;
  // Lista de adyacencia
  // vector de listas ligadas de pares (vertice, peso)
  std::vector<std::list<std::pair<int, int>>> adjList;

  void split(std::string line, std::vector<int> &res);

public:
  Graph();
  ~Graph();
  void readGraph(std::istream &input);
  void print();
  void DFS(int v);
  void BFS(int v);
};

//Shortest Path 


/*
void Graph::shortestP(int src)
{
   
    
    priority_queue<std::pair<int, int>, 
    vector<std::pair<int, int>>,
    greater<std::pair<int, int>> >
        pq;

    vector<int> distancia(numNodes+1, distToInfinity);

    pq.push(std::crearPair(0, src));
    distancia[src] = 0; //se denomina distanciancia 0 (estando en src)
 

    while (!pq.empty()) {
        int u = pq.top().second; 
        pq.pop();

        list<std::pair<int,int>> parNodosLista = adjList[u];
        list<std::pair<int,int>>::iterator loopCheck;
        for (it = parNodosLista.begin(); it != parNodosLista.end(); ++loopCheck) {
          pair<int,int> par = *loopCheck; //Leer los pares
          int v = par.first; //nodo
          int pesoArista = par.second; 

          if (distancia[v] > distancia[u] + pesoArista) {
            //Acumlar cambios en distanciaancia de vertices
            distancia[v] = distancia[u] + pesoArista;
            pq.push(std::crearPair(distancia[v], v));
          }
        }
    }

    // Print
    for (int i = 1; i < numNodes+1; ++i)
      if (distancia[i] == distToInfinity) {
        cout << i << " distToInfinity" << std::endl;
      } else {
        cout << i << " " << distancia[i] << std::endl;
      }
}

*/





#endif // _GRAPH_H_


