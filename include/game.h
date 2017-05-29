/********************************************************************************
game.H: the implementation file for game class
          this is the main file where the whole monopoly game runs
********************************************************************************/

#ifndef GAME_H
#define GAME_H

//including headers for classes used in class
#include "MonopolyHeader.h"
#include "Players.h"
#include "board.h"
#include "dice.h"
#include "chance.h"
#include "communityChest.h"
#include "boardState.h"





class game
{
public:
    //constructors and destructor
    game();
    ~game();
    //the game
    boardState gameStart(boardState bs);

protected:

private:
    //variables used in monopoly
    board b;
    players p;
    dice d;
    communityChest cc;
    chance cd;
    int choice, tempPlayerPosition, tempWinner,tempBankruptOwner,currentPlayer =1,numberOfPlayers,turns = 0;
    unsigned int k,counter;
    bool wasInJail, turnEnd,gameEnd = false, goToMain = false;
    char endCheck;
    //player menu functions
    boardState playerMenu(boardState bs);
    boardState playerMenuDouble(boardState bs);

};

#endif // GAME_H
