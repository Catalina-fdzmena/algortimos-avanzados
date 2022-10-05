#include "Graph.h"
#include <limits.h>
#include <iomanip>

#define INF INT_MAX

Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  adjList.clear();
  numNodes = 0;
  numEdges = 0;
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

void Graph::readGraph(std::istream &input) {
  std::string line;
  int i = 1;
  while (std::getline(input, line)) {
    if (i == 1) {
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[2];
      // Reservar memoria para los renglones 
      // de la lista de adyacencia (renglon 0 no utilizado) 
      adjList.resize(numNodes+1);
      // Declara una lista vacia para cada renglon y 
      // la almacena en el vector
      for (int k = 1; k <= numNodes; k++) {
        std::list<std::pair<int,int>> tmpList; // lista de pares(nodo, peso)
        adjList[k] = tmpList; 
      }
      i++;
      continue; 
    }

    std::vector<int> res;
    split(line, res);
    int u = res[0];
    int v = res[1];
    int weight = res[2];    
    // Grafos dirigidos agrega solo la arista (u,v)
    // Grafo ponderado guarda pares(nodo, peso)
    adjList[u].push_back(std::make_pair(v, weight));
    i++;
  }
}

void Graph::print() {
  std::cout << "Adjacency List" << std::endl;
  for (int u = 1; u <= numNodes; u++){
    std::cout << "vertex " << u << ":";
    std::list<std::pair<int,int>> g = adjList[u];
    std::list<std::pair<int,int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int,int> par = *it;
      std::cout << '\t' << "{"<< par.first << "," << par.second << "}";
    }
    std::cout << std::endl;
  }
}

void Graph::DFS(int v) {
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos un stack 
  std::stack<int> stack;
  std::cout << "Recorrido DFS " << std::endl;
  // Entra al stack el vertice inicial
  stack.push(v);
  while(!stack.empty()) {
    // Extraemos un vertice del stack y lo procesamos (print) 
    v = stack.top(); 
    stack.pop();
    bool isInVisited = visited.find(v) != visited.end();
    if (!isInVisited) {
      visited.insert(v);
      std::cout << v << " ";
    }
    // Obtenemos los vertices adyacentes del vertice v
    // Si estos no han sido visitados se marcan como visitados
    // y los metemos al stack
    std::list<std::pair<int,int>> g = adjList[v];
    std::list<std::pair<int,int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int,int> par = *it;
      int u = par.first;
      // Verificar si el vecino u ya fue visitado
      isInVisited = visited.find(u) != visited.end();
      if (!isInVisited) { // no visitado
        stack.push(u);
      }
    }
  }
  std::cout << std::endl;
}

void Graph::BFS(int v) {
  // Declarar un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Crear un queue
  std::queue<int> queue;
  // Marcar al vertice actual v como visitado y meterlo en el queue
  visited.insert(v);
  queue.push(v);
  std::cout << "Recorrido BFS" << std::endl;
  while (!queue.empty()) {
    // Extraer un vertice del queue
    v = queue.front();
    queue.pop();
    std::cout << v << " ";
    // Obtener los vecinos del vertice v
    // Si estos no han sido visitados marcarlos como visitados
    // y los metemos en el queue
    // Recorremos los vertices vecinos de v
    std::list<std::pair<int,int>> g = adjList[v];
    std::list<std::pair<int,int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int,int> par = *it;
      int u = par.first;
      // Verificar si el vecino u ya fue visitado
      bool isInVisited = visited.find(u) != visited.end();
      if (!isInVisited) { // no visitado
        visited.insert(u);
        queue.push(u);
      }
    }    
  }
  std::cout << std::endl;
}

// Complejidad de tiempo: O(V^3)
// Complejidad de espacio: O(V^2)
void Graph::floydWarshall() {
  // Inicializar matriz de las distancias mas cortas
  std::vector<std::vector<int>> dist(numNodes, std::vector<int> (numNodes, INF));
  for (int i = 0; i < dist.size(); i++) { dist[i][i] = 0; }

  // Llenar matriz con la lista de adyacencias 
  for (int nodo = 1; nodo <= numNodes; nodo++){
    std::list<std::pair<int,int>> nodosAdyacentes = adjList[nodo];
    std::list<std::pair<int,int>>::iterator it;
    for (it = nodosAdyacentes.begin(); it != nodosAdyacentes.end(); ++it) {
      std::pair<int,int> par = *it;
      dist[nodo - 1][par.first - 1] = par.second;
    }
  }

  // Se actualiza la matriz con las distancias y el algoritmo de floyd warshal
  for (int k = 0; k < numNodes; k++) {
    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < numNodes; j++) {
        if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF)) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  // Imprimir matriz de distancias
  for (int i = 0; i < dist.size(); i++) {
    for (int j = 0; j < dist[i].size(); j++) {
      if (dist[i][j] == INF) {
        std::cout << std::left << std::setw(8) << "INF";
      } else {  
        std::cout << std::left << std::setw(8) << dist[i][j]; 
      }
    }
    std::cout << std::endl;
  }
}

// Complejidad de tiempo: O((|V + E|)log|V|)
// Complejidad de espacio: O(V + E)
void Graph::shortestPath(int src) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
  std::vector<int> dist(numNodes + 1, INF);
  pq.push(std::make_pair(0, src));
  dist[src] = 0;

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    std::list<std::pair<int,int>> nodosAdyacentes = adjList[u];
    std::list<std::pair<int,int>>::iterator it;
    for (it = nodosAdyacentes.begin(); it != nodosAdyacentes.end(); ++it) {
      std::pair<int,int> par = *it;
      int v = par.first;
      int peso = par.second;

      if (dist[v] > dist[u] + peso) {
        dist[v] = dist[u] + peso;
        pq.push(std::make_pair(dist[v], v));
      }
    }
  }

  for (int i = 1; i < numNodes + 1; i++)
    if (dist[i] == INF) {
      std::cout << i << ": INF" << std::endl;
    } else {
      std::cout << i << ": " << dist[i] << std::endl;
    }
}