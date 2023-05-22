#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "UI.h"
#include "logic.h"

int main() {
	start_message();
	char player_choice = getchar();
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
		} while (continue_game == 'Q');
	}
	return 0;
}
