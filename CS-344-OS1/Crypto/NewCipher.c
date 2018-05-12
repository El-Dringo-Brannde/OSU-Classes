#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

char decrypt_me(char letter, int key){
	letter = (int)letter - key;
	
	while((int)letter < 65 || (int)letter > 90 ){
		if ((int)letter == 32)
			break;
		if ((int)letter > 90) // If value goes passed bounds loop back.
			letter = (int)letter + key;
		if ((int)letter < 65)
			letter = (int)letter - key;
	}
	return letter;
}

char encrypt_me(char letter, int key){
		//letter = (int)letter + convertedToNumber;
	letter = (int)letter + key;
	while((int)letter < 65 || (int)letter > 90){
	if (letter == ' ')
		break;
	if ((int)letter > 90) // If value goes passed bounds loop back.
		letter = (int)letter - key;
	if ((int)letter < 65)
		letter = (int)letter + key;
	}
	return letter;
}




int main(){
		//char mixer[27] = {'A','Z','U','D',' ','F','Y','M','P','J'};
	char key[70005], secret_message[100],norm[100];
	FILE *fp;
	fp = fopen("key70000","r+");
	fgets(key,70001,fp);
	time_t t;
	srand((unsigned)time(&t));
	char word[100] = "THE RED GOOSE FLIES AT MIDNIGHT \n";
	
	int i = 0;
	while (word[i] != '\n'){
		int random = key[i] - 48; //converts key to number
		char encrypted_letter = encrypt_me(word[i],random);
		secret_message[i] = encrypted_letter;
		fflush(stdout);
		i++;
	}
	secret_message[i] = '\n';
	printf("%s",secret_message);
	i = 0;
	while (secret_message[i] != '\n'){
		int random = key[i] - 48;
		char decrypted_letter = decrypt_me(secret_message[i],random);
		norm[i] = decrypted_letter;
		i++;
	}
	
	
	return 0;
}
