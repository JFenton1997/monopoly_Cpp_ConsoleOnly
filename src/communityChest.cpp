/********************************************************************************
communityChest.cpp: header file for the communityChest class
********************************************************************************/

#include "communityChest.h"

//defining constructor and destructor
communityChest::communityChest() {}
communityChest::~communityChest() {}

//display whole deck, used for debugging
void communityChest::displayDeck()
{
    for (int i = 0 ; i <15; i++)
    {
        cout<< chestDeck[i].cardText<<endl;
        cout<< chestDeck[i].type<<endl;
        cout<< chestDeck[i].value<<endl;
        cout<<endl;
    }
}

//picking up cards, same as chance
players communityChest::pickUpCard(int currentPlayer, players p, board b)
{
    cout<<"communityChest card"<<endl;
    cout<<"------------------------"<<endl;

    //jail free card
    if(!chestDeck[currentChestCard].type.compare("jailFree"))
    {
        if(getOutOfJailFreeInDeck==true)
        {
            p.playerVect[currentPlayer].gainJailFree();
            playerWithCard = currentPlayer;
            getOutOfJailFreeInDeck = false;
        }
        else
        {
            currentChestCard++;
            if(currentChestCard==15)
            {
                currentChestCard = 0;
            }
        }
    }
    cout<<chestDeck[currentChestCard].cardText<<endl;
    //move to specific sq
    if(!chestDeck[currentChestCard].type.compare("move"))
    {
        if(p.playerVect[currentPlayer].currentLocation()>chestDeck[currentChestCard].value)
        {
            p.playerVect[currentPlayer].updateMoney(200,currentPlayer);
        }
        p.playerVect[currentPlayer].goToLocation(chestDeck[currentChestCard].value);
    }
    //money paid by others
    if(!chestDeck[currentChestCard].type.compare("moneyFromPlayers"))
    {
        for(unsigned int i = 1; i<p.playerVect.size(); i++)
        {
            if(i == currentPlayer)
            {
                p.playerVect[i].updateMoney(chestDeck[currentChestCard].value,i);
            }
            else
            {
                p.playerVect[i].updateMoney(-chestDeck[currentChestCard].value,i);
            }

        }

    }
    //money involved
    if(!chestDeck[currentChestCard].type.compare("money"))
    {
        p.playerVect[currentPlayer].updateMoney(chestDeck[currentChestCard].value,currentPlayer);
    }

    //going to jail
    if(!chestDeck[currentChestCard].type.compare("goToJail"))
    {
        p.playerVect[currentPlayer].goToJail();
    }

    //repairs on houses
    if(!chestDeck[currentChestCard].type.compare("houseRepairs"))
    {
        int houses=0,hotels=0;
        for(unsigned int i = 0; i<b.boardVect.size(); i++)
        {
            if(b.boardVect[i].getHouses() == 5 && b.boardVect[i].getOwner()== currentPlayer)
            {
                hotels++;
            }
            else if(b.boardVect[i].getOwner()== currentPlayer && b.boardVect[i].getHouses() < 5)
                houses += b.boardVect[i].getHouses();
        }
        cout <<endl<<"houses owned: "<<houses<<endl;
        cout <<"hotels owned: "<<hotels<<endl;
        p.playerVect[currentPlayer].updateMoney(((hotels*115)+(houses*40))*-1,currentPlayer);
    }

    currentChestCard++;
    if(currentChestCard==14)
    {
        currentChestCard = 0;
    }
    return p;
}





//reading files and filling in the attributes
void communityChest::initialiseChestDeck()
{
    string tempFilename;
    for (int i = 0; i<17; i++)
    {
        tempFilename = "chest"+std::to_string(i)+".txt";
        if (!ifstream(tempFilename))
        {
            cout <<"error, communityChest card "<< i <<" missing."<<endl;
        }
        else
        {
            ifstream chanceCardFile(tempFilename);
            getline(chanceCardFile,chestDeck[i].cardText, '\n');
            getline(chanceCardFile,chestDeck[i].type, '\n');
            chanceCardFile>>chestDeck[i].value;
        }

    }
    shuffle();
}

//shuffling deck
void communityChest::shuffle()
{
    std::random_shuffle(std::begin(chestDeck),std::end(chestDeck));
}

//if get out of jail free is returned
void communityChest::returnJailCard(int currentPlayer)
{
    if (currentPlayer == playerWithCard)
    {
        playerWithCard = 0;
        getOutOfJailFreeInDeck = true;
    }
}
