#include "gpio_driver.h" 
#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"
#include "RGB_driver.h"

void RGB_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = TIMER_PERIOD;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/*
Set the value between 0 and 1000 to set the compare channels.
*/
void write_RGB(uint16_t red, uint16_t green, uint16_t blue)
{
	TIM_SetCompare1(TIM1, green*TIMER_PERIOD/1000);
	TIM_SetCompare2(TIM1, red*TIMER_PERIOD/1000);
	TIM_SetCompare3(TIM1, blue*TIMER_PERIOD/1000);
}


/*
Set the value between 0 and 1000 to set the compare channel.
*/
void write_debug_led(uint16_t brightness)
{
	TIM_SetCompare4(TIM1, brightness*TIMER_PERIOD/1000);
}