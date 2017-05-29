/********************************************************************************
sq.h: header file for class sq
********************************************************************************/
#pragma once
#include "MonopolyHeader.h"

class sq
{
private:
    //attributes of the sq class
    string sqName;
    string sqType;
    string colour;
    int sqBuy;
    bool isMortgage;
    int rent[6];
    int owner;
    int house;
    int ownerOfSet;
public:
    //constructors and destructor
    sq();
    sq(string _sqName, string _sqType, string _colour, int _sqBuy, int _rent1, int _rent2, int _rent3, int _rent4, int _rent5, int _rent6, bool _mortgage, int _owner, int _house, int _ownerOfSet);
    ~sq();
    //procedures and functions
    void readFile(ifstream& sqFile);
    void setOwner(int newOwner);
    string getName();
    int getOwner();
    int getHouses();
    string getColour();
    int getBuyPrice();
    int getRent();
    int toggleMortgage();
    bool getIsMortgage();
    void buyProp(int buyer);
    string getType();
    void updateSetOwner(int newOwner);
    int getOwnerOfSet();
    void updateStationRent( int owned);
    int buyHouse();
    int sellHouse();
    int valueOfHouse();
    int tradeMortgage();
    void resetHouse();
};

