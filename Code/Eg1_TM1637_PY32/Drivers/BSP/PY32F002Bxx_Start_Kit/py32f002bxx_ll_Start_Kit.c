/**
 ******************************************************************************
 * @file    py32f002bxx_ll_Start_Kit.c
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

/* Includes ------------------------------------------------------------------*/
#include "py32f002bxx_ll_Start_Kit.h"

/**
 * @brief  DEBUG_USART GPIO Config,Mode Config,115200 8-N-1
 * @param  None
 * @retval None
 */
void BSP_USART_Config(void)
{
#if defined(__GNUC__)
  setvbuf(stdout, NULL, _IONBF, 0);
#endif
  DEBUG_USART_CLK_ENABLE();

  /* USART Init */
  LL_USART_SetBaudRate(DEBUG_USART, SystemCoreClock, LL_USART_OVERSAMPLING_16, DEBUG_USART_BAUDRATE);
  LL_USART_SetDataWidth(DEBUG_USART, LL_USART_DATAWIDTH_8B);
  LL_USART_SetStopBitsLength(DEBUG_USART, LL_USART_STOPBITS_1);
  LL_USART_SetParity(DEBUG_USART, LL_USART_PARITY_NONE);
  LL_USART_SetHWFlowCtrl(DEBUG_USART, LL_USART_HWCONTROL_NONE);
  LL_USART_SetTransferDirection(DEBUG_USART, LL_USART_DIRECTION_TX_RX);
  LL_USART_Enable(DEBUG_USART);
  LL_USART_ClearFlag_TC(DEBUG_USART);

  /**USART GPIO Configuration
    PB4     ------> USART1_TX
    PB5     ------> USART1_RX
    */
  DEBUG_USART_RX_GPIO_CLK_ENABLE();
  DEBUG_USART_TX_GPIO_CLK_ENABLE();

  LL_GPIO_SetPinMode(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
  LL_GPIO_SetPinPull(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_PIN, LL_GPIO_PULL_UP);
  LL_GPIO_SetAFPin_0_7(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_PIN, DEBUG_USART_TX_AF);

  LL_GPIO_SetPinMode(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_PIN, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
  LL_GPIO_SetPinPull(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_PIN, LL_GPIO_PULL_UP);
  LL_GPIO_SetAFPin_0_7(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_PIN, DEBUG_USART_RX_AF);
}
void bsp_init(void)
{
  SysTick_Init();

  /* Enable GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  /* Enable GPIOB clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  BSP_USART_Config();
  led_init();
  tm1637_init();
}

#if (defined(__CC_ARM)) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/**
 * @brief  writes a character to the usart
 * @param  ch
 *         *f
 * @retval the character
 */
int fputc(int ch, FILE *f)
{
  /* Send a byte to USART */
  LL_USART_TransmitData8(DEBUG_USART, ch); // ��USART����һ���ֽ�
  while (!LL_USART_IsActiveFlag_TC(DEBUG_USART))
    ;                                 // �ȴ��������?
  LL_USART_ClearFlag_TC(DEBUG_USART); // ���������ɱ�־

  return (ch);
}

/**
 * @brief  get a character from the usart
 * @param  *f
 * @retval a character
 */
int fgetc(FILE *f)
{
  int ch;
  while (!LL_USART_IsActiveFlag_RXNE(DEBUG_USART))
    ;
  ch = LL_USART_ReceiveData8(DEBUG_USART);
  return (ch);
}

#elif defined(__ICCARM__)
/**
 * @brief  writes a character to the usart
 * @param  ch
 *         *f
 * @retval the character
 */
int putchar(int ch)
{
  /* Send a byte to USART */
  LL_USART_TransmitData8(DEBUG_USART, ch);
  while (!LL_USART_IsActiveFlag_TC(DEBUG_USART))
    ;
  LL_USART_ClearFlag_TC(DEBUG_USART);

  return (ch);
}
#elif defined(__GNUC__)
/**
 * @brief  writes a character to the usart
 * @param  ch
 * @retval the character
 */
int __io_putchar(int ch)
{
  /* Send a byte to USART */
  LL_USART_TransmitData8(DEBUG_USART, ch);
  while (!LL_USART_IsActiveFlag_TC(DEBUG_USART))
    ;
  LL_USART_ClearFlag_TC(DEBUG_USART);
  return ch;
}

int _write(int file, char *ptr, int len)
{
  int DataIdx;
  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}

#endif

/**
 * @}
 */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
