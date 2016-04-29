/*
//Author: 		Jong Park (parkj6)
//Filename:		unittest2.c
//Description: 	Tests
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main() {
	struct gameState g;
	int test;

	initializeGame(2, k, 9, &g);
	test = shuffle(0, &g);
	
	checkasserts();
	return 0;
}