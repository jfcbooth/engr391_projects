#include "config/default/peripheral/uart/plib_uart1.h"
#include "config/default/peripheral/gpio/plib_gpio.h"
#include "motor.h"


char command[3];

void button_handler(char button){
    switch(button){
        case 'A': // attack down
            attack_set_direction(1);
            attack_set_speed(1);
            // delay
            attack_set_speed(0);
            break;
        case 'B': // attack up
            attack_set_direction(-1);
            attack_set_speed(1);
            // delay
            attack_set_speed(0);
            break;
        case 'C':
            break;
        case 'D':
            break;
    }
}



void switch_handler(char side, char magnitude){
    int mag_int = (int)magnitude-'0';
    int direction = (mag_int<4) ? -1 : 1;
    int speed = (mag_int>4) ? mag_int-4 :
                (mag_int==3) ? 1 :
                (mag_int==2) ? 2 :
                (mag_int==1) ? 3 :
                (mag_int==0) ? 4 : 0;
  
    switch(side){
        case 'L':
            movement_set_direction_left(direction);
            movement_set_speed_left(speed);
            break;
        case 'R':
            movement_set_direction_right(direction);
            movement_set_speed_right(speed);
            break;
    }
}

void parse_command(char command[3]){
    switch(command[0]){
        case 'B':
            button_handler(command[1]);
            break;
        case 'S':
            switch_handler(command[1], command[2]);
            break;
    }
}

void UART_handler(void){
    parse_command(command);
    UART1_Write(command, 3);
    UART1_Read(command, 3);
}

void setup_bt(void){
    UART1_ReadCallbackRegister( (UART_CALLBACK) UART_handler, (uintptr_t)NULL);
    UART1_Read(command, 3);
}