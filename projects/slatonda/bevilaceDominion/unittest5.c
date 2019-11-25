///////////////////////////////////
//UNIT TEST FOR THE MINE FUNCTION//
///////////////////////////////////
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

int assertCheck2(int check1, int check2){
    if(check1 == check2){
        printf(" FAILED!\n");
        return 1;
    }
    else{
        printf(" PASSED!\n");
        return 0;
    }
}

int main(int argc, char* argv[]){
    int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    struct gameState G;
    int seed = 300;
    int player = 0;

    /////////////////////////////////////////
    // TEST 1: Trash a Copper for a Silver //
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    //Add a Copper to the player's hand
    gainCard(copper, &G, 2, player);

    // The value here for handPos is a filler value
    // since it isn't required or used in this function call
    playMine(&G, player, 5, silver, 0);
    printf("MINE TESTS\n");
    printf("TEST #1: Trashing a Copper to gain a Silver:\n");
    printf("01: Checking if Silver was successfully added to the player's hand...");
    assertCheck(G.hand[player][5], silver);

    ///////////////////////////////////////////////////////////////////////
    //TEST 2: Attempting to trash a Copper to gain a Gold (illegal move) //
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    //Add a Copper to the player's hand
    gainCard(copper, &G, 2, player);

    playMine(&G, player, 5, gold, 0);
    printf("\nTEST #2: Attempting to trash a Copper to gain a Gold (illegal move)\n");
    printf("02: Checking if Gold was NOT added to the player's hand...");
    assertCheck2(G.hand[player][5], gold);

    printf("\n~MINE TESTS COMPLETE!~\n\n");
}
