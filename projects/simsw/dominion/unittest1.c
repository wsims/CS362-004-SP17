/*
 * unittest1.c
 *
 * Requirements of initializeGame():
 * Return -1 for invalid game states in intilization
 * No repeat kingdom cards are allowed
 * Games require at least 2 people and at most 4 players
 * The number of Curses in the Supply is 10 for each player beyond the first -- 10 for two players, 20 for
 * three players, 30 for four players, and so on.
 * Victory card piles should be 8 for a 2 player game and 12 for a 3 or 4 player game
 * Copper supply should start at 46 for 2 players, 39 for 3 players, and 32 for 4 player games.
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "initializeGame"

int main() {
  int testResult = 1;

  int i, j, m;
  int state;
  struct gameState G;
  int seed = 1000;
  int numPlayers = 0;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

  // ----------- TEST 1: Check if kingdom cards are set correctly at start of game --------------
  printf("\nTEST 1: Check if kingdom cards are set correctly at start of game\n");
  k[1] = adventurer;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("Check if game state returns -1 when duplicate kingdom cards are passed\n");
  testResult = assertTrue(state == -1, testResult);


  k[1] = embargo;
  printf("\nTEST 2: Check for valid number of players in a game\n");
  numPlayers = -1;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("Check if game state returns -1 when initialized with -1 players.\n");
  testResult = assertTrue(state == -1, testResult);

  numPlayers = 5;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("Check if game state returns -1 when initialized with 5 players.\n");
  testResult = assertTrue(state == -1, testResult);

  numPlayers = 2;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("Check if game is active when initialized with 2 players.\n");
  testResult = assertTrue(state == 0, testResult);
  printf("Check that number of players is correctly set.\n");
  testResult = assertTrue(G.numPlayers == numPlayers, testResult);
  printf("number of players = %d, expected = %d\n", G.numPlayers, numPlayers);

  printf("\nTEST 3: Check for valid curse supplies depending on number of players\n");
  numPlayers = 2;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("2 players\n");
  printf("curse supply = %d, expected = %d\n", G.supplyCount[curse], 10);
  testResult = assertTrue(G.supplyCount[curse] == 10, testResult);

  numPlayers = 3;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("3 players\n");
  printf("curse supply = %d, expected = %d\n", G.supplyCount[curse], 20);
  testResult = assertTrue(G.supplyCount[curse] == 20, testResult);

  numPlayers = 4;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("4 players\n");
  printf("curse supply = %d, expected = %d\n", G.supplyCount[curse], 30);
  testResult = assertTrue(G.supplyCount[curse] == 30, testResult);

  printf("\nTEST 4: Check for valid victory card supplies depending on number of players\n");
  numPlayers = 2;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("2 players\n");
  printf("estate supply = %d, expected = %d\n", G.supplyCount[estate], 8);
  testResult = assertTrue(G.supplyCount[estate] == 8, testResult);
  printf("duchy supply = %d, expected = %d\n", G.supplyCount[duchy], 8);
  testResult = assertTrue(G.supplyCount[duchy] == 8, testResult);
  printf("province supply = %d, expected = %d\n", G.supplyCount[province], 8);
  testResult = assertTrue(G.supplyCount[province] == 8, testResult);

  numPlayers = 3;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("3 players\n");
  printf("estate supply = %d, expected = %d\n", G.supplyCount[estate], 12);
  testResult = assertTrue(G.supplyCount[estate] == 12, testResult);
  printf("duchy supply = %d, expected = %d\n", G.supplyCount[duchy], 12);
  testResult = assertTrue(G.supplyCount[duchy] == 12, testResult);
  printf("province supply = %d, expected = %d\n", G.supplyCount[province], 12);
  testResult = assertTrue(G.supplyCount[province] == 12, testResult);

  numPlayers = 4;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("4 players\n");
  printf("estate supply = %d, expected = %d\n", G.supplyCount[estate], 12);
  testResult = assertTrue(G.supplyCount[estate] == 12, testResult);
  printf("duchy supply = %d, expected = %d\n", G.supplyCount[duchy], 12);
  testResult = assertTrue(G.supplyCount[duchy] == 12, testResult);
  printf("province supply = %d, expected = %d\n", G.supplyCount[province], 12);
  testResult = assertTrue(G.supplyCount[province] == 12, testResult);

  printf("\nTEST 5: Check for valid copper supplies depending on number of players\n");
  numPlayers = 2;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("2 players\n");
  printf("copper supply = %d, expected = %d\n", G.supplyCount[copper], 46);
  testResult = assertTrue(G.supplyCount[copper] == 46, testResult);

  numPlayers = 3;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("3 players\n");
  printf("copper supply = %d, expected = %d\n", G.supplyCount[copper], 39);
  testResult = assertTrue(G.supplyCount[copper] == 39, testResult);

  numPlayers = 4;
  state = initializeGame(numPlayers, k, seed, &G);
  printf("4 players\n");
  printf("copper supply = %d, expected = %d\n", G.supplyCount[copper], 32);
  testResult = assertTrue(G.supplyCount[copper] == 32, testResult);


  if(testResult)
      printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
  else
      printf("TEST FAILED\n\n");

	return 0;
}
