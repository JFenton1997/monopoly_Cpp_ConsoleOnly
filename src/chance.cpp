/********************************************************************************
chance.cpp: header file for the chance class
********************************************************************************/

#include "chance.h"

//defining constructor and destructor
chance::chance() {}
chance::~chance() {}

//display whole deck, used for debugging
void chance::displayDeck()
{
    for (int i = 0 ; i <15; i++)
    {
        cout<< chanceDeck[i].cardText<<endl;
        cout<< chanceDeck[i].type<<endl;
        cout<< chanceDeck[i].value<<endl;
        cout<<endl;
    }
}

//picking up a card
players chance::pickUpCard(int currentPlayer, players p, board b)
{
    cout<<"chance card"<<endl;
    cout<<"------------------------"<<endl;

    //if jail free card
    if(!chanceDeck[currentChanceCard].type.compare("jailFree"))
    {
        //if get out of jail is currently in the deck
        if(getOutOfJailFreeInDeck==true)
        {
            //give get out of jail to player
            p.playerVect[currentPlayer].gainJailFree();
            playerWithCard = currentPlayer;
            getOutOfJailFreeInDeck = false;
        }
        else
        {
            //if jail free card is missing, skip it in deck
            currentChanceCard++;
            if(currentChanceCard==15)
            {
                currentChanceCard = 0;
            }
        }
    }
    cout<<chanceDeck[currentChanceCard].cardText<<endl;
    //if back 3 spaces move player back 3 spaces
    if(!chanceDeck[currentChanceCard].type.compare("moveBack"))
    {
        p.playerVect[currentPlayer].movePlayer(chanceDeck[currentChanceCard].value);
        cout<<"player "<<currentPlayer<<" been moved back to "<<b.boardVect[p.playerVect[currentPlayer].currentLocation()].getName()<<endl;
    }

    //if move to specific sq, move player to square
    if(!chanceDeck[currentChanceCard].type.compare("move"))
    {
        //if pass go, give 200
        if(p.playerVect[currentPlayer].currentLocation()>chanceDeck[currentChanceCard].value)
        {
            p.playerVect[currentPlayer].updateMoney(200,currentPlayer);
        }
        p.playerVect[currentPlayer].goToLocation(chanceDeck[currentChanceCard].value);
    }

    //if money involved
    if(!chanceDeck[currentChanceCard].type.compare("money"))
    {
        //update money equal to value on card
        p.playerVect[currentPlayer].updateMoney(chanceDeck[currentChanceCard].value,currentPlayer);
    }

    //if going to jail, player go to jail
    if(!chanceDeck[currentChanceCard].type.compare("goToJail"))
    {
        p.playerVect[currentPlayer].goToJail();
    }

    //if repairs on houses
    if(!chanceDeck[currentChanceCard].type.compare("houseRepairs"))
    {
        int houses=0,hotels=0;
        //for all props
        for(unsigned int i = 0; i<b.boardVect.size(); i++)
        {
            //if prop is owned by current player and it has a hotel, increment hotels
            if(b.boardVect[i].getHouses() == 5 && b.boardVect[i].getOwner()== currentPlayer)
            {
                hotels++;
            }
            //if has houses, add houses to total of houses
            else if(b.boardVect[i].getOwner()== currentPlayer && b.boardVect[i].getHouses() < 5)
                houses += b.boardVect[i].getHouses();
        }
        //display findings
        cout <<endl<<"houses owned: "<<houses<<endl;
        cout <<"hotels owned: "<<hotels<<endl;
        //deduct money equal to calculations
        p.playerVect[currentPlayer].updateMoney(((hotels*100)+(houses*25))*-1,currentPlayer);
    }
    currentChanceCard++;
    if(currentChanceCard==14)
    {
        currentChanceCard = 0;
    }
    return p;
}





//initialising the chance deck
void chance::initialiseChanceDeck()
{
    //reading files
    string tempFilename;
    for (int i = 0; i<15; i++)
    {
        tempFilename = "chance"+std::to_string(i)+".txt";
        if (!ifstream(tempFilename))
        {
            cout <<"error, chance card "<< i <<" missing."<<endl;
        }
        else
        {
            ifstream chanceCardFile(tempFilename);
            getline(chanceCardFile,chanceDeck[i].cardText, '\n');
            getline(chanceCardFile,chanceDeck[i].type, '\n');
            chanceCardFile>>chanceDeck[i].value;
        }

    }
    //shuffle deck
    shuffle();
}

//shuffle deck
void chance::shuffle()
{
    std::random_shuffle(std::begin(chanceDeck),std::end(chanceDeck));
}

//if get out of jail free card is used
void chance::returnJailCard(int currentPlayer)
{
    if (currentPlayer == playerWithCard)
    {
        playerWithCard = 0;
        getOutOfJailFreeInDeck = true;
    }
}
