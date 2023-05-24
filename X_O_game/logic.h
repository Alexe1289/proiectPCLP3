#include <stdio.h>
#include <ncurses.h>
#define CONTINUE 3
#define DRAW 2
#define PlayerX_WIN 0
#define Player0_WIN 1

int check_game_state(char** matr, int table_size);

typedef struct coord {
    int line_idx, col_idx, i;
}Location;

typedef struct tree {
    struct tree** sibling;
    int gamestate;
    char** matrix;
    Location coords;
    char value;
}*Tree;

Tree createTree(int line_idx, int col_idx, char player, int table_size, char** matr);
Location get_AI_choice(Tree root, int table_size);

