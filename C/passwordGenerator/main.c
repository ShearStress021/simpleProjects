#include <stdio.h>
#include <stdlib.h>

const char *random_state = "/dev/random";

void generate_password(char *memory , int length){
	FILE *file = fopen(random_state, "r");
	
	int c = fgetc(file);

	if (c == EOF){
		printf("%s file could not be read", random_state);

		exit(-1);
	}

	int r;
	for (int i =0; i < length; i ++){
		int r = fgetc(file);
		r = (r % (126 - 33)) + 33;
		*(memory + i) = r;
	}

	
	 
}
int main(int argc, const char* argv[]){
	if (argc != 2){
		printf("Usage not less than allowed bytes\n");
		return 0;
	}
	int length = atoi(argv[1]);
	printf("Generate password with of %d bytes\n", length);


	char *password = (char *) malloc(length);

	generate_password(password, length);
	printf("Generated password: \n%s\n", password);

	free(password);
	return 0;
}
