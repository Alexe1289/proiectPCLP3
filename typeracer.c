#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>

#define MAX_LEN 1000
#define TOTAL_LINES 17

void initDisplay(char text[]) {
    initscr();
    cbreak();;
    mvprintw(0, 0, "\tWrite this sentence:\n\n%s",text);
    mvprintw(6, 0, "Input: ");
    refresh();
}

int randomLine() {
    srand(time(NULL));
    return rand() % TOTAL_LINES;
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
}

void printSpeed(double speed) {
    move(12, 0);
    mvprintw(12, 0, "Caractere pe secunda: %.2f", speed);
    refresh();
}

void moveCursorInput(int charactersFilled) {
    move(6, 7 + charactersFilled);
    move(6, 7 + charactersFilled);
    refresh();
}

int main() {
    char progress[MAX_LEN];
    char text[MAX_LEN];
    char loading_bar[MAX_LEN];
    getText(text);
    int size = (strlen(text) / 2);
    initDisplay(text);
    refresh();
    initLoadingbar(loading_bar, size);
    printLoadingBar(loading_bar);
    double speed = 0.0;
    printSpeed(speed);
    unsigned int charactersFilled = 0;
    moveCursorInput(charactersFilled);
    clock_t start = time(NULL), end;
    // move cursor at input block
    unsigned int position = 0;
    while (1) {
        moveCursorInput(charactersFilled);
        clrtoeol();
        int ch = getch();
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (charactersFilled > 0) {
                moveCursorInput(charactersFilled - 1);
                clrtoeol();
                if(position != 0 && progress[charactersFilled - 1] == text[charactersFilled - 1] && charactersFilled % 2) {
                    loading_bar[position - 1] = '.';
                    position--;
                }
                printLoadingBar(loading_bar);
                progress[charactersFilled - 1] = '\0';
                end = time(NULL);
                charactersFilled--;
                if(charactersFilled != 0)
                    speed = (double)(end - start) / charactersFilled;
                printSpeed(speed);
            }
        } else if ((charactersFilled < strlen(text) - 1)) {
            if(ch == text[charactersFilled] && charactersFilled % 2) {
                loading_bar[position] = '#';
                position++;
            }
            if(ch == text[charactersFilled])
            printLoadingBar(loading_bar);
            progress[charactersFilled] = ch;
            progress[charactersFilled + 1] = '\0';
            charactersFilled++;
            end = time(NULL);
            if(charactersFilled != 0)
                speed = (double)(end - start) / charactersFilled;
            printSpeed(speed);
            if(charactersFilled == strlen(text))
                break;
        } else {
            break;
        }
    }
    endwin();
    printf("\n-----Caractere pe secunda: %.2f-----\n\n", speed);
    return 0;
}
