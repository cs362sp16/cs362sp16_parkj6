/*
//Author: 		Jong Park (parkj6)
//Filename:		cardtest1.c
//Description: 	Tests cards
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main() {
	struct gameState g;
	int test;
	
	//initialize game.
	initializeGame(2, k, 9, &g);
	
	g.phase = 1;
	g.numActions = 1;
	test = playCard(4, 0, 0, 0, &g);
	printf ("test = %d",test);
	myassert(test==0, "card played.");
	
	checkasserts();
	return 0;
}

