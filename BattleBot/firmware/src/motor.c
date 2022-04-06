#include "config/default/peripheral/gpio/plib_gpio.h"
#include "config/default/peripheral/tmr/plib_tmr4.h"
#include "config/default/peripheral/tmr1/plib_tmr1.h"

#define MIN_SPEED_VALUE 60
#define MAX_SPEED_VALUE 150
#define SPEED_INCREMENTS 8
#define SPEED_LEVEL_MULTIPLIER (MAX_SPEED_VALUE-MIN_SPEED_VALUE)/SPEED_INCREMENTS
#define CHOP_ROTARY_COUNT 25
#define AXE_SPEED_VALUE 128
#define AXE_SETTLE_TIME 100

int leftSpeed = 0; // 0-255 scale for pwm
int rightSpeed = 0;
int axeSpeed = 0;
volatile int time_expired = 0;
int overflows = 0;

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
    
    if(counter < axeSpeed){
        axeEn_Set();
    } else {
        axeEn_Clear();
    }
    
    counter = counter >= 255 ? 0 : counter+1;
}

void timer1_handler(uint32_t status, uintptr_t context){
    if(overflows < 5){
        overflows++;
    } else { // 1 second has passed
        TMR1_Stop();
        overflows = 0;
        time_expired = 1;
    }
}

void setup_motors(void){
    TMR4_CallbackRegister(timer4_handler, (uintptr_t)NULL);
    TMR4_InterruptEnable();
    TMR4_Start();
    
    TMR1_CallbackRegister(timer1_handler, (uintptr_t)NULL);
    TMR1_InterruptEnable();
}

// 1 = forwards, -1 = backwards (defaults to forward)
void movement_set_direction_left(int dir){
    TMR4_Stop();
    leftEn_Clear();
    if(dir == -1){
        leftDir_Clear();
    } else{
        leftDir_Set();
    }
    TMR4_Start();
}

void movement_set_direction_right(int dir){
    TMR4_Stop();
    rightEn_Clear();
    if(dir == -1){
        rightDir_Set();
    } else{
        rightDir_Clear();
    }
    TMR4_Start();
}
// values between 0 - SPEED_INCREMEBTS
void movement_set_speed_left(int speed){
    TMR4_Stop();
    speed = (speed < 0) ? 0 : (speed > SPEED_INCREMENTS) ? SPEED_INCREMENTS : speed;
    leftSpeed = (speed==0) ? 0 : (int)(MIN_SPEED_VALUE + (speed*SPEED_LEVEL_MULTIPLIER)); // makes value between 100-255
    TMR4_Start();
}

void movement_set_speed_right(int speed){
    TMR4_Stop();
    speed = (speed < 0) ? 0 : (speed > SPEED_INCREMENTS) ? SPEED_INCREMENTS : speed;
    rightSpeed = (speed==0) ? 0 : (int)(MIN_SPEED_VALUE + (speed*SPEED_LEVEL_MULTIPLIER)); // makes value between 100-255
    TMR4_Start();
}



// **********************************
// ATTACK MOTOR FUNCTIONS
// **********************************

// speeds level from 0-1
void attack_set_speed(int speed){
    TMR4_Stop();
    if(speed == 1){
        axeSpeed = AXE_SPEED_VALUE;
    } else{
        axeSpeed = 0;
    }
    TMR4_Start();
}

// 1 = forwards, -1 = backwards (defaults to forward)
void attack_set_direction(int dir){
    TMR4_Stop();
        axeEn_Clear(); // always disable motors before changing direction to prevent a short

    if(dir == -1){
        axeDir_Clear();
    } else{
        axeDir_Set();
    }    
    TMR4_Start();
}

/* CP0.Count counts at half the CPU rate */
#define TICK_HZ (CPU_HZ / 2)

void delay_us(unsigned int us)
{
    // Convert microseconds us into how many clock ticks it will take
    us *= 80000000 / 1000000 / 2; // Core Timer updates every 2 ticks

    _CP0_SET_COUNT(0); // Set Core Timer count to 0

    while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}

void delay_ms(int ms)
{
    delay_us(ms * 1000);
}

void attack_down(void){
    attack_set_direction(1); // set direction to down
    int count = 0; // # of steps
    int en1 = 0; // value of encoder 1
    attack_set_speed(1); // turn on attack
    overflows = 0; // reset overflows for 1 second timeout timer
    TMR1_Start(); // start 1 second timer
    while(time_expired == 0 && count < CHOP_ROTARY_COUNT){
        int val = axeSensorB_Get();
        if(val != en1){
            en1 = val;
            count++;
        }
    }
    TMR1_Stop();
    time_expired = 0; // reset the timer
    attack_set_speed(0); // stop after down attack
    delay_ms(AXE_SETTLE_TIME); // wait 1 second
}

void attack_up(void){
    attack_set_direction(-1); // set direction to go up
    int count = 0;
    int en1 = 0;
    attack_set_speed(1); // start pulling back up
    overflows = 0; // reset overflows for 1 second timeout timer
    TMR1_Start();
    while(time_expired == 0 && count < (CHOP_ROTARY_COUNT + 10)){
        int val = axeSensorB_Get();
        if(val != en1){
            en1 = val;
            count++;
        }
    }
    TMR1_Stop();
    time_expired = 0;
    attack_set_speed(0); // stop after top has been reached 
    delay_ms(AXE_SETTLE_TIME);
}

void attack_chop(void){
    attack_down();
    attack_up();
}

void attack_spam(void){
    int i = 0;
    while(i < 5){
        attack_chop();
        i++;
    }
}