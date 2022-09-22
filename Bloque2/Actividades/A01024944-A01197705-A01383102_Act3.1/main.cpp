 /** 
* Ejemplo que implementa un Trie (Arbol de prefijos)
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/
#include <iostream>
#include <string>
#include "trie.h"

int main() {
  trie T;
  std::string palabra;
  int N, M;
  
  // Se leen palabras y se insertan
  std::cin >> N;
  for (int i = 0; i < N; i++) {
    std::cin >> palabra;
    T.insert(palabra);
  }

  // Busqueda dfs por palabra

  // Se leen palabras a buscar y se imprimen los booleanos
  std::cin >> M;
  for (int i = 0; i < M; i++) {
    std::cin >> palabra;
    std::cout << std::boolalpha << T.search(palabra) << std::endl;
  }

  return 0;
}