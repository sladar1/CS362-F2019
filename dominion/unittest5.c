///////////////////////////////////
//UNIT TEST FOR THE MINE FUNCTION//
///////////////////////////////////
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

int assertCheck2(int check1, int check2){
    if(check1 == check2){
        printf(" FAILED!\n\n");
        return 1;
    }
    else{
        printf(" PASSED!\n\n");
        return 0;
    }
}

int main(int argc, char* argv[]){
    int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    struct gameState G;
    int seed = 300;
    int player = 0;

    //TEST 1//
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    //Add a Copper to the player's hand
    gainCard(copper, &G, 2, player);

    //Trash a Copper to gain a Silver
    int countTest = G.handCount[player];
    playMine(player, copper, silver, 5, &G);
    printf("MINE TESTS\n");
    printf("TEST #1: Trashing a Copper to gain a Silver:\n");
    printf("01: Checking if Silver was successfully added to the player's hand...");
    assertCheck(G.hand[player][5], silver);
    printf("02: Checking if the number of cards in hand is the same...");
    assertCheck(G.handCount[player], countTest);

    //TEST 2//
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, kCards, seed, &G);

    //Add a Copper to the player's hand
    gainCard(copper, &G, 2, player);

    //Attempt to trash a Copper to gain a Gold (illegal move)
    countTest = G.handCount[player];
    playMine(player, copper, gold, 5, &G);
    printf("TEST #2: Attempting to trash a Copper to gain a Gold (illegal move)\n");
    printf("03: Checking if Gold was NOT added to the player's hand...");
    assertCheck2(G.hand[player][5], gold);
    printf("04: Checking if the number of cards in hand is the same...");
    assertCheck(G.handCount[player], countTest);

}
