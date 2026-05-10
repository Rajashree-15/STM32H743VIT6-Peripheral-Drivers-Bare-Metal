/*
 * pwm.h
 *
 *  Created on: May 3, 2026
 *      Author: rajashree
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "stm32h743xx.h"
#include <stdint.h>

void pwm_init(uint16_t prescaler, uint16_t period);
void pwm_set_duty(uint16_t duty);
void pwm_stop(void);

#endif /* INC_PWM_H_ */
