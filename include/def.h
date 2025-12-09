/*
 * File: def.h
 * Author: Young Kwan CHO, Lilith
 * Description:
 *   Global common definitions for cross-MCU HAL Layer.
 *   All driver headers must include ONLY this file.
 */

#ifndef DEF_H_
#define DEF_H_

/* -------------------------------------------------------------------------- */
/*                               BASIC INCLUDES                               */
/* -------------------------------------------------------------------------- */
#include <stdint.h>     // uint8_t, uint16_t, uint32_t
#include <stdbool.h>    // bool, true, false
#include <stddef.h>     // NULL
#include <stdlib.h>     // malloc/free (필요 시)
#include <string.h>     // memset, memcpy

/* -------------------------------------------------------------------------- */
/*                                MCU SELECTOR                                */
/* -------------------------------------------------------------------------- */
// MCU 리스트
#define MCU_ATMEGA128   1
#define MCU_STM32F4     2
#define MCU_ESP32       3

// 현재 MCU 선택
#ifndef MCU_TYPE
#define MCU_TYPE MCU_ATMEGA128
#endif

/* -------------------------------------------------------------------------- */
/*                             MCU-SPECIFIC DEFINES                           */
/* -------------------------------------------------------------------------- */
#if (MCU_TYPE == MCU_ATMEGA128)

/* ------------------------------- ATmega128 -------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#elif (MCU_TYPE == MCU_STM32F4)

/* ------------------------------- STM32F4 ---------------------------------- */
#include "stm32f4xx_hal.h"
#define F_CPU 84000000UL

#elif (MCU_TYPE == MCU_ESP32)

/* -------------------------------- ESP32 ----------------------------------- */
#include "driver/gpio.h"
#include "driver/uart.h"
#define F_CPU 240000000UL

#else
#error "Unknown MCU_TYPE"
#endif

/* -------------------------------------------------------------------------- */
/*                               COMMON MACROS                                */
/* -------------------------------------------------------------------------- */
#ifndef HIGH
#define HIGH    1
#endif

#ifndef LOW
#define LOW     0
#endif

#ifndef ON
#define ON      1
#endif

#ifndef OFF
#define OFF     0
#endif

#endif /* DEF_H_ */
