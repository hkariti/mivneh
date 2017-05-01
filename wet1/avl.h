#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <exception>
#include <cmath>

template <class Key, class Value>
class AVLTree {

public:
  class Node;

public:
  /*
    Class assumes the key of the tree has overloaded operators: >,<,==,!=
  */
  class Iterator{
  private:
    Node* current;

  public:
    Iterator(Node* node) : current(node) {};
    Key& operator*() const {
      return *(current->key);
    };
    Iterator& operator++() {
      Iterator copy(this);
      if (current->right != NULL) {
        current = current->right;
      } else {
        Node* previous = current;
        current = current->parent;
        while (current->right == previous) {
          previous = current;
          current = current->parent;
          if (current == NULL) break;
        }
      }
      return copy;
    }
    Iterator& operator--() {
      Iterator copy(this);
      if (current->left != NULL) {
        current = current->left;
      } else {
        Node* previous = current;
        current = current->parent;
        while (current->left == previous) {
          previous = current;
          current = current->parent;
          if (current == NULL) break;
        }
      }
      return copy;
    }
    bool operator==(const Iterator& second) const {
      return current == second.current;
    }
    bool operator!=(const Iterator& second) const {
      return !(this == second);
    }
    Value& value() const {
      return *(current->value);
    }
    Iterator left() const {
      return Iterator(current->left);
    }
    Iterator right() const {
      return Iterator(current->right);
    }
    void repalceWith(const Key& key, const Value& value) {
      current->key = key;
      current->value = value;
    }
  };

public:
  class Node {
  public:
    friend void Iterator::repalceWith(const Key& key, const Value& value);
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


    Node(const Key& key, const Value& value, Node* parent=NULL): left(NULL), right(NULL), BF(0), hightRight(0), hightLeft(0),hight(1), parent(parent) {
      this->key = new Key(key);
      this->value = new Value(value);
    }
  };

  class NotFound : public std::exception {};
  class isEmpty : public std::exception {};
  class AlreadyThere : public std::exception {};

  Node* head;

  AVLTree(const AVLTree& tree);
  static void rollRR(Node* top) {
    Node* second = top->right;
    top->right = second->left;
    second->parent = top-> parent;

    // update parent of the top node
    if(top->parent != NULL) {
      if((top->parent)->right == top) {
        (top->parent)->right = second;
      }
      else{
        (top->parent)->left = second;
      }
    }
    top->parent = second;

    //update tree hight and BF
    updateHightAndBF(top);
    updateHightAndBF(second);
  }

  static void rollLL(Node* top) {
    Node* second = top->left;
    top->left = second->right;
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
    top->parent = second;

    //update tree hight and BF
    updateHightAndBF(top);
    updateHightAndBF(second);
  }

  static void rollRL(Node* top) {
    rollLL(top->right);
    rollRR(top);
  }
  static void rollLR(Node* top) {
    rollRR(top->left);
    rollLL(top);
  }

  static void updateHightAndBF(Node* top) {
    int newLeftHight;
    int newRightHight;
    if(top->left == NULL) {
      newLeftHight = 0;
    }
    else{
      newLeftHight = (top->left)->hight + 1;
    }
    if(top->right == NULL) {
      newRightHight = 0;
    }
    else{
      newRightHight = (top->right)->hight + 1;
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

  //can only receive a node that has a two sons
  static void balance(Node* current) {
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

  //debug functions
  void checkBF(Node* base) const {
    if (base->BF > 1 || base->BF < -1) {
      std::cout << "OH NOES! " << base->key << " has BF of " << base->BF << std::endl;
      throw std::exception(base->key);
    }

    checkBF(base->left);
    checkBF(base->right);
  }

  void checkOrder() const {
    Iterator it(first());
    Key previous = *it;
    it++;
    for (Key current=*it; it != end(); it++) {
      if (current < previous) {
        std::cout << "OH NOES! " << current << " < " << previous << " but is sorted as >!" << std::endl;
        throw std::exception(std::pair<Key, Key>(current, previous));
      }
    }
  }

public:
AVLTree() {
  head = NULL;
}
  ~AVLTree(){
    delete head;
  }

  void printInOrder(const Node* node) const {
    if (!node) return;;
    printInOrder(node->left);
    std::cout << *(node->key) << "(" << *(node->value) << ") ";
    printInOrder(node->right);
  }
  void printPostOrder(const Node* node) const {
    if (!node) return;;
    printPostOrder(node->left);
    printPostOrder(node->right);
    std::cout << *(node->key) << " ";
  }
  void print() const {
    std::cout << "in-order:" << std::endl;
    printInOrder(head);
    std::cout << std::endl;
    std::cout << "post-order:" << std::endl;
    printPostOrder(head);
    std::cout << std::endl;
  }

Value& find(const Key& key) const{// may not be const
  Iterator it = first();
  while(it != end()) {
    if(key > *it) {
      it = it.right();
    }
    if(key < *it) {
      it = it.left;
    }
    return it.value;
  }
  throw NotFound();
}



void insert(const Key& key, const Value& value)
{
  std::cout << "inserting key " << key << " value " << value << std::endl;
  if(head == NULL) {
    Node* node = new Node(key, value);
    head = node;
    return;
  }
  Node* current = head;
  while(*(current->key) != key) {
    if(*(current->key) > key) {
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

void remove(const Key& key) {
  if(head == NULL) {
    throw isEmpty();
  }
  //makes sure the key exists
  find(key);

  //find the node that is to be removed
  Node* current = head;
  while(current->key != key) {
    if(current->key > key) {
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
    Key tempKey = next->key;
    next->key = current->key;
    current->key = tempKey;
    Value tempValue = next->value;
    next->value = current->value;
    current->value = tempValue;
    current = next;
  }

  // Node has zero or one sons (or was made to be like that previously)
  Node* parent = current->parent;
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
    }
    else{
      parent->right = current->right;
    }
  }
  else if(current->left != NULL && current->right == NULL) {
    if(parent->left == current) {
      parent->left = current->left;
    }
    else{
      parent->right = current->left;
    }
  }

  delete current;
  balance(parent);
}

  Iterator root() const{
    return Iterator(head);
  }

Iterator first() const{
  Node current = head;
  while(current->left != NULL) {
    current = current->left;
  }
  Iterator it(current);
  return it;
}

Iterator last() const{
  Node current = head;
  while(current->right != NULL) {
    current = current->right;
  }
  return Iterator(current);
}

Iterator end() const{
  return Iterator(NULL);
}

};
#endif
