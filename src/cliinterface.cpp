#include <ncurses.h>

#include "cliinterface.hpp"
#include "defines.hpp"

CliWindow::CliWindow(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

int CliWindow::exec()
{
    WINDOW* my_win;
    int ch;

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    mvprintw(1, COLS / 2, "%s", NAME_UPPER);
    refresh();

    my_win = newwin(LINES - 3, COLS - 4, 2, 2);
    box(my_win, 0, 0);
    wrefresh(my_win);

    while ((ch = getch()) != KEY_F(1))
    {
        refresh();
        switch (ch)
        {
            case KEY_RESIZE:
                wborder(my_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                wrefresh(my_win);
                delwin(my_win);

                for (int x = 0; x <= 1; ++x)
                    for (int y = 0; y <= COLS; ++y)
                        mvprintw(x, y, " ");

                mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME_UPPER);

                my_win = newwin(LINES - 3, COLS - 4, 2, 2);
                box(my_win, 0, 0); /* 0, 0 gives default characters 
                     * for the vertical and horizontal
                     * lines            */
                wrefresh(my_win);  /* Show that box      */
                break;
        }

        /*if (starty < LINES)
            starty = LINES;

        if (startx < COLS)
            startx = COLS;*/
    }

    endwin(); /* End curses mode		  */
    return 0;
}