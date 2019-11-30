////////////////////////////////////
//UNIT TEST FOR THE BARON FUNCTION//
////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion_helpers.h"
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
    int seed = 30; int player = 0;
    int handNum;

    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    // Empty out the deck, discard, and hand so we can fill it with cards
    // of our own choosing

    //discard hand
    //handNum = G.handCount[player];
    printf("Hand Count Test: %d\n", G.handCount[player]);
    while(G.handCount[player] > 0 ){
        discardCard(G.handCount[player]-1, player, &G, 1);
        //handNum--;
    }
    printf("Hand Count Test: %d\n", G.handCount[player]);
        
    gainCard(estate, &G, 2, player);
    gainCard(duchy, &G, 2, player);
    gainCard(province, &G, 2, player);
    //10 points in hand

    printf("Hand Count Test: %d\n", G.handCount[player]);

    printf("Deck Count Test: %d\n", G.deckCount[player]);
    while(G.deckCount[player] > 0 ){
        //discardCard(G.deckCount[player]-1, player, &G, 1);
        G.deckCount[player]--;
        //handNum--;
    }
    gainCard(estate, &G, 1, player);
    gainCard(duchy, &G, 1, player);
    gainCard(province, &G, 1, player);
    gainCard(estate, &G, 1, player);

    printf("Deck Count Test: %d\n", G.deckCount[player]);

    printf("Discard Count Test: %d\n", G.discardCount[player]);
    while(G.discardCount[player] > 0 ){
        //discardCard(G.discardCount[player]-1, player, &G, 1);
        G.discardCount[player]--;
        //handNum--;
    }
    gainCard(estate, &G, 0, player);
    gainCard(duchy, &G, 0, player);
    gainCard(province, &G, 0, player);

    printf("Discard Count Test: %d\n", G.discardCount[player]);
    int score = scoreFor(player, &G);
    printf("Score is: %d\n", score);

    //

    //G.handCount[p] = handCount;
    //TEST 1//
    /*
    int playerCoins = G.coins+4;

    printf("num buy check: %d\n", G.numBuys);
    printf("Getting ready to run tests:\n");
    playBaron(player, &G, 1);
    printf("TEST #1: ");
    printf("01: Checking if the number of coins is increased by 4...");
    assertCheck(G.coins, playerCoins);

    printf("num buy check: %d\n", G.numBuys);
    */


    //assert(G.numBuys, buyCheck);
}
