#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

//#include "team.h"
class Team;

class Student{
  int id;
  int power;
  int teamId;

public:
  Student(const int id, const int power, int teamId) : id(id), power(power), teamId(teamId) {}
  ~Student() {}

  int getID() const{
    return id;
  }
  int getPower() const{
    return power;
  }

  int getTeamId() const {
    return teamId;
  }
};
#endif
