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
    Value& operator*() const;
    Iterator operator++();
    Iterator operator--();
    bool operator==(const Iterator& second) const;
    bool operator!=(const Iterator& second) const;
    void repalceWith(const Key& key, const Value& value);
  };

private:
  class Node {
  private:
    friend void Iterator::repalceWith(const Key& key, const Value& value);
    Key* key;
    Value* value;
    Node* parent;
    Node* left;
    Node* right;
    int BF;
    int hightRight;
    int hightLeft;
  public:

    Node(const Key& key, const Value& value, const Node* parent=NULL): key(key), value(value), left(NULL), right(NULL), BF(0), hightRight(0), hightLeft(0), parent(parent){};
  };

  Node head;

  AVLTree(const AVLTree& tree);
  static void rollRR();
  static void rollLL();
  static void rollRL();
  static void rollLR();
  static void balance();

  //debug functions
  bool checkBF() const;
  bool checkOrder() const;

public:
  AVLTree();
  ~AVLTree();

  Value& find(const Key& key) const; // may not be const

  void insert(const Key& key, const Value& value);
  void remove(const Key& key, const Value& value);

  Iterator first() const;
  Iterator last() const;
  Iterator end() const;

};
#endif
