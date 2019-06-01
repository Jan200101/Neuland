#ifndef NO_QT
#include "frontend/qtinterface.hpp"
#include "ui_mainwindow.h"

#include "backend/dirs.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (auto& p : Backend::listCarddir())
        addRow(p.path().stem().string(), "", "");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRow(const char* title, const char* amount, const char* categories)
{
    unsigned short count = ui->tableWidget->rowCount();

    ui->tableWidget->setRowCount(count + 1);

    this->setItem(count, 0, title);
    this->setItem(count, 1, amount);
    this->setItem(count, 2, categories);
}

void MainWindow::addRow(std::string title, std::string amount, std::string categories)
{
    this->addRow(title.c_str(), amount.c_str(), categories.c_str());
}

void MainWindow::setItem(unsigned short count, unsigned short column, const char* text)
{
    QTableWidgetItem* __qtablewidgetitem = new QTableWidgetItem();

    ui->tableWidget->setItem(count, column, __qtablewidgetitem);
    __qtablewidgetitem->setText(text);
}
#endif