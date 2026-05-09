#include "stm32h743xx.h"
#include "gpio_driver.h"

int main(void)
{
    gpio_clk(GPIOE);
    gpio_cfg(GPIOE, 2, 0x1, 0);

    while (1)
    {
        gpio_tog(GPIOE, 2);
        for (volatile int i = 0; i < 500000; i++) {}
    }
}
