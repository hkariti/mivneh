.PHONY: all zip

all: avlTest

avlTest.o: avlTest.cpp

avlTest: avlTest.o
	g++ *.o -I. -o $@

zip:
	rm -f wet1.zip
	zip wet1.zip avl.h library1.cpp powerIDPair.h school.h student.h team.h submissions.txt
