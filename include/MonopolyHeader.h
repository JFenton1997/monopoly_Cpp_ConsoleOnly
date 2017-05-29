/********************************************************************************
MonopolyHeader.h : Defines the header file for all headerDictionaries used in program
here all the used headers are included as well as tell the program nameSpaces
********************************************************************************/



#pragma once
#ifndef MONOPOLYHEADER_H_INCLUDED
#define MONOPOLYHEADER_H_INCLUDED

#define CURRENTBOARDSPACETYPE b.boardVect[tempPlayerPosition].getType()
#define CURRENTPLAYER p.playerVect[currentPlayer]
#define ATCURRENTPLAYERLOCATION b.boardVect[tempPlayerPosition]


#include <fstream>
#include <istream>
#include <string>

#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>

#include <chrono>
#include <thread>
using namespace std::chrono;
using namespace std::this_thread;

using std::cout;
using std::cin;
using std::endl;

#include <vector>
using std::vector;

#include<string>
using std::string;

#include<fstream>
using std::ofstream;
using std::ifstream;

#include <iomanip>
using std::setw;
using std::setprecision;
using std::fixed;


#endif //MONOPOLYHEADER_H_INCLUDED
#pragma once


