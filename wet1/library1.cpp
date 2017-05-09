#include "library1.h"
#include "school.h"

void* Init() {
    return new School;
}

StatusType AddStudent(void *DS, int StudentID, int Grade, int Power) {
    return ((School*)DS)->addStudent(StudentID, Grade, Power);
}

StatusType AddTeam(void *DS, int TeamID) {
    return ((School*)DS)->addTeam(TeamID);
}

StatusType MoveStudentToTeam(void *DS, int StudentID, int TeamID) {
    return ((School*)DS)->moveStudentToTeam(StudentID, TeamID);
}

StatusType GetMostPowerful(void *DS, int TeamID, int *StudentID) {
    return ((School*)DS)->getMostPowerful(TeamID, StudentID);
}

StatusType RemoveStudent(void *DS, int StudentID) {
    return ((School*)DS)->removeStudent(StudentID);
}

StatusType GetAllStudentsByPower(void *DS, int TeamID, int **Students, int *numOfStudents) {
    return ((School*)DS)->getAllStudentsByPower(TeamID, Students, numOfStudents);
}

StatusType IncreaseLevel(void *DS, int Grade, int PowerIncrease) {
    return ((School*)DS)->increaseLevel(Grade, PowerIncrease);
}

void Quit(void** DS) {
    delete (School*)(*DS);
    *DS = NULL;
}
