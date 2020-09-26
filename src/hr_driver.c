#include <stdbool.h>
#include <stdint.h>
#include "hr_driver.h"
#include "gpio_driver.h"
#include "utilities.h"

// Function should be called as many times as possible. In the future, a timer interrupt
// could be used to run this code.
cur_heart_rate_t get_hr_periodic(void)
{
    static uint8_t last_val = 10;
    static uint32_t last_millis = 0;
    static cur_heart_rate_t hr;

    // Rudimentary peak detection using a digital input and assuming
    // the heart rate sensor can give us a high or low value
    bool cur_val = read_gpio(gpio_heart_input);
    if (cur_val == 1 && last_val == 0)
    {
        hr.peak = 1;
        hr.hr = 60000/(millis() - last_millis);
        last_millis = millis();
    }

    else
    {
        hr.peak = 0;
    }

    last_val = cur_val;
    return hr;
}