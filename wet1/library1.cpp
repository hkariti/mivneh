#include "library1.h"
#include "school.h"

void* Init() {
    return new School;
}

StatusType AddStudent(void *DS, int StudentID, int Grade, int Power) {
    if (!DS) return INVALID_INPUT;
    return ((School*)DS)->addStudent(StudentID, Grade, Power);
}

StatusType AddTeam(void *DS, int TeamID) {
    if (!DS) return INVALID_INPUT;
    return ((School*)DS)->addTeam(TeamID);
}

StatusType MoveStudentToTeam(void *DS, int StudentID, int TeamID) {
    if (!DS) return INVALID_INPUT;
    return ((School*)DS)->moveStudentToTeam(StudentID, TeamID);
}

StatusType GetMostPowerful(void *DS, int TeamID, int *StudentID) {
    if (!DS) return INVALID_INPUT;
    return ((School*)DS)->getMostPowerful(TeamID, StudentID);
}

StatusType RemoveStudent(void *DS, int StudentID) {
    if (!DS) return INVALID_INPUT;
    return ((School*)DS)->removeStudent(StudentID);
}

StatusType GetAllStudentsByPower(void *DS, int TeamID, int **Students, int *numOfStudents) {
    if (!DS) return INVALID_INPUT;
    return ((School*)DS)->getAllStudentsByPower(TeamID, Students, numOfStudents);
}

StatusType IncreaseLevel(void *DS, int Grade, int PowerIncrease) {
    if (!DS) return INVALID_INPUT;
    return ((School*)DS)->increaseLevel(Grade, PowerIncrease);
}

void Quit(void** DS) {
    if (!DS) return;
    delete (School*)(*DS);
    *DS = NULL;
}
