#include "config/default/peripheral/gpio/plib_gpio.h"
#include "config/default/peripheral/tmr/plib_tmr4.h"

#define MIN_SPEED_VALUE 100
#define MAX_SPEED_VALUE 255
#define SPEED_INCREMENTS 4
#define SPEED_LEVEL_MULTIPLIER (MAX_SPEED_VALUE-MIN_SPEED_VALUE)/SPEED_INCREMENTS
#define CHOP_ROTARY_COUNT 80
int leftSpeed = 0; // 0-255 scale for pwm
int rightSpeed = 0;
int axeSpeed = 0;


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

void setup_motors(void){
    TMR4_CallbackRegister(timer4_handler, (uintptr_t)NULL);
    TMR4_InterruptEnable();
    TMR4_Start();
}

void movement_disable_motors(void){
    // disable motors
    rightEn_Clear();
    leftEn_Clear();
}

// 1 = forwards, -1 = backwards (defaults to forward)
void movement_set_direction_left(int dir){
    TMR4_Stop();
    movement_disable_motors(); // always disable motors before changing direction to prevent a short
    if(dir == -1){
        leftDir_Clear();
    } else{
        leftDir_Set();
    }
    TMR4_Start();
}

void movement_set_direction_right(int dir){
    if(dir == -1){
        rightDir_Set();
    } else{
        rightDir_Clear();
    }
}

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

void attack_disable_motors(void ){
    // disable motors
    axeEn_Clear();
}


// speeds level from 0-1
void attack_set_speed(int speed){
    TMR4_Stop();
    if(speed == 1){
        axeSpeed = MAX_SPEED_VALUE;
    } else{
        axeSpeed = 0;
    }
    TMR4_Start();
}

// 1 = forwards, -1 = backwards (defaults to forward)
void attack_set_direction(int dir){
    TMR4_Stop();
    attack_disable_motors(); // always disable motors before changing direction to prevent a short

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


void attack_chop(void){
    attack_set_direction(1); // go down
    int count = 0;
    int en1 = 0;
    attack_set_speed(1); // turn on attack
    while(count < CHOP_ROTARY_COUNT){
        int val = axeSensorB_Get();
        if(val != en1){
            en1 = val;
            count++;
        }
    }
    attack_set_speed(0); // stop after down attack
    delay_ms(1000);
    attack_set_direction(-1); // set direction to go up
    count = 0;
    en1 = 0;
    attack_set_speed(1); // start pulling back up
    while(count < CHOP_ROTARY_COUNT){
        int val = axeSensorB_Get();
        if(val != en1){
            en1 = val;
            count++;
        }
    }
    attack_set_speed(0); // stop after top has been reached 
}