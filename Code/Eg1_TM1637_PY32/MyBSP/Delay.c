#include "Delay.h"

void delay_us(uint32_t us)
{
    // 估计一个循环的周期数
    uint32_t cycles_per_us = 4; // 24 MHz / 1,000,000 = 24 cycles per microsecond

    // 总循环次数
    uint32_t total_cycles = cycles_per_us * us;

    // 空循环
    while (total_cycles--)
    {
        __asm("NOP"); // 使用空操作指令确保编译器不会优化这个循环
    }
}

void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}
