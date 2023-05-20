#include "UI.h"

void start_message() {
	printf("#########################################################################################\n");
	printf("------------------------------------BOOTING X_0 GAME-------------------------------------\n");
	printf("#########################################################################################\n");
	//sleep(1);
	system("clear");
	// Wait for a key press
	printf("#########################################################################################\n");
	printf("#########################################################################################\n");
	printf("#########################################################################################\n");
	printf("------------------------------------CHOOSE GAME_MODE:------------------------------------\n");
	printf("                                                                                         \n");
	printf("                                    1) SINGLEPLAYER\n");
	printf("                                                                                         \n");
	printf("                                    2) MULTIPLAYER\n");
	printf("                                                                                         \n");
	printf("                                    Press '1' or '2' : ");
}

void multipl_confirmation(char* first_player_name, char* second_player_name, int* table_size) {
	system("clear");
	printf("#########################################################################################\n");
	printf("#########################################################################################\n");
	printf("#########################################################################################\n");
	printf("---------------------------------------MULTIPLAYER---------------------------------------\n");
	printf("#########################################################################################\n");
	printf("                                                                                         \n");
	printf("               INSERT FIRST PLAYER NAME (X player): ");
	scanf("%s", first_player_name);
	printf("\n");
	printf("               INSERT SECOND PLAYER NAME (0 player): ");
	scanf("%s", second_player_name);
	printf("\n");
	printf("               CHOOSE TABLE SIZE(only odd numbers) : ");
	scanf("%d", table_size);
	while ((*table_size) %  2 == 0) {
		printf("\n               BAD NUMBER, CHOOSE AGAIN(only odd numbers) : ");
		scanf("%d", table_size);
	}
	printf("\n                         TABLE SIZE : %d\n", *table_size);
	printf("\n                       BUILDING TABLE... \n");
}

void show_table(char** matr, int table_size, int line_idx, int col_idx, char* player) {
	system("clear");
	printf("\n      Player %s chooses:\n", player);
	printf("      ");
	printf("\n      ");
	int ok1 = 0, ok2 = 0;
	for(int i = 0; i < table_size; i++) {
		ok1 = 0;
		for(int k = 0; k < table_size; k++) {
			if((line_idx == i || line_idx + 1 == i) && col_idx == k) {
				ok1 = 1;
				printf("#####");
			}
			else
				printf("----");
		}
		if(ok1 == 0)
			printf("-\n      ");
		else
			printf("\n      ");
		for(int k = 0; k < table_size; k++) {
			if(line_idx == i && (col_idx == k || col_idx + 1 == k))
				printf("# %c ", matr[i][k]);
			else
				printf("| %c ", matr[i][k]);
		}
		if(line_idx == i && col_idx == table_size - 1) 
			printf("#");
		else
			printf("|");
		printf("\n      ");
	}
	for(int k = 0; k < table_size; k++) {
		if(line_idx == table_size - 1 && col_idx == k) {
			ok2 = 1;
			printf("#####");
		}
		else
			printf("----");
		}
	if(ok1 == 0 || line_idx != table_size - 1)
		printf("-\n\n");
	else
		printf("\n\n");
}

void player_moves(int *line_idx, int *col_index, char direction, int table_size) {
	switch (direction)
	{
	case 'W':
		if(*line_idx > 0)
			*line_idx--;
		break;
	case 'S':
		if(*line_idx < table_size)
			*line_idx--;
		break;
	case 'D':
		if(*col_index < table_size)
			*col_index++;
		break;
	case 'A':
		if(*col_index > 0)
			*col_index--;
		break;
	default:
		break;
	}
}

void player_confirms(char** matr, int table_size, int *line_idx, int *col_idx, char* player1, char* player2) {
	show_table(matr, table_size, *line_idx, *col_idx, player1);
	int ok1 = 0, ok2 = 0;
	char character;
	scanf("%c\n", &character);
	printf("CAR%c", character);
	player_moves(line_idx, col_idx, character, table_size);
	ok1 = 1;
	while(character != 'X') {
		printf("CARACTERE %d %d\n", *line_idx, *col_idx);
		sleep(1);
		show_table(matr, table_size, *line_idx, *col_idx, player1);
		scanf("%c\n", &character);
		printf("CAR%c", character);
	}
}



