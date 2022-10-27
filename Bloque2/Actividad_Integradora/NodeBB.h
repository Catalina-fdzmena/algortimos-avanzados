#ifndef _NODEBB_H_
#define _NODEBB_H_

#include <vector>

class NodeBB {
  private: 
    int nivel;                   // nivel en el arbol B&B
    int costoAcumulado;          // costo acumulado (CA)
    int costoPosible;            // costo posible (lb)
    int verticeAnterior;         // ultimo vertice del grafo visitado
    int verticeActual;           // vertice actual del grafo
    std::vector<bool> visitados; // vertices del grafo visitados
    std::vector<int> pathTSP;    // ruta TSP 

  public:
    NodeBB(int numNodes);
    ~NodeBB();
    // sobrecarga del operador < para usarse en la lista priorizada (minHeap)
    bool operator < (const NodeBB &other) const {
      return costoPosible >= other.costoPosible; 
    }

    friend class Graph;    // friend class

};


#endif // _NODEBB_H_
