/********************************************************************************
board.cpp: implementation file for the board class
********************************************************************************/
#include "Board.h"

//defining constructor and destructor
board::board() {}
board::~board() {}
board::board(vector<sq> _boardVect):
    boardVect(_boardVect) {}

//initialising the board using a file
void board::intialiseBoard(int i,ifstream& sqFile)
{
    boardVect.push_back(sq("", "", "", 0, 0,0,0,0,0,0, false, 0, 0,0));
    boardVect[i].readFile(sqFile);
}

void Boardbuffer()
{
    if(!cin)
    {
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    system("pause");
}

//displays the board information of a specific sq
void board::displayLocationBoardInfo(int i)
{
    if(boardVect[i].getOwner() > 0)
    {
        cout<<" squareNo              Name                type     colour    ownership   rent"<<endl;
        cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
    }
    else
    {
        cout<<" squareNo              Name                type     colour    ownership      Buy Price"<<endl;
        cout<<"----------------------------------------------------------------------------------------------------------"<<endl;

    }
    cout<<setw(2)<<i<<"   "<<setw(25)<<boardVect[i].getName()
        << "       "<<setw(10)<<boardVect[i].getType()
        <<" "<<setw(10)<<boardVect[i].getColour()
        <<"       "<<setw(2)<<boardVect[i].getOwner()
        <<"         \x9c"<<setw(5)<<boardVect[i].getRent()<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl<<endl;

}

//displaying all the sq information of props owned by given player
void board::displayPlayersProps(int playerNo, players p)
{
    cout<<endl<<"Money: \x9c" <<p.playerVect[playerNo].getMoney()<<endl<<endl;
    cout<<" squareNo              Name                type     colour    ownership    Houses     mortgage    rentIfLand   "<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
    for(unsigned int i; i<boardVect.size(); i++)
    {
        if(boardVect[i].getOwner() == playerNo)
        {
            cout<<setw(2)<<i<<"   "<<setw(25)<<boardVect[i].getName()
                << "      "<<setw(10)<<boardVect[i].getType()
                <<" "<<setw(10)<<boardVect[i].getColour()
                <<"      "<<setw(2)<<boardVect[i].getOwner()
                <<"           "<<setw(2)<<boardVect[i].getHouses()
                <<"         "<<setw(2)<<boardVect[i].getIsMortgage()
                <<"         \x9c"<<setw(5)<<boardVect[i].getRent() <<endl;
        }
    }
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
    cout<< "jail free cards: "<<p.playerVect[playerNo].getJailCards()<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl<<endl;

}

//display props for the trading for the selection of props
void board::displayPlayersPropsTrading(int playerNo, players p, int arrayIndex)
{
    bool isTraded;
    cout<<endl<<"Money: \x9c" <<p.playerVect[playerNo].getMoney()<<endl<<endl;
    cout<<" squareNo              Name                type     colour    ownership    Houses     mortgage    rentIfLand   "<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
    //only shows props which arnt currently in the trade deal
    for(unsigned int i; i<boardVect.size(); i++)
    {
        isTraded = false;
        for(unsigned int j=0; j<tradingArray[arrayIndex].propVect.size(); j++)
        {
            if(i == tradingArray[arrayIndex].propVect[j])
            {
                isTraded = true;
            }
        }
        if(boardVect[i].getOwner() == playerNo && isTraded == false)
        {
            cout<<setw(2)<<i<<"   "<<setw(25)<<boardVect[i].getName()
                << "      "<<setw(10)<<boardVect[i].getType()
                <<" "<<setw(10)<<boardVect[i].getColour()
                <<"      "<<setw(2)<<boardVect[i].getOwner()
                <<"           "<<setw(2)<<boardVect[i].getHouses()
                <<"         "<<setw(2)<<boardVect[i].getIsMortgage()
                <<"         \x9c"<<setw(5)<<boardVect[i].getRent() <<endl;
        }
    }
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl<<endl;

}

//displays current trade details
void board::displayTradingInfo(int currentPlayer, int tradingPlayer)
{
    //puts players in array, allowing for the for loop to call them correctly
    int playerLabel[2] = {currentPlayer,tradingPlayer},check=0;
    for (unsigned int j = 0; j<2; j++)
    {
        //check allows for the return of nothing, if no props are present
        check =0;
        cout<<"                                       Player "<<playerLabel[j]<<" side"<<endl;
        if(tradingArray[j].propVect.size()>0)
        {
            check++;
            cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<" squareNo              Name                type     colour    ownership    Houses     mortgage    rentIfLand   "<<endl;
            cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
            for(unsigned int i=0; i<tradingArray[j].propVect.size(); i++)
            {
                cout<<setw(2)<<tradingArray[j].propVect[i]<<"   "<<setw(25)<<boardVect[tradingArray[j].propVect[i]].getName()
                    << "      "<<setw(10)<<boardVect[tradingArray[j].propVect[i]].getType()
                    <<" "<<setw(10)<<boardVect[tradingArray[j].propVect[i]].getColour()
                    <<"      "<<setw(2)<<boardVect[tradingArray[j].propVect[i]].getOwner()
                    <<"           "<<setw(2)<<boardVect[tradingArray[j].propVect[i]].getHouses()
                    <<"         "<<setw(2)<<boardVect[tradingArray[j].propVect[i]].getIsMortgage()
                    <<"         \x9c"<<setw(5)<<boardVect[tradingArray[j].propVect[i]].getRent() <<endl;
            }
        }
        if(tradingArray[j].money >0)
        {
            cout<<"----------------------------------------------------------------------------------------------------------"<<endl;
            check++;
            cout<< "money: \x9c"<<tradingArray[j].money<<endl;
        }
        if(check ==0)
        {
            cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
            cout <<"nothing"<<endl;
        }
        cout<<"----------------------------------------------------------------------------------------------------------------"<<endl<<endl<<endl;

    }
}



//display the whole board information with player locations shown
void board::displayBoard(players p)
{
    cout<<"                                            Monopoly Board"<<endl<<endl;
    cout<<" squareNo              Name                type     colour    ownership    Houses/sets   mortgage  rentIfLand | playerLocation "<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------|---------------"<<endl;
    for(unsigned int i; i<boardVect.size(); i++)
    {
        cout<<setw(2)<<i<<"   "<<setw(25)<<boardVect[i].getName()
            << "       "<<setw(10)<<boardVect[i].getType()
            <<" "<<setw(10)<<boardVect[i].getColour()
            <<"       "<<setw(2)<<boardVect[i].getOwner()
            <<"          "<<setw(2)<<boardVect[i].getHouses()
            <<"            "<<setw(2)<<boardVect[i].getIsMortgage()
            <<"         \x9c"<<setw(5)<<boardVect[i].getRent();
        cout<<"  | ";
        for(unsigned int j = 1; j<p.playerVect.size(); j++)
        {
            if (i == p.playerVect[j].currentLocation())
            {
                cout << " "<<setw(2)<<j;
            }
        }
        cout <<endl;
    }
    cout<<"--------------------------------------------------------------------------------------------------------------|-------------"<<endl<<endl;

}


//function for mortgaging props
players board::mortgageProp(int currentPlayer, players p)
{
    int choice, tempSqNo,tempCost;
    //loop until player stops mortgaging
    do
    {
        system("cls");
        cout <<"                              Mortgage Menu"<<endl;
        displayPlayersProps(currentPlayer,p);
        //display menu
        cout<<endl<<"1: mortgage/ un-mortgage"<<endl;
        cout<<"2: exit"<<endl;
        cout<<"selection: ";
        cin>> choice;
        while(cin.fail())
        {
            cout << "invalid value" << endl;
            cout << "try Again: "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
        {
            //mortgage prop
            system("cls");
            cout <<"                      Mortgaging"<<endl;
            displayPlayersProps(currentPlayer,p);
            cout<<"pick a property to mortgage/un-mortgage(select by sqNo): ";
            cin>> tempSqNo;
            while(cin.fail())
            {
                cout << "invalid value" << endl;
                cout << "try Again: "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> tempSqNo;
            }
            //if sq given is a prop with a house
            if (boardVect[tempSqNo].getHouses()>0 && !boardVect[tempSqNo].getType().compare("prop"))
            {
                cout << "cant mortgage a property with a house"<<endl;
                Boardbuffer();
                break;
            }
            //if sq's owner is current player
            if (boardVect[tempSqNo].getOwner() == currentPlayer)
            {
                //if mortgage currently, get price to un-mortgage
                if (boardVect[tempSqNo].getIsMortgage() == true)
                {
                    tempCost = boardVect[tempSqNo].getBuyPrice()*0.6;
                    //if player cant afford it
                    if (tempCost > p.playerVect[currentPlayer].getMoney())
                    {
                        cout << "cant afford to unmortgage property, cost: "<<tempCost<<endl;
                        Boardbuffer();
                        break;
                    }
                }
                //mortgage prop
                p.playerVect[currentPlayer].updateMoney(boardVect[tempSqNo].toggleMortgage(),currentPlayer);
                Boardbuffer();
            }
            else
            {
                //invalid selection
                cout << "invalid choice"<<endl;
                Boardbuffer();
            }

            break;
        }

        }
        cout<<"pick a property to mortgage/un-mortgage(select by sqNo): ";
        //if 2 was selected, return p
    }
    while(choice != 2);
    return p;
}

void board::initialiseTradingArray()
{
    //reset/initialise the trading array
    for (unsigned int i = 0; i<2; i++)
    {
        tradingArray[i].propVect.clear();
        tradingArray[i].money=0;
    }
}

//adding a prop to the trade
void board::tradingAddProp(int owner,int index,players p)
{
    cout <<"                                             Adding prop to deal (player "<<owner<<")"<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
    //display players props, which are not in the deal
    displayPlayersPropsTrading(owner,p,index);
    int tempSqNo;
    bool isTraded;
    cout<<"pick a property to add to trade(select by sqNo): ";
    cin>> tempSqNo;
    while(cin.fail() || tempSqNo<0 || tempSqNo >39)
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> tempSqNo;
    }
    //if the selected prop has a house on it
    if (boardVect[tempSqNo].getHouses()>0 && !boardVect[tempSqNo].getType().compare("prop"))
    {
        cout<< "cant trade a property with a house"<<endl;
        Boardbuffer();
        return;
    }
    //if property currently on the deal, prevent it form being on the deal
    isTraded = false;
    for(unsigned int i=0; i<tradingArray[index].propVect.size(); i++)
    {
        if(tempSqNo == tradingArray[index].propVect[i])
        {
            isTraded = true;
        }
    }
    //if the current player is the owner and the prop isnt currently in the trade
    if (boardVect[tempSqNo].getOwner() == owner &&isTraded==false)
    {
        cout << "prop added "<<endl;
        tradingArray[index].propVect.push_back(tempSqNo);
        Boardbuffer();
        return;
    }
    else
    {
        cout<<"invalid selection"<<endl;
        Boardbuffer();
    }
}

