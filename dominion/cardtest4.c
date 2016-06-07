/*
//Author: 		Jong Park (parkj6)
//Filename:		cardtest4.c
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

  // TESTING -- int cardEffect(GARDENS, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
  // GARDENS -- worth 1 victory point for every 10 cards in deck

  gainCard(gardens, &G, 1, 1);                       // gain copper to player1's DECK
  int deckCount = fullDeckCount(1, 0, &G);           // deckCount should be 11 after gaining GARDENS (7 copper, 3 estates, 1 gardens)
  int cE = cardEffect(gardens, 0, 0, 0, &G, 0);
  if (cE == -1) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }
  
  int getp1Score = scoreFor(1, &G);
  getp1Score = getp1Score - 3;                      // we don't care about the 3 victory points from estates, only gardens
  if (getp1Score != (deckCount / 10)) {
	printf("FAILED\n");
  } else {
	printf("PASSED\n");
  }

  // we know the deck count is 11, and estates are no longer counted for score
  // p1Score should get 1, given we have 1 garden and 11 cards
  if (getp1Score != 1) {
	  printf("FAILED\n");
  } else {
	printf("PASSED\n");
  }

  return 0;
}