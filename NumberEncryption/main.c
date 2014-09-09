/* 
FUNCTION OVERVIEW
The main function calls upon other functions to perform encryption , error
checking etc. It does no actual processing it loops until the user decides
to quit

DATA DICTIONARY:

unsigned int:
'number' is the number to be encrypted

int:
'pos1' is a position to swap
'pos2' is a position to swap

char:
'usrChoice' this variable is used to keep the loop running if the user
wants to continue

*/
 


#include "header.h"

main()
{
	unsigned int number;
	int pos1, pos2;
	char usrChoice;

	//as it is seen clearly over here the main program does not
	//perform any actual processing. It calls over functions to encrypt and
	//verify	

	do
	{
		readData(&number, &pos1, &pos2);

		encrypt(number, pos1, pos2);

		printf("\nEncrypt another number ?\nPress Y for yes any other key to quit: ");
		fflush(stdin);
		scanf("%c",&usrChoice);

	}
	while(toupper(usrChoice) == 'Y');

	printf("\nThis program will now exit.....");

	return 0;

}

