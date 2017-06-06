from random import seed, randrange, shuffle, choice
from collections import namedtuple, OrderedDict
from sys import argv
from contextlib import nested
from math import log

probs = [
    9,  # "AddStudent"
    4,  # "RemoveStudent"
    2,  # "JoinTeams"
    8,  # "TeamFight"
    5,  # "GetStudentLeader"
    6,  # "GetNumOfWins"
]


def accumulate(arr):
    sum = 0
    for x in arr:
        sum += x
        yield sum


Command = namedtuple('Command',
                     ['name', 'args_format', 'func', 'student', 'team1',
                      'team2', 'power', 'n_fighters'])

Team = namedtuple('Team', ['t_students', 'n_wins'])

Student = namedtuple('Student', ['id', 'power', 'team'])

n = None
team_id_range = None
teams = []
teams_uf = []
student_id_range = None
student_power_range = None
students = OrderedDict()
team_mapping = []


def output(cmd, status):
    return "{name}: {status}".format(name=cmd.name, status=status)


def fail(cmd):
    return output(cmd, "FAILURE")


def invalid_input(cmd):
    return output(cmd, "INVALID_INPUT")


def success(cmd):
    return output(cmd, "SUCCESS")


def result(cmd, res):
    return "{res}".format(res=res)


def add_student(cmd):
    if cmd.student <= 0 or cmd.power <= 0 or not is_valid_team(cmd.team1):
        return invalid_input(cmd), "II id <= 0 or power <= 0"
    if cmd.student in students:
        return fail(cmd), "F student already exists"
    new_stud = Student(id=cmd.student, power=cmd.power, team=cmd.team1)
    students[cmd.student] = new_stud
    teams[team_mapping[cmd.team1]].t_students[(cmd.power, cmd.student)] = new_stud
    return success(cmd), "S"


def remove_student(cmd):
    if cmd.student <= 0:
        return invalid_input(cmd), "II id <= 0"
    if cmd.student not in students:
        return fail(cmd), "F student doesn't exist"
    team_n = team_mapping[students[cmd.student].team]
    power = students[cmd.student].power
    students.pop(cmd.student)
    del teams[team_n].t_students[(power, cmd.student)]
    return success(cmd), "S"


def is_valid_team(team):
    return team in range(1, n + 1)


def merge_dicts(x, y):
    z = x.copy()
    z.update(y)
    return z


def join_teams(cmd):
    if not (is_valid_team(cmd.team1) and is_valid_team(cmd.team2)):
        return invalid_input(cmd), "II invalid team"
    if teams_uf[team_mapping[cmd.team1]] == teams_uf[team_mapping[cmd.team2]]:
        return success(cmd), "S"
    real_t1 = team_mapping[cmd.team1]
    real_t2 = team_mapping[cmd.team2]
    united = min(real_t1, real_t2)
    teams_uf[united] = teams_uf[real_t2] | teams_uf[real_t1]  #union
    for i in teams_uf[united]:
        team_mapping[i] = united
    teams[united] = Team(n_wins=teams[real_t1].n_wins + teams[real_t2].n_wins,
                         t_students=merge_dicts(teams[real_t1].t_students,
                                              teams[real_t2].t_students))
    return success(cmd), "S"


def sum_n_strongest(cmd, team):
    if not team.t_students:
        return 0
    top_n_keys = sorted(team.t_students.keys(), cmp=None,
                        key=lambda (x, y): (x, -y),
                        reverse=True)[0:cmd.n_fighters]
    return sum(map(lambda (x, y): x, top_n_keys))


def team_fight(cmd):
    if not (is_valid_team(cmd.team1) and is_valid_team(cmd.team2)):
        return invalid_input(cmd), "II invalid team"
    if cmd.n_fighters <= 0:
        return invalid_input(cmd), "II negative number of fighters"
    t1 = teams[team_mapping[cmd.team1]]
    t2 = teams[team_mapping[cmd.team2]]
    sum1 = sum_n_strongest(cmd, t1)
    sum2 = sum_n_strongest(cmd, t2)
    if sum1 > sum2:
        teams[team_mapping[cmd.team1]] = Team(t_students=t1.t_students,
                                              n_wins=t1.n_wins + 1)
    if sum2 > sum1:
        teams[team_mapping[cmd.team2]] = Team(t_students=t2.t_students,
                                              n_wins=t2.n_wins + 1)
    return success(cmd), "S"


