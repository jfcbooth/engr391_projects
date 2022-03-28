#ifndef BT
#define BT

void UART_handler(void);
void setup_bt(void);
void parse_command(char command[3]);
void button_handler(char button);
void switch_handler(char side, char magnitude);


#endif