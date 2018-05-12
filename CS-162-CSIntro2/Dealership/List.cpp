/*********************************************************************
 ** Program Filename: List.cpp
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: contains all elements of menu choices, and all list elements
 ** Input: dependent on user
 ** Output: dependent on user
 *********************************************************************/

#include "List.hpp"

/*********************************************************************
 ** Function: list constructor
 ** Description: builds array for both the cars and the bikes for the program
 ** Parameters: none
 ** Pre-Conditions: object must be created
 ** Post-Conditions: none
 *********************************************************************/
list::list(){
	bike_capacity = 2, capacity = 2;
	arr_size = 0, bike_arrsize = 0;
	cars = new autos*[capacity];	//instantiates lists of both kinds.
	bikes = new motos*[bike_capacity];
}




/*********************************************************************
 ** Function: biketotalprice
 ** Description: calculates the total price include fees, and interest payment
 ** Parameters: bikenum
 ** Pre-Conditions: bikenum must be valid as part of inventory number
 ** Post-Conditions: none
 *********************************************************************/
void list :: biketotalprice(int bikenum){
	biketotal_price = bikes[bikenum - 1] -> get_bikeprice() + 172 + 77; //sells car
	cout << "******SOLD*******" << endl;
	cout << "With the Registration, taxes, and title fee's it comes out too.. "
	<< "$" << biketotal_price << endl;
	cout << "To finance this vehicle, it would be " << biketotal_price/60<< "a month, paid over the next five years. " << endl <<
	"With interest at 12% (Highest legal in Oregon) the total is.. $" << biketotal_price * 1.12<< endl;
}



/*********************************************************************
 ** Function: cartotalprice
 ** Description: gets total car price with fees, and interest payment.
 ** Parameters: carnum
 ** Pre-Conditions: carnum must be valid int in inventory
 ** Post-Conditions: none
 *********************************************************************/
void list ::cartotalprice(int carnum){
	cartotal_price = cars[carnum - 1] -> get_price() +172 + 77;
	cout << "GOING GOING GONE!!! IT IS SOLD!!!" << endl;	//sells car prints price
	cout << "With the Registration, taxes, and title fee's it comes out too.. "
 << "$" << cartotal_price << endl;
		cout << "To finance this vehicle, it would be " << cartotal_price/60<<
	" a month, paid over the next five years." << endl <<  " With interest at 12%" <<
	"(Highest legal in Oregon) the total is.. $" << cartotal_price * 1.12<< endl;
}



/*********************************************************************
 ** Function: bikesearch
 ** Description: searches through the inventory for bikes of make, model,
					or price range.
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void list:: bikesearch(){
	string search_name;
	int search_type;
	double price_range;
	
	cout << "Howdy! Let's search what I have in the dealership!" <<endl;
	cout <<"What do you want to search by? Make, model, or price?" << endl;
	cout << "'1' for Make, '2' for Model, '3' for price" << endl;
	cin >>search_type;
	
	if (search_type == 1){ //search by make
		cout <<"Please type the make of what you want to search" << endl;
		cin >> search_name;
		cout << "Searching.." << endl;
		for (int i = 0; i < bike_arrsize; i++){
			if (bikes[i] != NULL){
				if (search_name == bikes[i]->get_bikemake()){
					cout << "FOUND IT!" << endl;
					list::print_chosenbike(i);
				}
				else{
					cout << "Damn! We don't got anything!" << endl;
					return;
				}
			}
		}
	}
	else if (search_type == 2){ //search by model
		cout << "Please type in the model you are looking for" << endl;
		cin >> search_name;
		cout << "Searching.. " << endl;
		for (int i = 0; i < bike_arrsize; i++){
			if (bikes[i] != NULL){
				if (search_name == bikes[i]-> get_bikemodel()){
					cout << "Hot dawg! We got something" << endl;
					list::print_chosenbike(i);
			}
				else{
					cout << "Man we aint got nothin!" << endl;
					return;
				}
			}
		}
		cout << "Sorry man, we don't got that" << endl;
	}
	else if (search_type == 3){	//search by price
		do {
			cout << "Please enter what you can afford homie" << endl;
			cin >> price_range;
		}while (price_range < 0);
		for (int i = 0; i < bike_arrsize; i++){
			if (bikes[i] != NULL){
			if (price_range > bikes[i] -> get_bikeprice()){
				cout << "We got something just for you!" << endl;
				list::print_chosenbike(i);
			}
			else
				return;
		}
			cout << "Dude, you're too poor to shop here." << endl;
		}
	}
}



/*********************************************************************
 ** Function: printcar
 ** Description: shows the inventory of cars for the user
 ** Parameters: none
 ** Pre-Conditions: cars must be intialized
 ** Post-Conditions: none
 *********************************************************************/
