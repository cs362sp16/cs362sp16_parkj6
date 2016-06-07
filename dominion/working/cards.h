
#ifndef CARDS_H
#define CARDS_H
#include <stdio.h>

int Adventure(struct gameState *state, int currentPlayer, int drawntreasure, int *temphand, int z){
	int cardDrawn;
	while(drawntreasure<2){

		if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else{
			temphand[z]=cardDrawn;
			state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	}
	while(z-1>=0){
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
	}
	return 0;
}


int Council_room(struct gameState *state, int currentPlayer, int handPos){
	//+4 Cards
	int i;
	for (i = 0; i < 4; i++)
	{
		drawCard(currentPlayer, state);
	}

	//+1 Buy
	state->numBuys++;

	//Each other player draws a card
	for (i = 0; i < state->numPlayers; i++)
	{
		if ( i != currentPlayer )
		{
			drawCard(i, state);
		}
	}

	//put played card in played card pile
	discardCard(handPos, currentPlayer, state, 0);

	return 0;
}

int Feast(struct gameState *state, int currentPlayer, int handPos, int *temphand, int choice1){
	//gain card with cost up to 5
	//Backup hand
	int i;
	int x;
	for (i = 0; i < state->handCount[currentPlayer]; i++){
		temphand[i] = state->hand[currentPlayer][i];//Backup card
		state->hand[currentPlayer][i] = -1;//Set to nothing
	}
	//Backup hand

	//Update Coins for Buy
	updateCoins(currentPlayer, state, 5);
	x = 1;//Condition to loop on
	while( x == 1) {//Buy one card
		if (supplyCount(choice1, state) <= 0){
			if (DEBUG)
				printf("None of that card left, sorry!\n");

			if (DEBUG){
				printf("Cards Left: %d\n", supplyCount(choice1, state));
			}
		}
		else if (state->coins < getCost(choice1)){
			printf("That card is too expensive!\n");

			if (DEBUG){
				printf("Coins: %d < %d\n", state->coins, getCost(choice1));
			}
		}
		else{

			if (DEBUG){
				printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
			}

			gainCard(choice1, state, 0, currentPlayer);//Gain the card
			x = 0;//No more buying cards

			if (DEBUG){
				printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
			}

		}
	}     

	//Reset Hand
	for (i = 0; i <= state->handCount[currentPlayer]; i++){
		state->hand[currentPlayer][i] = temphand[i];
		temphand[i] = -1;
	}
	//Reset Hand

	return 0;
}

int Gardens(){
	return 0;
}

int Mine(struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos){
	int j;
	int i;
	j = state->hand[currentPlayer][choice1];  //store card we will trash

	if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
	{
		return -1;
	}

	if (choice2 > treasure_map || choice2 < curse)
	{
		return -1;
	}

	if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
	{
		return -1;
	}

	gainCard(choice2, state, 2, currentPlayer);

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	//discard trashed card
	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == j)
		{
			discardCard(i, currentPlayer, state, 0);			
			break;
		}
	}

	return 0;
}

int Remodel(struct gameState *state, int choice1, int choice2, int currentPlayer, int handPos){
	int i;
	int j;

	j = state->hand[currentPlayer][choice1];  //store card we will trash

	if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
	{
		return -1;
	}

	gainCard(choice2, state, 0, currentPlayer);

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	//discard trashed card
	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == j)
		{
			discardCard(i, currentPlayer, state, 0);			
			break;
		}
	}


	return 0;
}	

int Smithy(int currentPlayer, struct gameState *state, int handPos){
	//+3 Cards
	int i;
	for (i = 0; i < 3; i++)
	{
		drawCard(currentPlayer, state);
	}

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}

