/********************************************************************************
boardState.h: the header file for the boardState class
********************************************************************************/

#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include <board.h>
#include <players.h>

class boardState : public board
{
    struct gameStatsStruct
    {
        board bs;
        players ps;
        int currentPlayer;
        vector<int> rollTotals;
        vector<int> playerPosition;
    };

public:
    boardState();
    ~boardState();
    gameStatsStruct gameStats;
    vector<gameStatsStruct> boardStates;
    bool gameEnded = false;
    void addRecord(board b,players p, int currentPlayer);
    void addDiceTotal(int total);
    void addPlayerPosition(int position);
    void displayAllStates();
    void displayState(unsigned int i);
    void deleteGameData();
    int getSize();

};

#endif // BOARDSTATE_H
