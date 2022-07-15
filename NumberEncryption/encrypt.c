/*
FUNCTION OVERVIEW
This function is essentially the heart of this program. After verification
and input is done by other functions this function performs encryption on
the number

DATA DICTIONARY:

unsigned int:
'number' this is the number on which encryption is to be performed on
'byte[4]' is used to seperate the byte of the number 
'mask' is used to extract the bytes from the number
'encrypted' is used to store the encrypted number

int:
'pos1' is the number of the byte to swapped
'pos2' is the number of the byte to be swapped with
'i' is used to run a loop

*/

#include "headext.h"


void encrypt(unsigned int number, int pos1, int pos2)
{

	unsigned int byte[4], mask, encrypted;
	int i;

	//encrypted is initalized to be 0 and mask is initiazlied to have
	//four 1's on its first 4 bits	


	encrypted = 0;
	mask = 0xF000;

	//using the & operator the bytes are extraced and the mask is
	//shifted to extract the next byte
	

	for(i=0; i <= 3; i++)
	{
		byte[i] = number & mask;

		mask >>= 4;

	}

	
	//since the position of the bytes are to be swapped they are moved
	//into each others position. The > if test determines which way to 
	//shift without losing the number


	if((pos1-pos2) > 0)
	{
		byte[pos1] <<= (pos1-pos2)*4;

		byte[pos2] >>= (pos1-pos2)*4;

	}

	else
	{
		byte[pos1] >>= (pos2-pos1)*4;

		byte[pos2] <<= (pos2-pos1)*4;

	}

	
	//Then each byte is copied with positions swapped to encrypted

	
	for(i=0; i <= 3; i++)
	{
		encrypted |= byte[i];
	}

	printf("\nEncryption Complete !... Now printing \n");

	
	//print fucntion is called to print the values on screen

	print(number, encrypted);

}
