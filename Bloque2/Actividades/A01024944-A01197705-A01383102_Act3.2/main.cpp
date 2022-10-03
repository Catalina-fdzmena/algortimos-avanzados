/*
--Actividad 3.2--
--Integrantes de Equipo:
	* Jose Emilio Alvear Cantu - A01024944
	* Andrea Catalina Fernandez Mena - A01197705
	* Carlos Milano - A01383102
*/

/** 
* Ejemplo que implementa Grafos dirigidos ponderados con una
* Lista de adyacencia y los algoritmos DFS y BFS
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


int main() {
  std::cout << "Ejemplo de grafos (representacion y recorridos)!" << std::endl;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf(); 
  // Construye un grafo a partir de la consola usando
  // representacion de Lista de adyacencia
  Graph g1;
  g1.readGraph(inputInfo);
  g1.print();
  g1.DFS(1);
  g1.BFS(1);
}