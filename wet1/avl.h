#ifndef AVL_H
#define AVL_H

template <class Value> class Node {
  int key;
  Value* value;
  Node* parent;
  Node* left;
  Node* right;

public:
  Node(int key, Value* value): key(key), value(value), parent(nullptr), left(nullptr), right(nullptr) {};
};

template <class Value> class AVLTree {
  Node<Value> head;

};
#endif
