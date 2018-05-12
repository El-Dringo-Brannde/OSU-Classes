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

int get_file_size(FILE * fp, char CipherFile[100]){
  fp = fopen(CipherFile,"r+");
  fseek(fp,0,SEEK_END);
  int file_size = ftell(fp);
  fclose(fp);
  return file_size;
}

char *get_file_contents(FILE *fp, char Message[70002], char CipherFile[100],int SizeofFile){
    fp = fopen(CipherFile,"r+");
    fgets(Message,SizeofFile + 1,fp);
    fclose(fp);
    return Message;
}

int main(int argc, char *argv[]){
  struct sockaddr_in SERVER;
  struct hostent* SERVERInfo;
  int OnSocket, PortNumber, CharsWritten, CharsRead,SizeofFile;
  char Message[70002], Key[70002], CipherFile[100],KeyFile[100],decrypted[70002],Empty[10];
  FILE *fp;
  strcpy(CipherFile,argv[1]);
  strcpy(KeyFile,argv[2]);
  SizeofFile = get_file_size(fp,CipherFile);
  strcpy(Message,get_file_contents(fp,Message,CipherFile,SizeofFile));

  int SizeofKey = get_file_size(fp,KeyFile);
  strcpy(Key,get_file_contents(fp,Key,KeyFile,SizeofKey));

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

  CharsWritten = send(OnSocket, Message, 70001 , 0); //Don't touch me :)

  recv(OnSocket,Empty,9,0);
  CharsWritten = send(OnSocket, Key,70001,0);

  CharsWritten = recv(OnSocket,decrypted,70001,0);

  printf("%s", decrypted);
  return 0;
}
