/*
//Author: 		Jong Park (parkj6)
//Filename:		cardtest2.c
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
	
	
	
	
	checkasserts();
	return 0;
}
