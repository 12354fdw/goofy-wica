#include "Driver/spi.h"
#include "stm32c051xx.h"

void SYS_SPI_Init(void) {

	// clear and fill out Config Register 1
	SPI1->CR1 = 0;

	SPI1->CR1 |= (1U << SPI_CR1_MSTR_Pos) | (3U << SPI_CR1_BR_Pos) |
				 (1U << SPI_CR1_SSM_Pos) | (1U << SPI_CR1_SSI_Pos);

	// clear and fill out Config Register 2
	SPI1->CR2 = 0;
	SPI1->CR2 |= (7U << SPI_CR2_DS_Pos) | (1U << SPI_CR2_FRXTH_Pos);

	// enable
	SPI1->CR1 |= (1U << SPI_CR1_SPE_Pos);
}