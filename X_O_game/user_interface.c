#include <ncurses.h>
#include "UI.h"
#include "logic.h"

void start_message() {
	clear();
	printw("#########################################################################################\n");
	printw("------------------------------------BOOTING X_0 GAME-------------------------------------\n");
	printw("#########################################################################################\n");
	//sleep(1);
	// Wait for a key press
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("#########################################################################################\n");
	printw("------------------------------------CHOOSE GAME_MODE:------------------------------------\n");
	printw("                                                                                         \n");
	printw("                                    1) SINGLEPLAYER\n");
	printw("                                                                                         \n");
	printw("                                    2) MULTIPLAYER\n");
	printw("                                                                                         \n");
	printw("                                    Press '1' or '2' : ");
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

void show_table(char** matr, int table_size, int line_idx, int col_idx, char* player) {
	clear();
	if(player != NULL) {
		printw("\n      Player %s chooses:\n\n", player);
		if(strcmp(player, "computer") != 0) {
			printw("     To move use WASD. After deciding press ENTER.\n");
			refresh();
		}
	}
	printw("\n      ");
	printw("\n      ");
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
			printw("-\n      ");
		else
			printw("\n      ");
		for(int k = 0; k < table_size; k++) {
			if(line_idx == i && (col_idx == k || col_idx + 1 == k))
				printw("# %c ", matr[i][k]);
			else
				printw("| %c ", matr[i][k]);
		}
		if(line_idx == i && col_idx == table_size - 1) 
			printw("#");
		else
			printw("|");
		printw("\n      ");
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
		if(character >= 'a') {
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
		printw("\n\n          Player : %s has won the game! Congratulations!", player1);
	if(player == Player0_WIN)
		printw("\n\n          Player : %s has won the game! Congratulations!", player2);
	if(player == DRAW)
		printw("\n\n          DRAW!");
	printw("\n\n       If you want to play again press 'Q'. Press any other key to exit the game: ");
	refresh();
	char choice;
	scanf("%c", &choice);
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