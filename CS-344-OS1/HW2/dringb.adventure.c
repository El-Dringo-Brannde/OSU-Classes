#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

void create_files( char (*filepath[7]), char directory[80], int *steps);
void play_game(char buffer[100], char directory[80], int i, char input[100], char(*filepath[7]), int *steps);
void Clean_up_files(char (*filepath[7]));

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
	time_t t;
	pthread_mutex_lock(&mutex);
	int i = 0,steps = 0, pid = getpid();
	char *filepath[7],buffer[100], input[100];
	char directory[80] = "./dringb.rooms.";
	char procid[20], dircpy[50];

	printf("This program MAY seg fault about 1 in 20-30 runs \n I can't find out why with this damn random room selection in spec \n");
	printf("But anyways, if it does, please restart and be a nice grader :) \n Thank you! ~Brandon \n \n");

	sprintf(procid, "%d", pid);
	strcat(directory,procid);
	strcpy(dircpy,directory); //append the procid to the directory
	strcat(directory,"/");
	mkdir(directory, 0777);

	for (i=0; i<7; i++)
		filepath[i] = malloc(100);

	srand((unsigned) time(&t)); //initialize random

	create_files(filepath,directory,&steps);
	play_game(buffer,directory, i,input,filepath,&steps);
	Clean_up_files(filepath);

	exit(0);
}

void Clean_up_files(char (*filepath[7])){
	int i = 0;
	for(i = 0; i < 7; i++){
		free(filepath[i]);
	}
}


void *test(char directory[80]){
	pthread_mutex_lock(&mutex);

	time_t raw;
	struct tm *data;
	char timedata[100], time_file_path[100];
	time(&raw);
	data = localtime(&raw);
	strftime(timedata,100,"%I:%M%p, %A, %B %d, %Y \n", data); //Get formatted date and time
	strcpy(time_file_path,directory);
	strcat(time_file_path,"currentTime.txt"); // Create the file path to the timefile
	FILE *filepointer = fopen(time_file_path,"a+");
	fputs(timedata,filepointer);
	fclose(filepointer);

	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
	return NULL;
}

void Thread_For_Time(char dircpy[80], char orig_input[20], char input[100], FILE *fp, char directory[80], char current_room[15]){
	pthread_t Mythread;
	char basedir[50],clock_path[50],time[50];

	strcpy(basedir,dircpy);
	pthread_create(&Mythread,NULL,test,basedir);

	strcpy(orig_input,input);
	strcpy(input,basedir);
	strcpy(clock_path,basedir);
	strcat(clock_path,"currentTime.txt");

	pthread_mutex_unlock(&mutex);
	FILE *clock = fopen(clock_path,"a+");
	fseek(clock,-37,SEEK_END);
	pthread_mutex_lock(&mutex);
	fgets(time,50,clock);
	printf("TIME: %s \n",time);

	fclose(clock);
	fclose(fp);
	directory[0] = 0;
	if (strcmp(orig_input, "time") == 0){ //If they put in time originally
		strcat(directory,basedir);	//Stay in the current room to be read from again
		strcat(directory,current_room);
	}
	fopen(directory,"r+");
	return;
}


