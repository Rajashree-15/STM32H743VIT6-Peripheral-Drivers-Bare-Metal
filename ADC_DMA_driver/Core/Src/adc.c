#include "adc.h"

void adc_init(uint8_t channel, uint8_t sample_time)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_ADC12EN;
    (void)RCC->AHB1ENR;

    ADC12_COMMON->CCR = (1U << ADC_CCR_CKMODE_Pos);

    ADC1->CR &= ~ADC_CR_DEEPPWD;
    ADC1->CR |= ADC_CR_ADVREGEN;
    for (volatile int i = 0; i < 100000; i++) {}

    ADC1->CR &= ~ADC_CR_ADCALDIF;
    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL) {}

    ADC1->ISR = ADC_ISR_ADRDY;
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY)) {}

    ADC1->CFGR = (2U << ADC_CFGR_RES_Pos) | ADC_CFGR_CONT;

    if (channel < 10) {
        ADC1->SMPR1 = (ADC1->SMPR1 & ~(0x7U << (channel * 3)))
                    | ((uint32_t)sample_time << (channel * 3));
    } else {
        uint8_t pos = (channel - 10) * 3;
        ADC1->SMPR2 = (ADC1->SMPR2 & ~(0x7U << pos))
                    | ((uint32_t)sample_time << pos);
    }

    ADC1->PCSEL |= (1U << channel);
    ADC1->SQR1 = ((uint32_t)channel << ADC_SQR1_SQ1_Pos);
}

void adc_start_dma(volatile uint16_t *buffer, uint16_t length)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    (void)RCC->AHB1ENR;

    DMA1_Stream0->CR &= ~DMA_SxCR_EN;
    while (DMA1_Stream0->CR & DMA_SxCR_EN) {}
    DMA1->LIFCR = 0x3FU;

    DMA1_Stream0->PAR  = (uint32_t)&ADC1->DR;
    DMA1_Stream0->M0AR = (uint32_t)buffer;
    DMA1_Stream0->NDTR = length;

    DMA1_Stream0->CR = (1U << DMA_SxCR_PSIZE_Pos)
                     | (1U << DMA_SxCR_MSIZE_Pos)
                     | DMA_SxCR_MINC
                     | DMA_SxCR_CIRC;

    DMA1_Stream0->FCR = 0;
    DMAMUX1_Channel0->CCR = 9U;
    DMA1_Stream0->CR |= DMA_SxCR_EN;

    ADC1->CFGR |= (3U << ADC_CFGR_DMNGT_Pos);
    ADC1->CR |= ADC_CR_ADSTART;
}

void adc_stop(void)
{
    ADC1->CR |= ADC_CR_ADSTP;
    while (ADC1->CR & ADC_CR_ADSTP) {}
    DMA1_Stream0->CR &= ~DMA_SxCR_EN;
    while (DMA1_Stream0->CR & DMA_SxCR_EN) {}
}
