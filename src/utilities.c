#include "utilities.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
// #include <stdio.h>
// #include <stdarg.h>

// volatile uint32_t msTicks = 0;

// void delayMs(uint32_t ms_delay)
// {
// 	unsigned long startTicks = msTicks;
// 	while((msTicks - startTicks) < ms_delay);
// }


// void SysTick_Handler(void) {
// 	msTicks++;
// } 

void utilities_init()
{
	// Initialize Systick
	SysTick_Config(SystemCoreClock/100);

  // Initialize UART
  	RCC_APB2PeriphClockCmd(RCC_APB2ENR_USART1EN, ENABLE);
	USART_InitTypeDef usart_init;
	USART_StructInit(&usart_init);
	usart_init.USART_BaudRate = 115200;
	USART_Init(USART1, &usart_init);
	USART_Cmd(USART1, ENABLE);
}

// We're just going to block for now. 
// Move to DMA once we know it works this way
void send_string(char * string)
{
      while (*string != 0)
      {
            if (*string == '\n')
            {
            	USART_SendData(USART1, '\r');
            }
            USART_SendData(USART1, (uint16_t) *string++);
      }
}
 
// void print(const char* format, ...)
// {
//     char       msg[130];
//     va_list    args;
 
//     va_start(args, format);
//     vsnprintf(msg, sizeof(msg), format, args); // do check return value
//     va_end(args);
 
//     send_string(msg);
// }



// #ifdef __GNUC__
//    // With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
//      // set to 'Yes') calls __io_putchar() 
//   #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
// #else
//   #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
// #endif /* __GNUC__ */

// *
//   * @brief  Retargets the C library printf function to the USART.
//   * @param  None
//   * @retval None
  
// PUTCHAR_PROTOTYPE
// {
//   /* Place your implementation of fputc here 
//    e.g. write a character to the USART */
//   USART_SendData(USART1, (uint8_t) ch);

//   /* Loop until transmit data register is empty */
//   while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//   {}

//   return ch;
// }