int Village(int currentPlayer, struct gameState *state, int handPos){
	//+1 Card
	drawCard(currentPlayer, state);

	//+2 Actions
	state->numActions = state->numActions + 2;

	//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}		

int Baron(struct gameState *state, int choice1, int currentPlayer){
	state->numBuys++;//Increase buys by 1!
	if (choice1 > 0){//Boolean true or going to discard an estate
		int p = 0;//Iterator for hand!
		int card_not_discarded = 1;//Flag for discard set!
		while(card_not_discarded){
			if (state->hand[currentPlayer][p] == estate){//Found an estate card!
				state->coins += 4;//Add 4 coins to the amount of coins
				state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
				state->discardCount[currentPlayer]++;
				for (;p < state->handCount[currentPlayer]; p++){
					state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
				}
				state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
				state->handCount[currentPlayer]--;
				card_not_discarded = 0;//Exit the loop
			}
			else if (p > state->handCount[currentPlayer]){
				if(DEBUG) {
					printf("No estate cards in your hand, invalid choice\n");
					printf("Must gain an estate if there are any\n");
				}
				if (supplyCount(estate, state) > 0){
					gainCard(estate, state, 0, currentPlayer);
					state->supplyCount[estate]--;//Decrement estates
					if (supplyCount(estate, state) == 0){
						isGameOver(state);
					}
				}
				card_not_discarded = 0;//Exit the loop
			}

			else{
				p++;//Next card
			}
		}
	}

	else{
		if (supplyCount(estate, state) > 0){
			gainCard(estate, state, 0, currentPlayer);//Gain an estate
			state->supplyCount[estate]--;//Decrement Estates
			if (supplyCount(estate, state) == 0){
				isGameOver(state);
			}
		}
	}

	return 0;
}

int Great_hall(int currentPlayer, struct gameState *state, int handPos){
	//+1 Card
	drawCard(currentPlayer, state);

	//+1 Actions
	state->numActions++;

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}

int Minion(struct gameState *state, int handPos, int currentPlayer, int choice1, int choice2){
	int i;
	int j;
	//+1 action
	state->numActions++;

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	if (choice1)		//+2 coins
	{
		state->coins = state->coins + 2;
	}

	else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
	{
		//discard hand
		while(numHandCards(state) > 0)
		{
			discardCard(handPos, currentPlayer, state, 0);
		}

		//draw 4
		for (i = 0; i < 4; i++)
		{
			drawCard(currentPlayer, state);
		}

		//other players discard hand and redraw if hand size > 4
		for (i = 0; i < state->numPlayers; i++)
		{
			if (i != currentPlayer)
			{
				if ( state->handCount[i] > 4 )
				{
					//discard hand
					while( state->handCount[i] > 0 )
					{
						discardCard(handPos, i, state, 0);
					}

					//draw 4
					for (j = 0; j < 4; j++)
					{
						drawCard(i, state);
					}
				}
			}
		}

	}
	return 0;
}

int Steward(int choice1, int currentPlayer, struct gameState *state, int choice2, int choice3, int handPos){
	if (choice1 == 1)
	{
		//+2 cards
		drawCard(currentPlayer, state);
		drawCard(currentPlayer, state);
	}
	else if (choice1 == 2)
	{
		//+2 coins
		state->coins = state->coins + 2;
	}
	else
	{
		//trash 2 cards in hand
		discardCard(choice2, currentPlayer, state, 1);
		discardCard(choice3, currentPlayer, state, 1);
	}

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}	

int Tribute(struct gameState *state, int *tributeRevealedCards, int nextPlayer, int currentPlayer){
	int i;
	if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1){
		if (state->deckCount[nextPlayer] > 0){
			tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
			state->deckCount[nextPlayer]--;
		}
		else if (state->discardCount[nextPlayer] > 0){
			tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
			state->discardCount[nextPlayer]--;
		}
		else{
			//No Card to Reveal
			if (DEBUG){
				printf("No cards to reveal\n");
			}
		}
	}

	else{
		if (state->deckCount[nextPlayer] == 0){
			for (i = 0; i < state->discardCount[nextPlayer]; i++){
				state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
				state->deckCount[nextPlayer]++;
				state->discard[nextPlayer][i] = -1;
				state->discardCount[nextPlayer]--;
			}

			shuffle(nextPlayer,state);//Shuffle the deck
		} 
		tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
		state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
		state->deckCount[nextPlayer]--;
		tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
		state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
		state->deckCount[nextPlayer]--;
	}    

	if (tributeRevealedCards[0] == tributeRevealedCards[1]){//If we have a duplicate card, just drop one 
		state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
		state->playedCardCount++;
		tributeRevealedCards[1] = -1;
	}

	for (i = 0; i <= 2; i ++){
		if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold){//Treasure cards
			state->coins += 2;
		}

		else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall){//Victory Card Found
			drawCard(currentPlayer, state);
			drawCard(currentPlayer, state);
		}
		else{//Action Card
			state->numActions = state->numActions + 2;
		}
	}

	return 0;
}

