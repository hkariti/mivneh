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
  private:
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
