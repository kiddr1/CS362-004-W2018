/* Riam Sangdoung
 * CS 362 W 2018: Assignment 3 unittest4.c
 * Function: endTurn():
 *  1. Discard currentPlayer's hand to discard deck
 *	2. Reset gamestate attributes for the next turn
 *  3. Start next players turn by drawing their hand and updating coins
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TEST_FUNCTION "endTurn()"

void unittest4_helper(struct gameState* test, struct gameState* control, int currentPlayer, int nextPlayer);

int main()
{
  int seed = 1000;
  int numPlayers = 2;
	struct gameState control, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// Initialize a game state
	initializeGame(numPlayers, k, seed, &control);

	printf("----------------- Testing Function: %s ----------------\n", TEST_FUNCTION);

	int currentPlayer = whoseTurn(&control);
	int nextPlayer = (whoseTurn(&control) + 1) % numPlayers;

	// ----------- TEST 1: discard currentPlayer hand and will start next player's turn --------------
	printf("TEST 1: discard currentPlayer hand, start next players turn\n");

	// Sets the currentPlayer's hand and deck
	control.hand[currentPlayer][0] = copper;
	control.hand[currentPlayer][1] = copper;
	control.hand[currentPlayer][2] = copper;
	control.hand[currentPlayer][3] = copper;
	control.hand[currentPlayer][4] = copper;
	control.handCount[currentPlayer] = 5;

	control.deck[nextPlayer][0] = copper;
	control.deck[nextPlayer][1] = copper;
	control.deck[nextPlayer][2] = copper;
	control.deck[nextPlayer][3] = copper;
	control.deck[nextPlayer][4] = copper;
	control.deckCount[nextPlayer] = 5;
	control.handCount[nextPlayer] = 0;

	// Will copy game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));

	// Call to test TEST_FUNCTION functionality
	endTurn(&test);

	// Compare results of test with expected results
	unittest4_helper(&test, &control, currentPlayer, nextPlayer);

	printf("\n >>>>> %s Testing Complete <<<<<\n\n", TEST_FUNCTION);

	return 0;
}

void unittest4_helper(struct gameState* test, struct gameState* control, int currentPlayer, int nextPlayer)
{
    int i, j;

    //Compare values of each attribute of the test gameState with an expected value
   	if(test->numPlayers != control->numPlayers)
  		printf("\tFAILED: numPlayers = %d, expected = %d\n", test->numPlayers, control->numPlayers);

  	for(i = 0; i < (treasure_map + 1); i++)
  	{
  		if(test->supplyCount[i] != control->supplyCount[i])
  			printf("\tFAILED: supplyCount[%d] = %d, expected = %d\n", i, test->supplyCount[i], control->supplyCount[i]);
  	}

  	for(i = 0; i < (treasure_map + 1); i++)
  	{
  		if(test->embargoTokens[i] != control->embargoTokens[i])
  			printf("\tFAILED: embargoTokens[%d] = %d, expected = %d\n", i, test->embargoTokens[i], control->embargoTokens[i]);
  	}

  	if(test->outpostPlayed != 0)
  		printf("\tFAILED: outpostPlayed = %d, expected = %d\n", test->outpostPlayed, 0);

  	if(test->outpostTurn != control->outpostTurn)
  		printf("\tFAILED: outpostTurn = %d, expected = %d\n", test->outpostTurn, control->outpostTurn);

  	if(test->whoseTurn != nextPlayer)
  		printf("\tFAILED: whoseTurn = %d, expected = %d\n", test->whoseTurn, nextPlayer);

  	if(test->phase != 0)
  		printf("\tFAILED: phase = %d, expected = %d\n", test->phase, 0);

  	if(test->numActions != 1)
  		printf("\tFAILED: numActions = %d, expected = %d\n", test->numActions, 1);

  	if(test->coins != 5)
  		printf("\tFAILED: coins = %d, expected = %d\n", test->coins, 5);

  	if(test->numBuys != 1)
  		printf("\tFAILED: numBuys = %d, expected = %d\n", test->numBuys, 1);

  	for(i = 0; i < MAX_PLAYERS; i++)
  	{
  		if(i == currentPlayer)
  		{
  			if(test->handCount[currentPlayer] != 0)
  				printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[currentPlayer], 0);

	  		if(test->deckCount[currentPlayer] != control->deckCount[currentPlayer])
	  			printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", currentPlayer, test->deckCount[currentPlayer], control->deckCount[currentPlayer]);

		  	for(j = 0; j < test->deckCount[currentPlayer]; j++)
		  	{
		  		if(test->deck[currentPlayer][j] != control->deck[currentPlayer][j])
		  			printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->deck[currentPlayer][j], control->deck[currentPlayer][j]);
		  	}

		  	if(test->discardCount[currentPlayer] != control->discardCount[currentPlayer] + control->handCount[currentPlayer])
		  		printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer], control->discardCount[currentPlayer] + control->handCount[currentPlayer]);

		  	for(j = 0; j < test->discardCount[currentPlayer]; j++)
		  	{
		  		if(j > control->discardCount[currentPlayer] - 1)
		  		{
		  			if(test->discard[currentPlayer][j] != copper)
		  				printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, j, test->discard[currentPlayer][j], control->discard[currentPlayer][j]);
		  		}
		  		else
		  		{
		  			if(test->discard[currentPlayer][j] != control->discard[currentPlayer][j])
		  				printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, j, test->discard[currentPlayer][j], control->discard[currentPlayer][j]);
		  		}
		  	}
  		}
  		else if(i == nextPlayer)
  		{
  			if(test->handCount[nextPlayer] != 5)
  				printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[nextPlayer], 5);

	  		if(test->deckCount[nextPlayer] != 0)
	  			printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", nextPlayer, test->deckCount[nextPlayer], 0);

		  	if(test->discardCount[nextPlayer] != control->discardCount[nextPlayer])
		  		printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", nextPlayer, test->discardCount[nextPlayer], control->discardCount[nextPlayer]);

		  	for(j = 0; j < test->discardCount[nextPlayer]; j++)
		  	{
		  		if(test->discard[nextPlayer][j] != control->discard[nextPlayer][j])
		  			printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", nextPlayer, j, test->discard[nextPlayer][j], control->discard[nextPlayer][j]);
		  	}
  		}
  		else
  		{
	  		if(test->handCount[i] != control->handCount[i])
	  			printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[i], control->handCount[i]);

	  		for(j = 0; j < test->handCount[i]; j++)
	  		{
	  			if(test->hand[i][j] != control->hand[i][j])
	  				printf("\tFAILED: hand[%d][%d] = %d, expected = %d\n", i, j, test->hand[i][j], control->hand[i][j]);
	  		}

	  		if(test->deckCount[i] != control->deckCount[i])
	  			printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", i, test->deckCount[i], control->deckCount[i]);

	  		for(j = 0; j < test->deckCount[i]; j++)
	  		{
	  			if(test->deck[i][j] != control->deck[i][j])
	  				printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", i, j, test->deck[i][j], control->deck[i][j]);
	  		}

	  		if(test->discardCount[i] != control->discardCount[i])
	  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", i, test->discardCount[i], control->discardCount[i]);

	  		for(j = 0; j < test->discardCount[i]; j++)
	  		{
	  			if(test->discard[i][j] != control->discard[i][j])
	  				printf("\tFAILED: discard[%d][%d] = %d, expected = %d\n", i, j, test->discard[i][j], control->discard[i][j]);
	  		}

	  	}
  	}

  	if(test->playedCardCount != 0)
  		printf("\tFAILED: playedCardCount = %d, expected = %d\n", test->playedCardCount, 0);
}
