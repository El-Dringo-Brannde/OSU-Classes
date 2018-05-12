#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define maxlength 2048

void Get_Cmd(char cmd[maxlength], char *temparg, char *args[5], bool *pipeout, bool *Backgrounded);
void handle_status(int childExitMethod);
void handle_chdir(char *args[5]);

int main(int argc, const char * argv[]) {
	char cmd[maxlength];
	int childExitMethod = -5, i, sleepexit = 2;
	char *args[512], *temparg;
	pid_t spawnPid = 0, SleepersPID = 0;
	bool pipeout = false, Backgrounded = false;

	while (1){
		fflush(stdin); // Don't remove me!
		if (SleepersPID != 0){
			pid_t alive = waitpid(SleepersPID,&sleepexit,WNOHANG); //check to see if the sleeping child has died
			if (alive != 0){ //if the child has died or been killed
				printf("Oh nose! The child process died! Their PID was %d\n", alive);
				printf("The exit value of the process was %d\n",WEXITSTATUS(sleepexit));
				printf("The process was killed with signal #%d", WTERMSIG(sleepexit));
				SleepersPID = 0;
			}
		}
		bool builtins = false;
		Get_Cmd(cmd, temparg, args, &pipeout, &Backgrounded);
		if (strcmp(args[0],"exit") == 0){exit(0);}
		else if (strcmp(args[0], "cd") == 0){ handle_chdir(args); builtins = true;}
		else if (strcmp(args[0],"status") == 0){
			handle_status(childExitMethod);
			builtins = true;
		}
		//^ Built in functions
		if (builtins == false){
		spawnPid = fork();
		i = 0;
		switch(spawnPid){
			case -1:{
				printf("The child has failed.. You \n");
				exit(1);
			}
			case 0:{
				if (pipeout == true){
					int junk = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
					dup2(junk,1); //redirects stdout to file
					close(junk);
					fflush(stdout);// Don't remove me!
					execlp(args[0], args[0], NULL);
					exit(2);
				}
				else if ((strcmp(args[0],"sleep") == 0) && (Backgrounded == true)){
					fflush(stdout);// Don't remove me!
					printf("\nI'm running in the background! I have the PID %d\n", getpid() );
					fflush(stdout);// Don't remove me!
					execlp(args[0], args[0],args[1], NULL);
				}
				else {
					fflush(stdout);// Don't remove me!
					execvp(args[0],args);
					perror("CHILD: Exec failure!");
					exit(2);
				}
			}
			default:{
				fflush(stdout); // Don't remove me!
				if (Backgrounded == true){
					waitpid(spawnPid,&sleepexit,WNOHANG); //Don't wait unless the child has died
					SleepersPID = spawnPid;
					Backgrounded = false;
				 break;
				}
				else{
					fflush(stdout); // Don't remove me!
					waitpid(spawnPid,&childExitMethod,0); // wait for the child
					fflush(stdout); // Don't remove me!
					pipeout = false;
					Backgrounded = false;
				}
			}
		}
	}
		for ( i = 0; i < 512; i++)
			free(args[i]);
	}
	return 0;
}

void Get_Cmd(char cmd[maxlength], char *temparg, char *args[5], bool *pipeout, bool *Backgrounded){
	fflush(stdin); // Don't remove me!
	fflush(stdout); // Don't remove me!
	printf("\n: ");
	int i = 0;

	for (i = 0; i < 512; i++)
		args[i] = malloc(100);

	scanf(" %[^\n]s", cmd);
	int size = strlen(cmd), j, argcount = 0;

	for (i = 0; i <size -1 ; i++){
		if (cmd[i] == ' ') //find command arguements by spaces
			argcount++;
		else if (cmd[i] == '>') //redirect to file
			*pipeout = true;
	}
	temparg = strtok(cmd," "); // get commands by space
	i = 0, j = 0;
	while (temparg != NULL){
		while (temparg[j] != '\0'){
			if (temparg[j] == '\n') //if three is a newline character flip it to NULL
				temparg[j] = '\0';
			else if (temparg[j] == '&') //signal that a background process needs to be ran
				*Backgrounded = true;
			j++;
		}
		if (strcmp(temparg,">") != 0 && strcmp(temparg,"<") != 0){
			strcpy(args[i],temparg); //copy if the character is not a redirect
			i++;
		}
		temparg = strtok(NULL, " "); // move onto next word
		j = 0;
	}
	args[i] = '\0';
}
void handle_chdir(char *args[5]){
	fflush(stdout);
	int result = 0;
	if (!args[1]) //If it is just '$cd'
		chdir(getenv("HOME"));
	else{
		result = chdir(args[1]); // change directory to second arguement
	}
}
void handle_status(int childExitMethod){ printf("The status of the child was: %d \n", WEXITSTATUS(childExitMethod)); }
