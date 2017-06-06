#include "school.h"
#include <assert.h>


void AddStudentTest(){
  School technion(3);

  // invalid input
  assert(technion.addStudent(0,1,1) == INVALID_INPUT);
  assert(technion.addStudent(1,0,1) == INVALID_INPUT);
  assert(technion.addStudent(1,1,0) == INVALID_INPUT);
  assert(technion.addStudent(1,4,1) == INVALID_INPUT);

  //valid input
  assert(technion.addStudent(1,1,1) == SUCCESS);
  assert(technion.addStudent(2,1,1) == SUCCESS);
  assert(technion.addStudent(3,1,1) == SUCCESS);

  //samae id
  assert(technion.addStudent(1,2,2) == FAILURE);
  assert(technion.addStudent(2,1,1) == FAILURE);
}

void RemoveStudentTest(){
  School technion(3);
  assert(technion.addStudent(1,1,1) == SUCCESS);
  assert(technion.addStudent(2,1,1) == SUCCESS);
  assert(technion.addStudent(3,1,1) == SUCCESS);

  // invalid input
  assert(technion.removeStudent(0) == INVALID_INPUT);

  // doesn't exist
  assert(technion.removeStudent(4) == FAILURE);

  // exists
  assert(technion.removeStudent(1) == SUCCESS);
  assert(technion.addStudent(1,1,1) == SUCCESS);
}

void JoinTeamsAndLeaderTest(){
  School technion(3);
  assert(technion.addStudent(1,1,1) == SUCCESS);
  assert(technion.addStudent(2,1,1) == SUCCESS);
  assert(technion.addStudent(3,1,1) == SUCCESS);
  assert(technion.addStudent(4,3,10) == SUCCESS);

  int leader = 0;

  //invalid input
  assert(technion.joinTeams(0,1) == INVALID_INPUT);
  assert(technion.joinTeams(1,0) == INVALID_INPUT);
  assert(technion.joinTeams(4,1) == INVALID_INPUT);
  assert(technion.joinTeams(1,4) == INVALID_INPUT);
  assert(technion.getStudentTeamLeader(1, NULL) == INVALID_INPUT);
  assert(technion.getStudentTeamLeader(0, &leader) == INVALID_INPUT);

  //no such student
  assert(technion.getStudentTeamLeader(80, &leader) == FAILURE);

  //valid input
  assert(technion.joinTeams(1,2) == SUCCESS);
  assert(technion.getStudentTeamLeader(1,&leader) == SUCCESS);
  assert(leader == 1);
  assert(technion.joinTeams(2,3) == SUCCESS);
  assert(technion.getStudentTeamLeader(1,&leader) == SUCCESS);
  assert(leader == 4);
  assert(technion.addStudent(5,2,100) == SUCCESS);
  assert(technion.getStudentTeamLeader(1, &leader) == SUCCESS);
  assert(leader == 5);
  assert(technion.addStudent(6,1,1) == SUCCESS);
  assert(technion.getStudentTeamLeader(6, &leader) == SUCCESS);
  assert(leader == 5);
}


void FightTest(){
  School technion(3);
  assert(technion.addStudent(1,1,1) == SUCCESS);
  assert(technion.addStudent(2,1,1) == SUCCESS);
  assert(technion.addStudent(3,1,1) == SUCCESS);
  assert(technion.addStudent(4,3,10) == SUCCESS);
  assert(technion.addStudent(5,2,100) == SUCCESS);
  assert(technion.addStudent(6,1,1) == SUCCESS);
  assert(technion.addStudent(7,1,97) == SUCCESS);

  int wins = 0;

  //invalid input
  assert(technion.teamFight(0,1,1) == INVALID_INPUT);
  assert(technion.teamFight(1,0,1) == INVALID_INPUT);
  assert(technion.teamFight(1,1,0) == INVALID_INPUT);
  assert(technion.teamFight(4,1,1) == INVALID_INPUT);
  assert(technion.teamFight(1,4,1) == INVALID_INPUT);
  assert(technion.getNumOfWins(0, &wins) == INVALID_INPUT);
  assert(technion.getNumOfWins(1, &wins) == INVALID_INPUT);


  //valid input
  assert(technion.teamFight(2,1,1) == SUCCESS);
  assert(technion.getNumOfWins(1, &wins) == SUCCESS);
  assert(wins == 0);
  assert(technion.getNumOfWins(2, &wins) == SUCCESS);
  assert(wins == 1);
  assert(technion.teamFight(1,3,1) == SUCCESS);
  assert(technion.getNumOfWins(1, &wins) == SUCCESS);
  assert(wins == 0);
  assert(technion.getNumOfWins(4, &wins) == SUCCESS);
  assert(wins == 1);
  assert(technion.teamFight(1,3,4) == SUCCESS);
  assert(technion.getNumOfWins(1, &wins) == SUCCESS);
  assert(wins == 0);
  assert(technion.getNumOfWins(4, &wins) == SUCCESS);
  assert(wins == 1);
  assert(technion.teamFight(1,3,100) == SUCCESS);
  assert(technion.getNumOfWins(1, &wins) == SUCCESS);
  assert(wins == 1);
  assert(technion.getNumOfWins(4, &wins) == SUCCESS);
  assert(wins == 1);

  assert(technion.joinTeams(1,2) == SUCCESS);
  assert(technion.getNumOfWins(2, &wins) == SUCCESS);
  assert(wins == 2);
  assert(technion.getNumOfWins(1, &wins) == SUCCESS);
  assert(wins == 2);
  assert(technion.joinTeams(2,3) == SUCCESS);
  assert(technion.getNumOfWins(3, &wins) == SUCCESS);
  assert(wins == 3);
  assert(technion.getNumOfWins(1, &wins) == SUCCESS);
  assert(wins == 3);
}

int main(){
  AddStudentTest();
  RemoveStudentTest();
  JoinTeamsAndLeaderTest();
  FightTest();

  return 0;
}
