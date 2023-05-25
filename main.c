#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


#define ALLOC(t,n) (t *) malloc((n)*sizeof(t))

extern void Tic_Tac_Toe();

int main() {
    Tic_Tac_Toe();
}