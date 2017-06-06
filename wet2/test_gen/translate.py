import sys

def main():
    if len(sys.argv) <= 1:
        print "Usage: %s [input_file]" % sys.argv[0]
        return
    with open(sys.argv[1]) as f:
        with open(sys.argv[1]+".debug.cc", 'w') as o:
            o.write("void test() {\n")
            o.write("   int leader;\n")
            o.write("   int number_of_wins;\n")
            for line_num, line in enumerate(f):
                line = line.split()
                if line[0] == "Init":
                    o.write("   void* DS = Init(%s);" % line[1])
                elif line[0] == "AddStudent":
                    o.write("   AddStudent(DS,%s,%s,%s);" % (
                        line[1], line[2], line[3]))
                elif line[0] == "RemoveStudent":
                    o.write("   RemoveStudent(DS,%s);" % line[1])
                elif line[0] == "JoinTeams":
                    o.write("   JoinTeams(DS,%s,%s);" % (line[1], line[2]))
                elif line[0] == "TeamFight":
                    o.write("   TeamFight(DS,%s,%s,%s);" % (
                        line[1], line[2], line[3]))
                elif line[0] == "GetNumOfWins":
                    o.write("   GetNumOfWins(DS,%s,&number_of_wins);" % line[1])
                elif line[0] == "GetStudentLeader":
                    o.write("   GetStudentTeamLeader(DS,%s,&leader);" % line[1])
                else:
                    o.write("   Quit(&DS);")
                if (line_num + 1) % 10 == 0:
                    o.write(" // %s" % (line_num + 1))
                o.write("\n")
            o.write("}\n")


main()
