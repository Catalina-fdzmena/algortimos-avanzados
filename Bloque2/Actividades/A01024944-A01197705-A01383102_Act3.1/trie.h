#ifndef _TRIE_H
#define _TRIE_H

#include "nodeTrie.h"
#include <cstddef>
#include <cstring>
#include <iostream>

class trie {
private:
  nodeTrie *root;

public:
  trie();
  ~trie();
  void insert(std::string word);
  bool search(std::string word);
  void dfs();
};

trie::trie() { 
  root = new nodeTrie(); 
}

trie::~trie() {
  // to-do
  // Implementa un recorrido del trie para
  // liberar su memoria
}

void trie::insert(std::string word) {
  nodeTrie *current = root;
  for (int i = 0; i < (int)word.length(); i++) {
    if (current->getChild(word[i]) == nullptr) {
      nodeTrie *newNode = new nodeTrie(word[i], current);
      current->setChild(newNode);
    }
    current = current->getChild(word[i]);
  }
  current->setIsLeaf(true);
}

bool trie::search(std::string word) {
  nodeTrie *current = root;
  if (current == nullptr)
    return false;
  for (int i = 0; i < (int)word.length(); i++) {
    current = current->getChild(word[i]);
    if (current == nullptr)
      return false;
  }
  return current->getIsLeaf();
}

void trie::dfs() {
  // to-do
  // Implementa un recorrido DFS del trie
  // para imprimir todas las palabras en orden alfabetico
}

#endif // _TRIE_H