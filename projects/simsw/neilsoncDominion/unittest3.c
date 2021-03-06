/*
 * unittest3.c
 *
 * Requirements of kingdomCards():
 * Correctly set the array of kingdomCards when passed 10 integers
 * Error checking for valid cards should be done beforehand.
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "kingdomCards"

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

  int i, j, m;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int remove1, remove2;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

  printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
  // ----------- TEST 1: Check if the array returned is the same as what was passed --------------
  printf("\nTEST 1: Check if kingdom cards are set when passed 10 integers\n");
  int *testKingdomCards = kingdomCards(k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9]);
  printf("Check if kingdom cards are set correctly when passed 10 integers.\n");
  for (i = 0; i < 10; i++) {
    testResult = assertTrue(k[i] == testKingdomCards[i], testResult);
    printf("%d. card %d, expected = %d\n", i+1, testKingdomCards[i], k[i]);
  }

  if(testResult)
      printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
  else
      printf("\nTEST FAILED\n\n");

	return 0;
}
                                                                                                  