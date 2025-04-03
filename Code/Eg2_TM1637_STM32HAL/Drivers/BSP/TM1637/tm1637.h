/**
 * @file tm1637.h
 * @author e-play
 * @brief
 * @version 0.1
 * @date 2025-03-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __TM1637_H__
#define __TM1637_H__

#include "./SYSTEM/sys/sys.h"

#define TM_SCL_PORT GPIOA
#define TM_SCL_PIN GPIO_PIN_5
#define TM_SDA_PORT GPIOA
#define TM_SDA_PIN GPIO_PIN_6

#define TM_SCL_HIGH() HAL_GPIO_WritePin(TM_SCL_PORT, TM_SCL_PIN, GPIO_PIN_SET)
#define TM_SCL_LOW() HAL_GPIO_WritePin(TM_SCL_PORT, TM_SCL_PIN, GPIO_PIN_RESET)
#define TM_SDA_HIGH() HAL_GPIO_WritePin(TM_SDA_PORT, TM_SDA_PIN, GPIO_PIN_SET)
#define TM_SDA_LOW() HAL_GPIO_WritePin(TM_SDA_PORT, TM_SDA_PIN, GPIO_PIN_RESET)
#define TM_SDA_STA() HAL_GPIO_ReadPin(TM_SDA_PORT, TM_SDA_PIN)

extern const uint8_t CODE[10];
void disp0(unsigned char *p);
void tm1637_init(void);
void key_process(void);

#endif
