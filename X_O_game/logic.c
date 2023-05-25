#include <ncurses.h>
#include "logic.h"
#include <stdlib.h>

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

Coords find_best0_pos(char** matr, int table_size) {
	Coords idxs;
	idxs.line_idx = -1;
	idxs.col_idx = -1;
	for(int i = 0; i < table_size; i++) {
		for(int j = 0; j < table_size; j++)
			if(matr[i][j] == ' ') {
				matr[i][j] = '0'; //check if putting X here influences the game
				if(check_game_state(matr, table_size) == Player0_WIN) {
					Coords idxs;
					idxs.line_idx = i;
					idxs.col_idx = j;
					matr[i][j] = ' '; //revert the change
					return idxs;
				}
				matr[i][j] = ' '; //revert the change
			}
	}
	return idxs;
}

Coords find_bestX_pos(char** matr, int table_size) {
	Coords idxs;
	idxs.line_idx = -1;
	idxs.col_idx = -1;
	for(int i = 0; i < table_size; i++) {
		for(int j = 0; j < table_size; j++)
			if(matr[i][j] == ' ') {
				matr[i][j] = 'X'; //check if putting X here influences the game
				if(check_game_state(matr, table_size) == PlayerX_WIN) {
					Coords idxs;
					idxs.line_idx = i;
					idxs.col_idx = j;
					matr[i][j] = ' '; //revert the change
					return idxs;
				}
				matr[i][j] = ' '; //revert the change
			}
	}
	return idxs;
}

Coords pick_a_random_pos(char** matr, int table_size) {
	Coords free_idxs[Square(table_size)];
	int k = 0;
	for(int i = 0; i < table_size; i++) {
		for(int j = 0; j < table_size; j++) {
			if(matr[i][j] == ' ') {
				free_idxs[k].line_idx = i;
				free_idxs[k++].col_idx = j;
		}
		}
	}
	srand(time(NULL));
	int random_idx = rand() % k;
	return free_idxs[random_idx];
}

char** free_matrix(char** matr, int table_size) {
	for(int i = 0; i < table_size; i++) {
			free(matr[i]);
	}
	free(matr);
	return NULL;
}

