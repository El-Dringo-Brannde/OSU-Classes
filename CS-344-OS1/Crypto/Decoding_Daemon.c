#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(const char *msg) {
  perror(msg);
  exit(1);
}

char decrypt_me(char letter, int key){
	letter = (int)letter - key;

	while((int)letter < 65 || (int)letter > 90 ){
		if ((int)letter == 32 || key == 0)
			break;
		if ((int)letter > 90) // If value goes passed bounds loop back.
			letter = (int)letter + key;
		if ((int)letter < 65)
			letter = (int)letter - key;
	}
	return letter;
}

int main(int argc, char * argv[]){
  char message[70002], Key[70002],encrypted[70002];
  int ListenOnSocket, GoodConnection, PortNumber, CharLengthRead;
  struct sockaddr_in Server,Client;
  if (argc < 2){
    printf("Dammit, why can't you listen to directions \n");
    exit(1);
  }
  memset((char *)&Server, '\0', sizeof(Server));
  PortNumber = atoi(argv[1]);
  //fill Server struct
  Server.sin_family = AF_INET;
  Server.sin_port = htons(PortNumber);
  Server.sin_addr.s_addr = INADDR_ANY;

  ListenOnSocket = socket(AF_INET, SOCK_STREAM, 0); //Don't touch me :)
  if (ListenOnSocket < 0)
    error("Oh nose, socket failure \n");
  if (bind(ListenOnSocket, (struct sockaddr *) &Server, sizeof(Server)) < 0) //Don't touch me :)
    error("Could not bind :( \n");
  listen(ListenOnSocket,5); //handle 5 connections

  while(1){
    pid_t PID = 5;
    int ExitMethod = -5;
    int SizeofClient = sizeof(Client);
    GoodConnection = accept(ListenOnSocket,(struct sockaddr *) &Client, &SizeofClient); //Don't touch me :)
    sleep(0.75);
    PID = fork();
    if (PID == 0){
      if (GoodConnection < 0)
        error("Could not accept client");

      CharLengthRead = recv(GoodConnection, encrypted, 70001, 0);
      if (CharLengthRead < 0) error("ERROR reading from socket");
    //  printf("SERVER: I received this from the client: \"%s\"\n", encrypted);
      send(GoodConnection,"good",9,0);

      CharLengthRead = recv(GoodConnection, Key, 70001, 0);
      if (CharLengthRead < 0) error("ERROR reading from socket");
      int i = 0;
    	while (encrypted[i] != '\n'){
        int random = Key[i] - 48;
    		char letter = decrypt_me(encrypted[i],random/3);
    		message[i] = letter;
    		i++;
    	}
      message[i] = '\n';
      CharLengthRead = send(GoodConnection, message,70001,0);
      close(GoodConnection);
      break;
    }
    else
      waitpid(PID,&ExitMethod,0);
   }

    //close(GoodConnection); //Don't delete these they close the sockets and connections
    close(ListenOnSocket);
  return 0;
}
