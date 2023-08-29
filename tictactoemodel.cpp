#include "tictactoemodel.h"

#include <QRandomGenerator>
#include <iostream>

TicTacToeModel::TicTacToeModel(int boardSize, TicTacToeDataAccess* dataAccess)
{
    _dataAccess = dataAccess;

    _boardSize = boardSize;

    //_gameTable = new Player*[3];
    _gameTable = new Player*[_boardSize];
    //for (int i = 0; i < 3; ++i)
    for (int i = 0; i < _boardSize; ++i)
    {
        //_gameTable[i] = new Player[3];
        _gameTable[i] = new Player[_boardSize];
    }
}

TicTacToeModel::~TicTacToeModel()
{
    delete[] _gameTable;
}

void TicTacToeModel::newGame()
{
    delete[] _gameTable;
    //_gameTable = new Player*[3];
    _gameTable = new Player*[_boardSize];
    //for (int i = 0; i < 3; ++i)
    for (int i = 0; i < _boardSize; ++i)
    {
        //_gameTable[i] = new Player[3];
        _gameTable[i] = new Player[_boardSize];
    }

    //for (int i = 0; i < 3; ++i)
    for (int i = 0; i < _boardSize; ++i)
        //for (int j = 0; j < 3; ++j)
        for (int j = 0; j < _boardSize; ++j)
        {
            _gameTable[i][j] = NoPlayer; // a játékosok pozícióit töröljük
        }

    _stepNumber = 0;
    _currentPlayer = PlayerX; // először az X lép

    emit playerChanged("X játékos következik.");
}

void TicTacToeModel::stepGame(int x, int y)
{
    //if (_stepNumber >= 9) // ellenőrizzük a lépésszámot
    if (_stepNumber >= (_boardSize*_boardSize))
        return;
    //if (x < 0 || x > 2 || y < 0 || y > 2) // ellenőrizzük a tartomány
    if (x < 0 || x > (_boardSize-1) || y < 0 || y > (_boardSize-1))
        return;
    if (_gameTable[x][y] != 0) { // ellenőrizzük a mezőt
        return;
    }

    _gameTable[x][y] = _currentPlayer; // pozíció rögzítése

    if (_currentPlayer == PlayerX) {
        _xList.append(qMakePair(x, y));
    } else if (_currentPlayer == PlayerO) {
        _oList.append(qMakePair(x, y));
    }

    emit fieldChanged(x, y, _currentPlayer); // jelezzük egy eseménykiváltással, hogy változott a mező

    _stepNumber++;

    checkGame();

    _currentPlayer = Player(_currentPlayer % 2 + 1);
    // egészként kezelhető az érték, de konvertálnunk kell

    if (_currentPlayer == PlayerX) {
        emit playerChanged("X játékos következik.");
    } else {
        emit playerChanged("O játékos következik.");
    }
}

bool TicTacToeModel::loadGame(int gameIndex)
{
    if (_dataAccess == nullptr || !_dataAccess->isAvailable()) // ellenőrizzük az adatelérést
        return false;

    QVector<int> saveGameData;

    if (!_dataAccess->loadGame(gameIndex, saveGameData)) // az adatelérés végzi a tevékenységeket
        return false;


    // feldolgozttuk a kapott vektort
    _boardSize = saveGameData[0];

    delete[] _gameTable;
    //_gameTable = new Player*[3];
    _gameTable = new Player*[_boardSize];
    //for (int i = 0; i < 3; ++i)
    for (int i = 0; i < _boardSize; ++i)
    {
        //_gameTable[i] = new Player[3];
        _gameTable[i] = new Player[_boardSize];
    }

    _stepNumber = saveGameData[1];
    _currentPlayer = Player(saveGameData[2]);
    for (int i = 0; i < _boardSize; ++i)
        for (int j = 0; j < _boardSize; ++j)
        {
            _gameTable[i][j] = Player(saveGameData[3 + i * _boardSize + j]);
        }

    return true;

    /*
    if (_dataAccess == nullptr || !_dataAccess->isAvailable()) // ellenőrizzük az adatelérést
        return false;

    QVector<int> saveGameData;

    if (!_dataAccess->loadGame(gameIndex, saveGameData)) // az adatelérés végzi a tevékenységeket
        return false;

    // feldolgozttuk a kapott vektort
    _stepNumber = saveGameData[0];
    _currentPlayer = Player(saveGameData[1]);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            _gameTable[i][j] = Player(saveGameData[2 + i * 3 + j]);
        }

    return true;
    */
}

