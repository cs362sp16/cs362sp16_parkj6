/*
//Author: 		Jong Park (parkj6)
//Filename:		randomtestcard2.c
//Description: 	Tests the gardens card in cards.h file in the dominion.c file.
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main(){
	struct gameState g;
	int test;
	int i = 0;
	
	for(i=0; i<MIL; i++){
		initializeGame(dice(10), k, EVERYTHING, &g);
		
		test = cardEffect(k[2], NULL, NULL, NULL, &g, NULL, 0);
		myassert(test==-1, "Returned -1\n");
		
		
		
		
	}
	
	checkasserts();
	return 0;
}
