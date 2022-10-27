#include "NodeBB.h"

NodeBB::NodeBB(int numNodes) {
  nivel = 0;
  costoAcumulado = 0;
  costoPosible = 0;
  verticeAnterior = 0;
  verticeActual = 0;
  visitados = std::vector<bool>(numNodes+1, false);
  pathTSP.clear();   
}

NodeBB::~NodeBB() {
  nivel = 0;
  costoAcumulado = 0;
  costoPosible = 0;
  verticeAnterior = 0;
  verticeActual = 0;
  visitados.clear();
  pathTSP.clear();
}