////////////////////////////////////
//UNIT TEST FOR THE BARON FUNCTION//
////////////////////////////////////
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
    initializeGame(2, kCards, seed, &G);

    //G.handCount[p] = handCount;
    //TEST 1//
    int playerCoins = G.coins+4;

    printf("num buy check: %d\n", G.numBuys);
    printf("Getting ready to run tests:\n");
    playBaron(player, &G, 1);
    printf("TEST #1: ");
    printf("01: Checking if the number of coins is increased by 4...");
    assertCheck(G.coins, playerCoins);

    printf("num buy check: %d\n", G.numBuys);


    //assert(G.numBuys, buyCheck);
}
