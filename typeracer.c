#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#define MAX_LEN 1000
#define TOTAL_LINES 30

void initDisplay(char text[]) {
    initscr();
    cbreak();;
    mvprintw(0, 0, "\tWrite this sentence:\n\n%s",text);
    mvprintw(6, 0, "Input: ");
    refresh();
}

int randomLine() {
    srand(time(NULL));
    return rand() % TOTAL_LINES - 1;
}

void getText(char text[]) {
    FILE* fin = fopen("sentences.in", "r");
    int currentLine = 0;
    int randomline = randomLine();
    char ch;
    while (currentLine < randomline && (ch = fgetc(fin)) != EOF) {
        if (ch == '\n') {
            currentLine++;
        }
    }
    ch = fgetc(fin);
    int position = 0;
    while (ch != '\n') {
        text[position++] = ch;
        ch = fgetc(fin);
    }
    text[position] = '\0';
    fclose(fin);
    return;
}

void initLoadingbar(char loading_bar[], int size) {
    int position = 0;
    for(position = 0; position < size; position++)
        loading_bar[position] = '.';
    loading_bar[position] = '\0';
    return;
}

void printLoadingBar(char loading_bar[]) {
    move(9, 0);
    clrtoeol();
    mvprintw(9, 0, "[%s]", loading_bar);
    refresh();
    return;
}

void printSpeed(double speed) {
    mvprintw(12, 0, "Caractere pe secunda: %.2f", speed);
    refresh();
    return;
}

void printTimeLeft(int TimeLeft) {
    mvprintw(12, 30, "Timp ramas: %d secunde", TimeLeft);
    refresh();
}

void moveCursorInput(int charactersFilled) {
    move(6, 7 + charactersFilled);
    refresh();
    return;
}

extern void typeRacer() {
    int WINSTATE = 0;
    char progress[MAX_LEN];
    char text[MAX_LEN];
    char loading_bar[MAX_LEN];
    getText(text);
    int size = (strlen(text) / 2);
    initDisplay(text);
    initLoadingbar(loading_bar, size);
    printLoadingBar(loading_bar);
    double speed = 0.0;
    printSpeed(speed);
    int TimeLeft = (strlen(text) / 4);
    printTimeLeft(TimeLeft);
    unsigned int charactersFilled = 0;
    unsigned int charactersRead = 0;
    moveCursorInput(charactersFilled);
    clock_t start = time(NULL), end, countdowninit;
    countdowninit = start;
    timeout(0);
    unsigned int position = 0;
    while (TimeLeft > 0) {
        time_t current = time(NULL);
        int elapsed = difftime(current, countdowninit);
        if (elapsed >= 1) {
            TimeLeft--;
            countdowninit = current;
        }
        printTimeLeft(TimeLeft);
        moveCursorInput(charactersRead);
        clrtoeol();
        usleep(100000);
        int ok = 1;
        int ch = getch();
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (charactersFilled > 0) {
                moveCursorInput(charactersRead - 1);
                clrtoeol();
                if(position != 0 && progress[charactersFilled - 1] == text[charactersFilled - 1] && charactersRead == charactersFilled) {
                    if ((charactersFilled % 2)) {
                        loading_bar[position - 1] = '.';
                        position--;
                    }
                    ok = 1;
                    progress[charactersFilled - 1] = '\0';
                    charactersFilled--;
                }
                printLoadingBar(loading_bar);
                end = time(NULL);
                if(charactersFilled != 0)
                    speed = (double)(end - start) / charactersFilled;
                printSpeed(speed);
                charactersRead--;
            }
        } else if ((charactersFilled < strlen(text)) && ch >= 32 && ch <= 127) {
            if(ch == text[charactersFilled] && charactersFilled % 2 && ok == 1) {
                loading_bar[position] = '#';
                position++;
            } else if (ch != text[charactersFilled]) {
                ok = 0;
            }
            if(ch == text[charactersFilled]) {
                progress[charactersFilled] = ch;
                progress[charactersFilled + 1] = '\0';
                charactersFilled++;
            }
            printLoadingBar(loading_bar);
            end = time(NULL);
            if(charactersFilled != 0)
                speed = (double)(end - start) / charactersFilled;
            printSpeed(speed);
            if(charactersFilled == strlen(text) && strcmp(progress, text) == 0) {
                WINSTATE = 1;
                break;
            }
            charactersRead++;
        } else if (charactersFilled == strlen(text)) {
            break;
        }
    }
    clear();
    endwin();
    system("clear");
    if (WINSTATE) {
        printf("\n-----Felicitari! Ai fost rapid!-----\n");
    } else {
        printf("\n-----Din pacate ai pierdut! Quicker next time!-----\n");
    }
    printf("\n-----Caractere pe secunda: %.2f-----\n\n", speed);
    return ;
}
