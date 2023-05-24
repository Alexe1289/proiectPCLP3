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
    strcpy(piese[1].Ipiece[0] + 4, "##");
    strcpy(piese[1].Ipiece[1] + 4, "##");
    strcpy(piese[1].Ipiece[2] + 4, "##");
    strcpy(piese[1].Ipiece[3] + 4, "##");
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
    strcpy(piese[3].Ipiece[0] + 2, "##");
    strcpy(piese[3].Ipiece[1] + 2, "##");
    strcpy(piese[3].Ipiece[2] + 2, "##");
    strcpy(piese[3].Ipiece[3] + 2, "##");
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
    init_pair(2, COLOR_WHITE, COLOR_WHITE);  // Piesele
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
                    for (size_t j = 0; j < 2; j++) {
                        mvprintw(x + i, y + j + 4, " ");
                    }
                }
                break;
            case West:
                for (size_t i = 0; i < 4; i++) {
                    for (size_t j = 0; j < 2; j++) {
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
    int random = rand() % (WIDTH - 10);
    if (random % 2) {
        random--;
    }
    return 1 + random;
}

int getOrientation() {
    srand(time(NULL) + 1);
    return rand() % 4;
}

void initTable(int TableMatrix[HEIGHT][WIDTH]) {
    for (size_t i = 0; i < HEIGHT; i++) {
        for(size_t j = 0; j < WIDTH; j++) {
            if (i == HEIGHT - 1)
                TableMatrix[i][j] = 1;
            else if (j == 0 || j == WIDTH - 1)
                TableMatrix[i][j] = 1;
            else
                TableMatrix[i][j] = 0;
        }
    }
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
                for(size_t j = y + 4; j < y + 6; j++) {
                    if(TableMatrix[x + 4][j ] == 1)
                        return 1;
                }
                break;
            case West:
                for(size_t j = y + 2; j < y + 4; j++) {
                    if(TableMatrix[x + 4][j] == 1)
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
                for(size_t j = y + 2; j < y + 4; j++) {
                    if(TableMatrix[x + 3][j] == 1)
                        return 1;
                }
                for(size_t j = y + 4; j < y + 6; j++) {
                    if(TableMatrix[x + 1][j] == 1)
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
                for(size_t j = y + 2; j < y + 4; j++) {
                    if(TableMatrix[x + 3][j] == 1)
                        return 1;
                }
                for(size_t j = y + 4; j < y + 6; j++) {
                    if(TableMatrix[x + 2][j] == 1)
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

bool isHittingLeft(int TableMatrix[HEIGHT][WIDTH],int x, int y, int type, facing orientation) {
    if(type == 0) {
        switch(orientation) {
            case North:
                if(TableMatrix[x][y - 1] == 1)
                    return true;
                break;
            case South:
                if(TableMatrix[x][y - 1] == 1)
                    return true;
                break;
            case East:
                for(size_t i = x; i < x + 4; i++) {
                    if(TableMatrix[i][y + 3] == 1)
                        return true;
                }
                break;
            case West:
                for(size_t i = x; i < x + 4; i++) {
                    if(TableMatrix[i][y + 1] == 1)
                        return true;
                }
                break;
        }
    }
    if(type == 1) {
        switch(orientation) {
            case North:
                if(TableMatrix[x][y - 1] == 1)
                    return true;
                if(TableMatrix[x + 1][y - 1])
                    return true;
                break;
            case East:
                for(size_t i = x; i < x + 3; i++) {
                    if(TableMatrix[i][y + 1] == 1)
                        return true;
                }
                break;
            case South:
                if(TableMatrix[x][y - 1] == 1)
                    return true;
                if(TableMatrix[x + 1][y + 3] == 1)
                    return true;
                break;
            case West:
                for(size_t i = x; i < x + 2; i++) {
                    if(TableMatrix[i][y + 1] == 1)
                        return true;
                }
                if(TableMatrix[x + 2][y - 1] == 1)
                        return true;
                break;
        }
    }
    if(type == 2) {
        for (size_t i = x; i < x + 2; i++) {
            if(TableMatrix[i][y - 1] == 1)
                return true;
        }
    }
    if(type == 3) {
        switch(orientation) {
            case North:
                if(TableMatrix[x][y + 1] == 1)
                    return true;
                if(TableMatrix[x + 1][y - 1] == 1)
                    return true;
                break;
            case East:
                for (size_t i = x; i < x + 3; i++)
                if(TableMatrix[i][y + 1] == 1)
                    return true;
                break;
            case South:
                if(TableMatrix[x][y - 1] == 1)
                    return true;
                if(TableMatrix[x + 1][y + 1] == 1)
                    return true;
                break;
            case West:
                if(TableMatrix[x][y + 1] == 1)
                    return true;
                if(TableMatrix[x + 2][y + 1] == 1)
                    return true;
                if(TableMatrix[x + 1][y - 1] == 1)
                    return true;
                break;
        }
    }
    return false;
}

bool isHittingRight(int TableMatrix[HEIGHT][WIDTH],int x, int y, int type, facing orientation) {
    if(type == 0) {
        switch(orientation) {
            case North:
                if(TableMatrix[x][y + 8] == 1)
                    return true;
                break;
            case South:
                if(TableMatrix[x][y + 8] == 1)
                    return true;
                break;
            case East:
                for(size_t i = x; i < x + 4; i++) {
                    if(TableMatrix[i][y + 6] == 1)
                        return true;
                }
                break;
            case West:
                for(size_t i = x; i < x + 4; i++) {
                    if(TableMatrix[i][y + 4] == 1)
                        return true;
                }
                break;
        }
    }
    if(type == 1) {
        switch(orientation) {
            case North:
                if(TableMatrix[x][y + 2] == 1)
                    return true;
                if(TableMatrix[x + 1][y + 6])
                    return true;
                break;
            case East:
                if(TableMatrix[x][y + 6] == 1)
                    return true;
                for(size_t i = x + 1; i < x + 3; i++) {
                    if(TableMatrix[i][y + 4] == 1)
                        return true;
                }
                break;
            case South:
                for(size_t i = x; i < x + 2; i++) {
                    if(TableMatrix[i][y + 6] == 1)
                        return true;
                }
                break;
            case West:
                 for(size_t i = x; i < x + 3; i++) {
                    if(TableMatrix[i][y + 4] == 1)
                        return true;
                }
                break;
        }
    }
    if(type == 2) {
        for (size_t i = x; i < x + 2; i++) {
            if(TableMatrix[i][y + 4] == 1)
                return true;
        }
    }
    if(type == 3) {
        switch(orientation) {
            case North:
                if(TableMatrix[x][y + 4] == 1)
                    return true;
                if(TableMatrix[x + 1][y + 6] == 1)
                    return true;
                break;
            case East:
                if(TableMatrix[x][y + 4] == 1)
                    return true;
                if(TableMatrix[x + 2][y + 4] == 1)
                    return true;
                if(TableMatrix[x + 1][y + 6] == 1)
                    return true;
                break;
            case South:
                if(TableMatrix[x][y + 6] == 1)
                    return true;
                if(TableMatrix[x + 1][y + 4] == 1)
                    return true;
                break;
            case West:
                for (size_t i = x; i < x + 3; i++) {
                    if(TableMatrix[i][y + 4] == 1)
                return true;
                }
                break;
        }
    }
    return false;
}

bool isBottomFilled(int TableMatrix[HEIGHT][WIDTH]) {
    for(size_t j = 0; j < WIDTH; j++) {
        if (TableMatrix[HEIGHT - 2][j] == 0)
            return false;
    }
    return true;
}

void clearBottom(int TableMatrix[HEIGHT][WIDTH]) {
    for(size_t i = HEIGHT - 2; i > 0; i--)
        for(size_t j = 0; j < WIDTH; j++)
            TableMatrix[i][j] = TableMatrix[i - 1][j];
}
void printNewTable(int TableMatrix[HEIGHT][WIDTH]) {
    for(size_t i = 0 ; i < HEIGHT - 1; i++)
        for(size_t j = 1; j < WIDTH - 1; j++)
            if (TableMatrix[i][j] == 1) {
                attron(COLOR_PAIR(2));
                mvprintw(i, j, "#");
                attroff(COLOR_PAIR(2));
            } else {
                mvprintw(i, j, " ");
            }
    refresh();
}

int initGameplaySpeed() {
    printf("-----SELECT GAMEPLAY SPEED-----\n");
    printf("1. Slow\n");
    printf("2. Normal\n");
    printf("3. Fast\n");
    printf("4. SuperSonic(IMPOSSIBLE)\n");
    int getSpeed = 2;
    int Speed = 300000;
    scanf("%d", &getSpeed);
    if (getSpeed == 1) {
        Speed = 330000;
    } else if (getSpeed == 2) {
        Speed = 250000;
    } else if (getSpeed == 3) {
        Speed = 150000;
    } else if (getSpeed == 4) {
        Speed = 80000;
    }
    return Speed;
}

int main() {
    int Speed = initGameplaySpeed(Speed);
    initscr();
    initColor();
    Pieces* piese = definePieces();
    int TableMatrix[HEIGHT][WIDTH];
    initTable(TableMatrix);
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
        while (isBottomFilled(TableMatrix)){
            clearBottom(TableMatrix);
            printNewTable(TableMatrix);
        }
        orientaion = getOrientation();
        type = getType();
        char Piesa[8][8];
        int coord1 = 1;
        int coord2 = getCoord();
        int hitting = 0;
        while(!hitting) {
            hitting = hittingSurface(TableMatrix, coord1, coord2, type, orientaion);
            getPiece(TableMatrix, coord1, coord2, Piesa, type, orientaion, piese, hitting);
            printPiesa(Piesa, coord1, coord2);
            refresh();
            if(hitting == 1 && coord1 == 1) {
                shouldContinue = false;
                break;
            }
            if(hitting == 1)
                break;
            usleep(Speed);
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
                    getPiece(TableMatrix, coord1, coord2, Piesa, type, orientaion, piese, hitting);
                    printPiesa(Piesa, coord1, coord2);
                    if(hitting == 1 && coord1 == 1) {
                        shouldContinue = false;
                        break;
                    }
                    if(hitting == 1) {
                        break;
                    }
                    if (hitting == 0)
                        clearAfter(coord1, coord2, type, orientaion);
                    break;
                case KEY_RIGHT:
                    if (!isHittingRight(TableMatrix, coord1 + 1, coord2, type, orientaion))
                        coord2 += 2;
                    break;
                case KEY_LEFT:
                    if (!isHittingLeft(TableMatrix, coord1 + 1, coord2, type, orientaion))
                        coord2 -= 2;
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
    // for (size_t i = 0; i < 24; i++) {
    //     for(size_t j = 0; j < 24; j++)
    //         printf("%d ", TableMatrix[i][j]);
    //     printf("\n");
    // }
    // printf("type%d %d", type, orientaion);
        
    return 0;
}