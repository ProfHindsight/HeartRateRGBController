#include "stm32f0xx_conf.h"
#include "gpio_driver.h" 
#include <stdio.h>
#include <stdbool.h>
#include "utilities.h"

void extern delayMs(uint32_t ms);

int main(void)
{
  gpio_driver_init();

  utilities_init();

	while(1);
}
