// #include "stm32f0xx_conf.h"
// #include "gpio_driver.h" 
// #include <stdio.h>
// #include <stdbool.h>
// #include "utilities.h"

// void extern delayMs(uint32_t ms);

// int main(void)
// {
//   gpio_driver_init();

//   utilities_init();

// 	while(1)
// 	{
// 		for(volatile int i = 0; i < 10000000; i++);
// 		write_gpio(gpio_debug_led, 1);
// 		for(volatile int i = 0; i < 10000000; i++);
// 		write_gpio(gpio_debug_led, 0);
// 	}
// }

#include "stm32f0xx_conf.h"

void SysTick_Handler(void) {
  static uint16_t tick = 0;

  switch (tick++) {
  	case 100:
  		tick = 0;
  		GPIOA->ODR ^= (1 << 11);
  		break;
  }
}

int main(void)
{

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 	// enable the clock to GPIOA
						//(RM0091 lists this as IOPCEN, not GPIOCEN)

	// Set PA11 to output
	GPIOA->MODER &= ~(3 << 22);
	GPIOA->MODER |= (1 << 22);

	SysTick_Config(SystemCoreClock/100);

	while(1);

}