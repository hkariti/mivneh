#ifndef TEAM_H
#define TEAM_H

#include <exception>
#include "avl.h"
#include "student.h"
#include "powerIDPair.h"

typedef AVLTree<PowerIDPair, Student*> PowerTree;

class Team {
  int id;
  int mostPowerfulStudentId;
  PowerTree students;

public:
  Team(int id) : id(id), mostPowerfulStudentId(-1), students() {}

  int getID() {
    return id;
  }

  int getMostPowerfulStudent() {
    return mostPowerfulStudentId;
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

  void increaseLevel(int grade, int powerIncrease) {
    // Count the number of students in the requested grade
    int studentsCount = 0;
    for (PowerTree::Iterator it = students.first(); it != students.end(); it++) {
      if (it.value()->getGrade() == grade)
        studentsCount++;
    }
    if (studentsCount == 0) return;
    // Allocate and fill a merge array for them. Also do the powerIncrease here
    Student** studentsToMerge = new Student*[studentsCount];
    int currentMergeStudent = 0;
    for (PowerTree::Iterator it = students.first(); it != students.end(); it++) {
      if (it.value()->getGrade() == grade) {
        studentsToMerge[currentMergeStudent] = it.value();
        studentsToMerge[currentMergeStudent]->updatePower(powerIncrease);
        currentMergeStudent++;
      }
    }
    // Merge tree and array according to tree's sorting condition
    int arrayRead = 0;
    PowerTree::Iterator treeRead = students.first();
    for (PowerTree::Iterator treeWrite = students.first();
         treeWrite != students.end();
         treeWrite++) {
      // Skip tree nodes with the target grade, don't compare them with themselves
      while (treeRead != students.end() && treeRead.value()->getGrade() == grade)
        treeRead++;

      // Do the merge
      Student* chosenStudent;
      if (treeRead == students.end()) {
        chosenStudent = studentsToMerge[arrayRead];
        arrayRead++;
      } else if (arrayRead == studentsCount) {
        chosenStudent = treeRead.value();
        treeRead++;
      } else {
          PowerIDPair arrayKey(studentsToMerge[arrayRead]->getPower(),
                  studentsToMerge[arrayRead]->getID());
          if (*treeRead < arrayKey) {
              chosenStudent = treeRead.value();
              treeRead++;
          } else {
              chosenStudent = studentsToMerge[arrayRead];
              arrayRead++;
          }
      }
      PowerIDPair key(chosenStudent->getPower(), chosenStudent->getID());
      treeWrite.replaceWith(key, chosenStudent);
    }

    // Free memory and update team metadata
    delete[] studentsToMerge;
    updateMostPowerfulStudent();
  }

  int* getAllStudentsByPower(int* n) {
    if (!n) throw NullArgument();
    *n = 0;
    // Count the number of students
    for (PowerTree::Iterator it = students.last(); it != students.end(); it--)
      (*n)++;

    // Allocate array and fill it
    if (!*n) return NULL;
    int* studentsArray = new int[*n];
    int arrayPos = 0;
    for (PowerTree::Iterator it = students.last(); it != students.end(); it--) {
      studentsArray[arrayPos] = it.value()->getID();
      arrayPos++;
    }

    return studentsArray;
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
