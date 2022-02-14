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
#include "aic.h"

#define ADC_TO_3V3 3.3/1023 // conversion factor for 10-bit AIC number to 0-3.3V scale

int main ( void )
{
    /* Initialize all modules */    
    LCD_Init();
    AIC_Init();
    
    float aic_val; // Analog input control value (0-3.3V)
    char to_display[80]; // string to display on a line

    LCD_WriteStringAtPos("Scale: 0-3.3V", 0, 0); // first line

    while ( true )
    {      
        aic_val = AIC_Val() * ADC_TO_3V3; // convnert 10-bit AIC number to 0-3.3V scale
        sprintf(to_display, "Value: %5.1f", aic_val); // write value to string
        LCD_WriteStringAtPos(to_display, 1, 0); // show string on second display line

    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );

}


/*******************************************************************************
 End of File
*/

