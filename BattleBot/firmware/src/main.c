/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "motor.h"
#include "bt.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    setup_motors();
    setup_bt();  
    char action = 0;
    while ( true )
    {
        // this function should disable the UART interrupt before reading, but
        // given how slowly we run actions, we should be fine
        if(!q_empty()){
            action = q_pop();
        }
        
        // if C has been read from the queue, chop
        switch(action){
            case 'A': // attack down
                attack_down();
                action = 0;
                break;
            case 'B': // attack up
                attack_up();
                action = 0;
                break;
            case 'C':
                attack_chop();
                action = 0;
                break;
            case 'D':
                change_direction();
                action = 0;
                break;
        }
        
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        if(BTN1_Get()){
            attack_chop();
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

