#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define HEIGHT 24
#define WIDTH 24
#define SIDES 4

typedef struct {
    char Ipiece[8][8];
    char Lpiece[8][8];
    char Opiece[8][8];
    char Tpiece[8][8];
}Pieces;

Pieces* definePieces() {
    Pieces* piese = (Pieces*) malloc (SIDES * sizeof(Pieces));

    //---NORTH---
    // Ipiece
    strcpy(piese[0].Ipiece[0], "########");
    // Lpiece
    strcpy(piese[0].Lpiece[0], "##");
    strcpy(piese[0].Lpiece[1], "######");
    // Opiece
    strcpy(piese[0].Opiece[0], "####");
    strcpy(piese[0].Opiece[1], "####");
    // Tpiece
    strcpy(piese[0].Tpiece[0] + 2 , "##");
    strcpy(piese[0].Tpiece[1], "######");

    //---EAST---
    // Ipiece
    strcpy(piese[1].Ipiece[0] + 4, "#");
    strcpy(piese[1].Ipiece[1] + 4, "#");
    strcpy(piese[1].Ipiece[2] + 4, "#");
    strcpy(piese[1].Ipiece[3] + 4, "#");
    // Lpiece
    strcpy(piese[1].Lpiece[0] + 2, "####");
    strcpy(piese[1].Lpiece[1] + 2, "##");
    strcpy(piese[1].Lpiece[2] + 2, "##");
    // Opiece
    strcpy(piese[1].Opiece[0], "####");
    strcpy(piese[1].Opiece[1], "####");
    // Tpiece
    strcpy(piese[1].Tpiece[0] + 2, "##");
    strcpy(piese[1].Tpiece[1] + 2, "####");
    strcpy(piese[1].Tpiece[2] + 2, "##");

    //---SOUTH---
    // Ipiece
    strcpy(piese[2].Ipiece[0], "########");
    // Lpiece
    strcpy(piese[2].Lpiece[0], "######");
    strcpy(piese[2].Lpiece[1] + 4, "##");
    // Opiece
    strcpy(piese[2].Opiece[0], "####");
    strcpy(piese[2].Opiece[1], "####");
    // Tpiece
    strcpy(piese[2].Tpiece[0], "######");
    strcpy(piese[2].Tpiece[1] + 2, "##");

    //---WEST---
    // Ipiece
    strcpy(piese[3].Ipiece[0] + 2, "#");
    strcpy(piese[3].Ipiece[1] + 2, "#");
    strcpy(piese[3].Ipiece[2] + 2, "#");
    strcpy(piese[3].Ipiece[3] + 2, "#");
    // Lpiece
    strcpy(piese[3].Lpiece[0] + 2, "##");
    strcpy(piese[3].Lpiece[1] + 2, "##");
    strcpy(piese[3].Lpiece[2], "####");
    // Opiece
    strcpy(piese[3].Opiece[0], "####");
    strcpy(piese[3].Opiece[1], "####");
    // Tpiece
    strcpy(piese[3].Tpiece[0] + 2, "##");
    strcpy(piese[3].Tpiece[1], "####");
    strcpy(piese[3].Tpiece[2] + 2, "##");
    return piese;
}

typedef enum {
    North, East, South, West
}facing;

void initColor(void) {
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLUE);  // Bordura
    init_pair(2, COLOR_GREEN, COLOR_GREEN);  // Piesele
}

void printBorder(void) {
    attron(COLOR_PAIR(1));
    mvhline(0, 0, ACS_CKBOARD, WIDTH);
    mvvline(0, 0, ACS_CKBOARD, HEIGHT);
    mvhline(HEIGHT - 1, 0, ACS_CKBOARD, WIDTH);
    mvvline(0, WIDTH - 1, ACS_CKBOARD, HEIGHT);
    attroff(COLOR_PAIR(1));
    refresh();
}

