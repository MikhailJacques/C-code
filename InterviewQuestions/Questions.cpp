// Reverse a singly-linked linked-list (iterative version)
Node* ReverseList(Node ** List)	
{
	Node * temp1 = *List;
	Node * temp2 = NULL;
	Node * temp3 = NULL;

	while (temp1)
	{
		*List = temp1; 		// set the head to last node	
		temp2 = temp1->pNext; 	// save the next ptr in temp2
		temp1->pNext = temp3; 	// change next to previous
		temp3 = temp1;
		temp1 = temp2;
	}
 
	return *List;
}


// Delete a node in doubly-linked linked-list
void deleteNode(node *n)
{
	node *np = n->prev;
	node *nn = n->next;
	np->next = n->next;
	nn->prev = n->prev;
	delete n;
}


// Reverse a string
void ReverseString (char *String)
{
	char *Begin = String;
	char *End = String + strlen(String) - 1;
	char TempChar = '\0';

	while (Begin < End) 
	{
		TempChar = *Begin;
		*Begin = *End;
		*End = TempChar;
		Begin++;
		End--;
	}
}


// Sort a singly-linked list in descending order
struct node
{
	int value;
	node* NEXT;
}

// Assume Head pointer denotes the first element in the linked list;
// only need to change the values, not the pointers

Sort(Node *Head)
{
	node* first, second, temp;
	first = Head;

	while(first != null)
	{
		second = first->NEXT;

		while(second!=null)
		{
			if(first->value < second->value)
			{
				temp = new node();
				temp->value=first->value;
				first->value=second->value;
				second->value=temp->value;
				delete temp;
			}

			second = second->NEXT;
		}

		first = first->NEXT;
	}
}
 

// Insert a node in a sorted linked list
void sortedInsert(Node * head, Node * newNode)
{
	Node * current = head;
   	  
	// traverse list until you find item bigger than new node value
	while (current != NULL && current->data < newNode->data)
	{
		current = current->next;
	}
        
	// insert the new node before the big item
	newNode->next = current->next;
	current = newNode;
} 


// Convert string to upper case
void ToUpper(char * S)
{
	while (*S != 0)
	{
		*S = (*S >= 'a' && *S <= 'z') ? (*S-'a'+'A') : *S;
		S++;
	}
} 


// Multiply a number by 7 without using * and + operator.

//	NewNum = Num << 3; 	// mulitplied by 2 ^ 3 = 8
//	NewNum = NewNum - Num; 	// 8 – 1 = 7


// Write a function that takes in a string parameter and checks to see whether or not it is an integer, 
// and if it is then return the integer value.

#include <stdio.h>

int strtoint(char *s)
{
	int index = 0, flag = 0;

	while( *(s+index) != '\0')
	{
		if( (*(s + index) >= '0') && *(s + index) <= '9')
		{
			flag = 1;
			index++;
		}
		else
		{
			flag = 0;
			break;
		}
	}

	if( flag == 1 )
		return atoi(s);
	else
		return 0;
}

main() 
{ 
	printf("%d", strtoint("0123")); 
	printf("\n%d", strtoint("0123ii")); 
}

 

// Print data from a binary tree – In-order (ascending) recursive version
Void PrintTree (struct * node node)
{
	if ( node == NULL )
		return;

	PrintTree(node->left);
	Printf(“%d”, node->data);
	PrintTree(node->right);
}
 

// Print integer using only putchar function (recursive version)
void PrintNum (int Num)
{
	if (Num == 0)
		return;

	PrintNum (Num / 10);

	Puthcar (‘0’ + Num % 10);
}



// Find the factorial of number

// recursive version
int Factorial( int Num )
{
	if(num > 0)
		return Num * Factorial (Num –1); 
	else
		return 1;
}


// iterative version
int Factorial( int Num )
{
	int i;
	int result = 1;
	
	for (i = Num; i > 0; i-- )
	{
		result = result * i;
	}

	return result;
}

// Generate Fib numbers

// recursive version
int fib( n ) 
{
	if ( n < 2 )
		return 1;
	else
		return fib ( n – 1 ) + fib ( n – 2 );
}

// iterative version
int fib( n ) 
{
	int f1 = 1, f2 = 1;

	if ( n < 2 )
		return 1;
	
	for ( i = 1; i < n; i++)
	{
		f = f1 + f2;
		f1= f2;
		f = f1;
	}

	return f;
}



// Write a function that finds the last instance of a character in a string
char *lastchar(char *String, char ch)
{
	char * pStr = NULL;

	// traverse the entire string
	while(*String++ != NULL) 
		if( *String == ch ) 
			pStr = String;
	
	return pStr;
} 


// Return the Nth node from the end of the linked list in one pass.
Node * GetNthNode (Node* Head, int NthNode)
{
	Node * pNthNode = NULL;
	Node * pTempNode = NULL;
	int nCurrentElement = 0;
	
	for (pTempNode = Head; pTempNode != NULL; pTempNode = pTempNode->pNext)
	{
		nCurrentElement++;
			
		if (nCurrentElement - NthNode == 0)
		{
			pNthNode = Head;
		}
		else if(nCurrentElement - NthNode > 0)
		{
			pNthNode = pNthNode ->pNext;
		}					
	}

	if (pNthNode )
		return pNthNode;
	else
		return NULL;
}


// Counting set bits in a number.

// First version:
int CoutSetBits(int Num)
{
	for(int count=0; Num; Num >>= 1)
		if (Num & 1) 
	count++;

	return count;
}


// Optimized version:
int CoutSetBits(int Num)
{
	for(int count = 0; Num; count++)
		Num &= Num - 1;

	return count;
}



// Binary Search

// this function returns the location of key in the list;
// if the value is not found returns -1
int BinarySearch(int list[], int size, int key)
{
	int left, right, midpt;
	left = 0;
	right = size - 1;

	while (left <= right)
	{
		midpt = (int) ((left + right) / 2);

		if (key == list[midpt])
			return midpt;
		else if (key > list[midpt])
			left = midpt + 1;
		else
			right = midpt - 1;
	}

	return -1;
}


// Recursive
int BinarySearch2(int sortedArray[], int first, int last, int key) 
{
	if (first <= last) 
	{
		// compute mid point
		int mid = (first + last) / 2;  

		if (key == sortedArray[mid]) 
			return mid;   // found it
		else if (key < sortedArray[mid]) 
			// call itself for the lower part of the array
           	return BinarySearch2(sortedArray, first, mid-1, key);
		else
           	// call itself for the upper part of the array
           	return BinarySearch2(sortedArray, mid+1, last, key);
	}
	
	return -1;    // failed to find key
}