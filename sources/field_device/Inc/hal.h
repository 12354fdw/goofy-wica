#ifndef HAL_H
#define HAL_H

#include "stm32c051xx.h"
#include <stdint.h>

#define BUS_IOPENR 0U
#define BUS_APBENR1 1U
#define BUS_APBENR2 2U

#define PERIPH_ID(bus, mask) (((bus) << 24) | (mask))

typedef enum {
	HAL_PERIPH_USART1 = PERIPH_ID(BUS_APBENR2, RCC_APBENR2_USART1EN),
	HAL_PERIPH_USART2 = PERIPH_ID(BUS_APBENR1, RCC_APBENR1_USART2EN),
	HAL_PERIPH_SPI1 = PERIPH_ID(BUS_APBENR2, RCC_APBENR2_SPI1EN),
	HAL_PERIPH_SPI2 = PERIPH_ID(BUS_APBENR1, RCC_APBENR1_SPI2EN),
	HAL_PERIPH_I2C1 = PERIPH_ID(BUS_APBENR1, RCC_APBENR1_I2C1EN),
	HAL_PERIPH_I2C2 = PERIPH_ID(BUS_APBENR1, RCC_APBENR1_I2C2EN),
	HAL_PERIPH_SYSCFG = PERIPH_ID(BUS_APBENR2, RCC_APBENR2_SYSCFGEN)
} HAL_Peripheral_t;

typedef enum {
	GPIO_MODE_INPUT = 0,
	GPIO_MODE_OUTPUT = 1,
	GPIO_MODE_AF = 2,
	GPIO_MODE_ANALOG = 3
} GPIOMode_t;

typedef enum {
	GPIO_PULL_NONE = 0,
	GPIO_PULL_UP = 1,
	GPIO_PULL_DOWN = 2
} GPIOPull_t;

void HAL_GPIO_EnableClock(GPIO_TypeDef *GPIOx);
void HAL_Peripheral_EnableClock(HAL_Peripheral_t periph_id);

	void
	HAL_GPIO_Init(GPIO_TypeDef *GPIOx, uint32_t pin, GPIOMode_t mode,
				  GPIOPull_t pull);

void HAL_GPIO_AF_Init(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t af_num);

inline void HAL_GPIO_WriteHigh(GPIO_TypeDef *GPIOx, uint32_t pin) {
	GPIOx->BSRR = (1U << pin);
}

inline void HAL_GPIO_WriteLow(GPIO_TypeDef *GPIOx, uint32_t pin) {
	GPIOx->BSRR = (1U << (pin + 16));
}

inline void HAL_GPIO_Toggle(GPIO_TypeDef *GPIOx, uint32_t pin) {
	GPIOx->ODR ^= (1U << pin);
}

inline uint8_t HAL_GPIO_Read(GPIO_TypeDef *GPIOx, uint32_t pin) {
	return (uint8_t)((GPIOx->IDR >> pin) & 1U);
}

#endif