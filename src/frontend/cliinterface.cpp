#include <ncurses/ncurses.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

#include "defines.hpp"

#include "frontend/cliinterface.hpp"

#include "backend/config.hpp"
#include "backend/dirs.hpp"
#include "backend/files.hpp"

#define TEXTCOLOR 1
#define TITLECOLOR 2

namespace fs = std::filesystem;

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
    if (win == nullptr)
        return;

    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    wrefresh(win);
    delwin(win);
}

CliWindow::CliWindow(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;

    exitkey = KEY_END;

    config = Config::readConfig();

    hasColors = true;

    std::srand(config["lastrun"].asInt());
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

    std::vector<fs::directory_entry> paths;
    std::vector<Json::Value> cards;
    std::vector<Json::Value> answers;

    {
        fs::directory_iterator carddir = Backend::listCarddir();

        std::copy(fs::begin(carddir), fs::end(carddir),
                  std::back_inserter(paths));
    }

    WINDOW* Buttons[2] = {
        nullptr,
        nullptr,
    };

    constexpr char ButtonText[2][12] = {
        "Neu",
        "OK",
    };

    unsigned short textpos,
        state,
        curcard,
        scrollpos = 0,
        cursorpos = scrollpos;
    unsigned int keych = 0,
                 highscore = config.get("highscore", 0).asInt();

    std::string title;

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

                keych = 0;
                curcard = -1;
                state = 0;

                if (file.is_open())
                    file.close();
                file.open(paths[cursorpos].path().c_str());
                card = Backend::parseFile(file);
                file.close();

                if (card.get("cards", Json::Value()).empty())
                {
                    mvprintw(0, 0, "Diese Karte enthält keine Fragen");
                    getch();
                    break;
                }

                cards.clear();
                std::copy(card["cards"].begin(), card["cards"].end(),
                          std::back_inserter(cards));

                do
                {
                    if (!answers.empty())
                    {
                        if (answers.size() > keych - '1' && answers[keych - '1'][1].asBool())
                        {
                            cards.erase(cards.begin() + curcard);
                            ++state;
                        }
                    }
                    clear();

                    if (cards.empty())
                        continue;

                    // todo don't change curcard on resize
                    if (keych != KEY_RESIZE)
                        curcard = std::rand() % cards.size();

                    answers.clear();
                    std::copy(cards[curcard]["answers"].begin(), cards[curcard]["answers"].end(),
                              std::back_inserter(answers));
                    std::random_shuffle(answers.begin(), answers.end());

                    destroyWin(win);
                    refresh();

                    win = createWin(LINES - 2, COLS - 4, 1, 2);

                    mvprintw(2, COLS - 24 - (int)(state >= 10 ? 1 : 0), "%u richtig beantwortet", state);

                    mvprintw(3, (COLS - std::strlen(cards[curcard].get("question", "").asCString())) / 2, "%s", cards[curcard].get("question", "").asCString());

                    for (unsigned int i = 0; i < answers.size(); ++i)
                    {
                        mvprintw(5 + i, 4, "%i. %s", i + 1, answers[i][0].asCString());
                    }

                } while (!cards.empty() && (keych = getch()) != exitkey);

                highscore += state;

                break;

            case 'N':
            case 'n':
                keych = 0;
                state = 0;
                curs_set(1);
                title.clear();

                do
                {
                    clear();
                    switch (state)
                    {
                        case 0:
                            switch (keych)
                            {
                                case 0:
                                    // pass
                                    break;

                                case 263:
                                    if (!title.empty())
                                        title.erase(title.end() - 1);
                                    break;

                                case 10:
                                case KEY_ENTER:
                                    ++state;
                                    break;

                                default:
                                    title += keych;
                            }
                            break;

                        case 1:
                            switch (keych)
                            {
                                case 10:
                                case KEY_ENTER:
                                    ++state;
                                    break;
                            }
                            break;
                    }

                    destroyWin(win);
                    refresh();

                    win = createWin(LINES - 3, COLS - 4, 2, 2);

                    mvprintw(3, 4, "Title");
                    mvprintw(5, 4, "Kategorien");
                    mvprintw(4, 5, "%s", title.c_str());

                } while ((keych = getch()) != exitkey && state < 2);
                curs_set(0);
                break;

            case KEY_UP:
                if (--cursorpos == (unsigned short)-1)
                    ++cursorpos;

                if (cursorpos - scrollpos < 1)
                    if (--scrollpos == (unsigned short)-1)
                        ++scrollpos;
                break;

            case KEY_DOWN:
                if (++cursorpos >= paths.size())
                    --cursorpos;

                if (textpos - scrollpos - 3 < cursorpos) // ¯\_(ツ)_/¯
                    if (++scrollpos == paths.size())
                        --scrollpos;
                break;
        }
        clear();

        // cleanup all Windows
        destroyWin(win);
        destroyWin(list);

        destroyWin(Buttons[0]);
        destroyWin(Buttons[1]);

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

        textpos = 0;

        // print file names
        mvprintw(4 + textpos, 7, "Title");
        mvprintw(4 + textpos, 20, "Anzahl");
        mvprintw(4 + textpos, 30, "Kategorien");

        for (std::filesystem::directory_entry& p : paths)
        {
            if (!categories.empty()) // only clear categories if they are not empty to not waste resources
                categories.clear();

            if (file.is_open()) // incase something is still in file we close it
                file.close();

            file.open(p.path().c_str());
            card = Backend::parseFile(file);
            file.close();

            if (12 - scrollpos + textpos++ > LINES)
                break;
            else if (textpos <= scrollpos)
                continue;

            if (cursorpos + 1 == textpos)
            {
                attron(A_BOLD);
                mvprintw(4 + textpos - scrollpos, 5, "*");
                attroff(A_BOLD);
            }

            mvprintw(4 + textpos - scrollpos, 7, "%s", p.path().stem().string().c_str());

            unsigned short size = card.get("categories", Json::Value()).size();
            for (unsigned short i = 0; i < size; ++i)
            {
                if (!categories.empty())
                    categories += ", ";
                categories += card.get("categories", Json::Value())[i].asString();
            }

            mvprintw(4 + textpos - scrollpos, 20, "%u", card.get("cards", Json::Value()).size());
            mvprintw(4 + textpos - scrollpos, 30, "%s", categories.c_str());
        }

        attron(A_UNDERLINE);
        mvprintw(LINES - 4, 5, ButtonText[0]);                 // 0
        mvprintw(LINES - 4, COLS - (COLS / 5), ButtonText[1]); // 1
        attroff(A_UNDERLINE);

        mvprintw(LINES - 4, 6, &ButtonText[0][1]);                     // 0
        mvprintw(LINES - 4, COLS - (COLS / 5) + 1, &ButtonText[1][1]); // 1

        // Windows are used for the Buttons because they give it a "button" feel
        Buttons[0] = createWin(3, (COLS / 5), LINES - 5, 3);
        Buttons[1] = createWin(3, (COLS / 5), LINES - 5, COLS - (COLS / 5) - 3);
        //    Neu Importieren OK

        mvprintw(0, 0, "%i Fragen richtig beantwortet", highscore);

        refresh();
    } while ((keych = getch()) != exitkey);

    config["highscore"] = highscore;
    Config::writeConfig(config);

    endwin(); /* End curses mode		  */
    return 0;
}