#include <assert.h>
#include "team.h"
#include "testUtils.h"

void testAddStudent() {
  Team t(4);

  Student student1(1, 0, 0);

  // NULL argument
  THROWS(t.addStudent(NULL), Team::NullArgument);
  // To empty team
  t.addStudent(&student1);
  // Same student
  THROWS(t.addStudent(&student1), PowerTree::AlreadyThere);
  // Same power
  Student student2(2, 0, 0);
  t.addStudent(&student2);
  // To non empty team
  Student student3(3, 0, 0);
  t.addStudent(&student3);
}

void testRemoveStudent() {
  Team t(4);

  // Empty team
  THROWS(t.removeStudent(1, 1), PowerTree::isEmpty);

  Student student1(1, 0, 1);
  Student student2(2, 0, 1);
  Student student3(3, 0, 2);
  t.addStudent(&student1);
  t.addStudent(&student2);
  t.addStudent(&student3);

  // Non-existing student
  THROWS(t.removeStudent(124, 1), PowerTree::NotFound);

  // non-empty team
  t.removeStudent(1, 1);
  t.removeStudent(1, 2);
  // empty team
  t.removeStudent(2, 3);
}

void testGetMostPowerfulStudent() {
  Team t(4);

  // Empty team
  assert(t.getMostPowerfulStudent() == -1);

  // One student
  Student student1(2, 0, 1);
  t.addStudent(&student1);
  assert(t.getMostPowerfulStudent() == 2);

  // Same power, higher id
  Student student3(3, 0, 1);
  t.addStudent(&student3);
  assert(t.getMostPowerfulStudent() == 2);

  // Same power, smaller id
  Student student2(1, 0, 1);
  t.addStudent(&student2);
  assert(t.getMostPowerfulStudent() == 1);

  // Lower power
  Student student4(4, 0, 0);
  t.addStudent(&student4);
  assert(t.getMostPowerfulStudent() == 1);

  // Higher power
  Student student5(5, 0, 3);
  t.addStudent(&student5);
  assert(t.getMostPowerfulStudent() == 5);
}

void testIncreaseLevel() {
  Team t(4);

  // Empty team
  t.increaseLevel(2, 1);
  assert(t.getMostPowerfulStudent() == -1);

  // Add some students
  Student student1(1, 0, 1);
  Student student2(2, 1, 1);
  Student student3(3, 1, 4);
  Student student4(4, 0, 2);
  Student student5(5, 2, 3);
  Student student6(6, 0, 1);
  // Order in tree (low to high):
  //   Student student6(6, 0, 1);
  //   Student student2(2, 1, 1);
  //   Student student1(1, 0, 1);
  //   Student student4(4, 0, 2);
  //   Student student5(5, 2, 3);
  //   Student student3(3, 1, 4);
  t.addStudent(&student1);
  t.addStudent(&student2);
  t.addStudent(&student3);
  t.addStudent(&student4);
  t.addStudent(&student5);
  t.addStudent(&student6);

  // Empty grade
  t.increaseLevel(1337, 3);
  assert(t.getMostPowerfulStudent() == 3);

  // Zero power increase
  t.increaseLevel(0, 0);
  assert(t.getMostPowerfulStudent() == 3);

  // Increase causes most powerful student to be updated
  t.increaseLevel(0, 3);
  assert(t.getMostPowerfulStudent() == 4);

  // Increase doesn't update the most powerful student
  t.increaseLevel(2, 1);
  assert(t.getMostPowerfulStudent() == 4);

  // Sanity check the tree
  int studentsCorrectOrder[] = { 4, 1, 3, 5, 6, 2 };
  int n;
  int* studentsActualOrder = t.getAllStudentsByPower(&n);
  assert(n  == sizeof(studentsCorrectOrder)/sizeof(int));
  for (int i = 0; i < n; i++) {
    assert(studentsActualOrder[i] == studentsCorrectOrder[i]);
  }
  delete[] studentsActualOrder;
}

void testGetAllStudentsByPower() {
    Team t(4);
    int n;
    int* studentsArray;

    // NULL argument
    THROWS(t.getAllStudentsByPower(NULL), Team::NullArgument);

    // Empty team
    studentsArray = t.getAllStudentsByPower(&n);
    assert(n == 0);
    assert(studentsArray == NULL);

    // One student
    Student student1(1, 0, 3);
    t.addStudent(&student1);
    studentsArray = t.getAllStudentsByPower(&n);
    assert(n == 1);
    assert(studentsArray[0] == 1);
    delete[] studentsArray;

    // Weaker student
    Student student2(2, 0, 1);
    t.addStudent(&student2);
    studentsArray = t.getAllStudentsByPower(&n);
    assert(n == 2);
    assert(studentsArray[0] == 1);
    assert(studentsArray[1] == 2);
    delete[] studentsArray;

    // Stronger student
    Student student3(3, 0, 4);
    t.addStudent(&student3);
    studentsArray = t.getAllStudentsByPower(&n);
    assert(n == 3);
    assert(studentsArray[0] == 3);
    assert(studentsArray[1] == 1);
    assert(studentsArray[2] == 2);
    delete[] studentsArray;

    // In the middle
    Student student4(4, 0, 4);
    t.addStudent(&student4);
    studentsArray = t.getAllStudentsByPower(&n);
    assert(n == 4);
    assert(studentsArray[0] == 3);
    assert(studentsArray[1] == 4);
    assert(studentsArray[2] == 1);
    assert(studentsArray[3] == 2);
    delete[] studentsArray;
}

int main() {
  RUN_TEST(testAddStudent);
  RUN_TEST(testRemoveStudent);
  RUN_TEST(testGetMostPowerfulStudent);
  RUN_TEST(testIncreaseLevel);
  RUN_TEST(testGetAllStudentsByPower);
  return 0;
}
