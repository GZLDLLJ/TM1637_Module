#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "py32f002bxx_ll_Start_Kit.h"

// ��ʼ�� SysTick 1ms
void SysTick_Init(void);

// ��ȡϵͳʱ��
uint32_t SysTick_GetTick(void);

#endif
