CFLAGS = -Wall -coverage -lm -fprofile-arcs -ftest-coverage -std=c99 -g

default: playdom player test

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

dominion.o: dominion.h cards.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

workingdom: working/dominion.c working/cards.h dominion.h rngs.o
	gcc -c working/dominion.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
simple: playdom interface.o asimpleunittest.c 
	gcc -o simple asimpleunittest.c -g dominion.o rngs.o interface.o $(CFLAGS)
	
testdom: workingdom testdominion.c interface.o
	gcc -o testdominion testdominion.c -g dominion.o rngs.o interface.o $(CFLAGS)
	
testunit: playdom interface.o testing.h unittest*.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o interface.o $(CFLAGS)

testcard: playdom interface.o testing.h cardtest*.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o interface.o $(CFLAGS)

randtest: playdom interface.o testing.h randomtestcard1.c randomtestcard2.c randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	
test: testunit testcard randtest
	./testall
	
clean:
	rm -f playdom simple test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 testInit *.o *.gcov *.gcda *.gcno *.so *.a *.dSYM *.exe