bool list :: printcar(){
	for (int i = 0; i < arr_size ; i++){	//prints vehicle info
		if (cars[i] != NULL){
			cout << i +1 << ".)"<< endl;
			cout << '\t' << "Make: " <<  cars[i] -> get_carmake() << endl;
			cout << '\t' << "Model: " <<  cars[i] -> get_carmodel() << endl;
			cout << '\t' << "Miles: " <<  cars[i] -> get_miles() << endl;
			cout << '\t' << "Lot Number: " << cars[i] -> get_carlot() << endl;
			cout << '\t' << "color: " << cars[i] -> get_carcolor() << endl;
			cout << '\t' << "Price: " << '$' << cars[i] -> get_price() << endl;
			cout << '\t' << "Fuel: " << cars[i] -> get_carfuel() << endl;
			cout << '\t' << "Cool stuff: " << cars[i]  -> get_cool() << endl;
			cout << '\t' << "Horsepower: " << cars[i] -> get_power() << endl;
		}
	}
	return true;
}

/*********************************************************************
 ** Function:print_chosenbike
 ** Description: shows the bike that the user searched for
 ** Parameters: num
 ** Pre-Conditions: num must be valid number in inventory
 ** Post-Conditions: none
 *********************************************************************/
void list :: print_chosenbike(int num){
	cout << num+1 <<  ".)" << endl << " \t The make is: " << bikes[num] -> get_bikemake() << endl;
	cout << " \t The miles it has is: " << bikes[num] -> get_bikemiles() << endl;
	cout  << " \t The model is: " << bikes[num] -> get_bikemodel() << endl;
	 cout << " \t The lot it is in is: " << bikes[num] -> get_bikelot() << endl;
	 cout << " \t The color of the vehicle is: " << bikes[num] -> get_bikecolor() << endl;
	 cout << " \t The price of the vehicle is: $" << bikes[num] -> get_bikeprice() << endl;
	cout << " \t The bike type is: " << bikes[num] -> get_biketype() << endl;
	cout << " \t The fuel level in the bike is: " << bikes[num] -> get_bikegas() << endl;
}





/*********************************************************************
 ** Function: search
 ** Description: searches through the car inventory by make, model, and price
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void list:: search(){
	string search_name;
	int search_type;
	double price_range;
	
	cout << "Howdy! Let's search what I have in the dealership!" <<endl;
	cout <<"What do you want to search by? Make, model, or price?" << endl;
	cout << "'1' for Make, '2' for Model, '3' for price" << endl;
	cin >>search_type;
	
	if (search_type == 1){	//search by make
		cout <<"Please type the make of what you want to search" << endl;
		cin >> search_name;
		cout << "Searching.." << endl;
		for (int i = 0; i <  arr_size; i++){
			if (cars[i] != NULL){
				if (search_name == cars[i]->get_carmake()){
					cout << "FOUND IT!" << endl;
					list::print_chosencar(i);
				}
				else{
					cout << "Damn! We don't got anything!" << endl;
					return;
				}
			}
		}
	}
	else if (search_type == 2){	//search by model
		cout << "Please type in the model you are looking for" << endl;
		cin >> search_name;
		cout << "Searching.. " << endl;
		for (int i = 0; i <  arr_size; i++){
			if (cars[i] != NULL){
				if (search_name == cars[i]-> get_carmodel()){
					cout << "Hot dawg! We got something" << endl;
					list::print_chosencar(i);
				}
				else	{
					cout << "Sorry bruh bruh, we don't got that" << endl;
					return;
				}
			}
		}
	}
	else if (search_type == 3){	//search by price
		do {
			cout << "Please enter what you can afford homie" << endl;
			cin >> price_range;
		}while (price_range < 0);
		for (int i = 0; i < arr_size; i++){
			if (cars[i] != NULL){
				if (price_range > cars[i] -> get_price()){
					cout << "We got something just for you!" << endl;
					list::print_chosencar(i);
				}
				else	{
					cout << "Dude, you're too poor to shop here." << endl;
					return;
				}
			}
		}
	}
}



/*********************************************************************
 ** Function:printbike
 ** Description: prints bike inventory
 ** Parameters:none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void list :: printbike(){
	for (int i = 0; i < bike_arrsize; i++){
				if (bikes[i] != NULL){
			cout << i+1 <<  ".)" << endl << " \t The make is.. " << bikes[i] -> get_bikemake() << endl;
			cout << " \t The miles it has is.. " << bikes[i] -> get_bikemiles() << endl;
			cout  << " \t The model is.. " << bikes[i] -> get_bikemodel() << endl;
			cout << " \t The lot it is in is.. " << bikes[i] -> get_bikelot() << endl;
			cout << " \t The color of the vehicle is.. " << bikes[i] -> get_bikecolor() << endl;
			cout << " \t The price of the vehicle is.. " << bikes[i] -> get_bikeprice() << endl;
		}
	}
}





/*********************************************************************
 ** Function: removecar
 ** Description: turns the pointer in the list cars to NULL so it isn't read off
 ** Parameters:invent, carnum
 ** Pre-Conditions: carnum must be valid int in inventory
 ** Post-Conditions: none
 *********************************************************************/
