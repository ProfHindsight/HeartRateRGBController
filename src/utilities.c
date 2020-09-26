#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "utilities.h"
#include "stdbool.h"


volatile uint32_t msTicks = 0;

void delayMs(uint32_t ms_delay)
{
    unsigned long startTicks = msTicks;
    while ((msTicks - startTicks) < ms_delay);
}

void SysTick_Handler(void) {
    ++msTicks;
}

uint32_t millis()
{
    return msTicks;
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

// inline function to swap two numbers
inline void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

// function to reverse buffer[i..j]
char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

// Iterative function to implement itoa() function in C
char* itoa(int value, char* buffer, int base)
{
	// invalid input
	if (base < 2 || base > 32)
		return buffer;

	// consider absolute value of number
	int n = value;
    if (n < 0) n = n * -1;

	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10) 
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	// if number is 0
	if (i == 0)
		buffer[i++] = '0';

	// If base is 10 and value is negative, the resulting string 
	// is preceded with a minus sign (-)
	// With any other base, value is always considered unsigned
	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(buffer, 0, i - 1);
}

void send_stringln(char *string)
{
    send_string(string);
    send_string("\n");
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


int16_t map(int16_t value, int16_t from_low, 
    int16_t from_high, int16_t to_low, int16_t to_high)
{
    return (value - from_low) * (to_high - to_low) / (from_high - from_low) + to_low;
}