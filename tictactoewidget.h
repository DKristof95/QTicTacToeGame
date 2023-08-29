#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>
#include "tictactoemodel.h"
#include "loadgamewidget.h"
#include "savegamewidget.h"
#include "configuregamewidget.h"

class TicTacToeWidget : public QWidget // a nézet típusa
{
    Q_OBJECT

public:
    TicTacToeWidget(QWidget *parent = nullptr);
    ~TicTacToeWidget();

signals:
    void playerChanged(QString player);

public slots:
    void newGame(); // új játék indítása
    void configureGameDialog(); // játék konfigurálása*/
    void loadGameDialog();
    void saveGameDialog();

protected:
    void paintEvent(QPaintEvent *);    
    //void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void model_gameWon(TicTacToeModel::Player player); // eseménykezelők a modell eseményeire
    void model_gameOver();
    void model_fieldChanged(int, int, TicTacToeModel::Player);
    void loadGame();
    void saveGame();
    void configureGame();
    void init(int boardSize);
    void redraw();

private:
    QVector<QLineF> _tableGraphics; // tábla grafikája, egy vektorban tárljuk a kirajzoló vonalakat
    QVector<QLineF> _playerXGraphics; // kereszt grafikája
    QRectF _playerOGraphics; // kör grafikája

    TicTacToeModel* _model; // a játékot megvalósító modell
    TicTacToeDataAccess* _dataAccess; // adatelérés

    SaveGameWidget* _saveGameWidget; // a mentést biztosító ablak
    LoadGameWidget* _loadGameWidget; // a betöltést biztostó ablak
    ConfigureGameWidget* _configureGameWidget;

    int _boardSize;
};

#endif // TICTACTOEWIDGET_H
