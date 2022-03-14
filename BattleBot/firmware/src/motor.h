#ifndef MOTORS
#define MOTORS

void timer4_handler(uint32_t status, uintptr_t context);
void setup_motors(void);
void movement_disable_motors(void );
void movement_set_direction(int left, int right);
void set_speed(int left, int right);
void pause_tmr4(void);
void resume_tmr4(void);
void attack_disable_motors(void );
void attack_set_speed(int left, int right);
void attack_set_direction(int dir);

#endif