/*********************************************************************
 ** Program Filename: List.hpp
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: Declarations for list class
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include "Vehicle.hpp"
#include "Motorcycle.hpp"
#include "Autos.hpp"

class list{
private:
	class autos **cars;
	class motos **bikes;
	int arr_size, bike_arrsize;
	int capacity
	, bike_capacity;
	double biketotal_price, cartotal_price;
	
public:
	list();
	void search();
	void bikesearch();
	void print_chosenbike(int);
	void removebike(list,int);
	void removecar(list,int);
	void biketotalprice(int);
	void cartotalprice(int);
	void addcar(char, autos *);
	void addbike(char ,motos *);
	bool printcar();
	void printbike();
	void print_chosencar(int);
	void changevmiles(int); 
	void changebikemiles(int);
};

#endif /* List_hpp */
