#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#define CONTINUE 3
#define DRAW 2
#define PlayerX_WIN 0
#define Player0_WIN 1
#define Square(n) n * n

typedef struct coordinates {
    int line_idx, col_idx;
} Coords;

#define ALLOC(t,n) (t *) malloc((n)*sizeof(t))

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

void start_message() {
	clear();
	printw("#########################################################################################\n");
	printw("-----------------------------------------------------------------------------------------\n");
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("------------------------------------CHOOSE GAME_MODE:------------------------------------\n");
	printw("                                                                                         \n");
	printw("                                    1) SINGLEPLAYER\n");
	printw("                                                                                         \n");
	printw("                                    2) MULTIPLAYER\n");
	printw("                                                                                         \n");
	printw("                                    3) AI vs AI\n");
	printw("                                                                                         \n");
	printw("                                    Press '1' or '2' or '3' : ");
	refresh();
}

void multipl_confirmation(char* first_player_name, char* second_player_name, int* table_size) {
	clear();
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("---------------------------------------MULTIPLAYER---------------------------------------\n");
	printw("#########################################################################################\n");
	printw("                                                                                         \n");
	printw("               INSERT FIRST PLAYER NAME (X player): ");
	refresh();
	echo();
	getstr(first_player_name);
	printw("\n");
	printw("               INSERT SECOND PLAYER NAME (0 player): ");
	refresh();
	getstr(second_player_name);
	printw("\n");
	printw("               CHOOSE TABLE SIZE : ");
	refresh();
	scanw("%d", table_size);
	printw("\n                         TABLE SIZE : %d\n", *table_size);
	printw("\n                       BUILDING TABLE... \n");
	napms(500);
	refresh();
}

void show_table(char** matr, int table_size, int line_idx, int col_idx, char* player) {
	start_color();
	clear();
	if(player != NULL) {
		printw("\n            Player %s chooses:\n\n", player);
		if(strcmp(player, "computer") != 0) {
			printw("         To move use WASD. After deciding press ENTER.\n");
			refresh();
		}
	}
	printw("\n");
	printw("\n                      ");
	int ok1 = 0;
	for(int i = 0; i < table_size; i++) {
		ok1 = 0;
		for(int k = 0; k < table_size; k++) {
			if((line_idx == i || line_idx + 1 == i) && col_idx == k) {
				ok1 = 1;
				printw("#####");
			}
			else
				printw("----");
		}
		if(ok1 == 0)
			printw("-\n                      ");
		else
			printw("\n                      ");
		for(int k = 0; k < table_size; k++) {
			if(line_idx == i && (col_idx == k || col_idx + 1 == k)) {
				printw("# %c ", matr[i][k]);
			}
			else
				printw("| %c ", matr[i][k]);
		}
		if(line_idx == i && col_idx == table_size - 1) {
			printw("#");
		}
		else
			printw("|");
		printw("\n                      ");
	}
	for(int k = 0; k < table_size; k++) {
		if(line_idx == table_size - 1 && col_idx == k) {
			printw("#####");
		}
		else
			printw("----");
		}
	if(ok1 == 0 || line_idx != table_size - 1)
		printw("-\n\n");
	else
		printw("\n\n");
	refresh();
}

void player_confirms(char** matr, int table_size, int *line_idx, int *col_idx, char* player1, char* player2, int player) {
	if(player == 0) 
		show_table(matr, table_size, *line_idx, *col_idx, player1);
	else
		show_table(matr, table_size, *line_idx, *col_idx, player2);
	char character;
	while(1) {
		noecho();
		curs_set(0);
		character = getch();
		if(character == '\n') {
			if(matr[*line_idx][*col_idx] == ' ') {
				if(player == 0)
					matr[*line_idx][*col_idx] = 'X';	
				else
					matr[*line_idx][*col_idx] = '0';
				break;
			}
			else {
				printw("\n       Square already taken! ");
				refresh();
				napms(700);
			}
		}
		if(character >= 'a') { //conversion to UPPER CASE
			character = character - 32;
		}
		switch (character)
		{
		case 'W':
			if(*line_idx > 0)
				*line_idx = *line_idx - 1;
			break;
		case 'S':
			if(*line_idx < table_size - 1)
				*line_idx = *line_idx + 1;
			break;
		case 'D':
			if(*col_idx < table_size - 1)
				*col_idx = *col_idx + 1;
			break;
		case 'A':
			if(*col_idx > 0)
				*col_idx = *col_idx - 1;
			break;
		default:
			break;
		}
		if(player == 0) 
			show_table(matr, table_size, *line_idx, *col_idx, player1);
		else
			show_table(matr, table_size, *line_idx, *col_idx, player2);
	}
	show_table(matr, table_size, *line_idx, *col_idx, NULL);
}

