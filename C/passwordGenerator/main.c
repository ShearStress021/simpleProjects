#include <stdio.h>
#include <stdlib.h>

void generate_password(char *memory , int length){
	 
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
