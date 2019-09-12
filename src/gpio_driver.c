/**
  *
  * @file    gpio_driver.c
  * @author  ProfHindsight
  * @version x
  * @date    11/11/2018
  * @brief   This is a gpio driver. It's mostly GPIO mapping.
  * Keep in mind you should update the gpio_driver thing as well.
  */
#include "gpio_driver.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include <stdbool.h>

/*
typedef enum gpio_pins
{
  gpio_debug_led    ,
  gpio_red_led      ,
  gpio_green_led    ,
  gpio_blue_led     , // I don't remember these pins
  gpio_nrf24_miso   ,
  gpio_nrf24_mosi   ,
  gpio_nrf24_clk    ,
  gpio_nrf24_cs     ,
  gpio_nrf24_ce     ,
  gpio_nrf24_int    ,
  gpio_debug_rx     ,
  gpio_debug_tx     ,
  gpio_heart_input  , 
}gpio_pins_t;
*/

// This might be better as some kind of define to reduce code size
const gpio_struct_t gpio_pin_mapping[] = {
  {GPIOA, GPIO_Pin_11, 0x02, GPIO_AF_2},
  {GPIOA, GPIO_Pin_9, 0x02, GPIO_AF_2},  // RED PWM - A9 - TIM1CH2
  {GPIOA, GPIO_Pin_8, 0x02, GPIO_AF_2},  // GREEN PWM - A8 - TIM1CH1
  {GPIOA, GPIO_Pin_10, 0x02, GPIO_AF_2},  // BLUE PWM - A10 - TIM1CH3
  {GPIOA, GPIO_Pin_6, 0x02, GPIO_AF_0},  // NRF24 MISO
  {GPIOA, GPIO_Pin_7, 0x02, GPIO_AF_0},  // NRF24 MOSI
  {GPIOA, GPIO_Pin_5, 0x02, GPIO_AF_0},  // NRF24 CLK
  {GPIOA, GPIO_Pin_4, 0x02, GPIO_AF_0},  // NRF24 CS
  {GPIOA, GPIO_Pin_2, 0x01, 0x00},  // NRF24 CE
  {GPIOA, GPIO_Pin_3, 0x00, 0x00},  // NRF24 INT
  {GPIOB, GPIO_Pin_7, 0x02, GPIO_AF_0},  // UART RX
  {GPIOB, GPIO_Pin_6, 0x02, GPIO_AF_0},  // UART TX
  {GPIOB, GPIO_Pin_0, 0x00, 0x00},  // Heart Input (ADC8, TIM3CH3, GPIO)
};


// Used by gpio_init to do something. Not used anywhere else, so don't worry abou tit.
int gpiopin_to_gpiopinsource(int input)
{
  if(input == 0) return 0;
  int index = 0;
  while(index < 16)
    {
      if((input & 0x01) == 1) return index;
      index++;
      input = input >> 1;
    }
  return index;
}


// I wanted a way to be able to define each pin and then this script would
// set up each pin. Not very size efficient.
void gpio_init(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  for(int i = 0; i < sizeof(gpio_pin_mapping)/sizeof(gpio_pin_mapping[0]); i++)
  {
    gpio_struct_t my_pin = gpio_pin_mapping[i];
    GPIO_InitTypeDef pin_def = {my_pin.gpio_pin,          // Pin number
                                my_pin.gpio_mode,         // Pin Mode
                                GPIO_Speed_50MHz,         // Pin Speed
                                GPIO_OType_PP,            // Output Type
                                GPIO_PuPd_UP};        // Pull Direction
    GPIO_Init(my_pin.gpio_port, &pin_def);
    if(my_pin.gpio_mode == (0x02)) GPIO_PinAFConfig(my_pin.gpio_port,
      gpiopin_to_gpiopinsource(my_pin.gpio_pin),
      my_pin.gpio_af_selection);
  }
}


// I also wanted a way to abstract the pin port and value.
void write_gpio(gpio_pins_t gpio_pin, bool value)
{
  gpio_struct_t my_pin = gpio_pin_mapping[gpio_pin];
  GPIO_WriteBit(my_pin.gpio_port, my_pin.gpio_pin, value);
}

bool read_gpio(gpio_pins_t gpio_pin)
{
  gpio_struct_t my_pin = gpio_pin_mapping[gpio_pin];
	return GPIO_ReadInputDataBit(my_pin.gpio_port, my_pin.gpio_pin);
}
