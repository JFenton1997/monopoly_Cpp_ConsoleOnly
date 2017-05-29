/********************************************************************************
dice.h: Defines the header for the dice class
********************************************************************************/


#ifndef DICE_H
#define DICE_H
#include "MonopolyHeader.h"


class dice
{
private:
    //array holding two values for each die
    int diceValue[2] = {0,0};
public:
    //constructor and destructor
    dice();
    ~dice();
    bool seedGenerated = false;
    //functions
    int roll();
    bool isDouble();
    int getRollTotal();
};

#endif // DICE_H
