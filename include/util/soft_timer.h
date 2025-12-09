/*
 * File: soft_timer.h
 * Author: Young Kwan CHO, Lilith
 * Description: Software timer utilities based on millis()
 *              Provides non-blocking timers and timeout helpers.
 */

#ifndef SOFT_TIMER_H_
#define SOFT_TIMER_H_

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                                */
/* -------------------------------------------------------------------------- */
#include "def.h"


/* -------------------------------------------------------------------------- */
/*                               TYPE DEFINITIONS                              */
/* -------------------------------------------------------------------------- */
/**
 * @brief  Software timer object
 *         - start    : 기준 시간(ms)
 *         - interval : 주기(ms)
 */
typedef struct
{
    uint32_t start;
    uint32_t interval;
} soft_timer_t;


/* -------------------------------------------------------------------------- */
/*                                API PROTOTYPES                               */
/* -------------------------------------------------------------------------- */
/**
 * @brief  Start software timer with given interval (one-shot or periodic)
 * @param  tmr         Pointer to timer object
 * @param  interval_ms Interval in milliseconds
 */
void softTimerStart(soft_timer_t *tmr, uint32_t interval_ms);

/**
 * @brief  Restart timer from current time (interval 유지)
 * @param  tmr Pointer to timer object
 */
void softTimerRestart(soft_timer_t *tmr);

/**
 * @brief  Check if timer interval has elapsed (one-shot)
 * @param  tmr Pointer to timer object
 * @return true  : interval 이상 경과
 *         false : 아직 미경과
 *
 * @note   interval을 넘겼는지만 확인하고, start는 변경하지 않음.
 */
bool softTimerIsElapsed(soft_timer_t *tmr);

/**
 * @brief  Check if timer interval has elapsed and align for periodic use
 * @param  tmr Pointer to timer object
 * @return true  : interval 이상 경과 → handler 한 번 호출하기 적합
 *         false : 아직 미경과
 *
 * @note   경과 시 start를 interval 단위로 증가시켜
 *         고정 주기(periodic) 동작에 적합하게 정렬함.
 */
bool softTimerIsElapsedAndReset(soft_timer_t *tmr);

/**
 * @brief  Return elapsed time since start_ms
 * @param  start_ms 기준 시간 (millis() 값)
 * @return 현재 시점까지 경과 시간(ms)
 */
uint32_t timeElapsed(uint32_t start_ms);

/**
 * @brief  Check if timeout has occurred
 * @param  start_ms   기준 시간 (millis() 값)
 * @param  timeout_ms 타임아웃(ms)
 * @return true : 타임아웃 발생 (현재 - start >= timeout)
 *         false: 아직 타임아웃 아님
 */
bool timeIsTimeout(uint32_t start_ms, uint32_t timeout_ms);

#endif /* SOFT_TIMER_H_ */