void printPiesa(char piesa[8][8], int x, int y) {
    attron(COLOR_PAIR(2));
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            if (piesa[i][j] == '#') {
                mvprintw(x + i, y + j, "#");
            }
        }
    }
    attroff(COLOR_PAIR(2));
    refresh();
}
void clearAfter(int x, int y, int type, facing orientation) {
    if(type == 0) {
        switch (orientation) {
            case North:
                for (size_t i = 0; i < 1; i++) {
                    for (size_t j = 0; j < 8; j++) {
                        mvprintw(x + i, y + j, " ");
                    }
                }
                break;
            case South:
                for (size_t i = 0; i < 1; i++) {
                    for (size_t j = 0; j < 8; j++) {
                        mvprintw(x + i, y + j, " ");
                    }
                }
                break;
            case East:
                for (size_t i = 0; i < 4; i++) {
                    for (size_t j = 0; j < 1; j++) {
                        mvprintw(x + i, y + j + 4, " ");
                    }
                }
                break;
            case West:
                for (size_t i = 0; i < 4; i++) {
                    for (size_t j = 0; j < 1; j++) {
                        mvprintw(x + i, y + j + 2, " ");
                    }
                }
                break;
        }
    } else if (type == 1) {
        switch (orientation) {
            case North:
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x, y + j, " ");
                }
                for (size_t j = 0; j < 6; j++) {
                    mvprintw(x + 1, y + j, " ");
                }
                break;
            case South:
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x + 1 , y + j + 4, " ");
                }
                for (size_t j = 0; j < 6; j++) {
                    mvprintw(x, y + j, " ");
                }
                break;
            case East:
                for (size_t j = 0; j < 4; j++) {
                    mvprintw(x, y + j + 2, " ");
                }
                for (size_t i = 0; i < 2; i++) {
                    for (size_t j = 0; j < 2; j++) {
                        mvprintw(x + i + 1, y + j + 2, " ");
                    }
                }
                break;
            case West:
                for (size_t i = 0; i < 2; i++) {
                    for (size_t j = 0; j < 2; j++) {
                    mvprintw(x + i, y + j + 2, " ");
                    }
                }
                 for (size_t j = 0; j < 4; j++) {
                        mvprintw(x + 2, y + j, " ");
                    }
                break;
        }
    } else if (type == 2) {
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 4; j++) {
                mvprintw(x + i, y + j, " ");
        }
    }
    } else if (type == 3) {
        switch (orientation) {
            case North:
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x, y + j + 2, " ");
                }
                for (size_t j = 0; j < 6; j++) {
                    mvprintw(x + 1, y + j, " ");
                }
                break;
            case South:
                for (size_t j = 0; j < 6; j++) {
                    mvprintw(x, y + j, " ");
                }
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x + 1, y + j + 2, " ");
                }
                break;
            case East:
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x, y + j + 2, " ");
                }
                for (size_t j = 0; j < 4; j++) {
                    mvprintw(x + 1, y + j + 2, " ");
                }
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x + 2, y + j + 2, " ");
                }
                break;
            case West:
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x, y + j + 2, " ");
                }
                for (size_t j = 0; j < 4; j++) {
                    mvprintw(x + 1, y + j, " ");
                }
                for (size_t j = 0; j < 2; j++) {
                    mvprintw(x + 2, y + j + 2, " ");
                }
                break;
        }
    }
    refresh();
}

int getType() {
    srand(time(NULL));
    return rand() % 4;
}

int getCoord() {
    srand(time(NULL));
    return 1 + rand() % (WIDTH - 10);
}

int getOrientation() {
    srand(time(NULL) + 1);
    return rand() % 4;
}

