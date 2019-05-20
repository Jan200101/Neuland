#include <ncurses/ncurses.h>

#include "defines.hpp"
#include "frontend/cliinterface.hpp"

#define WINCOLOR 1
#define TEXTCOLOR 2

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
WINDOW* createWin(int height, int width, int starty, int startx)
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
void destroyWin(WINDOW* local_win)
{
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    wrefresh(local_win);
    delwin(local_win);
}

void createTextbox(WINDOW* win, int starty, int startx, int width, char* string, bool color)
{
    int length, temp;
    int x, y;

    if (win == nullptr)
        win = stdscr;

    getyx(win, y, x);

    if (startx != 0)
        x = startx;

    if (starty != 0)
        y = starty;

    length = std::strlen(string);
    temp = (width - length) / 2;
    x += temp;

    if (color)
        attron(COLOR_PAIR(TEXTCOLOR));
    mvwprintw(win, y, x, "%s", string);
    if (color)
        attroff(COLOR_PAIR(TEXTCOLOR));

    refresh();
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
    WINDOW* win;
    int keych;

    bool hasColor;

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    if ((hasColor = has_colors()) == TRUE)
    {
        // init colors
        start_color();
        init_pair(WINCOLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(TEXTCOLOR, COLOR_BLACK, COLOR_WHITE);
    }

    // print text in the middle of the head
    mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME_UPPER);
    refresh();

    // creates a window thats visually 1 smaller than the terminal
    win = createWin(LINES - 3, COLS - 4, 2, 2);
    curs_set(0);

    while ((keych = getch()) != 'q')
    {
        curs_set(0);
        refresh();
        switch (keych)
        {
            case KEY_RESIZE:
                destroyWin(win);

                /* Clears title bar */
                for (int x = 0; x <= 1; ++x)
                    for (int y = 0; y <= COLS; ++y)
                        mvprintw(x, y, " ");

                // print text in the middle of the title
                mvprintw(1, COLS / 2 - NAME_LENGTH / 2, "%s", NAME_UPPER);
                win = createWin(LINES - 3, COLS - 4, 2, 2);

                break;
        }
    }

    endwin(); /* End curses mode		  */
    return 0;
}