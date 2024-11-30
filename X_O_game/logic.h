#include <stdio.h>
#include <ncurses.h>
#define CONTINUE 3
#define DRAW 2
#define PlayerX_WIN 0
#define Player0_WIN 1
#define RANDOM -1
#define Square(n) n * n

typedef struct coordinates {
    int line_idx, col_idx;
} Coords;

int check_game_state(char** matr, int table_size);
Coords find_bestX_pos(char** matr, int table_size);
Coords find_best0_pos(char** matr, int table_size);
Coords pick_a_random_pos(char** matr, int table_size);
char** free_matrix(char** matr, int table_size);