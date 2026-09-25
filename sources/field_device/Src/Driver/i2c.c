#include "Driver/i2c.h"

#include "stm32c051xx.h"

void SYS_I2C_Init(void) {
	I2C1->CR1 &= ~(1U << I2C_CR1_PE_Pos);

	// set rate
	I2C1->TIMINGR = 0xB0420F13U;

	// turn on analog filter
	I2C1->CR1 &= ~(1U << I2C_CR1_ANFOFF_Pos);

	// enable
	I2C1->CR1 |= (1U << I2C_CR1_PE_Pos);
}