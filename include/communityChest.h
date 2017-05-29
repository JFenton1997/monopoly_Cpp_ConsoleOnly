/********************************************************************************
communityChest.h: the header file for the communityChest class
********************************************************************************/

#ifndef COMMUNITYCHEST_H
#define COMMUNITYCHEST_H
#include "Players.h"
#include "board.h"


class communityChest
{
private:
    //data stored per community chest card
    struct communityChestCard
    {
        string cardText;
        string type;
        int value;
    };
    int currentChestCard = 0;
    int playerWithCard = 0;
    bool getOutOfJailFreeInDeck = true;
public:
    //constructor and destructor
    communityChest();
    ~communityChest();
    void returnJailCard(int currentPlayer);
    communityChestCard chestDeck[17];
    void displayDeck();
    void initialiseChestDeck();
    void shuffle();
    players pickUpCard(int currentPlayer, players p, board b);



};


#endif // COMMUNITYCHEST_H
