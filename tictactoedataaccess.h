#ifndef TICTACTOEDATAACCESS_H
#define TICTACTOEDATAACCESS_H

#include <QString>
#include <QVector>

class TicTacToeDataAccess // az adatelérés típusa (absztrakt osztály)
{
public:
    TicTacToeDataAccess() { }
    virtual ~TicTacToeDataAccess() { }

    virtual bool isAvailable() const { return false; } // rendelkezésre állás lekérdezése
    virtual QVector<QString> saveGameList() const = 0; // mentett játékok lekérdezése

    virtual bool loadGame(int gameIndex, QVector<int> &saveGameData) = 0; // játék betöltése
    virtual bool saveGame(int boardSize, int gameIndex, const QVector<int> &saveGameData) = 0; // játék mentése
};

#endif // TICTACTOEDATAACCESS_H
