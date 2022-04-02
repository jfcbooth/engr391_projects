#ifndef MOTORS
#define MOTORS

void timer4_handler(uint32_t status, uintptr_t context);
void setup_motors(void);
void movement_disable_motors(void );
void movement_set_direction_left(int dir);
void movement_set_direction_right(int dir);
void movement_set_speed_left(int speed);
void movement_set_speed_right(int speed);
void attack_disable_motors(void);
void attack_set_speed(int speed);
void attack_set_direction(int dir);
void attack_down(void);
void attack_up(void);
void attack_chop(void);
void attack_spam(void);

#endif