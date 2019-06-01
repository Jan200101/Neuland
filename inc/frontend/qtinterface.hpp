#ifndef QTINTERFACE_HPP
#define QTINTERFACE_HPP

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private:
    Ui::MainWindow* ui;

    void addRow(const char* forename, const char* surname, const char* nickname);
    void addRow(std::string forename, std::string surname, std::string nickname);
    void setItem(unsigned short count, unsigned short column, const char* text);
};

#endif // INTERFACE_H
