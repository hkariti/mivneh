#ifndef STUDENT_H
#define STUDENT_H

class Team;

class Student{
  int id;
  const int grade;
  int power;
  Team* team;

public:
  Student(const int& id, const int& grade, const int& power) : id(id), grade(grade), power(power) {}
  ~Student() {}
  
  const int& ID() const{
    return this->id;
  }
  const int& Grade() const{
    return this->grade;
  }
  void updatePower(int addition) {
    this->power = this->power + addition;
  }
  const int& getPower() const{
    return power;
  }
  const Team* getTeam() const{
    return team;
  }
  void updateTeam(Team& newTeam) {
    this->team = &newTeam;
  }

};




#endif
