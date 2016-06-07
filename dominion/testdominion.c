/*
//Author: 		Jong Park (parkj6)
//Filename:		testdominion.c
//Description: 	
				-Plays complete games of Dominion (seed = 42)
				-Random number of players (2-4)
				-Random set of kingdom cards

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#define breaking printf("********************\n");



int checkCard(int *k, int card){
	int i, j;
	int check = 0;
	
	for (i=0; i<10; i++){
		card = rand() %20 + adventurer;
		for (j = 0; j<i; j++){
			if (card ==k[j]){
				check = 1;
				break;
			}else {
				check =0;
			}
			if(check==1) {
				i--;
			}else {
				k[i] = card;
			}
		}
	}
	return k;
}
	
void createCards(int *k, char *cardName){
	int i;
	for(i=0; i<10; i++){
		cardNumToName(k[i], cardName);
		printf("%s\n", cardName);
	}
}

int winPlayer(struct gameState *g, int *getWin){
	int i, winner;
	for(i=0; i< g->numPlayers; i++){
		printf("Player %d has score of %d\n",i,scoreFor(i,g));
		if(getWin[i] == 1){
			winner = i;
		}
	}
	return winner;
}	
	
int randomPlayers(){
	int players = (rand() % 3) +2;
	return players;
}
	
void testGame(struct gameState *g, char *cardName, int init, int *k){
	int i, coins, curPlayer, curCard, card, cardLocation;
	int actionCard=0;
	
	while(!isGameOver(g)){
		curPlayer = g->whoseTurn;
		printf("Player %d's turn to play.\n",curPlayer);
		cardLocation=0;
		actionCard=0;
		
		for(i=0; i<numHandCards(g);i++){
			if(handCard(i,g) < treasure_map 
			&& handCard(i,g) >= adventurer 
			&& handCard(i,g) != feast
			&& handCard(i,g) != tribute) {
				actionCard = i;
				break;
			}
		}
		
		//Action Stage
		breaking;
		printf("Action Stage.\n");
		while(g->numActions > 0 && actionCard != 0){
			curCard = handCard(i,g);
			cardNumToName(curCard, cardName);
			
			init = playCard(actionCard, -1, -1, -1, g);
			
			if(init == -1){
				discardCard(cardLocation, curPlayer, g, 0);
			}
			else {
				printf("Played card: %s, %d", cardName, curCard);
			}
			if(g->numActions<=0){
				printf("No action cards. Action Phase over\n");
			}
			for (i=actionCard; i< numHandCards(g); i++){
				if(handCard(i,g) < treasure_map 
				&& handCard(i,g) >= adventurer
				&& handCard(i,g) != feast
				&& handCard(i,g) != tribute) {
					actionCard = i;
					break;
				}else {
					actionCard = 0;
				}	
			}
		}
		
		// Buy Stage
		breaking;
		printf("Card Buying Phase.\n");
		coins = 0;
		for (i=0; i<numHandCards(g); i++){
			if(handCard(i,g) == copper)
				coins++;
			else if (handCard(i,g) == silver)
				coins = coins +2;
			else if (handCard(i,g) == gold)
				coins = coins +3;
		}
		
		while(g->numBuys >0 && coins>0){
			do{
				init = rand() % 2;
				cardLocation = rand() % 10;
				
				if(init)
					card = k[cardLocation];
				else
					card = rand() % treasure_map;
			} while (buyCard(card, g) != 0);
			
			cardNumToName(card, cardName);
			printf("Buying Card: %s.\n", cardName);
		}
		
		printf("Buying Stage Over.\n");
		breaking;
		printf("End Turn.\n");
		endTurn(g);
		
	}
	
}
	
//void actionStage(struct gameState *g, char *cardName, int init, int *k)

//void buyStage(struct gameState *g, char *cardName, int init, int *k)
		
int main (int argc, char** argv) {
	srand(time(NULL));
	int players, seed, init, winner;
	int card = 0;
	int getWin[5];
	int k[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	char cardName[20];
	struct gameState *g = newGame();	
	
	if (argv[1] != NULL){
		seed = atoi(argv[1]);
	}else {
		printf ("Enter a seed (default:42): ");
		scanf("%d", &seed);
		seed = 42;
	}
	
	k[10] = checkCard(k, card);
	
	breaking;
	printf("Test Game Starting...\n");
	createCards(k, cardName);
	
	players = randomPlayers();
	g->numPlayers = players;
	
	init = initializeGame(players, k, seed, g);
	if (init == -1){
		printf("Failed to initialize game...\n");
		return -1;
	}
	
	testGame(g, cardName, init, k);
	
	getWinners(getWin, g);	
	breaking;
	printf("Printing Scores\n");
	
	winner = winPlayer(g, getWin);
	printf("The winner is: Player %d\n", winner);
	
	printf("Thanks for playing!");
	return 0;
}
