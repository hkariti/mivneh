#ifndef UNION_FIND_H
#define UNION_FIND_H


#include <iostream>
#include <exception>

static const int not_there = -1;

template <class Value>
class UnionFind {

private:
  int size;
  Value** values;
  int* parents;
  int* number_of_sons;


public:

  class NoSuchTeam : public std::exception {};

  UnionFind(const int n) : size(n + 1){
    values = new Value[size];
    parents = new int[size];
    number_of_sons = new int[size];

    for(int i = 0; i < size ; i++)
      {
        *(values + i) = new Value;
        *(parents + i) = not_there;
        *(number_of_sons + i) = 1;
      }

  }

  ~UnionFind() {
    for(int i = 0 ; i < size; i++){
      delete *(values + i);
    }
    delete [] values;
    delete [] parents;
    delete [] number_of_sons;
  }

  int join(int i, int j) {
    if(i < 0 || j < 0 || i > size || j > size){
      throw NoSuchTeam();
    }
    if(*(number_of_sons + i) >= *(number_of_sons +j)) {
      *(number_of_sons + i) += *(number_of_sons +j);
      *(number_of_sons + j) = not_there;
      *(parents + j) = i;
      return i;
    }
    else{
      *(number_of_sons + j) += *(number_of_sons + i);
      *(number_of_sons + i) = not_there;
      *(parents + i) = j;
      return j;
    }
  }

  Value find(int i){
    if(i < 0 || i > size){
      throw NoSuchTeam();
    }
    int current = i;
    int parent;
    while(*(parents + current) != not_there){
      current = *(parents + current);
    }
    parent = current;
    current = i;
    while(*(parents + current) != parent){
      int temp = current;
      current = *(parents + current);
      *(parents + temp) = parent;
    }

    return parent;
  }







};




#endif
