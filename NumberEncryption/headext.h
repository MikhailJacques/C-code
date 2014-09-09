//This header contains external defination of functions.
//It is included in all functions except main


#include <stdio.h>

extern int checkPos(int pos1, int pos2);
extern void encrypt(unsigned int number, int pos1, int pos2);
extern void print(unsigned int number, unsigned int encrypted);
extern void readData(unsigned int *number, int *pos1, int *pos2);
