
#define DEBOUNCE_US 150

#ifndef CPU_HZ
#define CPU_HZ 80000000
#endif

#include <xc.h>

// setup switches as inputs
void switch_init(void){
    TRISFSET = 0x001c;
    TRISDSET = 0xc000;
    TRISBSET = 0x0e00;
    ANSELBCLR = 0x0e00;
}

// get the state of the switch and debounces it
int read_switch(int num){
    switch(num){
        case 0:
            return PORTFbits.RF3;
            break;
        case 1:
            return PORTFbits.RF5;
            break;
        case 2:
            return PORTFbits.RF4;
            break;
        case 3:
            return PORTDbits.RD15;
            break;
        case 4:
            return PORTDbits.RD14;
            break;
        case 5:
            return PORTBbits.RB11;
            break;
        case 6:
            return PORTBbits.RB10;
            break;
        case 7:
            return PORTBbits.RB9;
            break;
    }
    return 0;
}

//    int US_time = DEBOUNCE_US * CPU_HZ; // converts US to time per instr
//    int x = 0;
//    int last_switch = 0;
//    while(x < US_time){
//        last_switch = PORTFbits.RF3; // read SW0
//        for(x = 0; x < US_time; x++){
//            if(PORTFbits.RF3 != last_switch){
//                break;
//            }
//        }
//    }
//    return last_switch;
//    return
//}
