#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <exception>

template <class Key, class Value>
class AVLTree {

private:
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

private:
  class Node {
  public:
    friend void Iterator::repalceWith(const Key& key, const Value& value);
    ~Node() {
      delete left;
      delete right;
    }
    Key* key;
    Value* value;
    Node* parent;
    Node* left;
    Node* right;
    int BF;
    int hightRight;
    int hightLeft;
    int hight;


    Node(const Key& key, const Value& value, const Node* parent=NULL): key(key), value(value), left(NULL), right(NULL), BF(0), hightRight(0), hightLeft(0), parent(parent){};
  };

  class NotFound : public std::exception {};
  class isEmpty : public std::exception {};

  Node* head;

  AVLTree(const AVLTree& tree);
  static void rollRR(Node* top){
    Node* second = top->right;
    top->right = second->left;
    second->parent = top-> parent;

    // update parent of the top node
    if(top->parent != NULL){
      if((top->parent)->right == top){
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

  static void rollLL(Node* top){
    Node* second = top->left;
    top->left = second->right;
    second->parent = top->parent;

    // update parent of the top node
    if(top->parent != NULL){
      if((top->parent)->right == top){
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

  static void rollRL(Node* top){
    rollLL(top->right);
    rollRR(top);
  }
  static void rollLR(Node* top){
    rollRR(top->left);
    rollLL(top);
  }

  static void updateHightAndBF(Node* top){
    int newLeftHight;
    int newRightHight;
    if(top->left == NULL){
      newLeftHight = 0;
    }
    else{
      newLeftHight = (top->left)->hight;
    }
    if(top->right == NULL){
      newRightHight = 0;
    }
    else{
      newRightHight = (top->right)->hight;
    }
    if(newRightHight > newLeftHight){
      top->hight = newRightHight;
    }
    else{
      top->hight = newLeftHight;
    }
    top->hightLeft = newLeftHight;
    top->hightRight = newRightHight;
    top->BF = top->hightLeft - top->hightRight;
  }

  //can only receive a node that has a two sons
  static void balance(Node* current){
  if(current->BF == 2){
    if((current->left)->BF == -1){
      rollLR(current);
    }
  }
  if(current->BF == 2){
    if((current->left)->BF >= 0){
      rollLL(current);
    }
  }
  if(current->BF == -2){
    if((current->right)->BF <= 0){
      rollRR(current);
    }
  }
  if(current->BF == -2){
    if((current->right)->BF == 1){
      rollRL(current);
    }
  }
  }

  static void searchForInsert(Node* current, const Key& key, const Value& value){
    if(current->left == NULL && current->key > key){
      Node addition = new Node(key, value);
      current->left = &addition;
      addition->parent = &current;
      current->hightLeft++;
      if(current->hightLeft > current->hight){
        current->hight = current->hightLeft;
      }
      current->BF++;
      return;
    }
    if(current->right == NULL && current->key < key){
      Node addition = new Node(key, value);
      current->right = &addition;
      addition->parent = &current;
      current->hightRight++;
      if(current->hightRight > current->hight){
        current->hight = current->hightRight;
      }
      current->BF--;
      return;
    }
    if(current->key > key){
      searchForInsert(current->left, key, value);
    }
    searchForInsert(current->right, key, value);

    balance(current);
    return;

  }

  static void searchForRemove(Node* current, const Key& key){
    if(current->key == key){
      //no sons
      if(current->left == NULL && current->right == NULL){
        Node* parent = current->parent;
        if(parent->left == current){
          parent->left = NULL;
        }
        else{
          parent->right = NULL;
        }
        delete current;
        return;
      }
      //one son
      if(current->left == NULL && current->right != NULL){
        Node* parent = current->parent;
        if(parent->left == current){
          parent->left = current->right;
        }
        else{
          parent->right = current->right;
        }
        return;
      }
      if(current->left != NULL && current->right == NULL){
        Node* parent = current->parent;
        if(parent->left == current){
          parent->left = current->left;
        }
        else{
          parent->right = current->left;
        }
        return;
      }
      Node* next = current->right;
      while(next->left != NULL){
        next = next->left;
      }
      Key tempKey = next->key;
      next->key = current->key;
      current->key = tempKey;
      Value tempValue = next->value;
      next->value = current->value;
      current->value = tempValue;

      
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
  AVLTree(){
    head = NULL;
  }
  ~AVLTree();

  Value& find(const Key& key) const{// may not be const
    Iterator it = first();
    while(it != end()){
      if(key > *it){
        it = it.right();
      }
      if(key < *it){
        it = it.left;
      }
      return it.value;
    }
    throw NotFound();
    }



  void insert(const Key& key, const Value& value)
  {
    if(head == NULL){
      head = new Node(key, value);
    }
    searchForInsert(head, key, value);
  }

  void remove(const Key& key){
    if(head == NULL){
      throw isEmpty();
    }
    find(key); // checks that the pair exists, if not will throw an exception
    searchForRemove(head, key, value);
  }

  Iterator first() const{
    Node current = head;
    while(current->left != NULL){
      current = current->left;
    }
    Iterator it(current);
    return it;
  }

  Iterator last() const{
    Node current = head;
    while(current->right != NULL){
      current = current->right;
    }
    return Iterator(current);
  }

  Iterator end() const{
    return Iterator(NULL);
  }

};
#endif
