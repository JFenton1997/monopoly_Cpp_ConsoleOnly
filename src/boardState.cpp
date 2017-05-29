/********************************************************************************
boardState.cpp: the implementation file for the chance class
********************************************************************************/

#include "boardState.h"

boardState::boardState()
{
    //ctor
}

boardState::~boardState()
{
    //dtor
}

//adding a record to the boardstates vector
void boardState::addRecord(board b, players p, int currentPlayer)
{
    gameStats.bs = b;
    gameStats.ps = p;
    gameStats.currentPlayer = currentPlayer;
    boardStates.push_back(gameStats);
    gameStats.playerPosition.clear();
    gameStats.rollTotals.clear();

}
//clearing the boardstates vector
void boardState::deleteGameData()
{
    boardStates.clear();
}

//adding dice rolls
void boardState::addDiceTotal(int total)
{
    gameStats.rollTotals.push_back(total);
}

//adding player positions
void boardState::addPlayerPosition(int position)
{
    gameStats.playerPosition.push_back(position);
}

//displaying all data in boardstates
void boardState::displayAllStates()
{
    for (unsigned int i= 0; i<boardStates.size(); i++)
    {
        cout<<"turn "<<i+1<<" stats                               current player: "<<boardStates[i].currentPlayer<<endl;
        cout<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<endl<<"Roll total of the turn";
        for(unsigned int j = 0; j<boardStates[i].rollTotals.size(); j++)
        {
            cout<<" -> "<<setw(2)<<boardStates[i].rollTotals[j];
        }
        cout<<endl<<"player positions of the turn";
        for(unsigned int j = 0; j<boardStates[i].playerPosition.size(); j++)
        {
            cout<<" -> "<<setw(2)<<boardStates[i].playerPosition[j];
        }
        cout<<endl<<endl;
        boardStates[i].bs.displayBoard(boardStates[i].ps);
        cout <<endl;
        boardStates[i].ps.displayAllInfo();
        cout<<endl<<"**********************************************************************************************************************************************"<<endl;
        cout<<endl<<endl;

    }
    if(!cin)
    {
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    system("pause");

}

//displaying a single entry in the boardvect
void boardState::displayState(unsigned int i)
{
    if (i-1<boardStates.size())
    {
        cout<<"turn "<<i<<" stats                               current player: "<<boardStates[i-1].currentPlayer<<endl;
        i--;
        cout<<"-----------------------------------------------------------------------------------------------"<<endl<<endl;
        cout<<endl<<"Roll total of the turn";
        for(unsigned int j = 0; j<boardStates[i].rollTotals.size(); j++)
        {
            cout<<" -> "<<setw(2)<<boardStates[i].rollTotals[j];
        }
        cout<<endl<<"player positions of the turn";
        for(unsigned int j = 0; j<boardStates[i].playerPosition.size(); j++)
        {
            cout<<" -> "<<setw(2)<<boardStates[i].playerPosition[j];
        }
        cout<<endl<<endl;
        boardStates[i].bs.displayBoard(boardStates[i].ps);
        cout <<endl;
        boardStates[i].ps.displayAllInfo();
        cout<<endl<<endl;
        if(!cin)
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        system("pause");
    }
    else
    {
        cout<<"no data"<<endl;
        if(!cin)
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        system("pause");

    }
}

int boardState::getSize()
{
    return boardStates.size();
}