//adding money to the trade
void board::tradingMoney(int owner,int index,players p)
{
    int tempMoney;
    cout<<"adding money"<<endl;
    cout<<"player "<<owner<<" has currently \x9c"<<p.playerVect[owner].getMoney()<<endl;
    cout<<endl<<"money(can be set to 0 to remove):";
    //giving a value to add to the deal
    cin >> tempMoney;
    while(cin.fail())
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> tempMoney;
    }
    //if the value isnt less than 0 and isnt more than the players current money
    if(tempMoney<=p.playerVect[owner].getMoney() &&tempMoney>=0)
    {
        tradingArray[index].money=tempMoney;
        cout<<"money added to deal"<<endl;
        Boardbuffer();
    }
    else
    {
        //error message
        cout<<"the player currently cant afford it currently or invalid value"<<endl;
        Boardbuffer();
    }
}

//removing a prop from trade
void board::tradingRemoveProp(int currentPlayer, int tradingPlayer)
{
    displayTradingInfo(currentPlayer,tradingPlayer);
    int tempDelete;
    cout<<endl<<"please select a prop to remove from deal (sq numb): ";
    cin >>tempDelete;
    while(cin.fail())
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> tempDelete;
    }
    //looping through both trades
    for(unsigned int j = 0; j<2; j++)
    {
        //looping through all props in the in each trade
        for(unsigned int i = 0; i<tradingArray[j].propVect.size(); i++)
        {
            //if match
            if(tempDelete == tradingArray[j].propVect[i])
            {
                //erase entry in vector
                tradingArray[j].propVect.erase(tradingArray[j].propVect.begin()+i);
                cout<<"item deleted"<<endl;
                return;
            }
        }
    }
}

