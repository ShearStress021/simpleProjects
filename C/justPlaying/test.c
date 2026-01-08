#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hello.c"


int failed = 0;
#define TEST(name) void name()
#define RUN_TEST(name) printf("runnging %s\n", #name); name()
#define ASSERT(expr) if (!(expr)){\
	failed = 1;\
	printf("Failed: %s\n", #expr);\
}else { \
	printf("Passed: %s\n", #expr);\
}




TEST(test_add){
	ASSERT(add(1,3) == 4);
	ASSERT(add(4, 4) == 8);
	ASSERT(add(3,-4) == -1);

}




