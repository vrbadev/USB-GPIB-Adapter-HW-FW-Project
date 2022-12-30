#include "gpio.h"

void gpio_init(void)
{	
	// Enable clock to GPIO peripherals
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Disable JTAG to release PB3, PB4
	DBGMCU->CR &= ~DBGMCU_CR_TRACE_IOEN;
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
}

void gpio_mode(pin_t pin, uint8_t mode, uint8_t cnf)
{
	uint8_t pinnum = (pin.pin > 7) ? (pin.pin-8) : pin.pin;
	__IO uint32_t* reg = (pin.pin > 7) ? &(pin.base->CRH) : &(pin.base->CRL);
	
	*reg &= ~(3 << 4*pinnum);
	*reg &= ~(3 << (4*pinnum+2));
	*reg |= (mode << 4*pinnum);
	if (cnf >= GPIO_CNF_OUTPUT_ALTERNATE_PUSH_PULL) {
		*reg |= (2 << (4*pinnum+2));
		if (cnf == GPIO_CNF_OUTPUT_ALTERNATE_PUSH_PULL) {
			pin.base->ODR &= ~(1 << pin.pin);
		} else {
			pin.base->ODR |= (1 << pin.pin);
		}
	} else {
		*reg |= (cnf << (4*pinnum+2));
	}
}

void gpio_write(pin_t pin, uint8_t val)
{
	pin.base->ODR &= ~(1 << pin.pin);
	if (val) pin.base->ODR |= (val << pin.pin);
}

void gpio_toggle(pin_t pin)
{
	pin.base->ODR ^= (1 << pin.pin);
}

uint8_t gpio_read(pin_t pin)
{
	return ((pin.base->IDR & (1 << pin.pin)) == 0) ? 0 : 1;
}
