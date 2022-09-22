#ifndef _NODETRIE_H
#define _NODETRIE_H

#include <iostream>
#include <vector>

class nodeTrie {
private:
  char letter;
  bool isLeaf;
  nodeTrie *parent;
  std::vector<nodeTrie *> child;

public:
  nodeTrie();
  nodeTrie(char c, nodeTrie *p);
  nodeTrie *getChild(char c);
  void setChild(nodeTrie *ptrChild);
  bool getIsLeaf();
  void setIsLeaf(bool value);
  char getLetter();
};

nodeTrie::nodeTrie() {
  letter = '\0';
  isLeaf = false;
  parent = nullptr;
  child = std::vector<nodeTrie *>(26, nullptr);
}

nodeTrie::nodeTrie(char c, nodeTrie *ptrParent) {
  letter = c;
  isLeaf = false;
  parent = ptrParent;
  child = std::vector<nodeTrie *>(26, nullptr);
}

nodeTrie *nodeTrie::getChild(char c) { 
  return child[c - 'a']; 
}

void nodeTrie::setChild(nodeTrie *ptrChild) {
  child[ptrChild->letter - 'a'] = ptrChild;
}

bool nodeTrie::getIsLeaf() { 
  return isLeaf; 
}

char nodeTrie::getLetter() { 
  return letter; 
}

void nodeTrie::setIsLeaf(bool value) { 
  isLeaf = value; 
}

#endif // _NODETRIE_H