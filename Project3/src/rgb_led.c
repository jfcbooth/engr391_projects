
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config/default/peripheral/gpio/plib_gpio.h"
#include "config/default/peripheral/tmr/plib_tmr5.h"
#include "config/default/peripheral/tmr/plib_tmr4.h"

enum colors{
    R,G,B
};

static int accumulator[3] = {0,0,0};
static int color_intensity[3] = {0,0,0};

void set_color(int r, int g, int b){
    color_intensity[R] = (r>255) ? 255 : (r<0) ? 0 : r;
    color_intensity[G] = (g>255) ? 255 : (g<0) ? 0 : g;
    color_intensity[B] = (b>255) ? 255 : (b<0) ? 0 : b;
}

int in_range(int intensity){
   return (color_intensity[intensity] >= 0 && color_intensity[intensity] <= 255);
}

void led_rgb_on(int color){
    switch(color){
        case R:
            LED_R_Set();
            break;
        case G:
            LED_G_Set();
            break;
        case B:
            LED_B_Set();
            break;     
    }
}

void led_rgb_off(int color){
    switch(color){
        case R:
            LED_R_Clear();
            break;
        case G:
            LED_G_Clear();
            break;
        case B:
            LED_B_Clear();
            break;     
    }
}


void led_rgb_set(char color, int state){
    if (state){
        led_rgb_on(color);
    } else {
        led_rgb_off(color);
    }
}

 void timer_handler(uint32_t status, uintptr_t context){
     for(int i = 0; i < 3; i++){
         accumulator[i] += color_intensity[i];
         led_rgb_set(i, (accumulator[i] >> 8) & 0x01);
         accumulator[i] = accumulator[i] & 0xff;
     }
}

void timer4_handler(uint32_t status, uintptr_t context){
    static int state = 0;
    static int intensity = 0;
    switch(state){
        case 0:
            if(intensity < 255){
                set_color(intensity, 0, 255-intensity);
                intensity++;
            } else {
                state=1;
                intensity = 0;
            }
            break;
        case 1:
            if(intensity < 255){
                set_color(255-intensity, intensity, 0);
                intensity++;
            } else {
                state=2;
                intensity = 0;
            }
            break;
        case 2:
            if(intensity < 255){
                set_color(0, 255-intensity, intensity);
                intensity++;
            } else {
                state=0;
                intensity = 0;
            }
            break;

    }
//    switch(state){
//        case 0:
//            if(state_calls < 255){
//                color_intensity[R] = in_range(color_intensity[R]) ? color_intensity[R]+1 : 255;
//                color_intensity[B] = in_range(color_intensity[B]) ? color_intensity[B]-1 : 0;
//            } else {
//                state = 1;
//            }
//        case 1:
//            if(color_intensity[G] < 255){
//                color_intensity[G] = in_range(color_intensity[G]) ? color_intensity[G]+1 : 255;
//                color_intensity[R] = in_range(color_intensity[R]) ? color_intensity[R]-1 : 0;
//            } else {
//                state = 2;
//            }
//        case 2: 
//            if(color_intensity[B] < 255){
//                color_intensity[B] = in_range(color_intensity[B]) ? color_intensity[B]+1 : 255;
//                color_intensity[R] = in_range(color_intensity[R]) ? color_intensity[R]-1 : 0;
//            } else {
//                state = 0;
//            }
//    }
}

 
void setup_rgb_leds(){
    TMR5_CallbackRegister(timer_handler, (uintptr_t)NULL);
    TMR4_CallbackRegister(timer4_handler, (uintptr_t)NULL);
    TMR5_InterruptEnable();
    TMR4_InterruptEnable();
    TMR5_Start();
    TMR4_Start();
}

