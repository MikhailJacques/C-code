/* 
Author: Mikhail Jacques
Student ID: 0128039
Date: July 12, 2001
Place: Computer Science Department, Trent University, Ontario, Canada

This program shows the implementation of Abstract Data Type (ADT) lists by using pointers.
A general list or ordered list with a set of elements (of any type), where there
exists a linear relationship among the elements is called an ADT list.
- Each element (with an exception of the first and the last) has a unique predecessor
and a unique successor.
- Each element, therefore, has a unique position: the position of the first element
is 0, the position of the second is 1, ..., and the position of the last is n - 1.
- Linear relationship is represented by the order of the elements in the list.

Pointers refer to memory locations. A pointer is not the name of a memory location
containing a data item (i.e. variable), but rather the name of a memory location
containing the address of a location containing the data item.
Pointers facilitate the design and the usage of dynamic data structures - structures
that can expand and contract during the runtime of the program.
A pointer implementation of a list is called a linked list. Linked implementations
of lists are not as conceptually simple as arrays, but more efficient to implement.

This program uses a singly-linked list - each node has only one pointer that
points to the next node. The disadvantage of this method is that it makes
insertions and deletions more difficult because we do not have access to the
previous node. */

#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* Define a new type - the type of the data elements that will be stored in the
nodes of the linked list (this gives us the flexibility to change the type of
the data elements at a later date) */
typedef int ListEntry;

/* Define the node. Nodes (variables) of the type ListNode will be forming our linked list */
typedef struct listnode {
			 ListEntry data;            /* defines a member of ListEntry type */
			 struct listnode *next;     /* defines a pointer to the next element */
			 } ListNode;

/* Define a new type - the type of the variable that will serve to keep track
of the number of nodes in the linked list and that will be pointing to the first
node in the linked list */
typedef struct listtype {
			 int count;      /* keeps track of the current number of nodes in the linked list */
			 ListNode *head; /* defines a pointer to the first node in the linked list */
			 } ListType;

/* Declare functions prototypes */
void CreateList(ListType *list);
void ClearList(ListType *list);
int CheckListEmpty(ListType *list);
int CheckListFull(ListType *list);
int ListSize(ListType *list);
void AddElement(ListEntry x, ListType *list);
void PrintList(ListType *list);
void InsertElement(int pos, ListEntry x, ListType *list);
void DeleteElement(int pos, ListEntry *x, ListType *list);
void RetrieveElement(int pos, ListEntry *x, ListType *list);
void ReplaceElement(int pos, ListEntry x, ListType *list);
int LocateElement(ListEntry x, ListType *list);
void SwapTwoElements(int pos1, int pos2, ListType *list);
void RotateByOneElement(ListType *list);
ListNode *SetPosition(int pos, ListType *list);
ListNode *MakeNode(ListEntry x);
void print_menu(void);
int read_number(void);

// Function: ReverseList (implemented on 18-Mar-11)
// Purpose: to reverse elements in the list
// Precondition: list has been created
// Postcondition: the elements in the list have been (conceptually) reversed
// Input: a reference to a linked list
// Output: none
void ReverseList(ListType *list)
{
	// allocate three local pointer variables that will point to the elements of type ListNode
	ListNode *currptr, *nextptr, *prevptr = NULL;

	// assign the value of the pointer variable head to the pointer variable currptr;
	// now currptr points to the same memory location the head does, that is, 
	// to the first element in the linked list
	currptr = list->head;

	// execute the while loop until the currptr points to NULL;
	// this operation traverses the linked list and redirects the pointers
	// to point from the next element to the previous element, 
	// thus effectively reversing the linked list
	while (currptr != NULL)
	{
		nextptr = currptr->next; 
		currptr->next = prevptr; 
		prevptr = currptr; 
		currptr = nextptr;
	}

	// make pointer variable head point to the last element in the linked list
	list->head = prevptr;
}


