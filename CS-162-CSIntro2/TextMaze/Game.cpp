/*********************************************************************
 ** Program Filename:Game.cpp
 ** Author:Brandon Dring
 ** Date:3/11/16
 ** Description: All the game functions that have to do with the board at all, 
	 Or have to do with extracting anything from the players
 ** Input: Dependant on user, consists of WASD
 ** Output: new printed board, or player values depending on function call
 *********************************************************************/

#ifndef Game_cpp
#define Game_cpp

#include "main.h"

using namespace std;



/*********************************************************************
 ** Function: playernorth
 ** Description: checks to see if the player is north of the swan
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within board range
 ** Post-Conditions: none
 *********************************************************************/
bool game :: playernorth(int x, int y){
	if (maze[y-1][x] == 'P')
		return true;
	return false;
}

/*********************************************************************
 ** Function: playersouth
 ** Description: checks to see if the player is south of the swan
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within the board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: playersouth (int x, int y){
	if (maze[y+1][x] == 'P')
		return true;
	return false;
}

/*********************************************************************
 ** Function: playerwest
 ** Description: checks to see if the player is west of the swan
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within the board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: playerwest(int x, int y){
	if (maze[y][x-1] == 'P')
		return true;
	return false;
}

/*********************************************************************
 ** Function: playereast
 ** Description: checks to see if the player is east of the swan
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within the board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: playereast (int x, int y){
	if (maze[y][x+1] == 'P')
		return true;
	return false;
}

/*********************************************************************
 ** Function:swantestnorth
 ** Description: The swan checks to see if anything is to the north of the 
 swan that shouldn't be there, thus preventing movement.
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: swantestnorth(int x, int y) {
	if (maze[y-1][x] == '#' || maze[y-1][x] == 'S' || maze[y-1][x] == 'D'
		 || maze[y-1][x] == 'L' || maze[y-1][x] == 'A'|| maze[y-1][x] == 'X' || maze [y-1][x] == 'K')
		return true;
	return false;
}

/*********************************************************************
 ** Function:swantesteast
 ** Description: The swan checks to see if anything is to the east of the
 swan that shouldn't be there, thus preventing movement.
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: swantesteast(int x, int y) {
	if (maze[y][x+1] == '#' || maze[y][x+1] == 'S' || maze[y][x+1] == 'D'
		 || maze[y][x+1] == 'L' || maze[y][x+1] == 'A'|| maze[y][x+1] == 'X' || maze [y][x+1] == 'K')
		return true;
	return false;
}

/*********************************************************************
 ** Function:swantestsouth
 ** Description: The swan checks to see if anything is to the south of the
 swan that shouldn't be there, thus preventing movement.
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: swantestsouth(int x, int y) {
	if (maze[y+1][x] == '#' || maze[y+1][x] == 'S' || maze[y+1][x] == 'D'
		 || maze[y+1][x] == 'L' || maze[y+1][x] == 'A'|| maze[y+1][x] == 'X' || maze [y+1][x] == 'K')
		return true;
	return false;
}

/*********************************************************************
 ** Function:swantestwest
 ** Description: The swan checks to see if anything is to the west of the
 swan that shouldn't be there, thus preventing movement.
 ** Parameters: swanx, swany
 ** Pre-Conditions: must be within board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: swantestwest(int x, int y) {
	if (maze[y][x-1] == '#' || maze[y][x-1] == 'S' || maze[y][x-1] == 'D'
		 || maze[y][x-1] == 'L' || maze[y][x-1] == 'A'|| maze[y][x-1] == 'X' || maze [y][x-1] == 'K')
		return true;
	return false;
}


/*********************************************************************
 ** Function: testnorth
 ** Description: the player checks to make sure there is nothing that should
	 prevent movement, like walls. It also checks to make sure that if there is 
	 a door there, the player must have a key to pass through it.
 ** Parameters: swanx, swany, player object p1
 ** Pre-Conditions: must be within the board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: testnorth(int x, int y,player p1){
	if (maze[y-1][x] == '#' || maze[y-1][x] == 'S')
		return false;
	else if (maze[y-1][x] == 'D'){
		if (p1.givekeys() == 0){
			cout << "YOU SHALL NOT PASS, without a key." << endl;
			return false;
		}
		else{
			p1.minuskey();
			maze[y-1][x] = ' ';
			return true;
		}
	}
	return true;
}

/*********************************************************************
 ** Function: testsouth
 ** Description: the player checks to make sure there is nothing that should
 prevent movement, like walls. It also checks to make sure that if there is
 a door there, the player must have a key to pass through it.
 ** Parameters: swanx, swany, player object p1
 ** Pre-Conditions: must be within the board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: testsouth(int x, int y, player p1){
	if (maze[y + 1][x] == '#' || maze[y+1][x] == 'S')
		return false;
	else if (maze [y+1][x] == 'D'){
		if (p1.givekeys() == 0){
			cout << "YOU SHALL NOT PASS, without a key." << endl;
			return false;
		}
		else{
			p1.minuskey();
			maze[y+1][x] = ' ';
			return true;
		}
	}
	return true;
}


/*********************************************************************
 ** Function: testwest
 ** Description: the player checks to make sure there is nothing that should
 prevent movement, like walls. It also checks to make sure that if there is
 a door there, the player must have a key to pass through it.
 ** Parameters: swanx, swany, player object p1
 ** Pre-Conditions: must be within the board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: testwest (int x, int y, player p1){
	if (maze[y][x-1] == '#' || maze[y][x-1] == 'S')
		return false;
	else if (maze[y][x-1] == 'D'){
		if (p1.givekeys() == 0){
			cout << "YOU SHALL NOT PASS, without a key." << endl;
			return false;
		}
		else{
			p1.minuskey();
			maze[y][x-1] = ' ';
			return true;
		}
	}
	return true;
}


/*********************************************************************
 ** Function: testeast
 ** Description: the player checks to make sure there is nothing that should
 prevent movement, like walls. It also checks to make sure that if there is
 a door there, the player must have a key to pass through it.
 ** Parameters: swanx, swany, player object p1
 ** Pre-Conditions: must be within the board
 ** Post-Conditions: none
 *********************************************************************/
