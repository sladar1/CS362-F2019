/////////////////////////////////////
//UNIT TEST FOR THE MINION FUNCTION//
/////////////////////////////////////
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
    int player1 = 0;
    int player2 = 1;
    int player3 = 2;


    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);

    //TEST 1//
    gainCard(minion, &G, 2, player1);

    int coinCheck = G.coins+2;

    //Choosing to add +2 to coins
    playMinion(&G, 5, player1, 1, 0);
    printf("MINION TESTS\n");
    printf("TEST #1: Choosing to gain +2 to coins\n");
    printf("01: Checking if the number of coins is increased by 2...");
    assertCheck(G.coins, coinCheck);


    //TEST 2//
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);

    G.whoseTurn = 1;
    for (int it = 0; it < 5; it++) {
        drawCard(G.whoseTurn, &G);
    }
    G.whoseTurn = 2;
    for (int it = 0; it < 5; it++) {
        drawCard(G.whoseTurn, &G);
    }
    G.whoseTurn = 0;

    gainCard(minion, &G, 2, player1);
    gainCard(copper, &G, 2, player1);

    for(int i = 0; i < 3; i++){
        gainCard(copper, &G, 2, player2);
    }

    discardCard(5, player3, &G, 1);
    discardCard(4, player3, &G, 1);

    /*
    printf("Card check p1: %d\n", G.handCount[player1]);
    printf("Card check p2: %d\n", G.handCount[player2]);
    printf("Card check p3: %d\n", G.handCount[player3]);
    */

    playMinion(&G, 5, player1, 1, 0);

    /*
    printf("Card check p1: %d\n", G.handCount[player1]);
    printf("Card check p2: %d\n", G.handCount[player2]);
    printf("Card check p3: %d\n", G.handCount[player3]);
    */

    printf("TEST #2: Choosing to discard hand\n");
    printf("02: Checking if Player 1 has 4 cards...");
    assertCheck(G.handCount[player1], 4);
    printf("03: Checking if Player 2 has 4 cards...");
    assertCheck(G.handCount[player2], 4);
    printf("04: Checking if Player 3 has 3 cards...");
    assertCheck(G.handCount[player3], 3);

}
