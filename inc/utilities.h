// #include "stm32f0xx_rcc.h"
// #include "stm32f0xx.h"

void delayMs(uint32_t ms_delay);
void utilities_init(void);
void send_string(char*);
uint32_t millis(void);

int16_t map(int16_t value, int16_t from_low, 
    int16_t from_high, int16_t to_low, int16_t to_high);