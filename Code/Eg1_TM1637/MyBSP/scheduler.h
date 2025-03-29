/**
 * @file scheduler.h
 * @author ymlk
 * @brief
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "py32f002bxx_ll_Start_Kit.h"

// 任务结构体
typedef struct
{
    void (*task_func)(void); // 任务函数指针
    uint32_t period;         // 任务执行周期 (ms)
    uint32_t last_run;       // 上次执行时间
} Task_t;

// 任务调度器初始化
void Scheduler_Init(void);

// 任务调度器运行
void Scheduler_Run(void);

#endif
