/*
//Author: 		Jong Park (parkj6)
//Filename:		cardtest2.c
//Description: 	Tests cards
*/

#include <stdio.h>
#include "dominion.h"
#include "testing.h"
#include "cards.h"

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

  // TESTING -- int remodelEffect(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
  // Remodel trashes a card in current_player's hand (choice1)
  // ... then, the player gains a card of value UP TO 2 more than trashed card (choice2)
  int p1handCount = G.handCount[0];

  
  if (G.playedCardCount == 0) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }
  
  int re = rem(0, &G, 0, estate, smithy);

  if (G.handCount[0] == (p1handCount-1)) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }
  if (G.playedCardCount == 1) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }
  if (re == 0) {
	printf("PASSED\n");  
  } else {
	printf("FAILED\n");
  }

  return 0;
}
