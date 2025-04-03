/**
 * @file led.c
 * @author ymlk
 * @brief
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "led.h"



void led_init(void)
{
    /* Enable GPIOA clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

    /* Configure GPIO in output mode */
    LL_GPIO_SetPinMode(LED1_PORT, LED1_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_ResetOutputPin(LED1_PORT, LED1_PIN);
}