void getPiece(int TableMatrix[HEIGHT][WIDTH], int x, int y, char piesa[8][8], int type, facing orientation, Pieces* piese, int ok) {
    if (type == 0)
    switch (orientation) {
        case North:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[0].Ipiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[0].Ipiece[i][j];
                }
                    
            break;
        case East:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[1].Ipiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[1].Ipiece[i][j];
                }
                    
            break;
        case South:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[2].Ipiece[i][j] == '#')
                        if (ok == 1) TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[2].Ipiece[i][j];
                }
                    
            break;
        case West:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[3].Ipiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[3].Ipiece[i][j];
                }
                    
    }
    if (type == 1)
    switch (orientation) {
        case North:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[0].Lpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[0].Lpiece[i][j];
                }
                    
            break;
        case East:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[1].Lpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[1].Lpiece[i][j];
                }
                    
            break;
        case South:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[2].Lpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[2].Lpiece[i][j];
                }
                    
            break;
        case West:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[3].Lpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[3].Lpiece[i][j];
                }
                    
    }
    if (type == 2)
    switch (orientation) {
        case North:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[0].Opiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[0].Opiece[i][j];
                }
                    
            break;
        case East:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[1].Opiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[1].Opiece[i][j];
                    } 
                    
            break;
        case South:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[2].Opiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[2].Opiece[i][j];
                }
                    
            break;
        case West:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[3].Opiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[3].Opiece[i][j];
                }
                    
    }
    if (type == 3)
    switch (orientation) {
        case North:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[0].Tpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[0].Tpiece[i][j];
                }
                    
            break;
        case East:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[1].Tpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[1].Tpiece[i][j];
                }
                    
            break;
        case South:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[2].Tpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[2].Tpiece[i][j];
                }
                    
            break;
        case West:
            for(size_t i = 0; i < 8; i++)
                for(size_t j = 0; j < 8; j++) {
                    if (piese[3].Tpiece[i][j] == '#')
                        if (ok == 1)TableMatrix[x + i][y + j] = 1;
                    piesa[i][j] = piese[3].Tpiece[i][j];
                }
                    
    }
    return;
}
int hittingSurface(int TableMatrix[HEIGHT][WIDTH], int x, int y, int type, facing orientation) {
    if(type == 0) {
        switch(orientation) {
            case North:
                for(size_t j = y; j < y + 8; j++) {
                    if(TableMatrix[x + 1][j] == 1)
                        return 1;
                }
                break;
            case South:
                for(size_t j = y; j < y + 8; j++) {
                    if(TableMatrix[x + 1][j] == 1)
                        return 1;
                }
                break;
            case East:
                for(size_t j = y; j < y + 1; j++) {
                    if(TableMatrix[x + 4][j + 4] == 1)
                        return 1;
                }
                break;
            case West:
                for(size_t j = y; j < y + 1; j++) {
                    if(TableMatrix[x + 4][j + 2] == 1)
                        return 1;
                }
                break;
        }
    }
    if(type == 1) {
        switch(orientation) {
            case North:
                for(size_t j = y; j < y + 6; j++) {
                    if(TableMatrix[x + 2][j] == 1)
                        return 1;
                }
                break;
            case East:
                for(size_t j = y; j < y + 2; j++) {
                    if(TableMatrix[x + 3][j + 2] == 1)
                        return 1;
                }
                for(size_t j = y + 2; j < y + 4; j++) {
                    if(TableMatrix[x + 1][j + 2] == 1)
                        return 1;
                }
                break;
            case South:
                for(size_t j = y; j < y + 4; j++) {
                    if(TableMatrix[x + 1][j] == 1)
                        return 1;
                }
                for(size_t j = y + 4; j < y + 6; j++) {
                    if(TableMatrix[x + 2][j] == 1)
                        return 1;
                }
                break;
            case West:
                for(size_t j = y; j < y + 4; j++) {
                    if(TableMatrix[x + 3][j] == 1)
                        return 1;
                }
                break;
        }
    }
    if(type == 2) {
        for (size_t j = y; j < y + 4; j++) {
            if(TableMatrix[x + 2][j] == 1)
                return 1;
        }
    }
    if(type == 3) {
        switch(orientation) {
            case North:
                for(size_t j = y; j < y + 6; j++) {
                    if(TableMatrix[x + 2][j] == 1)
                        return 1;
                }
                break;
            case East:
                for(size_t j = y; j < y + 2; j++) {
                    if(TableMatrix[x + 3][j + 2] == 1)
                        return 1;
                }
                for(size_t j = y + 2; j < y + 4; j++) {
                    if(TableMatrix[x + 2][j + 2] == 1)
                        return 1;
                }
                break;
            case South:
                for(size_t j = y; j < y + 2; j++) {
                    if(TableMatrix[x + 1][j] == 1)
                        return 1;
                }
                for(size_t j = y + 4; j < y + 6; j++) {
                    if(TableMatrix[x + 1][j] == 1)
                        return 1;
                }
                for(size_t j = y + 2; j < y + 4; j++) {
                    if(TableMatrix[x + 2][j] == 1)
                        return 1;
                }
                break;
            case West:
                for(size_t j = y ; j < y + 2; j++) {
                    if(TableMatrix[x + 3][j + 2] == 1)
                        return 1;
                }
                for(size_t j = y; j < y + 2; j++) {
                    if(TableMatrix[x + 2][j] == 1)
                        return 1;
                }
                break;
        }
    }
    return 0;
}
int main() {
    initscr();
    initColor();
    Pieces* piese = definePieces();
    int TableMatrix[HEIGHT][WIDTH];
    for (size_t i = 0; i < HEIGHT; i++)
        if(i == HEIGHT - 1) {
            for(size_t j = 0; j < WIDTH; j++)
            TableMatrix[i][j] = 1;
        } else {
            for(size_t j = 0; j < WIDTH; j++)
                TableMatrix[i][j] = 0;
        }
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    printBorder();
    int type;
    facing orientaion;
    int max_level;
    bool shouldContinue = true;
    while (shouldContinue == true) {
        orientaion = getOrientation();
        type = getType();
        char Piesa[8][8];
        int coord1 = 1;
        int coord2 = getCoord();
        int ok = 0;
        int hitting = 0;
        while(!hitting) {
            hitting = hittingSurface(TableMatrix, coord1, coord2, type, orientaion);
            if (hitting == 1)
                ok = 1;
            getPiece(TableMatrix, coord1, coord2, Piesa, type, orientaion, piese, ok);
            printPiesa(Piesa, coord1, coord2);
            if(hitting == 1 && coord1 == 1) {
                shouldContinue = false;
                break;
            }
            if(hitting == 1)
                break;
            usleep(300000);
            if (hitting == 0)
                clearAfter(coord1, coord2, type, orientaion);
            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    if (orientaion == West)
                        orientaion = North;
                    else
                        orientaion++;
                    break;
                case KEY_DOWN:
                    coord1++;
                    hitting = hittingSurface(TableMatrix, coord1, coord2, type, orientaion);
                    if (hitting == 1)
                        ok = 1;
                    getPiece(TableMatrix, coord1, coord2, Piesa, type, orientaion, piese, ok);
                    printPiesa(Piesa, coord1, coord2);
                    if(hitting == 1 && coord1 == 1) {
                        shouldContinue = false;
                        hitting = 0;
                        break;
                    }
                    if (hitting == 0)
                        clearAfter(coord1, coord2, type, orientaion);
                    break;
                case KEY_RIGHT:
                    if(coord2 < (WIDTH))
                        coord2++;
                    break;
                case KEY_LEFT:
                    if(coord2 > 1)
                        coord2--;
                    break;
                case 'q':
                    shouldContinue = false;
                    hitting = 1;
                    break;
            }
            coord1++;
        }
        if(shouldContinue == false) {
            endwin();
            printf("Ai pierdut!:(\n");
        }
    }
    for (size_t i = 0; i < 24; i++) {
        for(size_t j = 0; j < 24; j++)
            printf("%d ", TableMatrix[i][j]);
        printf("\n");
    }
    printf("type%d %d", type, orientaion);
        
    return 0;
}