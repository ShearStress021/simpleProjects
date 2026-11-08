#include <stdio.h>
#include "mat.h"
#include <stdint.h>




int main(void){


	Mat m = {
		.rows = 2, .cols = 2, 
		.data = (float[]){1,2,3,4},

	};	
	Mat a = {
		.rows = 2, .cols = 2, 
		.data = (float[]){5,4,6,8},

	};

	Mat b = {
		.rows = 2, .cols = 2, 
		.data = (float[]){0},

	};



	for(size_t i = 0; i < m.rows; ++i){
		for(size_t k = 0; k < m.rows; ++k){
			for(size_t j = 0; j < a.cols; ++j){
				printf("%f\n", a.data[i * a.cols + k]);
			}
		}
	}


	//matPrint(m);
	//matPrint(a);
	//matPrint(b);
	return 0;
}



