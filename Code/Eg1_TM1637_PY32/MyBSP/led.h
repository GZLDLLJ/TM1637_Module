/**
 * @file led.h
 * @author ymlk
 * @brief
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef __LED_H__
#define __LED_H__
#include "py32f002bxx_ll_Start_Kit.h"

#define LED1_PORT GPIOA
#define LED1_PIN LL_GPIO_PIN_1

#define OPEN_STATUS_LED() LL_GPIO_SetOutputPin(LED1_PORT, LED1_PIN)
#define CLOSE_STATUS_LED() LL_GPIO_ResetOutputPin(LED1_PORT, LED1_PIN)
#define TOGGLE_STATUS_LED() LL_GPIO_TogglePin(LED1_PORT, LED1_PIN)

void led_init(void);
void set_status_led(uint32_t timeout);
void status_led_handler(void);
#endif
