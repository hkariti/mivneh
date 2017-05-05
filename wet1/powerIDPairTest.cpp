#include "powerIDPair.h"
#include <iostream>

void PowerIDPairTest(){

  PowerIDPair first(1,1);
  PowerIDPair copy(first);
  if(copy == first){
    std::cout << "copy success" << std::endl;
  }

  PowerIDPair second(1,2);
  if(second == first){
    std::cout << "ABORT (equal)" << std::endl;
  }
  if(first < second){
    std::cout << "ABORT (>)" << std::endl;
  }
  if(second < first){
    std::cout << "success (>)" << std::endl;
  }
  if(first > second) {
    std::cout << "success (<)" << std::endl;
  }
  if(second > first){
    std::cout << "ABORT (<)" << std::endl;
  }

  PowerIDPair third(2,1);
  if(second != third){
    std::cout << "success (!=)" << std::endl;
  }
  if(third == first){
    std::cout << "ABORT (==)" << std::endl;
  }
  if(third < second){
    std::cout << "ABORT (<)" << std::endl;
  }
  if(first > third){
    std::cout << "ABORT (>)" << std::endl;
  }

}


int main(){
  PowerIDPairTest();
  return 0;
}


