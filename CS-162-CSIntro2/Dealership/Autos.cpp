/*********************************************************************
 ** Program Filename: Autos.cpp
 ** Author: Brandon Dring
 ** Date:1/29/16
 ** Description: getters and setters for Autos
 ** Input: various input suplied by user to be set
 ** Output: none
 *********************************************************************/

#include "Autos.hpp"

/*********************************************************************
 ** Function: autos constructor
 ** Description: assigns all information to the car object
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
autos::autos() : vehicle() {
	car_lot = setlot_num();
	car_make = set_make();
	car_model = set_model();
	car_color = set_color();
	car_fuel = set_fuel();
	miles = change_miles();
	car_price = set_price();
	horse_power = power();
	coolio = coolness();

}


/*********************************************************************
 ** Function:get_cool
 ** Description: get's whether the user entered if its cool or not
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string autos:: get_cool()
{	return coolio;}


/*********************************************************************
 ** Function: get_power
 ** Description: gets the horsepower of the car
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
double autos:: get_power()
{return horse_power; }

/*********************************************************************
 ** Function: coolness
 ** Description: asks for a cool feature the car has
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string autos :: coolness(){
	cout <<"What cool feature does this car have?" << endl;
	cin >> coolio;
	return coolio;
}

/*********************************************************************
 ** Function: power
 ** Description: lets user input how much horse power the car has
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
double autos :: power(){
	cout << "How much horse power does this puppy got?" << endl;
	cin >> horse_power;
	return horse_power;
}


/*********************************************************************
 ** Function: cool
 ** Description: lets user input something cool about the car
 ** Parameters: cool
 ** Pre-Conditions: cool must be a string
 ** Post-Conditions: none
 *********************************************************************/
void autos :: cool (string cool){
	coolio = cool;
}

/*********************************************************************
 ** Function: adjust_miles
 ** Description: lets user 'update' the miles
 ** Parameters: new_miles
 ** Pre-Conditions: none
 ** Post-Conditions: new_miles must be a double
 *********************************************************************/
void autos:: adjust_miles(double new_miles) {
	cout << "Keep this on the low low." << endl;
	cout << "But what is the 'new' mileage? ;D" << endl;
	cin >> new_miles;
	miles = new_miles;
}

/*********************************************************************
 ** Function: get_miles
 ** Description: returns miles from car
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
double autos :: get_miles()
{return miles;}

/*********************************************************************
 ** Function: get_carmake
 ** Description: returns the car make
 ** Parameters: none
 ** Pre-Conditions:none
 ** Post-Conditions:none
 *********************************************************************/
string autos:: get_carmake()
{ return car_make; }

/*********************************************************************
 ** Function: get_carlot
 ** Description: gets the lot the car is in
 ** Parameters:none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int autos :: get_carlot()
{return car_lot;}

/*********************************************************************
 ** Function: get_carmodel
 ** Description: returns the model of the car
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string autos:: get_carmodel()
{ return car_model;}

/*********************************************************************
 ** Function: get_carcolor
 ** Description: gets the color of the car
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string autos :: get_carcolor()
{return car_color;}

/*********************************************************************
 ** Function:get_price
 ** Description: gets the price of the vehicle
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
double autos:: get_price()
{return car_price;}


/*********************************************************************
 ** Function:get_carfuel
 ** Description: gets the fuel level of the car
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string autos :: get_carfuel()
{return car_fuel;}


