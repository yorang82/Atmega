/*
 * File: app.h
 * Author: Young Kwan CHO, Lilith
 * Description: Application Layer Header
 *              Declares initialization, periodic task execution,
 *              and main loop functions. This layer does not access
 *              MCU registers directly and depends only on HAL APIs.
 */

#ifndef APP_H_
#define APP_H_

/* -------------------------------------------------------------------------- */
/*                             APPLICATION API                                 */
/* -------------------------------------------------------------------------- */
/**
 * @brief System initialization
 *        HAL layer init routines are called here.
 */
void appInit(void);

/**
 * @brief Main application loop
 *        Must be called repeatedly inside main()
 */
void appMain(void);

/**
 * @brief Task dispatcher
 *        Executes periodic tasks based on timing
 */
void appTask(void);

#endif /* APP_H_ */
