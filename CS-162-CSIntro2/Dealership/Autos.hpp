/*********************************************************************
 ** Program Filename: Autos.hpp
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: declarations of autos/cars functions
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Autos_hpp
#define Autos_hpp

#include <stdio.h>
#include "Vehicle.hpp"
using namespace std;

class autos: public vehicle {
private:
	int car_lot;
	string car_make, car_model, car_color, car_fuel;
	double miles, car_price;
	double horse_power;
	string auto_brakes;
	string coolio;
	
public:
	autos();
	double power();
	void ABS(string);
	void cool(string);
	int set_carlot();
	double get_miles();
	double get_price();
	string get_carmake();
	int get_carlot();
	string get_carcolor();
	string get_carfuel();
	string get_carmodel();
	void adjust_miles(double);
	string coolness();
	string get_cool();
	double get_power(); 
	
};


#endif /* Autos_hpp */
