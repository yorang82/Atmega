/*
 * File: delay.h
 * Author: Young Kwan CHO, Lilith
 * Description: MCU-independent delay and timing API
 *              ATmega128 Timer1-based implementation.
 */

#ifndef DELAY_H_
#define DELAY_H_
/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                               */
/* -------------------------------------------------------------------------- */
#include "def.h"


/* -------------------------------------------------------------------------- */
/*                                API PROTOTYPES                              */
/* -------------------------------------------------------------------------- */
void delayInit(void);
uint32_t millis(void);
uint32_t micros(void);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);


#endif /* DELAY_H_ */
