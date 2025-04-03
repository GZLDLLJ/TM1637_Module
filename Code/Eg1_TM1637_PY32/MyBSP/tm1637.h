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

#include "py32f002bxx_ll_Start_Kit.h"

#define TM_SCL_PORT GPIOA
#define TM_SCL_PIN LL_GPIO_PIN_5
#define TM_SDA_PORT GPIOA
#define TM_SDA_PIN LL_GPIO_PIN_6

#define TM_SCL_HIGH() LL_GPIO_SetOutputPin(TM_SCL_PORT, TM_SCL_PIN)
#define TM_SCL_LOW() LL_GPIO_ResetOutputPin(TM_SCL_PORT, TM_SCL_PIN)
#define TM_SDA_HIGH() LL_GPIO_SetOutputPin(TM_SDA_PORT, TM_SDA_PIN)
#define TM_SDA_LOW() LL_GPIO_ResetOutputPin(TM_SDA_PORT, TM_SDA_PIN)
#define TM_SDA_STA() LL_GPIO_IsInputPinSet(TM_SDA_PORT, TM_SDA_PIN)

extern const uint8_t CODE[10];
void disp0(unsigned char *p);
void tm1637_init(void);
void key_process(void);

#endif
