#define TIMER_PERIOD 1000

typedef enum RGB_Effect {
	RGB_effect_fadeout = 0,
	RGB_effect_constant = 1} RGB_Effect_t;

void RGB_init(void);
void RGB_write(uint16_t red, uint16_t green, uint16_t blue);
void write_debug_led(uint16_t brightness);
void RGB_set_effect(RGB_Effect_t effect);