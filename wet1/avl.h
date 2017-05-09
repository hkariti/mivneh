#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <exception>
#include <cmath>

template <class Key, class Value>
class AVLTree {

private:
  class Node;

public:
  /*
    A class used to iterate over a tree
    Class assumes the key of the tree has overloaded operators: >,<,==,!=
  */
  class Iterator{
  private:
    Node* current;

  public:
    //create a new Iterator
    Iterator(Node* node) : current(node) {};

    // returns the key stored in the node the iterator is currently pointing at (the key is stored as a pointer in the tree itself)
    Key& operator*() const {
      return *(current->key);
    };

    // moves the iterator one forward, according to an inorder movement in the tree.
    Iterator operator++(int) {
      Iterator copy(this->current);
      if (current->right != NULL) {
        current = current->right;
        while (current->left != NULL)
            current = current->left;
      } else {
        Node* previous = current;
        current = current->parent;
        while (current != NULL && current->right == previous) {
          previous = current;
          current = current->parent;
        }
      }
      return copy;
    }

    // moves the iterator one backwards, according to an inorder movement in the tree
    Iterator operator--(int) {
      Iterator copy(this->current);
      if (current->left != NULL) {
        current = current->left;
        while (current->right != NULL)
            current = current->right;
      } else {
        Node* previous = current;
        current = current->parent;
        while (current != NULL && current->left == previous) {
          previous = current;
          current = current->parent;
        }
      }
      return copy;
    }

    //comparison operators for Iterators
    bool operator==(const Iterator& second) const {
      return current == second.current;
    }
    bool operator!=(const Iterator& second) const {
      return !(*this == second);
    }


    // returns the value stored in the node the iterator is currently pointing at (the value is stored as a pointer in the tree itself)
    Value& value() const {
      return *(current->value);
    }

    //moves the Iterator to the left son of the current Iterator
    Iterator left() const {
      if(this->current == NULL) return Iterator(NULL);
      return Iterator(current->left);
    }

    //moves the iterator to the right son of the current iterator
    Iterator right() const {
      if(this->current == NULL) return Iterator(NULL);
      return Iterator(current->right);
    }
    //replaces the key and value of the node the iterator is pointing at with the supplied key and value
    void replaceWith(const Key& key, const Value& value) {
      if (!current) throw EndOfTree();
      delete current->key;
      delete current->value;
      this->current->key = new Key(key);
      this->current->value = new Value(value);
    }
  };

  private:
  class Node {
    //allows the iterator replaceWith function to access the nodes private fields
    friend void Iterator::replaceWith(const Key& key, const Value& value);

  public:
    //d'tor that releases the node itself and all the nodes connected to it via left\right.
    ~Node() {
      delete key;
      delete value;
      delete left;
      delete right;
    }

    Key* key;
    Value* value;
    Node* left;
    Node* right;
    int BF;
    int hightRight;
    int hightLeft;
    int hight;
    Node* parent;

  public:
    Node(const Key& key, const Value& value, Node* parent=NULL): left(NULL), right(NULL), BF(0), hightRight(0), hightLeft(0),hight(1), parent(parent) {
      this->key = new Key(key);
      this->value = new Value(value);
    }
  };
  Node* head;


  AVLTree(const AVLTree& tree);


  void rollRR(Node* top) {
    //switch between the two nodes
    Node* second = top->right;
    top->right = second->left;
    if (top->right) {
      top->right->parent = top;
    }
    second->left = top;
    second->parent = top->parent;

    // update parent of the top node
    if(top->parent != NULL) {
      if((top->parent)->right == top) {
        (top->parent)->right = second;
      }
      else{
        (top->parent)->left = second;
      }
    }
    else {
      this->head = second;
    }
    top->parent = second;

    //update tree hight and BF
    updateHightAndBF(top);
    updateHightAndBF(second);
  }

