#include "systick.h"

volatile uint32_t sys_tick = 0;

// SysTick ������
void SysTick_Handler(void)
{
    sys_tick++;
}

// ��ʼ�� SysTick (1ms)
void SysTick_Init(void)
{

    LL_Init1msTick(24000000);
    LL_SYSTICK_EnableIT();
}

// ��ȡ��ǰϵͳʱ��
uint32_t SysTick_GetTick(void)
{
    return sys_tick;
}
