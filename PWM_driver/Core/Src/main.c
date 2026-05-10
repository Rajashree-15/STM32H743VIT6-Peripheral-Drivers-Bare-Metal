#include "stm32h743xx.h"
#include "gpio_driver.h"
#include "adc.h"

static volatile uint16_t adc_buf[16] __attribute__((aligned(4)));

int main(void)
{
    gpio_clk(GPIOE);
    gpio_cfg(GPIOE, 3, 0x1, 0);

    gpio_clk(GPIOB);
    gpio_cfg(GPIOB, 0, 0x1, 0);
    gpio_set(GPIOB, 0);

    gpio_clk(GPIOA);
    gpio_cfg(GPIOA, 3, 0x3, 0);

    adc_init(15, 7);
    adc_start_dma(adc_buf, 16);

    for (volatile int i = 0; i < 500000; i++) {}

    while (1)
    {
    	while (1)
    	    {
    	        gpio_set(GPIOB, 0);
    	        for (volatile int i = 0; i < 500000; i++) {}

    	        if (adc_buf[0] > 2000)
    	            gpio_set(GPIOE, 3);
    	        else
    	            gpio_clr(GPIOE, 3);

    	        for (volatile int i = 0; i < 500000; i++) {}

    	        gpio_clr(GPIOB, 0);
    	        for (volatile int i = 0; i < 500000; i++) {}

    	        if (adc_buf[0] > 2000)
    	            gpio_set(GPIOE, 3);
    	        else
    	            gpio_clr(GPIOE, 3);

    	        for (volatile int i = 0; i < 500000; i++) {}
    	    }
    }
}
