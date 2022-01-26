
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config/default/peripheral/gpio/plib_gpio.h"

void led_on(int led){
    switch(led){
        case 0:
            LED0_Set();
            break;
        case 1:
            LED1_Set();
            break;
        case 2:
            LED2_Set();
            break;
        case 3:
            LED3_Set();
            break;
        case 4:
            LED4_Set();
            break;
        case 5:
            LED5_Set();
            break;
        case 6:
            LED6_Set();
            break;
        case 7:
            LED7_Set();
            break;
    }
}

void led_off(int led){
    switch(led){
        case 0:
            LED0_Clear();
            break;
        case 1:
            LED1_Clear();
            break;
        case 2:
            LED2_Clear();
            break;
        case 3:
            LED3_Clear();
            break;
        case 4:
            LED4_Clear();
            break;
        case 5:
            LED5_Clear();
            break;
        case 6:
            LED6_Clear();
            break;
        case 7:
            LED7_Clear();
            break;
    }
}

// change led state
void led_set(int led, int state){
    if(state){
        led_on(led);
    } else {
        led_off(led);
    }
}

// toggle give led
void led_toggle(int led){
    switch(led){
        case 0:
            LED0_Toggle();
            break;
        case 1:
            LED1_Toggle();
            break;
        case 2:
            LED2_Toggle();
            break;
        case 3:
            LED3_Toggle();
            break;
        case 4:
            LED4_Toggle();
            break;
        case 5:
            LED5_Toggle();
            break;
        case 6:
            LED6_Toggle();
            break;
        case 7:
            LED7_Toggle();
            break;
    }}

void led_all_off(void){
    for(int i = 0; i < 8; i++){
        led_off(i);
    }}

void led_all_on(void){
    for(int i = 0; i < 8; i++){
        led_on(i);
    }
}
