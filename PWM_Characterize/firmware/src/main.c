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
#include "uart.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************


#define DELAY 20  // Our delay between speed updates in millis
#define INCREMENT 5   // Our increment value for speed control

#define HISTORY_SIZE 32   // The size of our history for
                          // averaging the period
#define TIMEOUT 1000  // MS to wait for averaging period to
                      // complete before timing out

/* CP0.Count counts at half the CPU rate */
#define TICK_HZ (CPU_HZ / 2)

void wait_us(unsigned int us)
{
    // Convert microseconds us into how many clock ticks it will take
    us *= 80000000 / 1000000 / 2; // Core Timer updates every 2 ticks

    _CP0_SET_COUNT(0); // Set Core Timer count to 0

    while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}

void wait_ms(int ms)
{
    wait_us(ms * 1000);
}

char info[100] = "tests\n";

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    setup_motors();
    setup_uart();
    set_command(info);
    movement_set_speed_left(0);
    movement_set_direction_left(1);
    wait_ms(1000); // wait 1 seconnd for thng to settle
    
    
    while ( true )
    {
        
       
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

