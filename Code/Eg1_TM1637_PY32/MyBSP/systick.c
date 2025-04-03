#include "systick.h"

volatile uint32_t sys_tick = 0;

// SysTick 处理函数
void SysTick_Handler(void)
{
    sys_tick++;
}

// 初始化 SysTick (1ms)
void SysTick_Init(void)
{

    LL_Init1msTick(24000000);
    LL_SYSTICK_EnableIT();
}

// 获取当前系统时基
uint32_t SysTick_GetTick(void)
{
    return sys_tick;
}
