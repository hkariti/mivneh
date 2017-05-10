import random
import sys

commandStr = ["AddTeam", "AddStudent",
                "MoveStudentToTeam", "AssignMagi", "RemoveStudent",
                "IncreaseLevel", "GetMostPowerful", "GetAllStudentsByPower"]

SUCCESS = "SUCCESS"
FAILURE = "FAILURE"
INVALID_INPUT = "INVALID_INPUT"

TeamsID = dict()

StudentsID = dict()
StudentsGrade = dict()
StudentsPower = dict()
StudentsTeam = dict()

size = 0
teams_count = 0;
students_count = 0;


def initline():
    global size, StudentsPower, StudentsID
    inLine = "Init"
    outLine = "Init done."
    return inLine, outLine


# AddTeam team_id
def AddTeam():
    global TeamsID, teams_count
    team_id = random.randint(-3, 3)
    inLine = "AddTeam %d" % (team_id)
    outLine = "AddTeam: "
    if team_id <= 0:
        outLine += INVALID_INPUT
    elif team_id in TeamsID.keys():
        outLine += FAILURE
    else:
        TeamsID[team_id] = {}
        teams_count += 1
        outLine += SUCCESS
    return inLine, outLine

# AddStudent student_id grade power 
def AddStudent():
    global StudentsID, StudentsGrade, StudentsPower, StudentsTeam, students_count
    student_id = random.randint(-10, 1000)
    grade = random.randint(-3, 3)
    power = random.randint(-3, 3)
    inLine = "AddStudent %d %d %d" % (student_id,grade,power)
    outLine = "AddStudent: "
    if student_id <= 0 or grade < 0 or power <=0:
        outLine += INVALID_INPUT
    elif student_id in StudentsID.keys():
        outLine += FAILURE
    else:
        StudentsID[student_id] = student_id
        StudentsGrade[student_id] = grade
        StudentsPower[student_id] = power
        StudentsTeam[student_id] = -1
        students_count += 1
        outLine += SUCCESS
    return inLine, outLine
    
# MoveStudentToTeam student_id team_id 
def MoveStudentToTeam():
    global TeamsID, StudentsID, StudentsGrade, StudentsPower, StudentsTeam, teams_count
    student_id = random.randint(-10, 1000)
    team_id = random.randint(-3, 3)
    inLine = "MoveStudentToTeam %d %d" % (student_id,team_id)
    outLine = "MoveStudentToTeam: "
    if student_id <= 0 or team_id <=0:
        outLine += INVALID_INPUT
    elif student_id not in StudentsID.keys() or team_id not in TeamsID.keys():
        outLine += FAILURE
    else:
        if StudentsTeam[student_id] > 0 :
            TeamsID[StudentsTeam[student_id]].pop(student_id, None)
        TeamsID[team_id][student_id] = (student_id, StudentsGrade[student_id], StudentsPower[student_id])
        StudentsTeam[student_id] = team_id
        outLine += SUCCESS
    return inLine, outLine


# RemoveStudent student_id
def RemoveStudent():
    global StudentsID, StudentsGrade, StudentsPower, StudentsTeam, students_count
    student_id = random.randint(-10, 1000)
    inLine = "RemoveStudent %d" % student_id
    outLine = "RemoveStudent: "
    if student_id <= 0 :
        outLine +=INVALID_INPUT
    elif student_id not in StudentsID.keys():
        outLine += FAILURE
    else:
        StudentsID.pop(student_id, None)
        StudentsGrade.pop(student_id, None)
        StudentsPower.pop(student_id, None)
        if StudentsTeam[student_id] > 0 :
            TeamsID[StudentsTeam[student_id]].pop(student_id, None)
        StudentsTeam.pop(student_id, None)
        outLine += SUCCESS
    return inLine, outLine
    
    # GetMostPowerful team_id
