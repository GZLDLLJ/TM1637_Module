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

// ����ṹ��
typedef struct
{
    void (*task_func)(void); // ������ָ��
    uint32_t period;         // ����ִ������ (ms)
    uint32_t last_run;       // �ϴ�ִ��ʱ��
} Task_t;

// �����������ʼ��
void Scheduler_Init(void);

// �������������
void Scheduler_Run(void);

#endif
