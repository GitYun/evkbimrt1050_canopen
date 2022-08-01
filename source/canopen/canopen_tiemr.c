/*
 * canopen_tiemr.c
 *
 *  Created on: 2022年7月29日
 *      Author: renqingyun
 */


#include "fsl_gpt.h"
#include "canfestival/mimxrt1052/canfestival.h"
#include "canfestival/timers.h"

#if defined (USE_RTOS) && (USE_RTOS == 1)

#define CANOPEN_TIMER_HW_BASE
#define CANOPEN_TIEMR_IRQn
#define CANOPEN_TIMER_ISR       rtos_systick_hook

#else

#define IRQ_NUM(x)      x ## _IRQn
#define IRQ_ISR(x)      x ## _IRQHandler

#define CANOPEN_TIMER_HW_BASE   GPT2
#define CANOPEN_TIEMR_IRQn      IRQ_NUM(GPT2)
#define CANOPEN_TIMER_ISR       IRQ_ISR(GPT2)

#endif

TIMEVAL g_last_dispatch_counter_val = 0;
TIMEVAL g_next_dispatch_counter_val = 0;
TIMEVAL g_elapsed_time = 0;

void setTimer(TIMEVAL value)
{
//    g_next_dispatch_counter_val = GPT_GetCurrentTimerCount(CANOPEN_TIMER_HW_BASE) + value;

    TIMEVAL current_counter = GPT_GetCurrentTimerCount(CANOPEN_TIMER_HW_BASE);
    g_elapsed_time += current_counter - g_last_dispatch_counter_val;
    g_last_dispatch_counter_val = current_counter;

    GPT_SetOutputCompareValue(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare_Channel1, current_counter + value);
}

TIMEVAL getElapsedTime(void)
{
//    return GPT_GetCurrentTimerCount(CANOPEN_TIMER_HW_BASE) - g_last_dispatch_counter_val;

    TIMEVAL current_counter = GPT_GetCurrentTimerCount(CANOPEN_TIMER_HW_BASE);
    TIMEVAL elapsed = (TIMEVAL)(current_counter - g_last_dispatch_counter_val) + g_elapsed_time;

    return elapsed;
}

void tiemrElapsed(void)
{
//    TIMEVAL current_counter = GPT_GetCurrentTimerCount(CANOPEN_TIMER_HW_BASE);
//
//    if (current_counter >= g_next_dispatch_counter_val) {
//        g_last_dispatch_counter_val = current_counter;
//        TimeDispatch();
//    }

    g_elapsed_time = 0;
    g_last_dispatch_counter_val = 0;

    TimeDispatch();
}

#if defined (USE_RTOS) && (USE_RTOS == 1)

void initTimer(void)
{

}

void clearTimer(void)
{

}

void CANOPEN_TIMER_ISR(void)
{
    tiemrElapsed();
}

#else

void initTimer(void)
{
    gpt_config_t cfg;

    GPT_GetDefaultConfig(&cfg);

    cfg.divider = 3; // 75MHz / 3 = 25MHz
    cfg.enableFreeRun = true;
    cfg.enableMode = false;

    GPT_Init(CANOPEN_TIMER_HW_BASE, &cfg);

//    GPT_EnableInterrupts(CANOPEN_TIMER_HW_BASE, kGPT_RollOverFlagInterruptEnable);
    GPT_EnableInterrupts(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare1InterruptEnable);

    EnableIRQ(CANOPEN_TIEMR_IRQn);

    GPT_StartTimer(CANOPEN_TIMER_HW_BASE);
}

void clearTimer(void)
{
    GPT_Deinit(CANOPEN_TIMER_HW_BASE);

//    GPT_DisableInterrupts(CANOPEN_TIMER_HW_BASE, kGPT_RollOverFlagInterruptEnable);
    GPT_DisableInterrupts(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare1InterruptEnable);

    DisableIRQ(CANOPEN_TIEMR_IRQn);

    GPT_StopTimer(CANOPEN_TIMER_HW_BASE);
}

void CANOPEN_TIMER_ISR(void)
{
//    GPT_ClearStatusFlags(CANOPEN_TIMER_HW_BASE, kGPT_RollOverFlag);
    GPT_ClearStatusFlags(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare1Flag);

    tiemrElapsed();

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
    #if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
        __DSB();
    #endif
}

#endif // defined (USE_RTOS) && (USE_RTOS == 1)
