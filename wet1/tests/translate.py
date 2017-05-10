import sys

def main():
    if len(sys.argv) <= 1:
        print "Usage: %s [input_file]" % sys.argv[0]
        return
    sep = '.'
    file_name = ".".join(sys.argv[1].split(sep)[0:-1]) + ".debug.c"
    
    with open(sys.argv[1]) as f:
        with open(file_name, 'w') as o:
            o.write("/* Line numbers in comments correspond to line numbers in input file. \n")
            o.write("   To match the numbers of lines in output file, you can find and \n")
            o.write("   replace (Notepad++ recommended) following regular expression:\n")
            o.write("   [^\\n]*\|\|[^\\n]*\\n   with nothing. */\n\n")
            o.write("void test() {\n")
            o.write("   int studentId;\n")
            o.write("   int* students;\n")
            o.write("   int size;\n")
            for line_num, line in enumerate(f):
                line_n = " // %s" % (line_num+1) if (line_num+1)%10 == 0 else ""
                line = line.split()
                if line[0] == "Init":
                    o.write("   void* DS = Init();%s\n" % line_n)
                elif line[0] == "AddStudent":
                    o.write("   AddStudent(DS,%s,%s,%s);%s\n" % (line[1], line[2], line[3], line_n))
                elif line[0] == "AddTeam":
                    o.write("   AddTeam(DS,%s);%s\n" % (line[1], line_n))
                elif line[0] == "MoveStudentToTeam":
                    o.write("   MoveStudentToTeam(DS,%s,%s);%s\n" % (line[1], line[2], line_n))
                elif line[0] == "GetMostPowerful":
                    o.write("   GetMostPowerful(DS,%s,&studentId);%s\n" % (line[1], line_n))
                elif line[0] == "RemoveStudent":
                    o.write("   RemoveStudent(DS,%s);%s\n" % (line[1], line_n))
                elif line[0] == "GetAllStudentsByPower":
                    o.write("   GetAllStudentsByPower(DS,%s,&students, &size);%s\n" % (line[1], line_n))
                    o.write("   free(students);\n")
                    o.write("   students=NULL;\n")
                elif line[0] == "IncreaseLevel":
                    o.write("   IncreaseLevel(DS,%s,%s);%s\n" % (line[1], line[2], line_n))
                else:
                    o.write("   Quit(&DS);\n")
            o.write("}\n")


main()

