/*******************************************************************************
  SYS PORTS Static Functions for PORTS System Service

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.c

  Summary:
    GPIO function implementations for the GPIO PLIB.

  Description:
    The GPIO PLIB provides a simple interface to manage peripheral
    input-output controller.

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
//DOM-IGNORE-END

#include "plib_gpio.h"


/* Array to store callback objects of each configured interrupt */
GPIO_PIN_CALLBACK_OBJ portPinCbObj[8];

/* Array to store number of interrupts in each PORT Channel + previous interrupt count */
uint8_t portNumCb[7 + 1] = { 0, 0, 3, 3, 5, 5, 8, 8, };

/******************************************************************************
  Function:
    GPIO_Initialize ( void )

  Summary:
    Initialize the GPIO library.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_Initialize ( void )
{
    /* PORTA Initialization */
    LATA = 0x0; /* Initial Latch Value */
    TRISACLR = 0xff; /* Direction Control */

    /* PORTB Initialization */
    ANSELBCLR = 0xe00; /* Digital Mode Enable */
    /* Change Notice Enable */
    CNCONBSET = _CNCONB_ON_MASK;
    PORTB;
    IEC1SET = _IEC1_CNBIE_MASK;

    /* PORTC Initialization */

    /* PORTD Initialization */
    /* Change Notice Enable */
    CNCONDSET = _CNCOND_ON_MASK;
    PORTD;
    IEC1SET = _IEC1_CNDIE_MASK;

    /* PORTE Initialization */

    /* PORTF Initialization */
    /* Change Notice Enable */
    CNCONFSET = _CNCONF_ON_MASK;
    PORTF;
    IEC1SET = _IEC1_CNFIE_MASK;

    /* PORTG Initialization */



    /* PPS Input Remapping */

    /* PPS Output Remapping */


    uint32_t i;
    /* Initialize Interrupt Pin data structures */
    portPinCbObj[0 + 0].pin = GPIO_PIN_RB9;
    
    portPinCbObj[0 + 1].pin = GPIO_PIN_RB10;
    
    portPinCbObj[0 + 2].pin = GPIO_PIN_RB11;
    
    portPinCbObj[3 + 0].pin = GPIO_PIN_RD14;
    
    portPinCbObj[3 + 1].pin = GPIO_PIN_RD15;
    
    portPinCbObj[5 + 0].pin = GPIO_PIN_RF4;
    
    portPinCbObj[5 + 1].pin = GPIO_PIN_RF5;
    
    portPinCbObj[5 + 2].pin = GPIO_PIN_RF3;
    
    for(i=0; i<8; i++)
    {
        portPinCbObj[i].callback = NULL;
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: GPIO APIs which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    uint32_t GPIO_PortRead ( GPIO_PORT port )

  Summary:
    Read all the I/O lines of the selected port.

  Description:
    This function reads the live data values on all the I/O lines of the
    selected port.  Bit values returned in each position indicate corresponding
    pin levels.
    1 = Pin is high.
    0 = Pin is low.

    This function reads the value regardless of pin configuration, whether it is
    set as as an input, driven by the GPIO Controller, or driven by a peripheral.

  Remarks:
    If the port has less than 32-bits, unimplemented pins will read as
    low (0).
    Implemented pins are Right aligned in the 32-bit return value.
*/
uint32_t GPIO_PortRead(GPIO_PORT port)
{
    return (*(volatile uint32_t *)(&PORTA + (port * 0x40)));
}

// *****************************************************************************
/* Function:
    void GPIO_PortWrite (GPIO_PORT port, uint32_t mask, uint32_t value);

  Summary:
    Write the value on the masked I/O lines of the selected port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value)
{
    *(volatile uint32_t *)(&LATA + (port * 0x40)) = (*(volatile uint32_t *)(&LATA + (port * 0x40)) & (~mask)) | (mask & value);
}

// *****************************************************************************
/* Function:
    uint32_t GPIO_PortLatchRead ( GPIO_PORT port )

  Summary:
    Read the latched value on all the I/O lines of the selected port.

  Remarks:
    See plib_gpio.h for more details.
*/
uint32_t GPIO_PortLatchRead(GPIO_PORT port)
{
    return (*(volatile uint32_t *)(&LATA + (port * 0x40)));
}

// *****************************************************************************
/* Function:
    void GPIO_PortSet ( GPIO_PORT port, uint32_t mask )

  Summary:
    Set the selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortSet(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&LATASET + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortClear ( GPIO_PORT port, uint32_t mask )

  Summary:
    Clear the selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortClear(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&LATACLR + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortToggle ( GPIO_PORT port, uint32_t mask )

  Summary:
    Toggles the selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortToggle(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&LATAINV + (port * 0x40))= mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortInputEnable ( GPIO_PORT port, uint32_t mask )

  Summary:
    Enables selected IO pins of a port as input.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&TRISASET + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortOutputEnable ( GPIO_PORT port, uint32_t mask )

  Summary:
    Enables selected IO pins of a port as output(s).

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&TRISACLR + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortInterruptEnable(GPIO_PORT port, uint32_t mask)

  Summary:
    Enables IO interrupt on selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortInterruptEnable(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&CNENASET + (port * 0x40)) = mask;
}

// *****************************************************************************
/* Function:
    void GPIO_PortInterruptDisable(GPIO_PORT port, uint32_t mask)

  Summary:
    Disables IO interrupt on selected IO pins of a port.

  Remarks:
    See plib_gpio.h for more details.
*/
void GPIO_PortInterruptDisable(GPIO_PORT port, uint32_t mask)
{
    *(volatile uint32_t *)(&CNENACLR + (port * 0x40)) = mask;
}

// *****************************************************************************
// *****************************************************************************
// Section: GPIO APIs which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    bool GPIO_PinInterruptCallbackRegister(
        GPIO_PIN pin,
        const GPIO_PIN_CALLBACK callback,
        uintptr_t context
    );

  Summary:
    Allows application to register callback for configured pin.

  Remarks:
    See plib_gpio.h for more details.
