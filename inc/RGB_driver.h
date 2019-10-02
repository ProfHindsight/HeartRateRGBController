#define TIMER_PERIOD 1024

enum RGB_Effect {effect_fadeout, constant};

void RGB_init(void);
void write_RGB(uint16_t red, uint16_t green, uint16_t blue);
void write_debug_led(uint16_t brightness);

// effects
void set_effect(RGB_Effect effect);