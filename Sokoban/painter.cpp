#include "painter.h"

Painter::Painter() {
    logic = new GameLogic(10, 10, 1);
    connect(logic, &GameLogic::reportVictory, this, &Painter::handleVictory);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

QVector<QVector<QColor>> Painter::getter(QVector<QVector<QColor>> matrix) {
    return matrix;
}

void Painter::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    drawGrid(painter);
}

void Painter::resizeEvent(QResizeEvent* event) {
    update();
}

void Painter::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_W:
        logic->movePlayer(0, -1);
        break;

    case Qt::Key_D:
        logic->movePlayer(1, 0);
        break;

    case Qt::Key_S:
        logic->movePlayer(0, 1);
        break;

    case Qt::Key_A:
        logic->movePlayer(-1, 0);
        break;

    default: break;
    }
    update();
    QWidget::keyPressEvent(event);
}

void Painter::drawGrid(QPainter &painter) {
    int rows = logic->getRows();
    int cols = logic->getCols();

    int cellSize = qMin(width() / cols, height() / rows);

    int fullWidth = cellSize * cols;
    int fullHeight = cellSize * rows;

    QVector<QVector<GameLogic::cell>> Field = logic->getGrid();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (Field[i][j]){
            case GameLogic::cell::Grass:
                painter.setBrush(Qt::white);
                break;
            case GameLogic::cell::Player:
                painter.setBrush(Qt::yellow);
                break;
            case GameLogic::cell::Wall:
                painter.setBrush(Qt::black);
                break;
            case GameLogic::cell::Box:
                painter.setBrush(Qt::gray);
                break;
            case GameLogic::cell::Targets:
                painter.setBrush(Qt::darkRed);
                break;
            case GameLogic::cell::BoxInTarget:
                painter.setBrush(Qt::red);
                break;
            case GameLogic::cell::PlayerInTarget:
                painter.setBrush(Qt::darkYellow);
            default : break;
            }
            QRect cellRect((width() - fullWidth)/2 + j * cellSize, (height() - fullHeight) / 2 + i * cellSize, cellSize, cellSize);
            painter.drawRect(cellRect);
        }
    }
}

void Painter::handleVictory() {
    // Double Free memory
    // if (VictoryText != nullptr) {
    //     delete VictoryText;
    //     VictoryText = nullptr;
    // }

    VictoryText = new QLabel("Победа!", this);

    QFont font;
    font.setPointSize(24);
    font.setBold(true);
    VictoryText->setFont(font);
    VictoryText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    int rows = logic->getRows();
    int cols = logic->getCols();

    int cellWidth = qMin(width() / cols, height() / rows);

    int totalWidth = cellWidth * cols;
    int totalHeight = cellWidth * rows;

    int PosX = (width() - totalWidth) / 2;
    int PosY = (height() - totalHeight) / 2;

    VictoryText->setGeometry(PosX, PosY, totalWidth, totalHeight);

    VictoryText->show();
    update();
}
