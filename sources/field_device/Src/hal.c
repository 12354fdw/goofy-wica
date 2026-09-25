#include "hal.h"

void HAL_GPIO_EnableClock(GPIO_TypeDef *GPIOx) {
	if (GPIOx == GPIOA) {
		RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	} else if (GPIOx == GPIOB) {
		RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	} else if (GPIOx == GPIOC) {
		RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
	} else if (GPIOx == GPIOD) {
		RCC->IOPENR |= RCC_IOPENR_GPIODEN;
	}
}

void HAL_Peripheral_EnableClock(HAL_Peripheral_t periph_id) {
	uint32_t enable_mask = periph_id & 0x00FFFFFFU;

	switch (periph_id >> 24) {
	case BUS_IOPENR:
		RCC->IOPENR |= enable_mask;
		break;
	case BUS_APBENR1:
		RCC->APBENR1 |= enable_mask;
		break;
	case BUS_APBENR2:
		RCC->APBENR2 |= enable_mask;
		break;
	}
}

void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, uint32_t pin, GPIOMode_t mode,
					   GPIOPull_t pull) {

	// clear and set MODE
	GPIOx->MODER &= ~(3U << (pin * 2));
	GPIOx->MODER |= ((uint32_t)mode << (pin * 2));

	// clear and set PULL UP / DOWN
	GPIOx->PUPDR &= ~(3U << (pin * 2));
	GPIOx->PUPDR |= ((uint32_t)pull << (pin * 2));
}

void HAL_GPIO_AF_Init(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t af_num) {
	if (pin < 8) {

		// clear and set LOW AF Registers
		GPIOx->AFR[0] &= ~(0xFU << (pin * 4));
		GPIOx->AFR[0] |= (af_num << (pin * 4));
	} else {
		uint32_t high_pin_pos = pin - 8;

		// clear and set HIGH AF Registers
		GPIOx->AFR[1] &= ~(0xFU << (high_pin_pos * 4));
		GPIOx->AFR[1] |= (af_num << (high_pin_pos * 4));
	}
}