//transfer trade items when trade is accepted
players board::completeTrade(int owner, int tradingPlayer, players p)
{
    //player array allows for a "for" loop
    int playerArray[2] = {owner,tradingPlayer},otherPlayer;
    //loop twice, once for each side of the deal
    for(unsigned int j = 0; j<2; j++)
    {
        //other player to be opposite of j
        if(j == 1)
        {
            otherPlayer = 0;
        }
        else
        {
            otherPlayer = 1;
        }
        //exchanging of the money
        p.playerVect[playerArray[j]].updateMoney(-(tradingArray[j].money),playerArray[j]);
        p.playerVect[playerArray[otherPlayer]].updateMoney(tradingArray[j].money,playerArray[otherPlayer]);
        //loop through properties in deal
        for(unsigned int i = 0; i<tradingArray[j].propVect.size(); i++)
        {
            //changing owner
            boardVect[tradingArray[j].propVect[i]].setOwner(playerArray[otherPlayer]);
            //rule in monopoly, inheriting mortgage prop requires a payment of 10% of mortgage (5% of total buy)
            if (boardVect[tradingArray[j].propVect[i]].getIsMortgage() == true)
            {
                //pay 5% of mortgage as inheriting mortgage props
                p.playerVect[playerArray[otherPlayer]].updateMoney(-boardVect[tradingArray[j].propVect[i]].tradeMortgage(),playerArray[otherPlayer]);
            }
        }
    }
    //empty trading array
    initialiseTradingArray();
    return p;
}

