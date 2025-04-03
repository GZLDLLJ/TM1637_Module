/**
 * @file scheduler.c
 * @author ymlk
 * @brief
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "scheduler.h"
#include "systick.h"

void task_10ms_handler(void)
{
}
void Task_100ms_handler(void)
{
    __disable_irq();
    key_process();
    __enable_irq();
}
void Task_500ms_handler(void)
{
    TOGGLE_STATUS_LED();

    // MY_PRINTF("Task_300ms_handler\n");
}

Task_t task_list[] = {
    {task_10ms_handler, 10, 0},
    {Task_100ms_handler, 100, 0},
    {Task_500ms_handler, 500, 0},
};

#define TASK_COUNT (sizeof(task_list) / sizeof(Task_t))

void Scheduler_Init(void)
{

    for (uint8_t i = 0; i < TASK_COUNT; i++)
    {
        task_list[i].last_run = 0;
    }
}

void Scheduler_Run(void)
{
    uint32_t current_tick = SysTick_GetTick();

    for (uint8_t i = 0; i < TASK_COUNT; i++)
    {
        if ((current_tick - task_list[i].last_run) >= task_list[i].period)
        {
            task_list[i].last_run = current_tick;
            task_list[i].task_func();
        }
    }
}
