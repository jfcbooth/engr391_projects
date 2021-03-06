/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

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

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for LED0 pin ***/
#define LED0_Set()               (LATASET = (1<<0))
#define LED0_Clear()             (LATACLR = (1<<0))
#define LED0_Toggle()            (LATAINV= (1<<0))
#define LED0_OutputEnable()      (TRISACLR = (1<<0))
#define LED0_InputEnable()       (TRISASET = (1<<0))
#define LED0_Get()               ((PORTA >> 0) & 0x1)
#define LED0_PIN                  GPIO_PIN_RA0

/*** Macros for SW7 pin ***/
#define SW7_Set()               (LATBSET = (1<<9))
#define SW7_Clear()             (LATBCLR = (1<<9))
#define SW7_Toggle()            (LATBINV= (1<<9))
#define SW7_OutputEnable()      (TRISBCLR = (1<<9))
#define SW7_InputEnable()       (TRISBSET = (1<<9))
#define SW7_Get()               ((PORTB >> 9) & 0x1)
#define SW7_PIN                  GPIO_PIN_RB9
#define SW7_InterruptEnable()   (CNENBSET = (1<<9))
#define SW7_InterruptDisable()  (CNENBCLR = (1<<9))

/*** Macros for SW6 pin ***/
#define SW6_Set()               (LATBSET = (1<<10))
#define SW6_Clear()             (LATBCLR = (1<<10))
#define SW6_Toggle()            (LATBINV= (1<<10))
#define SW6_OutputEnable()      (TRISBCLR = (1<<10))
#define SW6_InputEnable()       (TRISBSET = (1<<10))
#define SW6_Get()               ((PORTB >> 10) & 0x1)
#define SW6_PIN                  GPIO_PIN_RB10
#define SW6_InterruptEnable()   (CNENBSET = (1<<10))
#define SW6_InterruptDisable()  (CNENBCLR = (1<<10))

/*** Macros for SW5 pin ***/
#define SW5_Set()               (LATBSET = (1<<11))
#define SW5_Clear()             (LATBCLR = (1<<11))
#define SW5_Toggle()            (LATBINV= (1<<11))
#define SW5_OutputEnable()      (TRISBCLR = (1<<11))
#define SW5_InputEnable()       (TRISBSET = (1<<11))
#define SW5_Get()               ((PORTB >> 11) & 0x1)
#define SW5_PIN                  GPIO_PIN_RB11
#define SW5_InterruptEnable()   (CNENBSET = (1<<11))
#define SW5_InterruptDisable()  (CNENBCLR = (1<<11))

/*** Macros for LED1 pin ***/
#define LED1_Set()               (LATASET = (1<<1))
#define LED1_Clear()             (LATACLR = (1<<1))
#define LED1_Toggle()            (LATAINV= (1<<1))
#define LED1_OutputEnable()      (TRISACLR = (1<<1))
#define LED1_InputEnable()       (TRISASET = (1<<1))
#define LED1_Get()               ((PORTA >> 1) & 0x1)
#define LED1_PIN                  GPIO_PIN_RA1

/*** Macros for SW4 pin ***/
#define SW4_Set()               (LATDSET = (1<<14))
#define SW4_Clear()             (LATDCLR = (1<<14))
#define SW4_Toggle()            (LATDINV= (1<<14))
#define SW4_OutputEnable()      (TRISDCLR = (1<<14))
#define SW4_InputEnable()       (TRISDSET = (1<<14))
#define SW4_Get()               ((PORTD >> 14) & 0x1)
#define SW4_PIN                  GPIO_PIN_RD14
#define SW4_InterruptEnable()   (CNENDSET = (1<<14))
#define SW4_InterruptDisable()  (CNENDCLR = (1<<14))

/*** Macros for SW3 pin ***/
#define SW3_Set()               (LATDSET = (1<<15))
#define SW3_Clear()             (LATDCLR = (1<<15))
#define SW3_Toggle()            (LATDINV= (1<<15))
#define SW3_OutputEnable()      (TRISDCLR = (1<<15))
#define SW3_InputEnable()       (TRISDSET = (1<<15))
#define SW3_Get()               ((PORTD >> 15) & 0x1)
#define SW3_PIN                  GPIO_PIN_RD15
#define SW3_InterruptEnable()   (CNENDSET = (1<<15))
#define SW3_InterruptDisable()  (CNENDCLR = (1<<15))