bool game :: testeast(int x, int y, player p1){
	if (maze[y][x+1] == '#' || maze[y][x+1] == 'S')
		return false;
	else if (maze[y][x+1] == 'D'){
		if (p1.givekeys() == 0){
			cout << "YOU SHALL NOT PASS, without a key." << endl;
			return false;
		}
		else{
			p1.minuskey();
			maze[y][x+1] = ' '; 
			return true;
		}
	}
	return true;
}


/*********************************************************************
 ** Function: openandget
 ** Description: gets the levelnumber, corresponding to an array of txt files
	 and opens the files, and reading it to a dynamic array that scales with size
	 of the first two numbers
 ** Parameters: level_num
 ** Pre-Conditions: level_arr must contain values, you can find it in constructor
 ** Post-Conditions: none
 *********************************************************************/
void game :: openandget(int num){
	int levelheight, levelwidth;
	if (num == 0){
	ifstream inputfile;
		
	inputfile.open("floor_1.txt");
	if (inputfile.is_open())
		cout << "File opened successfully!" << endl;
	else{
		cout << "ERROR opening file!" << endl;
		exit(0);
	}
	inputfile >> levelheight;
	inputfile >> levelwidth;
	inputfile.ignore();
	
	height = levelheight;
	width = levelwidth;
	
	maze = new char*[height];
	for (int i = 0; i < height; i++)
		maze[i] = new char[width];
	
	for(int a = 0; a < height; a++)
		for (int b = 0; b < width; b++){
			data = inputfile.get();
			maze[a][b] = data;
		}
	inputfile.close();
	}
	if (num == 1) {
		ifstream inputfile;
		inputfile.open("floor_2.txt");
		if (inputfile.is_open())
			cout << "File opened successfully!" << endl;
		else{
			cout << "ERROR opening file!" << endl;
			exit(0);
		}
		
		inputfile >> levelheight;
		inputfile >> levelwidth;
		inputfile.ignore();
		
		height = levelheight;
		width = levelwidth;
		
		maze = new char*[height];
		for (int i = 0; i < height; i++)
			maze[i] = new char[width];
		
		for(int a = 0; a < height; a++)
			for (int b = 0; b < width; b++){
				data = inputfile.get();
				maze[a][b] = data;
			}
		inputfile.close();
	}
	if (num == 2){
		ifstream inputfile;
		inputfile.open("floor_3.txt");
		if (inputfile.is_open())
			cout << "File opened successfully!" << endl;
		else{
			cout << "ERROR opening file!" << endl;
			exit(0);
		}
		inputfile >> levelheight;
		inputfile >> levelwidth;
		inputfile.ignore();
		
		height = levelheight;
		width = levelwidth;
		
		maze = new char*[height];
		for (int i = 0; i < height; i++)
			maze[i] = new char[width];
		
		for(int a = 0; a < height; a++)
			for (int b = 0; b < width; b++){
				data = inputfile.get();
				maze[a][b] = data;
			}
		inputfile.close();
	}
}