*/
bool GPIO_PinInterruptCallbackRegister(
    GPIO_PIN pin,
    const GPIO_PIN_CALLBACK callback,
    uintptr_t context
)
{
    uint8_t i;
    uint8_t portIndex;

    portIndex = pin >> 4;

    for(i = portNumCb[portIndex]; i < portNumCb[portIndex +1]; i++)
    {
        if (portPinCbObj[i].pin == pin)
        {
            portPinCbObj[i].callback = callback;
            portPinCbObj[i].context  = context;
            return true;
        }
    }
    return false;
}

// *****************************************************************************
// *****************************************************************************
// Section: Local Function Implementation
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Function:
    void CHANGE_NOTICE_B_InterruptHandler(void)

  Summary:
    Interrupt Handler for change notice interrupt for channel B.

  Remarks:
	It is an internal function, user should not call it directly.
*/
void CHANGE_NOTICE_B_InterruptHandler(void)
{
    uint8_t i;
    uint32_t status;

    status  = CNSTATB;
    status &= CNENB;

    PORTB;
    IFS1CLR = _IFS1_CNBIF_MASK;

    /* Check pending events and call callback if registered */
    for(i = 0; i < 3; i++)
    {
        if((status & (1 << (portPinCbObj[i].pin & 0xF))) && (portPinCbObj[i].callback != NULL))
        {
            portPinCbObj[i].callback (portPinCbObj[i].pin, portPinCbObj[i].context);
        }
    }
}

// *****************************************************************************
/* Function:
    void CHANGE_NOTICE_D_InterruptHandler(void)

  Summary:
    Interrupt Handler for change notice interrupt for channel D.

  Remarks:
	It is an internal function, user should not call it directly.
*/
void CHANGE_NOTICE_D_InterruptHandler(void)
{
    uint8_t i;
    uint32_t status;

    status  = CNSTATD;
    status &= CNEND;

    PORTD;
    IFS1CLR = _IFS1_CNDIF_MASK;

    /* Check pending events and call callback if registered */
    for(i = 3; i < 5; i++)
    {
        if((status & (1 << (portPinCbObj[i].pin & 0xF))) && (portPinCbObj[i].callback != NULL))
        {
            portPinCbObj[i].callback (portPinCbObj[i].pin, portPinCbObj[i].context);
        }
    }
}

// *****************************************************************************
/* Function:
    void CHANGE_NOTICE_F_InterruptHandler(void)

  Summary:
    Interrupt Handler for change notice interrupt for channel F.

  Remarks:
	It is an internal function, user should not call it directly.
*/
void CHANGE_NOTICE_F_InterruptHandler(void)
{
    uint8_t i;
    uint32_t status;

    status  = CNSTATF;
    status &= CNENF;

    PORTF;
    IFS1CLR = _IFS1_CNFIF_MASK;

    /* Check pending events and call callback if registered */
    for(i = 5; i < 8; i++)
    {
        if((status & (1 << (portPinCbObj[i].pin & 0xF))) && (portPinCbObj[i].callback != NULL))
        {
            portPinCbObj[i].callback (portPinCbObj[i].pin, portPinCbObj[i].context);
        }
    }
}

/* Function:
    void CHANGE_NOTICE_InterruptHandler(void)

  Summary:
    Interrupt Handler for change notice interrupt.

  Remarks:
	It is an internal function called from ISR, user should not call it directly.
*/
void CHANGE_NOTICE_InterruptHandler(void)
{
    if(IFS1bits.CNBIF)
    {
        CHANGE_NOTICE_B_InterruptHandler();
    }
    if(IFS1bits.CNDIF)
    {
        CHANGE_NOTICE_D_InterruptHandler();
    }
    if(IFS1bits.CNFIF)
    {
        CHANGE_NOTICE_F_InterruptHandler();
    }
}

/*******************************************************************************
 End of File
*/
