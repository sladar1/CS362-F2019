CFLAGS= -Wall -fpic -coverage -lm -std=c99 -fprofile-arcs -ftest-coverage

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	gcov -f -b testme.c

clean:
	rm -f *.o *.gcno *.gcda *.gcov *.gcov *.gcda *.gcno *.so *.out testme