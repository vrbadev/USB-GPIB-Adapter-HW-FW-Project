#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f103x6.h"

typedef struct {
	GPIO_TypeDef* base;
	uint8_t pin;
} pin_t;


#define GPIO_CNF_INPUT_ANALOG 0
#define GPIO_CNF_INPUT_FLOATING 1
#define GPIO_CNF_INPUT_PULL_DOWN 2
#define GPIO_CNF_INPUT_PULL_UP 3

#define GPIO_CNF_OUTPUT_GENERAL_PUSH_PULL 0
#define GPIO_CNF_OUTPUT_GENERAL_OPEN_DRAIN 1
#define GPIO_CNF_OUTPUT_ALTERNATE_PUSH_PULL 2
#define GPIO_CNF_OUTPUT_ALTERNATE_OPEN_DRAIN 3

#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT_10MHZ 1
#define GPIO_MODE_OUTPUT_2MHZ 2
#define GPIO_MODE_OUTPUT_50MHZ 3

#define PA0 ((pin_t) {.base = GPIOA, .pin = 0})
#define PA1 ((pin_t) {.base = GPIOA, .pin = 1})
#define PA2 ((pin_t) {.base = GPIOA, .pin = 2})
#define PA3 ((pin_t) {.base = GPIOA, .pin = 3})
#define PA4 ((pin_t) {.base = GPIOA, .pin = 4})
#define PA5 ((pin_t) {.base = GPIOA, .pin = 5})
#define PA6 ((pin_t) {.base = GPIOA, .pin = 6})
#define PA7 ((pin_t) {.base = GPIOA, .pin = 7})
#define PA8 ((pin_t) {.base = GPIOA, .pin = 8})
#define PA9 ((pin_t) {.base = GPIOA, .pin = 9})
#define PA10 ((pin_t) {.base = GPIOA, .pin = 10})
#define PA11 ((pin_t) {.base = GPIOA, .pin = 11})
#define PA12 ((pin_t) {.base = GPIOA, .pin = 12})
#define PA13 ((pin_t) {.base = GPIOA, .pin = 13})
#define PA14 ((pin_t) {.base = GPIOA, .pin = 14})
#define PA15 ((pin_t) {.base = GPIOA, .pin = 15})

#define PB0 ((pin_t) {.base = GPIOB, .pin = 0})
#define PB1 ((pin_t) {.base = GPIOB, .pin = 1})
#define PB2 ((pin_t) {.base = GPIOB, .pin = 2})
#define PB3 ((pin_t) {.base = GPIOB, .pin = 3})
#define PB4 ((pin_t) {.base = GPIOB, .pin = 4})
#define PB5 ((pin_t) {.base = GPIOB, .pin = 5})
#define PB6 ((pin_t) {.base = GPIOB, .pin = 6})
#define PB7 ((pin_t) {.base = GPIOB, .pin = 7})
#define PB8 ((pin_t) {.base = GPIOB, .pin = 8})
#define PB9 ((pin_t) {.base = GPIOB, .pin = 9})
#define PB10 ((pin_t) {.base = GPIOB, .pin = 10})
#define PB11 ((pin_t) {.base = GPIOB, .pin = 11})
#define PB12 ((pin_t) {.base = GPIOB, .pin = 12})
#define PB13 ((pin_t) {.base = GPIOB, .pin = 13})
#define PB14 ((pin_t) {.base = GPIOB, .pin = 14})
#define PB15 ((pin_t) {.base = GPIOB, .pin = 15})

#define PC13 ((pin_t) {.base = GPIOC, .pin = 13})
#define PC14 ((pin_t) {.base = GPIOC, .pin = 14})
#define PC15 ((pin_t) {.base = GPIOC, .pin = 15})

void gpio_init(void);
void gpio_mode(pin_t pin, uint8_t mode, uint8_t cnf);
void gpio_write(pin_t pin, uint8_t val);
void gpio_toggle(pin_t pin);
uint8_t gpio_read(pin_t pin);

#endif
