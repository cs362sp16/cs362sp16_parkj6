/*
//Author: 		Jong Park (parkj6)
//Filename:		testing.h
//Description: 	Contains the assert statement used in all the testing files.
*/

#include <stdio.h>

int tests = 0;
int pass = 0;
int fail = 0;
//default card sets
int k[10] = {smithy,
			adventurer,
			gardens,
			embargo,
			cutpurse,
			mine,
			ambassador,
			outpost,
			baron,
			tribute};

void myassert (int pass, char* msg) {
	if (pass){
		printf("TEST PASSED.\nTEST CONDITION: %s\n\n",msg);
	}
	else{
		printf("TEST FAILED.\nTEST CONDITION: %s\n\n",msg);
		fail++;
	}
	tests++;
}

void checkasserts() {
	if (fail==0) {
		printf("\nALL TEST PASSES!\t(%d/%d Passed)\n",tests,tests);
	}
	else{
		printf("\nSOME TESTS FAILED.\t (%d/%d Passed)\n",tests-fail, tests);
	}
}