bool TicTacToeModel::saveGame(int gameIndex)
{
    if (_dataAccess == nullptr || !_dataAccess->isAvailable()) // ellenőrizzük az adatelérést
        return false;

    QVector<int> saveGameData;

    // összerakjuk a megfelelő tartalmat
    saveGameData.push_back(_boardSize);
    saveGameData.push_back(_stepNumber);
    saveGameData.push_back(int(_currentPlayer));
    for (int i = 0; i < _boardSize; ++i)
        for (int j = 0; j < _boardSize; ++j)
        {
            saveGameData.push_back(int(_gameTable[i][j]));
        }

    return _dataAccess->saveGame(_boardSize, gameIndex, saveGameData); // az adatelérés végzi a tevékenységeket



    /*
    if (_dataAccess == nullptr || !_dataAccess->isAvailable()) // ellenőrizzük az adatelérést
        return false;

    QVector<int> saveGameData;

    // összerakjuk a megfelelő tartalmat
    saveGameData.push_back(_stepNumber);
    saveGameData.push_back(int(_currentPlayer));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            saveGameData.push_back(int(_gameTable[i][j]));
        }

    return _dataAccess->saveGame(gameIndex, saveGameData); // az adatelérés végzi a tevékenységeket
     */
}

QVector<QString> TicTacToeModel::saveGameList() const
{
    return _dataAccess->saveGameList(); // az adatelérés végzi a tevékenységeket
}

TicTacToeModel::Player TicTacToeModel::getField(int x, int y) const
{
    //if (x < 0 || x > 2 || y < 0 || y > 2) // ellenőrizzük a tartomány
    if (x < 0 || x > (_boardSize-1) || y < 0 || y > (_boardSize-1))
        return NoPlayer; // már a felsorolt értéket adjuk vissza

    return _gameTable[x][y];
}


void TicTacToeModel::checkGame()
{
    QPair<int, int> currentScore = find3To5Adjacent();

    if (currentScore.first == 5 || currentScore.second == 5) { // ha valaki győzött
        emit gameWon(_currentPlayer); // esemény kiváltása

    } else if (currentScore.first == 4 && _currentPlayer == PlayerX) {
        int randField = QRandomGenerator::global()->bounded(0, _xList.length());
        _gameTable[_xList[randField].first][_xList[randField].second] = NoPlayer;
        emit fieldChanged(_xList[randField].first, _xList[randField].second, _currentPlayer);
        _xList.removeAt(randField);

        randField = QRandomGenerator::global()->bounded(0, _xList.length());
        _gameTable[_xList[randField].first][_xList[randField].second] = NoPlayer;
        emit fieldChanged(_xList[randField].first, _xList[randField].second, _currentPlayer);
        _xList.removeAt(randField);

        _stepNumber -= 2;

    } else if (currentScore.second == 4 && _currentPlayer == PlayerO) {
        int randField = QRandomGenerator::global()->bounded(0, _oList.length());
        _gameTable[_oList[randField].first][_oList[randField].second] = NoPlayer;
        emit fieldChanged(_oList[randField].first, _oList[randField].second, _currentPlayer);
        _oList.removeAt(randField);

        randField = QRandomGenerator::global()->bounded(0, _oList.length());
        _gameTable[_oList[randField].first][_oList[randField].second] = NoPlayer;
        emit fieldChanged(_oList[randField].first, _oList[randField].second, _currentPlayer);
        _oList.removeAt(randField);

        _stepNumber -= 2;

    } else if (currentScore.first == 3 && _currentPlayer == PlayerX) {
        int randField = QRandomGenerator::global()->bounded(0, _xList.length());
        _gameTable[_xList[randField].first][_xList[randField].second] = NoPlayer;
        emit fieldChanged(_xList[randField].first, _xList[randField].second, _currentPlayer);
        _xList.removeAt(randField);

        _stepNumber --;

    } else if (currentScore.second == 3 && _currentPlayer == PlayerO) {
        int randField = QRandomGenerator::global()->bounded(0, _oList.length());
        _gameTable[_oList[randField].first][_oList[randField].second] = NoPlayer;
        emit fieldChanged(_oList[randField].first, _oList[randField].second, _currentPlayer);
        _oList.removeAt(randField);

        _stepNumber --;
    } else if (_stepNumber == (_boardSize*_boardSize)) { // döntetlen játék
        emit gameOver(); // esemény kiváltása
    }

}

