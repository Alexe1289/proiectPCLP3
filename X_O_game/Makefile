CFLAGS=-Wall -g
all: build
build: X_O.o user_interface.o logic.o
	gcc $(CFLAGS) -o X_O X_O.o user_interface.o logic.o

main.o: X_O.c
	gcc $(CFLAGS) -c X_O.c

user_interface.o: user_interface.c UI.h
	gcc $(CFLAGS) -c user_interface.c

logic.o: logic.c logic.h
	gcc $(CFLAGS) -c logic.c
run: build
	./X_O

.PHONY: clean

clean:
	rm -f *.o X_O