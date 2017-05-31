.PHONY: test clean

test: hashTableTest
	./hashTableTest
clean:
	rm *.o
	rm *Test
%.o: %.cpp
	g++ -O0 -g -c $^
hashTableTest: hashTableTest.o
	g++ -o $@ $<

hashTableTest.o: hashTableTest.cpp hashTable.h testUtils.h
