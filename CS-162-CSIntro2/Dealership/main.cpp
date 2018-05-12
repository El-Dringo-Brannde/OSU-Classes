/*********************************************************************
 ** Program Filename: Dealership inventory
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: Allows the user to add, remove, and alter items in the 'inventory' 
 each class comes with it's own unique functions along with inherited functions
 ** Input: Dependant on User
 ** Output:	Dependant on User
 *********************************************************************/

#include <iostream>
#include "Vehicle.hpp"
#include "Declarations.h"
#include "Autos.hpp"
#include "Motorcycle.hpp"
#include "List.hpp"


int main(int argc, const char * argv[]){
	intro(menu_choice, type);
	list invent;	//creates list object
	
	menu_system(invent, type, menu_choice);
	
	
	return 0;
}

/*********************************************************************
 ** Function: Menu_system
 ** Description: Prompts the user if they want cars or bikes, and calls 
					  each class function respectively.
 ** Parameters: invent, type, &menu_choice
 ** Pre-Conditions: list object invent must have been created
 ** Post-Conditions: user must choose y or n to quit or go back to menu
 *********************************************************************/

void menu_system(list invent, char type, int &menu_choice){
	char choice, again;
	int adjust;
	
	if (menu_choice == 1){	//prints out vehicles in inventory
			cout << "What would you like to look at today?" << endl;
			cout << "'c' for cars, 'b' for bikes, or 'd' for both" << endl;
			cin >> choice;
		if (choice == 'c' || choice == 'C')
			invent.printcar();
		if (choice == 'b' || choice == 'B')
			invent.printbike();
		if (choice == 'd' || choice == 'D'){
			cout << "CARS!!!" << endl;
			invent.printcar();
			cout << "BIKES!!!" << endl;
			invent.printbike();
		}
	}
	
	else if (menu_choice == 2){	//Let's you adjust miles
			do {
				cout << "What would you like to look at today?" << endl;
				cout << "'c' for cars, 'b' for bikes" << endl;
				cin >> choice;
			}while ((choice != 'c') && (choice != 'C') && (choice !='b') && (choice != 'B'));
	
		
		if (choice == 'c' || choice == 'C'){
			if (invent.printcar() == false){	//checks to make sure list is not empty.
				cout << "Shucks! Nothing here!" << endl;
				intro(menu_choice,type);
				menu_system(invent, type, menu_choice);
			}
			cout << "What would you like to pick today?" << endl;
			cin >> adjust;
			invent.changevmiles(adjust);
		}
		if (choice == 'b' || choice == 'B'){
			invent.printbike();
			cout << "What would you like to pick today?" << endl;
			cin >> adjust;
			invent.changebikemiles(adjust); 
		}
		
	}
	
	else if (menu_choice == 3){	//searches through inventory
		do {
			cout << "What would you like to look at today?" << endl;
			cout << "'c' for cars, 'b' for bikes" << endl;
			cin >> choice;
		}while ((choice != 'c') && (choice != 'C') && (choice !='b') && (choice != 'B'));
		if (choice == 'c' || choice == 'C')
			invent.search();
		else if (choice == 'b' || choice == 'B')
			invent.bikesearch(); 
	}
	else if (menu_choice == 4){	//adds cars
		cout << "What would you like to look at today?" << endl;
		cout << "'c' for cars, 'b' for bikes" << endl;
		cin >> type;
		if (type == 'c'|| type == 'C'){
			autos *autoptr = new autos();
			invent.addcar(type, autoptr);
		}
		else if (type == 'b' || type == 'B'){
			motos *motoptr = new motos();
			invent.addbike(type, motoptr);
		}
	}
	
	else if (menu_choice == 5){	//takes cars off the inventory.. 
		int carnum,bikenum;
		
		cout << "What would you like to look at today?" << endl;
		cout << "'c' for cars, 'b' for bikes" << endl;
		cin >> choice;
		if (choice == 'c' || choice == 'C'){
			invent.printcar();
			cout << "What is the car you fancy?" << endl;
			cin >> carnum;
			invent.cartotalprice(carnum);
			invent.removecar(invent,carnum);
		}
		if (choice == 'b' || choice == 'B'){
			invent.printbike();
			cout << "What is the bike you fancy?" << endl;
			cin >> bikenum;
			invent.biketotalprice(bikenum);
			invent.removebike(invent,bikenum); 
		}
	}
	cout << "Would you like to see the menu again?" << endl;
	cout << "'y' for yes, else for no" << endl;
	cin >> again;
	cout << endl << endl;
	if (again == 'y' || again =='Y'){
		intro(menu_choice, type);
		menu_system(invent, type, menu_choice);
	}
	else
		cout << "You done son!" << endl;
	
}


/*********************************************************************
 ** Function: Intro
 ** Description: Welcomes the user to the program, gives display of options
 ** Parameters: &menu_choice, &type
 ** Pre-Conditions: none
 ** Post-Conditions: menu_choice must be between 1-5
 *********************************************************************/
void intro(int &menu_choice, char &type){
	cout << "WELCOME TO BRANDON'S AUTO EMPORIUM, HOME TO THE BEST BRANDS!" << endl;
	cout << "\t       What would you like to do today?" << "\n \n";
	cout << "'1' shows you the vehicles I have in stock" << endl;
	cout << "'2' adjusts the mileage for a car in inventory ('Unscrupulous')" << endl;
	cout << "'3' searches for a vehicle I have in inventory" << endl;
	cout << "'4' adds a vehicle to the inventory" << endl;
	cout << "'5' means you want to purchase one of my fine vehicles!" << endl;
	do{
	cout << "Please enter your choice" << endl;
	cin >> menu_choice;
	}while (menu_choice >= 5 && menu_choice <= 0);
}

