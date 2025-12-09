/*
 * File: soft_timer.c
 * Author: Young Kwan CHO, Lilith
 * Description: Software timer utilities based on millis()
 *              Provides non-blocking timers and timeout helpers.
 */

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                                */
/* -------------------------------------------------------------------------- */
#include "soft_timer.h"
#include "delay.h"   // millis() 사용


/* -------------------------------------------------------------------------- */
/*                            SOFTWARE TIMER CORE                              */
/* -------------------------------------------------------------------------- */
/**
 * @brief  Start software timer with given interval
 */
void softTimerStart(soft_timer_t *tmr, uint32_t interval_ms)
{
    if (tmr == NULL) return;

    tmr->interval = interval_ms;
    tmr->start    = millis();
}

/**
 * @brief  Restart timer from current time (interval 유지)
 */
void softTimerRestart(soft_timer_t *tmr)
{
    if (tmr == NULL) return;

    tmr->start = millis();
}

/**
 * @brief  Check if timer interval has elapsed (one-shot)
 */
bool softTimerIsElapsed(soft_timer_t *tmr)
{
    if (tmr == NULL) return false;

    uint32_t now = millis();
    return ((now - tmr->start) >= tmr->interval);
}

/**
 * @brief  Check if timer interval has elapsed and align for periodic use
 *
 * 고정 주기(periodic)용:
 *   - 경과 시 true 반환
 *   - start를 interval 단위로 증가시켜 주기 정렬
 */
bool softTimerIsElapsedAndReset(soft_timer_t *tmr)
{
    if (tmr == NULL) return false;

    uint32_t now = millis();
    uint32_t elapsed = now - tmr->start;

    if (elapsed >= tmr->interval)
    {
        /*
         * 주기 정렬 방식:
         *   - 여러 주기가 한꺼번에 지나갔을 경우를 고려하여
         *     start += interval 을 반복해서 "가장 가까운 과거 tick"에 맞춤.
         */
        if (tmr->interval > 0)
        {
            uint32_t n = elapsed / tmr->interval;
            tmr->start += (tmr->interval * n);
        }
        else
        {
            tmr->start = now;
        }

        return true;
    }

    return false;
}


/* -------------------------------------------------------------------------- */
/*                         TIME ELAPSED / TIMEOUT API                          */
/* -------------------------------------------------------------------------- */
/**
 * @brief  Return elapsed time since start_ms
 */
uint32_t timeElapsed(uint32_t start_ms)
{
    uint32_t now = millis();
    return (now - start_ms);
}

/**
 * @brief  Check if timeout has occurred
 */
bool timeIsTimeout(uint32_t start_ms, uint32_t timeout_ms)
{
    uint32_t now = millis();
    return ((now - start_ms) >= timeout_ms);
}
