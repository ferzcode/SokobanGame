#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QColor>
#include <QVector>
#include <QString>
#include <QFile>

class GameLogic : public QObject {
    Q_OBJECT

public:

    enum class cell{
        Grass = 0,
        Wall = 1,
        Player = 2,
        Box = 3,
        Targets = 4,
        BoxInTarget = 5,
        PlayerInTarget = 6
    };


    GameLogic(int numRows, int numCols, int level);

    void initializeGrid();
    void startGame();
    void makeGrid();
    bool checkVictory();

    QVector<QVector<cell>> getGrid();
    int getRows();
    int getCols();
    int getStartX();
    int getStartY();

    void movePlayer(int changeY, int changeX);

    const QVector<QVector<cell>>& getMatrixColor() const;

signals:
    void reportVictory();
    void gridUpdated();

private:
    int level;

    int numRows;
    int numCols;

    int charPosX;
    int charPosY;
    int TargetCounter = 0;
    bool Victory = false;

    QVector<QVector<cell>> matrixColor;

    void updateGrid();
};

#endif // GAMELOGIC_H
