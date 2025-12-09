/*
 * File: main.c
 * Author: Young Kwan CHO, Lilith
 * Description: Application Entry Point
 *              Initializes the system and repeatedly executes
 *              application-level logic. MCU-dependent details
 *              are abstracted inside HAL drivers.
 */

/* -------------------------------------------------------------------------- */
/*                                INCLUDE FILES                               */
/* -------------------------------------------------------------------------- */
#include "app.h"


/* -------------------------------------------------------------------------- */
/*                                 MAIN                                       */
/* -------------------------------------------------------------------------- */
int main(void)
{
    appInit();      // 시스템 / HAL 초기화
    appMain();  // APP 로직 실행 (내부에서 task 처리 포함)

    // while (1)
    // {

    // }

    return 0;       // 도달하지 않음
}
