#ifndef SCHOOL_H
#define SCHOOL_H

#include "student.h"
#include "team.h"
#include "avl.h"
#include "library1.h"


class School {
  AVLTree<int, Student> students;
  AVLTree<int, Team> teams;
  Team globalTeam;

public:
  School() : students(), teams(), globalTeam(-1) {};

  StatusType addStudent(int studentID, int grade, int power);

  StatusType addTeam(int teamID);

  StatusType moveStudentToTeam(int studentID, int teamID);

  StatusType getMostPowerful(int teamID, int* studentID);

  StatusType removeStudent(int studentID);

  StatusType getAllStudentsByPower(int teamID, int** students, int* numOfStudents);

  StatusType increaseLevel(int grade, int powerIncrease);
};
#endif
