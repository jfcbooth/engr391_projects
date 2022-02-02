#ifndef RGB_LED
#define RGB_LED

void set_color(int r, int g, int b);
void setup_rgb_leds();
void led_rgb_set(int color, int state);
void led_rgb_on(int color);
void led_rgb_off(int color);


#endif