#include "logic.h"

int check_lines(char** matr, int table_size) {
    for(int i = 0; i < table_size; i++) {
        int ok = 0;
        char element = matr[i][0];
        for(int j = 1; j < table_size; j++) {
            if(element != matr[i][j]) {
                ok = 1;
            }
        }
        if(ok == 0) {
            if(element == 'X')
                return PlayerX_WIN;
            else
                if(element == '0')
                    return Player0_WIN;
        }
    }
    return DRAW;
}

int check_cols(char** matr, int table_size) {
    for(int i = 0; i < table_size; i++) {
        int ok = 0;
        char element = matr[0][i];
        for(int j = 1; j < table_size; j++) {
            if(element != matr[j][i]) {
                ok = 1;
            }
        }
        if(ok == 0) {
            if(element == 'X')
                return PlayerX_WIN;
            else
                if(element == '0')
                    return Player0_WIN;
        }
    }
    return DRAW;
}

int check_diags(char** matr, int table_size) {
    int ok = 0;
    char element = matr[0][0];
    for(int i = 1; i < table_size; i++) {
        if(matr[i][i] != element) {
            ok = 1;
        }
    }
    if(ok == 0) {
        if(element == 'X')
            return PlayerX_WIN;
        else
            if(element == '0')
                return Player0_WIN;
    }
    ok = 0;
    element = matr[0][table_size - 1];
    for(int i = 1; i < table_size; i++) {
        if(matr[i][table_size - i - 1] != element)
            ok = 1;
    }
    if(ok == 0) {
        if(element == 'X')
            return PlayerX_WIN;
        else
            if(element == '0')
                return Player0_WIN;
    }
    return DRAW;
}

int check_game_state(char** matr, int table_size) {
    if(check_lines(matr, table_size) != DRAW)
        return check_lines(matr, table_size);
    if(check_cols(matr, table_size) != DRAW)
        return check_cols(matr, table_size);
    if(check_diags(matr, table_size) != DRAW)
        return check_diags(matr, table_size);
    int blank_spaces = 0;
    for(int i = 0; i < table_size; i++) {
        for(int j = 0; j < table_size; j++) {
            if(matr[i][j] == ' ')
                blank_spaces++;
        }
    }
    if(blank_spaces == 0)
        return DRAW;
    return CONTINUE;
}

Tree createTree(int line_idx, int col_idx, char player, int table_size, char** matr) {
    Tree root = calloc(1, sizeof(struct tree));
    root->gamestate = check_game_state(matr, table_size);
    if(root->gamestate == CONTINUE) {
        root->matrix = malloc(table_size * sizeof(char*));
            for(int i = 0; i < table_size; i++) {
                root->matrix[i] = malloc(table_size * sizeof(char));
            }
        for(int i = 0; i < table_size; i++) {
            for(int j = 0; j < table_size; j++)
                root->matrix[i][j] = matr [i][j];
        }
    }
}