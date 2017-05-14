/*
 * randomtestcard1.c
 * Author: Will Sims
 * Random testing of the adventurer card
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

#define TESTCARD "adventurer"

int main(){
    int testResult = 1;
    int seed = 1;
    int handPos = 0;
    char* testName = malloc(256);
    int n, i, p, handCount, deckCount;
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
      for (i = 0; i < 5; i++) {
            int randomcard = rand() % 10;
            G.hand[p][i] = k[randomcard];
      }

      //store variables to compare
      handCount = G.handCount[p];
      deckCount = G.deckCount[p];

      //call village function
      playAdventurer(&G);

      // ----------- TEST 1: +2 Card --------------
      strcpy(testName, "TEST 1: +2 Cards ");
      testResult = assertTrueName(G.handCount[p] == handCount + 1, testResult, testName);

      // ----------- TEST 2: 1 Card removed from players pile --------------
      strcpy(testName, "TEST 2: At least 2 Cards removed from players pile ");
      testResult = assertTrueName(G.deckCount[p] < deckCount, testResult, testName);

       // ----------- TEST 3 & 4: 2 treasure cards in hand --------------
       strcpy(testName, "TEST 3: Checking if first card is a treasure card ");
       testResult = assertTrueName(G.hand[p][G.handCount[p]-1] == copper || G.hand[p][G.handCount[p]-1] == silver || G.hand[p][G.handCount[p]-1] == gold, testResult, testName);

       strcpy(testName, "TEST 4: Checking if second card is a treasure card ");
       testResult = assertTrueName(G.hand[p][G.handCount[p]-2] == copper || G.hand[p][G.handCount[p]-2] == silver || G.hand[p][G.handCount[0]-2] == gold, testResult, testName);
  }

  if(testResult)
      printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
  else
      printf("\nTEST FAILED\n\n");

  free(testName);
	return 0;
}

