#include "gpio_driver.h" 
#include <stdio.h>
#include <stdbool.h>
#include "utilities.h"
#include "stm32f0xx_conf.h"
#include "RGB_driver.h"


int main(void)
{
    SystemInit();
    gpio_init();
    utilities_init();
    send_string("Starting RGB_Init\n");
    RGB_init();

    // // Example usage
    send_string("Writing RGBs\n");
    RGB_write(5,1000,100);
    write_debug_led(1000);
    delayMs(1000);
    write_debug_led(0);
    delayMs(1000);
    write_debug_led(1000);
    
    uint8_t last_hr = 0;
    uint8_t cur_hr = 0;
    RGB_set_effect(RGB_effect_fadeout);
    send_string("Entering While Loop\n");
    while(1)
    {

        RGB_write(1000, 0, 0);
        delayMs(1000);
        RGB_write(0, 1000, 0);
        delayMs(1000);
        RGB_write(0, 0, 1000);
        delayMs(1000);

    }
}