/*** Macros for SW2 pin ***/
#define SW2_Set()               (LATFSET = (1<<4))
#define SW2_Clear()             (LATFCLR = (1<<4))
#define SW2_Toggle()            (LATFINV= (1<<4))
#define SW2_OutputEnable()      (TRISFCLR = (1<<4))
#define SW2_InputEnable()       (TRISFSET = (1<<4))
#define SW2_Get()               ((PORTF >> 4) & 0x1)
#define SW2_PIN                  GPIO_PIN_RF4
#define SW2_InterruptEnable()   (CNENFSET = (1<<4))
#define SW2_InterruptDisable()  (CNENFCLR = (1<<4))

/*** Macros for SW1 pin ***/
#define SW1_Set()               (LATFSET = (1<<5))
#define SW1_Clear()             (LATFCLR = (1<<5))
#define SW1_Toggle()            (LATFINV= (1<<5))
#define SW1_OutputEnable()      (TRISFCLR = (1<<5))
#define SW1_InputEnable()       (TRISFSET = (1<<5))
#define SW1_Get()               ((PORTF >> 5) & 0x1)
#define SW1_PIN                  GPIO_PIN_RF5
#define SW1_InterruptEnable()   (CNENFSET = (1<<5))
#define SW1_InterruptDisable()  (CNENFCLR = (1<<5))

/*** Macros for SW0 pin ***/
#define SW0_Set()               (LATFSET = (1<<3))
#define SW0_Clear()             (LATFCLR = (1<<3))
#define SW0_Toggle()            (LATFINV= (1<<3))
#define SW0_OutputEnable()      (TRISFCLR = (1<<3))
#define SW0_InputEnable()       (TRISFSET = (1<<3))
#define SW0_Get()               ((PORTF >> 3) & 0x1)
#define SW0_PIN                  GPIO_PIN_RF3
#define SW0_InterruptEnable()   (CNENFSET = (1<<3))
#define SW0_InterruptDisable()  (CNENFCLR = (1<<3))

/*** Macros for LED2 pin ***/
#define LED2_Set()               (LATASET = (1<<2))
#define LED2_Clear()             (LATACLR = (1<<2))
#define LED2_Toggle()            (LATAINV= (1<<2))
#define LED2_OutputEnable()      (TRISACLR = (1<<2))
#define LED2_InputEnable()       (TRISASET = (1<<2))
#define LED2_Get()               ((PORTA >> 2) & 0x1)
#define LED2_PIN                  GPIO_PIN_RA2

/*** Macros for LED3 pin ***/
#define LED3_Set()               (LATASET = (1<<3))
#define LED3_Clear()             (LATACLR = (1<<3))
#define LED3_Toggle()            (LATAINV= (1<<3))
#define LED3_OutputEnable()      (TRISACLR = (1<<3))
#define LED3_InputEnable()       (TRISASET = (1<<3))
#define LED3_Get()               ((PORTA >> 3) & 0x1)
#define LED3_PIN                  GPIO_PIN_RA3

/*** Macros for LED4 pin ***/
#define LED4_Set()               (LATASET = (1<<4))
#define LED4_Clear()             (LATACLR = (1<<4))
#define LED4_Toggle()            (LATAINV= (1<<4))
#define LED4_OutputEnable()      (TRISACLR = (1<<4))
#define LED4_InputEnable()       (TRISASET = (1<<4))
#define LED4_Get()               ((PORTA >> 4) & 0x1)
#define LED4_PIN                  GPIO_PIN_RA4

/*** Macros for LED5 pin ***/
#define LED5_Set()               (LATASET = (1<<5))
#define LED5_Clear()             (LATACLR = (1<<5))
#define LED5_Toggle()            (LATAINV= (1<<5))
#define LED5_OutputEnable()      (TRISACLR = (1<<5))
#define LED5_InputEnable()       (TRISASET = (1<<5))
#define LED5_Get()               ((PORTA >> 5) & 0x1)
#define LED5_PIN                  GPIO_PIN_RA5

