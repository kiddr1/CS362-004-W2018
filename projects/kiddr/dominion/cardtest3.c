/* Riam Sangdoung
* CS 362 W 2018: Assignment 3 - cardtest3.c
* Smithy
*/

#include "dominion.h"
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

	state->hand[0][0] = smithy;
	state->handCount[0] = 1;
}


int main() {
	srand(RSEED);
	int players, correct, i;
	players = rand() % (MAX_PLAYERS - 2) + 2;
	struct gameState state;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	customInit(players, cards, &state);


	printf("TEST: SMITHY CARD\n\n");
	printf("FULL DECK\n");
	cardEffect(smithy, 0, 0, 0, &state, 0, NULL);
	printf("Print hand: ");
	for (i = 0; i < state.handCount[0]; i++)
		printf("%d ", state.hand[0][i]);
	printf("\n");
	printf("Hand count: %d\n", state.handCount[0]);
	printf("Should be 3\n");
	if (state.handCount[0] == 3)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if smithy was discarded: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == smithy)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Discard count: %d\n", state.discardCount[0]);
	printf("Should be 1\n");
	if (state.discardCount[0] == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if anything else was discarded: ");
	for (i = 0; i < state.discardCount[0]; i++) {
		if (state.discard[0][i] != smithy)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");


	printf("\nEMPTY DECK\n");
	customInit(players, cards, &state);
	for (i = 0; i < state.deckCount[0]; i++) {
		state.discard[0][i] = state.deck[0][i];
		state.discardCount[0]++;
	}
	state.deckCount[0] = 0;
	cardEffect(smithy, 0, 0, 0, &state, 0, NULL);
	printf("Print hand: ");
	for (i = 0; i < state.handCount[0]; i++)
		printf("%d ", state.hand[0][i]);
	printf("\n");
	printf("Hand count: %d\n", state.handCount[0]);
	printf("Should be 3\n");
	if (state.handCount[0] == 3)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if smithy was discarded: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == smithy)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Discard count: %d\n", state.discardCount[0]);
	printf("Should be 1\n");
	if (state.discardCount[0] == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if anything else was discarded: ");
	for (i = 0; i < state.discardCount[0]; i++) {
		if (state.discard[0][i] != smithy)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	return 0;
}
