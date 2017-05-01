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

  //roll LL test
  AVLTree<int, int> tree2;
  tree2.insert(2,3);
  tree2.insert(6,7);
  tree2.insert(8,9);

  std::cout << "head: " << *((tree2.head)->key) << std::endl;
  std::cout << "right: " << *(((tree2.head)->right)->key) << std::endl;
  std::cout << "left: " << *(((tree2.head)->left)->key) << std::endl;

  //roll RL test
  AVLTree<int, int> tree3;
  tree3.insert(1,3);
  tree3.insert(5,7);
  tree3.insert(3,9);
  std::cout << "head: " << *((tree3.head)->key) << std::endl;
  std::cout << "right: " << *(((tree3.head)->right)->key) << std::endl;
  std::cout << "left: " << *(((tree3.head)->left)->key) << std::endl;

  //roll LR test
  AVLTree<int, int> tree4;
  tree4.insert(3,3);
  tree4.insert(1,7);
  tree4.insert(2,9);
  std::cout << "head: " << *((tree4.head)->key) << std::endl;
  std::cout << "right: " << *(((tree4.head)->right)->key) << std::endl;
  std::cout << "left: " << *(((tree4.head)->left)->key) << std::endl;

}

main(){
 AVLTreeRollTest();
}
