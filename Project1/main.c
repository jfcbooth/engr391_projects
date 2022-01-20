
#pragma config FNOSC = FRCPLL
#pragma config FSOSCEN = OFF
#pragma config POSCMOD = XT //set clock src as external 8Mhz crystal
#pragma config OSCIOFNC = ON
#pragma config FPBDIV = DIV_1
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1

#pragma config JTAGEN = OFF

#define CPU_MHZ 80
#define CPU_HZ CPU_MHZ*1000000
#define NUM_SWITCHES 8
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "led.h"
#include "timing.h"
#include "switches.h"


int main(int argc, char** argv) {
    led_init();
    switch_init();
    led_all_off();
    while(1){
        for(int i = 0; i < NUM_SWITCHES; i++){
            led_set(i, read_switch(i));
        }
    }
    return (EXIT_SUCCESS);
}