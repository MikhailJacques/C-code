#include <stdio.h>

// The state functions are the functions which are called when the current 
// state and event matches a pair in the state transition matrix. 
// While the rest of the state machine controls the high-level flow, 
// the state functions are the guts of the state machine and 
// are the functions which actually do something.
// These state functions below are only really stubs, 
// and do not do much. Real life state functions do real life things.

void Led_Init(void)
{
    printf("Led_Init() called.\r\n");
}

void Led_On(void)
{
    printf("LED turned on.\r\n");
}

void Led_Off(void)
{
    printf("LED turned off.\r\n");
}

void Led_Idle(void)
{
    printf("LED in idle state.\r\n");
}