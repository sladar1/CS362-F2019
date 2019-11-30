CFLAGS= -Wall -fpic -coverage -lm -std=c99 -fprofile-arcs -ftest-coverage

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: unittest5.c unittest6.c unittest7.c unittest8.c dominion.c rngs.c
	gcc -g -o unittest5 dominion.c rngs.c unittest5.c $(CFLAGS)
	./unittest5 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	
#	gcc -o unittest6 dominion.c rngs.c unittest6.c $(CFLAGS)
#	./unittest6 >> unittestresults.out
#	gcov -f -b dominion.c >> unittestresults.out
	
	#gcc -o unittest7 dominion.c rngs.c unittest7.c $(CFLAGS)
	#./unittest7 >> unittestresults.out
	#gcov -f -b dominion.c >> unittestresults.out
	
	#gcc -o unittest8 dominion.c rngs.c unittest8.c $(CFLAGS)
	#./unittest8 >> unittestresults.out
	#gcov -f -b dominion.c >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o *.gcno *.gcda *.gcov playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestresults unittest5 unittest6 unittest7 unittest8
