//////////////////////////////////////
//UNIT TEST FOR THE TRIBUTE FUNCTION//
//////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"

int assertCheck(int check1, int check2){
    if(check1 == check2){
        printf(" PASSED!\n\n");
        return 1;
    }
    else{
        printf(" FAILED!\n\n");
        return 0;
    }
}

int main(int argc, char* argv[]){
    int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    struct gameState G;
    int seed = 30;
    int player = 1;

    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);
 
    int coinCheck = G.coins+4;

    //TEST 1//
    //Adding 2 Treasure cards to the next player's deck
    printf("TRIBUTE TESTS:\n");
    printf("TEST #1: One Copper and one Silver for Tribute (Treasures)\n");
    gainCard(copper, &G, 1, 1);
    gainCard(silver, &G, 1, 1);

    playTribute(&G, 1, player);
    printf("01: Checking if coins are increased by 4 (+2 for each Treasure)...");
    assertCheck(G.coins, coinCheck);

    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);

    int handCheck = G.handCount[player]+4;

    //TEST 2//
    //Adding 2 Victory cards to the next player's deck
    printf("TEST #2: One Estate and one Duchy for Tribute (Victory)\n");
    gainCard(estate, &G, 1, 1);
    gainCard(duchy, &G, 1, 1);

    playTribute(&G, 1, player);
    printf("02: Checking if 2 cards are drawn for each Victory card...");
    assertCheck(G.handCount[player], handCheck);


    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);

    //TEST 3//
    //Adding 2 Action cards to the next player's deck
    printf("TEST #3: One Minion and one Mine for Tribute (Action)\n");
    gainCard(minion, &G, 1, 1);
    gainCard(mine, &G, 1, 1);

    int actionCheck = G.numActions+4;

    playTribute(&G, 1, player);
    printf("03: Checking if actions are increased by +4 (+2 for each Action card)...");
    assertCheck(G.numActions, actionCheck);

    //TEST 4//
    //Duplicate check
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);

    gainCard(copper, &G, 1, 1);
    gainCard(copper, &G, 1, 1);

    coinCheck = G.coins+2;

    printf("TEST #4: Two Coppers for Tribute (cards of same name)\n");
    playTribute(&G, 1, player);
    printf("04: Checking if coins are increased by 2 (+2 for each Treasure)...");
    assertCheck(G.coins, coinCheck);

}
