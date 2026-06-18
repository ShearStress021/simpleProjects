#include <stdio.h>
#include "commons/include/apue.h"


int main(int argc , char *argv[]){

	if( argc != 2 ){
		err_quit("Usage: ls directory_name ");
	}
	printf("Hello, World\n");
	return 0;
}
