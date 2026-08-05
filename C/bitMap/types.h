#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef unsigned char int8;

typedef unsigned short int int16;

typedef unsigned int int32;

typedef int8 bitmap;





#define $c (char *)
#define $i (int)
#define $1 (int8 *)
#define $2 (int16 )
#define $4 (int32)

void zero(int8 *,  int16);
bitmap *mkbitmap(int16);
bool getbit(bitmap*, int16);
int main(void);

