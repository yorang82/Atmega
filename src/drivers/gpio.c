/*
 * File: gpio.c
 * Author: Young Kwan CHO, Lilith
 * Description: ATmega128 GPIO HAL Wrapper (ENUM-based logical GPIO control)
 */

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                                */
/* -------------------------------------------------------------------------- */
#include "gpio.h"


#if (MCU_TYPE == MCU_ATMEGA128)
/* -------------------------------------------------------------------------- */
/*                             GPIO CONFIG TABLE                              */
/* -------------------------------------------------------------------------- */
/* Logical GPIO → Physical Port/Pin/Mode mapping                               */
/* 이 테이블만 수정하면 MCU 핀 변경, PCB REV 변경에도 APP 코드는 수정 불필요 */
typedef struct
{
    uint8_t port;
    uint8_t pin;
    gpio_mode_t mode;
} gpio_cfg_t;

static const gpio_cfg_t gpio_table[GPIO_MAX] =
{
    { PORT_B, 0, GPIO_OUTPUT }, // GPIO_LED
    // { PORT_D, 2, GPIO_INPUT  }, // GPIO_BUTTON
    // { PORT_C, 3, GPIO_OUTPUT }, // GPIO_SPI_CS
};

/* -------------------------------------------------------------------------- */
/*                     INTERNAL REGISTER ACCESS HELPERS                        */
/* -------------------------------------------------------------------------- */
/* 포트번호(enum) → AVR 레지스터 반환 (MCU 독립 API) */

static inline volatile uint8_t* gpio_get_ddr(uint8_t port)
{
    switch(port)
    {
        case PORT_A: return &DDRA;
        case PORT_B: return &DDRB;
        case PORT_C: return &DDRC;
        case PORT_D: return &DDRD;
        case PORT_E: return &DDRE;
        case PORT_F: return &DDRF;
        case PORT_G: return &DDRG;
        default:     return 0;
    }
}

static inline volatile uint8_t* gpio_get_port(uint8_t port)
{
    switch(port)
    {
        case PORT_A: return &PORTA;
        case PORT_B: return &PORTB;
        case PORT_C: return &PORTC;
        case PORT_D: return &PORTD;
        case PORT_E: return &PORTE;
        case PORT_F: return &PORTF;
        case PORT_G: return &PORTG;
        default:     return 0;
    }
}

static inline volatile uint8_t* gpio_get_pin(uint8_t port)
{
    switch(port)
    {
        case PORT_A: return &PINA;
        case PORT_B: return &PINB;
        case PORT_C: return &PINC;
        case PORT_D: return &PIND;
        case PORT_E: return &PINE;
        case PORT_F: return &PINF;
        case PORT_G: return &PING;
        default:     return 0;
    }
}

/* -------------------------------------------------------------------------- */
/*                                GPIO INIT                                   */
/* -------------------------------------------------------------------------- */
/**
 * @brief  Initialize all GPIOs defined in gpio_table
 *         (논리 ID 기반 GPIO 초기화)
 */
void gpioInit(void)
{
    for (uint8_t i = 0; i < GPIO_MAX; i++)
    {
        volatile uint8_t *ddr = gpio_get_ddr(gpio_table[i].port);
        if (!ddr) continue;

        if (gpio_table[i].mode == GPIO_OUTPUT)
            *ddr |=  (1 << gpio_table[i].pin);  // output
        else
            *ddr &= ~(1 << gpio_table[i].pin);  // input
    }
}

/* -------------------------------------------------------------------------- */
/*                              GPIO WRITE                                    */
/* -------------------------------------------------------------------------- */
/**
 * @brief   Set logical GPIO output state
 */
void gpioWrite(gpio_id_t id, gpio_state_t state)
{
    volatile uint8_t *out = gpio_get_port(gpio_table[id].port);
    if (!out) return;

    if (state == GPIO_HIGH)
        *out |=  (1 << gpio_table[id].pin);
    else
        *out &= ~(1 << gpio_table[id].pin);
}

/* -------------------------------------------------------------------------- */
/*                              GPIO TOGGLE                                   */
/* -------------------------------------------------------------------------- */
/**
 * @brief   Toggle logical GPIO output
 */
void gpioToggle(gpio_id_t id)
{
    volatile uint8_t *out = gpio_get_port(gpio_table[id].port);
    if (!out) return;

    *out ^= (1 << gpio_table[id].pin); // invert pin
}

/* -------------------------------------------------------------------------- */
/*                               GPIO READ                                    */
/* -------------------------------------------------------------------------- */
/**
 * @brief   Read logical GPIO input state
 * @return  1 = HIGH, 0 = LOW
 */
uint8_t gpioRead(gpio_id_t id)
{
    volatile uint8_t *in = gpio_get_pin(gpio_table[id].port);
    if (!in) return 0;

    return (*in & (1 << gpio_table[id].pin)) ? 1 : 0;
}

#endif /* MCU_ATMEGA128 */
