/*
 * cardtest2.c
 * Author: Will Sims
 * Testing the adventurer card
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
  int newCards = 0;
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
    sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  // ----------- TEST 1: +2 Cards --------------
  printf("TEST 1: +2 Cards\n");
  newCards = 2;
  printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
  testResult = assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, testResult);

  // ----------- TEST 2: 2 Cards removed from players pile --------------
  printf("TEST 2: At least 2 Cards removed from players pile\n");
  printf("deck count should be equal or less than expected = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
  testResult = assertTrue(testG.deckCount[thisPlayer] <= G.deckCount[thisPlayer] - newCards + shuffledCards, testResult);

  // ----------- TEST 3: 2 treasure cards in hand --------------
  printf("TEST 3: Cards in players hand\n");
  printf("checking if first card is a treasure card\n");
  testResult = assertTrue(testG.hand[0][testG.handCount[0]-1] == copper || testG.hand[0][testG.handCount[0]-1] == silver || testG.hand[0][testG.handCount[0]-1] == gold, testResult);

  printf("checking if second card is a treasure card\n");
  testResult = assertTrue(testG.hand[0][testG.handCount[0]-2] == copper || testG.hand[0][testG.handCount[0]-2] == silver || testG.hand[0][testG.handCount[0]-2] == gold, testResult);

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
