/*
//Author: 		Jong Park (parkj6)
//Filename:		unittest2.c
//Description: 	Tests the function numHandCards in dominion.c file.
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main() {
	struct gameState g;
	int test;
	
	//initialize game.
	initializeGame(2, k, 9, &g);
	
	//test 1 = 5 cards at start. 
	test = numHandCards (&g);
	myassert(test==5, "5 Cards at start.\n\t(SHOULD PASS...)");
		
	//test 2 = 10 cards at start. 
	test = numHandCards (&g);
	myassert(test==10, "10 Cards at start.\n\t(SHOULD NOT PASS...)");
	
	//test 3 = 1 cards at start. 
	test = numHandCards (&g);
	myassert(test==1, "1 Cards at start.\n\t(SHOULD NOT PASS...)");
	
	checkasserts();
	return 0;
}
