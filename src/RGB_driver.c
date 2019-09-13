#include "gpio_driver.h" 
#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"
#include "RGB_driver.h"

volatile uint16_t brightness = 0;

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        NVIC_ClearPendingIRQ(TIM2_IRQn);
    }
    uint16_t cur1 = TIM_GetCapture1(TIM1);
    uint16_t cur2 = TIM_GetCapture1(TIM1);
    uint16_t cur3 = TIM_GetCapture1(TIM1);
    
    if(cur1 != 0) cur1--;
    if(cur2 != 0) cur2--;
    if(cur3 != 0) cur3--;

    TIM_SetCompare1(TIM1, cur1);
    TIM_SetCompare2(TIM1, cur2);
    TIM_SetCompare3(TIM1, cur3);

    if(cur1 == 0 && cur2 == 0 && cur3 == 0)
    {
        TIM_Cmd(TIM2, DISABLE);
    }
}


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
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = SystemCoreClock/1000;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM_Cmd(TIM2, ENABLE);
}

/*
Set the value between 0 and 1000 to set the compare channels.
*/
void write_RGB(uint16_t red, uint16_t green, uint16_t blue)
{
    TIM_SetCompare1(TIM1, green);
    TIM_SetCompare2(TIM1, red);
    TIM_SetCompare3(TIM1, blue);
}


/*
Set the value between 0 and 1000 to set the compare channel.
*/
void write_debug_led(uint16_t brightness)
{
    TIM_SetCompare4(TIM1, brightness);
}
