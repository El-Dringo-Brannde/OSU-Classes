/*********************************************************************
 ** Program Filename: Motorcycle.hpp
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: declarations for motos/bikes
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Motorcycle_hpp
#define Motorcycle_hpp

#include <stdio.h>
#include "Vehicle.hpp" 



class motos: public vehicle {
private:
	string bike_make, bike_model, bike_color, bike_fuel;
	double bike_miles, bike_price;
	int bike_lot;
	
	string bike_type;
	string saddle_bags;
	string handle_bars;
public:
	motos(); 
	string bike_kind();
	string saddle_kind();
	string handle_kind();
	string get_bikemake();
	string get_bikemodel();
	double get_bikemiles();
	int get_bikelot();
	string get_bikecolor();
	double get_bikeprice();
	void update_miles(double);
	string get_biketype();
	string get_bikegas();
};







#endif /* Motorcycle_hpp */
