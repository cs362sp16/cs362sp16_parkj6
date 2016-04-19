int adventurer(int drawntreasure, struct gameState *state, int currentPlayer, int temphand, int z) {
	while(drawntreasure<2){
		//if the deck is empty we need to shuffle discard and add to deck
		if (state->deckCount[currentPlayer] <1){
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		//top card of hand is most recently drawn card.
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
			drawntreasure++;
		}else {
		  temphand[z]=cardDrawn;
		  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
		  z++;
		}
    }
    
	while(z-1>=0){
		// discard all cards in play that have been drawn
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; 
		z=z-1;
	}
	
	return 0;
}

int council(int currentPlayer, struct gameState *state, int handPos) {
	int i;

	//+4 Cards
    for (i = 0; i < 4; i++) {
	  drawCard(currentPlayer, state);
	}
			
    //+1 Buy
	state->numBuys++;
			
    //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++) {
		if ( i != currentPlayer ) {
			drawCard(i, state);
	    }
	}
	
    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);
			
      return 0;
}

