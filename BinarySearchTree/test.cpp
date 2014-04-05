#include <iostream>

#include "BST.h"

int main() {
  BST bst;
  bst.insert(10);
  bst.insert(13);
  bst.insert(5);
  bst.insert(23);
  bst.insert(3);
  bst.insert(7);
  bst.inorderWalk();
  std::cout << bst.max() << "\n";
  std::cout << bst.min() << "\n";
  std::cout << bst.search(10) << "\n"
            << bst.search(13) << "\n"
            << bst.search(5) << "\n"
            << bst.search(23) << "\n"
            << bst.search(3) << "\n"
            << bst.search(7) << "\n";
  return 0;
}

