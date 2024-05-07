// #include "mainwindow.h"
// #include <QApplication>
#include "painter.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painter painter;
    painter.show();
    return a.exec();
}
