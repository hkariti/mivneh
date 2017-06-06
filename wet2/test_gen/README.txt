
Requirements:
	Bash, Python 2, valgrind.
	You can use T2 (I also heard about csl2.cs.technion.ac.il) or ubuntu on windows (Anniversary update)

Instructions:
	0. If you work on T2 - run ". /usr/local/gcc4.7/setup.sh" to update g++ (if you need to)
	1. Put your *.cpp files in the same folder with test scripts
	2. run ./run_test
	3. check the output

Contents:
	generator.py - script, which creates a random test
	
	translate.py - script which translates a text test to a c++ code (for debugging). Lines in c++ test are numbered according to their numbers in text test.
	
	run_test - bash script which creates number of random tests, compiles your program, and runs created tests with diff and valgrind.
		You can tweak some paramers in this script, for example there are options to set random seed (so you won't get different tests every run),
		to generate test with successful actions only (makes debugging easier), or to change tests' lengths.

Tip: 
	If you don't pass some of the tests, I suggest you to switch to no-FAILURE mode and set some arbitrary random seed (I explained about it 
	just few lines above, you also can find examples in run_test.sh code. Don't ), and of course, to use c++ version of test. 
	
	Optional: for those of you who want to tweak the test even further, I suggest to play with probability weights of each command at generator.py, lines 7-14.

Special credit to:
	Yair Twito and Arik Rinberg who wrote the original scripts (or maybe they just changed a test from previous semester, like I did, I'm not sure). 

Good luck!
