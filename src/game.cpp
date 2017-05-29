/********************************************************************************
game.cpp: implementation file for the game class
********************************************************************************/
//turn limit
#define MAXTURNS 500

#include "game.h"
#include "functions.cpp"

//defining constructor and destructor
game::game()
{
    //ctor
}

game::~game()
{
    //dtor
}


//the gameStart function runs the monopoly game
boardState game::gameStart(boardState bs)
{
    intro();
    //if no game is currently being played initialise game settings
    if (bs.getSize()==0)
    {
        bs.gameEnded = false;
        cout <<"new game"<<endl;
        cout <<"------------------"<<endl;
        //get number of players for the game
        cout <<"how many players (must be 2 or higher):";
        cin >> numberOfPlayers;
        while(cin.fail() || numberOfPlayers<2)
        {
            cout << "invalid value" << endl;
            cout << "try Again: "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> numberOfPlayers;
        }
        //initialising the players and board information
        p = initialisePlayers(p,numberOfPlayers);
        b = initialiseBoard(b);
        //generating and shuffling the decks
        cc.initialiseChestDeck();
        cd.initialiseChanceDeck();
        //if files are missing
        if (b.boardVect.size()<40)
        {
            cout<<"files missing"<<endl;
            system("pause");
            return bs;
        }
    }
    //if game is already been initialised
    else
    {
        currentPlayer++;
        while(true)
        {
            if (CURRENTPLAYER.getIsBankrupt()==true)
            {
                currentPlayer++;
                continue;
            }
            if (currentPlayer>numberOfPlayers-1)
            {
                currentPlayer = 1;
                continue;
            }
            break;
        }


    }
    numberOfPlayers = p.numberOfPlayers();
    system("cls");
    //looping of turns
    for (turns = bs.getSize()+1; turns <MAXTURNS; turns++)
    {
        //updating the boardState class
        bs.addPlayerPosition(CURRENTPLAYER.currentLocation());
        //displaying player information
        showPlayerDetailsWithLocation(p,b,currentPlayer, turns);
        // turn
        while(true)
        {
            tempBankruptOwner = 0;
            wasInJail = false;
            //if player in jail
            if(CURRENTPLAYER.getJail() == true)
            {
                //prevents players who leave jail with a double from having a second turn
                wasInJail = true;
                cout<<"player "<<currentPlayer<<" has "<<CURRENTPLAYER.getJailCards()<< " get out of jail free cards"<<endl<<endl;
                CURRENTPLAYER.addTurnsInJail();
                choice = choiceJail(CURRENTPLAYER.getTurnsInJail());
                switch (choice)
                {
                //rolling for double
                case 1:
                {
                    showPlayerDetails(p,currentPlayer,turns);
                    rollBuffer();
                    system("cls");
                    showPlayerDetails(p,currentPlayer,turns);
                    d.roll();
                    bs.addDiceTotal(d.getRollTotal());
                    //if player rolls double
                    if (d.isDouble() == true)
                    {
                        cout<<endl<<"rolled double, leaving jail"<<endl;
                        buffer();
                        system("cls");
                        CURRENTPLAYER.leaveJail();
                        cout<<endl<<"                                            Landed On"<<endl<<endl;
                        b.displayLocationBoardInfo(p.playerVect[currentPlayer].movePlayer(d.getRollTotal()));
                        break;
                    }
                    //if player in jail for 3 turns
                    else if(CURRENTPLAYER.getTurnsInJail() == 3)
                    {
                        cout<<endl<<"failed to roll double, paying to leave jail due to being in for 3 turns"<<endl;
                        buffer();
                        system("cls");
                        CURRENTPLAYER.updateMoney(-50,currentPlayer);
                        CURRENTPLAYER.leaveJail();
                        cout<<endl<<"                                            Landed On"<<endl<<endl;
                        b.displayLocationBoardInfo(p.playerVect[currentPlayer].movePlayer(d.getRollTotal()));
                        break;
                    }
                    else
                    {
                        //if player fails to roll double
                        cout<<endl<<"failed to roll double"<<endl;
                        buffer();
                        system("cls");
                        break;

                    }
                }
                //paying to leave jail
                case 2:
                {
                    CURRENTPLAYER.updateMoney(-50,currentPlayer);
                    CURRENTPLAYER.leaveJail();
                    cout<<endl<<"                                            Landed On"<<endl<<endl;
                    b.displayLocationBoardInfo(p.playerVect[currentPlayer].movePlayer(d.roll()));
                    bs.addDiceTotal(d.getRollTotal());
                    break;
                }
                //using a getOutOfJailFree card
                case 3:
                {
                    if(CURRENTPLAYER.getJailCards()>0)
                    {
                        CURRENTPLAYER.loseJailFree();
                        CURRENTPLAYER.leaveJail();
                        cd.returnJailCard(currentPlayer);
                        cc.returnJailCard(currentPlayer);
                        cout<<endl<<"                                            Landed On"<<endl<<endl;
                        b.displayLocationBoardInfo(p.playerVect[currentPlayer].movePlayer(d.roll()));
                        bs.addDiceTotal(d.getRollTotal());
                        break;
                    }
                    //if player has no getOutOfJailFreeCards
                    else
                    {
                        cout<<"you have no 'get out of jail free' cards"<<endl;
                        cout<<"paying instead"<<endl;
                        buffer();
                        system("cls");
                        CURRENTPLAYER.updateMoney(-50,currentPlayer);
                        CURRENTPLAYER.leaveJail();
                        cout<<endl<<"                                            Landed On"<<endl<<endl;
                        b.displayLocationBoardInfo(p.playerVect[currentPlayer].movePlayer(d.roll()));
                        bs.addDiceTotal(d.getRollTotal());
                        break;
                    }
                }
                }
            }
            //if player isnt in jail
            else
            {
                rollBuffer();
                system("cls");
                //moving player
                cout<<endl<<"                                            Landed On"<<endl<<endl;
                b.displayLocationBoardInfo(p.playerVect[currentPlayer].movePlayer(d.roll()));
                //recording dice total
                bs.addDiceTotal(d.getRollTotal());
            }
            //display ui
            showPlayerDetails(p,currentPlayer,turns);
            tempPlayerPosition = p.playerVect[currentPlayer].currentLocation();

            //lands on chance
            if(!CURRENTBOARDSPACETYPE.compare("chance"))
            {
                bs.addPlayerPosition(CURRENTPLAYER.currentLocation());
                p = cd.pickUpCard(currentPlayer,p,b);
            }
            //updates position if position changes due to chance card
            if(tempPlayerPosition!=p.playerVect[currentPlayer].currentLocation())
            {
                buffer();
                system("cls");
                cout<<endl<<"                                            Landed On"<<endl<<endl;
                b.displayLocationBoardInfo(p.playerVect[currentPlayer].currentLocation());
                tempPlayerPosition = p.playerVect[currentPlayer].currentLocation();
            }

            //land on community chest
            if(!CURRENTBOARDSPACETYPE.compare("chest"))
            {
                bs.addPlayerPosition(CURRENTPLAYER.currentLocation());
                p = cc.pickUpCard(currentPlayer,p,b);
            }
            //updates position if position changes due to community chest card
            if(tempPlayerPosition!=p.playerVect[currentPlayer].currentLocation())
            {
                buffer();
                system("cls");
                cout<<endl<<"                                            Landed On"<<endl<<endl;
                b.displayLocationBoardInfo(p.playerVect[currentPlayer].currentLocation());
                tempPlayerPosition = p.playerVect[currentPlayer].currentLocation();
            }//updating position
            bs.addPlayerPosition(CURRENTPLAYER.currentLocation());
            //land on tax
            if(!CURRENTBOARDSPACETYPE.compare("tax"))
            {
                CURRENTPLAYER.updateMoney(-b.boardVect[tempPlayerPosition].getBuyPrice(),currentPlayer);
            }


            //land on goToJail
            if (!CURRENTBOARDSPACETYPE.compare("goToJail"))
            {
                bs.addPlayerPosition(10);
                CURRENTPLAYER.goToJail();
            }
            //paying rent on utility
            if (!CURRENTBOARDSPACETYPE.compare("utility") && b.boardVect[tempPlayerPosition].getOwner() != 0 && b.boardVect[tempPlayerPosition].getOwner() != currentPlayer
                    && b.boardVect[tempPlayerPosition].getIsMortgage() == false)
            {
                cout<<"rent"<<endl;
                CURRENTPLAYER.updateMoney((-b.boardVect[tempPlayerPosition].getRent()*d.getRollTotal()),currentPlayer);
                p.playerVect[b.boardVect[tempPlayerPosition].getOwner()].updateMoney(b.boardVect[tempPlayerPosition].getRent()*d.getRollTotal(),b.boardVect[tempPlayerPosition].getOwner());
                tempBankruptOwner = b.boardVect[tempPlayerPosition].getOwner();
            }

            //paying rent on station
            if (!CURRENTBOARDSPACETYPE.compare("station") && b.boardVect[tempPlayerPosition].getOwner() != 0 && b.boardVect[tempPlayerPosition].getOwner() != currentPlayer
                    && b.boardVect[tempPlayerPosition].getIsMortgage() == false)
            {
                cout<<"rent"<<endl;
                CURRENTPLAYER.updateMoney((-b.boardVect[tempPlayerPosition].getRent()),currentPlayer);
                p.playerVect[b.boardVect[tempPlayerPosition].getOwner()].updateMoney(b.boardVect[tempPlayerPosition].getRent(),b.boardVect[tempPlayerPosition].getOwner());
                tempBankruptOwner = b.boardVect[tempPlayerPosition].getOwner();
            }

            //paying rent on prop
            if (!CURRENTBOARDSPACETYPE.compare("prop") && b.boardVect[tempPlayerPosition].getOwner() != 0 && b.boardVect[tempPlayerPosition].getOwner() != currentPlayer
                    && b.boardVect[tempPlayerPosition].getIsMortgage() == false)
            {
                cout<<"rent"<<endl;

                CURRENTPLAYER.updateMoney((-b.boardVect[tempPlayerPosition].getRent()),currentPlayer);
                p.playerVect[b.boardVect[tempPlayerPosition].getOwner()].updateMoney(b.boardVect[tempPlayerPosition].getRent(),b.boardVect[tempPlayerPosition].getOwner());
                tempBankruptOwner = b.boardVect[tempPlayerPosition].getOwner();
            }

            //land on buy sq which is not owned/ buying prop
            if (!CURRENTBOARDSPACETYPE.compare("prop") || !CURRENTBOARDSPACETYPE.compare("station")|| !CURRENTBOARDSPACETYPE.compare("utility"))
            {

                if(ATCURRENTPLAYERLOCATION.getOwner() == 0)
                {
                    choice = choiceBuyProp();
                    switch (choice)
                    {
                    case 1:
                    {
                        system("cls");
                        CURRENTPLAYER.updateMoney(-b.boardVect[tempPlayerPosition].getBuyPrice(),currentPlayer);
                        ATCURRENTPLAYERLOCATION.setOwner(currentPlayer);
                        cout<<endl<<"                                            currently On"<<endl<<endl;
                        b.displayLocationBoardInfo(tempPlayerPosition);
                        showPlayerDetails(p,currentPlayer,turns);

                        break;
                    }
                    case 2:
                    {
                        system("cls");
                        //auction if not bought
                        p=b.auction(p,tempPlayerPosition);
                        break;
                    }
                    }
                }
            }

            buffer();
            system("cls");

            //rolling 3 doubles = jail
            if(d.isDouble() ==true && CURRENTPLAYER.getDouble()==2)
            {
                showPlayerDetails(p,currentPlayer,turns);
                cout<<"player "<<currentPlayer<<" goes to jail for speeding (3 doubles in row)"<<endl;
                buffer();
                CURRENTPLAYER.goToJail();
                break;
            }
            //rolled double
            else if (d.isDouble()==true && wasInJail == false)
            {
                p.playerVect[currentPlayer].addDouble();
                bs = playerMenuDouble(bs);
                if(CURRENTPLAYER.getIsBankrupt() == true)
                {
                    break;
                }
                else
                {
                    showPlayerDetailsWithLocation(p,b,currentPlayer, turns);
                    continue;
                }
            }
            //player menu
            else
            {
                bs = playerMenu(bs);
                if (goToMain == true)
                {
                    goToMain = false;
                    return bs;
                }
                break;
            }
        }
        //recording data
        bs.addRecord(b,p,currentPlayer);
        //bankrupt
        if (CURRENTPLAYER.getIsBankrupt()==true)
        {
            system("cls");
            cout <<"                player "<<currentPlayer<<" is BANKRUPT"<<endl;
            cout <<"---------------------------------------------------------"<<endl;
            //changing ownership of all props owned by current player to the player who bankrupt them
            for(unsigned int t= 0; t<b.boardVect.size(); t++)
            {
                if(b.boardVect[t].getOwner() == currentPlayer)
                {
                    b.boardVect[t].setOwner(tempBankruptOwner);
                    b.boardVect[t].resetHouse();
                    if (tempBankruptOwner !=0)
                    {
                        cout <<b.boardVect[t].getName()<<" new owner is "<<tempBankruptOwner<<endl;
                    }
                    else
                    {
                        cout <<b.boardVect[t].getName()<<" will be auctioned"<<endl;
                        buffer();
                        b.auction(p,t);
                    }
                    //player getting the prop pays interest due to rules in monopoly
                    if (b.boardVect[t].getIsMortgage() == true && tempBankruptOwner != 0)
                    {
                        cout<< "due to "<<b.boardVect[t].getName()<< " being mortgaged"<<endl;
                        p.playerVect[tempBankruptOwner].updateMoney(-b.boardVect[t].tradeMortgage(),tempBankruptOwner);
                        cout<<endl;

                    }
                    //if prop is auctioned, the new owner has to pay for obtaining a mortgage property
                    else if(b.boardVect[t].getIsMortgage() == true && tempBankruptOwner ==0)
                    {
                        p.playerVect[b.boardVect[t].getOwner()].updateMoney(-b.boardVect[t].tradeMortgage(),b.boardVect[t].getOwner());
                    }
                }
            }
            system("pause");
            //makes sure the player who is owed money get the money of the player who went bankrupt
            //stopping them getting more money than the current player had
            //and sets bankrupt player to 0 money
            p.playerVect[tempBankruptOwner].updateMoney(CURRENTPLAYER.getMoney(),tempBankruptOwner);
            CURRENTPLAYER.updateMoney(-CURRENTPLAYER.getMoney(),currentPlayer);
        }
        //reseting doubles and moving to new player
        system("cls");
        CURRENTPLAYER.resetDouble();
        currentPlayer++;
        while(true)
        {
            if (CURRENTPLAYER.getIsBankrupt()==true)
            {
                currentPlayer++;
                continue;
            }
            if (currentPlayer>numberOfPlayers-1)
            {
                currentPlayer = 1;
                continue;
            }
            break;
        }
        //winner check
        for( k = 1; k<p.playerVect.size(); k++)
        {
            if (p.playerVect[k].getIsBankrupt() == true)
            {
                counter++;
            }
            else
            {
                tempWinner = k;
            }
            if(counter == p.playerVect.size()-2)
            {
                gameEnd = true;
                break;
            }
        }
        counter = 0;
        //if winner is present
        if (gameEnd ==true)
        {
            break;
        }
    }

    //display when game is ended
    cout<<"                                              games ended"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
    b.displayBoard(p);
    p.displayAllInfo();
    cout<<"********************************--->  winner is "<<tempWinner<<"  <---*************************************************"<<endl;
    bs.gameEnded = true;
    buffer();
    return bs;
}



