#ifndef TEAM_H
#define TEAM_H


#include "avl.h"
#include "student.h"
#include "powerIDPair.h"

class Team {
  int id;
  int mostPowerfulStudentId;
  AVLTree<PowerIDPair, Student*> students;

public:
  Team(int id) : id(id), mostPowerfulStudentId(-1), students() {}

  int getMostPowerfulStudent() {
    return mostPowerfulStudentId;
  }

  void addStudent(Student* student);

  void removeStudent(int power, int id);

  void increaseLevel(int grade, int powerIncrase);

  int* getAllStudentsByPower(int* n);
};

#endif
