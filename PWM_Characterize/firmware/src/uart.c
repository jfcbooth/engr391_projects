#include "config/default/peripheral/uart/plib_uart1.h"
#include <string.h>

char cmd[100];

void UART1_handler(void){
    UART1_Write(cmd, 100);
}

//void setup_uart(void){
//    UART1_ReadCallbackRegister( (UART_CALLBACK) UART1_handler, (uintptr_t)NULL);
//    UART1_Write(cmd, 100);
//}

void set_command(char my_cmd[100]){
    strncpy(cmd, my_cmd, 100);
}