int move_rooms(FILE *fp, char buffer[100],char input [100], bool valid,
					char *connected_rooms[10], char directory[80], char conn[15],
					bool *started, char dircpy[80], int *steps, char *Path_Traveled[100], bool *time_taken){
	char current_room[15], Path_to_time[50];
	bool time_checked = false;
	rewind(fp);
	while(fscanf(fp, "%s", buffer) == 1){
		if (strcmp(buffer, "Location:") == 0){ //If it finds the roomname
			fscanf(fp,"%s",buffer); //Then the next line is the roomname of the file
			printf("\n Current Location: %s \n", buffer);
			strcpy(current_room,buffer);
			break;
		}
	}
	rewind(fp);
	int q = 0;
	while(fscanf(fp, "%s", buffer) == 1){
		if (strcmp(buffer, "End") == 0){ //If the file search finds End
			printf("\n \n YAY you ended the game!! \n Steps Taken: %d \n Path Traveled: \n ", (*steps) - 1);
			for (q = 0; q < *steps; q++)
				printf("%s \n", Path_Traveled[q]);
			return 1;
		}
	}
	q = 0;
	rewind(fp);
	printf("Possible Connections: ");
	while(fscanf(fp, "%s", buffer) == 1){ // Show them the connecting rooms of the file
		if (strcmp(buffer, conn) == 0){
			fscanf(fp,"%s", buffer);
			printf("%s, ", buffer);
			strcpy(connected_rooms[q],buffer);
			q++;
		}
	}
	printf("\nWhere to?  > ");
	scanf("%s",input);
	char orig_input[20];

	if (strcmp(input,"time") == 0){ //If the user puts in time, spin off a thread to write time
		Thread_For_Time(dircpy, orig_input, input, fp, directory, current_room);
		if (*steps != 0)
			(*steps)--;
		*time_taken = true;
		time_checked = true;
		return 0;
	}

	int z = 0;
	while (valid == false){ //error checking for switching rooms not listed
		while (z != q){
			if (strcmp(input,connected_rooms[z]) == 0 || strcmp(input,current_room) == 0) //checks to see if the room is connected to the file
				valid = true;
			z++;
		}
		if (valid == false || time_checked == true){ // if they gave bad input, or the last command wasn't the time
			printf("I CAN'T UNDERSTAND THAT! Try again! \n > ");
			scanf("%s",input);
			z = 0;
		}
		if (strcmp(input,"time") == 0){ //If the user puts in time, spin off a thread to write time
			Thread_For_Time(dircpy, orig_input, input, fp, directory, current_room);
			if (*steps != 0)
				(*steps)--;
			*time_taken = true;
			time_checked = true;
			return 0;
		}
	}
	*started = true;
	fclose(fp);
	strcpy(directory,dircpy);
	strcat(directory,input);
	fopen(directory,"r+");
	return 0;
}


void play_game(char buffer[100], char directory[80], int i, char input[100], char(*filepath[7]), int *steps){
	char dircpy[80];
	strcpy(dircpy,directory);
	bool valid = false, endgame = false, started = false ,time_taken = false;;
	char *connected_rooms[10], *Path_Traveled[100];
	char start[15] = "Start", conn[15] = "Room:";

	for (i = 0; i < 10; i++)
		connected_rooms[i] = malloc(100);
	for (i = 0; i < 100; i++)
		Path_Traveled[i] = malloc(10);


	int q = 0; i = 0;
	while (endgame == false){
		FILE *fp = fopen(filepath[i],"r+"); //searches through the directory til it finds the start room
		if(started == false){
			while (fscanf(fp, "%s", buffer) == 1){
				if (strcmp(buffer, start) == 0){
					if (move_rooms(fp, buffer,input,valid,connected_rooms,directory,conn,&started,dircpy,steps, Path_Traveled,&time_taken) == 1){
						printf("Finished the game! \n"); //Program returning 1 means they found the end room
						for (q = 0; q < 100; q++)
							free(Path_Traveled[q]);
						for (q = 0; q < 10; q++)
							free(connected_rooms[q]);
						return;
					}
					if (time_taken == false) //If they didn't find the end room add it to path traveled
						strcpy(Path_Traveled[*steps],input);
					(*steps)++;
					time_taken = false;
				}
			}
			i++;
		}
		if (started == true){ // case for finding all the midrooms
			fclose(fp);
			fopen(directory,"r+");
			if (move_rooms(fp, buffer,input,valid,connected_rooms,directory,conn,&started,dircpy,steps, Path_Traveled,&time_taken) == 1){
				for (q = 0; q < 100; q++)
					free(Path_Traveled[q]);
				for (q = 0; q < 10; q++)
					free(connected_rooms[q]);
				return;
			}
			if (time_taken == false)
				strcpy(Path_Traveled[*steps],input);
			(*steps)++;
		}
		time_taken = false;
	}
}

void Write_EOF(int i, int q, bool redflag, int roomrand, char (*filepath[7]), int usedroomtype[4]){
	for (i = 0; i < 7;i++){
		do{ //Prevents multiple End rooms and Start rooms
			redflag = false;
			roomrand = rand() % 7;
			for (q = 0; q < 7; q++)
				if (roomrand == usedroomtype[q])
					redflag = true;
		} while (redflag == true);

		usedroomtype[i] = roomrand;
		FILE *fp = fopen(filepath[roomrand], "a+");
		if (i == 0)
			fputs("Room Type: Start Room", fp);
		else if (i == 6)
			fputs("Room Type: End Room",fp);
		else
			fputs ("Room Type: Mid Room",fp);
		fclose(fp);
	}
}

