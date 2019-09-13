#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "utilities.h"


volatile uint32_t msTicks = 0;

void delayMs(uint32_t ms_delay)
{
    unsigned long startTicks = msTicks;
    while ((msTicks - startTicks) < ms_delay);
}

void SysTick_Handler(void) {
    ++msTicks;
}

void utilities_init()
{
    // Initialize Systick
    SysTick_Config(SystemCoreClock / 1000);

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
void send_string(char *string)
{
    while (*string != 0)
    {
        while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
        USART_SendData(USART1, (uint16_t) *string++);
    }
}
