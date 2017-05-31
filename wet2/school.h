#include "team.h"
#include "hashTable.h"
#include "union_find.h"
#include "library2.h"

typedef UnionFind<Team> TeamUnion;
typedef HashTable<int, Student> StudentMap;

class School {
private:
  int teamCount;
  TeamUnion teams;
  StudentMap students;

public:
  School(int n) : teamCount(n), teams(n) {};

  StatusType addStudent(int studentID, int teamId, int power) {
    if (studentID <= 0 || power <= 0 || !validTeam(teamId))
      return INVALID_INPUT;
    Student student(studentID, power, teamId);
    Team& targetTeam = teams.find(teamId);
    try {
      Student& studentInMap = students.insert(studentID, student);
      targetTeam.addStudent(&studentInMap);
    } catch (StudentMap::EntryExists) {
      return FAILURE;
    } catch (std::bad_alloc) {
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }

  StatusType removeStudent(int studentID) {
    if (studentID <= 0) return INVALID_INPUT;
    try {
      Student& student = students[studentID];
      int teamId = student.getTeamId();
      Team& team = teams.find(teamId);
      students.remove(studentID);
      team.removeStudent(student.getPower(), student.getID());
    } catch (StudentMap::NoSuchEntry){
      return FAILURE;
    } catch (std::bad_alloc) {
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }

  StatusType joinTeams(int team1Id, int team2Id) {
    if (!validTeam(team1Id) || !validTeam(team2Id))
      return INVALID_INPUT;
    try {
      teams.join(team1Id, team2Id);
    } catch (std::bad_alloc) {
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }

  StatusType teamFight(int team1Id, int team2Id, int numOfFighters) {
    if (!validTeam(team1Id) || !validTeam(team2Id) || numOfFighters <= 0)
      return INVALID_INPUT;
    try {
      Team& team1 = teams.find(team1Id);
      Team& team2 = teams.find(team2Id);
      team1.fight(team2, numOfFighters);
    } catch (std::bad_alloc) {
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }

  StatusType getNumOfWins(int teamId, int* wins) {
    if (!validTeam(teamId)) return INVALID_INPUT;
    try {
      Team& team = teams.find(teamId);
      *wins = team.getWins();
    } catch (std::bad_alloc) {
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }

  StatusType getStudentTeamLeader(int studentId, int* leader) {
    if (studentId <= 0) return INVALID_INPUT;
    try {
      Student& student = students[studentId];
      Team& team = teams.find(student.getTeamId());
      *leader = team.getMostPowerfulStudent();
    } catch (std::bad_alloc) {
      return ALLOCATION_ERROR;
    }
    return SUCCESS;
  }
private:
  bool validTeam(int teamId) {
    return teamId > 0 && teamId <= teamCount;
  }
};
