#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include "GameBoard.hpp"
#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *combo_box = new QComboBox(this);
    combo_box->addItem("4x4");
    combo_box->addItem("5x5");
    combo_box->addItem("6x6");
    combo_box->addItem("8x8");

    auto *start_button = new QPushButton("Start", this);

    connect(start_button, &QPushButton::clicked, this, &MainWindow::startGame);

    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(new QVBoxLayout(this));
    centralWidget()->layout()->addWidget(combo_box);
    centralWidget()->layout()->addWidget(start_button);
}

void MainWindow::startGame() {
    auto selected_option = dynamic_cast<QComboBox *>(centralWidget()->layout()->itemAt(0)->widget())->currentText();

    int numTiles = selected_option.leftRef(1).toInt();

    auto *gameBoard = new GameBoard(this, numTiles);
    setCentralWidget(gameBoard);

    update();

    QApplication::processEvents();

    show();

    raise();
};



