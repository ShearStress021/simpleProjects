#include <stdio.h>
#include "mat.h"
#include <string.h>




void matMultiply(Mat1 a, Mat1 b, Mat1 res){
//	memset(res.data, 0, res.cols * res.rows * sizeof *res.data);
	for(size_t i = 0; i < res.rows; ++i){
		for(size_t j= 0; j < res.cols; ++j){
			uint32_t c_ix = i * res.cols + j;
			res.data[c_ix] = 0.f;
			for(size_t k= 0; k < b.cols; ++k)
				res.data[c_ix] += a.data[i * a.cols + k] * b.data[k * b.cols+ j];
		}
	}
}


void matPrint(Mat1 m){
	for(size_t i = 0; i < m.rows; ++i){
		for(size_t j=0; j < m.cols; ++j){
			printf(" %f", m.data[i * m.cols + j]);
		}
		printf("\n");
	}

}

