//#include "../src/mat.h"
#include "utils.h"
#include <assert.h>



void testMatMulSqr(void){
	Mat1 a = {
		.rows = 2, .cols = 2, .data=(float[]){1,2,3,4}
	};

	Mat1 b = {
		.rows = 2, .cols = 2, .data=(float[]){2,3,4,5}
	};

	Mat1 out = {
		.rows = 2, .cols = 2, .data=(float[4]){0}
	};

	Mat1 exp = {
		.rows = 2, .cols = 2, .data = (float[4]){10,13,22,29}
	};

	matMultiply(a, b, out);
	matPrint(out);

	assert(checkEqual(out, exp));
}

int main(){
	testMatMulSqr();
	return 0;
}
