/********************************************************************************
players.cpp: implementation file for the players class
********************************************************************************/
#include "Players.h"

//defining constructors and destructor
players::players() {}
players::~players() {}
players::players(vector<player> _playerVect):
    playerVect(_playerVect) { }

//initialise the player vector
void players::initialisePlayerVect(int i, bool isAI)
{
    playerVect.push_back(player(0,0,false,0,0,false,false,0));
    playerVect[i].intialisePlayer(isAI);
}

//returns the number of players
int players::numberOfPlayers()
{
    return playerVect.size();
}

//displaying all player information
void players::displayAllInfo()
{
    cout<<endl<<"                                           player Info"<<endl<<endl;
    cout<<" playerNo  Isbankrupt       money    location     jail    turnsInJail "<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
    for(unsigned int i =1; i<playerVect.size(); i++)
    {
        cout<<"   "<<setw(2)<<i<<"          "<<setw(2)<<playerVect[i].getIsBankrupt()
            <<"        \x9c"<<setw(7)<<playerVect[i].getMoney()
            << "     "<<setw(3)<<playerVect[i].currentLocation()
            <<"         "<<setw(2)<<playerVect[i].getJail()
            <<"           "<<setw(2)<<playerVect[i].getTurnsInJail()<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl<<endl;
}

//displaying player information of the players trading
void players::displayTradingInfo(int currentPlayer, int tradingPlayerInfo)
{
    cout<<endl<<"                                           player Info"<<endl<<endl;
    cout<<" playerNo  Isbankrupt       money    location     jail    turnsInJail "<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
    int i = currentPlayer;
    for(unsigned int j = 0; j<2; j++)
    {
        cout<<"   "<<setw(2)<<i<<"          "<<setw(2)<<playerVect[i].getIsBankrupt()
            <<"        \x9c"<<setw(7)<<playerVect[i].getMoney()
            << "     "<<setw(3)<<playerVect[i].currentLocation()
            <<"         "<<setw(2)<<playerVect[i].getJail()
            <<"           "<<setw(2)<<playerVect[i].getTurnsInJail()<<endl;
        i = tradingPlayerInfo;
    }
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl<<endl;
}

