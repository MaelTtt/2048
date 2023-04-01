#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include "GameBoard.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void startGame();

private:
    QComboBox* comboBox;
    QPushButton* startButton;
};

#endif // MAINWINDOW_H
