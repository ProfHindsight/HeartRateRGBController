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
    RGB_init();

    // // Example usage
    send_string("Hello World\n");
    write_RGB(250,1000,750);
    write_debug_led(1000);
    delayMs(1000);
    write_debug_led(0);
    delayMs(1000);
    write_debug_led(1000);
    
    uint8_t last_hr = 0;
    uint8_t cur_hr = 0;
    while(1)
    {
        // Look for a rising edge
        cur_hr = read_gpio(gpio_heart_input);
        if(cur_hr == 1 && last_hr == 0)
        {
            write_RGB(1000,0,0);
        }
        last_hr = cur_hr;
        delayMs(1);
    }
}
