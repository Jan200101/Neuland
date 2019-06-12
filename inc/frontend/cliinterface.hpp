#ifndef CLIINTERFACE_HPP
#define CLIINTERFACE_HPP

#include <json/json.h>

/* 
 * You can't include NCurses here with QT present
 */

/**
 * @brief      class for the ncurses interface
 */
class CliWindow
{
   private:
    int argc;
    char** argv;
    bool hasColors;
    unsigned int exitkey;
    Json::Value* config;

   public:
    CliWindow(int argc, char** argv);
    ~CliWindow();

    int exec();
};

#endif