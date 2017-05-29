/********************************************************************************
Player.cpp: implementation file for player class
********************************************************************************/
#include "Player.h"

//defined constructor and destructor
player::player() {}
player::player(int _money,int _boardLocation,bool _inJail,int _doublesInRow,int _turnsInJail,bool _isBankrupt, bool _isAI, int _getOutOfJailFreeCards):
    money(_money), boardLocation(_boardLocation), inJail(_inJail),doublesInRow(_doublesInRow),turnsInJail(_turnsInJail),isBankrupt(_isBankrupt),isAI (_isAI),
    getOutOfJailFreeCards(_getOutOfJailFreeCards) {}
player::~player() {}

//initialising starting attributes for start of the game
void player::intialisePlayer(bool isAI)
{
    money = 1500;
    boardLocation = 0;
    inJail = false;
    doublesInRow = 0;
    turnsInJail = 0;
    isBankrupt = false;
    isAI = false;
}

//for player to move along the board
int player::movePlayer(int i)
{
    boardLocation+= i;
    //when end of board, loop round
    if(boardLocation>39)
    {
        boardLocation-=40;
        //pass go, collect money
        money+=200;
    }
    return boardLocation;
}

//player going to jail
void player::goToJail()
{
    inJail = true;
    //jail sq
    boardLocation = 10;
}

//set player to sq location
void player::goToLocation(int i)
{
    boardLocation = i;
}

//player leaves jail
void player::leaveJail()
{
    inJail = false;
    turnsInJail = 0;
}

//updating money
void player::updateMoney(int i, int playerNo)
{
    // adding i to money, i can be negative
    money += i;
    //output changes to user
    if (i<=0)
    {
        cout <<"player "<<playerNo<<" paid: \x9c"<<-i<<endl;
    }
    else
    {
        cout <<"player "<<playerNo<<" gained: \x9c"<<i<<endl;
    }
}

//return number of jail cards
int player::getJailCards()
{
    return getOutOfJailFreeCards;
}

//gaining a jail card
void player::gainJailFree()
{
    getOutOfJailFreeCards++;
}

//using a jail card
void player::loseJailFree()
{
    getOutOfJailFreeCards--;
}

//if player gets a double
void player::addDouble()
{
    doublesInRow++;
}

//returning if player is currently in jail
bool player::getJail()
{
    return inJail;
}

//returning the players current location
int player::currentLocation()
{
    return boardLocation;
}

//returning the players current money
int player::getMoney()
{
    return money;
}

//returning doubles in row
int player::getDouble()
{
    return doublesInRow;
}

//resetting doubles in row
void player::resetDouble()
{
    doublesInRow = 0;
}

//adding turns in jail
void player::addTurnsInJail()
{
    turnsInJail++;
}

//returning number of turns in jail
int player::getTurnsInJail()
{
    return turnsInJail;
}

//returning if the player is currently bankrupt
bool player::getIsBankrupt()
{
    return isBankrupt;
}

//setting player to be bankrupted
void player::goBankrupt()
{
    isBankrupt = true;
}

