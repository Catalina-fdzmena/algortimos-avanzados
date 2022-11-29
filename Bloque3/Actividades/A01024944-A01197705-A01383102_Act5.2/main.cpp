/*
** Integrantes:
**    José Emilio Alvear Cantú - A01024944
**    Andrea Catalina Fernández Mena - A01197705
**    Carlos Milano - A01383102
**
** Actividad:
**    Actividad 5.1 Implementación backtracking con Bitmask
**
** Referencias:
** Revisar un string es un número: https://www.baeldung.com/java-check-string-number 
** Subsets Bitmask approach:  https://www.geeksforgeeks.org/find-distinct-subsets-given-set/ 
**
**
----Instrucciones ----
** Compilacion para ejecucion:
**    g++ -o main.exe main.cpp
** Ejemplo de ejecucion:
-------------forma2----------------
** Compilacion para ejecucion:
** g++ -std=c++17 -O3 -o main *.cpp
** ./main < TestCases/test01.txt
** 
*/

//Preprocesors
#include <iostream>
#include <sstream>
#include "Graph.h"


int main() {
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf(); 
  // Construye un grafo a partir de la consola usando
  // representacion de Lista de adyacencia
  Graph g1;
  g1.readGraph(inputInfo);
  g1.print();
  g1.localSearch();
  return 0;
}