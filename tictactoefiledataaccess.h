#ifndef TICTACTOEFILEDATAACCESS_H
#define TICTACTOEFILEDATAACCESS_H

#include "tictactoedataaccess.h"

class TicTacToeFileDataAccess : public TicTacToeDataAccess // az adatelérés típusa fájlokra
{
public:
    TicTacToeFileDataAccess() { }
    ~TicTacToeFileDataAccess() { }

    bool isAvailable() const { return true; } // rendelkezésre állás lekérdezése
    QVector<QString> saveGameList() const; // mentett játékok lekérdezése

    bool loadGame(int gameIndex, QVector<int> &saveGameData); // játék betöltése
    bool saveGame(int boardSize, int gameIndex, const QVector<int> &saveGameData); // játék mentése
};

#endif // TICTACTOEFILEDATAACCESS_H
