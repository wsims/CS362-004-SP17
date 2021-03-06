/*
 * randomtestcard1.c
 * Author: Will Sims
 * Random testing of the village
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int assertTrue (testVar, testResult) {
  if (! testVar) {
    testResult = 0;
    	printf("Test failure.\n");
  }
  return testResult;
}

int assertTrueName(int testVar, int testResult, char *testName) {
  if (! testVar) {
    testResult = 0;
    	printf("%s - FAILED\n", testName);
  }
  return testResult;
}

int main(){
    int testResult = 1;
    int seed = 1;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    char* testName = malloc(256);
    int n, i, p, handCount, deckCount, numActions;
    SelectStream(2);
    PutSeed(3);
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    struct gameState G;

    p = 0;
    int numPlayers = rand() % 4 + 1;
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Random Testing Card: %s ----------------\n", TESTCARD);

    for (n = 0; n < 2000; n++){

      initializeGame(numPlayers, k, seed, &G);

      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = floor(Random() * MAX_HAND);
      G.numActions = floor(Random() * MAX_HAND);
      G.whoseTurn = p;

      //create randomized hand
      for (i = 0; i < G.handCount[p]; i++) {
            int randomcard = rand() % 10;
            G.hand[p][i] = k[randomcard];
      }

      //store variables to compare
      handCount = G.handCount[p];
      numActions = G.numActions;
      deckCount = G.deckCount[p];

      //call village function
      cardEffect(village, choice1, choice2, choice3, &G, handPos, &bonus);

      // ----------- TEST 1: +1 Card --------------
      strcpy(testName, "TEST 1: +1 Cards ");
      testResult = assertTrueName(G.handCount[p] == handCount, testResult, testName);

      // ----------- TEST 2: 1 Card removed from players pile --------------
      strcpy(testName, "TEST 2: 1 Card removed from players pile ");
      testResult = assertTrueName(G.deckCount[p] == deckCount - 1, testResult, testName);

      // ----------- TEST 3: +2 Action --------------
      strcpy(testName, "TEST 3: +2 Actions ");
      testResult = assertTrueName(G.numActions == numActions + 2, testResult, testName);
  }

  if(testResult)
      printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
  else
      printf("\nTEST FAILED\n\n");

  free(testName);
	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
 