
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

// setup LEDs as outputs
void led_init(void){
    TRISACLR = 0xff; // set bottom 8 bits to 0
}

// change led state
void led_set(int led, int state){
    if(state){
        LATASET = (0x1 << led);
    } else {
        LATACLR = (0x1 << led);
    }
}

// toggle give led
void led_toggle(int led){
    LATAINV = (0x1 << led);
}

void led_all_off(void){
    LATACLR = 0xff;
}

void led_all_on(void){
    LATASET = 0xff;
}
