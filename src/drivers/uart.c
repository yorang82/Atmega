/*
 * File: uart.c
 * Author: Young Kwan CHO, Lilith
 * Description: ATmega128 UART HAL Wrapper
 *              Provides simple TX-only UART for debugging/logging.
 */

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                               */
/* -------------------------------------------------------------------------- */
#include "uart.h"


#if (MCU_TYPE == MCU_ATMEGA128)
/* -------------------------------------------------------------------------- */
/*                               UART INIT                                    */
/* -------------------------------------------------------------------------- */
/**
 * @brief Initialize UART0
 *        Only TX is enabled (RX not required for debugging)
 */
void uartInit(uint32_t baud)
{
    uint16_t ubrr = (F_CPU / (16UL * baud)) - 1;

    UBRR0H = (ubrr >> 8);
    UBRR0L = (ubrr & 0xFF);

    UCSR0B = (1 << TXEN0);                    // Enable TX only
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // 8N1 mode
}

/* -------------------------------------------------------------------------- */
/*                               UART WRITE                                   */
/* -------------------------------------------------------------------------- */
/**
 * @brief Send one byte
 */
void uartWrite(char c)
{
    while (!(UCSR0A & (1 << UDRE0)));   // Wait until TX buffer empty
    UDR0 = c;
}

/* -------------------------------------------------------------------------- */
/*                            UART PRINT STRING                               */
/* -------------------------------------------------------------------------- */
/**
 * @brief Send null-terminated string
 */
void uartPrint(const char *str)
{
    while (*str)
        uartWrite(*str++);
}

#endif /* MCU_ATMEGA128 */
