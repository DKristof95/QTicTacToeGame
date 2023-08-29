#ifndef TICTACTOEDBDATAACCESS_H
#define TICTACTOEDBDATAACCESS_H

#include "tictactoedataaccess.h"

class TicTacToeDbDataAccess : public TicTacToeDataAccess // az adatelérés típusa adatbázisokra
{
public:
    TicTacToeDbDataAccess();
    ~TicTacToeDbDataAccess();

    bool isAvailable() const; // rendelkezésre állás lekérdezése
    QVector<QString> saveGameList() const; // mentett játékok lekérdezése

    bool loadGame(int gameIndex, QVector<int> &saveGameData); // játék betöltése
    bool saveGame(int boardSize, int gameIndex, const QVector<int> &saveGameData); // játék mentése
};

#endif // TICTACTOEDBDATAACCESS_H
