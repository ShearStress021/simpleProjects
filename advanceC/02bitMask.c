#include <stdio.h> 

typedef enum {
	FLAG_A  = (1 << 0 ),
	FLAG_B  = (1 << 1 ),
	FLAG_C  = (1 << 2 )

} t_flags;


int func(int x, t_flags flags){
	if(flags & FLAG_A) x += x;
	if(flags & FLAG_B) x *= x;
	if(flags & FLAG_C) x = ~x;
	return x;
}


int main(){
	printf("my result %d\n",func(1234, 1));
	printf("my result %d\n",func(1234, FLAG_A | FLAG_B ));
	printf("my result %d\n",func(1234, FLAG_C));
	return 0;
}
