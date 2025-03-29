/**
 ******************************************************************************
 * @file    py32f002bxx_ll_Start_Kit.h
 * @author  MCU Application Team
 * @brief   This file provides set of firmware functions to manage Leds,
 *          push-button available on Start Kit.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by Puya under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PY32F002Bxx_LL_START_KIT_H
#define __PY32F002Bxx_LL_START_KIT_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "py32f002b_ll_rcc.h"
#include "py32f002b_ll_bus.h"
#include "py32f002b_ll_system.h"
#include "py32f002b_ll_exti.h"
#include "py32f002b_ll_cortex.h"
#include "py32f002b_ll_utils.h"
#include "py32f002b_ll_pwr.h"
#include "py32f002b_ll_gpio.h"
#include "py32f002b_ll_usart.h"
#include "py32f002b_ll_tim.h"
#include "py32f002b_ll_adc.h"

#include "led.h"
#include "tm1637.h"
#include "systick.h"
#include "scheduler.h"
#include "Delay.h"

/* debug printf redirect config */
#define DEBUG_USART_BAUDRATE 1000000

#define DEBUG_USART USART1
#define DEBUG_USART_CLK_ENABLE() LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1)

#define __GPIOA_CLK_ENABLE()                            \
  do                                                    \
  {                                                     \
    __IO uint32_t tmpreg = 0x00U;                       \
    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);           \
    /* Delay after an RCC peripheral clock enabling */  \
    tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); \
    UNUSED(tmpreg);                                     \
  } while (0U)

#define DEBUG_USART_RX_GPIO_PORT GPIOB
#define DEBUG_USART_RX_GPIO_CLK_ENABLE() LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB)
#define DEBUG_USART_RX_PIN LL_GPIO_PIN_5
#define DEBUG_USART_RX_AF LL_GPIO_AF_1

#define DEBUG_USART_TX_GPIO_PORT GPIOB
#define DEBUG_USART_TX_GPIO_CLK_ENABLE() LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB)
#define DEBUG_USART_TX_PIN LL_GPIO_PIN_4
#define DEBUG_USART_TX_AF LL_GPIO_AF_1

#define DEBUG_USART_IRQHandler USART1_IRQHandler
#define DEBUG_USART_IRQ USART1_IRQn

#define LOG_ENABLED 1 // Set to 0 to disable logging, set to 1 to enable logging

#if LOG_ENABLED
#define MY_PRINTF(...) printf(__VA_ARGS__)
#else
#define MY_PRINTF(...)
#endif

  void BSP_USART_Config(void);

  void bsp_init(void); /* bsp.c */
  /**
   * @}
   */

  /**
   * @}
   */

#ifdef __cplusplus
}
#endif

#endif /* PY32F002Bxx_LL_START_KIT_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
