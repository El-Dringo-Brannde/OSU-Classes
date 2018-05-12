/*********************************************************************
 ** Program Filename: Declarations.h
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: declartions of functions to be used
 ** Input: none
 ** Output: none 
 *********************************************************************/
#ifndef Header_h
#define Header_h
#include "List.hpp"

void carorbike(char &);
void intro(int &, char &);
void menu_system(list invent, char type, int &);

int lot, menu_choice;
string maker, modelo, colore, fuel;
double miles, price;
char type, again;

#endif /* Header_h */
