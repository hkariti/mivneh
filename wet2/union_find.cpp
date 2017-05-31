#include "union_find.h"
#include <assert.h>

typedef UnionFind<int> Union;

void UnionTest(){
  Union test(6);

  //join test
  std::cout << "join test" << std::endl;
  //invalid input
  try{
    test.join(0, 1);
  }
  catch(Union::NoSuchTeam& e){
    std::cout << "left 0 ok" << std::endl;
  }
  try{
    test.join(1, 0);
  }
  catch(Union::NoSuchTeam& e){
    std::cout << "right 0 ok" << std::endl;
  }
  try{
    test.join(7,1);
  }
  catch(Union::NoSuchTeam& e){
    std::cout << "left size ok" << std::endl;
  }
  try{
    test.join(1,7);
  }
  catch(Union::NoSuchTeam& e){
    std::cout << "right size ok" << std::endl;
  }

  test.print();

  test.join(1,2); //1 should be parent
  test.join(3,4); //3 should be parent
  test.join(2,4); //1 should be parent
  test.print();

  test.join(5,1); //1 should be parent
  test.join(6,4); //1 should be parent
  test.print();

  /*
        1
      2  3  5  6
         4
   */

  //find test
  std::cout << "testing find" << std::endl;
  //invalid input
  try{
    test.find(0);
  }
  catch(Union::NoSuchTeam& e){
    std::cout << "zero fine" << std::endl;
  }
  try{
    test.find(7);
  }
  catch(Union::NoSuchTeam& e){
    std::cout << "large find" << std::endl;
  }

  assert(test.find(5) == 1);
  assert(test.find(1) == 1);
  assert(test.find(4) == 1);
  test.print();

  /*
         1
     2 3 4 5 6
   */

}

int main(){
  UnionTest();
  std::cout << "WOO HOO" << std::endl;
  return 0;
}