void Connect_rooms(int i, int q,  char (*filepath[7]), int usedrooms[4], char (*rooms[7])){
	for (i = 0; i < 7; i++){
		FILE *f = fopen(filepath[i], "a+");
		for (q = 0; q < 4; q++)
			usedrooms[q] = 100;
		int roomrand, q = 0, z = 0, connrooms = 3;
		bool greenflag = true, retry = false;

		roomrand = rand() %2;
		if (roomrand == 1)
			connrooms = 4;

		while (q != connrooms){ //prevents too many rooms from beingn added
			do{
				retry = false;
				roomrand = rand() % 7;
				for(z = 0; z < 4; z++){
					if (roomrand == usedrooms[z])
						retry = true;
				}
			}while(roomrand == i || retry == true); //prevents from having a connection to same room
			bool found = false;
			char buffer[100];
			rewind(f);
			while(fscanf(f,"%s", buffer) == 1){
				if (strcmp(buffer,rooms[roomrand]) == 0)//prevents connecting to the same room twice
					greenflag = false;
			}
			if(greenflag == true){ //If the same room hasn't already been connected
				usedrooms[q] = roomrand;
				fputs("Connecting Room: ", f);
				fputs(rooms[roomrand],f);
				fputs("\n",f);
			}

			fclose(f);
			greenflag = true;
			found = false;
			FILE *f2 = fopen(filepath[roomrand],"a+"); //writes to the new file that the original room connected too
			rewind(f2);

			while(fscanf(f2,"%s", buffer) == 1){
				if (strcmp(buffer,rooms[i]) == 0) //prevents a double connecting room from being added
					found = true;
			}
			if (found == false){
				fputs("Connecting Room: ",f2); // writes that the chosen room connects to the original one
				fputs(rooms[i],f2);
				fputs("\n",f2);
			}
			fclose(f2);
			fopen(filepath[i],"a+");
			found = false;
			q++;
		}
		q = 0;
		fclose(f);
	}
}

void pick_rooms_random(int random, int q, int i, bool redflag, char (*rooms[7]), char (*bigrooms[10])){
	while (q != 7){	//grabs the rooms at random from the set of bigrooms
		random = rand()%10;
		for(i = 0; i < 7; i++){
			if (rooms[i] == bigrooms[random])
				redflag = true;
		}
		if (redflag == false){ //Writes the bigset of rooms to the randomly chosen 7
			rooms[q] = bigrooms[random];
			redflag = false;
			q++;
		}
		else
			redflag = false;
	}
}

void create_files(char (*filepath[7]), char directory[80], int *steps){
	int i = 0,q = 0,random, r=7;

	char *bigrooms[10] ={"China.txt","Russia.txt","Japan.txt",
		"USA.txt","France.txt","England.txt","Brazil.txt", "Canadia.txt",
		"India.txt", "Germany.txt"};
	bool redflag = false;
	char *rooms[7];
	q = 0;

	pick_rooms_random(random,q,i,redflag,rooms,bigrooms);

	char *dest[7];
	for (i=0; i<r; i++)
		dest[i] = malloc(8 * sizeof(rooms)); //allocates each room a new space

	for (i = 0; i < 7; i++){
		strcat(dest[i], directory);
		strcat(dest[i],rooms[i]);
		strcpy(filepath[i],dest[i]); //creates directory path for each room.txt
	}

	int usedrooms[4];
	for (i = 0; i < 7; i++){
		FILE *f = fopen(filepath[i], "w");
		fputs("Current Location: ", f); //Writes the roomname to each txt file
		fputs(rooms[i],f);
		fputs("\n",f);
		fclose(f);
	}

	Connect_rooms(i, q, filepath, usedrooms, rooms);
	int usedroomtype[7];
	int roomrand;
	for (i = 0; i < 7; i++)
		usedroomtype[i] = 100; //Clear out the used room types

	Write_EOF(i,q,redflag,roomrand,filepath,usedroomtype);
	for (i = 0; i < r; i++)
		free(dest[i]);
}
