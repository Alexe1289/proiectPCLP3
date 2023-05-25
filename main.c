#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

extern void Tic_Tac_Toe();
extern void tetris();
extern void typeRacer();

int main() {
	system("clear");
	printf("\n\n\n\n");
    printf("\t\t\033[0;31mM       M     A     IIIII  N      N          M       M   EEEEEEE   N      N    U     U\033[0m\n");
    printf("\t\tMM     MM    A A      I    NN     N          MM     MM   E         NN     N    U     U\n");
    printf("\t\t\033[0;31mM M   M M   AAAAA     I    N N    N          M M   M M   EEEEE     N N    N    U     U\033[0m\n");
    printf("\t\tM  M M  M  A     A    I    N  N   N          M  M M  M   E         N  N   N    U     U\n");
    printf("\t\t\033[0;31mM   M   M A       A IIIII  N    N N          M   M   M   EEEEEEE   N    N N    UUUUUUU \033[0m\n");
	printf("\n\n");
	printf("\t    1\033[0;34m    TTTTT  EEEE TTTTT  RRRR   III   SSSS\033[0m\n");
    printf("\t  111      T    E      T    R   R   I   S \n");
    printf("\t    1 --\033[0;34m   T    EEE    T    RRRR    I    SSS\033[0m\n");
    printf("\t    1      T    E      T    R  R    I       S\n");
    printf("\t  1111\033[0;34m     T    EEEE   T    R   R  III  SSSS\033[0m\n");
	printf("\n\n");
	printf("\t  222\033[0;35m    TTTTT  Y   Y  PPPP   EEEE  RRRR       A      CCCC  EEEE  RRRR\033[0m\n");
    printf("\t 2   2\033[0;35m     T     Y Y   P   P  E     R   R     A A     C     E     R   R\033[0m\n");
    printf("\t    2  --\033[0;35m  T      Y    PPPP   EEE   RRRR     AAAAA    C     EEE   RRRR\033[0m\n");
    printf("\t   2\033[0;35m       T      Y    P      E     R  R    A     A   C     E     R  R\033[0m\n");
    printf("\t 222222\033[0;35m    T      Y    P      EEEE  R   R  A       A  CCCC  EEEE  R   R\033[0m\n");
	printf("\n\n");
    printf("\t 3333\033[0;32m    X     X\033[0m             \033[1;33m00000\033[0m\n");
    printf("\t    3\033[0;32m     X   X\033[0m             \033[1;33m0   / 0\033[0m\n");
    printf("\t  333 --\033[0;32m    X\033[0m               \033[1;33m0  /  0\033[0m\n");
    printf("\t    3\033[0;32m     X   X\033[0m             \033[1;33m0 /   0\033[0m\n");
    printf("\t 3333\033[0;32m    X     X\033[0m   #######   \033[1;33m00000 \033[0m\n");
	char choice;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	scanf("%c", &choice);
	switch (choice) {
	case '1':
		tetris();
		break;
	case '2':
		typeRacer();
		break;
	case '3':
		Tic_Tac_Toe();
		break;
	default:
		break;
	}
	return 0;
}