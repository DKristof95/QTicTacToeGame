#include "tictactoewidget.h"
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include "tictactoefiledataaccess.h"
#include "tictactoedbdataaccess.h"

#include <iostream>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{


    _loadGameWidget = nullptr;
    _saveGameWidget = nullptr;
    _configureGameWidget = nullptr;

    init(6);

}

TicTacToeWidget::~TicTacToeWidget()
{
    delete _model;
    delete _dataAccess;

    if (_loadGameWidget != nullptr) delete _loadGameWidget;
    if (_saveGameWidget != nullptr) delete _saveGameWidget;
    if (_configureGameWidget != nullptr) delete _configureGameWidget;
}

void TicTacToeWidget::init(int boardSize){

    _boardSize = boardSize;

    setMinimumSize(400, 400);
    setBaseSize(400,400);
    setWindowTitle(tr("Amőba"));


    // az adatkezelést itt döntjük el
    _dataAccess = new TicTacToeDbDataAccess(); // alapértelmezetten adatbázist használunk
    if (!_dataAccess->isAvailable()) // de ha az nem elérhető
    {
        _dataAccess = new TicTacToeFileDataAccess(); // átváltunk fájlra
    }

    _model = new TicTacToeModel(_boardSize, _dataAccess); // a modellt az adott adateléréssel hozzuk létre



    // mezők grafikája:
    /*_tableGraphics.append(QLineF(0, 66, 200, 66));
    _tableGraphics.append(QLineF(0, 132, 200, 132));
    _tableGraphics.append(QLineF(66, 0, 66, 200));
    _tableGraphics.append(QLineF(132, 0, 132, 200));*/

    for (int i = 1; i < _boardSize; i++){
        _tableGraphics.append(QLineF(0, floor(200.0/_boardSize*i), 200, floor(200.0/_boardSize*i)));
        _tableGraphics.append(QLineF(floor(200.0/_boardSize*i), 0, floor(200.0/_boardSize*i), 200));
    }


    // játékosok grafikája:
    _playerXGraphics.append(QLineF(floor(10.0*(3.0/_boardSize)), floor(10.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize))));
    _playerXGraphics.append(QLineF(floor(10.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize)), floor(10.0*(3.0/_boardSize))));
    //_playerXGraphics.append(QLineF(10, 10, 56, 56));
    //_playerXGraphics.append(QLineF(10, 56, 56, 10));
    _playerOGraphics = QRectF(floor(10.0*(3.0/_boardSize)), floor(10.0*(3.0/_boardSize)), floor(46.0*(3.0/_boardSize)), floor(46.0*(3.0/_boardSize)));
    //_playerOGraphics = QRectF(10.0, 10.0, 46.0, 46.0);

    // modell eseményeinek feldolgozása
    connect(_model, SIGNAL(gameWon(TicTacToeModel::Player)), this, SLOT(model_gameWon(TicTacToeModel::Player)));
    connect(_model, SIGNAL(gameOver()), this, SLOT(model_gameOver()));
    connect(_model, SIGNAL(fieldChanged(int, int, TicTacToeModel::Player)), this, SLOT(model_fieldChanged(int, int, TicTacToeModel::Player)));

    connect(_model, SIGNAL(playerChanged(QString)), this, SIGNAL(playerChanged(QString)));

    _model->newGame(); // új játék indítása
}

void TicTacToeWidget::redraw(){

    _tableGraphics.clear();
    _tableGraphics.squeeze();
    _playerXGraphics.clear();
    _playerXGraphics.squeeze();


    // mezők grafikája:
    for (int i = 1; i < _boardSize; i++){
        _tableGraphics.append(QLineF(0, floor(200.0/_boardSize*i), 200, floor(200.0/_boardSize*i)));
        _tableGraphics.append(QLineF(floor(200.0/_boardSize*i), 0, floor(200.0/_boardSize*i), 200));
    }


    // játékosok grafikája:
    _playerXGraphics.append(QLineF(floor(10.0*(3.0/_boardSize)), floor(10.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize))));
    _playerXGraphics.append(QLineF(floor(10.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize)), floor(56.0*(3.0/_boardSize)), floor(10.0*(3.0/_boardSize))));

    _playerOGraphics = QRectF(floor(10.0*(3.0/_boardSize)), floor(10.0*(3.0/_boardSize)), floor(46.0*(3.0/_boardSize)), floor(46.0*(3.0/_boardSize)));

    update();
}

void TicTacToeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // rajzoló objektum
    painter.setRenderHint(QPainter::Antialiasing); // élsimítás használata
    painter.scale(width() / 200.0, height() / 200.0); // skálázás

    //painter.setPen(QPen(Qt::black, 2)); // toll beállítása
    painter.setPen(QPen(Qt::black, floor(2*(3.0/_boardSize))));
    painter.setBrush(Qt::red); // ecset beállítása
    painter.drawLines(_tableGraphics); // tábla kirajzolása

    //for(int i = 0; i < 3; i++)
    for(int i = 0; i < _boardSize; i++)
    {
        //for(int j = 0; j < 3; j++)
        for(int j = 0; j < _boardSize; j++)
        {
            painter.save(); // elmentjük a rajztulajdonságokat
            //painter.translate(i * 200.0 / 3 , j * 200.0 / 3); // elmozdítjuk a rajzpontot a megfelelő mezőre
            painter.translate(i * (200.0 / _boardSize) , j * (200.0 / _boardSize));

            // mező kirajzolása a játékos függvényében
            switch (_model->getField(i, j))
            {
            case TicTacToeModel::PlayerX:
                //painter.setPen(QPen(Qt::blue, 4)); // toll beállítása
                painter.setPen(QPen(Qt::blue, floor(4*(3.0/_boardSize)) == 0 ? 1 : floor(4*(3.0/_boardSize))));
                painter.drawLines(_playerXGraphics); // megfelelõ grafika kirajzolása
                break;
            case TicTacToeModel::PlayerO:
                //painter.setPen(QPen(Qt::black, 2)); // toll beállítása
                painter.setPen(QPen(Qt::black, floor(2*(3.0/_boardSize)) == 0 ? 1 : floor(2*(3.0/_boardSize))));
                painter.drawEllipse(_playerOGraphics);
                break;
            default:;
            }
            painter.restore(); // visszatöltjük a korábbi állapotot
        }
    }
}

/*void TicTacToeWidget::keyPressEvent(QKeyEvent *event)
{       
    if (event->key() == Qt::Key_N && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        // lekezeljük a Ctrl+N kombinációt
        _model->newGame();
        update();
    }

    // játék betöltése
    if (event->key() == Qt::Key_L && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_loadGameWidget == nullptr) // ha még egyszer sem nyitották meg az ablakot
        {
            _loadGameWidget = new LoadGameWidget();
            connect(_loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _loadGameWidget->setGameList(_model->saveGameList());
        _loadGameWidget->open();
    }

    // játék mentése
    if (event->key() == Qt::Key_S && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_saveGameWidget == nullptr) // ha még egyszer sem nyitották meg az ablakot
        {
            _saveGameWidget = new SaveGameWidget();
            connect(_saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _saveGameWidget->setGameList(_model->saveGameList());
        _saveGameWidget->open();
    }
}*/

void TicTacToeWidget::newGame() {
    _model->newGame();
    update();
}

void TicTacToeWidget::configureGameDialog() {
    if (_configureGameWidget == nullptr)
    {
        _configureGameWidget = new ConfigureGameWidget();
        connect(_configureGameWidget, SIGNAL(accepted()), this, SLOT(configureGame()));
    }

    _configureGameWidget->open();
}