//trading function
players board::trading(int currentPlayer, players p)
{
    int tradingPlayer,choice;
    char check;
    cout <<"                                                        Trading"<<endl;
    cout <<"--------------------------------------------------------------------------------------------------------------------------"<<endl;
    displayBoard(p);
    p.displayAllInfo();
    //selecting a trading partner
    cout <<"trading player, current player "<<currentPlayer<<endl;
    cout<<"-------------------------------------------"<<endl;
    cout<<"Selection: ";
    cin>>tradingPlayer;
    while(cin.fail())
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> tradingPlayer;
    }
    cin.ignore();
    //if value is a other player in the game
    if(tradingPlayer < p.playerVect.size() && tradingPlayer != 0 && tradingPlayer != currentPlayer && p.playerVect[tradingPlayer].getIsBankrupt() != true)
    {
        system("cls");
        initialiseTradingArray();
        cout <<"                                                     Trading"<<endl;
        cout <<"----------------------------------------------------------------------------------------------------------------------"<<endl;
        //start trading
        while(true)
        {
            system("cls");
            //display trading info
            displayTradingInfo(currentPlayer,tradingPlayer);
            //menu
            cout <<"trading Menu"<<endl;
            cout <<"1:add prop for player "<<currentPlayer<<endl;
            cout <<"2:add prop for player "<<tradingPlayer<<endl;
            cout <<"3:add/set money for player "<<currentPlayer<<endl;
            cout <<"4:add/set money for player "<<tradingPlayer<<endl;
            cout <<"5:remove prop for trade"<<endl;
            cout <<"6:propose deal to player "<<tradingPlayer<<endl;
            cout <<"7:cancel"<<endl;
            cout <<"------------------------------------------------------"<<endl;
            cout <<"selection: "<<endl;
            cin >>choice;
            while(cin.fail())
            {
                cout << "invalid value" << endl;
                cout << "try Again: "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> choice;
            }
            switch (choice )
            {
            //adding prop
            case 1:
            {
                system("cls");
                tradingAddProp(currentPlayer,0,p);
                break;
            }
            case 2:
            {
                system("cls");
                tradingAddProp(tradingPlayer,1,p);
                break;
            }
            //changing money in trade
            case 3:
            {
                system("cls");
                tradingMoney(currentPlayer,0,p);
                break;
            }
            case 4:
            {
                system("cls");
                tradingMoney(tradingPlayer,1,p);
                break;
            }
            //removing props
            case 5:
            {
                system("cls");
                tradingRemoveProp(currentPlayer,tradingPlayer);


                break;
            }
            //proposing deal
            case 6:
            {
                system("cls");
                displayTradingInfo(currentPlayer,tradingPlayer);
                cout <<endl<<"you sure you want to propose the trade (y): ";
                cin >>check;
                while(cin.fail())
                {
                    cout << "invalid value" << endl;
                    cout << "try Again: "<<endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> check;
                }
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                if(check == 'y' || check == 'Y')
                {
                    system("cls");
                    displayTradingInfo(currentPlayer,tradingPlayer);
                    //player to accept trade
                    cout <<endl<<"Player "<<tradingPlayer<< ",Do you accept this trade (y): ";
                    cin >>check;
                    while(cin.fail())
                    {
                        cout << "invalid value" << endl;
                        cout << "try Again: "<<endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                        cin >> check;
                    }
                    //if accepted
                    if(check == 'y' || check == 'Y')
                    {
                        cout<<"trade accepted"<<endl;
                        Boardbuffer();
                        p = completeTrade(currentPlayer,tradingPlayer,p);
                        return p;
                    }
                    else
                    {
                        cout<<"trade declined"<<endl;
                        Boardbuffer();
                    }
                }
                break;
            }
            //cancel trade
            case 7:
            {
                system("cls");
                cout <<"you sure you want to cancel the trade (y): ";
                cin >>check;
                if(check == 'y' || check == 'Y')
                {
                    initialiseTradingArray();
                    return p;
                }
                break;
            }
            }

        }

    }
    else
    {
        cout<<"invalid trading partner"<<endl;
    }

    return p;
}



