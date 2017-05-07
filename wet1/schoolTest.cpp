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

  int* id;
  assert(Technion.getMostPowerful(-1, id) == SUCCESS);
  assert(*id == 2);

  //invalid argument
  assert(Technion.getMostPowerful(0,id) == INVALID_INPUT);
  assert(Technion.getMostPowerful(-1, NULL) == INVALID_INPUT);

  //invalid team
  assert(Technion.getMostPowerful(1, id) == FAILURE);

  //removing

  //remove existing student
  assert(Technion.removeStudent(2) == SUCCESS);
  assert(Technion.getMostPowerful(-1, id) == SUCCESS);

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
  Technion.getMostPowerful(-1, id);
  assert(*id == 3);

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

  Technion.getMostPowerful(-1,id);
  assert(*id == 3);
  assert(Technion.getMostPowerful(1,id) == SUCCESS);
  assert(*id == 1);

  //invalid arguments
  assert(Technion.getMostPowerful(2,id) == FAILURE);

  //adding a new student to a team that is to become the most powerful student
  Technion.moveStudentToTeam(3,1);
  Technion.getMostPowerful(1,id);
  assert(*id == 3);

  //remove the most powerful student in the system and in a given team
  Technion.removeStudent(3);
  Technion.getMostPowerful(1,id);
  assert(*id == 1);
  Technion.getMostPowerful(-1, id);
  assert(*id == 2);


}

int main(){
  schoolTest();
  return 0;
}




