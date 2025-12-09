/*
 * File: gpio.h
 * Author: Young Kwan CHO, Lilith
 * Description: MCU-Independent GPIO HAL Wrapper Header
 *              Provides ENUM-based logical GPIO abstraction layer
 *              allowing application code to access GPIO without
 *              knowing MCU port/pin details.
 */

#ifndef GPIO_H_
#define GPIO_H_

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                               */
/* -------------------------------------------------------------------------- */
#include "def.h"
#include "gpio_port.h"   // PORT_A ~ PORT_G 공용 포트 정의


/* -------------------------------------------------------------------------- */
/*                               GPIO ID ENUM                                 */
/* -------------------------------------------------------------------------- */
/*
 * 애플리케이션은 PORT/PIN 정보를 몰라도 되며,
 * 아래 논리 ID만 사용하여 GPIO 접근 가능.
 * 핀맵 변경 시 gpio_table만 수정하면 되고,
 * app.c는 수정하지 않아도 됨 → MCU 독립성 확보.
 */
typedef enum
{
    GPIO_LED = 0,        // Example LED Output
    // GPIO_BUTTON,         // Example Input Button
    // GPIO_SPI_CS,         // SPI Chip Select

    GPIO_MAX             // Enum Count (항상 마지막에 위치)
} gpio_id_t;


/* -------------------------------------------------------------------------- */
/*                                GPIO MODE                                   */
/* -------------------------------------------------------------------------- */
typedef enum
{
    GPIO_INPUT = 0,      // 입력
    GPIO_OUTPUT          // 출력
} gpio_mode_t;


/* -------------------------------------------------------------------------- */
/*                               GPIO STATE                                   */
/* -------------------------------------------------------------------------- */
typedef enum
{
    GPIO_LOW = 0,        // LOW level
    GPIO_HIGH            // HIGH level
} gpio_state_t;


/* -------------------------------------------------------------------------- */
/*                                API PROTOTYPES                              */
/* -------------------------------------------------------------------------- */
/**
 * @brief  Initialize all logical GPIOs defined in gpio_table
 */
void gpioInit(void);

/**
 * @brief  Set GPIO output level
 * @param  id     Logical GPIO ID (gpio_id_t)
 * @param  state  GPIO_HIGH or GPIO_LOW
 */
void gpioWrite(gpio_id_t id, gpio_state_t state);

/**
 * @brief  Toggle GPIO output
 * @param  id   Logical GPIO ID
 */
void gpioToggle(gpio_id_t id);

/**
 * @brief  Read GPIO input level
 * @param  id   Logical GPIO ID
 * @return 1 = HIGH, 0 = LOW
 */
uint8_t gpioRead(gpio_id_t id);

#endif /* GPIO_H_ */
