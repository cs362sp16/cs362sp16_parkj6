/*
//Author: 		Jong Park (parkj6)
//Filename:		unittest1.c
//Description: 	Tests initializeGame function in dominion.c file.
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main(){
	struct gameState g;
	int test;
		
	int k1[10] = {smithy,
				smithy, 	//extra smithy
				gardens,
				gardens,	//extra gardens
				cutpurse,
				mine,
				ambassador,
				outpost,
				baron,
				tribute};

	//test 1 = no duplicate cards
	test = initializeGame(2, k, 9, &g);
	myassert(test==0, "2 players, no duplicate cards.\n\t(SHOULD PASS...)");
	
	//test 2 = duplicate cards	
	test = initializeGame(2, k1, 9, &g);
	myassert(test==0, "2 players, duplicate cards.\n\t(SHOUDLD NOT PASS...)");
	
	// test 3 = multiplayers
	test = initializeGame(4, k, 9, &g);
	myassert(test==0, "4 players, no duplicate cards.\n\t(SHOULD PASS...)");
	
	// test 4 = multiplayers
	test = initializeGame(10, k, 9, &g);
	myassert(test==0, "10 players, no duplicate cards.\n\t(SHOULD NOT PASS...)");

	checkasserts();
	return 0;
}
