#include <stdio.h>
#include <stdint.h>


typedef struct {
	uint32_t rows, cols;
	float* data;
} Mat;



void printMat(Mat m){
	for (size_t i = 0; i < m.rows; ++i){
		for(size_t j = 0; j < m.cols ; ++j){
			printf("%f", m.data[i * m.cols + j]);

		}
		printf("\n");

	}

}


int main(void){

	Mat m = {
		.rows = 2, .cols = 2, .data = (float[]){1,2,3,4}
	};

	printMat(m);
	printf("Hello, World");
	return 0;
}