QPair<int, int> TicTacToeModel::find3To5Adjacent() {

    int xMaxAdj = 0;
    int oMaxAdj = 0;

    /*for(int i = 0; i < _boardSize; ++i)
    {
        for (int j = 0; j <= _boardSize-5; ++j) {

            Player columnPlayer = _gameTable[i][j];
            Player linePlayer = _gameTable[j][i];
            Player diag1Player = _gameTable[i][j];
            Player diag2Player = _gameTable[i][j];

            int columnCounter = 1;
            int lineCounter = 1;
            int diag1Counter = 1;
            int diag2Counter = 1;

            for (int k = 0; k < 4; ++k) {

                // oszlopok ellenőrzése
                if (_gameTable[i][j+k] == _gameTable[i][j+k+1]) {
                    ++columnCounter;
                } else if (columnCounter < 3) {
                    columnCounter = 1;
                    columnPlayer = _gameTable[i][j+k+1];
                } else {
                    break;
                }

                // sorok ellenőrzése
                if (_gameTable[j+k][i] == _gameTable[j+k+1][i]) {
                    ++lineCounter;
                } else if (lineCounter < 3) {
                    lineCounter = 1;
                    linePlayer = _gameTable[j+k+1][i];
                } else {
                    break;
                }

                // átlók ellenőrzése
                if (i <= _boardSize-5) {
                    if (_gameTable[i+k][j+k] == _gameTable[i+k+1][j+k+1]) {
                        ++diag1Counter;
                    } else if (diag1Counter < 3) {
                        diag1Counter = 1;
                        diag1Player = _gameTable[i+k+1][j+k+1];
                    } else {
                        break;
                    }
                }
                if (i >= 4) {
                    if (_gameTable[i-k][j+k] == _gameTable[i-(k+1)][j+k+1]) {
                        ++diag2Counter;
                    } else if (diag2Counter < 3) {
                        diag2Counter = 1;
                        diag2Player = _gameTable[i-(k+1)][j+k+1];
                    } else {
                        break;
                    }
                }
            }


            std::cout << "i: " << i << ", j: " << j << ", cP: " << columnPlayer << ", cC: " << columnCounter << ", lP: " << linePlayer << ", lC: " << lineCounter  << ", d1P: " << diag1Player << ", d1C: " << diag1Counter << ", d2P: " << diag2Player << ", d2C: " << diag2Counter << std::endl;
            if (columnPlayer == PlayerX) {
                if (columnCounter > 2 && columnCounter > xMaxAdj) {
                    xMaxAdj = columnCounter;
                }
            } else if (columnPlayer == PlayerO) {
                if (columnCounter > 2 && columnCounter > oMaxAdj) {
                    oMaxAdj = columnCounter;
                }

            }


            if (linePlayer == PlayerX) {
                if (lineCounter > 2 && lineCounter > xMaxAdj) {
                    xMaxAdj = lineCounter;
                }
            } else if (linePlayer == PlayerO) {
                if (lineCounter > 2 && lineCounter > oMaxAdj) {
                    oMaxAdj = lineCounter;
                }

            }

            if (diag1Player == PlayerX) {
                if (diag1Counter > 2 && diag1Counter > xMaxAdj) {
                    xMaxAdj = diag1Counter;
                }
            } else if (diag1Player == PlayerO) {
                if (diag1Counter > 2 && diag1Counter > oMaxAdj) {
                    oMaxAdj = diag1Counter;
                }

            }

            if (diag2Player == PlayerX) {
                if (diag2Counter > 2 && diag2Counter > xMaxAdj) {
                    xMaxAdj = diag2Counter;
                }
            } else if (diag2Player == PlayerO) {
                if (diag2Counter > 2 && diag2Counter > oMaxAdj) {
                    oMaxAdj = diag2Counter;
                }

            }
        }
    }*/

    // győzelem ellenőrzése

    for(int i = 0; i < _boardSize; ++i) {
        for (int j = 0; j <= _boardSize-5; ++j) {
            // oszlopok ellenőrzése
            if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i][j+1] && _gameTable[i][j+1] == _gameTable[i][j+2] && _gameTable[i][j+2] == _gameTable[i][j+3] && _gameTable[i][j+3] == _gameTable[i][j+4]) {
                if (_gameTable[i][j] == PlayerX && xMaxAdj < 5) {
                    xMaxAdj = 5;
                } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 5) {
                    oMaxAdj = 5;
                }
            }
            // sorok ellenőrzése
            if (_gameTable[j][i] != 0 && _gameTable[j][i] == _gameTable[j+1][i] && _gameTable[j+1][i] == _gameTable[j+2][i] && _gameTable[j+2][i] == _gameTable[j+3][i] && _gameTable[j+3][i] == _gameTable[j+4][i]) {
                if (_gameTable[j][i] == PlayerX && xMaxAdj < 5) {
                    xMaxAdj = 5;
                } else if (_gameTable[j][i] == PlayerO && oMaxAdj < 5) {
                    oMaxAdj = 5;
                }
            }
            // átlók ellenőrzése
            if (i <= _boardSize-5) {
                if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i+1][j+1] && _gameTable[i+1][j+1] == _gameTable[i+2][j+2] && _gameTable[i+2][j+2] == _gameTable[i+3][j+3] && _gameTable[i+3][j+3] == _gameTable[i+4][j+4]) {
                    if (_gameTable[i][j] == PlayerX && xMaxAdj < 5) {
                        xMaxAdj = 5;
                    } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 5) {
                        oMaxAdj = 5;
                    }
                }
            }
            if (i >= 4) {
                if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i-1][j+1] && _gameTable[i-1][j+1] == _gameTable[i-2][j+2] && _gameTable[i-2][j+2] == _gameTable[i-3][j+3] && _gameTable[i-3][j+3] == _gameTable[i-4][j+4]) {
                    if (_gameTable[i][j] == PlayerX && xMaxAdj < 5) {
                        xMaxAdj = 5;
                    } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 5) {
                        oMaxAdj = 5;
                    }
                }
            }
        }
    }

    // 4 egymás melletti ellenőrzése

    for(int i = 0; i < _boardSize; ++i) {
        for (int j = 0; j <= _boardSize-4; ++j) {
            // oszlopok ellenőrzése
            if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i][j+1] && _gameTable[i][j+1] == _gameTable[i][j+2] && _gameTable[i][j+2] == _gameTable[i][j+3]) {
                    if (_gameTable[i][j] == PlayerX && xMaxAdj < 4) {
                        xMaxAdj = 4;
                    } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 4) {
                        oMaxAdj = 4;
                    }
            }
            // sorok ellenőrzése
            if (_gameTable[j][i] != 0 && _gameTable[j][i] == _gameTable[j+1][i] && _gameTable[j+1][i] == _gameTable[j+2][i] && _gameTable[j+2][i] == _gameTable[j+3][i]) {
                    if (_gameTable[j][i] == PlayerX && xMaxAdj < 4) {
                        xMaxAdj = 4;
                    } else if (_gameTable[j][i] == PlayerO && oMaxAdj < 4) {
                        oMaxAdj = 4;
                    }
            }
            // átlók ellenőrzése
            if (i <= _boardSize-4) {
                if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i+1][j+1] && _gameTable[i+1][j+1] == _gameTable[i+2][j+2] && _gameTable[i+2][j+2] == _gameTable[i+3][j+3]) {
                    if (_gameTable[i][j] == PlayerX && xMaxAdj < 4) {
                        xMaxAdj = 4;
                    } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 4) {
                        oMaxAdj = 4;
                    }
                }
            }
            if (i >= 3) {
                if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i-1][j+1] && _gameTable[i-1][j+1] == _gameTable[i-2][j+2] && _gameTable[i-2][j+2] == _gameTable[i-3][j+3]) {
                    if (_gameTable[i][j] == PlayerX && xMaxAdj < 4) {
                        xMaxAdj = 4;
                    } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 4) {
                        oMaxAdj = 4;
                    }
                }
            }
        }
    }

    // 3 egymás melletti ellenőrzése

    for(int i = 0; i < _boardSize; ++i) {
        for (int j = 0; j <= _boardSize-3; ++j) {
            // oszlopok ellenőrzése
            if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i][j+1] && _gameTable[i][j+1] == _gameTable[i][j+2]) {
                if (_gameTable[i][j] == PlayerX && xMaxAdj < 3) {
                    xMaxAdj = 3;
                } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 3) {
                    oMaxAdj = 3;
                }
            }
            // sorok ellenőrzése
            if (_gameTable[j][i] != 0 && _gameTable[j][i] == _gameTable[j+1][i] && _gameTable[j+1][i] == _gameTable[j+2][i]) {
                if (_gameTable[j][i] == PlayerX && xMaxAdj < 3) {
                    xMaxAdj = 3;
                } else if (_gameTable[j][i] == PlayerO && oMaxAdj < 3) {
                    oMaxAdj = 3;
                }
            }
            // átlók ellenőrzése
            if (i <= _boardSize-3) {
                if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i+1][j+1] && _gameTable[i+1][j+1] == _gameTable[i+2][j+2]) {
                    if (_gameTable[i][j] == PlayerX && xMaxAdj < 3) {
                        xMaxAdj = 3;
                    } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 3) {
                        oMaxAdj = 3;
                    }
                }
            }
            if (i >= 2) {
                if (_gameTable[i][j] != 0 && _gameTable[i][j] == _gameTable[i-1][j+1] && _gameTable[i-1][j+1] == _gameTable[i-2][j+2]) {
                    if (_gameTable[i][j] == PlayerX && xMaxAdj < 3) {
                        xMaxAdj = 3;
                    } else if (_gameTable[i][j] == PlayerO && oMaxAdj < 3) {
                        oMaxAdj = 3;
                    }
                }
            }
        }
    }


    return qMakePair(xMaxAdj, oMaxAdj);
}

int TicTacToeModel::getBoardSize() {
    return _boardSize;
}

void TicTacToeModel::setBoardSize(int n){
    _boardSize=n;
}
