/*
//Author: 		Jong Park (parkj6)
//Filename:		cardtest3.c
//Description: 	Tests cards
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"

int main (int argc, char** argv) {
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

  printf ("Starting game.\n");

  // 2 player game
  srand(time(NULL));
  int rando = ( rand()%10 );
  int r = initializeGame(2, k, rando, &G);
  if (r == 0) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }

  // TESTING -- int cardEffect(STEWARD, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
  // STEWARD -- choice1 = 1:     +2 cards
  //         -- choice1 = 2:     +2 coins
  //         -- choice1 = 3:     trash 2 cards from hand  (given by choice2 and choice3)
  int p1handCount = G.handCount[0];
  int cE = cardEffect(steward, 1, 0, 0, &G, 0);

  if (G.handCount[0] != (p1handCount + 2)) {
	printf("FAILED\n");
  } else {
	printf("PASSED\n");
  }
  if (cE == 0) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }

  int numCoins = G.coins;
  cE = cardEffect(steward, 2, 0, 0, &G, 0);

  if (G.coins != (numCoins + 2)) {
	printf("FAILED\n");
  } else {
	printf("PASSED\n");
  }
  if (cE == 0) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }

  gainCard(copper, &G, 2, 1);   // gain copper to player1's hand
  gainCard(copper, &G, 2, 1);   // do it twice, so we can discard 2 coppers
  p1handCount = G.handCount[0];
  cE = cardEffect(steward, 3, copper, copper, &G, 0);

 if (G.handCount[0] != (p1handCount - 2)) {
	printf("FAILED\n");
  } else {
	printf("PASSED\n");
  }
  if (cE == 0) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }

  return 0;
}
