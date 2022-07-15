/*
FUNCTION OVERVIEW
This function valiadates the data. The basic rules are that pos1 cannot be
equal to pos2 and both have to be within 0-3. It checks all for all
possible errors and prints them out on screen

DATA DICTIONARY:
int:
'pos1' is position 1
'pos2' is position 2

*/


#include "headext.h"


int checkPos(int pos1, int pos2)
{
	
	//flag is set to 0, so be begin assuming that there are no errors
	//If an error is found flag is set to 1 to indicate to the calling
	//function that errors were found. A description of each error is 	
	//printed onscreen
	
	int flag = 0;

	//check pos1 for bounds

	if(pos1 > 3 || pos1 < 0)
	{
		printf("\n***ERROR Pos1 out of bounds\n");
		flag = 1;
	}

	
	//check pos2 for bounds

	if(pos2 > 3 || pos2 < 0)
	{
		printf("\n***ERROR Pos2 out of bounds\n");
		flag = 1;
	}

	//check if pos1 and pos2 are the same
	

	if(pos1 == pos2)
	{
		printf("\n***ERROR If Pos1 and Pos2 are the same no encryption takes place\n");
		flag = 1;
	}

	return flag;
}
