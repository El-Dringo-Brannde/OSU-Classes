/*********************************************************************
 ** Program Filename: Vehicle.cpp
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: all getters / setters to be used by vehicles' children classes
 ** Input: none
 ** Output: none 
 *********************************************************************/
#include "Vehicle.hpp"


/*********************************************************************
 ** Function: vehicle constructor
 ** Description: constructs vehicle object
 ** Parameters:none
 ** Pre-Conditions: one of the child classes must be called
 ** Post-Conditions: none
 *********************************************************************/
vehicle:: vehicle(){
}


/*********************************************************************
 ** Function: setlot_num
 ** Description: Asks for the lot number to be used by children
 ** Parameters:none
 ** Pre-Conditions: child constructors must be called
 ** Post-Conditions: must be an int
 *********************************************************************/
int vehicle::setlot_num(){
	int lot;
	cout << "lot num?" << endl;
	cin >> lot;
	return lot;
}

/*********************************************************************
 ** Function: set_price
 ** Description: asks for price of vehicle, double checks if it is over $10000
 ** Parameters: none
 ** Pre-Conditions: child constructors need to be called
 ** Post-Conditions: must hit y to confirm
 *********************************************************************/
double vehicle:: set_price(){
	double price;
	char sure;
	cout << "What is the price of the vehicle?" << endl;
	cin >> price;
	if (price <= 0)		//double check to make sure no negatives
		do {
			cout << "Whoa you can't think I'll let you put a amount that low in my lot do you? " << endl;
			cin >> price;
		} while ( price <= 1 );
	if (price >=10000) // double check to make sure it is the correct price
		do{
				cout << "Whoa! Are you sure you want to put something that expensive on the market?" << "press 'y' for yes" <<endl;
				cin >> sure;
		}while ((sure != 'y') && (sure != 'Y'));
	
		return price;
}

/*********************************************************************
 ** Function: change_miles
 ** Description: asks and stores the mileage of the vehicle
 ** Parameters: none
 ** Pre-Conditions: child constructors need to be called
 ** Post-Conditions: must be an int
 *********************************************************************/
double vehicle::change_miles(){
	int mileage;
	cout << "What is the new mileage of the vehicle?" << endl;
	cin >> mileage;
	return mileage;
}


/*********************************************************************
 ** Function: set_fuel
 ** Description: get's the fuel level
 ** Parameters: none
 ** Pre-Conditions:	child constructors need to be called
 ** Post-Conditions: must be a string
 *********************************************************************/
string vehicle::set_fuel(){
	string fuel_level;
	cout << "What is the fuel level? (Ex: 5/8, half full, etc)" << endl;
	cin >> fuel_level;
	return fuel_level;
}


/*********************************************************************
 ** Function: set_model
 ** Description: asks what model the user wants
 ** Parameters: none
 ** Pre-Conditions: child constructors need to be called
 ** Post-Conditions: must be a string
 *********************************************************************/
string vehicle:: set_model(){
	string model;
	cout << "What is the model" << endl;
	cin >> model;
	return model;
}

/*********************************************************************
 ** Function:set_color
 ** Description: gets the color the user wants
 ** Parameters: none
 ** Pre-Conditions: child constructors need to be called
 ** Post-Conditions: must be a string
 *********************************************************************/
string vehicle::set_color(){
	string color;
	cout << "What color is the vehicle?" << endl;
	cin >> color;
	return color;
}

/*********************************************************************
 ** Function: set_make
 ** Description: gets the make of the vehicle
 ** Parameters: none
 ** Pre-Conditions: child constructors need to be called
 ** Post-Conditions: must be a string
 *********************************************************************/
string vehicle ::set_make(){
	string maker;
	cout << "What is the make of the vehicle?" << endl;
	cin >> maker;
	return maker;
}