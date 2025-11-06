#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "password.h"

#define LENGTH 12
#define LEN_PASS LENGTH / 4


int main(){
	init_random();
	char arr[LENGTH]; 
	
	const char *uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char *lowercase_letters = "abcdefghijklmnopqrstuvwxyz";
	const char *number = "0123456789";
	const char *symbols = "!@#$*_";
	

	for(int i = 0; i < LENGTH; i++){
		arr[i] = uppercase_letters[generate_random(0, 25)];
	}



	printf("digit is %d  \n",LEN_PASS);
	printf("Hello, World\n");
	puts(arr);

	return 0;
}


int generate_random(int min, int max){

	int count = max - min + 1;
	int limit = RAND_MAX -(RAND_MAX % count);

	int r;
	do {
		r = rand();
	}while(r >= limit);
	return min + (r % count);
}

void init_random(){
	srand((unsigned int)time(NULL));
}
