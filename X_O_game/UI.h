#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void start_message();
void multipl_confirmation(char* first_player_name, char* second_player_name, int* table_size);
void show_table(char** matr, int table_size, int line_idx, int col_idx, char* player);
void player_confirms(char** matr, int table_size, int *line_idx, int *col_idx, char* player1, char* player2, int player);
char final_message(int player, char* player1, char* player2);