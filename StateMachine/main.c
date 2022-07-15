
#include <stdio.h>
#include <stdbool.h>

#include "state_machine.h"

int main() 
{
    printf("main() called.\r\n");

    // Create new state machine object
    STATE_MACHINE_STRUCT state_machine;

    Init(&state_machine);
    printf("State is now %s.\r\n", GetStateName(state_machine.current_state));

    // Push button to start flasher
    printf("Button pushed.\r\n");
    RunIteration(&state_machine, EVENT_BUTTON_PUSHED);
    printf("State is now %s.\r\n", GetStateName(state_machine.current_state));

    // Timeout
    printf("Timeout.\r\n");
    RunIteration(&state_machine, EVENT_TIME_OUT);
    printf("State is now %s.\r\n", GetStateName(state_machine.current_state));

    // Timeout
    printf("Timeout.\r\n");
    RunIteration(&state_machine, EVENT_TIME_OUT);
    printf("State is now %s.\r\n", GetStateName(state_machine.current_state));

    // Timeout
    printf("Timeout.\r\n");
    RunIteration(&state_machine, EVENT_TIME_OUT);
    printf("State is now %s.\r\n", GetStateName(state_machine.current_state));

    // Push button again to stop flasher
    printf("Button pushed.\r\n");
    RunIteration(&state_machine, EVENT_BUTTON_PUSHED);
    printf("State is now %s.\r\n", GetStateName(state_machine.current_state));

    return 0;
}