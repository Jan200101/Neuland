#include <ncurses.h>

#include "defines.hpp"
#include "frontend/cliinterface.hpp"

/**
 * @brief creates ncurses window with given value and returns it
 *
 * @return WINDOW*
 * @retval returns freshly allocated WINDOW pointer
 *
 * @param height
 * @param width
 * @param starty
 * @param startx
 */
WINDOW* create_newwin(int height, int width, int starty, int startx)
{
    WINDOW* local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0); /* 0, 0 gives default characters 
                           * for the vertical and horizontal
                           * lines            */
    wrefresh(local_win);  /* Show that box        */

    return local_win;
}

/**
 * @brief makes window invisible and then deletes it
 *
 * @param local_win
 */
void destroy_win(WINDOW* local_win)
{
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    wrefresh(local_win);
    delwin(local_win);
}

CliWindow::CliWindow(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

/**
 * @brief main interface loop
 *
 * @return int
 * @retval returns status code
 */
int CliWindow::exec()
{
    WINDOW* my_win;
    int keych;

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME_UPPER);
    refresh();

    my_win = create_newwin(LINES - 3, COLS - 4, 2, 2);
    curs_set(0);

    while ((keych = getch()) != KEY_F(1))
    {
        curs_set(0);
        refresh();
        switch (keych)
        {
            case KEY_RESIZE:
                destroy_win(my_win);

                /* Clears title bar */
                for (int x = 0; x <= 1; ++x)
                    for (int y = 0; y <= COLS; ++y)
                        mvprintw(x, y, " ");

                mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME_UPPER);
                my_win = create_newwin(LINES - 3, COLS - 4, 2, 2);

                break;
        }
    }

    endwin(); /* End curses mode		  */
    return 0;
}