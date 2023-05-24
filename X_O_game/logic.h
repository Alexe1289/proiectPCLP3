#include <stdio.h>
#define CONTINUE 3
#define DRAW 2
#define PlayerX_WIN 0
#define Player0_WIN 1

int check_game_state(char** matr, int table_size);

typedef struct tree {
    struct tree* child;
    struct tree* sibling;
    int gamestate;
    char** matrix;
    int line_idx, col_idx;
}*Tree;

