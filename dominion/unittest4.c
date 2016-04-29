/*
//Author: 		Jong Park (parkj6)
//Filename:		unittest4.c
//Description: 	Tests endTurn functions in the dominion.c file.
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main() {
	struct gameState g;
	int test;
	
	//initialize game.
	initializeGame(2, k, 9, &g);
	
	test = endTurn(&g);
	myassert(test==0, "Turn ended.");
	
	checkasserts();
	return 0;
}
