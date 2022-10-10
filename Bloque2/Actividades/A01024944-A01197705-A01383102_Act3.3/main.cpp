/*
--Actividad 3.3--
Grafos bipartitas

--Integrantes de Equipo:
	* Jose Emilio Alvear Cantu - A01024944
	* Andrea Catalina Fernandez Mena - A01197705
	* Carlos Milano - A01383102
*/

#include <iostream>
#include <sstream>
#include "Graph.h"

int main() {
	std::stringstream inputInfo;
  	inputInfo << std::cin.rdbuf(); 

  	Graph g1;
  	g1.readGraph(inputInfo);
	g1.print();

	return 0;
}

