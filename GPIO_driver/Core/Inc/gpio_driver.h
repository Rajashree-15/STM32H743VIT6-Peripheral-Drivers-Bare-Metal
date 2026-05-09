/*
 * gpio_driver.h
 *
 *  Created on: May 3, 2026
 *      Author: rajashree
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_

#include "stm32h743xx.h"
#include <stdint.h>

void gpio_clk(GPIO_TypeDef *port);
void gpio_cfg(GPIO_TypeDef *port, uint8_t pin, uint8_t mode, uint8_t af);
void gpio_set(GPIO_TypeDef *port, uint8_t pin);
void gpio_clr(GPIO_TypeDef *port, uint8_t pin);
void gpio_tog(GPIO_TypeDef *port, uint8_t pin);
uint8_t gpio_get(GPIO_TypeDef *port, uint8_t pin);

#endif /* INC_GPIO_DRIVER_H_ */
