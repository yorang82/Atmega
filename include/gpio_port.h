/*
 * File: gpio_port.h
 * Author: Young Kwan CHO, Lilith
 * Description: Logical GPIO Port Index Definitions
 *              These indices are MCU-independent and used by
 *              HAL GPIO drivers to map logical port names to
 *              actual MCU registers.
 */

#ifndef GPIO_PORT_H_
#define GPIO_PORT_H_

/* -------------------------------------------------------------------------- */
/*                               PORT INDEX LIST                               */
/* -------------------------------------------------------------------------- */
/**
 * @brief Logical port identifiers
 *        MCU drivers must internally map these to real hardware ports.
 *
 * NOTE:
 *  - ATmega128  : PORTA ~ PORTG 존재
 *  - STM32/ESP32: 실제 포트 구성은 다르지만 동일 인덱스로 매핑
 */
#define PORT_A     0
#define PORT_B     1
#define PORT_C     2
#define PORT_D     3
#define PORT_E     4
#define PORT_F     5
#define PORT_G     6

#endif /* GPIO_PORT_H_ */
