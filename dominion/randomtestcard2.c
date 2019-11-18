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

void testMinion(){
    int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    struct gameState G;
    int numPlayers, seed, player, coins, choice1, choice2, drawNum, handNum;
    int it = 1;

    while(it < 3500){
        numPlayers = rand() % (4 + 1 - 2) + 2;
        seed = rand();
        player = numPlayers-1;
        choice1 = rand() % (1 + 1 - 0) + 0;
        choice2 = rand() % (1 + 1 - 0) + 0;
        coins = rand() % (50 + 1 - 0) + 1;
        int hand[4];

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

        gainCard(minion, &G, 2, player);

        G.coins = coins;
        coins += 2;
        printf("MINION TEST %d:\n", it);
        for(int i = 0; i < numPlayers; i++){
            hand[i] = G.handCount[i];
        }

        playMinion(&G, G.handCount[player], player, choice1, choice2);
        if(choice1 > 0){
            printf("COIN CHECK BRANCH:");
            assertCheck(G.coins, coins);
        }
        else{
            printf("CARD CHECK BRANCH: \n");
            if(numPlayers > 1){
                for(int i = 0; i < numPlayers; i++){
                    printf("\tPLAYER %d:", i);
                    if(hand[i] > 4){
                        //Check if hand was discarded and +4 cards
                        assertCheck(G.handCount[i], 4);
                    }
                    else{
                        //Check that handCount is original value
                        assertCheck(G.handCount[i], hand[i]);
                    }
                }
            }
        }
        it++;
        printf("\n");
    }

    printf("~MINION TEST COMPLETE!~\n");

}

int main(){
    srand(time(NULL));
    testMinion();
    return 0;
}