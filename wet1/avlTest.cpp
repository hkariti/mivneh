#include "avl.h"

void AVLTreeRollTest(){
  //rolll RR test
  AVLTree<int, int> tree;
  tree.insert(1,2);
  tree.insert(5,6);
  tree.insert(7,8);

  std::cout << "head: " << *((tree.head)->key) << std::endl;
  std::cout << "right: " << *(((tree.head)->right)->key) << std::endl;
  std::cout << "left: " << *(((tree.head)->left)->key) << std::endl;

  //rolll LL test
  AVLTree<int, int> tree2;
  tree2.insert(2,3);
  tree2.insert(6,7);
  tree2.insert(8,9);

  std::cout << "head: " << *((tree2.head)->key) << std::endl;
  std::cout << "right: " << *(((tree2.head)->right)->key) << std::endl;
  std::cout << "left: " << *(((tree2.head)->left)->key) << std::endl;

}

main(){
 AVLTreeRollTest();
}