//updates prices of train stations depending on owners
void board::updatingStationInfo(int currentPlayer)
{
    int playerStationsOwned = 0;
    //every station
    for (unsigned int i=5; i<boardVect.size(); i+=10)
    {
        //each time current player owns one
        if (boardVect[i].getOwner() == currentPlayer)
        {
            playerStationsOwned++;
        }
    }
    for (unsigned int i=5; i<boardVect.size(); i+=10)
    {
        //if owned, used the number playerStationOwned to set new price
        if (boardVect[i].getOwner() == currentPlayer )
        {
            boardVect[i].updateStationRent(playerStationsOwned);
        }
    }

}

//updating prices for utility
//same method as stations
void board::updatingUtilityInfo(int currentPlayer)
{
    int playerUtilitiesOwned = 0;
    for (int i = 12; i <=28; i+=16)
    {
        ;
        if (boardVect[i].getOwner() == currentPlayer)
        {
            playerUtilitiesOwned++;
        }
    }
    for (int i = 12; i <=28; i+=16)
    {
        if (boardVect[i].getOwner() == currentPlayer )
        {
            boardVect[i].updateStationRent(playerUtilitiesOwned);
        }
    }



}

//updating prices of sets / setting set owners
void board::updateSets(int currentPlayer)
{
    //to assign colour with a number of props
    struct colourStruct
    {
        string colour;
        int propNo;
    };
    int counter;
    //initialising array
    colourStruct colourArray[8]= {{"brown",2},{"blue",3},{"pink",3},{"orange",3},{"red",3},{"yellow",3},{"green",3},{"darkBlue",2}};
    //for each colour (set)
    for(int j = 0 ; j<8; j++)
    {
        counter =0;
        //for each sq on board
        for(unsigned int i = 0; i<boardVect.size(); i++)
        {
            //if current player owns the prop
            if(!colourArray[j].colour.compare(boardVect[i].getColour())&& boardVect[i].getOwner()== currentPlayer)
            {
                counter++;
                //if counter is equal to total props in set
                if (counter == colourArray[j].propNo)
                {
                    // if player owns set, set them as set owner
                    for(unsigned int k = 0; k<boardVect.size(); k++)
                    {
                        if(!colourArray[j].colour.compare(boardVect[k].getColour())&& boardVect[k].getOwner()== currentPlayer)
                        {
                            boardVect[k].updateSetOwner(currentPlayer);
                        }
                    }
                }
                // if they dont have all set props and they own it, set setOwner to 0
                else if (counter < colourArray[j].propNo && counter > 0 && i==39)
                {
                    for(unsigned int k = 0; k<boardVect.size(); k++)
                    {
                        if(!colourArray[j].colour.compare(boardVect[k].getColour())&& boardVect[k].getOwner()== currentPlayer)
                        {
                            boardVect[k].updateSetOwner(0);
                        }
                    }
                    break;
                }
            }
        }
    }

}