void main()
{
	/* Declare variable list of type ListType (this is an actual declaration of
	the list). This simply allocates a header node for the list.
	The variable list is a structure with two members.
	The first member of type integer is a counter that will store the current
	number of nodes in the linked list.
	The second member is a pointer to the first node in the linked list. */
	ListType list;

	/* declare three variables of type ListEntry */
	ListEntry x, pos, pos2;

	/* declare character variable */
	char action;

	/* print out a menu of available operations */
	print_menu();

	/* invoke function CreateList */
	CreateList(&list);

	for(;;)
	{
		printf("Enter action: ");
		fflush(stdin);
		action = getchar();

		switch (toupper(action))
		{
			case 'W': ClearList(&list);                   
				break;
			case 'S': printf("The size of the list is %d\n", ListSize(&list)); 
				break;
			case 'R': ReverseList(&list); 
				break;
			case 'A': printf("Enter the element to add: ");
						 x = read_number();
						 AddElement(x, &list);                  
				break;
			case 'P': PrintList(&list);                   
				break;
			case 'I': printf("Enter the element to insert: ");
						 x = read_number();
						 printf("Enter the position of the new element: ");
						 pos = read_number();
						 InsertElement(pos, x, &list);          
				break;
			case 'D': printf("Enter the position of the element to delete: ");
						 pos = read_number();
						 DeleteElement(pos, &x, &list);         
				break;
			case 'G': printf("Enter the position of the element to retrieve: ");
						 pos = read_number();
						 RetrieveElement(pos, &x, &list);       
				break;
			case 'X': printf("Enter the position of the first element to swap: ");
						 pos = read_number();
						 printf("Enter the position of the second element to swap: ");
						 pos2 = read_number();
						 SwapTwoElements(pos, pos2, &list);         
				break;
			case 'Y': RotateByOneElement(&list);             
				break;
			case 'E': printf("Enter the position of the element to replace: ");
						 pos = read_number();
						 printf("Enter the new value of the element: ");
						 x = read_number();
						 ReplaceElement(pos, x, &list);         
				break;
			case 'L': printf("Enter the element to locate: ");
						 x = read_number();
						 pos = LocateElement(x, &list);
						 if (pos == -1)
							 printf("The element was not found\n");
						 else
							 printf("The position of the element %d is %d\n", x, pos);
						 break;
			case 'M': print_menu();                       break;
			case 'Q': return;
			default:  printf("Invalid input! ");
		}
	}
}

/* Function: CreateList
Purpose: creates a new list
Precondition: none
Postcondition: list has been created and the list is empty
Input: an argument of type ListType (passed by reference)
Output: variable list (returned by reference) */
void CreateList(ListType *list)
{
	/* create and initialize list to empty */
	list->head = NULL;
	list->count = 0;
}

/* Function: ClearList
Purpose: clears a list, i.e. resets list to empty
Precondition: list has been created
Postcondition: all entries in the list have been removed
Input: one argument of type ListType (passed by reference)
Output: returns a variable list (returned by reference) */
void ClearList(ListType *list)
{
	/* allocate two local pointer variables that will point to the elements of
	type ListNode */
	ListNode *currptr, *tmpptr;

	/* assign the value of the pointer variable head to the pointer variable currptr.
	Now currptr points to the same memory location the head does, that is, to the first
	element in the linked list */
	currptr = list->head;

	/* run the while loop as long as the currptr does not point to NULL */
	while(currptr != NULL)
	{
		/* assign the value of the pointer variable currptr to the pointer variable
		tmpptr. Now, tmpptr points to the same pmemory location the currptr does */
		tmpptr = currptr;

		/* assign the value of the pointer variable next to the pointer variable
		currptr. Now, currptr points to the same pmemory location the next does */
		currptr = currptr->next;

		/* release the memory at the location pointed to by pointer variable tmpptr */
		free(tmpptr);
	}

	/* set the counter to 0 */
	list->count = 0;

	/* make head point to NULL (i.e. no first element exists in the linked list) */
	list->head = NULL;  /* alternatively: list->head = currptr; */
}

