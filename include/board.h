/********************************************************************************
board.h: header file for the board class
********************************************************************************/
#pragma once
#include "Sq.h"
#include "players.h"






class board
{
private:
    //struct storing information for the trading of props and money
    struct tradingStruct
    {
        vector<int> propVect;
        int money;
    };
    //struct storing information for auctions
    struct auctionStruct
    {
        int money=0;
        bool passed=false;
    } auctionStructVariable;
    vector<auctionStruct> auctionVect;
    //two iterations of the trading struct, one each each player of the trade
    tradingStruct tradingArray[2];
    //the board vector

public:
    //constructor and destructor
    board();
    ~board();
    vector<sq> boardVect;
    board(vector<sq> _boardVect);
    //functions and procedures
    void initialiseTradingArray();
    void displayPlayersPropsTrading(int playerNo, players p, int arrayIndex);
    void displayTradingInfo(int currentPlayer, int tradingPlayer);
    void tradingAddProp(int owner,int index,players p);
    void tradingRemoveProp(int currentPlayer, int tradingPlayer);
    void tradingMoney(int owner,int index,players p);
    players completeTrade(int owner, int tradingPlayer, players p);
    void intialiseBoard(int i,ifstream& sqFile);
    void displayBoard(players p);
    void displayPlayersProps(int playerNo,players p);
    void displayLocationBoardInfo(int i);
    void updatingStationInfo(int currentPlayer);
    void updatingUtilityInfo(int currentPlayer);
    void displayPlayersSets(int currentPlayer, players p);
    void updateSets(int currentPlayer);
    players mortgageProp(int currentPlayer, players p);
    players trading(int currentPlayer, players p);
    players buyingAndSelling(int currentPlayer,players p);
    players auction(players p, int sqNumber);
    bool checkEvenBuild(char checking,int currentSq);
};


