/*
 * File: delay.c
 * Author: Young Kwan CHO, Lilith
 * Description: ATmega128 Delay & Time API
 *              Implemented using Timer1 (CTC mode) for stable 1ms tick
 *              and 4µs resolution micros().
 */

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                               */
/* -------------------------------------------------------------------------- */
#include "delay.h"


#if (MCU_TYPE == MCU_ATMEGA128)
/* -------------------------------------------------------------------------- */
/*                               LOCAL VARIABLES                              */
/* -------------------------------------------------------------------------- */

static volatile uint32_t g_ms = 0;   // 1ms tick counter

/* -------------------------------------------------------------------------- */
/*                               delayInit()                                  */
/* -------------------------------------------------------------------------- */
/**
 * @brief Configure Timer1 for 1ms system tick
 *
 * F_CPU = 16MHz
 * Prescaler = 64  → 16MHz / 64 = 250kHz
 * 1 tick = 4µs
 * 250 ticks = 1000µs = 1ms
 *
 * → CTC mode, TOP = OCR1A = 249
 */
void delayInit(void)
{
    cli();

    // Timer1 stop & reset
    TCCR1A = 0x00;
    TCCR1B = 0x00;

    // CTC mode (TOP = OCR1A)
    TCCR1B |= (1 << WGM12);

    // Prescaler /64 → 4µs per tick
    TCCR1B |= (1 << CS11) | (1 << CS10);   // CS12:0 = 011 → /64

    // Compare value for 1ms
    OCR1A = 249;   // 0~249 = 250 ticks → 250 * 4µs = 1000µs = 1ms

    // Compare Match A Interrupt Enable
    TIMSK |= (1 << OCIE1A);

    sei();
}

/* -------------------------------------------------------------------------- */
/*                                millis()                                    */
/* -------------------------------------------------------------------------- */
/**
 * @brief Return system time in milliseconds
 */
uint32_t millis(void)
{
    uint32_t m;
    uint8_t sreg = SREG;

    cli();
    m = g_ms;
    SREG = sreg;

    return m;
}

/* -------------------------------------------------------------------------- */
/*                                micros()                                    */
/* -------------------------------------------------------------------------- */
/**
 * @brief Return system time in microseconds
 *        Resolution = 4µs
 */
uint32_t micros(void)
{
    uint32_t m;
    uint16_t t;
    uint8_t sreg = SREG;

    cli();
    m = g_ms;      // ms
    t = TCNT1;     // timer ticks (4µs 단위)
    SREG = sreg;

    // m * 1000us + t * 4us
    return (m * 1000UL) + (t * 4UL);
}

/* -------------------------------------------------------------------------- */
/*                               delay_us()                                   */
/* -------------------------------------------------------------------------- */
void delay_us(uint32_t us)
{
    uint32_t start = micros();

    // 4µs 해상도라서, 아주 작은 값은 약간 길어질 수 있음
    while ((micros() - start) < us)
    {
        // busy wait
    }
}

/* -------------------------------------------------------------------------- */
/*                               delay_ms()                                   */
/* -------------------------------------------------------------------------- */
void delay_ms(uint32_t ms)
{
    uint32_t start = millis();
    while ((millis() - start) < ms)
    {
        // busy wait (ms 단위)
    }
}

/* -------------------------------------------------------------------------- */
/*                         TIMER1 COMPARE MATCH ISR                           */
/* -------------------------------------------------------------------------- */
/**
 * @brief Timer1 Compare Match A Interrupt
 *        Called every 1ms
 */
ISR(TIMER1_COMPA_vect)
{
    g_ms++;
}

#endif /* MCU_ATMEGA128 */
