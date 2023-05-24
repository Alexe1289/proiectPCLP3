#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "UI.h"
#include "logic.h"

int main() {
	initscr();
	//keypad(stdscr, TRUE);
	start_message();
	char player_choice;
	scanw("%c", &player_choice);
	char continue_game = 0;
	if(player_choice == '2') {
		do {
		char player1_name[20], player2_name[20];
		int table_size;
		multipl_confirmation(player1_name, player2_name, &table_size);
		char **matr = malloc(table_size * sizeof(char*));
		for(int i = 0; i < table_size; i++) {
			matr[i] = malloc(table_size * sizeof(char));
		}
		for(int i = 0; i < table_size; i++) {
			for(int j = 0; j < table_size; j++) {
				matr[i][j] = ' '; //matrix is empty initially
			}
		}
		int mid_pos = table_size / 2;
		int line_idx = mid_pos, col_idx = mid_pos;
		//show_table(matr, table_size, mid_pos, mid_pos, player1_name);
		int ok = 0;
		do {
			player_confirms(matr, table_size, &line_idx, &col_idx, player1_name, player2_name, ok);
			ok = 1;
			int game_state = check_game_state(matr, table_size);
			if(game_state != CONTINUE) {
				continue_game = final_message(game_state, player1_name, player2_name);
				break;
			}
			player_confirms(matr, table_size, &line_idx, &col_idx, player1_name, player2_name, ok);
			ok = 0;
			game_state = check_game_state(matr, table_size);
			if(game_state != CONTINUE) {
				continue_game = final_message(game_state, player1_name, player2_name);
				break;
			}
		} while (1);
		printw("%c", continue_game);
		} while (continue_game == 'Q' || continue_game == 'q');
	}
	else {
		char player_name[20];
		int table_size;
		int ok = 0;
		// singlepl_confirmation(player_name, &table_size);
		table_size = 3;
		int mid_pos = table_size / 2;
		int line_idx = mid_pos, col_idx = mid_pos;
		char **matr = malloc(table_size * sizeof(char*));
		for(int i = 0; i < table_size; i++) {
			matr[i] = malloc(table_size * sizeof(char));
		}
		for(int i = 0; i < table_size; i++) {
			for(int j = 0; j < table_size; j++) {
				matr[i][j] = ' '; //matrix is empty initially
			}
		}
		//player_confirms(matr, table_size, &line_idx, &col_idx, player_name, "computer", ok);
		Tree tree = createTree(line_idx, col_idx, 'X', table_size, matr);
		//printw("\nAfter :%d", tree->sibling[1]->sibling[0]->gamestate);
		//refresh();
		Location idxs = get_AI_choice(tree, table_size);
		printw("%d, %d", idxs.line_idx, idxs.col_idx);
		refresh();
		napms(100000);
	}
	endwin();
	return 0;
}