  void rollLL(Node* top) {
    //switch between the two nodes
    Node* second = top->left;
    top->left = second->right;
    if (top->left) {
      top->left->parent = top;
    }
    second->right = top;
    second->parent = top->parent;

    // update parent of the top node
    if(top->parent != NULL) {
      if((top->parent)->right == top) {
        (top->parent)->right = second;
      }
      else{
        (top->parent)->left = second;
      }
    }
    else{
      this->head = second;
    }
    top->parent = second;

    //update tree hight and BF
    updateHightAndBF(top);
    updateHightAndBF(second);
  }

  void rollRL(Node* top) {
    rollLL(top->right);
    rollRR(top);
  }

  void rollLR(Node* top) {
    rollRR(top->left);
    rollLL(top);
  }

  //updates the hight, hightLeft, hightRight and dBF of the given node.
  static void updateHightAndBF(Node* top) {
    int newLeftHight;
    int newRightHight;
    if(top->left == NULL) {
      newLeftHight = 0;
    }
    else{
      newLeftHight = (top->left)->hight;
    }
    if(top->right == NULL) {
      newRightHight = 0;
    }
    else{
      newRightHight = (top->right)->hight;
    }
    if(newRightHight > newLeftHight) {
      top->hight = newRightHight + 1;
    }
    else{
      top->hight = newLeftHight + 1;
    }
    top->hightLeft = newLeftHight;
    top->hightRight = newRightHight;
    top->BF = top->hightLeft - top->hightRight;
  }

  // makes sure the tree is balanced, starting at the given node and moving up
  void balance(Node* current) {
    while(current != NULL) {
      updateHightAndBF(current);
      if(current->BF == 2) {
        if((current->left)->BF == -1) {
          rollLR(current);
        }
        else {
          rollLL(current);
        }
      }
      if(current->BF == -2) {
        if((current->right)->BF <= 0) {
          rollRR(current);
        }
        else {
          rollRL(current);
        }
      }
      current = current->parent;
    }
  }

public:
  class NotFound : public std::exception {};
  class isEmpty : public std::exception {};
  class EndOfTree : public std::exception {};
  class AlreadyThere : public std::exception {};
  class DebugException : public std::exception {};
  //debug functions

  //checks that all the BF in the tree are allowed
  void checkBFRecurse(Node* base) const {
    if (!base) return;

    if (base->BF > 1 || base->BF < -1) {
      throw DebugException();
    }

    checkBFRecurse(base->left);
    checkBFRecurse(base->right);
  }

  void checkBF() const {
    checkBFRecurse(head);
  }

  //checks that the tree is correctly ordered
  void checkOrder() const {
    Iterator it(first());
    Key previous = *it;
    it++;
    for (Key current=*it; it != end(); it++) {
      if (current < previous) {
        throw DebugException();
      }
    }
  }

  //checks that all the parent pointers match the current situation of the tree
  void checkParentsRecurse(Node* current, Node* parent) const {
    if (!current) return;
    if (current->parent != parent) {
      throw DebugException();
    }
    checkParentsRecurse(current->left, current);
    checkParentsRecurse(current->right, current);
  }
  void checkParents() const {
    checkParentsRecurse(head, NULL);
  }

public:
  AVLTree() {
    head = NULL;
  }
  ~AVLTree(){
    delete head;
  }

  //prints the tree according to inorder walk through
  void printInOrder(const Node* node) const {
    if (!node) return;;
    printInOrder(node->left);
    printInOrder(node->right);
  }

  // prints the tree according to preoder walk through
  void printPreOrder(const Node* node) const {
    if (!node) return;;
    printPreOrder(node->left);
    printPreOrder(node->right);
  }
  void print() const {
    printInOrder(head);
    printPreOrder(head);
  }

  // finds a given key in the tree and returns its value. if the key does not exsist throws NotFound
  Value& find(const Key& key) const{// may not be const
    Iterator it = root();
    while(it != end()) {
      if(key == *it){
        return it.value();
      }
      if(key > *it) {
        it = it.right();
      }
      else if(key < *it) {
        it = it.left();
      }
      else {
        return it.value();
      }
    }
    throw NotFound();
  }

