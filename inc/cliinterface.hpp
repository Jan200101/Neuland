#ifndef CLIINTERFACE_HPP
#define CLIINTERFACE_HPP

class CliWindow
{
   private:
    int argc;
    char** argv;

   public:
    CliWindow(int argc, char** argv);
};

#endif