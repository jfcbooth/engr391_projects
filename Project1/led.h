#ifndef LEDS
#define LEDS

void led_init(void); // setup LEDs for controlling the display
void led_set(int led, int state);
void led_toggle(int led);
void led_all_off(void);
void led_all_on(void);

#endif