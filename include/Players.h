/********************************************************************************
players.h: header file for the players class
********************************************************************************/

#ifndef PLAYERS_H
#define PLAYERS_H
#include <Player.h>
#include "MonopolyHeader.h"
#include "dice.h"


class players: protected player
{
public:
    //vector of all the player objects
    vector<player> playerVect;
    //constructor and destructor
    players(vector<player> _playerVect);
    players();
    ~players();
    //functions and procedures
    void initialisePlayerVect(int i, bool isAI);
    int numberOfPlayers();
    void displayAllInfo();
    void displayTradingInfo(int currentPlayer, int tradingPlayer);
};

#endif // PLAYERS_H
