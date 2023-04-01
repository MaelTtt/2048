#include <QApplication>
#include <QtWidgets>

#include "GameBoard.hpp"


int maxTileValue = 0;
bool gameStarted = false;

GameBoard::GameBoard(QWidget* parent, int numTiles)
        : QWidget(parent),
          board(QVector<QVector<int>>(numTiles, QVector<int>(numTiles))),
          colorMap({
                           { 0,    QColor(0xeee4da) },
                           { 2,    QColor(0xeee4da) },
                           { 4,    QColor(0xede0c8) },
                           { 8,    QColor(0xf2b179) },
                           { 16,   QColor(0xf59563) },
                           { 32,   QColor(0xf67c5f) },
                           { 64,   QColor(0xf65e3b) },
                           { 128,  QColor(0xedcf72) },
                           { 256,  QColor(0xedcc61) },
                           { 512,  QColor(0xedc850) },
                           { 1024, QColor(0xedc53f) },
                           { 2048, QColor(0xedc22e) }
                   }),
          tileSize(100),
          score(0)
{
    setFixedSize(numTiles * tileSize,  numTiles * tileSize);
    setFocusPolicy(Qt::StrongFocus);

    QPushButton* startButton = new QPushButton("Start", this);
    connect(startButton, &QPushButton::clicked, this, &GameBoard::startGame);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(startButton, 0, Qt::AlignCenter);
}


void GameBoard::startGame()
{
    gameStarted = true;
    // Reset la partie
    score = 0;
    maxTileValue = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            board[i][j] = 0;
        }
    }
    addRandomTile();
    addRandomTile();

    QString title = "2048 - Score: " + QString::number(score);
    setWindowTitle(title);

    delete layout()->itemAt(0)->widget();
    setFocus();

    update();
}

void GameBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(QFont("Arial", 20));
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            QRect rect(j * tileSize, i * tileSize, tileSize, tileSize);
            painter.setPen(Qt::white);
            int value = board[i][j];
            QColor color = colorMap.value(value, Qt::black);
            painter.setBrush(color);
            painter.drawRoundedRect(rect, 10, 10);
            if (board[i][j] != 0) {
                painter.setBrush(Qt::white);
                painter.drawText(rect, Qt::AlignCenter, QString::number(board[i][j]));
            }
        }
    }

    QString titleScore = QString("Score: %1").arg(score);
    parentWidget()->setWindowTitle(titleScore);
    // painter.setPen(Qt::red);
    // painter.drawText(0, height() - 50, QString("Score: %1").arg(score));
}


