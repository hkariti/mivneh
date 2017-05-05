#ifndef SCHOOL_H
#define SCHOOL_H

#include "student.h"
#include "team.h"
#include "avl.h"
#include "library1.h"

typedef AVLTree<int, Student*> idTree;
typedef AVLTree<int, Team*> teamTree;


class School {
  idTree students;
  teamTree teams;
  Team globalTeam;

public:
  School() : students(), teams(), globalTeam(-1) {}

  StatusType addStudent(int studentID, int grade, int power) {
    if(studentID <= 0 || power <= 0 || grade < 0){
      return INVALID_INPUT;
    }
    try{
      students.insert(studentID, new Student(studentID, grade, power));
    }
    catch(idTree::AlreadyThere& e){
      return FAILURE;
    }
    catch(std::bad_alloc& e){
      return ALLOCATION_ERROR;
    }
    try {
      globalTeam.addStudent(students.find(studentID));
    }
    catch(std::bad_alloc& e){
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }

  StatusType addTeam(int teamID) {
    if(teamID <= 0){
      return INVALID_INPUT;
    }
    try{
      Team* newTeam = new Team(teamID);
      teams.insert(teamID, newTeam);
    }
    catch(teamTree::AlreadyThere& e){
      return FAILURE;
    }
    catch(std::bad_alloc& e){
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }

  StatusType moveStudentToTeam(int studentID, int teamID) {
    if(studentID <= 0 || teamID <= 0){
      return INVALID_INPUT;
    }
    try{
      students.find(studentID);
      teams.find(teamID);
    }
    catch(idTree::NotFound& e){
      return FAILURE;
    }
    catch(teamTree::NotFound& e){
      return FAILURE;
    }
    catch(idTree::isEmpty& e){
      return FAILURE;
    }
    catch(teamTree::isEmpty& e){
      return FAILURE;
    }

    Student* currentStudent = students.find(studentID);
    Team* prevTeam = currentStudent->getTeam();
    prevTeam->removeStudent(currentStudent->getPower(), studentID);
    currentStudent->updateTeam(*teams.find(teamID));



  }

  StatusType getMostPowerful(int teamID, int* studentID);

  StatusType removeStudent(int studentID);

  StatusType getAllStudentsByPower(int teamID, int** students, int* numOfStudents);

  StatusType increaseLevel(int grade, int powerIncrease);
};
#endif
