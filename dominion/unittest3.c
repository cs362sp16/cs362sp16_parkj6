/*
//Author: 		Jong Park (parkj6)
//Filename:		unittest3.c
//Description: 	Tests the function supplyCount in the dominion.c file.
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main() {
	struct gameState g;
	int test;
	
	//initialize game.
	initializeGame(2, k, 9, &g);

	//test1 = Silver
	test = supplyCount(smithy, &g);
	myassert(test==10, "Smithy gets 10 Supplies. \n\t(SHOULD PASS...)");
	
	
	//test2 = Silver
	test = supplyCount(silver, &g);
	myassert(test==40, "Silver gets 40 Supplies. \n\t(SHOULD PASS...)");
	
	
	//test3 = Copper
	test = supplyCount(copper, &g);
	myassert(test==46, "Copper gets 46 Supplies. \n\t(SHOULD PASS...)");
	
	checkasserts();
	return 0;
}
