#ifndef MOTORS
#define MOTORS

void timer4_handler(uint32_t status, uintptr_t context);
void setup_motors(void);
void disable_motors(void );
void set_direction(int left, int right);
void set_speed(int left, int right);

#endif