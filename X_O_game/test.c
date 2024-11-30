#include <ncurses.h>

int main() {
    initscr();  // Initialize ncurses
    cbreak();   // Disable line buffering (disable Enter key waiting)
    noecho();   // Disable automatic echoing of input

    int key;

    while (1) {
        key = getch();  // Read the pressed key
        // Process the key
        printw("Pressed key: %c\n", key);
        refresh();  // Refresh the screen
    }

    endwin();  // End ncurses

    return 0;
}
