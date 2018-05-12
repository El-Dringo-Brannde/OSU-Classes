#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
  perror(msg);
  exit(1);
 } // Error function used for reporting issues

int get_file_size(FILE * fp, char TextFile[100]){
  fp = fopen(TextFile,"r+");
  fseek(fp,0,SEEK_END);
  int file_size = ftell(fp);
  fclose(fp);
  return file_size;
}

char *get_file_contents(FILE *fp, char Message[70002], char TextFile[100],int SizeofFile){
    fp = fopen(TextFile,"r+");
    fgets(Message,SizeofFile + 2,fp);
    fclose(fp);
    return Message;
}

void ValidateDoc(FILE *fp, char Message[70002],long SizeofFile){
  int i;
  for (i = 2; i < SizeofFile - 1; i++){
		int current = (int)Message[i];
		if (current > 90 || (current < 65 && current != 32)) // Makes sure that the input is just caps A-Z
			error("Give me good input!!\n");
	}
}

int main(int argc, char *argv[]){
  struct sockaddr_in SERVER;
  struct hostent* SERVERInfo;
  int OnSocket, PortNumber, CharsWritten, CharsRead;
  long SizeofFile;
  char Message[70002], Key[70002], TextFile[100],KeyFile[100],encrypted[70002],Empty[10];
  FILE *fp;
  strcpy(TextFile,argv[1]);
  strcpy(KeyFile,argv[2]);
  SizeofFile = get_file_size(fp,TextFile);
  strcpy(Message,get_file_contents(fp,Message,TextFile,SizeofFile));
  int SizeofKey = get_file_size(fp,KeyFile);
  strcpy(Key,get_file_contents(fp,Key,KeyFile,SizeofKey));
  ValidateDoc(fp,Message,SizeofFile);

  if (SizeofFile > SizeofKey)
    error("Give me a longer key!!! \n");

  if (argc < 4)
    error("Listen dumb dumb.. \n");

  memset((char *) &SERVER, '\0',sizeof(SERVER));
  PortNumber = atoi(argv[3]);
  SERVER.sin_family = AF_INET;
  SERVER.sin_port = htons(PortNumber);
  SERVERInfo = gethostbyname("localhost");
  memcpy((char*)SERVERInfo->h_addr, (char*)&SERVER.sin_addr.s_addr, SERVERInfo->h_length);

  OnSocket = socket(AF_INET,SOCK_STREAM,0); //Don't touch me :)
  if (OnSocket < 0)
    error("Could not open socket :( \n");

  if (connect(OnSocket, (struct sockaddr*)&SERVER, sizeof(SERVER)) < 0) //Don't touch me :)
    error("Could not connect :( \n");

  CharsWritten = send(OnSocket, Message, 70001, 0); //Don't touch me :)
  recv(OnSocket,Empty,10,0);

  CharsWritten = send(OnSocket, Key,70001,0);

  recv(OnSocket,encrypted,70001,0);
  printf("%s", encrypted); // Don't delete this

  return 0;
}
