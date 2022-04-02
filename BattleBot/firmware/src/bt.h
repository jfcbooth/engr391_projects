#ifndef BT
#define BT

void UART_handler(void);
void setup_bt(void);
void parse_command(void);
void button_handler(char button);
void switch_handler(char side, char magnitude);
void q_add(char c);
char q_pop();
int q_empty();

#endif