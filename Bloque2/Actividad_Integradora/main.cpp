 /**
 * Ejemplo que implementa la lectura de los casos de prueba
 * para la Act Ingradora 2
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main < TestCases/test01.txt
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main < TestCases/test01.txt
 **/

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
      std::cout << line << std::endl;
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
  


int main() {
  std::cout << "Ejemplo de coloreo de grafos!" << std::endl;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  // Construye un grafo a partir de la consola usando
  // representacion de Lista de adyacencia
  Graph grafo1;
  Graph grafo2;
  readTestCase(inputInfo, grafo1, grafo2);
  std::cout << "Grafo 1"<< std::endl;
  grafo1.print();
  //std::cout << "Grafo 2"<< std::endl;
  //grafo2.print();
  grafo1.BranchAndBoundTSP();
  return 0;
}