/*** Macros for LED6 pin ***/
#define LED6_Set()               (LATASET = (1<<6))
#define LED6_Clear()             (LATACLR = (1<<6))
#define LED6_Toggle()            (LATAINV= (1<<6))
#define LED6_OutputEnable()      (TRISACLR = (1<<6))
#define LED6_InputEnable()       (TRISASET = (1<<6))
#define LED6_Get()               ((PORTA >> 6) & 0x1)
#define LED6_PIN                  GPIO_PIN_RA6

/*** Macros for LED7 pin ***/
#define LED7_Set()               (LATASET = (1<<7))
#define LED7_Clear()             (LATACLR = (1<<7))
#define LED7_Toggle()            (LATAINV= (1<<7))
#define LED7_OutputEnable()      (TRISACLR = (1<<7))
#define LED7_InputEnable()       (TRISASET = (1<<7))
#define LED7_Get()               ((PORTA >> 7) & 0x1)
#define LED7_PIN                  GPIO_PIN_RA7


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA2 = 2,
    GPIO_PIN_RA3 = 3,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA5 = 5,
    GPIO_PIN_RA6 = 6,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA9 = 9,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC3 = 35,
    GPIO_PIN_RC4 = 36,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC14 = 46,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD0 = 48,
    GPIO_PIN_RD1 = 49,
    GPIO_PIN_RD2 = 50,
    GPIO_PIN_RD3 = 51,
    GPIO_PIN_RD4 = 52,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD6 = 54,
    GPIO_PIN_RD7 = 55,
    GPIO_PIN_RD8 = 56,
    GPIO_PIN_RD9 = 57,
    GPIO_PIN_RD10 = 58,
    GPIO_PIN_RD11 = 59,
    GPIO_PIN_RD12 = 60,
    GPIO_PIN_RD13 = 61,
    GPIO_PIN_RD14 = 62,
    GPIO_PIN_RD15 = 63,
    GPIO_PIN_RE0 = 64,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE2 = 66,
    GPIO_PIN_RE3 = 67,
    GPIO_PIN_RE4 = 68,
    GPIO_PIN_RE5 = 69,
    GPIO_PIN_RE6 = 70,
    GPIO_PIN_RE7 = 71,
    GPIO_PIN_RE8 = 72,
    GPIO_PIN_RE9 = 73,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RF2 = 82,
    GPIO_PIN_RF3 = 83,
    GPIO_PIN_RF4 = 84,
    GPIO_PIN_RF5 = 85,
    GPIO_PIN_RF6 = 86,
    GPIO_PIN_RF7 = 87,
    GPIO_PIN_RF8 = 88,
    GPIO_PIN_RF12 = 92,
    GPIO_PIN_RF13 = 93,
    GPIO_PIN_RG0 = 96,
    GPIO_PIN_RG1 = 97,
    GPIO_PIN_RG2 = 98,
    GPIO_PIN_RG3 = 99,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,
    GPIO_PIN_RG12 = 108,
    GPIO_PIN_RG13 = 109,
    GPIO_PIN_RG14 = 110,
    GPIO_PIN_RG15 = 111,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;

typedef  void (*GPIO_PIN_CALLBACK) ( GPIO_PIN pin, uintptr_t context);

void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortInterruptEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortInterruptDisable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: Local Data types and Prototypes
// *****************************************************************************
// *****************************************************************************

typedef struct {

    /* target pin */
    GPIO_PIN                 pin;

    /* Callback for event on target pin*/
    GPIO_PIN_CALLBACK        callback;

    /* Callback Context */
    uintptr_t               context;

} GPIO_PIN_CALLBACK_OBJ;

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInterruptEnable(GPIO_PIN pin)
{
    GPIO_PortInterruptEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInterruptDisable(GPIO_PIN pin)
{
    GPIO_PortInterruptDisable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

bool GPIO_PinInterruptCallbackRegister(
    GPIO_PIN pin,
    const   GPIO_PIN_CALLBACK callBack,
    uintptr_t context
);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