/* Function: CheckListEmpty
Purpose: checks whether the list contains any elements
Precondition: list has been created
Postcondition: returns true (1) if the list is empty; otherwise returns false (0)
Input: one argument of type ListType (passed by reference)
Output: returns true (1) if the list is empty; otherwise returns false (0) */
int CheckListEmpty(ListType *list)
{
	/* see if there are any elements in the linked list */
	return (list->count == 0);
}

/* Function: CheckListFull
Purpose: checks whether the list contains the maximum allowed number of elements
Precondition: list has been created
Postcondition: returns true (1) if the list is full; otherwise returns false (0)
Input: one argument of type ListType (passed by reference)
Output: returns true (1) if the list is full; otherwise returns false (0) */
int CheckListFull(ListType *list)
{
	/* not required for linked list implementation */
	return 0;
}

/* Function: ListSize
Purpose: checks the current number of elements in the linked list
Precondition: list has been created
Postcondition: returns the number of entries in the list
Input: one argument of type ListType (passed by reference)
Output: returns the number of elements in the list */
int ListSize(ListType *list)
{
	/* return the number of elements in the linked list */
	return (list->count);
}

/* Function: SetPosition
Purpose: sets the current pointer in the linked list to position pos.
		 0 <= pos < n, where n is the current number of elements in the list.
Precondition: list has been created
Postcondition: the pointer to the position pos in the linked list has been returned;
		list remains unchanged.
Input: i) an argument of type int which specifies the position (passed by value)
	  ii) an argument of type ListType (passed by reference)
Output: returns the pointer of type ListNode to the specified position */
ListNode *SetPosition(int pos, ListType *list)
{
	/* declare local pointer variable that will point to elements of type ListNode */
	ListNode *currptr;
	int counter = 0;

	/* check to see if the pos is within a valid range */
	if ((pos < 0)||(pos >= list->count))
		printf("***Error - position %d is out of range***\n", pos);

	else  /* move the pointer forward pos positions */
	{
		currptr = list->head;

		/* run the while loop as long as the counter is less than the pos.
		The second part of the while loop condition is not really needed,
		i.e. it is a paranoid programmer approach. */
		while((counter < pos) && (currptr != NULL))
		{
			currptr = currptr->next;
			++counter;
		}
	}

	if (currptr == NULL)
	{
		printf("***Error - problems in SetPosition\n");
		exit(EXIT_FAILURE);
	}
	else
		return currptr;
}

/* Function: MakeNode
Purpose: allocates a new node for the list
Precondition: list has been created; x is an element of type ListEntry to be added to the list
Postcondition: element x has been placed into the new node
Input: one argument of type ListEntry (passed by value)
Output: pointer to a new variable list of type ListNode (passed by reference) */
ListNode *MakeNode(ListEntry x)
{
	/* declare local pointer variable that will point to a new node of type ListNode */
	ListNode *newnode;

	/* allocate a new piece of memory and assign the address of the memory location
	to the pointer variable newnode */
	newnode = (ListNode *)malloc(sizeof(ListNode));

	/* make sure the memory allocation worked properly */
	if (newnode != NULL)
	{
		/* assign the value of x to data */
		newnode->data = x;

		/* make pointer next point to NULL */
		newnode->next = NULL;
	}
	else
	{
		printf("***Error - memory allocation failed***\n");
		exit(EXIT_FAILURE);
	}

	return newnode;
}

/*Function: AddElement
Purpose: adds a new element to the linked list
Precondition: list has been created; x is an element of type ListEntry that is
	to be added to the linked list
Postcondition: list has been added to the linked list
Input: i) an argument of type ListEntry (passed by value)
	  ii) an argument of type ListType (passed by reference)
Output: a variable list of type ListType (returned by reference) */
void AddElement(ListEntry x, ListType *list)
{
	/* allocate two local pointer variables that will point to the elements of
	type ListNode */
	ListNode *newnode, *currptr;

	/* call MakeNode to allocate a new node. Pointer variable newnode will be
	pointing to the memory address the MakeNode references */
	newnode = MakeNode(x);

	/* special case - list is empty. Make newnode the head of the list */
	if (list->head == NULL)
		list->head = newnode;
	else /* general case */
	{
		/* move the currptr pointer to the end of the linked list, i.e. currptr will
		be pointing to the last element in the linked list */
		currptr = SetPosition(list->count - 1, list);

		/* re-assign the last node's next pointer in the linked list to point to
		the newnode instead of the NULL */
		currptr->next = newnode;
	}

	/* increment the counter */
	++list->count;
}

