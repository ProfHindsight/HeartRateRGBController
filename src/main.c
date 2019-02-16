#include "stm32f0xx_conf.h"
#include "gpio_driver.h"

void SysTick_Handler(void) {
  static uint16_t tick = 0;

  switch (tick++) {
  	case 100:
  		tick = 0;
  		GPIOC->ODR ^= (1 << 8);
  		break;
  }
}

int main(void)
{
  gpio_init();

	SysTick_Config(SystemCoreClock/100);

	while(1);

}
