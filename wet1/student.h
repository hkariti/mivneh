#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

//#include "team.h"
class Team;

class Student{
  int id;
  const int grade;
  int power;
  Team* team;

public:
  Student(const int& id, const int& grade, const int& power) : id(id), grade(grade), power(power), team(NULL) {}
  ~Student() {}

  const int& getID() const{
    return this->id;
  }
  const int& getGrade() const{
    return this->grade;
  }
  void updatePower(int addition) {
    this->power = this->power + addition;
  }
  const int& getPower() const{
    return power;
  }
  Team* getTeam() const {
    return team;
  }
  void updateTeam(Team& newTeam) {
    this->team = &newTeam;
  }

};
#endif
