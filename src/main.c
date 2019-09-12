#include <stdio.h>
#include <stdbool.h>

#include "gpio_driver.h"
#include "RGB_driver.h"
#include "stm32f0xx_conf.h"
#include "stm32f0xx_tim.h"
#include "utilities.h"

int main(void)
{
    SystemInit();
    gpio_init();
    utilities_init();
    RGB_init();

    // Example usage
    send_string("Hello World!\n");
    write_RGB(250,1000,750);
    write_debug_led(1000);

    while (1);
}
