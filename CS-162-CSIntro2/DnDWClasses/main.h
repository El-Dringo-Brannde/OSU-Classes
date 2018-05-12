
/*********************************************************************
 ** Program Filename: main.h
 ** Author: Brandon Dring
 ** Date: 2/25/16
 ** Description:	declarations for program and includes
 ** Input: none
 ** Output: none
 *********************************************************************/

#ifndef main_h
#define main_h


#include "lose_list.h"
#include "Fight_que.h"
#include "Creature.h"
#include "Barbarian.h"
#include "Unicorn.h"
#include "Blue_men.h"
#include "Baba_Yaga.h"
#include "Gollum.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void intro();
int  choose_fighter(int );
creature *get_creature(int, int, creature *, int);





#endif /* main_h */
