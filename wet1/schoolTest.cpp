#include "school.h"
#include <assert.h>

void schoolTest(){
  School Technion;

  //adding students

  assert(Technion.addStudent(1,1,10) == SUCCESS);
  assert(Technion.addStudent(2,1,100) == SUCCESS);

  //invalid arguments
  assert(Technion.addStudent(0, 1, 10) == INVALID_INPUT);
  assert(Technion.addStudent(11,10,0) == INVALID_INPUT);
  assert(Technion.addStudent(1,-1,1) == INVALID_INPUT);

  //student already exists
  assert(Technion.addStudent(1,2,20) == FAILURE);

  //find most powerful student so far in the whole system

  int id = 0;
  assert(Technion.getMostPowerful(-1, &id) == SUCCESS);
  assert(id == 2);

  //invalid argument
  assert(Technion.getMostPowerful(0, &id) == INVALID_INPUT);
  assert(Technion.getMostPowerful(-1, NULL) == INVALID_INPUT);

  //invalid team
  assert(Technion.getMostPowerful(1, &id) == FAILURE);

  //removing

  //remove existing student
  assert(Technion.removeStudent(2) == SUCCESS);
  assert(Technion.getMostPowerful(-1, &id) == SUCCESS);
assert(id == 1);

  //remove non-exsitant student
  assert(Technion.removeStudent(2) == FAILURE);

  //invalid argument for removeStudent
  assert(Technion.removeStudent(0) == INVALID_INPUT);

  assert(Technion.removeStudent(1) == SUCCESS);

  //building system
  Technion.addStudent(1,1,10);
  Technion.addStudent(2,2,20);
  Technion.addStudent(3,3,30);

  //check if the most powerful student in the system updates when adding new students
  Technion.getMostPowerful(-1, &id);
  assert(id == 3);

  //adding team

  assert(Technion.addTeam(1) == SUCCESS);
  //invalid argument for addTeam
  assert(Technion.addTeam(0) == INVALID_INPUT);
  //insert team that already exists
  assert(Technion.addTeam(1) == FAILURE);

  //moving a student into teams

  //invalid argument
  assert(Technion.moveStudentToTeam(0,1) == INVALID_INPUT);
  assert(Technion.moveStudentToTeam(1,0) == INVALID_INPUT);
  //student or team ID doesn't exist
  assert(Technion.moveStudentToTeam(4,1) ==  FAILURE);
  assert(Technion.moveStudentToTeam(1,2) == FAILURE);
  //correct use
  assert(Technion.moveStudentToTeam(1,1) == SUCCESS);

  //get most powerful in team

  Technion.getMostPowerful(-1,&id);
  assert(id == 3);
  assert(Technion.getMostPowerful(1,&id) == SUCCESS);
  assert(id == 1);

  //invalid arguments
  assert(Technion.getMostPowerful(2,&id) == FAILURE);

  //adding a new student to a team that is to become the most powerful student
  Technion.moveStudentToTeam(3,1);
  Technion.getMostPowerful(1,&id);
  assert(id == 3);

  //remove the most powerful student in the system and in a given team
  Technion.removeStudent(3);
  Technion.getMostPowerful(1,&id);
  assert(id == 1);
  Technion.getMostPowerful(-1, &id);
  assert(id == 2);

  //getAllStudentsByPower
  Technion.addStudent(3,3,30);
  Technion.moveStudentToTeam(3,1);
  Technion.addStudent(4,4,40);

  int length = 0;
  int* students;
  //check getting students from the whole system
  assert(Technion.getAllStudentsByPower(-1, &students, &length) == SUCCESS);
  assert(length == 4);
  assert(*students == 4);
  assert(*(students + 1) == 3);
  assert(*(students + 2) == 2);
  assert(*(students + 3) == 1);
  delete [] students;

  //check getting students from a certian team
  Technion.addStudent(5,4,40);
  Technion.addTeam(2);
  Technion.moveStudentToTeam(4,2);
  Technion.moveStudentToTeam(5,2);
  assert(Technion.getAllStudentsByPower(2, &students, &length) == SUCCESS);
  assert(length == 2);
  assert(*students == 4);
  assert(*(students + 1) == 5);
  delete [] students;

  //check moving student from team to team
  Technion.moveStudentToTeam(4,1);
  Technion.getAllStudentsByPower(2,&students, &length);
  Technion.getMostPowerful(2, &id);
  assert(id == 5);
  assert(length == 1);
assert(*students == 5);
  delete[] students;
  Technion.getAllStudentsByPower(1, &students, &length);
  assert(length == 3);
assert(*students == 4);
assert(*(students + 1) == 3);
assert(*(students +2) == 1);
  delete [] students;

  //checking invalid input for getAllStudentsByPower
  assert(Technion.getAllStudentsByPower(0, &students, &length) == INVALID_INPUT);
  assert(Technion.getAllStudentsByPower(-1, NULL, &length) == INVALID_INPUT);
  assert(Technion.getAllStudentsByPower(-1, &students, NULL) == INVALID_INPUT);

  //checking increaseLevel
  //invalid input
  assert(Technion.increaseLevel(-1, 1) == INVALID_INPUT);
  assert(Technion.increaseLevel(1, 0) == INVALID_INPUT);

//update a grade with one person  
  assert(Technion.increaseLevel(3, 20) == SUCCESS);
  assert(Technion.getMostPowerful(-1, &id) == SUCCESS);
  assert(id == 3);
  assert(Technion.getMostPowerful(1, &id) == SUCCESS);
  assert(id == 3);

//update a grade with 1 person moving to not most powerful
  assert(Technion.increaseLevel(2,20) == SUCCESS);
  assert(Technion.getMostPowerful(-1, &id) == SUCCESS);
  assert(id == 3);
  assert(Technion.getAllStudentsByPower(-1, &students, &length) == SUCCESS);
  assert(length == 5);
  assert(*(students + 1) == 2);
  delete [] students;
  assert(Technion.getAllStudentsByPower(1, &students, &length) == SUCCESS);
  assert(length == 3);
  assert(*(students + 1) == 4);
  delete [] students;

//update a grade with 2 students
  assert(Technion.increaseLevel(4,5) == SUCCESS);
  assert(Technion.getAllStudentsByPower(1, &students, &length) == SUCCESS);
  assert(*(students + 1) == 4);
  delete [] students;
  assert(Technion.getAllStudentsByPower(-1, &students, &length) == SUCCESS);
  assert(*(students + 1) == 4);
  assert(*(students + 2) == 5);
delete [] students;

//update a grade with no students
  assert(Technion.increaseLevel(10, 10) == SUCCESS);

  std::cout << "~~~~~~~~~~WOO_HOO~~~~~~~~~~" << std::endl;
}

void schoolSmallRemove(){
School technion;

technion.addStudent(1,1,10);
technion.addStudent(2,2,20);
technion.addStudent(3,3,30);

technion.addTeam(1);
technion.addTeam(2);

technion.moveStudentToTeam(1,1);
technion.moveStudentToTeam(2,1);
technion.moveStudentToTeam(1,2);

int* students;
int length;
technion.getAllStudentsByPower(1, &students, &length);
assert(length == 1);
delete[] students;
}

int main(){
//schoolSmallRemove();  
schoolTest();
  return 0;
}




