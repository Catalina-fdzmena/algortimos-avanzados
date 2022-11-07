/*
** Integrantes:
**    José Emilio Alvear Cantú - A01024944
**    Andrea Catalina Fernández Mena - A01197705
**    Carlos Milano - A01383102
**
** Referencias:
**    Algoritmo de Maximum Flow obtenido de: https://www.youtube.com/watch?v=duKIzgJQ1w8
**    Algoritmo de Prim obtenido de: https://youtu.be/4ZlRH0eK-qQ 
**    
*/

#include <iostream>
#include <sstream>
#include "Graph.h"


void split(std::string line, std::vector<int> &res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void readTestCase(std::istream &input, Graph &g1, Graph &g2) {
  std::string line;
  int numNodes1, numNodes2;
  int numEdges1, numEdges2;
  int start, end;
  std::vector<std::string> aristas1;
  std::vector<std::string> aristas2;
  int i = 0;
  while (std::getline(input, line)) {
    if (i == 0) { // Ignorar primera linea de texto
      i++;
      continue;
    }
    if (i == 1) {
      std::vector<int> res;
      split(line, res);
      numNodes1 = res[0];
      numEdges1 = res[1];
      i++;
      continue; 
    }
    if (i > 1 && i <= numEdges1+1) {
      aristas1.push_back(line);
      i++;
      continue;
    }
    if (i == numEdges1+2) {
      std::vector<int> res;
      split(line, res);
      numNodes2 = res[0];
      numEdges2 = res[1];
      start = res[2];
      end = res[3];
      i++;
      continue;
    }
    aristas2.push_back(line);
    i++;
  }
  // construir grafos
  g1.initUndirectedGraph(numNodes1, numEdges1, 0, 0, aristas1);
  g2.initDirectedGraph(numNodes2, numEdges2, start, end, aristas2);
}
  


int main()
{
  Graph grafo1;
  Graph grafo2;

  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  readTestCase(inputInfo, grafo1, grafo2);

  std::cout << "Problem 1" << std::endl;
  grafo1.Prim();  //Problema de Prim's Algorithm
  std::cout << std::endl;

  std::cout << "Problem 2" << std::endl;
  grafo1.BranchAndBoundTSP(); //Problema de Branch and Bound
  std::cout << std::endl;

  std::cout << "Problem 3" << std::endl;
  grafo2.MaximumFlow(); //Problema de Dinics Flow 

  return 0;
}