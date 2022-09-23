#ifndef _TRIE_H
#define _TRIE_H

#include "nodeTrie.h"
#include <cstddef>
#include <cstring>
#include <iostream>

class trie {
private:
  nodeTrie *root;
  void destroy(nodeTrie *node);
  void dfsHelper(nodeTrie *node, std::string stringHelper);

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
  destroy(root);
}

void trie::destroy(nodeTrie *node) {
  if (node != nullptr) {
    for (nodeTrie *childNode : node->getChild()) {
      if (childNode != nullptr) {
        destroy(childNode);
      }
    }
    delete(node);
  }
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
  std::string stringHelper = "";
  dfsHelper(root, stringHelper);
}

void trie::dfsHelper(nodeTrie *node, std::string stringHelper) {
  if (node != nullptr) {
    for (nodeTrie *childNode : node->getChild()) {
      if (childNode != nullptr) {
        if (childNode->getIsLeaf()) {
          std::cout << stringHelper + childNode->getLetter() << std::endl;
        }
        dfsHelper(childNode, stringHelper + childNode->getLetter());
      }
    }
  }
}

#endif // _TRIE_H