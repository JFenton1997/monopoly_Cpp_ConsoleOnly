/********************************************************************************
dice.cpp: implementation file for dice class
********************************************************************************/
#include "dice.h"
#include <cstdlib>
//defining type from <random>, rng_type
typedef std::mt19937 rng_type;
//return a int from rng, udist, being equal to a dice roll
std::uniform_int_distribution<rng_type::result_type> udist(1, 6);
rng_type rng;

dice::dice() {}
dice::~dice() {}



//rolls dice then returns the roll total
int dice::roll()
{
    //generated value is between and including 1 and 6
    //generating a random seed using the system clock
    //random_number of data-type result_type is set random value 1,2,3,4,5 or 6
    if (seedGenerated == false){
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        //setting result_type const seed to equal seed
        rng_type::result_type const seedval = seed;
        rng.seed(seedval);
        seedGenerated = true;
    }
    rng_type::result_type random_number = udist(rng);
    //equal to random number
    diceValue[0] = random_number;
    //re-randomise random_number
    random_number = udist(rng);
    //equal to random number
    diceValue[1] =  random_number;
    //displaying information to the user
    cout<<"Dice rolled"<<endl<<"-------------"<<endl;
    cout << "Dice 1 = "<< diceValue[0] << "  Dice 2 = "<< diceValue[1];
    int rollTotal = diceValue[0] + diceValue[1];
    cout << "      roll total = "<< rollTotal<<endl;
    return rollTotal;
}



//check if a double, then return result
bool dice::isDouble()
{
    if (diceValue[1] == diceValue[0])
    {
        return true;
    }
    return false;
}

//returning roll total
int  dice::getRollTotal()
{
    int rollTotal = diceValue[0] + diceValue[1];
    return rollTotal;
}