/* Function: PrintList
Purpose: prints out the elements in the linked list
Precondition: list has been created
Postcondition: elements in the list are printed out in the order from beginning to end
Input: one argument of type ListType (passed by reference)
Output: None */
void PrintList(ListType *list)
{
	/* declare local pointer variable that will point to an element of type ListNode */
	ListNode *currptr;
	int i = 0;

	/* make currptr pointer point to the first element in the linked list.
	(Assign the value of the pointer variable head to the pointer variable currptr
	so that currptr points to the same memory location the head does.) */
	currptr = list->head;

	/* run the while loop as long as the currptr does not point to NULL */
	while(currptr != NULL)
	{
		/* print could be replaced by any operation. We are simply moving through
		the list and visiting each element - traversing the list.
		The conversion specifications depend on the type of data stored in the
		linked list */
		printf("The element at position %d is %d\n", i, currptr->data);

		currptr = currptr->next;

		++i;
	}
}

/* Function: InsertElement
Purpose: inserts a new node in the list
Precondition: the list has been created, is not full, x is an element of type ListEntry
	and 0 <= pos <= n where n is the current number of nodes in the list
Postcondition: x has been inserted at the position pos of the list; all entries formerly
	at the position pos and after it in the linked list have had their
		positions increased by one.
Input: i) an argument of type int that specifies the insertion position (passed by value)
	  ii) an argument of type ListEntry that specifies the value to be inserted (passed by value)
	 iii) an argument of type ListType (passed by reference)
Output: variable list (returned by reference) */
void InsertElement(int pos, ListEntry x, ListType *list)
{
	/* allocate three local pointer variables that will point to the elements of
	type ListNode */
	ListNode *newnode, *currptr, *prevptr;

	/* make sure the pos is within a valid range */
	if ((pos < 0)||(pos > list->count))
		printf("***Error - position is out of range***\n");
	else
	{
		/* call MakeNode to allocate a new node. Pointer variable newnode will be
		pointing to the memory address the MakeNode references */
		newnode = MakeNode(x);

		/* special case - inserting at position 0 */
		if (pos == 0)
		{
			newnode->next = list->head;
			list->head = newnode;
		}
		else  /* general case - inserting at position pos */
		{
			prevptr = SetPosition(pos - 1, list);
			currptr = prevptr->next;
			newnode->next = currptr;
			prevptr->next = newnode;
		}
		
		/* increment counter */
		list->count++;
	}
}

/* Function: DeleteElement
Purpose: deletes an element from the linked list
Precondition: list has been created, x is an element of type ListEntry
	and 0 <= pos < n, where n is the current number of elements in the list
Postcondition: an entry in the linked list at the position pos has been returned
	in x and deleted from the linked list; all entries after the position pos 
	in the linked list have (virtually) shifted backwards by one, i.e. the actual 
	memory locations never changed
Input: i) an argument of type int that defines the position of the entry to be
		deleted (passed by value)
	  ii) an argument of type ListEntry that retrieves the deleted value
	    (passed by reference)
     iii) an argument of type ListType (passed by reference)
Output: variable list (returned by reference) */
void DeleteElement(int pos, ListEntry *x, ListType *list)
{
	/* allocate two local pointer variables that will point to the elements of
	type ListNode */
	ListNode *currptr, *prevptr;

	/* make sure the list is not empty */
	if(CheckListEmpty(list))
		printf("***Error - the list is empty***\n");

	/* make sure the pos is within the valid range */
	else if ((pos < 0)||(pos >= list->count))
		printf("***Error - position is out of range***\n");
	else
	{
		if (pos == 0)   /* special case - deleting list head */
		{
			currptr = list->head;
			list->head = currptr->next;
		}
		else            /* general case */
		{
			prevptr = SetPosition(pos - 1, list);
			currptr = prevptr->next;
			prevptr->next = currptr->next;
		}

		/* retrieve the data */
		*x = currptr->data;

		/* free up the memory */
		free(currptr);

		/* decrement the counter by 1 */
		--list->count;
	}
}

