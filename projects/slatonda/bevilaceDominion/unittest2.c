/////////////////////////////////////////
//UNIT TEST FOR THE AMBASSADOR FUNCTION//
/////////////////////////////////////////
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
    int player = 0;

    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);

    //TEST 1//
    gainCard(copper, &G, 2, player);
    gainCard(copper, &G, 2, player);

    int p2Check = G.discardCount[1]+1;
    int p3Check = G.discardCount[2]+1;

    //printf("Hand check p2: %d\n", G.discardCount[1]);

    gainCard(gardens, &G, 2, player);
    int handCheck = G.handCount[player]-2;
    //printf("Hand check p1: %d\n", G.handCount[player]);
    playAmbassador(&G, player, 7, 6, 1);

    /*
    printf("Hand check p1: %d\n", G.handCount[player]);
    printf("Hand check p2: %d\n", G.discardCount[1]);
    printf("Hand check p2: %d\n", G.discardCount[2]);
    */

    printf("AMBASSADOR TESTS\n");
    printf("Test #1: Choosing to return one Copper to supply\n");
    printf("Checking that Player 1 has the correct number of cards...");
    assertCheck(G.handCount[player], handCheck);
    printf("Checking if Player 2 gained a card...");
    assertCheck(G.discardCount[1], p2Check);
    printf("Checking if Player 3 gained a card...");
    assertCheck(G.discardCount[2], p3Check);
    printf("Checking if the gained card is a Copper...");
    assertCheck(G.discard[1][0], copper);
    printf("Checking if the gained card is a Copper...");
    assertCheck(G.discard[2][0], copper);


    //TEST 2//
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(3, kCards, seed, &G);

    gainCard(copper, &G, 2, player);
    gainCard(copper, &G, 2, player);

    p2Check = G.discardCount[1]+1;
    p3Check = G.discardCount[2]+1;

    //printf("Hand check p2: %d\n", G.discardCount[1]);

    gainCard(gardens, &G, 2, player);
    handCheck = G.handCount[player]-3;
    //printf("Hand check p1: %d\n", G.handCount[player]);
    playAmbassador(&G, player, 7, 6, 2);

    /*
    printf("Hand check p1: %d\n", G.handCount[player]);
    printf("Hand check p2: %d\n", G.discardCount[1]);
    printf("Hand check p2: %d\n", G.discardCount[2]);
    */

    printf("TEST #2: Choosing to return two Coppers to supply\n");
    printf("Checking that Player 1 has the correct number of cards...");
    assertCheck(G.handCount[player], handCheck);
    printf("Checking if Player 2 gained a card...");
    assertCheck(G.discardCount[1], p2Check);
    printf("Checking if Player 3 gained a card...");
    assertCheck(G.discardCount[2], p3Check);
    printf("Checking if the gained card is a Copper...");
    assertCheck(G.discard[1][0], copper);
    printf("Checking if the gained card is a Copper...");
    assertCheck(G.discard[2][0], copper);
 
}