  // inserts a key and value into the tree. if the key already exists throws AlreadyThere
  void insert(const Key& key, const Value& value)
  {
    if(head == NULL) {
      Node* node = new Node(key, value);
      head = node;
      return;
    }
    Node* current = head;
    while(*(current->key) != key) {
      if(*(current->key) < key) {
        if(current->right == NULL) {
          break;
        }
        current = current->right;
      }
      else{
        if(current->left == NULL) {
          break;
        }
        current = current->left;
      }
    }
    if(*(current->key) == key) {
      throw AlreadyThere();
    }

    if(current->left == NULL && *(current->key) > key) {
      Node* addition = new Node(key, value);
      current->left = addition;
      addition->parent = current;
    }
    if(current->right == NULL && *(current->key) < key) {
      Node* addition = new Node(key, value);
      current->right = addition;
      addition->parent = current;
    }

    balance(current);
  }

  // removes the given key from the tree, if it doesn't exist throws NotFound, if tree is empty throws isEmpty
    void remove(const Key& key) {
    if(head == NULL) {
      throw isEmpty();
    }
    //makes sure the key exists
      this->find(key);

    //find the node that is to be removed
    Node* current = head;
    while(*(current->key) != key) {
      if(*(current->key) > key) {
        current = current->left;
      }
      else{
        current = current->right;
      }
    }
    // Node to be removed has two sons.
    // We switch it with the next node according to in-order,
    // then handle it like a node with zero or one sons
    if(current->left != NULL && current->right != NULL) {
      Node* next = current->right;
      // Find the next node
      while(next->left != NULL) {
        next = next->left;
      }
      // Switch
      Key* tempKey = next->key;
      next->key = current->key;
      current->key = tempKey;
      Value* tempValue = next->value;
      next->value = current->value;
      current->value = tempValue;
      current = next;
    }

    // Node has zero or one sons (or was made to be like that previously)
    Node* parent = current->parent;
    if(parent == NULL) {
      if(current->left == NULL && current->right == NULL){
        head = NULL;
      }
      else if(current->left == NULL && current->right != NULL){
        head = current->right;
      }
      else{
        head = current->left;
      }
    }
    else{
      // Zero sons
      if(current->left == NULL && current->right == NULL) {
        if(parent->left == current) {
          parent->left = NULL;
        }
        else{
          parent->right = NULL;
        }
      }
      // One son
      else if(current->left == NULL && current->right != NULL) {
        if(parent->left == current) {
          parent->left = current->right;
          parent->left->parent = parent;
          current->right = NULL;
        }
        else{
          parent->right = current->right;
          parent->right->parent = parent;
          current->right = NULL;
        }
      }
      else if(current->left != NULL && current->right == NULL) {
        if(parent->left == current) {
          parent->left = current->left;
          current->left = NULL;
          parent->left->parent = parent;
        }
        else{
          parent->right = current->left;
          current->left = NULL;
          parent->right->parent = parent;
        }
      }
    }
    delete current;
    balance(parent);
  }

  //returns an iterator that points at the root of the tree
  Iterator root() const{
    return Iterator(head);
  }

  //returns an iterator that points at the smallest value in the tree
  Iterator first() const{
    Node* current = head;
    if(current == NULL){
      return Iterator(NULL);
    }
    while(current->left != NULL) {
      current = current->left;
    }
    Iterator it(current);
    return it;
  }

  //returns an iterator that points at the largest value in the tree
  Iterator last() const{
    Node* current = head;
    if(current == NULL){
      return Iterator(NULL);
    }
    while(current->right != NULL) {
      current = current->right;
    }
    return Iterator(current);
  }

  Iterator end() const{
    return Iterator(NULL);
  }

  treeSanity(){
    checkOrder();
    checkBF();
    checkParents();
  }

};
#endif
