#ifndef LEDS
#define LEDS

void led_on(int led);
void led_off(int led);
void led_set(int led, int state);
void led_toggle(int led);
void led_all_off(void);
void led_all_on(void);

#endif