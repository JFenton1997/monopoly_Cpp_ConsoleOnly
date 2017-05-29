/********************************************************************************
sq.cpp: implementation file for the sq class
********************************************************************************/
#include "Sq.h"

//defining constructor and destructor
sq::sq() {}
sq::sq(string _sqName, string _sqType, string _colour, int _sqBuy, int _rent1, int _rent2,int _rent3,int _rent4,int _rent5,int _rent6, bool _mortgage, int _owner, int _house, int _ownerOfSet):
    sqName(_sqName), sqType(_sqType), colour(_colour), sqBuy(_sqBuy), rent{ _rent1,_rent2,_rent3,_rent4,_rent5,_rent6 }, isMortgage(_mortgage),
    owner(_owner), house(_house), ownerOfSet(_ownerOfSet) {}
sq::~sq() {}

//reads data from the given sqFile and fills in the attributes
void sq::readFile(ifstream& sqFile)
{
    string temp;
    while (!sqFile.eof())
    {
        //name
        getline(sqFile, sqName, '\n');
        //type
        getline(sqFile, sqType, '\n');
        //colour
        getline(sqFile, colour, '\n');
        //buy price
        sqFile >> sqBuy;
        //rents, 0houses to 5houses (hotel)
        for (int i = 0; i < 6; i++)
        {
            sqFile >> rent[i];
            getline(sqFile, temp, ',');

        }
    }
}

//setting the owner
void sq::setOwner(int newOwner)
{
    owner = newOwner;
}

//returns current owner
int sq::getOwner()
{
    return owner;
}

//returns buy price
int sq::getBuyPrice()
{
    return sqBuy;
}

//returns sq type
string sq::getType()
{
    return sqType;
}

//returns the correct rent
int sq::getRent()
{
    //if prop is part of a set with no houses
    if (owner !=0 && ownerOfSet == owner&& house == 0)
    {
        return rent[house]*2;
    }
    if (owner != 0)
    {
        //return rent equal to number of houses
        return rent[house];
    }
    else
    {
        //if no rent current, return buy price
        return sqBuy;
    }
}

//toggles mortgage and returns a value equal to the mortgage return value
int sq::toggleMortgage()
{
    if (isMortgage == true)
    {
        isMortgage = false;
        cout <<"property un-mortgaged"<<endl;
        return -((sqBuy*0.5)+(sqBuy*0.1));
    }
    else
    {
        isMortgage = true;
        cout<<"property mortgaged"<<endl;
        return (sqBuy*0.5);
    }
}

//setting station rent price to the number of stations owned
void sq::updateStationRent(int owned)
{
    house = owned-1;
}

//setting the set owner
void sq::updateSetOwner(int newOwner)
{
    ownerOfSet = newOwner;
}

//buying a house of the prop and returning the price of the house
int sq::buyHouse()
{
    //making sure house !>5
    if(house <5)
    {
        house++;
        //returning the price of the house which was just purchased, depending on the colour
        if(!colour.compare("brown")||!colour.compare("blue"))
        {
            return -50;
        }
        else if(!colour.compare("pink")||!colour.compare("orange"))
        {
            return -100;
        }
        else if(!colour.compare("red")||!colour.compare("yellow"))
        {
            return -150;
        }
        else if(!colour.compare("green")||!colour.compare("darkBlue"))
        {
            return -200;
        }
    }
    return 0;
}

//selling a house on the prop, and returning the money for selling a house
int sq::sellHouse()
{
    //double checking house !<0
    if(house >0)
    {
        house--;
        //returning the price of the house which was just sold, depending on the colour
        if(!colour.compare("brown")||!colour.compare("blue"))
        {
            return 25;
        }
        else if(!colour.compare("pink")||!colour.compare("orange"))
        {
            return 50;
        }
        else if(!colour.compare("red")||!colour.compare("yellow"))
        {
            return 75;
        }
        else if(!colour.compare("green")||!colour.compare("darkBlue"))
        {
            return 100;
        }
    }
    return 0;
}

//returns the cost of the house depending on the colour
int sq::valueOfHouse()
{
    if(!colour.compare("brown")||!colour.compare("blue"))
    {
        return 50;
    }
    else if(!colour.compare("pink")||!colour.compare("orange"))
    {
        return 100;
    }
    else if(!colour.compare("red")||!colour.compare("yellow"))
    {
        return 150;
    }
    else if(!colour.compare("green")||!colour.compare("darkBlue"))
    {
        return 200;
    }
    return 0;
}

//returns %10 of the buy price, needed for paying interest
int sq::tradeMortgage()
{
    return sqBuy*0.05;
}

//returns sqName
string sq::getName()
{
    return sqName;
}

//returns houses
int sq::getHouses()
{
    return house;
}

//returns colour
string sq::getColour()
{
    return colour;
}

//returns isMortgage
bool sq::getIsMortgage()
{
    return isMortgage;
}

//return set owner
int sq::getOwnerOfSet()
{
    return ownerOfSet;
}

//sets houses to 0, when player bankrupts
void sq::resetHouse()
{
    house = 0;
}



