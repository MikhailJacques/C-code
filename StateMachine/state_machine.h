#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum {
    STATE_INIT,
    STATE_IDLE,
    STATE_LED_ON,
    STATE_LED_OFF
} STATE_ENUM;

// This simple state machine needs to remember only one thing, the current state. 
// All the state machine’s variables are declared in the STATE_MACHINE_STRUCT.
// A pointer to this struct gets passed in as the first variable to all the state machine functions, 
// just like the 'this' object gets passed in the object-oriented world.
typedef struct 
{
    STATE_ENUM current_state;
} STATE_MACHINE_STRUCT;

// All the possible events that can occur for this state machine.
// Unlike STATE_ENUM, these do not need to be kept in special order.
typedef enum {
    EVENT_ANY,
    EVENT_NONE,
    EVENT_BUTTON_PUSHED,
    EVENT_TIME_OUT,
} EVENT_ENUM;

void Init(STATE_MACHINE_STRUCT* state_machine);
void RunIteration(STATE_MACHINE_STRUCT* state_machine, EVENT_ENUM event);
const char* GetStateName(STATE_ENUM state);

#endif