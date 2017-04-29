#ifndef AVL_H
#define AVL_H

#include <iostream>


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
    Value& operator*();
    Iterator operator++();
    Iterator operator--();
    bool operator==(Iterator& second);
    bool operator!=(Iterator& second);
    void repalceWith(Key& key, Value& value);
  };

private:
  class Node {
  private:
    friend void Iterator::repalceWith(Key& key, Value& value);
    Key* key;
    Value* value;
    Node* parent;
    Node* left;
    Node* right;
    int BF;
    int hightRight;
    int hightLeft;
  public:

    Node(Key& key, Value& value, Node* parent=NULL): key(key), value(value), left(NULL), right(NULL), BF(0), hightRight(0), hightLeft(0), parent(parent){};
  };

  Node head;

  AVLTree(AVLTree& tree);
  static void rollRR();
  static void rollLL();
  static void rollRL();
  static void rollLR();
  static void balance();

  //debug functions
  static bool checkBF();
  static bool checkOrder();

public:
  AVLTree();
  ~AVLTree();


  Value& find(Key key);

  void insert(Key& key, Value& value);
  void remove(Key& key, Value& value);

  Iterator first();
  Iterator last();
  Iterator end();

};
#endif
