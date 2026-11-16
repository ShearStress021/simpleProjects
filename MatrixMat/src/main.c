#include <stdio.h>
#include "mat.h"
#include <stdint.h>




int main(void){


	Mat1 m = {
		.rows = 2, .cols = 2, 
		.data = (float[]){1,2,3,4},

	};	
	Mat1 a = {
		.rows = 2, .cols = 2, 
		.data = (float[]){2,3,4,5},

	};

	Mat1 b = {
		.rows = 2, .cols = 2, 
		.data = (float[]){0},

	};
	matPrint(b);

	matMultiply(m, a, b);
	printf("%zu\n",b.rows * b.cols *sizeof *b.data);






	//matPrint(m);
	//matPrint(a);
	matPrint(b);
	return 0;
}



