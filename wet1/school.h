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

    //add student to student tree
    try{
      students.insert(studentID, new Student(studentID, grade, power));
    }
    catch(idTree::AlreadyThere& e){
      return FAILURE;
    }
    catch(std::bad_alloc& e){
      return ALLOCATION_ERROR;
    }

    //add student to the globalTeam
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

    //add team to team tree
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

    //check that the student and the team exist in the system
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

    //remove student from previous team and add to the current team.
    try{
      Student* currentStudent = students.find(studentID);
    Team* prevTeam = currentStudent->getTeam();
    if(prevTeam != NULL){
      prevTeam->removeStudent(currentStudent->getPower(), studentID);
    }
    currentStudent->updateTeam(*teams.find(teamID));
    teams.find(teamID)->addStudent(currentStudent);
    }
    catch(std::bad_alloc& e){
      return ALLOCATION_ERROR;
    }
  }

  StatusType getMostPowerful(int teamID, int* studentID){
    if(teamID == 0 || studentID == NULL){
      return INVALID_INPUT;
    }

  //if we are looking for the most powerful student in the whole system
    if(teamID < 0){
      *studentID = globalTeam.getMostPowerfulStudent();
      return SUCCESS;
    }

  //if we are looking for the most powerful student in a certain team
    else{
      //check that the team exists in the system
      try{
        teams.find(teamID);
      }
      catch(teamTree::NotFound& e){
        return FAILURE;
      }
      catch(teamTree::isEmpty& e){
        return FAILURE;
      }
      *studentID = teams.find(teamID)->getMostPowerfulStudent();
      return SUCCESS;
    }
    }

  StatusType removeStudent(int studentID){
    if(studentID <= 0){
      return INVALID_INPUT;
    }

    //checks that the student exists in the system
    try{
      students.find(studentID);
    }
    catch(idTree::NotFound& e){
      return FAILURE;
    }
    catch(idTree::isEmpty& e){
      return FAILURE;
    }

    //remove the student from his team, from globalTeam and from the id tree
    Student* student = students.find(studentID);
    globalTeam.removeStudent(student->getPower(), studentID);
    if(student->getTeam() != NULL){
      student->getTeam()->removeStudent(student->getPower(), studentID);
    }
    students.remove(studentID);
    delete student;

    return SUCCESS;
  }

  StatusType getAllStudentsByPower(int teamID, int** students, int* numOfStudents){
    if(students == NULL || numOfStudents == NULL ||teamID == 0){
      return INVALID_INPUT;
    }

    //if we are looking for all the students in the system
    if(teamID < 0){
      try{
        *students = globalTeam.getAllStudentsByPower(numOfStudents);
        return SUCCESS;
      }
      catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
      }
    }

    //if we are lookig for all the students in a certian team
    else{
      try{
        teams.find(teamID);
      }
      catch(teamTree::NotFound& e){
        return FAILURE;
      }
      catch(teamTree::isEmpty& e){
        return FAILURE;
      }
      try {
      *students = teams.find(teamID)->getAllStudentsByPower(numOfStudents);
      return SUCCESS;
      }
      catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
      }
    }
  }

StatusType increaseLevel(int grade, int powerIncrease){
  if(grade < 0 || powerIncrease <= 0){
    return INVALID_INPUT;
  }

  try {
    //update only happens in the globalTeam because that is the place where we have pointers to all the students in the system. 
    globalTeam.increaseLevel(grade, powerIncrease);
    //for each team the increase happens with 0 because the students power was already increased in the globalTeam, but we still need to re-arrange them in the teams tree.
    teamTree::Iterator it = teams.first();
  while(it != teams.end()){
    it.value()->increaseLevel(grade, 0);
    it++;
  }
  }
  catch(std::bad_alloc& e){
    return ALLOCATION_ERROR;
  }
  return SUCCESS;
}

~School(){
  //free all of the memory taken up by students
  idTree::Iterator itID = students.first();
  while(itID != students.end()){
    delete itID.value();
    itID++;
  }
  //free all the memory taken up by the teams
  teamTree::Iterator itTeam = teams.first();
  while(itTeam != teams.end()){
    delete itTeam.value();
    itTeam++;
  }
}

};

#endif
