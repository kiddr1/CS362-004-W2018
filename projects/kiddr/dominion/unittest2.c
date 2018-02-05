/* Riam Sangdoung
 * CS 362 W 2018: Assignment 3 unittest2.c
 * Function: isGameOver():
 *  1. Return 1 if the supply count for province is 0
 *	2. Return 1 if any 3 supply counts are 0
 *  3. Otherwise returns 0
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

  #define TEST_FUNCTION "isGameOver()"

 void unittest2_helper(struct gameState* test, struct gameState* control);

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

 	// ----------- TEST 1: 3 x supplyCount[i] == 0 --------------
 	printf("TEST 1: supplyCount[province] == 0\n");
 	control.supplyCount[province] = 0;

 	// copy the game state to a test case
 	memcpy(&test, &control, sizeof(struct gameState));

 	// call to test TEST_FUNCTION functionality
 	if(isGameOver(&test) == 0)
 		printf("\tFAILED: returned 0, expected = 1\n");

 	// compare results of test with expected results
 	unittest2_helper(&test, &control);

 	// ----------- TEST 2: 3 x supplyCount[i] == 0 --------------
 	printf("TEST 2: 3 x supplyCount[i] == 0\n");

 	control.supplyCount[province] = 5;
 	control.supplyCount[smithy] = 0;
 	control.supplyCount[adventurer] = 0;
 	control.supplyCount[village] = 0;

 	// copy the game state to a test case
 	memcpy(&test, &control, sizeof(struct gameState));

 	// call to test TEST_FUNCTION functionality
 	if(isGameOver(&test) == 0)
 		printf("\tFAILED: returned 0, expected = 1\n");

 	// compare results of test with expected results
 	unittest2_helper(&test, &control);

 	// ----------- TEST 3: neither supplyCount[province] == 0 nor 3 x supplyCount[i] == 0 --------------
 	printf("TEST 3: neither supplyCount[province] == 0 nor 3 x supplyCount[i] == 0\n");

 	control.supplyCount[smithy] = 5;
 	control.supplyCount[adventurer] = 5;
 	control.supplyCount[village] = 5;

 	// copy the game state to a test case
 	memcpy(&test, &control, sizeof(struct gameState));

 	// call to test TEST_FUNCTION functionality
 	if(isGameOver(&test) == 1)
 		printf("\tFAILED: returned 1, expected = 0\n");

 	// compare results of test with expected results
 	unittest2_helper(&test, &control);


 	printf("\n >>>>> %s Testing Complete <<<<<\n\n", TEST_FUNCTION);

 	return 0;
 }

 void unittest2_helper(struct gameState* test, struct gameState* control)
 {
     int i, j;

     //Compare values of each attribute of the test gameState with an expected value
     //All values should remain the same as before running test (same as control)
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

   	if(test->playedCardCount != control->playedCardCount)
   		printf("\tFAILED: playedCardCount = %d, expected = %d\n", test->playedCardCount, control->playedCardCount);

   	for(i = 0; i < test->playedCardCount; i++)
   	{
   		if(test->playedCards[i] != control->playedCards[i])
   			printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], control->playedCards[i]);
   	}
 }
