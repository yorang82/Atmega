# Coding Style Guide
**Project:** ReLief U Firmware
**Author:** Young Kwan CHO  
**AI Assistant:** Lucy (루시)
**Last Updated:** 2025-12-21

---

## 1. 파일 헤더

모든 소스 파일(.c, .h)은 다음 형식의 헤더로 시작합니다:

```c
/*
* Project: 33KHz Ultrasound Firmware
 * 
 * File: [filename].c
 * Author: Young Kwan CHO, Lucy
 * Last Modified: YYYY-MM-DD
 * Description: [상세 설명 - 여러 줄 가능]
 */
```

*예시:**
```c
/*
 * Project: 33KHz Ultrasound Firmware
 * 
 * File: adc_driver.c
 * Author: Young Kwan CHO, Lucy
 * Last Modified: 2025-12-21
 * Description: ADC 드라이버 (LL 버전, API + CLI)
 *              배터리 전압, 전류, 온도 측정 기능 포함
 */
```

---

## 2. 섹션 구분

### 2.1 큰 섹션 (주요 기능 블록)

```c
/* -------------------------------------------------------------------------- */
/*                                SECTION NAME                                */
/* -------------------------------------------------------------------------- */
```

**예시:**
```c
/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                                */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                             GPIO CONFIG TABLE                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                GPIO INIT                                   */
/* -------------------------------------------------------------------------- */
```

### 2.2 작은 섹션 (변수 그룹, Define 그룹 등)

```c
// ------------------- 섹션 이름 -------------------
```

또는

```c
// ---------------- 섹션 이름 ----------------
```

**예시:**
```c
// ------------------- RX 버퍼 -------------------
static uint8_t rx_buf_dbug[256];
static uint8_t rx_buf_lcd[256];

// ---------------- 참조 전압/분해능 ----------------
#define ADC_VREF        3.3f
#define ADC_RESOLUTION  4095.0f
```

### 2.3 섹션 설명 (블록 주석)

```c
/* 한 줄 설명 또는 여러 줄 설명 */
/* 이렇게 계속 이어서 작성 가능 */
```

**예시:**
```c
/* Logical GPIO → Physical Port/Pin/Mode mapping                               */
/* 이 테이블만 수정하면 MCU 핀 변경, PCB REV 변경에도 APP 코드는 수정 불필요 */

/* 포트번호(enum) → AVR 레지스터 반환 (MCU 독립 API) */
```

---

## 3. 함수 설명

모든 함수 위에는 Doxygen 스타일 주석을 작성합니다:

```c
/**
 * @brief  함수의 간단한 설명
 *         (추가 설명이 필요하면 여기에)
 * @param  param1 파라미터 설명
 * @return 반환값 설명
 */
```

**예시:**
```c
/**
 * @brief  Initialize all GPIOs defined in gpio_table
 *         (논리 ID 기반 GPIO 초기화)
 */
void gpioInit(void);

/**
 * @brief   Set logical GPIO output state
 * @param   id GPIO 논리 ID
 * @param   state GPIO_HIGH 또는 GPIO_LOW
 */
void gpioWrite(gpio_id_t id, gpio_state_t state);

/**
 * @brief   Read logical GPIO input state
 * @return  1 = HIGH, 0 = LOW
 */
uint8_t gpioRead(gpio_id_t id);
```

---

## 4. 변수 및 Define

### 4.1 Define 정의

값의 의미를 인라인 주석으로 설명합니다:

```c
#define VALUE_NAME    123    // 설명
```

**예시:**
```c
// ---------------- VBAT 분압 저항 ----------------
// VBAT → R1 →(측정점)→ R2 → GND
#define ADC_VBAT_R1    680000.0f   // 기본값: 680kΩ
#define ADC_VBAT_R2    220000.0f   // 기본값: 220kΩ
#define ADC_VBAT_COEF  ((ADC_VBAT_R1 + ADC_VBAT_R2) / ADC_VBAT_R2)

// ---------------- 온도 센서 보정 ----------------
#define ADC_V25         0.76f     // 25°C에서의 전압 [V]
#define ADC_AVG_SLOPE   0.0025f   // 2.5mV/°C (STM32F405 DS 기준)
```

### 4.2 전역/Static 변수

