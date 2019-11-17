#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "dominion.h"

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

void testBaron(){
    int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    struct gameState G;
    int numPlayers, seed, player, coins, choice, drawNum, handNum;
    int it = 1;

    while(it < 3000){
        numPlayers = rand() % (4 + 1 - 2) + 2;
        seed = rand();
        player = numPlayers-1;
        choice = rand() % (1 + 1 - 0) + 0;
        coins = rand() % (50 + 1 - 0) + 1;

        memset(&G, 0, sizeof(struct gameState));    
        initializeGame(numPlayers, kCards, seed, &G);

        //discard hand
        handNum = G.handCount[player];
        while(G.handCount[player] > 0 ){
            discardCard(handNum, player, &G, 0);
            handNum--;
        }
        
        //draw new hand
        drawNum = rand() % (10 + 1 - 0) + 0;
        for (int j = 0; j <= drawNum ; j++){
            drawCard(player, &G);
        }
        

        G.coins = coins;
        coins += 4;
        printf("BARON TEST %d:\n", it);
        printf("COIN CHECK %d:", it);
        playBaron(player, &G, choice);
        assertCheck(G.coins, coins);
        it++;
        printf("\n");
    }

    printf("~BARON TEST COMPLETE!~\n");

    /*
    coins = 10;
    printf("num buy check: %d\n", G.numBuys);
    printf("Getting ready to run tests:\n");
    playBaron(player, &G, 1);
    printf("TEST #1: ");
    printf("01: Checking if the number of coins is increased by 4...");
    assertCheck(G.coins, coins);

    printf("num buy check: %d\n", G.numBuys);
    */
}

int main(){
    srand(time(NULL));
    testBaron();
    return 0;
}