void GameBoard::keyPressEvent(QKeyEvent *event) {
    if (!gameStarted) { // Empêche de jouer si le bouton start n'a pas été cliqué
        return;
    }
    if (event->key() == Qt::Key_Left) { // Gauche
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                // Si la case n'est pas vide
                if (board[i][j] != 0) {
                    int k = j;
                    // Tant que la case suivante est vide
                    while (k > 0 && board[i][k - 1] == 0) {
                        board[i][k - 1] = board[i][k]; // On déplace la case
                        board[i][k] = 0; // On vide la case
                        --k;
                    }
                    // Si la case suivante est égale à la case actuelle
                    if (k > 0 && board[i][k - 1] == board[i][k]) {
                        board[i][k - 1] *= 2; // On double la valeur de la case
                        board[i][k] = 0; // On vide la case
                        score += board[i][k - 1]; // On ajoute la valeur de la case au score
                        if (board[i][k - 1] > maxTileValue) { // On vérifie si la valeur de la case est la plus grande
                            maxTileValue = board[i][k - 1]; // Si oui, on met à jour la valeur max
                        }
                    }
                }
            }
        }
    } else if (event->key() == Qt::Key_Right) { // Droite
        for (int i = 0; i < board.size(); i++) {
            for (int j = board[i].size() - 2; j >= 0; j--) {
                if (board[i][j] != 0) {
                    int k = j;
                    while (k < board[i].size() - 1 && board[i][k + 1] == 0) {
                        board[i][k + 1] = board[i][k];
                        board[i][k] = 0;
                        k++;
                    }
                    if (k < board[i].size() - 1 && board[i][k + 1] == board[i][k]) {
                        board[i][k + 1] *= 2;
                        score += board[i][k + 1];
                        board[i][k] = 0;
                        if (board[i][k + 1] > maxTileValue) {
                            maxTileValue = board[i][k + 1];
                        }
                    }
                }
            }
        }
    } else if (event->key() == Qt::Key_Up) { // Haut
        for (int j = 0; j < board[0].size(); j++) {
            for (int i = 1; i < board.size(); i++) {
                if (board[i][j] != 0) {
                    int k = i;
                    while (k > 0 && board[k - 1][j] == 0) {
                        board[k - 1][j] = board[k][j];
                        board[k][j] = 0;
                        k--;
                    }
                    if (k > 0 && board[k - 1][j] == board[k][j]) {
                        board[k - 1][j] *= 2;
                        score += board[k - 1][j];
                        board[k][j] = 0;
                        if (board[k - 1][j] > maxTileValue) {
                            maxTileValue = board[k - 1][j];
                        }
                    }
                }
            }
        }
    } else if (event->key() == Qt::Key_Down) { // Bas
        for (int j = 0; j < board[0].size(); j++) {
            for (int i = board.size() - 2; i >= 0; i--) {
                if (board[i][j] != 0) {
                    int k = i;
                    while (k < board.size() - 1 && board[k + 1][j] == 0) {
                        board[k + 1][j] = board[k][j];
                        board[k][j] = 0;
                        k++;
                    }
                    if (k < board.size() - 1 && board[k + 1][j] == board[k][j]) {
                        board[k + 1][j] *= 2;
                        score += board[k + 1][j];
                        board[k][j] = 0;
                        if (board[k + 1][j] > maxTileValue) {
                            maxTileValue = board[k + 1][j];
                        }
                    }
                }
            }
        }
    } else {
        QWidget::keyPressEvent(event);
        return;
    }
    // On vérifie si le joueur a gagné
    if (maxTileValue == 2048) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, "Game Over", "Gagné!\nVoulez-vous rejouez ?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            reset();
        } else {
            QApplication::quit();
        }
    }


    addRandomTile();
    checkFinished();
    update();
}


void GameBoard::addRandomTile() {
    QVector<QPair<int, int>> emptyTiles;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 0) {
                emptyTiles.append(qMakePair(i, j));
            }
        }
    }
    // On ajoute une Tile aléatoire si il y a des cases vides
    if (!emptyTiles.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(emptyTiles.size());
        int i = emptyTiles[index].first;
        int j = emptyTiles[index].second;

        board[i][j] = (QRandomGenerator::global()->bounded(10) < 9) ? 2 : 4;
    }
}

void GameBoard::checkFinished() {
    bool finished = true;
    for (int i = 0; i < board.size(); ++i) { // On vérifie si il reste des cases vides
        for (int j = 0; j < board[i].size(); ++j) {
            // Si il y a une case vide, on continue
            if (board[i][j] == 0) {
                finished = false;
                break;
            }
            // Si il y a une case avec la même valeur à gauche ou à droite, on continue
            if (i > 0 && board[i][j] == board[i - 1][j]) {
                finished = false;
                break;
            }
            // Si il y a une case avec la même valeur à gauche ou à droite, on continue
            if (i < board.size() - 1 && board[i][j] == board[i + 1][j]) {
                finished = false;
                break;
            }
            // Si il y a une case avec la même valeur en haut ou en bas, on continue
            if (j > 0 && board[i][j] == board[i][j - 1]) {
                finished = false;
                break;
            }
            // Si il y a une case avec la même valeur en haut ou en bas, on continue
            if (j < board[i].size() - 1 && board[i][j] == board[i][j + 1]) {
                finished = false;
                break;
            }
        }
    }
    if (finished) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, "Game Over", "Perdu!\nVoulez-vous rejouez ?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            reset();
        } else {
            QApplication::quit();
        }
    }
}

void GameBoard::reset() {
    score = 0;
    maxTileValue = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            board[i][j] = 0;
        }
    }
    addRandomTile();
    addRandomTile();
    update();
}

