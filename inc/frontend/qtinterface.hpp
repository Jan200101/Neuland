#ifndef QTINTERFACE_HPP
#define QTINTERFACE_HPP

#include <json/json.h>
#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class QtInterface : public QMainWindow
{
    Q_OBJECT

   public:
    explicit QtInterface(QWidget* parent = nullptr);
    ~QtInterface();

   private:
    Ui::MainWindow* ui;
    Json::Value config;

    void addRow(const char* forename, const char* surname, const char* nickname);
    void addRow(std::string forename, std::string surname, std::string nickname);
    void setItem(unsigned short column, unsigned short row, const char* text);
};

#endif // INTERFACE_H
