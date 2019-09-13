#define TIMER_PERIOD 1024

void RGB_init(void);
void write_RGB(uint16_t red, uint16_t green, uint16_t blue);
void write_debug_led(uint16_t brightness);

// effects
void set_effect(void* fcnHandle);
void effect_fadeOut(void);