int Ambassador(int choice2, int choice1, int handPos, struct gameState *state, int currentPlayer){
	int i;
	int j;
	j = 0;		//used to check if player has enough cards to discard

	if (choice2 > 2 || choice2 < 0)
	{
		return -1;				
	}

	if (choice1 == handPos)
	{
		return -1;
	}

	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
		{
			j++;
		}
	}
	if (j < choice2)
	{
		return -1;				
	}

	if (DEBUG) 
		printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

	//increase supply count for choosen card by amount being discarded
	state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

	//each other player gains a copy of revealed card
	for (i = 0; i < state->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			gainCard(state->hand[currentPlayer][choice1], state, 0, i);
		}
	}

	//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);			

	//trash copies of cards returned to supply
	for (j = 0; j < choice2; j++)
	{
		for (i = 0; i < state->handCount[currentPlayer]; i++)
		{
			if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
			{
				discardCard(i, currentPlayer, state, 1);
				break;
			}
		}
	}			

	return 0;
}

int Cutpurse(int handPos, int currentPlayer, struct gameState *state){

	int i;
	int j;
	int k;
	updateCoins(currentPlayer, state, 2);
	for (i = 0; i < state->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			for (j = 0; j < state->handCount[i]; j++)
			{
				if (state->hand[i][j] == copper)
				{
					discardCard(j, i, state, 0);
					break;
				}
				if (j == state->handCount[i])
				{
					for (k = 0; k < state->handCount[i]; k++)
					{
						if (DEBUG)
							printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
					}	
					break;
				}		
			}

		}

	}				

	//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);			

	return 0;

}

int Embargo(struct gameState *state, int choice1, int handPos, int currentPlayer){ 
	//+2 Coins
	state->coins = state->coins + 2;

	//see if selected pile is in play
	if ( state->supplyCount[choice1] == -1 )
	{
		return -1;
	}

	//add embargo token to selected supply pile
	state->embargoTokens[choice1]++;

	//trash card
	discardCard(handPos, currentPlayer, state, 1);		
	return 0;
}	

int Outpost(struct gameState *state, int handPos, int currentPlayer){
	//set outpost flag
	state->outpostPlayed++;

	//discard card
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}

int Salvager(struct gameState *state, int choice1, int currentPlayer, int handPos){
	//+1 buy
	state->numBuys++;

	if (choice1)
	{
		//gain coins equal to trashed card
		state->coins = state->coins + getCost( handCard(choice1, state) );
		//trash card
		discardCard(choice1, currentPlayer, state, 1);	
	}

	//discard card
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}

int Sea_hag(struct gameState *state, int currentPlayer){
	int i; 
	for (i = 0; i < state->numPlayers; i++){
		if (i != currentPlayer){
			state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];			   
			state->deckCount[i]--;
			state->discardCount[i]++;
			state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
		}
	}
	return 0;
}

int Treasure_map(int currentPlayer, struct gameState *state, int handPos){
	int index;
	int i;
	//search hand for another treasure_map
	index = -1;
	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == treasure_map && i != handPos)
		{
			index = i;
			break;
		}
	}
	if (index > -1)
	{
		//trash both treasure cards
		discardCard(handPos, currentPlayer, state, 1);
		discardCard(index, currentPlayer, state, 1);

		//gain 4 Gold cards
		for (i = 0; i < 4; i++)
		{
			gainCard(gold, state, 1, currentPlayer);
		}

		//return success
		return 1;
	}

	//no second treasure_map found in hand
	return -1;
}


#endif