//player menu for choosing a action to do
boardState game::playerMenu(boardState bs)
{
    choice  = 0;
    turnEnd = false;
    //loop until user ends turn
    while(turnEnd==false)
    {
        for(unsigned int i = 1; i < p.playerVect.size(); i++)
        {
            b.updatingStationInfo(i);
            b.updatingUtilityInfo(i);
            b.updateSets(i);
        }
        system("cls");
        showPlayerDetailsWithLocation(p,b,currentPlayer,turns);

        choice = choicePlayerMenu();
        if(CURRENTPLAYER.getIsBankrupt()==true)
        {
            break;
        }
        switch (choice)
        {
        //ending turn
        case 1:
        {
            //if player has negative money, bankrupt player
            if (CURRENTPLAYER.getMoney()<0)
            {
                cout <<"you will go bankrupt due to negative funds, are you sure you want to end your turn (y): ";
                cin >>endCheck;
                while(cin.fail())
                {
                    cout << "invalid value" << endl;
                    cout << "try Again: "<<endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> endCheck;
                }
                if(endCheck == 'y' || endCheck == 'Y')
                {
                    turnEnd = true;
                    p.playerVect[currentPlayer].goBankrupt();
                }
            }
            else
            {
                system("cls");
                turnEnd = true;
            }
            break;
        }
        //displaying all board information
        case 2:
        {
            system("cls");
            b.displayBoard(p);
            p.displayAllInfo();
            buffer();
            break;
        }
        //displaying current players props and money
        case 3:
        {
            system("cls");
            b.displayPlayersProps(currentPlayer,p);
            buffer();
            break;
        }
        //mortgaging props
        case 4:
        {
            system("cls");
            p = b.mortgageProp(currentPlayer,p);
            break;

        }
        //buying and selling houses on sets
        case 5:
        {
            system("cls");
            p = b.buyingAndSelling(currentPlayer,p);

            break;

        }
        //trading with other player
        case 6:
        {
            system("cls");
            p = b.trading(currentPlayer,p);
            break;
        }
        //going back to the main menu
        case 7:
        {
            system("cls");
            if (CURRENTPLAYER.getMoney()<0)
            {
                cout <<"you will go bankrupt due to negative funds, are you sure you want to leave to menu and end your turn (y): ";
                cin >>endCheck;
                while(cin.fail())
                {
                    cout << "invalid value" << endl;
                    cout << "try Again: "<<endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> endCheck;
                }
                if(endCheck == 'y' || endCheck == 'Y')
                {
                    p.playerVect[currentPlayer].goBankrupt();
                }
            }
            bs.addRecord(b,p,currentPlayer);
            goToMain = true;
            return bs;
        }
        //forfeiting the game (self bankrupt)
        case 8:
        {
            system("cls");
            char endCheck;
            cout <<"forfeit player "<<currentPlayer<<endl;
            cout<<"-------------------------------"<<endl<<endl;
            cout <<"are you sure you want to do this (y): ";
            cin >>endCheck;
            while(cin.fail())
            {
                cout << "invalid value" << endl;
                cout << "try Again: "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> endCheck;
            }
            if(endCheck == 'y' || endCheck == 'Y')
            {
                turnEnd = true;
                p.playerVect[currentPlayer].goBankrupt();
                break;
            }
        }
        }
    }

    return bs;

}

