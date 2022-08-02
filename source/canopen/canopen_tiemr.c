/*
 * canopen_tiemr.c
 *
 *  Created on: 2022年7月29日
 *      Author: renqingyun
 */


#include "fsl_gpt.h"
#include "canfestival/mimxrt1052/canfestival.h"
#include "canfestival/timers.h"

#define IRQ_NUM(x)      x ## _IRQn
#define IRQ_ISR(x)      x ## _IRQHandler

#define CANOPEN_TIMER_HW_BASE   GPT2
#define CANOPEN_TIEMR_IRQn      IRQ_NUM(GPT2)
#define CANOPEN_TIMER_ISR       IRQ_ISR(GPT2)

#define g_next_dispatch_counter_val CANOPEN_TIMER_HW_BASE->OCR[kGPT_OutputCompare_Channel1]

TIMEVAL g_next_dispatch_counter_base = 0;

TIMEVAL g_last_dispatch_counter_val = 0;


void setTimer(TIMEVAL value)
{
    g_next_dispatch_counter_val = g_next_dispatch_counter_base + value;
}

TIMEVAL getElapsedTime(void)
{
    g_next_dispatch_counter_base = GPT_GetCurrentTimerCount(CANOPEN_TIMER_HW_BASE);

    return g_next_dispatch_counter_base - g_last_dispatch_counter_val;
}

void tiemrElapsed(void)
{
    TIMEVAL current_timer_count = GPT_GetCurrentTimerCount(CANOPEN_TIMER_HW_BASE);
    TIMEVAL expect_timer_count = g_next_dispatch_counter_val;

    if ((current_timer_count - g_last_dispatch_counter_val) >=
            (expect_timer_count - g_last_dispatch_counter_val)) {
        g_last_dispatch_counter_val = expect_timer_count;
        TimeDispatch();
    }
}

void initTimer(void)
{
    gpt_config_t cfg;

    GPT_GetDefaultConfig(&cfg);

    cfg.divider = 3; // 75MHz / 3 = 25MHz
    cfg.enableFreeRun = true;
    cfg.enableMode = false;

    GPT_Init(CANOPEN_TIMER_HW_BASE, &cfg);

    GPT_EnableInterrupts(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare1InterruptEnable);

    EnableIRQ(CANOPEN_TIEMR_IRQn);

    GPT_StartTimer(CANOPEN_TIMER_HW_BASE);
}

void clearTimer(void)
{
    GPT_Deinit(CANOPEN_TIMER_HW_BASE);

    GPT_DisableInterrupts(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare1InterruptEnable);

    DisableIRQ(CANOPEN_TIEMR_IRQn);

    GPT_StopTimer(CANOPEN_TIMER_HW_BASE);
}

void CANOPEN_TIMER_ISR(void)
{
    if (GPT_GetStatusFlags(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare1Flag) != 0) {
        GPT_ClearStatusFlags(CANOPEN_TIMER_HW_BASE, kGPT_OutputCompare1Flag);

        tiemrElapsed();
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
    #if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
        __DSB();
    #endif
}