def get_student_leader(cmd):
    if cmd.student <= 0:
        return invalid_input(cmd), "II invalid id"
    if cmd.student not in students:
        return fail(cmd), "F student doesn't exist"
    curr_team = team_mapping[students[cmd.student].team]
    return result(cmd, "The leader is: {0}".format(
        sorted(teams[curr_team].t_students, cmp=None, key=lambda (x, y): (x, -y),
               reverse=True)[0][1])), "S"


def get_num_of_wins(cmd):
    if not is_valid_team(cmd.team1):
        return fail(cmd), "II invalid team"
    return result(cmd, "Team {0} won {1} times.".format(cmd.team1, teams[
        team_mapping[cmd.team1]].n_wins)), "S"


def init(num_teams):
    global n, teams, teams_uf, student_id_range, student_power_range, \
        team_id_range, team_mapping
    n = num_teams
    teams = []
    for i in range(0, n+1):
        teams.append(Team(n_wins=0, t_students=dict()))
    student_power_range = (-1, n * (n + 1) // 2)
    student_id_range = (-1, n * 4)
    team_id_range = (1, n + 1)
    teams_uf = [set([i]) for i in range(0, n + 1)]
    team_mapping = range(0, n + 1)


def execute_cmd(cmd):
    return cmd.func(cmd)


cmds = [
    ("AddStudent", "{student} {team1} {power}", add_student),
    ("RemoveStudent", "{student}", remove_student),
    ("JoinTeams", "{team1} {team2}", join_teams),
    ("TeamFight", "{team1} {team2} {n_fighters}", team_fight),
    ("GetStudentLeader", "{student}", get_student_leader),
    ("GetNumOfWins", "{team1}", get_num_of_wins),
]


def random_team():
    return randrange(*team_id_range)


def random_student():
    return randrange(*student_id_range)


def random_power():
    return randrange(*student_power_range)


def random_n_fighters():
    max_fighters, _ = divmod(len(students), n)
    return choice(range(-1, (max_fighters+1) * 5))


def is_team_ok(team):
    return all(
        map(lambda x: x.team == -1 or team not in teams_uf[x.team],
            students.values()))


def random_cmd():
    choices = sum([[element] * int(weight * 100) for element, weight in
                   zip(cmds, probs)], [])
    cmd = Command(*choice(choices), student=random_student(), team1=random_team(),
                  team2=random_team(), power=random_power(),
                  n_fighters=random_n_fighters())
    return cmd

"""
Args:
    [1] - test length, number of lines
    [2] - test name
    [3] - 0 to choose random seed, any other number will be taken as seed
    [4] - 1 to shuffle probabilities of each command, 0 otherwise
    [5] - 1 to generate in no failures mode (only successful cases will be tested)
    [6] - (optional) number of teams
"""
if __name__ == "__main__":

    """ for debugging purposes - comment this """
    if len(argv) not in [6, 7]:
        exit(1)
    test_length = int(argv[1])
    if test_length <= 0:
        exit(1)
    test_name = argv[2]
    detailed = True
    if argv[3] != "0":
        seed(int(argv[3]))
    if argv[4] == "1":
        shuffle(probs)
    no_failures = (argv[5] == "1")
    if len(argv) == 7:
        num_teams = int(argv[6])
    else:
        num_teams = int(5 * (log(test_length, 10) ** 1.2))


    """ for debugging purposes - uncomment this """
    # seed(30031990)
    # test_length = 1000
    # test_name = "gen_test"
    # detailed = True
    # no_failures = True
    # num_teams = int(5 * (log(test_length, 10) ** 1.2))


    num_teams = min(num_teams, 50)
    with nested(open(test_name + ".in", 'w'),
                open(test_name + ".out", 'w')) as (in_file, out_file):

        def print_to_in(s):
            in_file.write(s + "\n")


        def print_to_out(s):
            out_file.write(s + "\n")


        init(num_teams)
        print_to_in("Init {n}".format(n=num_teams))
        print_to_out("Init done.")

        for _ in range(test_length):
            cmd = random_cmd()
            res, comment = execute_cmd(cmd)
            if no_failures:
                if comment[0] == "F" or comment[0] == "I":
                    continue
            if detailed:
                print_to_in((cmd.name + " " + cmd.args_format.format(
                    **cmd._asdict())).ljust(25) + ("#" + comment))
            else:
                print_to_in(
                    (cmd.name + " " + cmd.args_format.format(**cmd._asdict())))
            print_to_out(res)

        print_to_in("Quit")
        print_to_out("Quit done.")


"""
Note: regex for removing failed lines from test.in : ^[^#\n]*#[FI][^\n]*\n
"""