/* Function: SwapTwoElements
Purpose: exchanges two entries at the specified positions in the linked list
Precondition: list has been created, is not empty, and 0 < pos1, pos2 < n,
	where n is the current number of nodes in the linked list
Postcondition: Entry at the position pos1 in the list has been exchanged with the entry at
	the position pos2 in the list; the rest of the entries in the list remained unchanged
Input: i) an argument of type int which specifies the position of the first node (passed by value)
	  ii) an argument of type int which specifies the position of the second node (passed by value)
	 iii) an argument of type ListType (passed by reference)
Output: variable list; returned by reference */
void SwapTwoElements(int pos1, int pos2, ListType *list)
{
	/* allocate two local pointer variables that will point to the elements of type ListNode */
	ListNode *ptr1, *ptr2;

	int temp;

	/* make sure the list is not empty */
	if(CheckListEmpty(list))
		printf("***Error - the list is empty***\n");

	/* make sure the pos1 is within the valid range */
	else if ((pos1 < 0)||(pos1 >= list->count))
		printf("***Error - position %d is out of range***\n", pos1);

	/* make sure the pos2 is within a valid range */
	else if ((pos2 < 0)||(pos2 >= list->count))
		printf("***Error - position %d is out of range***\n", pos2);
	else
	{
		/* make pointer ptr1 point to the node at the position pos1 */
		ptr1 = SetPosition(pos1, list);

		/* make pointer ptr2 point to the node at the position pos2 */
		ptr2 = SetPosition(pos2, list);

		/* perform the swap */
		temp = ptr1->data;
		ptr1->data = ptr2->data;
		ptr2->data = temp;
	}
}

/* Function: RetrieveElement
Purpose: retrieves an element from the linked list
Precondition: list has been created, x is an element of type ListEntry
	and 0 < pos <= n, where n is the current number of elements in the list
Postcondition: the entry in the linked list data at the position pos of the list has
	been returned in variable x; all entries in the list remained unchanged.
Input: i) an argument of type int that defines the position (passed by value)
	  ii) an argument of type ListEntry that defines the value to be retrieved (passed by reference)
	 iii) an argument of type ListType (passed by reference)
Output: variable list (returned by reference) */
void RetrieveElement(int pos, ListEntry *x, ListType *list)
{
	/* declare local pointer variable that will point to an element of type ListNode */
	ListNode *currptr;

	/* make sure the list is not empty */
	if(CheckListEmpty(list))
		printf("***Error - the list is empty***\n");

	/* make sure the pos is within the valid range */
	else if ((pos < 0)||(pos >= list->count))
		printf("***Error - position is out of range***\n");
	else
	{
		/* retrieve the element at the position pos. Set the currptr pointer to point to the
		memory address specified by the position pos and then assign the value of the data
		to the variable x */
		currptr = SetPosition(pos, list);
		*x = currptr->data;
	}
}

