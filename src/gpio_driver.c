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
  gpio_debug_rx     ,
  gpio_debug_tx     ,
  gpio_clk_lfxo1    , // I don't remember if I have this
  gpio_clk_lfxo2    , // I don't remember if I have this
  gpio_swclk        ,
  gpio_swdio        ,
  gpio_nrst         ,
  gpio_swo      
}gpio_pins_t;
*/

const gpio_struct_t gpio_pin_mapping[] = {
  {GPIOA, GPIO_Pin_11, 0x01, 0x00},
  {GPIOB, GPIO_Pin_8, 0x02, GPIO_AF_1},  // gpio_i2c_scl   - D15
  {GPIOB, GPIO_Pin_9, 0x02, GPIO_AF_1},  // gpio_i2c_sda   - D14
  {GPIOA, GPIO_Pin_9, 0x01, 0x00},     // gpio_i2c_power   - D8
  {GPIOA, GPIO_Pin_6, 0x02, GPIO_AF_0},  // gpio_nrf24_miso  - D12
  {GPIOA, GPIO_Pin_7, 0x02, GPIO_AF_0},  // gpio_nrf24_mosi  - D11
  {GPIOA, GPIO_Pin_5, 0x02, GPIO_AF_0},  // gpio_nrf24_clk - D13
  {GPIOB, GPIO_Pin_6, 0x02, GPIO_AF_0},  // gpio_nrf24_cs  - D10
  {GPIOC, GPIO_Pin_7, 0x01, 0x00},  // gpio_nrf24_ce  - D9
  {GPIOA, GPIO_Pin_8, 0x01, 0x00},     // gpio_nrf24_power - D7
  {GPIOB, GPIO_Pin_10, 0x01, 0x00},    // gpio_nrf24_pa_en - D6
  {GPIOA, GPIO_Pin_0, 0x03, 0x00},     // gpio_bat_detect  - A0
  {GPIOA, GPIO_Pin_3, 0x02, GPIO_AF_1},  // gpio_debug_rx  - D0
  {GPIOA, GPIO_Pin_2, 0x02, GPIO_AF_1}   // gpio_debug_tx  - D1
};

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

void gpio_driver_init(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  for(int i = 0; i < sizeof(gpio_pin_mapping)/sizeof(gpio_pin_mapping[0]); i++)
  {
    gpio_struct_t my_pin = gpio_pin_mapping[i];
    GPIO_InitTypeDef pin_def = {my_pin.gpio_pin,          // Pin number
                                my_pin.gpio_af_selection, // Pin Mode
                                GPIO_Speed_10MHz,         // Pin Speed
                                GPIO_OType_PP,            // Output Type
                                GPIO_PuPd_NOPULL};        // Pull Direction
    GPIO_Init(my_pin.gpio_port, &pin_def);
    if(my_pin.gpio_mode == (0x02)) GPIO_PinAFConfig(my_pin.gpio_port,
      gpiopin_to_gpiopinsource(my_pin.gpio_pin),
      my_pin.gpio_af_selection);
  }
}

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
