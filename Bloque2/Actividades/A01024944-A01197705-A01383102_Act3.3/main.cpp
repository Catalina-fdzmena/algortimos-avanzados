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
using namespace std;

int main() {
	stringstream inputInfo;
  	inputInfo << cin.rdbuf(); 

  	Graph g1;
  	g1.readGraph(inputInfo);

	return 0;
}

