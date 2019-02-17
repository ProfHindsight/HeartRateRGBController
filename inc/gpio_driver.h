/**
  *
  * @file    gpio_driver.h
  * @author  ProfHindsight
  * @version x
  * @date    11/10/2018
  * @brief   This is a gpio driver. It's mostly GPIO mapping. 
  */

// The STM32F030K6T6 has 26 I/O
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include <stdbool.h>

/*
I have:
One debug uart
One debug LED
Three PWM LEDs
One Analog/Digital Input
Pins for future nRF24L01 integration (yea right)
*/
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


/*
* This is just a struct to keep track of all the GPIO information.
* Alternatively, you could initialize gpios for each function,
* i.e. initialize the ADC pin for the ADC driver
*/
typedef struct gpio_struct
{
	GPIO_TypeDef * gpio_port;
	uint16_t gpio_pin;
	GPIOMode_TypeDef gpio_mode; 
	uint8_t gpio_af_selection;
}gpio_struct_t;


/*
* Self-explanatory gpio functions
*/
void gpio_driver_init(void);
void write_gpio(gpio_pins_t gpio_pin, bool value);
bool read_gpio(gpio_pins_t gpio_pin);