//same as player menu, with last two options gone and output for rolling
//instead of ending turn
boardState game::playerMenuDouble(boardState bs)
{
    choice  = 0;
    turnEnd = false;

    while(turnEnd==false)
    {
        for(unsigned int i = 1; i < p.playerVect.size(); i++)
        {
            b.updatingStationInfo(i);
            b.updatingUtilityInfo(i);
            b.updateSets(i);
        }
        system("cls");
        showPlayerDetailsWithLocation(p,b,currentPlayer,turns);

        choice = choicePlayerMenuDouble();
        if(CURRENTPLAYER.getIsBankrupt()==true)
        {
            break;
        }
        switch (choice)
        {
        case 1:
        {
            if (CURRENTPLAYER.getMoney()<0)
            {
                cout <<"you will go bankrupt due to negative funds, are you sure you want to end your turn (y): ";
                cin >>endCheck;
                while(cin.fail())
                {
                    cout << "invalid value" << endl;
                    cout << "try Again: "<<endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> endCheck;
                }
                if(endCheck == 'y' || endCheck == 'Y')
                {
                    turnEnd = true;
                    p.playerVect[currentPlayer].goBankrupt();
                }
            }
            else
            {
                system("cls");
                turnEnd = true;
            }
            break;
        }
        case 2:
        {
            system("cls");
            b.displayBoard(p);
            p.displayAllInfo();
            buffer();
            break;
        }
        case 3:
        {
            system("cls");
            b.displayPlayersProps(currentPlayer,p);
            buffer();
            break;
        }
        case 4:
        {
            system("cls");
            p = b.mortgageProp(currentPlayer,p);
            break;

        }
        case 5:
        {
            system("cls");
            p = b.buyingAndSelling(currentPlayer,p);

            break;

        }
        case 6:
        {
            system("cls");
            p = b.trading(currentPlayer,p);
            break;
        }

        }
    }

    return bs;

}

