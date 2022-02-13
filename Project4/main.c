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
#include "lcd.h"
// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

//void match_switches(void){
//    for(int i = 0; i < 8; i++){;
//        led_set(i, read_switch(i));
//    }
//}

int main ( void )
{
    LCD_Init();
    LCD_DisplaySet(displaySetBlinkOn);
    LCD_WriteStringAtPos("My Text", 1, 0);
    /* Initialize all modules */    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        //set_color(255,0,0);
    }

    /* Execution should not come here during normal operation */

}


/*******************************************************************************
 End of File
*/

