#include <ncurses/ncurses.h>
#include <iostream>

#include "defines.hpp"
#include "frontend/cliinterface.hpp"

#define TEXTCOLOR 1
#define TITLECOLOR 2

/**
 * @brief      creates ncurses window with given value and returns it
 *
 * @param      height   The height
 * @param      width    The width
 * @param      starty   The starty
 * @param      startx   The startx
 *
 * @return     WINDOW*
 * @retval     returns  freshly allocated WINDOW pointer
 */
WINDOW* createWin(int height, int width, int starty, int startx)
{
    WINDOW* win;

    win = newwin(height, width, starty, startx);
    box(win, 0, 0); /* 0, 0 gives default characters 
                     * for the vertical and horizontal
                     * lines            */
    wrefresh(win);  /* Show that box        */

    return win;
}

/**
 * @brief      makes window invisible and then deletes it
 *
 * @param      win   The window
 */
void destroyWin(WINDOW* win)
{
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    wrefresh(win);
    delwin(win);
}

/**
 * @brief      creates a text box esk object on the screen
 *
 * @param      win     The window
 * @param      starty  The starty
 * @param      startx  The startx
 * @param      width   The width
 * @param      color   The color
 */
void createTextbox(WINDOW* win, int starty, int startx, int width, bool color)
{
    char* temp = new char[width + 1];

    for (int i = 0; i < width; ++i)
        temp[i] = ' ';

    if (win == nullptr)
        win = stdscr;

    if (color)
        attron(COLOR_PAIR(TEXTCOLOR));
    mvwprintw(win, starty, startx, "%s", temp);
    if (color)
        attroff(COLOR_PAIR(TEXTCOLOR));

    refresh();
}

CliWindow::CliWindow(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;

    exitkey = 'q';

    hasColors = true;
}

/**
 * @brief      main interface loop
 *
 * @return     int
 * @retval     returns  status code
 */
int CliWindow::exec()
{
    WINDOW* win;
    WINDOW* list;

    WINDOW* Buttons[3];

    int keych;

    initscr();

    if (hasColors)
    {
        start_color();
        init_pair(TEXTCOLOR, COLOR_BLACK, COLOR_WHITE);
        init_pair(TITLECOLOR, COLOR_RED, COLOR_BLACK);
    }

    raw();
    keypad(stdscr, true);
    noecho();

    // print text in the middle of the head
    if (hasColors)
        attron(COLOR_PAIR(TITLECOLOR));
    mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME);
    if (hasColors)
        attroff(COLOR_PAIR(TITLECOLOR));

    refresh();

    // creates a window thats visually 1 smaller than the terminal
    win = createWin(LINES - 3, COLS - 4, 2, 2);
    list = createWin(LINES - 8, COLS - 6, 3, 3);

    Buttons[0] = createWin(3, (COLS / 7), LINES - 5, 3);
    Buttons[1] = createWin(3, (COLS / 7), LINES - 5, 3 + (COLS / 7));
    Buttons[2] = createWin(3, (COLS / 7), LINES - 5, COLS - (COLS / 7) - 3);
    //    Neu Importieren OK

    // hide Cursor
    curs_set(0);

    while ((keych = getch()) != exitkey)
    {
        switch (keych)
        {
            case KEY_RESIZE:
                destroyWin(win);
                destroyWin(list);

                destroyWin(Buttons[0]);
                destroyWin(Buttons[1]);
                destroyWin(Buttons[2]);

                /* Clears title bar */
                for (int x = 0; x <= 1; ++x)
                    for (int y = 0; y <= COLS; ++y)
                        mvprintw(x, y, " ");

                // print text in the middle of the head
                if (hasColors)
                    attron(COLOR_PAIR(TITLECOLOR));
                mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME);
                if (hasColors)
                    attroff(COLOR_PAIR(TITLECOLOR));

                refresh();

                // creates a window thats visually 1 smaller than the terminal
                win = createWin(LINES - 3, COLS - 4, 2, 2);
                list = createWin(LINES - 8, COLS - 6, 3, 3);

                Buttons[0] = createWin(3, (COLS / 7), LINES - 5, 3);
                Buttons[1] = createWin(3, (COLS / 7), LINES - 5, 3 + (COLS / 7));
                Buttons[2] = createWin(3, (COLS / 7), LINES - 5, COLS - (COLS / 7) - 3);
                //    Neu Importieren OK

                break;

            case KEY_UP:
                printw("UP");
                break;

            case KEY_LEFT:
                printw("LEFT");
                break;

            case KEY_RIGHT:
                printw("RIGHT");
                break;

            case KEY_DOWN:
                printw("DOWN");
                break;
        }
        refresh();
    }

    endwin(); /* End curses mode		  */
    return 0;
}