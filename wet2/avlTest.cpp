#include "avl.h"

template <typename T>
void treeSanity(AVLTree<T, int>& tree) {
  std::cout << "Sanity" << std::endl;
  tree.print();
  tree.checkOrder();
  tree.checkBF();
  tree.checkParents();
}

void AVLTreeRollTest(){
  /*//rolll RR test
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

  treeSanity(tree);
  treeSanity(tree2);
  treeSanity(tree3);
  treeSanity(tree4);*/

  AVLTree<int, int> tree;
  tree.insert(2,2);
  tree.insert(1,1);
  tree.insert(3,3);
  tree.insert(4,4);
  treeSanity(tree);

  std::cout << "removing 1" << std::endl;
  tree.remove(1);
  treeSanity(tree);

  std::cout << "re-inserrting 1" << std::endl;
  tree.insert(1,1);
  treeSanity(tree);

  std::cout << "removing 2" << std::endl;
  tree.remove(2);
  treeSanity(tree);

  std::cout << "re-inserting 0" << std::endl;
  tree.insert(0,0);
  treeSanity(tree);

  std::cout << "removing 4" << std::endl;
  tree.remove(4);
  treeSanity(tree);

  std::cout << "re-inserting 4" << std::endl;
  tree.insert(4,4);
  treeSanity(tree);

  std::cout << "re-inserting 1 incorrectly" << std::endl;
  try{
    tree.insert(1,1); 
  }
  catch(std::exception& e){
    std::cout << "successfully blocked" << std::endl;
  }

  std::cout << "removing 1" << std::endl;
  tree.remove(1);
  treeSanity(tree);
}

void AVLBigTree() {
    AVLTree<float, int> tree;
    tree.insert(1, 0);
    tree.insert(2, 0);
    tree.insert(5, 0);
    tree.insert(8, 0);
    tree.insert(7, 0);
    // BF is for root is -1 now

    tree.insert(10, 0); // BF is now -2, child is -1 - RR roll

    tree.insert(4,0);
    tree.insert(0,0);
    tree.insert(6,0);
    tree.insert(3, 0); // LR roll

    tree.insert(5.5, 0);
    tree.insert(6.5, 0);
    tree.insert(5.6, 0);
    tree.insert(5.4, 0);
    tree.insert(5.3, 0); // LL roll

    tree.insert(1.1, 0);
    tree.insert(-1, 0);
    tree.insert(7.5, 0);
    tree.insert(9, 0);
    tree.insert(7.1, 0);
    tree.insert(7.9, 0);
    tree.insert(13, 0);
    tree.insert(7.3, 0);
    tree.insert(7.7, 0);
    tree.insert(8.9, 0);
    tree.insert(7.01, 0);
    tree.insert(7.2, 0); // RL roll

    // output of print should be:
    // in-order:
    // -1 0 1 1.1 2 3 4 5 5.3 5.4 5.5 5.6 6 6.5 7 7.01 7.1 7.2 7.3 7.5 7.7 7.9 8 8.9 9 10 13
    // pre-order:
    // 5 2 1 0 -1 1.1 4 3 7.5 7 5.5 5.4 5.3 6 5.6 6.5 7.1 7.01 7.3 7.2 8 7.9 7.7 10 9 8.9 13
    treeSanity(tree);

    //remove test

    tree.remove(1.1);
    treeSanity(tree);

    try{
      tree.remove(0.1);
    }
    catch (std::exception& e){
      std::cout << "not removing what isnt there" << std::endl;
    }

    tree.remove(7.01);
    treeSanity(tree);
}
int main(){
 AVLTreeRollTest();
 //AVLBigTree();

 return 0;
}