/* Function: ReplaceElement
Purpose: replaces an element in the linked list
Precondition: list has been created, x is an element of type ListEntry
	and 0 <= pos < n, where n is the current number of elements in the list
Postcondition: the entry at the position pos in the linked list has been replaced
	with x; all other entries remained unchanged.
Input: i) an argument of type int that specifies the position of the element to
		  be replaced (passed by value)
	  ii) an argument of type ListEntry that specifies the replacement value (passed by value)
	 iii) an argument of type ListType (passed by reference)
Output: variable list (returned by reference) */
void ReplaceElement(int pos, ListEntry x, ListType *list)
{
	/* declare local pointer variable that will point to an element of type ListNode */
	ListNode *currptr;

	/* make sure the list is not empty */
	if(CheckListEmpty(list))
		printf("***Error - the list is empty***\n");

	/* make sure the pos is within the valid range */
	else if ((pos < 0)||(pos >= list->count))
		printf("***Error - position is out of range***\n");
	else
	{
		/* replace element at the position pos with x. Set the currptr pointer point to
		the memory address specified by the position pos and then assign the value of the
		x to the variable data */
		currptr = SetPosition(pos, list);
		currptr->data = x;
	}
}

/* Function: LocateElement
Purpose: locates an element in the linked list
Precondition: list has been created, x is an element of type ListEntry
Postcondition: elements in the linked list are searched in order from beginning
	to end looking for the element x; if x is found its position is returned; 
	otherwise -1 is returned.
Input: i) an argument of type ListEntry that specifies the element (i.e. the value 
	      stored in the data) to be searched for (passed by value)
	  ii) an argument of type ListType (passed by reference)
Output: returns the position of the found element or -1 if no element was found */
int LocateElement(ListEntry x, ListType *list)
{
	/* declare local pointer variable that will point to elements of type ListNode */
	ListNode *currptr;
	int i = 0, found = FALSE, pos;

	/* make currptr pointer point to the first element in the linked list */
	currptr = list->head;

	/* lineary search the linked list for x */
	while (currptr != NULL && !found)
	{
		/* see if x is found.
		If x were a string then the following comparison statement would be used:
		if (strcmp(currptr->data, x) == 0) */
		if (currptr->data == x)
		{
			found = TRUE;

			/* save the position where x was found */
			pos = i;
		}
		else
		{
			/* move to the next element and increment index i */
			currptr = currptr->next;
			++i;
		}
	}
	/* after the loop has terminated, see if x was located or the end of the linked
	list has been reached */
	if (found)
		return pos;
	else
		return -1;
}

/* Function: RotateByOneElement
Purpose: to rotate elements in the list forward by one position
Precondition: list has been created and is not empty
Postcondition: elements in the list have been moved forward by one position with
	the element in the last position moving to position 0.
Input: one argument of type ListType (passed by reference)
Output: none */
void RotateByOneElement(ListType *list)
{
	ListEntry item;

	/* make sure the list is not empty */
	if (CheckListEmpty(list))
		printf("***Error - the list is empty***\n");
	else
	{
		DeleteElement(ListSize(list) - 1, &item, list);
		InsertElement(0, item, list);
   }
}

/* Function: print_menu
Purpose: prints a menu of available operations
Input: none
Output: none */
void print_menu(void)
{
	printf("Available operations:\n");
	printf("W - clear list\n");
	printf("R - reverse list\n");
	printf("S - print list size\n");
	printf("A - add element\n");
	printf("P - print list\n");
	printf("I - insert element\n");
	printf("D - delete element\n");
	printf("G - retrieve element\n");
	printf("E - replace element\n");
	printf("L - locate element\n");
	printf("X - swap two elements\n");
	printf("Y - rotate list by one element forward\n");
	printf("M - print menu\n");
	printf("Q - quit the program\n");
}

/* Function: read_number
Purpose: reads a list number and validates it to be a numeric value
Input: none
Output: returns the valid read number */
int read_number(void)
{
	int i = 0, correct_input, number;
	char ch, num[6];

	do {
		fflush(stdin);

		while (isspace(ch = getchar()))
			;

		while (ch != '\n' && ch != EOF && i < 5) {
			if (isdigit(ch)) {
				num[i++] = ch;
				correct_input = TRUE;
			}
			else {
				printf("Invalid input! Must be a numeric value.\n");
				printf("Try again: ");
				i = 0;
				correct_input = FALSE;
				break;
			}
			ch = getchar();
		}
	} while (!correct_input);

	num[i] = '\0';
	number = atoi(num);

	return number;
}