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

void testTribute(){
    int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    int numPlayers, seed, player, coins, drawNum, handNum, actNum, tCards[2];
    int it = 1;

    while(it < 3500){
        numPlayers = rand() % (4 + 1 - 2) + 2;
        seed = rand();
        player = numPlayers-1;
        coins = rand() % (50 + 1 - 0) + 1;
        int nextPlayer = player + 1;

        memset(&G, 0, sizeof(struct gameState));    
        initializeGame(numPlayers, kCards, seed, &G);

        for(int i = 0; i < G.numPlayers; i++){
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
        }

        if (nextPlayer > (G.numPlayers - 1)) {
            nextPlayer = 0;
        }

        if(coins == 25){
            G.discardCount[nextPlayer] = 0; G.deckCount[nextPlayer] = 0;
        }

        tCards[0] = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
        tCards[1] = G.deck[nextPlayer][G.deckCount[nextPlayer]-2];

        G.coins = coins;
        handNum = G.handCount[player];
        actNum = G.numActions;

        coins += 2; handNum += 2; actNum += 2;

        printf("TRIBUTE TEST %d\n", it);
        playTribute(&G, 0, player);
        for (int i = 0; i < 2; i ++) {
            if (tCards[i] == copper || tCards[i] == silver || tCards[i] == gold) { //Treasure cards
                printf("COIN CHECK +2: ");
                assertCheck(G.coins, coins);
                coins += 2;
            }

            else if (tCards[i] == estate || tCards[i] == duchy || tCards[i] == province || tCards[i] == gardens || tCards[i] == great_hall) { //Victory Card Found
                printf("DRAW CHECK +2: ");
                assertCheck(G.handCount[player], handNum);
                handNum += 2;
            }

            else { //Action Card
                printf("ACTION CHECK +2: ");
                assertCheck(G.numActions, actNum);
                actNum += 2;
        }
    }
        it++;
        printf("\n");
    }

    printf("~TRIBUTE TEST COMPLETE!~\n");

}

int main(){
    srand(time(NULL));
    testTribute();
    return 0;
}