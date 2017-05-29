/*****************************************************************
extraFunctions.cpp: a cpp file which stores functions and
                    procedures used in all programs
*****************************************************************/

#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP


//adds buffer in code, allow user to read info and clear buffer
void buffer()
{
    if(!cin)
    {
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    system("pause");
}

//adds a buffer in code, telling user to roll the dice.
void rollBuffer()
{
    if(!cin)
    {
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    cout <<"***----> ROLL DICE <----***"<<endl;
    system("pause");
}
//shows players details
void showPlayerDetails(players p,int currentPlayer, int turn)
{
    cout <<"turn: "<<turn<<endl<<"current player: "<<currentPlayer<<endl<<"--------------------"<<endl<<"Money: \x9c" <<CURRENTPLAYER.getMoney()<<endl;
    cout<<endl;
}

//hows players details with location
void showPlayerDetailsWithLocation(players p,board b, int currentPlayer, int turn)
{
    cout <<"turn: "<<turn<<endl<<"current player: "<<currentPlayer<<endl<<"--------------------"<<endl<<"Money: \x9c" <<CURRENTPLAYER.getMoney()<<endl;
    b.displayLocationBoardInfo(p.playerVect[currentPlayer].currentLocation());
    cout<<endl;
}

//intro
void intro (void)
{
    cout << "                         MONOPOLY    created by James Fenton"<<endl;
}

//initialising the board vect
board initialiseBoard(board b)
{
    string filename;
    for (int i = 0; i < 40; i++)
    {
        filename ="sq"+std::to_string(i) + ".txt";
        if (ifstream(filename))
        {
            ifstream sqFile(filename);
            b.intialiseBoard(i, sqFile);
        }
        else
        {
            cout <<"sqFile "<< i <<" is missing.";
            buffer();
        }
    }
    return b;
}

//initialising the player vect
players initialisePlayers(players p, int number)
{
    for(int i = 0; i <number+1; i++)
    {
        p.initialisePlayerVect(i,false);

    }


    return p;
}

//choice menu
int choicePlayerMenu()
{
    int choice;
    cout<<endl<<"               do you want to do?"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"1:end turn"<<endl;
    cout<<"2:view whole board info"<<endl;
    cout<<"3:view you props and moneys"<<endl;
    cout<<"4:mortgage properties"<<endl;
    cout<<"5:buy and sell / view sets"<<endl;
    cout<<"6:trade properties"<<endl;
    cout<<"7:Back to program menu"<<endl;
    cout<<"8:forfeit(make self bankrupt)"<<endl;
    cout<<"selection: ";
    cin>>choice;
    while(cin.fail())
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
    }
    return choice;

}

//double menu
int choicePlayerMenuDouble()
{
    int choice;
    cout <<"**********--->you rolled a double<---***********"<<endl<<endl;
    cout<<endl<<"               do you want to do?"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"1:roll again"<<endl;
    cout<<"2:view whole board info"<<endl;
    cout<<"3:view you props and moneys"<<endl;
    cout<<"4:mortgage properties"<<endl;
    cout<<"5:buy and sell / view sets"<<endl;
    cout<<"6:trade properties"<<endl;
    cout<<"selection: ";
    cin>>choice;
    while(cin.fail())
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
    }
    return choice;

}

//buy prop menu
int choiceBuyProp()
{
    int choice;
    cout <<endl<<endl<<"do you want to buy the property?"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<< "1:yes"<<endl;
    cout<< "2:no"<<endl;
    cout<< "selection: ";
    cin>>choice;
    while(cin.fail() || choice <1 ||choice >2)
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
    }
    return choice;
}

//choice in jail menu
int choiceJail(int turnsInJail)
{
    int choice;
    cout<<endl<<endl<<"Player has been in jail for "<< turnsInJail<<" turns"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<< "1:roll for double"<<endl;
    cout<< "2:pay to leave"<<endl;
    cout<< "3:use get out of jail free card"<<endl;
    cout<< "selection: ";
    cin >>choice;
    while(cin.fail())
    {
        cout << "invalid value" << endl;
        cout << "try Again: "<<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
    }
    return choice;
}

#endif
