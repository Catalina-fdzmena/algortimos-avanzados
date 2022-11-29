
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
        std::list<int> tmpList; // lista de int (vertice)
        adjList[k] = tmpList; 
      }
      i++;
      continue; 
    }
    std::vector<int> res;
    split(line, res);
    int u = res[0];
    int v = res[1];
    // Grafos no dirigidos agrega la arista (u,v) y la (v,u)
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    i++;
  }
}

void Graph::print() {
  std::cout << "Adjacency List" << std::endl;
  for (int u = 1; u <= numNodes; u++){
    std::cout << "vertex " << u << ":";
    std::list<int> g = adjList[u];
    std::list<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      int v = *it;
      std::cout << '\t' << v << ",";
    }
    std::cout << std::endl;
  }
}


void Graph::localSearch() {
  std::vector<int> s(numNodes+1);
  // Create initial solution
  
  for (int i = 1; i <= numNodes; i++) s[i] = i;
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(s), std::end(s), rng);
  std::cout << "Solucion inicial" << std::endl;
  for (int i = 1; i <= numNodes; i++) {
    std::cout << s[i] << " ";
  }
  std::cout << std::endl;
  bool improvement = true;
  do {
    
    
  } while (improvement);
  
  
}