#ifndef TEAM_H
#define TEAM_H

#include <stdlib.h>
#include <exception>
#include "avl.h"
#include "student.h"
#include "powerIDPair.h"

typedef AVLTree<PowerIDPair, Student*> PowerTree;

class Team {
  int mostPowerfulStudentId;
  int wins;
  PowerTree students;

public:
  Team() : mostPowerfulStudentId(-1), wins(0), students() {}

  int getMostPowerfulStudent() {
    return mostPowerfulStudentId;
  }

  int getWins() {
    return wins;
  }

  void addStudent(Student* student) {
    if (!student) throw NullArgument();
    PowerIDPair key(student->getPower(), student->getID());
    students.insert(key, student);
    updateMostPowerfulStudent();
  }

  void removeStudent(int power, int id) {
    PowerIDPair key(power, id);
    students.remove(key);
    updateMostPowerfulStudent();
  }

  void fight(Team& otherTeam, int numOfFighters) {
    int myFightersPower = students.findSumOfTopX(numOfFighters);
    int otherFightersPower = otherTeam.students.findSumOfTopX(numOfFighters);
    if (myFightersPower > otherFightersPower)
      wins++;
    else if (myFightersPower < otherFightersPower)
      otherTeam.wins++;
  }

  void merge(Team& otherTeam) {
    students.mergeTrees(otherTeam.students);
    wins += otherTeam.wins;
    updateMostPowerfulStudent();
  }

  class NullArgument : public std::exception {};

private:
  void updateMostPowerfulStudent() {
      PowerTree::Iterator mostPowerfulStudent = students.last();
      if (mostPowerfulStudent != students.end()) {
          mostPowerfulStudentId = mostPowerfulStudent.value()->getID();
      } else {
          mostPowerfulStudentId = -1;
      }
  }
};

#endif
