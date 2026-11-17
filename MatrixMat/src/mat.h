#ifndef MAT_H
#define MAT_H
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	size_t rows, cols;
	float *data;
} Mat;

typedef struct {
	uint32_t rows, cols;
	float *data;
} Mat1;

typedef struct {
	float *data;
	uint32_t rows, cols;
} Mat2;


void matPrint(Mat1 m);
void matMultiply(Mat1 a, Mat1 b, Mat1 res);
#endif
