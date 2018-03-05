/* Riam Sangdoung
 * CS 362 W 2018: Assignment 3 unittest3.c
 * Function: discardCard() criteria:
 *  1. Remove a given card from current players hand
 *	2. Place discarded card played into current player's discard deck
 *  3. Place discarded card played into current player's playedCards
 *	4. No changes to game state
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

#define TEST_FUNCTION "discardCard()"

void unittest3_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool trashFlag);

int main()
{
    int seed = 1000;
    int numPlayers = 2;
	struct gameState control, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state
	initializeGame(numPlayers, k, seed, &control);

	printf("----------------- Testing Function: %s ----------------\n", TEST_FUNCTION);

	int currentPlayer = whoseTurn(&control);

	// ----------- TEST 1: Discard card at end of Hand --------------
	printf("TEST 1: Discard card at end of Hand\n");

	//set currentPlayer's hand and deck
	control.hand[currentPlayer][0] = copper;
	control.hand[currentPlayer][1] = copper;
	control.hand[currentPlayer][2] = copper;
	control.hand[currentPlayer][3] = copper;
	control.hand[currentPlayer][4] = silver;
	control.handCount[currentPlayer] = 5;

	control.deck[currentPlayer][0] = gold;
	control.deckCount[currentPlayer] = 1;

	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));

	// call to test TEST_FUNCTION functionality
	discardCard(4, currentPlayer, &test, 0);

	// compare results of test with expected results
	unittest3_helper(&test, &control, currentPlayer, false);

	// ----------- TEST 2: Discard only card in hand --------------
	printf("TEST 2: Discard only card in hand\n");
	//set currentPlayer's hand and deck
	control.hand[currentPlayer][0] = silver;
	control.handCount[currentPlayer] = 1;

	control.deck[currentPlayer][0] = gold;
	control.deckCount[currentPlayer] = 1;

	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));

	// call to test TEST_FUNCTION functionality
	discardCard(0, currentPlayer, &test, 0);

	// compare results of test with expected results
	unittest3_helper(&test, &control, currentPlayer, false);

	// ----------- TEST 3: Discard card in middle of hand --------------
	printf("TEST 3: Discard card in middle of Hand\n");

	//set currentPlayer's hand and deck
	control.hand[currentPlayer][0] = copper;
	control.hand[currentPlayer][1] = copper;
	control.hand[currentPlayer][2] = silver;
	control.hand[currentPlayer][3] = copper;
	control.hand[currentPlayer][4] = mine;
	control.handCount[currentPlayer] = 5;

	control.deck[currentPlayer][0] = gold;
	control.deckCount[currentPlayer] = 1;

	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));

	// call to test TEST_FUNCTION functionality
	discardCard(2, currentPlayer, &test, 0);

	// compare results of test with expected results
	unittest3_helper(&test, &control, currentPlayer, false);

	// ----------- TEST 4: Trash card in middle of hand --------------
	printf("TEST 4: Trash card in middle of Hand\n");

	//set currentPlayer's hand and deck
	control.hand[currentPlayer][0] = copper;
	control.hand[currentPlayer][1] = copper;
	control.hand[currentPlayer][2] = silver;
	control.hand[currentPlayer][3] = copper;
	control.hand[currentPlayer][4] = mine;
	control.handCount[currentPlayer] = 5;

	control.deck[currentPlayer][0] = gold;
	control.deckCount[currentPlayer] = 1;

	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));

	// call to test TEST_FUNCTION functionality
	discardCard(2, currentPlayer, &test, 1);

	// compare results of test with expected results
	unittest3_helper(&test, &control, currentPlayer, true);

	printf("\n >>>>> %s Testing Complete <<<<<\n\n", TEST_FUNCTION);

	return 0;
}

void unittest3_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool trashFlag)
{
    int discardedCards = 1;
    int i, j;

    //Compare values of each attribute of the test gameState with an expected value
    //Almost All values should remain the same as before running test (same as control)
    //Exceptions: hand, handCount, deck, deckCount, discard, discardCount, playedCards, playedCardCount
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

  	if(test->outpostPlayed != control->outpostPlayed)
  		printf("\tFAILED: outpostPlayed = %d, expected = %d\n", test->outpostPlayed, control->outpostPlayed);

  	if(test->outpostTurn != control->outpostTurn)
  		printf("\tFAILED: outpostTurn = %d, expected = %d\n", test->outpostTurn, control->outpostTurn);

  	if(test->whoseTurn != control->whoseTurn)
  		printf("\tFAILED: whoseTurn = %d, expected = %d\n", test->whoseTurn, control->whoseTurn);

  	if(test->phase != control->phase)
  		printf("\tFAILED: phase = %d, expected = %d\n", test->phase, control->phase);

  	if(test->numActions != control->numActions)
  		printf("\tFAILED: numActions = %d, expected = %d\n", test->numActions, control->numActions);

  	if(test->coins != control->coins)
  		printf("\tFAILED: coins = %d, expected = %d\n", test->coins, control->coins);

  	if(test->numBuys != control->numBuys)
  		printf("\tFAILED: numBuys = %d, expected = %d\n", test->numBuys, control->numBuys);

  	for(i = 0; i < MAX_PLAYERS; i++)
  	{
  		if(i == currentPlayer)
  		{
  			if(test->handCount[currentPlayer] != control->handCount[currentPlayer] - discardedCards)
  				printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[currentPlayer], control->handCount[i]);

  			for(j = 0; j < test->handCount[currentPlayer]; j++)
	  		{
	  			if(test->hand[currentPlayer][j] == silver)
	  					printf("\tFAILED: hand[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->hand[i][j], silver);
	  		}

	  		if(test->deckCount[currentPlayer] != control->deckCount[currentPlayer])
	  			printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", currentPlayer, test->deckCount[currentPlayer], control->deckCount[currentPlayer]);

		  	for(j = 0; j < test->deckCount[currentPlayer]; j++)
		  	{
		  		if(test->deck[currentPlayer][j] != control->deck[currentPlayer][j])
		  			printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->deck[currentPlayer][j], control->deck[currentPlayer][j]);
		  	}

	  		if(test->discardCount[currentPlayer] != control->discardCount[currentPlayer] + discardedCards)
	  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer], control->discardCount[currentPlayer] + discardedCards);

	  		for(j = 0; j < test->discardCount[currentPlayer] - 1; j++)
	  		{
	  			if(test->discard[currentPlayer][j] != control->discard[currentPlayer][j])
	  				printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, j, test->discard[currentPlayer][j], control->discard[currentPlayer][j]);
	  		}

	  		if(test->discard[currentPlayer][test->discardCount[currentPlayer] - 1] - 1 != silver)
  				printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer] - 1, test->discard[currentPlayer][j], silver);
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

  	if(trashFlag)
  	{
  		if(test->playedCardCount != control->playedCardCount)
  			printf("\tFAILED: playedCardCount = %d, expected = %d\n", test->playedCardCount, control->playedCardCount);

  		for(i = 0; i < test->playedCardCount; i++)
  		{
  			if(test->playedCards[i] != control->playedCards[i])
  				printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], control->playedCards[i]);
  		}
  	}
  	else
  	{
  		if(test->playedCardCount != control->playedCardCount + discardedCards)
  			printf("\tFAILED: playedCardCount = %d, expected = %d\n", test->playedCardCount, control->playedCardCount);

  		for(i = 0; i < test->playedCardCount - 1; i++)
  		{
  			if(test->playedCards[i] != control->playedCards[i])
  				printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], control->playedCards[i]);
  		}

  		if(test->playedCards[i] != silver)
  			printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], silver);

  	}
}