void list :: removecar(list invent, int carnum){
	delete cars[carnum -1];
	cars[carnum - 1] = NULL;	//wont show up in print inventory
}

/*********************************************************************
 ** Function: removebike
 ** Description: turns pointer to NULL so it isn't printed off
 ** Parameters: invent, bikenum
 ** Pre-Conditions: bikenum must be valid int chosen in the inventory
 ** Post-Conditions: none
 *********************************************************************/
void list :: removebike(list invent, int bikenum){
	delete bikes [bikenum -1 ];
	bikes[bikenum -1] = NULL; //wont show up in print inventory
}

		

/*********************************************************************
 ** Function: print_chosencar
 ** Description: prints the car off that the user picked out
 ** Parameters: chosen
 ** Pre-Conditions: chosen must be valid int in size of car array
 ** Post-Conditions: none
 *********************************************************************/
void list :: print_chosencar(int chosen){
	cout << '\t' << "Make: " <<  cars[chosen] -> get_carmake() << endl;
	cout << '\t' << "Model: " <<  cars[chosen] -> get_carmodel() << endl;
	cout << '\t' << "Miles: " <<  cars[chosen] -> get_miles() << endl;
	cout << '\t' << "Lot Number: " << cars[chosen] -> get_carlot() << endl;
	cout << '\t' << "color: " << cars[chosen] -> get_carcolor() << endl;
	cout << '\t' << "Price: " << '$' << cars[chosen] -> get_price() << endl;
}



/*********************************************************************
 ** Function: changebikemiles
 ** Description: updates the bike miles of a selected member
 ** Parameters: adjust
 ** Pre-Conditions: adjust must be valid int in array of bikes
 ** Post-Conditions: none
 *********************************************************************/
void list :: changebikemiles(int adjust){
	double updated_miles;
	bikes [adjust -1] -> update_miles(updated_miles);	//updates miles in bike
}

/*********************************************************************
 ** Function: changevmiles
 ** Description: changes the selected car miles
 ** Parameters: adjust
 ** Pre-Conditions: adjust must be valid size in the array
 ** Post-Conditions: none
 *********************************************************************/
void list :: changevmiles(int adjust){
	double new_miles;
	cars[adjust - 1]-> adjust_miles(new_miles); //updates miles in cars
	
}


/*********************************************************************
 ** Function: addbike
 ** Description: adds bike created to the array of objects, also resizes if 
					  capacity has been hit
 ** Parameters: type, *motoptr
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void list :: addbike(char type, motos *motoptr){
	if (bike_arrsize == bike_capacity){
			motos **temparray = new motos*[bike_capacity * 2];
			for (int i = 0; i < bike_arrsize; i++)
				temparray[i] = bikes[i];
			delete [] bikes;
		bike_capacity = bike_arrsize * 2;	//resizes array
			bikes = temparray;
			bikes[bike_arrsize] = motoptr;
			bike_arrsize++;
			cout << "added bike successfully!" << endl;
	}
	else {
		bikes[bike_arrsize] = motoptr;
		bike_arrsize++;
		cout << "Bike added successfully!" << endl;
		}
}



/*********************************************************************
 ** Function: addcar
 ** Description: add's object to array of cars
 ** Parameters: type, *autoptr
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void list::addcar(char type, autos *autoptr){
	if (arr_size == capacity){			//resizes array 
			autos **temparray = new autos*[capacity * 2];
			for (int i = 0; i < arr_size; i++)
				temparray[i] = cars[i];
			delete [] cars;
			capacity = arr_size * 2;
			cars = temparray;
			cars[arr_size] = autoptr;
			arr_size++;
			cout << "Car added successfully!" << endl;
	}
	else {
			cars[arr_size] = autoptr;
			arr_size++;
			cout << "Added car sucessfully!" << endl;
		}
}








