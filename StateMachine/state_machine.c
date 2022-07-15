
#include <stdio.h>
#include "led.h"
#include "main.h"
#include "state_machine.h"

// The state function array holds a function pointer to the function which gets called for each state. 
// In addition, a printable state name is stored for debugging purposes. 
// Each row in the state function array is defined by a struct:
typedef struct 
{
    const char* name;
    void (*func)(void);
} STATE_FUNCTION_ROW_STRUCT;

// Maps a state to its state transition function, which should be called when the state transitions into this state.
// The order of the members must be in sync with the STATE_ENUM member declaration order.
// This array has to stay in sync with the STATE_ENUM enumeration. That is, there must be the same number 
// of rows in state_function as there are states in STATE_ENUM, and they must be in the same order.

static STATE_FUNCTION_ROW_STRUCT state_function[] = 
{
    // STATE NAME        // STATE FUNCTION
    { "STATE_INIT",      &Led_Init },
    { "STATE_IDLE",      &Led_Idle },
    { "STATE_LED_ON",    &Led_On },
    { "STATE_LED_OFF",   &Led_Off }
};

// This following code defines a row in the state transition matrix (the state transition matrix is just an array of this structure). 
// This structure contains the current state, an event, and the state to transition to.
typedef struct 
{
    STATE_ENUM current_state;
    EVENT_ENUM event;
    STATE_ENUM next_state;
} STATE_TRANSITION_MATRIX_ROW_STRUCT;

// The state transition matrix is the heart of this state machine methodology. 
// It specifies what the next state should be, given the current state and the event that just occurred. 
// It is built as an array of the current_state/event/next_state structure defined above.
static STATE_TRANSITION_MATRIX_ROW_STRUCT state_transition_matrix[] = 
{
    // CURRENT STATE  // EVENT                // NEXT STATE
    { STATE_IDLE,     EVENT_BUTTON_PUSHED,     STATE_LED_ON  },
    { STATE_LED_ON,   EVENT_TIME_OUT,          STATE_LED_OFF },
    { STATE_LED_ON,   EVENT_BUTTON_PUSHED,     STATE_IDLE    },
    { STATE_LED_OFF,  EVENT_TIME_OUT,          STATE_LED_ON  },
    { STATE_LED_OFF,  EVENT_BUTTON_PUSHED,     STATE_IDLE    }
};

void Init(STATE_MACHINE_STRUCT* state_machine) 
{
    printf("Init state machine.\r\n");
    state_machine->current_state = STATE_IDLE;
}

const char* GetStateName(STATE_ENUM state)
{
    return state_function[state].name;
}

// The RunIteration() function for this state machine is pretty generic and simple, and there is no real need to modify it. 
// All of the logic is controlled by the state transition matrix above. Essentially, the function gets passed in an event 
// (lets call it the current event), and then runs through the state transition matrix row by row to find a pre-defined state 
// and event pair that match the current state and event. 
// If so, it transitions to the specified next state, and then calls the state function pointed to by the function pointer.

// The event would typically come as a result of some other operation or trigger. However, the EVENT_NONE can be passed 
// if no event has occurred, which is useful if we want to call RunIteration() every loop cycle, but events may come in less frequently.
void RunIteration(STATE_MACHINE_STRUCT *state_machine, EVENT_ENUM event) 
{
    // Iterate through the state transition matrix, checking if there is both a match with the current state and the event
    for (int i = 0; i < sizeof(state_transition_matrix) / sizeof(state_transition_matrix[0]); i++) 
    {
        if (state_transition_matrix[i].current_state == state_machine->current_state) 
        {
            if ((state_transition_matrix[i].event == event) || (state_transition_matrix[i].event == EVENT_ANY)) 
            {
                // Transition to the next state
                state_machine->current_state =  state_transition_matrix[i].next_state;

                // Call the function associated with transition
                (state_function[state_machine->current_state].func)();
                break;
            }
        }
    }
}