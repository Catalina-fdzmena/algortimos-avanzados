
#include "Graph.h"

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
  int i = 0;
  while (std::getline(input, line)) {
    if (i == 0) { // Ignorar primera linea de texto
      i++;
      continue;
    }
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