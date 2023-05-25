#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
		singlepl_confirmation(player_name, &table_size);
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
		do {
		player_confirms(matr, table_size, &line_idx, &col_idx, player_name, "computer", ok); //here player makes a choice
		int game_state = check_game_state(matr, table_size);
		if(game_state != CONTINUE) {
			continue_game = final_message(game_state, player_name, "computer");
			break;
		}
		Coords locations;
		locations = find_bestX_pos(matr, table_size);
		if(locations.col_idx == -1) { //if the player didn't make a game-ending decision, then pick a random position
			locations = pick_a_random_pos(matr, table_size);
		}
		matr[locations.line_idx][locations.col_idx] = '0';
		show_table(matr, table_size, locations.line_idx, locations.col_idx, "computer");
		game_state = check_game_state(matr, table_size);
		if(game_state != CONTINUE) {
			continue_game = final_message(game_state, player_name, "computer");
			break;
		}
	} while (1);
	}
	endwin();
	return 0;
}
