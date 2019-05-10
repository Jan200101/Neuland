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
    keypad(stdscr, TRUE);
    noecho();

    mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME_UPPER);
    refresh();

    my_win = newwin(LINES - 3, COLS - 4, 2, 2);
    box(my_win, 0, 0);
    wrefresh(my_win);
    curs_set(0);

    while ((ch = getch()) != KEY_F(1))
    {
        curs_set(0);
        refresh();
        switch (ch)
        {
            case KEY_RESIZE:
                wrefresh(my_win);
                delwin(my_win);

                for (int x = 0; x <= 1; ++x)
                    for (int y = 0; y <= COLS; ++y)
                        mvprintw(x, y, " ");

                mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME_UPPER);

                my_win = newwin(LINES - 3, COLS - 4, 2, 2);
                box(my_win, 0, 0);

                wrefresh(my_win);
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