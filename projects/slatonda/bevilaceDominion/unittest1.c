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
        printf(" PASSED!\n");
        return 1;
    }
    else{
        printf(" FAILED!\n");
        return 0;
    }
}

int main(int argc, char* argv[]){
    int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    struct gameState G;
    int seed = 30;
    int player = 1;
    int estCheck = 0;
    int handNum;

    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    ///////////////////////////////////////
    // TEST 1: Checking the first branch //
    int playerCoins = G.coins+4;

    gainCard(estate, &G, 2, player);

    printf("BARON TESTS:\n");
    // handPos is not used in this function
    playBaron(&G, player, 1, 0);
    printf("TEST #1: Discarding an Estate to gain +$4\n");
    printf("01: Checking if the number of coins is increased by 4...");
    assertCheck(G.coins, playerCoins);
    // Check if Estate was discarded
    if(G.hand[G.handCount[player]-1] == estate){ estCheck = 1; }
    printf("02: Checking if the Estate was discarded...");
    assertCheck(estCheck, 0);

    ////////////////////////////////////////
    // TEST 2: Checking the second branch //
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    playerCoins = G.coins;

    //gainCard(estate, &G, 2, player);

    // handPos is not used in this function
    playBaron(&G, player, 0, 0);
    printf("\nTEST #2: Choosing not to discard\n");
    printf("01: Checking if the number of coins remains the same...");
    assertCheck(G.coins, playerCoins);
    // Check if Estate was gained
    if(G.discard[player][G.discardCount[player]-1] == estate){ estCheck = 1; }
    printf("02: Checking if an Estate was gained...");
    assertCheck(estCheck, 1);
    
    ////////////////////////////////
    // TEST 3: No Estates in hand //
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    for(int i = 0; i < G.numPlayers; i++){
        //discard hand
        handNum = G.handCount[player];
        while(G.handCount[player] > 0 ){
            discardCard(handNum, player, &G, 0);
            handNum--;
        }

        //refill hand with Coppers
        for (int j = 0; j <= 5 ; j++){
            gainCard(copper, &G, 2, player);
        }
    }

    playerCoins = G.coins;

    // handPos is not used in this function
    playBaron(&G, player, 1, 0);
    printf("\nTEST #3: Attempting to discard with no Estates\n");
    printf("01: Checking if the number of coins remains the same...");
    assertCheck(G.coins, playerCoins);
    // Check if Estate was gained
    if(G.discard[player][G.discardCount[player]-1] == estate){ estCheck = 1; }
    printf("02: Checking if an Estate was gained...");
    assertCheck(estCheck, 1);
    printf("\n~BARON TESTS COMPLETE!~\n\n");
}
