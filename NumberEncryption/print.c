/*
FUNCTION OVERVIEW
This function simply prints data to the screen

DATA DICTIONARY:

unsigned int:

'number' is the number the was entered by the user
'encrypted' is the number encrypted by the program
*/



#include "headext.h"

void print(unsigned int number, unsigned int encrypted)
{
	printf("\nOrigional Number : %x\n",number);
	printf("\nEncrypted Number : %x\n",encrypted);
}
