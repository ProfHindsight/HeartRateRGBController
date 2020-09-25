#include "gpio_driver.h" 
#include <stdio.h>
#include <stdbool.h>
#include "utilities.h"
#include "stm32f0xx_conf.h"
#include "RGB_driver.h"
#include "hr_driver.h"

// define heart rate values
#define HR_LOW 60
#define HR_HIGH 120
#define LED_MAX 1000

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
    cur_heart_rate_t hr = get_hr_periodic();

    while(1)
    {
        hr = get_hr_periodic();
        if(hr.peak == 1)
        {
            // Determine red value, LED_MAX if 120
            int32_t red = map(hr.hr, HR_LOW, HR_HIGH, 0, LED_MAX);

            // HR may be outside [60, 120] so correct if needed
            if(red < 0) red = 0;
            if(red > LED_MAX) red = LED_MAX;
            
            // Determine green value, LED_MAX if 60, 0 if 120
            int32_t green = map(hr.hr, HR_HIGH, HR_LOW, 0, LED_MAX);
            if(green < 0) green = 0;
            if(green > LED_MAX) green = LED_MAX;

            // Write RGB values
            RGB_write(red, green, 0);
        }
        delayMs(10);
    }
}
