#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "UI.h"

int main() {
    start_message();
    char player_choice = getchar();
    if(player_choice == '2') {
        char player1_name[20], player2_name[20];
        multipl_confirmation(player1_name, player2_name);
    }
    return 0;
}
