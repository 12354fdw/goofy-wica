#include "init.h"
#include "Driver/rf.h"
#include "hal.h"
#include "stm32c051xx.h"

#include <stdint.h>
#include <stdio.h>

#define UART_BAUD 115200u
#define HSI16_HZ 48000000u

void init(void) {
	// port remap
	HAL_Peripheral_EnableClock(HAL_PERIPH_SYSCFG);
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_RMP | SYSCFG_CFGR1_PA12_RMP;
	
	// init logging
	HAL_GPIO_EnableClock(GPIOA);
	HAL_Peripheral_EnableClock(HAL_PERIPH_USART1);

	// set PA9 to AF1 (USART1_TX)
	HAL_GPIO_Init(GPIOA, 9, GPIO_MODE_AF, GPIO_PULL_UP);
	HAL_GPIO_AF_Init(GPIOA, 9, 1);

	// set PA10 to AF1 (USART1_RX)
	HAL_GPIO_Init(GPIOA, 10, GPIO_MODE_AF, GPIO_PULL_UP);
	HAL_GPIO_AF_Init(GPIOA, 10, 1);

	USART1->BRR = HSI16_HZ / UART_BAUD;
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

	printf("hello\r\n");

	printf("init peripherals...");

	// SPI1 for RF
	HAL_Peripheral_EnableClock(HAL_PERIPH_SPI1);

	printf("ok\r\n");

	// actual init
	printf("init pins...");

	SYS_RF_InitPins();

	printf("ok\r\n");
}

int _write(int file, char *ptr, int len) {
	(void)file;
	for (int i = 0; i < len; i++) {
		while (!(USART1->ISR & USART_ISR_TXE_TXFNF))
			;
		USART1->TDR = ptr[i];
	}
	return len;
}