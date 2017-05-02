#ifndef STUDENT_H
#define STUDENT_H

class Student{
  int id;
  const int grade;
  int power;

public:
  Student(const int& id, const int& grade, const int& power) : id(id), grade(grade), power(power) {}
  ~Student() {}
  Student (const Student& student) : id(student.id), grade(student.grade), power(student.power) {}

  const int& ID() const{
    return this->id;
  }
  const int& Grade() const{
    return this->grade;
  }
  void update(int addition) {
    this->power = this->power + addition;
  }

};




#endif
