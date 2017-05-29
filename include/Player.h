/********************************************************************************
Player.h: Defines the header for the player class
********************************************************************************/



#ifndef PLAYER_H
#define PLAYER_H
#include "MonopolyHeader.h"

class player
{
    //variables stored per player object
private:
    int money;
    int boardLocation;
    bool inJail;
    int doublesInRow;
    int turnsInJail;
    bool isBankrupt;
    bool isAI;
    int getOutOfJailFreeCards;


public:
    //constructors and destructor
    player();
    player(int _money,int _boardLocation,bool _inJail,int _doublesInRow,int _turnsInJail,bool _isBankrupt,bool _isAI, int _getOutOfJailFreeCards);
    ~player();
    //prototypes of procedures and functions
    void updateMoney(int i, int playerNo);
    int currentLocation();
    int movePlayer(int i);
    int getMoney();
    void intialisePlayer(bool isAI);
    void goToJail();
    bool getJail();
    void leaveJail();
    void addTurnInJail();
    void addDouble();
    int getDouble();
    void resetDouble();
    int updateBoardLocation();
    void addTurnsInJail();
    int getTurnsInJail();
    void gainJailFree();
    void loseJailFree();
    void goToLocation(int i);
    int getJailCards();
    bool getIsBankrupt();
    void goBankrupt();
};

#endif // PLAYER_H
