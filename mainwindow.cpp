#include "mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMinimumSize(500,500);
    setWindowTitle(tr("Amőba"));

    _newGameAction = new QAction(tr("Ú&j játék"), this);
    _newGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    _newGameAction->setStatusTip(tr("Új játék indítása"));

    _configureAction = new QAction(tr("&Beállítások"), this);
    _configureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    _configureAction->setStatusTip(tr("Játék beállításainak módosítása"));

    _saveAction = new QAction(tr("&Mentés"), this);
    _saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    _saveAction->setStatusTip(tr("Játék mentése"));

    _loadAction = new QAction(tr("&Betöltés"), this);
    _loadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    _loadAction->setStatusTip(tr("Játék betöltése"));

    _exitAction = new QAction(tr("&Kilépés"), this);
    _exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    _exitAction->setStatusTip(tr("Kilépés a játékból"));


    _gameMenu2 = new MyMenu(tr("&Játék"));
    menuBar()->addMenu(_gameMenu2);
    _gameMenu2->addAction(_newGameAction);
    _gameMenu2->addAction(_configureAction);
    _gameMenu2->addAction(_saveAction);
    _gameMenu2->addAction(_loadAction);
    _gameMenu2->addSeparator();
    _gameMenu2->addAction(_exitAction);

    /*_gameMenu = menuBar()->addMenu(tr("&Játék"));
    _gameMenu->addAction(_newGameAction);
    _gameMenu->addAction(_configureAction);
    _gameMenu->addAction(_saveAction);
    _gameMenu->addAction(_loadAction);
    _gameMenu->addSeparator();
    _gameMenu->addAction(_exitAction);*/

    _gameWidget = new TicTacToeWidget(this);
    setCentralWidget(_gameWidget);

    statusBar()->showMessage(tr("X játékos következik."));
    _player = statusBar()->currentMessage();

    connect(_newGameAction, SIGNAL(triggered()), _gameWidget, SLOT(newGame()));
    connect(_configureAction, SIGNAL(triggered()), _gameWidget, SLOT(configureGameDialog()));
    connect(_saveAction, SIGNAL(triggered()), _gameWidget, SLOT(saveGameDialog()));
    connect(_loadAction, SIGNAL(triggered()), _gameWidget, SLOT(loadGameDialog()));
    connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));

    connect(_gameMenu2, SIGNAL(myMenuMouseHover()), this, SLOT(menuHover()));
    connect(_gameMenu2, SIGNAL(myMenuMouseLeave()), this, SLOT(menuExit()));

    connect(_gameWidget, SIGNAL(playerChanged(QString)), this->statusBar(), SLOT(showMessage(QString)));
    connect(_gameWidget, SIGNAL(playerChanged(QString)), this, SLOT(savePlayer()));
    // játékosváltás a játékban
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton returnButton;

    // bezáráskor megkérdezzük, biztos kilép-e a játékos
    returnButton = QMessageBox::warning(this, tr("Amőba - Kilépés"), tr("Biztos ki akarsz lépni a játékból?"), QMessageBox::Yes | QMessageBox::No);
    if (returnButton == QMessageBox::No)
        event->ignore();
    else
        event->accept();
}

void MainWindow::menuHover(){

    statusBar()->showMessage(tr("Menü"));
}

void MainWindow::menuExit(){
    statusBar()->showMessage(_player);
}

void MainWindow::savePlayer(){
    _player = statusBar()->currentMessage();
}
