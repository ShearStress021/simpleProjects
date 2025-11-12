#ifndef PASSWORD_H
#define PASSWORD_H


void init_random();
int generate_random(int min, int max);
void generate_password(char* memory, int length);

#endif