void TicTacToeWidget::saveGameDialog() {
    if (_saveGameWidget == nullptr) // ha még egyszer sem nyitották meg az ablakot
    {
        _saveGameWidget = new SaveGameWidget();
        connect(_saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
    }

    // beállítjuk a listát, és megnyitjuk az ablakot
    _saveGameWidget->setGameList(_model->saveGameList());
    _saveGameWidget->open();
}

void TicTacToeWidget::loadGameDialog() {
    if (_loadGameWidget == nullptr) // ha még egyszer sem nyitották meg az ablakot
    {
        _loadGameWidget = new LoadGameWidget();
        connect(_loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
    }

    // beállítjuk a listát, és megnyitjuk az ablakot
    _loadGameWidget->setGameList(_model->saveGameList());
    _loadGameWidget->open();
}

void TicTacToeWidget::mousePressEvent(QMouseEvent *event)
{
    // az event->pos() megadja az egérpozíciót, ami QPoint típusú, ebbõl kiszámolható, melyik mezőn vagyunk:
    //int x = event->pos().x() * 3 / width();
    int x = floor((event->pos().x() + (event->pos().x() * 1.0 / width()  * 2 )) * ((_boardSize * 1.0) / width()));
    //int y = event->pos().y() * 3 / height();
    int y = floor((event->pos().y() + (event->pos().y() * 1.0 / height()  * 2 )) * ((_boardSize * 1.0) / height()));

    /*std::cout << "event->pos().x(): " << event->pos().x() << ", event->pos().y(): " << event->pos().y() << std::endl;
    std::cout << "width(): " << width() << ", height(): " << height() << std::endl;
    std::cout << "(_boardSize * 1.0) / width(): " << (_boardSize * 1.0) / width()<< ", (_boardSize * 1.0) / height(): " << (_boardSize * 1.0) / height() << std::endl;
    std::cout << "x0: " << event->pos().x() * ((_boardSize * 1.0) / width()) << ", y0: " << event->pos().y() * ((_boardSize * 1.0) / height()) << std::endl;
    std::cout << "x: " << x << ", y: " << y << std::endl;*/

    _model->stepGame(x, y); // játék léptetése
}

void TicTacToeWidget::model_gameWon(TicTacToeModel::Player player)
{
    // az eredmény függvényében jelenítjük meg a győztest
    switch (player)
    {
    case TicTacToeModel::PlayerX:
        QMessageBox::information(this, tr("Amőba"), tr("Játék vége! Az X nyerte a játékot!"));
        _model->newGame();
        break;
    case TicTacToeModel::PlayerO:
        QMessageBox::information(this, tr("Amőba"), tr("Játék vége! A O nyerte a játékot!"));
        _model->newGame();
        break;
    default:;
    }
}

void TicTacToeWidget::model_gameOver()
{
    QMessageBox::information(this, tr("Amőba"), tr("Játék vége! A játék döntetlen lett!"));
    _model->newGame();
}

void TicTacToeWidget::model_fieldChanged(int, int, TicTacToeModel::Player)
{
    update();
}

void TicTacToeWidget::loadGame()
{
    // betöltjük a kiválasztott játékot
    if (_model->loadGame(_loadGameWidget->selectedGame()))
    {
        _tableGraphics.clear();
        _tableGraphics.squeeze();
        _playerXGraphics.clear();
        _playerXGraphics.squeeze();

        init(_model->getBoardSize());

        _model->loadGame(_loadGameWidget->selectedGame());

        update();
        QMessageBox::information(this, tr("Amőba"), tr("Játék betöltve, következik: ") + ((_model->currentPlayer() == TicTacToeModel::PlayerX) ? "X" : "O") + "!");
    }
    else
    {
        QMessageBox::warning(this, tr("Amőba"), tr("A játék betöltése sikertelen!"));
    }
}

void TicTacToeWidget::saveGame()
{
    // elmentjük a kiválasztott játékot

    if (_model->saveGame(_saveGameWidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, tr("Amőba"), tr("Játék sikeresen mentve!"));
    }
    else
    {
        QMessageBox::warning(this, tr("Amőba"), tr("A játék mentése sikertelen!"));
    }
}

void TicTacToeWidget::configureGame()
{
    _tableGraphics.clear();
    _tableGraphics.squeeze();
    _playerXGraphics.clear();
    _playerXGraphics.squeeze();



    //delete _model;
    //delete _dataAccess;

    init(_configureGameWidget->newSize());

    //if (_loadGameWidget != nullptr) delete _loadGameWidget;
    //if (_saveGameWidget != nullptr) delete _saveGameWidget;
    //if (_configureGameWidget != nullptr) delete _configureGameWidget;

    update();

    //_boardSize = _configureGameWidget->newSize();
    //_model->setBoardSize(_configureGameWidget->newSize());

    //redraw();
}
