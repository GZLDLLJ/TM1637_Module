#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "py32f002bxx_ll_Start_Kit.h"

// 初始化 SysTick 1ms
void SysTick_Init(void);

// 获取系统时基
uint32_t SysTick_GetTick(void);

#endif