//checking for even building and even selling
bool board::checkEvenBuild(char checking,int currentSq)
{
    struct colourStruct
    {
        string colour;
        int propNo;
    };
    int counter,colourIndex;
    colourStruct colourArray[8]= {{"brown",2},{"blue",3},{"pink",3},{"orange",3},{"red",3},{"yellow",3},{"green",3},{"darkBlue",2}};
    counter =0;
    for (int j = 0; j<8; j++)
    {
        if(!boardVect[currentSq].getColour().compare(colourArray[j].colour))
        {
            colourIndex = j;
            break;
        }
    }
    //for each prop
    for(unsigned int i = 0; i<boardVect.size(); i++)
    {
        //buying
        if(checking =='b')
        {
            if(!colourArray[colourIndex].colour.compare(boardVect[i].getColour()))
            {
                //increment counter if prop has more or same houses
                if(boardVect[i].getHouses()>=boardVect[currentSq].getHouses())
                {
                    counter++;
                    //if counter equals total prop in set, return true
                    if (counter == colourArray[colourIndex].propNo)
                    {
                        return true;
                    }
                }
            }
        }
        //checking even selling
        else if(checking =='s')
        {
            if(!colourArray[colourIndex].colour.compare(boardVect[i].getColour()))
            {
                //increment counter if prop has less or same number of houses
                if(boardVect[i].getHouses()<=boardVect[currentSq].getHouses())
                {
                    counter++;
                    //if counter equals number of props in set, return true
                    if (counter == colourArray[colourIndex].propNo)
                    {
                        return true;
                    }
                }
            }
        }
    }
    //else return false
    return false;
}

//display all sets owned by current player
void board::displayPlayersSets(int currentPlayer, players p)
{
    cout<<endl<<"Money: \x9c" <<p.playerVect[currentPlayer].getMoney()<<endl<<endl;
    cout<<" squareNo              Name                type     colour    ownership    Houses     mortgage    rentIfLand   "<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
    for(unsigned int i; i<boardVect.size(); i++)
    {
        if(boardVect[i].getOwner() == currentPlayer && boardVect[i].getOwnerOfSet()== currentPlayer)
        {
            cout<<setw(2)<<i<<"   "<<setw(25)<<boardVect[i].getName()
                << "      "<<setw(10)<<boardVect[i].getType()
                <<" "<<setw(10)<<boardVect[i].getColour()
                <<"      "<<setw(2)<<boardVect[i].getOwner()
                <<"           "<<setw(2)<<boardVect[i].getHouses()
                <<"         "<<setw(2)<<boardVect[i].getIsMortgage()
                <<"         \x9c"<<setw(5)<<boardVect[i].getRent() <<endl;
        }
    }


}

