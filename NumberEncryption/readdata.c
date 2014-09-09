/*
FUNCTION OVERVIEW
This function reads in the data that is to be processed.

DATA DICTIONARY:

unsigned int:
'*number' : is a pointer to the number to be encrypted
'*pos1' : is a pointer to the position being swapped
'*pos2' : is a pointer to the position being swapped with

*/

#include "headext.h"


void readData(unsigned int *number, int *pos1, int *pos2)
{

	printf("\nPlease enter the 4 digit hexadecimal number : ");
	scanf("%x",number);

	do
	{
		printf("\nPlease enter the the bytes to be swapped (0-3)\n");
		printf("First Byte: ");
		scanf("%i",pos1);
		printf("Second Byte: ");
		scanf("%i",pos2);
	}
	
	//After reading the data it calls on checkPos to verify if its
	//correct

	while(checkPos(*pos1, *pos2));
}