/*********************************************************************
 ** Function: oldswansymb
 ** Description: places a blank space at the current position of the swan
 ** Parameters: swanx, swany, char pre_symbol
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void game :: oldswansymb(int x, int y, char pre_symbol)
{  maze[y][x] = ' '; }


/*********************************************************************
 ** Function: update
 ** Description: updates the board with the players last symbol they had
 ** Parameters: playx,play, prev_symbol
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void game :: update(int x, int y, char prev_symbol)
{  maze[y][x] = prev_symbol;}



/*********************************************************************
 ** Function: updateswanmap
 ** Description: playes the swan tile 'B' to the updated move area
 ** Parameters: swanx, swany
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void game :: updateswanmap(int x, int y)
{ maze[y][x] = 'S';}


/*********************************************************************
 ** Function: updateplaymap
 ** Description: updates the map to the current player spot and fills with 'p'
 ** Parameters: tempx, tempy
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void game :: updateplaymap(int x, int y)
{ maze [y][x] = 'P'; }


/*********************************************************************
 ** Function: giveswanstart_X
 ** Description: returns the 'x' value of the starting spot of the swan
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int game :: giveswanstart_X(){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (maze[i][j] == 'S')
				return j;
	return 0;
}


/*********************************************************************
 ** Function: giveswanstart_Y
 ** Description: gives the 'y' position of the swan start
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int game :: giveswanstart_Y(){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (maze[i][j] == 'S')
				return i;
	return 0;
}


/*********************************************************************
 ** Function: giveplaystart_X
 ** Description: gives 'x' value of player starting spot
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int game :: giveplaystart_X(){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (maze[i][j] == 'E')
				return j;
	return -1;
}


/*********************************************************************
 ** Function: giveplaystart_Y
 ** Description: gives the starting 'y' value of the players starting spot
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int game :: giveplaystart_Y(){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (maze[i][j] == 'E')
				return i;
	return -2;
}


/*********************************************************************
 ** Function: findsymbol
 ** Description: gets the symbol of the next position on the map for any character
 ** Parameters: swanx or swany, or tempx and tempy
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
char game :: findsymbol(int x, int y){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (i == x && y == j)
				return maze[j][i];
	return 'f';
}

/*********************************************************************
 ** Function: cleaner
 ** Description: makes sure there are no duplicate 'P' tiles on map
 ** Parameters: tempx, tempy
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void game :: cleaner(int x, int y){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (maze[i][j] == 'P')
				if (i != y || j != x)
					maze[i][j] = ' ';
}

/*********************************************************************
 ** Function: swancleaner
 ** Description: makes sure there are no duplicate 'B' tiles on map
 ** Parameters: swanx,swany
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void game :: swancleaner(int x, int y){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (maze[i][j] == 'S')
				if (i != y || j != x)
					maze[i][j] = ' ';
}


/*********************************************************************
 ** Function: print
 ** Description: checks to see if the player is in any of the special spots
	 does the correct action if he is, and then prints the board,
	 or it loads the next level
 ** Parameters: tempx, tempy, player (object) p1, swanx, swany, level_arr
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
int game :: print(int tempx, int tempy, player &p1, int swanx, int swany, int &level_arr){
	
	if (p1.giveprev() == 'X'){
		cout<< "You beat the game!!!" << endl; //load next level in array
		cout << "You done son!!!" << endl;
		
		for (int i = 0; i < height; i++)
			delete []maze[i];
		delete []maze;
		exit(0);
	}
	else if	(p1.giveprev() == 'A'){
		if (p1.giveapple() < 30){
			cout << "You picked up an Apple!" << endl;
			p1.change_symb();
			p1.addapple();
			cout << "The player has " << (p1.giveapple() / 15) << "apple(s) now " << endl;
		}
		else
			cout << "Can't pick up no mo' apples!" << endl;
	}
	
	else if (p1.giveprev() == 'L'){
		cout << "You found the ladder, press 'U' to climb it!" << endl;
		char climb;
		cin >> climb;
		
		if (climb == 'U'){	//
			for (int i = 0; i < height; i++)
				delete []maze[i];
			delete []maze;
			
			level_arr++;
			p1.resetkey();
			p1.resetapp();
			openandget(level_arr);
			
			return 5;
		}
	}
	
	else if (p1.giveprev() == 'K'){
		if (p1.givekeys() < 3){
			cout << endl << "Golly gosh! You picked up a key!" << endl;
			p1.addkey();
			p1.change_symb();
			cout << "The player now has " << p1.givekeys() << " key(s) now!" << endl;
		}
		else
			cout << "You have too many keys playa!" << endl;
	}
	
	return 0; 
}

void game :: print(){
for (int i = 0; i < height; i++){
	for (int j = 0; j < width; j++)
		cout << maze[i][j];
		}
		cout << endl;
}

#endif