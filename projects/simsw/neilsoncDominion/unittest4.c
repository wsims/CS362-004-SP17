/*
 * unittest4.c
 * isGameOver Requirements:
 * Game should be over whenever there are three or more piles empty or the
 * province pile is empty.
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver"

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

int main() {
  int testResult = 1;
  int endGame;

  int seed = 1000;
  int numPlayers = 2;
  struct gameState G;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
  // ----------- TEST 1: Check if correct number of cards is returned for player 1 --------------
  printf("\nTEST 1: Check if the game doesn't end with full piles\n");
  printf("The game should not end\n");
  endGame = isGameOver(&G);
  testResult = assertTrue(endGame == 0, testResult);

  printf("\nTEST 2: If the province pile is empty then the game should end\n");
  G.supplyCount[province] = 0;
  printf("The game should end\n");
  endGame = isGameOver(&G);
  testResult = assertTrue(endGame == 1, testResult);

  initializeGame(numPlayers, k, seed, &G);
  printf("\nTEST 3: If two piles are empty the game should not end\n");
  G.supplyCount[duchy] = 0;
  G.supplyCount[embargo] = 0;
  printf("The game should end\n");
  endGame = isGameOver(&G);
  testResult = assertTrue(endGame == 0, testResult);

  initializeGame(numPlayers, k, seed, &G);
  printf("\nTEST 4: If three piles are empty the game should end\n");
  G.supplyCount[gold] = 0;
  G.supplyCount[duchy] = 0;
  G.supplyCount[silver] = 0;
  printf("The game should end\n");
  endGame = isGameOver(&G);
  testResult = assertTrue(endGame == 1, testResult);

  initializeGame(numPlayers, k, seed, &G);
  printf("\nTEST 5: If four piles are empty the game should end\n");
  G.supplyCount[curse] = 0;
  G.supplyCount[embargo] = 0;
  G.supplyCount[village] = 0;
  G.supplyCount[minion] = 0;
  printf("The game should end\n");
  endGame = isGameOver(&G);
  testResult = assertTrue(endGame == 1, testResult);

  if(testResult)
      printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
  else
      printf("\nTEST FAILED\n\n");

	return 0;
}

                                                                                                                                            