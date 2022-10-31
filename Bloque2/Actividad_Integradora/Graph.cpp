#include "Graph.h"

Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  directedGraph = false;
}

Graph::~Graph() {
  adjList.clear();
  adjMatrix.clear();
  numNodes = 0;
  numEdges = 0;
  directedGraph = false;
}

void Graph::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::initUndirectedGraph(int n, int m, int s, int e,
                                std::vector<std::string> aristas) {
  numNodes = n;
  numEdges = m;
  start = s;
  end = e;
  directedGraph = false;
  // Reservar memoria la lista de adyacencia (renglon 0 no utilizado)
  adjList.resize(numNodes + 1);
  // Reservar memoria para la matriz de adyacencia (renglon 0 no utilizado)
  adjMatrix.resize(numNodes + 1);
  // Declara una lista vacia para cada renglon de la lista de adyacencia
  for (int k = 0; k <= numNodes; k++) {
    std::list<std::pair<int, int>> tmpList; // Lista de pares (vertices, peso)
    std::vector<int> tmpVector(numNodes + 1, INF);
    adjList[k] = tmpList;
    adjMatrix[k] = tmpVector;
  }
  for (int i = 0; i < (int)aristas.size(); i++) {
    std::string line = aristas[i];
    std::vector<int> res;
    split(line, res);
    int u = res[0];
    int v = res[1];
    int weight = res[2];
    // Grafos no dirigidos agrega la arista (u,v) y la (v,u)
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight});
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
  }
}

void Graph::initDirectedGraph(int n, int m, int s, int e,
                              std::vector<std::string> aristas) {
  numNodes = n;
  numEdges = m;
  start = s;
  end = e;
  directedGraph = true;
  // Reservar memoria la lista de adyacencia (renglon 0 no utilizado)
  adjList.resize(numNodes + 1);
  // Reservar memoria para la matriz de adyacencia (renglon 0 no utilizado)
  adjMatrix.resize(numNodes + 1);
  // Declara una lista vacia para cada renglon de la lista de adyacencia
  for (int k = 0; k <= numNodes; k++) {
    std::list<std::pair<int, int>> tmpList; // Lista de pares (vertices, peso)
    std::vector<int> tmpVector(numNodes + 1, 0);
    adjList[k] = tmpList;
    adjMatrix[k] = tmpVector;
  }
  for (int i = 0; i < (int)aristas.size(); i++) {
    std::string line = aristas[i];
    std::vector<int> res;
    split(line, res);
    int u = res[0];
    int v = res[1];
    int weight = res[2];
    // Grafos dirigidos agrega solo la arista (u,v)
    adjList[u].push_back({v, weight});
    adjMatrix[u][v] = weight;
  }
}

void Graph::print() {
  std::cout << "Directed graph: " << std::boolalpha << directedGraph
            << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int u = 1; u <= numNodes; u++) {
    std::cout << "vertex " << u << ":";
    std::list<std::pair<int, int>> g = adjList[u];
    std::list<std::pair<int, int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int, int> par = *it;
      std::cout << "{" << par.first << "," << par.second << "} ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl << "Adjacency Matrix" << std::endl;
  for (int u = 1; u <= numNodes; u++) {
    for (int v = 1; v <= numNodes; v++) {
      std::cout << adjMatrix[u][v] << " ";
    }
    std::cout << std::endl;
  }
}

void Graph::calculaCostoPosible(NodeBB &nodoActual) {
  nodoActual.costoPosible = nodoActual.costoAcumulado;
  int costoObtenido = 0;
  for (int i = 1; i <= numNodes; i++) {
    costoObtenido = INF;
    // si no he visitado al vertice i o si es el ultimo vertices del recorrido
    if (!nodoActual.visitados[i] || i == nodoActual.verticeActual) {
      if (!nodoActual.visitados[i]) {
        for (int j = 1; j <= numNodes; j++) {
          if (i != j && (!nodoActual.visitados[j] || j == 1)) {
            costoObtenido = std::min(costoObtenido, adjMatrix[i][j]);
          }
        }
      } else { // es el ultimo visitado
        for (int j = 1; j <= numNodes; j++) {
          if (!nodoActual.visitados[j]) {
            costoObtenido = std::min(costoObtenido, adjMatrix[i][j]);
          }
        }
      }
      if (costoObtenido != INF)
        nodoActual.costoPosible += costoObtenido;
      else
        nodoActual.costoPosible = INF;
    }
  }
}

void Graph::BranchAndBoundTSP() {
  int bestCostTSP = INF;
  std::vector<int> bestPathTSP;
  int src = 1; // primer vertice del recorrido TSP
  NodeBB tope(numNodes);
  tope.visitados[src] = true;
  tope.verticeActual = src;
  tope.verticeAnterior = 0;
  tope.pathTSP.push_back(src);
  calculaCostoPosible(tope);
  
  std::priority_queue<NodeBB> pq;
  pq.push(tope);
  while (!pq.empty()) {
    tope = pq.top();
    pq.pop();
    // Si el nodo puede generar un camino mas corto que el mejor actual
    if (tope.costoPosible < bestCostTSP) {
      for (int j = 1; j <= numNodes; j++) {
        int i = tope.verticeActual;
        NodeBB raiz = tope;
        if (!raiz.visitados[j] && adjMatrix[i][j] != INF) {
          raiz.verticeAnterior = raiz.verticeActual;
          raiz.verticeActual = j;
          raiz.visitados[j] = true;
          raiz.pathTSP.push_back(j);
          raiz.nivel++;
          raiz.costoAcumulado += adjMatrix[i][j];
          // Si llegamos al penultimo vertice del recorrido
          if (raiz.nivel == numNodes - 2) {
            int falta = 0;
            for (int k = 2; k <= numNodes; k++) {
              if (!raiz.visitados[k])
                falta = k;
            }
            if (adjMatrix[raiz.verticeActual][falta] != INF &&
                adjMatrix[falta][src] != INF) {
              // costo real
              raiz.costoAcumulado += adjMatrix[raiz.verticeActual][falta];
              raiz.costoAcumulado += adjMatrix[falta][src];
              raiz.pathTSP.push_back(falta);
              raiz.pathTSP.push_back(src);
            } else {
              raiz.costoAcumulado = INF;
            }
            if (raiz.costoAcumulado < bestCostTSP) {
              bestCostTSP = raiz.costoAcumulado;
              bestPathTSP = raiz.pathTSP;
            }
          } else {
            calculaCostoPosible(raiz);
            if (raiz.costoPosible < bestCostTSP) {
              pq.push(raiz);
            }
          }
        }
      }
    }
  }
  
  std::cout << "Path: " << std::endl;
  for (int i = 0; i < (int)bestPathTSP.size(); i++) {
    std::cout << bestPathTSP[i] << " ";
  }

  std::cout << std::endl << "Optimal cost: " << bestCostTSP << std::endl;
}
