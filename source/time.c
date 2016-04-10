/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "time.h"

#define SYSTICK_EACH_1000_HZ  (1000u)
#define SYSTICK_RELOAD      (CYDEV_BCLK__SYSCLK__HZ / SYSTICK_EACH_1000_HZ)

static uint32 ms_counter;

/* Interrupt prototype */
static CY_ISR_PROTO(SysTickIsrHandler);
 
static CY_ISR(SysTickIsrHandler)
{
    ms_counter++;
}


void Time_Init()
{
    ms_counter = 0;
}

void Time_Start()
{
    uint32 ii;
    
    /* Starts SysTick component */
    CySysTickStart();
 
    /* Configure SysTick timer to generate interrupt every 1 ms */
    CySysTickSetReload(SYSTICK_RELOAD);
 
    /* Find unused callback slot. */
    for (ii = 0u; ii < CY_SYS_SYST_NUM_OF_CALLBACKS; ++ii)
    {
        if (CySysTickGetCallback(ii) == NULL)
        {
            /* Set callback */
            CySysTickSetCallback(ii, SysTickIsrHandler);
            break;
        }
    }
}

uint32 millis()
{
    return ms_counter;
}

/* [] END OF FILE */
