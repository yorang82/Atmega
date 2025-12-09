/*
 * File: app.c
 * Author: Young Kwan CHO, Lilith
 * Description: Application Layer Source
 *              Implements system initialization and main loop tasks.
 *              This layer depends only on HAL drivers and
 *              contains no MCU-dependent code.
 */

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                               */
/* -------------------------------------------------------------------------- */
#include "app.h"
#include "gpio.h"   // GPIO HAL
#include "uart.h"   // UART HAL 추가 시 활성화
#include "delay.h"  // TIMER 기반 delay 사용 시 활성화
#undef millis


/* -------------------------------------------------------------------------- */
/*                                 TASK TYPES                                 */
/* -------------------------------------------------------------------------- */
typedef struct
{
    void (*handler)(void);     // Task 함수
    uint32_t period_ms;        // 주기
    uint32_t last_tick;        // 최근 실행 tick
} task_t;

/* -------------------------------------------------------------------------- */
/*                             TASK PROTOTYPES                                */
/* -------------------------------------------------------------------------- */
static void task_1ms(void);
static void task_50ms(void);
static void task_100ms(void);
static void task_500ms(void);

/* -------------------------------------------------------------------------- */
/*                                TASK TABLE                                  */
/* -------------------------------------------------------------------------- */
#define TASK_MAX 4

static task_t task_tbl[TASK_MAX] =
{
    { task_1ms,     1,   0 },
    { task_50ms,   50,   0 },
    { task_100ms, 100,   0 },
    { task_500ms, 500,   0 },
};

/* -------------------------------------------------------------------------- */
/*                              APP INITIALIZE                                */
/* -------------------------------------------------------------------------- */
/**
 * @brief System initialization
 *        HAL layer init routines are called here.
 */
void appInit(void)
{
    gpioInit();            // 논리 GPIO 초기화
    delayInit();        // TIMER 기반 delay 사용 시 활성화
    uartInit(38400);         // UART 사용 시 

    
    uartPrint("APP INIT OK\r\n");  
}

/* -------------------------------------------------------------------------- */
/*                                TASK EXECUTOR                               */
/* -------------------------------------------------------------------------- */
/**
 * @brief Task dispatcher
 *        main() 또는 scheduler에서 반복 호출되어야 함
 */
void appTask(void)
{
    uint32_t now = millis();

    for (uint8_t i = 0; i < TASK_MAX; i++)
    {
        if (now - task_tbl[i].last_tick >= task_tbl[i].period_ms)
        {
            task_tbl[i].last_tick = now;
            task_tbl[i].handler();
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                                 APP MAIN                                   */
/* -------------------------------------------------------------------------- */
/**
 * @brief Main application loop
 *        호출 주기는 main.c 또는 timer interrupt에서 결정
 */
void appMain(void)
{
    uartPrint("APP MAIN START\r\n");
 
      while (1)
  {
    appTask();             // Task 처리 
  }

    // NOTE:
    // appMain() 내부는 절대 무한 지연 사용 금지
    // delay는 타이머 또는 task scheduler 기반으로 처리
}

/* -------------------------------------------------------------------------- */
/*                                TASK BODIES                                 */
/* -------------------------------------------------------------------------- */
/**
 * @brief 실행 주기: 1ms
 */
static void task_1ms(void)
{
    // TODO: KEY SCAN, debounce 등
}

/**
 * @brief 실행 주기: 50ms
 */
static void task_50ms(void)
{
    // TODO: Sys status check
}

/**
 * @brief 실행 주기: 100ms
 */
static void task_100ms(void)
{
    // TODO: Sys status check
}

/**
 * @brief 실행 주기: 500ms
 */
static void task_500ms(void)
{
    gpioToggle(GPIO_LED);  // LED 토글
}
