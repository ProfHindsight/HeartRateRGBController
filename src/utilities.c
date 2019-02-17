#include "utilities.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
#include <stdio.h>
#include <stdarg.h>

volatile uint32_t msTicks = 0;

void delayMs(uint32_t ms_delay)
{
	unsigned long startTicks = msTicks;
	while((msTicks - startTicks) < ms_delay);
}


void SysTick_Handler(void) {
	msTicks++;
} 

void utilities_init()
{

	SysTick_Config(SystemCoreClock/1000);

  // Initialize UART
	USART_InitTypeDef usart_init;
	usart_init.USART_BaudRate = 115200;
	USART_StructInit(&usart_init);
	USART_Init(DEBUG_UART, &usart_init);
}

// We're just going to block for now. 
// Move to DMA once we know it works this way
void send_string(char * string)
{
      while (*string != 0)
      {
            if (*string == '\n')
            {
            	USART_SendData(DEBUG_UART, '\r');
            }
            USART_SendData(DEBUG_UART, (uint16_t) *string++);
      }
}
 
void print(const char* format, ...)
{
    char       msg[130];
    va_list    args;
 
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args); // do check return value
    va_end(args);
 
    send_string(msg);
}