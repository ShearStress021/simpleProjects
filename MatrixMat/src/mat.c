#include <stdio.h>
#include "mat.h"




void matMultiply(Mat* a, Mat *b, Mat* res){
	for(size_t i = 0; i < a->rows; ++i){
		for(size_t j = 0; j < b->rows; ++j){
			for(size_t k = 0; k < res->rows; ++k){
			}
		}
	}

}
void matPrint(Mat m){
	for(size_t i = 0; i < m.rows; ++i){
		for(size_t j=0; j < m.cols; ++j){
			printf(" %f", m.data[i * m.cols + j]);
		}
		printf("\n");
	}

}

