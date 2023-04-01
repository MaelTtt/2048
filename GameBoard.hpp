#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <QtWidgets>

class GameBoard : public QWidget {

public:
    GameBoard(QWidget *parent, int i);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void addRandomTile();

private:
    QVector<QVector<int>> board;
    QMap<int, QColor> colorMap;
    int tileSize;
    int score;

    void checkFinished();

    void reset();

    void startGame();
};

#endif // GAMEBOARD_H