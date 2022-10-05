/*
--Actividad 3.2--
--Integrantes de Equipo:
	* Jose Emilio Alvear Cantu - A01024944
	* Andrea Catalina Fernandez Mena - A01197705
	* Carlos Milano - A01383102
*/

//Info recabada de: 
 // https://www.geeksforgeeks.org/implement-min-heap-using-stl/


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


== Ejecución desde CMD ==
1.- Direccionarse a carpeta indicada
2.- colocar desde la terminal:   g++ -o main.exe main.cpp graph.cpp
3.- Posteriormente a correr, una vez que se muestre que se creo un archivo main.exe colocar de la terminal lo siguiente: 
                    main.exe < TestCases\test01.txt     (o el test case que quiera revisar)
4. - Su resultado se imprimirá en la terminal :) 

**/

#include <iostream>
#include <sstream>
#include "Graph.h"


int main() {
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf(); 

  Graph g1;
  g1.readGraph(inputInfo);

  std::cout << "Dijkstra, shortest paths from source vertex" << std::endl;
  g1.shortestPath(1);
  std::cout << "Floyd-Warshall, all pairs shortest path" << std::endl;
  g1.floydWarshall();
}