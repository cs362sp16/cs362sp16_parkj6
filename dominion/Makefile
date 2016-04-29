CFLAGS = -Wall -fpic -coverage -lm

all: playdom player

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

dominion.o: dominion.h cards.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
simple: playdom interface.o asimpleunittest.c 
	gcc -o simple asimpleunittest.c -g dominion.o rngs.o interface.o $(CFLAGS)
	
test: playdom interface.o testing.h unittest*.c 
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o interface.o $(CFLAGS)

clean:
	rm -f playdom simple test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 testInit *.o *.gcov *.gcda *.gcno *.so *.a *.dSYM *.exe
