#include "config/default/peripheral/gpio/plib_gpio.h"
#include "config/default/peripheral/tmr/plib_tmr4.h"

#define MIN_SPEED_VALUE 100
#define SPEED_LEVEL_MULTIPLIER 15.5

int leftSpeed = 0; // 0-255 scale for pwm
int rightSpeed = 0;


void timer4_handler(uint32_t status, uintptr_t context){
    static int counter = 0; // value between 0-255

    if(counter < leftSpeed){
        leftEn_Set();
    } else {
        leftEn_Clear();
    }
    
    if(counter < rightSpeed){
        rightEn_Set();
    } else {
        rightEn_Clear();
    }
    counter = counter >= 255 ? 0 : counter+1;
}

void setup_motors(void){
    TMR4_CallbackRegister(timer4_handler, (uintptr_t)NULL);
    TMR4_InterruptEnable();
    TMR4_Start();
}

void disable_motors(void ){
    // disable motors
    rightEn_Clear();
    leftEn_Clear();
}

// 1 = forwards, -1 = backwards (defaults to forward)
void set_direction(int left, int right){
    disable_motors(); // always disable motors before changing direction to prevent a short
    if(left == -1){
        leftDir_Clear();
    } else{
        leftDir_Set();
    }
    
    if(right == -1){
        rightDir_Set();
    } else{
        rightDir_Clear();
    }    
}

// speeds level from 0-10
void set_speed(int left, int right){
    left = (left < 0) ? 0 : (left > 10) ? 10 : left;
    right = (right < 0) ? 0 : (right > 10) ? 10 : right;
    leftSpeed = (int)(MIN_SPEED_VALUE + (left*SPEED_LEVEL_MULTIPLIER)); // makes value between 100-255
    rightSpeed = (int)(MIN_SPEED_VALUE + (right*SPEED_LEVEL_MULTIPLIER)); // makes value between 100-255
}
