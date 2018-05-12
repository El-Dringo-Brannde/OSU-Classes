/*********************************************************************
 ** Program Filename: Declarations.h
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Just declarations for functions in main.
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Declarations_h
#define Declarations_h


#include <iostream>
#include <cstdlib>
#include "Creature.h"
#include "Gollum.h"
#include "Blue_men.h"
#include "Baba_Yaga.h"
#include "Unicorn.h"
#include "Barbarian.h"


using namespace std;

void intro();
void fighter();
void tofight();
void choose_attack (creature **, int &);
void choose_defender(int, int, int, creature **);
#endif /* Declarations_h */
