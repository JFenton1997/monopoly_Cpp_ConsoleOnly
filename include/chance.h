/********************************************************************************
chance.h: the header file for the chance class
********************************************************************************/
#ifndef CHANCE_H
#define CHANCE_H
#include "player.h"
#include "players.h"
#include "board.h"


class chance
{
private:
    //data stored per community chest card
    struct chanceCard
    {
        string cardText;
        string type;
        int value;
    };
    int currentChanceCard = 0;
    int playerWithCard = 0;
    bool getOutOfJailFreeInDeck = true;

public:
    //constructor and destructor
    chance();
    ~chance();
    void returnJailCard(int currentPlayer);
    int getSize();
    chanceCard chanceDeck[15];
    void displayDeck();
    void initialiseChanceDeck();
    void shuffle();
    players pickUpCard(int currentPlayer, players p, board b);



};

#endif // CHANCE_H
