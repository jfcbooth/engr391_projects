#include "config/default/peripheral/uart/plib_uart2.h"
#include "config/default/peripheral/gpio/plib_gpio.h"
#include "motor.h"

#define QUEUE_LEN 15
#define L_BIAS_VALUE 10

char command[3];

// poor man's circular queue
char button_queue[QUEUE_LEN+1];
// location to add an item
static int q_index = 0;
// action that has been processed
static int q_action_index = 0;

// shift through the queue positions
void q_action_advance(){
    q_action_index = (q_action_index > QUEUE_LEN) ? 0 : q_action_index+1;
}

void q_index_advance(){
    q_index = (q_index > QUEUE_LEN) ? 0 : q_index+1;
}

void q_add(char c){
    button_queue[q_index] = c; // add a button to the queue
    q_index_advance(); // move the to next position
}

// return the item in queue
char q_pop(){
    char to_return = button_queue[q_action_index];
    button_queue[q_action_index] = 0;
    q_action_advance(); // say an action has been processed
    return to_return;
}

// checks if there is an item in the queue
int q_empty(){
    if(q_index == q_action_index){
            return 1;
    }
    return 0;
}

void button_handler(char button){
    switch(button){
        case 'A': // attack down
            q_add('A');
            break;
        case 'B': // attack up
            q_add('B');
            break;
        case 'C':
            q_add('C');
            break;
        case 'D':
            q_add('D');
            break;
    }
}

static int direction = 1; // start forward

// for L & R independent controls, using the entire range for forward
// and a button to put it into reverse mode
void switch_handler_forward(char side, char magnitude){
    movement_set_direction_left(direction);
    movement_set_direction_right(direction);
    int mag_int = (int)magnitude-'0';

    switch(side){
        case 'L':
            movement_set_speed_left(mag_int);
            break;
        case 'R':
            movement_set_speed_right(mag_int);
            break;
    }
}

void change_direction(void){
    if(direction == 1){
        direction = -1;
    }else {
        direction = 1;
    }
}

// for L & R independent controls
void switch_handler_independent(char side, char magnitude){
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


// one slides handles forward/backward, one handles L+R
void switch_handler_straight(char side, char magnitude){
    int mag_int = (int)magnitude-'0';
    int direction = (mag_int<4) ? -1 : 1;
    int speed = (mag_int>4) ? mag_int-4 :
                (mag_int==3) ? 1 :
                (mag_int==2) ? 2 :
                (mag_int==1) ? 3 :
                (mag_int==0) ? 4 : 0;
  
    switch(side){
        case 'L': // straight / backwards
            movement_set_direction_left(direction);
            movement_set_direction_right(direction);
            movement_set_speed_left(speed + L_BIAS_VALUE);
            movement_set_speed_right(speed);
            break;
        case 'R':

            break;
    }
}
void parse_command(void){
    switch(command[0]){
        case 'B':
            button_handler(command[1]);
            break;
        case 'S':
            switch_handler_forward(command[1], command[2]);
            break;
    }
}

void UART_handler(void){
    parse_command();
    //UART2_Write(command, 3);
    UART2_Read(command, 3);
}

void setup_bt(void){
    UART2_ReadCallbackRegister( (UART_CALLBACK) UART_handler, (uintptr_t)NULL);
    UART2_Read(command, 3);
}