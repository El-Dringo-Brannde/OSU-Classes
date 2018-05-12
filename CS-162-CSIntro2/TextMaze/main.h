/*********************************************************************
 ** Program Filename: Main.h
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: Declarations and libraries for program
 ** Input: none
 ** Output: none
 *********************************************************************/

#ifndef main_h
#define main_h


#include <iostream>
#include <fstream>
#include <cstdlib> 
#include "Game.h"
#include "Player.h"
#include "swan.h"

using namespace std;
void intro(game &, int &);
void getplaycoord(int &,int &, player &, int &, int &, actor **);
void givebegining(int &, int &, int &, int &, game &);



#endif /* main_h */
