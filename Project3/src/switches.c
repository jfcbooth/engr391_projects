#include <xc.h>
#include "config/default/peripheral/gpio/plib_gpio.h"
#include "led.h"

GPIO_PIN switch_pin[] = {
    SW0_PIN,
    SW1_PIN,
    SW2_PIN,
    SW3_PIN,
    SW4_PIN,
    SW5_PIN,
    SW6_PIN,
    SW7_PIN
};

static void switch_handler(GPIO_PIN pin, uintptr_t context){
    if(switch_pin[0] == pin){
        led_set(0, SW0_Get());
    } else if(switch_pin[1] == pin){
        led_set(1, SW1_Get());
    }  else if(switch_pin[2] == pin){
        led_set(2, SW2_Get());
    }  else if(switch_pin[3] == pin){
        led_set(3, SW3_Get());
    }  else if(switch_pin[4] == pin){
        led_set(4, SW4_Get());
    }  else if(switch_pin[5] == pin){
        led_set(5, SW5_Get());
    }  else if(switch_pin[6] == pin){
        led_set(6, SW6_Get());
    }  else if(switch_pin[7] == pin){
        led_set(7, SW7_Get());
    }
}

void setup_switches(){
    for(int i = 0; i < 8; i++){
        GPIO_PinInterruptCallbackRegister(switch_pin[i], switch_handler, 0);
    }
    SW0_InterruptEnable();
    SW1_InterruptEnable();
    SW2_InterruptEnable();
    SW3_InterruptEnable();
    SW4_InterruptEnable();
    SW5_InterruptEnable();
    SW6_InterruptEnable();
    SW7_InterruptEnable();
}


// get the state of the switch and debounces it
int read_switch(int num){
    switch(num){
        case 1:
            return SW1_Get();
            break;
        case 2:
            return SW2_Get();
            break;
        case 3:
            return SW3_Get();
            break;
        case 4:
            return SW4_Get();
            break;
        case 5:
            return SW5_Get();
            break;
        case 6:
            return SW6_Get();
            break;
        case 7:
            return SW7_Get();
            break;
    }
    return 0;
}
