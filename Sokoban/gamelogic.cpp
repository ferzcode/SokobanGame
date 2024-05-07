#include "gamelogic.h"
#include <fstream>

GameLogic::GameLogic(int numRows, int numCols, int level)
    : numRows(numRows), numCols(numCols), level(level) {
    initializeGrid();
}

void GameLogic::initializeGrid() {

    std::string path;
    switch (level) {
    case 1:
        path = "lvl1.txt";
        break;
    case 2:
        path = "lvl2.txt";
        break;
    case 3:
        path = "lvl3.txt";
        break;
    default:
        break;
    }

    std::ifstream fin(path);
    int sym;

    matrixColor = QVector<QVector<cell>>(numRows, QVector<cell>(numCols, GameLogic::cell::Grass));

    for(size_t i = 0; i < numRows; i++){
        for(size_t j = 0; j < numCols; j++){
            fin >> sym;
            if (sym == 2){
                charPosX = j;
                charPosY = i;
            }
            if (sym == 4){
                TargetCounter++;
            }
            matrixColor[i][j] = static_cast<GameLogic::cell>(sym);
        }
    }
    fin.close();
}

QVector<QVector<GameLogic::cell>> GameLogic::getGrid(){
    return matrixColor;
}

int GameLogic::getRows(){
    return numRows;
}

int GameLogic::getCols(){
    return numCols;
}

int GameLogic::getStartX(){
    return charPosX;
}

int GameLogic::getStartY(){
    return charPosY;
}

void GameLogic::movePlayer(int changeX, int changeY) {

    if (charPosX + changeY >= 0 && charPosX + changeY < numRows && charPosY + changeX >= 0 && charPosY + changeX < numCols) {
        int nextPosX = charPosX + changeY;
        int nextPosY = charPosY + changeX;
        int nextBoxPosX = nextPosX + changeY;
        int nextBoxPosY = nextPosY + changeX;

        if (matrixColor[nextPosX][nextPosY] == GameLogic::cell::Wall) {
            return; // Нельзя двигаться через стены
        }

        if (matrixColor[nextPosX][nextPosY] == GameLogic::cell::Box) {
            if (matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::Box ||
                matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::BoxInTarget) {
                return; // Нельзя двигать ящик через другие ящики
            }

            if (matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::Wall) {
                return;
            }

            if (matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::Targets) {
                matrixColor[nextBoxPosX][nextBoxPosY] = GameLogic::cell::BoxInTarget;
                matrixColor[nextPosX][nextPosY] = GameLogic::cell::Grass;
                TargetCounter--;
            } else if (matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::Grass) {
                std::swap(matrixColor[nextPosX][nextPosY], matrixColor[nextBoxPosX][nextBoxPosY]);
                std::swap(matrixColor[charPosX][charPosY], matrixColor[nextPosX][nextPosY]);
            }

            if (matrixColor[charPosX][charPosY] == GameLogic::cell::PlayerInTarget) {
                matrixColor[nextPosX][nextPosY] = GameLogic::cell::Player;
                matrixColor[charPosX][charPosY] = GameLogic::cell::Targets;
            } else {
                std::swap(matrixColor[charPosX][charPosY], matrixColor[nextPosX][nextPosY]);
            }
        }

        if (matrixColor[nextPosX][nextPosY] == GameLogic::cell::BoxInTarget) {
            if (matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::Box ||
                matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::BoxInTarget) {
                return; // Нельзя двигать ящик через другие ящики
            }

            if (matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::Targets) {
                matrixColor[nextBoxPosX][nextBoxPosY] = GameLogic::cell::BoxInTarget;
                matrixColor[nextPosX][nextPosY] = GameLogic::cell::PlayerInTarget;
            } else if (matrixColor[nextBoxPosX][nextBoxPosY] == GameLogic::cell::Grass) {
                matrixColor[nextBoxPosX][nextBoxPosY] = GameLogic::cell::Box;
                matrixColor[nextPosX][nextPosY] = GameLogic::cell::PlayerInTarget;
                TargetCounter++;
            }

            if (matrixColor[charPosX][charPosY] == GameLogic::cell::PlayerInTarget) {
                matrixColor[charPosX][charPosY] = GameLogic::cell::Targets;
            } else {
                matrixColor[charPosX][charPosY] = GameLogic::cell::Grass;
            }
        }

        if (matrixColor[nextPosX][nextPosY] == GameLogic::cell::Grass) {
            if (matrixColor[charPosX][charPosY] == GameLogic::cell::PlayerInTarget) {
                matrixColor[nextPosX][nextPosY] = GameLogic::cell::Player;
                matrixColor[charPosX][charPosY] = GameLogic::cell::Targets;
            } else {
                std::swap(matrixColor[charPosX][charPosY], matrixColor[nextPosX][nextPosY]);
            }
        }

        if (matrixColor[nextPosX][nextPosY] == GameLogic::cell::Targets) {
            matrixColor[nextPosX][nextPosY] = GameLogic::cell::PlayerInTarget;
            if (matrixColor[charPosX][charPosY] == GameLogic::cell::PlayerInTarget) {
                matrixColor[charPosX][charPosY] = GameLogic::cell::Targets;
            } else {
                matrixColor[charPosX][charPosY] = GameLogic::cell::Grass;
            }
        }

        charPosX = nextPosX;
        charPosY = nextPosY;
    }

    if (checkVictory()) {
        emit reportVictory();
        return;
    }

}

bool GameLogic::checkVictory(){
    return TargetCounter == 0 ? Victory = true : Victory = false;
}

const QVector<QVector<GameLogic::cell>>& GameLogic::getMatrixColor() const {
    return matrixColor;
}

void GameLogic::updateGrid() {
    emit gridUpdated();
}
