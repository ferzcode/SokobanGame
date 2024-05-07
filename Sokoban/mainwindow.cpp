#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    painter(nullptr){

}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::onPlayButtonClicked()
// {
//     // Создаем виджет Painter и устанавливаем его в центральный виджет
//     painter = new Painter();
//     setCentralWidget(painter);
// }
