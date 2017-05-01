/*
 * unittest2.c
 *
`* numHandCards Requirements:
 * Returns the correct number of cards based on whose turn it is. `
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "numHandCards"

int main() {
  int testResult = 1;

  int i, j, m;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 1000;
  int numPlayers = 3;
  int thisPlayer = 0;
  struct gameState G;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int numCards = 999; //Arbitrary default value, since I'm also testing 0.

  initializeGame(numPlayers, k, seed, &G);
  G.whoseTurn = thisPlayer;
  G.handCount[0] = -9;
  G.handCount[1] = 0;
  G.handCount[2] = 50;

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
  // ----------- TEST 1: Check if correct number of cards is returned for player 1 --------------
  printf("\nTEST 1: Check if correct number of cards is returned for player 1");

  printf("Checking cards in player 1's hand\n");
  numCards = numHandCards(&G);
  testResult = assertTrue(numCards == -9, testResult);
  printf("player 1 hand count: %d, expected: -9\n", numCards);

  // ----------- TEST 2: Check if correct number of cards is returned for player 2 --------------
  printf("\nTEST 2: Check if correct number of cards is returned for player 2");
  G.whoseTurn = 1; //Change to player 2
  printf("Checking cards in player 2's hand\n");
  numCards = numHandCards(&G);
  testResult = assertTrue(numCards == 0, testResult);
  printf("player 2 hand count: %d, expected: 0\n", numCards);

  // ----------- TEST 3: Check if correct number of cards is returned for player 3 --------------
  printf("\nTEST 3: Check if correct number of cards is returned for player 3");
  G.whoseTurn = 2; //Change to player 2
  printf("Checking cards in player 3's hand\n");
  numCards = numHandCards(&G);
  testResult = assertTrue(numCards == 50, testResult);
  printf("player 3 hand count: %d, expected: 50\n", numCards);


  if(testResult)
      printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
  else
      printf("\nTEST FAILED\n\n");

	return 0;
}
