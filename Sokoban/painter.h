#ifndef PAINTER_H
#define PAINTER_H

#include <QApplication>
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QLabel>
#include "gamelogic.h"

class Painter : public QWidget {
public:
    Painter();

    QVector<QVector<QColor>> getter(QVector<QVector<QColor>> matrix);

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    GameLogic *logic = nullptr;
    QLabel *VictoryText = nullptr;

    void drawGrid(QPainter &painter);

private slots:
    void handleVictory();
};

#endif // PAINTER_H
