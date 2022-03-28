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
//    attack_chop();
    
//    attack_set_direction(-1);
//    attack_set_speed(1);
    
    
//    movement_set_direction_left(1);
//    movement_set_speed_left(1);
//    
//    movement_set_direction_right(1);
//    movement_set_speed_right(1);
    
    while ( true )
    {
        
        if(axeSensorA_Get() == 1){
            LED3_Set();
        } else {
            LED3_Clear();
        }
        if(axeSensorB_Get() == 1){
            LED4_Set();
        } else {
            LED4_Clear();
        }
        if(BT_STATUS_Get() == 1){
            LED1_Set();
        } else {
            LED1_Clear();
        }
        
       
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

