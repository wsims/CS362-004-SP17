/*
 * cardtest4.c
 * Author: Will Sims
 * Testing the great hall card
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great hall"

int main() {
  int newCards = 0;
  int newActions = 0;
  int discarded = 1;
  int xtraCoins = 0;
  int shuffledCards = 0;
  int testResult = 1;

  int i, j, m;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int remove1, remove2;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, great_hall};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  // ----------- TEST 1: +1 Card --------------
  printf("TEST 1: +1 Cards\n");
  newCards = 1;
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  testResult = assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, testResult);

  // ----------- TEST 2: 1 Card removed from players pile --------------
  printf("TEST 2: 1 Card removed from players pile\n");
  printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  testResult = assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, testResult);

  // ----------- TEST 3: +1 Action --------------
  printf("TEST 3: +1 Actions\n");
  newActions = 1;
  printf("action count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
  testResult = assertTrue(testG.numActions == G.numActions + newActions, testResult);

  // ----------- TEST 4: Other players state shouldn't change --------------
  printf("TEST 4: Other players state shouldn't change and your score should remain the same\n");
  printf("deck count = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
  testResult = assertTrue(testG.deckCount[1] == G.deckCount[1], testResult);

  printf("hand count = %d, expected = %d\n", testG.handCount[1], G.handCount[1]);
  testResult = assertTrue(testG.handCount[1] == G.handCount[1], testResult);

  printf("score = %d, expected = %d\n", scoreFor(thisPlayer, &testG), scoreFor(thisPlayer, &G));
  testResult = assertTrue(scoreFor(thisPlayer, &testG) == scoreFor(thisPlayer, &G), testResult);

  // ----------- TEST 5: Victory and Kingdom card piles --------------
  printf("TEST 5: Victory and Kingdom card piles shouldn't change\n");

  printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
  testResult = assertTrue(testG.supplyCount[estate] == G.supplyCount[estate], testResult);

  printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
  testResult = assertTrue(testG.supplyCount[province] == G.supplyCount[province], testResult);

  printf("duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
  testResult = assertTrue(testG.supplyCount[duchy] == G.supplyCount[duchy], testResult);

  printf("checking if the kingdom card pile is unchanged\n");
  for (i = 0; i < 10; i++) {
    testResult = assertTrue(testG.supplyCount[k[i]] == G.supplyCount[k[i]], testResult);
  }

  if(testResult)
      printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
  else
      printf("\nTEST FAILED\n\n");

	return 0;
}
