/*
 * pwm.c
 *
 *  Created on: May 3, 2026
 *      Author: rajashree
 */


#include "pwm.h"

void pwm_init(uint16_t prescaler, uint16_t period)
{
    // TIM1 clock enable — APB2
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    (void)RCC->APB2ENR;

    // Stop timer while configuring
    TIM1->CR1 = 0;

    // Prescaler and period
    TIM1->PSC = prescaler;
    TIM1->ARR = period;
    TIM1->CCR1 = 0;

    // PWM mode 1 on channel 1: high while CNT < CCR1
    // OC1PE = preload enable (duty changes take effect at next cycle)
    TIM1->CCMR1 = (6U << TIM_CCMR1_OC1M_Pos) | TIM_CCMR1_OC1PE;

    // Enable channel 1 output, active high
    TIM1->CCER = TIM_CCER_CC1E;

    // Main Output Enable — TIM1 is advanced timer
    // Without this line, output stays high-impedance
    TIM1->BDTR |= TIM_BDTR_MOE;

    // Load shadow registers
    TIM1->EGR = TIM_EGR_UG;

    // Auto-reload preload + start counter
    TIM1->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
}

void pwm_set_duty(uint16_t duty)
{
    TIM1->CCR1 = duty;
}

void pwm_stop(void)
{
    TIM1->CR1 &= ~TIM_CR1_CEN;
    TIM1->BDTR &= ~TIM_BDTR_MOE;
}
