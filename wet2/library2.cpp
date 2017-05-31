#include "library2.h"
#include "school.h"

void* Init(int n) {
  return new School(n);
}

StatusType AddStudent(void *DS, int StudentID, int Team, int Power) {
  return ((School*)DS)->addStudent(StudentID, Team, Power);
}

StatusType RemoveStudent(void *DS, int StudentID) {
  return ((School*)DS)->removeStudent(StudentID);
}

StatusType JoinTeams(void *DS, int Team1, int Team2) {
  return ((School*)DS)->joinTeams(Team1, Team2);
}

StatusType TeamFight(void *DS, int Team1, int Team2, int NumOfFighters) {
  return ((School*)DS)->teamFight(Team1, Team2, NumOfFighters);
}

StatusType GetNumOfWins(void *DS, int Team, int* Wins) {
  return ((School*)DS)->getNumOfWins(Team, Wins);
}

StatusType GetStudentTeamLeader(void *DS, int StudentID, int* Leader) {
  return ((School*)DS)->getStudentTeamLeader(StudentID, Leader);
}

void Quit(void** DS) {
    delete (School*)(*DS);
    *DS = NULL;
}
