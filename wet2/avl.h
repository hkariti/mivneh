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

    //additional fields
    int numberRight;
    int numberLeft;
    int powerRight;
    int powerLeft;


  public:
    Node(Node* parent) : key(NULL), value(NULL), left(NULL), right(NULL), BF(0), hightRight(0), hightLeft(0), parent(parent), numberRight(0), numberLeft(0), powerRight(0), powerLeft(0) {}

    Node(const Key& key, const Value& value, Node* parent=NULL): left(NULL), right(NULL), BF(0), hightRight(0), hightLeft(0),hight(1), parent(parent), numberRight(0), numberLeft(0), powerRight(0), powerLeft(0) {
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
      top->numberLeft = 0;
      top->powerLeft = 0;
    }
    else{
      newLeftHight = (top->left)->hight;
      top->numberLeft = (top->left->numberLeft) + (top->left->numberRight) + 1;
      top->powerLeft = (top->left->powerLeft) + (top->left->powerRight) + *(top->left->key);
    }
    if(top->right == NULL) {
      newRightHight = 0;
      top->numberRight = 0;
      top->powerRight = 0;
    }
    else{
      newRightHight = (top->right)->hight;
      top->numberRight = (top->right->numberLeft) + (top->right->numberRight) + 1;
      top->powerRight = (top->right->powerLeft) + (top->right->powerRight) + *(top->right->key);
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
  class InvalidInput : public std::exception {}; 
  //debug functions

  //checks that all the BF in the tree are allowed
  void checkBFRecurse(Node* base) const {
    if (!base) return;

    if (base->BF > 1 || base->BF < -1) {
std::cout << "BF error" << std::endl;
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
std::cout << "order error" << std::endl;
 throw DebugException();
      }
    }
  }

  //checks that all the parent pointers match the current situation of the tree
  void checkParentsRecurse(Node* current, Node* parent) const {
    if (!current) return;
    if (current->parent != parent) {
std::cout << "parent error" << std::endl;
      throw DebugException();
    }
    checkParentsRecurse(current->left, current);
    checkParentsRecurse(current->right, current);
  }
  void checkParents() const {
    checkParentsRecurse(head, NULL);
  }

  void checkRankRecurse(Node* current){
    if(!current) return;
    if(current->left == NULL){
      if(current->numberLeft != 0){
        std::cout << "there are no left nodes but it thinks there are " << current->numberLeft << " nodes" << std::endl;
        throw DebugException();
      }
      if(current->powerLeft != 0){
        std::cout << "there are no left nodes but it thinks there is a sum of " << current->powerLeft << " power" << std::endl;
        throw DebugException();
      }
    }
    else{
      if(current->numberLeft != current->left->numberLeft + current->left->numberRight + 1){
        std::cout << "there are nodes to the left, but the numbers dont agree"  << std::endl;
        throw DebugException();
      }
      if(current->powerLeft != current->left->powerRight + current->left->powerLeft + *(current->left->key)){
        std::cout << "there are nodes to the right but the power sums dont agree" << std::endl;
        throw DebugException();
      }
    }
    if(current->right == NULL){
      if(current->numberRight != 0){
        std::cout << "there are no right nodes but it thinks there are " << current->numberRight << " nodes" << std::endl;
        throw DebugException();
      }
      if(current->powerRight != 0){
        std::cout << "there are no right nodes but it thinks there is a sum of " << current->powerRight << " power" << std::endl;
      }
    }
    else{
      if(current->numberRight != current->right->numberLeft + current->right->numberRight + 1){
        std::cout << "there are nodes to the right but the number dont agree" << std::endl;
        throw DebugException();
      }
      if(current->powerRight != current->right->powerRight + current->right->powerLeft + *(current->right->key)){
        std::cout << "there are nodes to the right but the power sums dont agree" << std::endl;
        throw DebugException();
      }
    }
    checkRankRecurse(current->left);
    checkRankRecurse(current->right);
  }

  void checkRank(){
    checkRankRecurse(head);
  }

  static void buildEmptyRecursive(Node* head, int n){
    if(n == 1) return;
    head->left = new Node(head);
    head->right = new Node(head);

    buildEmptyRecursive(head->left, n - 1);
    buildEmptyRecursive(head->right, n - 1);
  }

  static int trimDownRecursive(Node* head, int target, int soFar){
    if(soFar == target) return soFar;
    if(head == NULL) return soFar;

    if(head->right == NULL && head->left == NULL){
      if(head->parent->right == head){
        head->parent->right = NULL;
      }
      else{
        head->parent->left = NULL;
      }
      delete head;
      return 1 + soFar;
    }

    int right = trimDownRecursive(head->right, target, soFar);
    if(right == target) return right;
    int left = trimDownRecursive(head->left, target, right);
    return left;
  }

  static Node* buildEmpty(int n){
    int hight = ceil(log2(n + 1));
    if (hight == 0) return NULL;
    Node* head = new Node(NULL);
    buildEmptyRecursive(head, hight);
    Node* current = head;
    while(current->right != NULL){
      current = current->right;
    }
    if(hight > 1){
    trimDownRecursive(head, pow(2,hight) - 1 - n, 0);
    }
    return head;
  }


  static int updateHightAndBFRecursive(Node* head){
    if(head == NULL) return 0;

    head->hightLeft = updateHightAndBFRecursive(head->left);
    head->hightRight = updateHightAndBFRecursive(head->right);
    if(head->hightRight > head->hightLeft){
      head->hight = head->hightRight + 1;
    }
    else{
      head->hight = head->hightLeft + 1;
    }
    head->BF = head->hightLeft - head->hightRight;
    return head->hight;
  }

  static int updateNumbersRecursive(Node* head){
    if(head == NULL) return 0;

    head->numberLeft = updateNumbersRecursive(head->left);
    head->numberRight = updateNumbersRecursive(head->right);
    return head->numberRight + head->numberLeft + 1;
  }

  static int updatePowerRecursive(Node* head){
    if(head == NULL) return 0;
    head->powerLeft = updatePowerRecursive(head->left);
    head->powerRight = updatePowerRecursive(head->right);
    return head->powerLeft + head->powerRight + *(head->key);
  }

  void updateEverything(Node* head){
    updateHightAndBFRecursive(head);
    updateNumbersRecursive(head);
    updatePowerRecursive(head);
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
std::cout << " " << *node->key << " ";
    printInOrder(node->right);
  }

  // prints the tree according to preoder walk through
  void printPreOrder(const Node* node) const {
    if (!node) return;;
std::cout << " " << *node->key << " ";
printPreOrder(node->left);
    printPreOrder(node->right);
  }

  void print() const {
if(head == NULL) {
std::cout << "no tree to print" << std::endl;
}
printInOrder(head);
std::cout << std::endl;
    printPreOrder(head);
std::cout << std::endl;
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

  int findSumOfTopX(int x){
    if(x <= 0){
      throw InvalidInput();
    }

    int people = 0;
    int powerSum = 0;
    Node* current = head;

    if (!current) return 0;
    if(1 + current->numberRight + current->numberLeft <= x){
      return current->powerRight + current->powerLeft + *(current->key);
    }

    while(current != NULL){
      if(people + 1 + current->numberRight > x){
        current = current->right;
      }
      else if(people + 1 + current->numberRight < x){
        people += 1 + current->numberRight;
        powerSum += current->powerRight + *(current->key);
        current = current->left;
      }
      else{
        return powerSum + current->powerRight + *(current->key);
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

    bool isThere = true;
    try{
      this->find(key);
    }
    catch(NotFound& e){
      isThere = false;
    }

    if(isThere){
      throw AlreadyThere();
    }

    Node* current = head;
    while(true) {
      if(*(current->key) < key) {
        if(current->right == NULL) {
          break;
        }
        current->numberRight++;
        current->powerRight = current->powerRight + key;
        current = current->right;
      }
      else{
        if(current->left == NULL) {
          break;
        }
        current->numberLeft++;
        current->powerLeft = current->powerLeft + key;
        current = current->left;
      }
    }

    if(current->left == NULL && *(current->key) > key) {
      Node* addition = new Node(key, value);
      current->left = addition;
      current->numberLeft++;
      current->powerLeft = current->powerLeft + key;
      addition->parent = current;
    }
    if(current->right == NULL && *(current->key) < key) {
      Node* addition = new Node(key, value);
      current->right = addition;
      current->numberRight++;
      current->powerRight = + current->powerRight + key;
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
        current->numberLeft--;
        current->powerLeft = current->powerLeft - key;
        current = current->left;
      }
      else{
        current->numberRight--;
        current->powerRight = current->powerRight - key;
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

      current->numberRight--;
      current->powerRight = current->powerRight - *(next->key);
      Node* fixing = current->right;
      while(fixing->left != next && fixing->left != NULL){
        fixing->numberLeft--;
        fixing->powerLeft = fixing->powerLeft - *(next->key);
        fixing = fixing->left;
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
head->parent = NULL;
current->right = NULL;
      }
      else{
        head = current->left;
current->left = NULL;
head->parent = NULL;
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

  void treeSanity(){
this->print();
std::cout << "printing done" << std::endl;
//checkOrder();
    checkBF();
    checkParents();
    checkRank();
  }

  void mergeTrees(AVLTree<Key, Value>& tree2){
    int size1, size2;
    if(head != NULL){
      size1 = head->numberRight + head->numberLeft + 1;
    }
    else{
      size1 = 0;
    }
    if(tree2.head != NULL){
      size2 = tree2.head->numberRight + tree2.head->numberLeft + 1;
    }
    else{
      size2 = 0;
    } 
    Node* newTree = buildEmpty(size1 + size2);
    if (!newTree) return;
    Node* current = newTree;
    while(current->left != NULL){
      current = current->left;
    }
    Iterator newIt(current);

    Iterator it1 = this->first();
    Iterator it2 = tree2.first();


    while(it1 != this->end() && it2 != tree2.end()){
      if(*it1 > *it2){
        newIt.replaceWith(*it2, it2.value());
        it2++;
        newIt++;
      }
      else{
        newIt.replaceWith(*it1, it1.value());
        it1++;
        newIt++;
      }
    }

    while(it1 != this->end()){
      newIt.replaceWith(*it1, it1.value());
      it1++;
      newIt++;
    }
    while(it2 != tree2.end()){
      newIt.replaceWith(*it2, it2.value());
      it2++;
      newIt++;
    }
    updateEverything(newTree);
    delete head;
    head = newTree;
  }

};
#endif