char final_message(int player, char* player1, char* player2) {
	if(player == PlayerX_WIN)
		printw("\n\n                 Player : %s has won the game! Congratulations!", player1);
	if(player == Player0_WIN)
		printw("\n\n                 Player : %s has won the game! Congratulations!", player2);
	if(player == DRAW)
		printw("\n\n                 DRAW!");
	printw("\n\n       If you want to play again press 'Q'. Press any other key to exit the game: ");
	refresh();
	napms(700);
	char choice;
	choice = getch();
	printw("\n");
	refresh();
	return choice;
}

void singlepl_confirmation(char* player_name, int* table_size) {
	clear();
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("---------------------------------------SINGLEPLAYER--------------------------------------\n");
	printw("#########################################################################################\n");
	printw("                                                                                         \n");
	printw("               INSERT YOUR NAME (X player): ");
	refresh();
	getstr(player_name);
	printw("\n");
	printw("\n");
	printw("               CHOOSE TABLE SIZE : ");
	refresh();
	scanw("%d", table_size);
	// while ((*table_size) %  2 == 0) {
	// 	printw("\n               BAD NUMBER, CHOOSE AGAIN(only odd numbers) : ");
	// 	refresh();
	// 	scanw("%d", table_size);
	// }
	printw("\n                         TABLE SIZE : %d\n", *table_size);
	printw("\n                       BUILDING TABLE... \n");
	napms(500);
	refresh();
}

extern void Tic_Tac_Toe() {
	initscr();
	//keypad(stdscr, TRUE);
	start_message();
	char player_choice;
	scanw("%c", &player_choice);
	char continue_game = 0;
	int table_size;
	if(player_choice == '2') {
		do {
		char player1_name[20], player2_name[20];
		multipl_confirmation(player1_name, player2_name, &table_size);
		char **matr = ALLOC(char*, table_size);
		for(int i = 0; i < table_size; i++) {
			matr[i] = ALLOC(char, table_size);
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
		matr = free_matrix(matr, table_size);
		} while (continue_game == 'Q' || continue_game == 'q');
	}
	else if(player_choice == '1') {
		char player_name[20];
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
		do {
		player_confirms(matr, table_size, &line_idx, &col_idx, player_name, "computer", ok); //here player makes a choice
		int game_state = check_game_state(matr, table_size);
		if(game_state != CONTINUE) {
			continue_game = final_message(game_state, player_name, "computer");
			break;
		}
		Coords locations;
		locations = find_best0_pos(matr, table_size);
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
		matr = free_matrix(matr, table_size);
		} while(continue_game == 'Q' || continue_game == 'q');
		}
	else
		{
		int table_size;
		printw("-----------------INSERT TABLE SIZE : ");
		scanw("%d", &table_size);
		do {
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
		Coords locations;
		locations = find_bestX_pos(matr, table_size);
		locations = find_best0_pos(matr, table_size);
		if(locations.col_idx == -1) {
			locations = pick_a_random_pos(matr, table_size);
		}
		matr[locations.line_idx][locations.col_idx] = 'X';
		show_table(matr, table_size, locations.line_idx, locations.col_idx, "0");
		int game_state = check_game_state(matr, table_size);
		if(game_state != CONTINUE) {
			continue_game = final_message(game_state, "X", "0");
			break;
		}
		napms(850);
		locations = find_best0_pos(matr, table_size);
		locations = find_bestX_pos(matr, table_size);
		if(locations.col_idx == -1) {
			locations = pick_a_random_pos(matr, table_size);
		}
		matr[locations.line_idx][locations.col_idx] = '0';
		show_table(matr, table_size, locations.line_idx, locations.col_idx, "0");
		game_state = check_game_state(matr, table_size);
		if(game_state != CONTINUE) {
			continue_game = final_message(game_state, "X", "0");
			break;
		}
		} while(1);
		matr = free_matrix(matr, table_size);
		} while(continue_game == 'Q' || continue_game == 'q');
	}
	endwin();
	return;
}
