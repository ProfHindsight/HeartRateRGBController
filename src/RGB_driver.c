#include "gpio_driver.h" 
#include "RGB_driver.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"

uint16_t brightness_red     = 0;
uint16_t brightness_green   = 0;
uint16_t brightness_blue    = 0;
uint16_t brightness_debug   = 0;

void *irq_effect();

// Create any time-dependent effects here.
void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        NVIC_ClearPendingIRQ(TIM2_IRQn);
    }

    (*irq_effect)();

}

void set_effect(RGB_Effect effect)
{
    switch(effect)
    {
        case effect_fadeout:
        irq_effect = effect_fadeout_fcn;
        break;
        case constant:
        irq_effect = effect_constant_fcn;

    }
}

void effect_constant_fcn(void)
{

}

void effect_fadeout_fcn(void)
{
    // After this, define what you want it to do
    
    if(brightness_red   != 0) 
    {
        brightness_red--  ;
    }
    if(brightness_green != 0) 
    {
        brightness_green--;
    }
    if(brightness_blue  != 0) 
    {
        brightness_blue-- ;
    }

    TIM_SetCompare1(TIM1, brightness_green * TIMER_PERIOD / 1000);
    TIM_SetCompare2(TIM1, brightness_red   * TIMER_PERIOD / 1000);
    TIM_SetCompare3(TIM1, brightness_blue  * TIMER_PERIOD / 1000);

    // You probably don't need to disable. Save the trees!
    if(
        brightness_green == 0 && 
        brightness_red == 0 && 
        brightness_blue == 0)
    {
        TIM_Cmd(TIM2, DISABLE);
    }
}

void RGB_init(void)
{
    // Enable the TIM1 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    // Set up the base timer 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = TIMER_PERIOD;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    // Configure all of the compare channels in one go
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

    // Configure the second timer and interrupt
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = SystemCoreClock/1500;
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
    brightness_red = red;
    brightness_green = green;
    brightness_blue = blue;
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    NVIC_ClearPendingIRQ(TIM2_IRQn);
    TIM_Cmd(TIM2, ENABLE);
}

/*
Set the value between 0 and 1000 to set the compare channel.
*/
void write_debug_led(uint16_t brightness)
{
    TIM_SetCompare4(TIM1, brightness * TIMER_PERIOD / 1000);
}