//buying and selling of houses
players board::buyingAndSelling(int currentPlayer, players p)
{
    int choice, tempSqNo;
    do
    {
        system("cls");
        cout <<"                              buying and selling Menu"<<endl;
        cout <<"-----------------------------------------------------------------------------------------"<<endl;
        displayPlayersSets(currentPlayer,p);
        //menu
        cout<<endl<<"1: buy"<<endl;
        cout<<"2: sell"<<endl;
        cout <<"3: exit"<<endl;
        cout<<"selection: ";
        cin>> choice;
        while(cin.fail())
        {
            cout << "invalid value" << endl;
            cout << "try Again: "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
        {
            //buying a house
            system("cls");
            cout <<"                      Buying"<<endl;
            cout <<"-----------------------------------------------------------------------------------------"<<endl;
            displayPlayersSets(currentPlayer,p);
            cout<<"pick a property you wish to buy a house/hotel on (select by sqNo): ";
            cin>> tempSqNo;
            while(cin.fail())
            {
                cout << "invalid value" << endl;
                cout << "try Again: "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> tempSqNo;
            }
            //if owner is current player and the owner owns set
            if (boardVect[tempSqNo].getOwner() == currentPlayer&& boardVect[tempSqNo].getOwnerOfSet()==currentPlayer)
            {
                //if prop is not mortgage
                if(boardVect[tempSqNo].getIsMortgage() == false)
                {
                    //does not have a hotel
                    if(boardVect[tempSqNo].getHouses()<5)
                    {
                        //even buy returns true
                        if(checkEvenBuild('b',tempSqNo)==true)
                        {
                            //can afford the house
                            if(p.playerVect[currentPlayer].getMoney() - boardVect[tempSqNo].valueOfHouse()>0)
                            {
                                //build the house and update money
                                p.playerVect[currentPlayer].updateMoney(boardVect[tempSqNo].buyHouse(),currentPlayer);
                            }
                            //feedback
                            else
                            {
                                cout << "you cant afford to buy"<<endl;
                                Boardbuffer();

                            }
                        }
                        //feedback
                        else
                        {
                            cout << "you need to build evenly"<<endl;
                            Boardbuffer();
                        }


                    }
                    //feedback
                    else
                    {
                        cout << "cant build any more on that sq"<<endl;
                        Boardbuffer();
                    }
                }
                //feedback
                else
                {
                    cout << "cant build on mortgaged sq"<<endl;
                    Boardbuffer();
                }
            }
            //feedback
            else
            {
                cout << "invalid choice"<<endl;
                Boardbuffer();

            }
            break;
        }
        case 2:
        {
            system("cls");
            cout <<"                      Selling"<<endl;
            cout <<"-----------------------------------------------------------------------------------------"<<endl;
            displayPlayersSets(currentPlayer,p);
            cout<<"pick a property you wish to sell a house/hotel on (select by sqNo): ";
            cin>> tempSqNo;
            while(cin.fail())
            {
                cout << "invalid value" << endl;
                cout << "try Again: "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> tempSqNo;
            }
            //if currently owned by player and player owns set
            if (boardVect[tempSqNo].getOwner() == currentPlayer&& boardVect[tempSqNo].getOwnerOfSet()==currentPlayer)
            {
                //if it has a house
                if(boardVect[tempSqNo].getHouses()>0)
                {
                    //if even sell returns true
                    if(checkEvenBuild('s',tempSqNo)==true)
                    {
                        //sell house and update money
                        p.playerVect[currentPlayer].updateMoney(boardVect[tempSqNo].sellHouse(),currentPlayer);
                    }
                    else
                    {
                        cout << "you need to sell evenly"<<endl;
                        Boardbuffer();
                    }


                }
                else
                {
                    cout << "cant sell any more on that sq"<<endl;
                    Boardbuffer();
                }
            }
            else
            {
                cout << "invalid choice"<<endl;
                Boardbuffer();
            }
            break;
        }

        }
    }
    while(choice != 3);
    return p;
}

