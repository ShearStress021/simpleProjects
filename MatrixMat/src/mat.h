#ifndef MAT_H
#define MAT_H
#include <stdint.h>

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


void matPrint(Mat m);
void matMultiply(Mat* a, Mat *b, Mat *res);
#endif
