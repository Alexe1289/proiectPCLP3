CFLAGS=-Wall -g
all: build
build: main.o X_O.o tetris.o typeracer.o
	gcc $(CFLAGS) -o main main.o X_O.o tetris.o typeracer.o -lcurses
	
main.o: main.c
	gcc $(CFLAGS) -c main.c

X_O.o: X_O.c
	gcc $(CFLAGS) -c X_O.c

tetris.o: tetris.c
	gcc $(CFLAGS) -c tetris.c

typeracer.o: typeracer.c
	gcc $(CFLAGS) -c typeracer.c

run: build
	./main

.PHONY: clean

clean:
	rm -f *.o main