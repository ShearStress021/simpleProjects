#ifndef UTILS
#define UTILS
#include "../src/mat.h"
#include <stdbool.h>








static inline bool checkEqual(Mat1 a, Mat1 b){

	if(a.rows != b.rows){
		printf("rows mismatch (a: %u != b: %u)\n",a.rows, b.rows );
		return false;
	}
	if(a.cols != b.cols){
		printf("cols mismatch (a: %u != b: %u)\n",a.rows, b.rows );
		return false;
	}

	for(size_t i = 0; i < a.rows * a.cols; i++){
		if(a.data[i] != b.data[i]){
			printf("a:\n");
			printf("data mismatch (a: %f != b: %f)\n",a.data[i], b.data[i]);
			return false;

		}
	}

	return true;
}
#endif

