/*********************************************************************
 ** Program Filename: Motorcycle.cpp
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: all getters and setters for motos/bikes class
 ** Input: none
 ** Output: none 
 *********************************************************************/

#include "Motorcycle.hpp"


/*********************************************************************
 ** Function: motos constructor
 ** Description: assigns all values to motorcycle object
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
motos::motos(){
	bike_make = set_make();
	bike_miles = change_miles();
	bike_model = set_model();
	bike_color = set_color();
	bike_price = set_price();
	bike_lot = setlot_num();
	bike_fuel = set_fuel();
	bike_type = bike_kind();

	
}

/*********************************************************************
 ** Function: bike_kind
 ** Description: gets bike information
 ** Parameters:none
 ** Pre-Conditions: none
 ** Post-Conditions: must be a string
 *********************************************************************/
string motos:: bike_kind(){
	string type_bike;
	cout << "What type of bike is it?" << endl;
	cin >> type_bike;
	bike_type = type_bike; 
	return bike_type;
}

/*********************************************************************
** Function: get_bikegas
** Description: gets the gas of the bike
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none 
*********************************************************************/
string motos :: get_bikegas()
{return bike_fuel;}

/*********************************************************************
** Function: get_biketype
** Description: returns the bike type
** Parameters:none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
string motos :: get_biketype()
{return bike_type; }

/*********************************************************************
 ** Function: update_miles
 ** Description: gets the information for updated mileage
 ** Parameters: update_miles
 ** Pre-Conditions: none
 ** Post-Conditions:updated_miles must be a double
 *********************************************************************/
void motos :: update_miles(double updated_miles){
	cout << "What is the new mileage?" << endl;
	cin >> updated_miles;
	bike_miles = updated_miles;
}

/*********************************************************************
 ** Function: get_bikemake
 ** Description: returns the make of the bike
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string motos :: get_bikemake()
{return bike_make;}

/*********************************************************************
 ** Function: get_bikemodel
 ** Description: returns the bike model
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string motos :: get_bikemodel()
{return bike_model;}

/*********************************************************************
 ** Function: get_bikemiles
 ** Description: gets the bike miles
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
double motos :: get_bikemiles()
{return bike_miles;}

/*********************************************************************
 ** Function: get_bikelot
 ** Description: gets the lot of the bike
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int motos :: get_bikelot()
{return bike_lot; }

/*********************************************************************
 ** Function: get_bikecolor
 ** Description: gets the bike color
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions:none
 *********************************************************************/
string motos :: get_bikecolor()
{return bike_color;}

/*********************************************************************
 ** Function:get_bikeprice
 ** Description: gets the bike price
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
double motos :: get_bikeprice()
{return bike_price;}












