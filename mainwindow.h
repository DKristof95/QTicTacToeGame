#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tictactoewidget.h"
#include "mymenu.h"

// főablak
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    QAction* _newGameAction; // új játék akció
    QAction* _exitAction; // kilépés akció
    QAction* _configureAction; // beállítások akciója

    QAction* _saveAction; // mentés akciója
    QAction* _loadAction; // betöltés akciója

    //QMenu* _gameMenu; // játékmenü

    MyMenu* _gameMenu2;

    TicTacToeWidget* _gameWidget; // játékmezõ vezérlője

    QString _player;

private slots:
    void menuHover();
    void menuExit();
    void savePlayer();
};


#endif // MAINWINDOW_H
