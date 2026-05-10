#include "gpio_driver.h"

void gpio_clk(GPIO_TypeDef *port)
{
    uint8_t pos = ((uint32_t)port - GPIOA_BASE) / 0x400U;
    RCC->AHB4ENR |= (1U << pos);
    (void)RCC->AHB4ENR;
}

void gpio_cfg(GPIO_TypeDef *port, uint8_t pin, uint8_t mode, uint8_t af)
{
    if (port == GPIOA && (pin == 13 || pin == 14)) return;
    port->MODER = (port->MODER & ~(0x3U << (pin * 2))) | (mode << (pin * 2));
    if (mode == 0x2U) {
        uint8_t r = pin / 8, s = (pin % 8) * 4;
        port->AFR[r] = (port->AFR[r] & ~(0xFU << s)) | ((uint32_t)af << s);
    }
}

void gpio_set(GPIO_TypeDef *port, uint8_t pin) { port->BSRR = (1U << pin); }
void gpio_clr(GPIO_TypeDef *port, uint8_t pin) { port->BSRR = (1U << (pin + 16)); }
void gpio_tog(GPIO_TypeDef *port, uint8_t pin) { port->ODR ^= (1U << pin); }
uint8_t gpio_get(GPIO_TypeDef *port, uint8_t pin) { return (port->IDR >> pin) & 1U; }