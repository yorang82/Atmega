/*
 * File: uart.h
 * Author: Young Kwan CHO, Lilith
 * Description: ATmega128 UART HAL Wrapper
 *              Minimal TX-only UART for debugging/log output.
 */

#ifndef UART_H_
#define UART_H_

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                               */
/* -------------------------------------------------------------------------- */
#include "def.h"


/* -------------------------------------------------------------------------- */
/*                                API PROTOTYPES                              */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize UART0 with given baudrate.
 *
 * @param baud Baudrate (ex: 38400, 9600)
 */
void uartInit(uint32_t baud);

/**
 * @brief Transmit one character
 */
void uartWrite(char c);

/**
 * @brief Transmit null-terminated string
 */
void uartPrint(const char *str);

#endif /* UART_H_ */
