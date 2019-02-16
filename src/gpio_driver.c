#include "gpio_driver.h"
#include "stm32f0xx_conf.h"

void gpio_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 	// enable the clock to GPIOC
						//(RM0091 lists this as IOPCEN, not GPIOCEN)

	GPIOC->MODER = (1 << 16);
}