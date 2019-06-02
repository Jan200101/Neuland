#include <ncurses/ncurses.h>
#include <fstream>

#include "defines.hpp"

#include "frontend/cliinterface.hpp"

#include "backend/config.hpp"
#include "backend/dirs.hpp"
#include "backend/files.hpp"

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
 */
WINDOW*
createWin(int height, int width, int starty, int startx)
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
    if (win == nullptr)
        return;

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

    exitkey = KEY_END;

    config = Config::readConfig();

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
    std::ifstream file;
    Json::Value card;
    std::string categories;

    WINDOW* win = nullptr;
    WINDOW* list = nullptr;

    WINDOW* Buttons[3] = {
        nullptr,
        nullptr,
        nullptr,
    };

    constexpr char ButtonText[3][12] = {
        "Neu",
        "Importieren",
        "OK",
    };

    short cursorpos = 0;
    int keych = 0;

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

    // hide Cursor
    curs_set(0);

    do
    {
        switch (keych)
        {
            case 10: // Enter is 10 on my machine so ???
            case KEY_ENTER:
            case 'O':
            case 'o':
                clear();
                do
                {
                    mvprintw(0, 0, "O\nI still have to implement this.");
                } while ((keych = getch()) != exitkey);
                break;

            case 'N':
            case 'n':
                clear();
                do
                {
                    destroyWin(win);
                    refresh();

                    win = createWin(LINES - 3, COLS - 4, 2, 2);

                    mvprintw(0, 0, "N\nI still have to implement this.");
                } while ((keych = getch()) != exitkey);
                break;

            case 'I':
            case 'i':
                clear();
                do
                {
                    mvprintw(0, 0, "I\nI still have to implement this.");
                } while ((keych = getch()) != exitkey);
                break;

            case KEY_UP:
                if (--cursorpos < 0)
                    ++cursorpos;
                break;

            case KEY_DOWN:
                if (++cursorpos < 0)
                    --cursorpos;
                break;
        }

        // cleanup all Windows
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

        // print file names

        short textpos = 0;

        mvprintw(4 + textpos, 7, "Title");
        mvprintw(4 + textpos, 20, "Anzahl");
        mvprintw(4 + textpos, 30, "Kategorien");

        for (auto& p : Backend::listCarddir())
        {
            categories.clear();
            file.open(p.path().c_str());
            card = Backend::parseFile(file);

            if ((3 + textpos++) > LINES - 8)
                break;
            if (cursorpos + 1 == textpos)
            {
                attron(A_BOLD);
                mvprintw(4 + textpos, 5, "*");
                attroff(A_BOLD);
            }

            int size = card.get("categories", Json::Value()).size();
            for (int i = 0; i < size; ++i)
            {
                if (!categories.empty())
                    categories += " ,";
                categories += card.get("categories", Json::Value())[i].asString();
            }

            mvprintw(4 + textpos, 7, "%s", p.path().stem().string().c_str());
            mvprintw(4 + textpos, 20, "%u", card.get("cards", Json::Value()).size());
            mvprintw(4 + textpos, 30, "%s", categories.c_str());

            file.close();
        }

        attron(A_UNDERLINE);
        mvprintw(LINES - 4, 5, ButtonText[0]);                 // 0
        mvprintw(LINES - 4, 5 + (COLS / 5), ButtonText[1]);    // 1
        mvprintw(LINES - 4, COLS - (COLS / 5), ButtonText[2]); // 2
        attroff(A_UNDERLINE);

        mvprintw(LINES - 4, 6, &ButtonText[0][1]);                     // 0
        mvprintw(LINES - 4, 6 + (COLS / 5), &ButtonText[1][1]);        // 1
        mvprintw(LINES - 4, COLS - (COLS / 5) + 1, &ButtonText[2][1]); // 2

        // Windows are used for the Buttons because they give it a "button" feel
        Buttons[0] = createWin(3, (COLS / 5), LINES - 5, 3);
        Buttons[1] = createWin(3, (COLS / 5), LINES - 5, 3 + (COLS / 5));
        Buttons[2] = createWin(3, (COLS / 5), LINES - 5, COLS - (COLS / 5) - 3);
        //    Neu Importieren OK

        mvprintw(0, 0, "%i %i", KEY_ENTER, keych);

        refresh();
    } while ((keych = getch()) != exitkey);

    endwin(); /* End curses mode		  */
    return 0;
}