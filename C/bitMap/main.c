
#include "types.h"


bool getbit(bitmap *bmp, int16 bitNo){
	int16 byteNu;
	int8 byte, bitPos;

	bool bit;


	byteNu = (bitNo / 8);
	bitPos = (bitNo % 8);

	byte = $1 bitmap[byteNu];


	return 0;
}


bitmap *mkbitmap(int16 bits){

	int16 bytes;

	bitmap *p;

	bytes = (bits/ 8) + 1;

	p = malloc($i bytes);

	zero(p, $2 bytes);

	return p;

}


void zero(int8 *dst,  int16 size){

	int8 *p;
	int16 n;

	for(p=dst, n = size; n; n--, p++){
		*p = 0;
	
	return;
		
	}

}



int main(){
	return 0;
}
