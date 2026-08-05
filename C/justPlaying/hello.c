#include <stdio.h>



void my_strCat(char *buffer, char *a, char *b)
{
	sprintf(buffer, "%s%s", a, b);
}
int main(){

	for(int i =0, j = 10; j; j--,i++){
		printf("j = %d\n", j);
		printf("i= %d\n", i);

	}
	printf("\n");
	char result[5]={0};
	my_strCat(result, "hi", "ya");
	printf("\033[0;31mFAIL: %s\n\033[0m", "Hey");
	printf("result : %s\n", result);
}









