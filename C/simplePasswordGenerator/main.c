#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "password.h"


int main(int argc, const char* argv[]){
	init_random();
	if (argc != 2){
		printf("Usage not less than allowed bytes\n");
		return 0;
	}
	int length = atoi(argv[1]);

	char * password = (char *)malloc(length);
	

	generate_password(password, length);
	
	printf("Generated password is: %s\n", password);
	
	free(password);

	return 0;
}

void init_random(){
	srand((unsigned int) time(NULL));
}

int generate_random(int min, int max){
	int count = max - min + 1;

	int limit = RAND_MAX - (RAND_MAX % count);

	int r;

	do {
		r = rand();
	} while(r >= limit);

	return min + (r % count);
	
}

void generate_password(char * memory, int length){

	
	const char* uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char* lowercase = "abcdefghmijklmnopqrstuvwxyz";
	const char* numbers = "0123456789";
	const char* symbols = "!@#$%^&*_";

	char* alphabets = malloc(strlen(uppercase) + strlen(lowercase) + strlen(numbers) + strlen(symbols) + 1);
	

	strcat(alphabets, uppercase);
	strcat(alphabets,lowercase);
	strcat(alphabets,numbers);
	strcat(alphabets, symbols);
	
	int n = strlen(alphabets);
	for(int i = 0; i < length; i++){
		int r = generate_random(0, n);
		*(memory + i) = alphabets[r];
		
	}

	free(alphabets);
	
}



