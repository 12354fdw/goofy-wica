/**
 * @file    init.c
 * @brief   System and peripheral initialization.
 *
 * Debug UART: USART2 on PA2 (TX) / PA3 (RX), 115200 8N1.
 * The MCU boots on HSI16 (16 MHz), which the UART baud rate uses.
 */
#include "init.h"

#include <stdint.h>

#include "stm32c051xx.h"

#define UART_BAUD 115200u
#define HSI16_HZ  16000000u

void uart_init(void) {
	// TODO: impl this
}