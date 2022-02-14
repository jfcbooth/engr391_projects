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

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "lcd.h"
#include "acl.h"

int main ( void )
{
    /* Initialize all modules */    
    LCD_Init();
    ACL_Init();
    
    float acl_vals[3]; // accelerometer values in terms of g (1g = vertical)
    char to_display[80]; // string to display on a line

    while ( true )
    {      
        ACL_ReadGValues(acl_vals); // read values
        sprintf(to_display, "X:%5.1f  Y:%5.1f", acl_vals[0], acl_vals[1]); // write to string
        LCD_WriteStringAtPos(to_display, 0, 0); // update display line 1
        sprintf(to_display, "Z:%5.1f", acl_vals[2]);
        LCD_WriteStringAtPos(to_display, 1, 0); // update display line 2
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );

}


/*******************************************************************************
 End of File
*/

