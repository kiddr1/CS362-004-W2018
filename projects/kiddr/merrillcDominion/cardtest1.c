/* Riam Sangdoung
* CS 362 W 2018: Assignment 3 - cardtest1.c
* Adventurer
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define RSEED 5


void customInit (int players, int cards[10], struct gameState *state) {
	int rseed = time(0);
	initializeGame(players, cards, rseed, state);
	int i;
	for (i = 0; i < players; i++) {
		state->handCount[i] = 0;
		state->discardCount[i] = 0;
		state->deckCount[i] = 0;
	}

	for (i = 0; i < 3; i++) {
		state->deck[0][i] = gold;
		state->deckCount[0]++;
	}
	for (i = 3; i < 6; i++) {
		state->deck[0][i] = silver;
		state->deckCount[0]++;
	}
	for (i = 6; i < 9; i++) {
		state->deck[0][i] = copper;
		state->deckCount[0]++;
	}
	for (i = 9; i < 29; i++) {
		state->deck[0][i] = estate;
		state->deckCount[0]++;
	}
	shuffle(0, state);
	state->hand[0][0] = adventurer;
	state->handCount[0] = 1;
}


int main() {
	int rseed;
	rseed  = time(0);
	srand(rseed);
	int players, correct, i;
	players = rand() % (MAX_PLAYERS - 2) + 2;
	struct gameState state;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	customInit(players, cards, &state);
	printf("TEST: ADVENTURER CARD\n\n");
	//full deck
	printf("FULL DECK\n");
	cardEffect(adventurer, 0, 0, 0, &state, 0, NULL);
	printf("Print hand: ");
	for (i = 0; i < state.handCount[0]; i++)
		printf("%d ", state.hand[0][i]);
	printf("\n");
	printf("Check hand count: %d\n", state.handCount[0]);
	printf("Should be 2\n");
	if (state.handCount[0] == 2)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if non-treasure cards were drawn: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == estate)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if adventurer card was discarded: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == adventurer)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Print discard: ");
	for (i = 0; i < state.discardCount[0]; i++)
		printf("%d ", state.discard[0][i]);
	printf("\n");
	printf("Check that discard pile is only non-treasure cards: ");
	correct = 1;
	if (state.discardCount[0] > 0) {
		for (i = 0; i < state.discardCount[0]; i++) {
			if (state.discard[0][i] != estate && state.discard[0][i] != adventurer)
				correct = 0;
		}
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	//empty deck
	printf("\nEMPTY DECK\n");
	customInit(players, cards, &state);
	for (i = 0; i < state.deckCount[0]; i++) {
		state.discard[0][i] = state.deck[0][i];
		state.discardCount[0]++;
	}
	state.deckCount[0] = 0;
	cardEffect(adventurer, 0, 0, 0, &state, 0, NULL);
	printf("Print hand: ");
	for (i = 0; i < state.handCount[0]; i++)
		printf("%d ", state.hand[0][i]);
	printf("\n");
	printf("Check hand count: %d\n", state.handCount[0]);
	printf("Should be 2\n");
	if (state.handCount[0] == 2)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if non-treasure cards were drawn: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == estate)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Check if adventurer card was discarded: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == adventurer)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Print discard: ");
	for (i = 0; i < state.discardCount[0]; i++)
		printf("%d ", state.discard[0][i]);
	printf("\n");
	printf("Check that discard pile is only non-treasure cards: ");
	correct = 1;
	if (state.discardCount[0] > 0) {
		for (i = 0; i < state.discardCount[0]; i++) {
			if (state.discard[0][i] != estate && state.discard[0][i] != adventurer)
				correct = 0;
		}
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");


	return 0;
}
