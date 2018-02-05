/* Riam Sangdoung
* CS 362 W 2018: Assignment 3 - cardtest3.c
* Village
*/

#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#define RSEED 5


void customInit (int players, int cards[10], struct gameState *state) {
	initializeGame(players, cards, RSEED, state);
	int i;
	for (i = 0; i < players; i++) {
		state->handCount[i] = 0;
		state->discardCount[i] = 0;
	}
	state->hand[0][0] = village;
	state->handCount[0] = 1;
}


int main() {
	srand(RSEED);
	int players, curActions, correct, i;
	players = rand() % (MAX_PLAYERS - 2) + 2;
	struct gameState state;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	customInit(players, cards, &state);

	printf("TEST: VILLAGE CARD\n\n");
	curActions = state.numActions;
	cardEffect(village, 0, 0, 0, &state, 0, NULL);
	printf("Actions: %d\n", state.numActions);
	printf("Should be %d\n", curActions + 2);
	if (state.numActions == curActions + 2)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Hand count: %d\n", state.handCount[0]);
	printf("Should be 1\n");
	if (state.handCount[0] == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Discard count: %d\n", state.discardCount[0]);
	printf("Should be 1\n");
	if (state.discardCount[0] == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	correct = 0;
	printf("Village in discard pile: ");
	for (i = 0; i < state.discardCount[0]; i++) {
		if (state.discard[0][i] == village)
			correct = 1;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");


	return 0;
}
