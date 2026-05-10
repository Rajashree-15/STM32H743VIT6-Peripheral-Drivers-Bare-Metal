/*
 * adc.h
 *
 *  Created on: May 3, 2026
 *      Author: rajashree
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32h743xx.h"
#include <stdint.h>

void adc_init(uint8_t channel, uint8_t sample_time);
void adc_start_dma(volatile uint16_t *buffer, uint16_t length);
void adc_stop(void);
uint8_t adc_dma_done(void);
void adc_dma_clear_flag(void);

#endif /* INC_ADC_H_ */