변수의 용도를 인라인 주석으로 설명합니다:

```c
static type variable_name;     // 변수 용도 설명
```

**예시:**
```c
static bool is_open[UART_MAX_CH];     // UART 채널별 열림/닫힘 상태
static qbuffer_t qbuffer[UART_MAX_CH]; // UART 채널별 수신 링버퍼

static uint8_t rx_buf_dbug[256];       // 디버그 UART 수신 버퍼
static uint8_t rx_buf_lcd[256];        // LCD UART 수신 버퍼
```

### 4.3 구조체 멤버

각 멤버에 인라인 주석으로 설명을 추가합니다:

```c
typedef struct
{
    uint8_t port;         // 포트 번호
    uint8_t pin;          // 핀 번호
    gpio_mode_t mode;     // 입출력 모드
} gpio_cfg_t;
```

**예시:**
```c
typedef struct
{
  ADC_TypeDef *p_adc;           // LL ADC 인스턴스 포인터
  uint32_t channel;             // 채널 번호
  char *name;                   // CLI 표시용 이름
  uint16_t value;               // 최근 변환 값 저장
} adc_tbl_t;

typedef struct
{
  UART_HandleTypeDef *p_huart;        // HAL UART 핸들 포인터
  DMA_HandleTypeDef  *p_hdma_rx;      // RX DMA 핸들 포인터
  uint8_t            *p_rx_buf;       // 수신 버퍼 포인터
  uint32_t            rx_buf_len;     // 수신 버퍼 크기
} uart_tbl_t;
```

---

## 5. 인라인 주석

코드 라인 끝에 간단한 설명을 추가합니다:

```c
variable = value;  // 간단한 설명
```

**예시:**
```c
*ddr |=  (1 << gpio_table[i].pin);  // output
*ddr &= ~(1 << gpio_table[i].pin);  // input

*out ^= (1 << gpio_table[i].pin);   // invert pin

cliMain(); // Ctrl+C 감지
```

---

## 6. 네이밍 규칙

### 6.1 함수명
- **camelCase** 사용
- 동사로 시작
- 예: `gpioInit()`, `adcReadVoltage()`, `uartWrite()`

### 6.2 변수명
- **snake_case** 또는 **camelCase**
- 전역/static 변수는 접두어 사용 고려
- 예: `is_open`, `rx_buf_dbug`, `gpio_table`

### 6.3 Define/Enum
- **UPPER_CASE** 사용
- 언더스코어로 단어 구분
- 예: `ADC_VREF`, `UART_MAX_CH`, `GPIO_OUTPUT`

### 6.4 타입명
- **snake_case_t** 형식 (_t 접미사)
- 예: `gpio_cfg_t`, `adc_ch_t`, `uart_tbl_t`

---

## 7. 코드 구조

### 7.1 헤더 파일 (.h)

```c
/*
 * File: module.h
 * Author: Young Kwan CHO, Lucy
 * Last Modified: YYYY-MM-DD
 * Description: 모듈 설명
 */

#ifndef INCLUDE_MODULE_H_
#define INCLUDE_MODULE_H_

#include "def.h"

// ==================================================
//                  매크로 정의
// ==================================================

// ==================================================
//                  타입 정의
// ==================================================

// ==================================================
//                  외부 API
// ==================================================

#ifdef _USE_CLI
void moduleCliInit(void);
#endif

#endif /* INCLUDE_MODULE_H_ */
```

### 7.2 소스 파일 (.c)

```c
/*
 * File: module.c
 * Author: Young Kwan CHO, Lucy
 * Last Modified: YYYY-MM-DD
 * Description: 모듈 구현
 */

#include "module.h"

// ==================================================
//                  내부 구조체
// ==================================================

// ==================================================
//                  내부 변수
// ==================================================

// ==================================================
//                  내부 함수
// ==================================================

// ==================================================
//                  외부 함수
// ==================================================

// ==================================================
//                  CLI
// ==================================================
#ifdef _USE_CLI
// CLI 구현
#endif
```

---

## 8. 특수 기호 사용

### 8.1 중요 표시
```c
// ⚡ 중요한 설정이나 주의사항
```

### 8.2 회로도 설명
```c
// VBAT → R1 →(측정점)→ R2 → GND
```

---