//auctioning props
players board::auction(players p, int sqNumber)
{
    bool winner= false;
    char bidCheck;
    int highestBid = 0,currentPlayer = 0,currentWinningPlayer = 0,counter = 0,bankruptCounter = 0;
    //initialising vector to store auction details per player
    for(int i =0; i<p.playerVect.size(); i++)
    {
        auctionVect.push_back(auctionStructVariable);
    }
    //loop until winner is found
    while(winner == false)
    {
        system("cls");
        //looping through active players
        currentPlayer++;
        while(true)
        {
            if (CURRENTPLAYER.getIsBankrupt()==true)
            {
                currentPlayer++;
                continue;
            }
            if (currentPlayer>p.playerVect.size()-1)
            {
                currentPlayer = 1;
                continue;
            }
            break;
        }
        //display information

        cout<<endl<<"                                            Auction On"<<endl<<endl;
        displayLocationBoardInfo(sqNumber);
        cout <<"current winning player: "<<currentWinningPlayer<<endl;
        cout <<"current highest bid is: \x9c"<<highestBid<<endl<<endl;
        cout <<"player "<<currentPlayer<<endl;
        cout <<"------------------------"<<endl;
        cout <<"do you want to bid (y):";
        //get if current auction player wants to bid
        cin >>bidCheck;
        while(cin.fail())
        {
            cout << "invalid value" << endl;
            cout << "try Again: "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> bidCheck;
        }
        if(!cin)
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        if(bidCheck == 'y' || bidCheck == 'Y')
        {
            system("cls");
            //displaying information to active player bider
            cout<<endl<<"                                            Auction On"<<endl<<endl;
            displayLocationBoardInfo(sqNumber);
            cout <<"current winning player: "<<currentWinningPlayer<<endl;
            cout << "current highest bid is: \x9c"<<highestBid<<endl<<endl;
            cout <<"player "<<currentPlayer<<endl;
            cout <<"------------------------------------"<<endl;
            cout <<"how much do you want to bid, you must bid higher than current bid:";
            //getting bid
            cin >> auctionVect[currentPlayer].money;
            while(cin.fail()||auctionVect[currentPlayer].money<=highestBid )
            {
                cout << "you must bid higher than current bid: "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> auctionVect[currentPlayer].money;
            }
            //setting new bid to highestBid and player
            highestBid = auctionVect[currentPlayer].money;
            currentWinningPlayer = currentPlayer;
            //new bid resets all passes, so other players can bid again
            for(unsigned int i = 1; i<p.playerVect.size(); i++)
            {
                auctionVect[i].passed = false;
            }
        }
        //player chooses not to bid
        else
        {
            cout <<"player "<<currentPlayer<<" passed"<<endl;
            system("pause");
            auctionVect[currentPlayer].passed = true;
        }
        system("cls");
        //checking if all players have passed after a bid
        for(unsigned int i = 1; i<p.playerVect.size(); i++)
        {
            if(p.playerVect[i].getIsBankrupt() == true)
            {
                bankruptCounter++;
            }
            if(auctionVect[i].passed == true)
            {
                counter++;
            }
        }
        //if the number of active players have all passed after a player has bid, the bidding player wins the auction
        if(counter == p.playerVect.size()-2-bankruptCounter && highestBid != 0)
        {
            winner = true;
            p.playerVect[currentWinningPlayer].updateMoney(-highestBid,currentWinningPlayer);
            boardVect[sqNumber].setOwner(currentWinningPlayer);
            auctionVect.clear();
            cout<<endl<<"                                            Auction finished"<<endl<<endl;
            displayLocationBoardInfo(sqNumber);
            return p;
        }
        //reset counters for next bid
        else
        {
            counter = 0;
            bankruptCounter = 0;
        }

    }
    return p;
}





