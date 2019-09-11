// #include "stm32f0xx_conf.h"
#include "gpio_driver.h" 
// #include <stdio.h>
// #include <stdbool.h>
#include "utilities.h"
#include "stm32f0xx_conf.h"

// void extern delayMs(uint32_t ms);


// This is mostly for debugging, will move to utilities.c
void SysTick_Handler(void) {
  static uint16_t tick = 0;

  switch (tick++){
  	case 100:
  		write_gpio(gpio_debug_led, 0);
  		// write_gpio(gpio_debug_tx, 0);
  		break;
	case 200:
		write_gpio(gpio_debug_led, 1);
		// write_gpio(gpio_debug_tx, 1);
		tick = 0;
		send_string("HI");
		break;
  }
}

int main(void)
{
	SystemInit();
	gpio_init();
	utilities_init();

	while(1);

}