def GetMostPowerful():
    global TeamsID, StudentsPower
    team_id = random.randint(-3, 3)
    inLine = "GetMostPowerful %d" % team_id
    outLine = ""
    if team_id == 0 :
        outLine += "GetMostPowerful: " + INVALID_INPUT
    elif team_id < 0:
        if any(StudentsID):
            #max_power = StudentsPower[max(StudentsPower)] #biggest_id
            all_students = sorted(StudentsPower.items() ,key = lambda (k,v):k)
            all_students.sort(key = lambda (k,v) : v, reverse = True)
            #min_power_student_id = (sorted((dict(filter(lambda (k,v): v == max_power, StudentsPower.items()))).items(), lambda (k,v) : k, reverse = True))[0][0]
            outLine += "Most powerful student is: " + "%d" % all_students[0][0]
        else:
            outLine += "Most powerful student is: " + "-1"
    elif team_id in TeamsID.keys():
        if any(TeamsID[team_id]):
            students_of_team = sorted(TeamsID[team_id].items() ,key = lambda x:(x[1][0]))
            students_of_team.sort(key = lambda x:(x[1][2]), reverse = True)
            #max_power = max(TeamsID[team_id].items(), key = lambda (k,v) :v[2])[1][2]
            #min_power_student_id = (sorted((dict(filter(lambda (k,v): v[2] == max_power, TeamsID[team_id].items()))).items(), lambda (k,v) : k, reverse = True))[0][0]
            outLine += "Most powerful student is: " + "%d" %  students_of_team[0][0]
        else: 
            outLine += "Most powerful student is: " + "-1"
    else:
        outLine += "GetMostPowerful: " + FAILURE
    return inLine, outLine

def natural_numbers():
    n = 0
    while True:
        n += 1
        yield n    
    
    # GetAllStudentsByPower team_id
def GetAllStudentsByPower():
    global TeamsID, StudentsPower
    team_id = random.randint(-3, 3)
    gen = natural_numbers()
    inLine = "GetAllStudentsByPower %d" % team_id
    outLine = ""
    if team_id == 0:
        outLine += "GetAllStudentsByPower: " + INVALID_INPUT
    elif team_id < 0:
           all_students = sorted(StudentsPower.items() ,key = lambda (k,v):k)
           all_students.sort(key = lambda (k,v) : v, reverse = True)
           gen = natural_numbers()
           first = 1
           for student in all_students:
                if first == 1:
                    outLine += "Rank\t||\tStudent\n"
                first = 0
                i = gen.next()
                outLine += "%d\t\t||\t%d\n" %  (i,student[0])
           outLine += "and there are no more students!"
    elif team_id in TeamsID.keys():
           students_of_team = sorted(TeamsID[team_id].items() ,key = lambda x:(x[1][0]))
           students_of_team.sort(key = lambda x:(x[1][2]), reverse = True)
           first = 1
           for student in students_of_team:
                if first == 1:
                    outLine += "Rank\t||\tStudent\n"
                first = 0
                i = gen.next()
                outLine += "%d\t\t||\t%d\n" %  (i,student[0])
           outLine += "and there are no more students!"
    else:
        outLine += "GetAllStudentsByPower: " + "FAILURE"
    return inLine, outLine

    
    # GetAllStudentsByPower grade power_increase
def IncreaseLevel():
    global TeamsID, StudentsGrade, StudentsPower, StudentsTeam
    grade = random.randint(-3, 3)
    power_increase = random.randint(-3, 3)
    inLine = "IncreaseLevel %d %d" % (grade, power_increase)
    outLine = "IncreaseLevel: "
    if grade < 0 or power_increase <= 0:
        outLine += INVALID_INPUT
    else:
        for (student_id, student_grade) in StudentsGrade.items():
            if student_grade == grade:
                StudentsPower[student_id] += power_increase
                if StudentsTeam[student_id] > 0 :
                    TeamsID[StudentsTeam[student_id]][student_id] = (TeamsID[StudentsTeam[student_id]][student_id][0], TeamsID[StudentsTeam[student_id]][student_id][1], TeamsID[StudentsTeam[student_id]][student_id][2] + power_increase)
        outLine += SUCCESS
    return inLine, outLine

def main():
    if len(sys.argv) < 2:
        print "Usage %s <lines>" % sys.argv[0]
        exit(0)
    lines = int(sys.argv[1])
    infname = "%s.in" % sys.argv[2]
    outfname = "%s.out" % sys.argv[2]
    functions = [AddTeam, AddStudent, MoveStudentToTeam, RemoveStudent,
                IncreaseLevel, GetMostPowerful, GetAllStudentsByPower]
    with open(infname, 'wb') as infhandler:
        with open(outfname, 'wb') as outfhandler:
            inLine, outLine = initline()
            infhandler.write(inLine + "\n")
            outfhandler.write(outLine + "\n")
            while lines > 0:
                f = random.randint(0, len(functions)-1)
                func = functions[f]
                inLine, outLine = func()
                if inLine is not "":
                    infhandler.write(inLine + "\n")
                    outfhandler.write(outLine + "\n")
                    lines -= 1
            infhandler.write("Quit\n")
            outfhandler.write("Quit done.\n")


main()
