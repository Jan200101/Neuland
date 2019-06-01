#ifndef NO_QT
#include <json/json.h>
#include <fstream>
#include <string>

#include "frontend/qtinterface.hpp"
#include "ui_mainwindow.h"

#include "backend/config.hpp"
#include "backend/dirs.hpp"
#include "backend/files.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    config = Config::readConfig();

    std::ifstream file;
    Json::Value card;
    std::string categories;

    for (auto& p : Backend::listCarddir())
    {
        categories.clear();

        file.open(p.path().c_str());
        card = Backend::parseFile(file);

        int size = card.get("categories", Json::Value()).size();

        for (int i = 0; i < size; ++i)
        {
            if (!categories.empty())
                categories += " ,";
            categories += card.get("categories", Json::Value())[i].asString();
        }

        addRow(p.path().stem().string(),
               std::to_string(card.get("cards", Json::Value()).size()),
               categories);
        file.close();
    }
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