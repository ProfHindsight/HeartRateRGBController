#include "gpio_driver.h" 
#include "RGB_driver.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"
#include "utilities.h"

uint16_t brightness_red     = 0;
uint16_t brightness_green   = 0;
uint16_t brightness_blue    = 0;
uint16_t brightness_debug   = 0;

void effect_constant_fcn(void);
void effect_fadeout_fcn(void);
void (*irq_effect)(void);

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

void RGB_set_effect(RGB_Effect_t effect)
{
    switch(effect)
    {
        case RGB_effect_fadeout:
        irq_effect = &effect_fadeout_fcn;
        break;
        case RGB_effect_constant:
        irq_effect = &effect_constant_fcn;

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

    TIM_SetCompare1(TIM1, brightness_green);
    TIM_SetCompare2(TIM1, brightness_red);
    TIM_SetCompare3(TIM1, brightness_blue);

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
    // Set the effect first things first
    irq_effect = &effect_constant_fcn;

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

    // Figure out the prescalar and time period for the second timer
    // Target: 1 kHz interrupts
    // Clock is something like 48 MHz
    // Setting 1,000 for the prescalar should give a min freq of 48 kHz
    // and max freq of like over 1 second.
    // For the time period, we will set it to 1 kHz. The fade effect should last 1 second then.
    int16_t prescalar = 1000;
    int16_t period = 48;

    // Configure the second timer and interrupt
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Prescaler = prescalar;
    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM_Cmd(TIM2, ENABLE);
}

/*
Set the value between 0 and 1000 to set the compare channels.
*/
void RGB_write(uint16_t red, uint16_t green, uint16_t blue)
{
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    NVIC_ClearPendingIRQ(TIM2_IRQn);
    brightness_red = red;
    brightness_green = green;
    brightness_blue = blue;
    TIM_SetCompare1(TIM1, green);
    TIM_SetCompare2(TIM1, red);
    TIM_SetCompare3(TIM1, blue);
    TIM_Cmd(TIM2, ENABLE);
}

/*
Set the value between 0 and 1000 to set the compare channel.
*/
void write_debug_led(uint16_t brightness)
{
    TIM_SetCompare4(TIM1, brightness * TIMER_PERIOD / 1000);
}