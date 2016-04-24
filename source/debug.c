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

#include "debug.h"

#define COMMS_DEBUG_ENABLED

// https://www.raspberrypi.org/forums/viewtopic.php?f=91&t=134391


void Debug_Init()
{
    memset(formatted_string, 0, sizeof(formatted_string));
}

void Debug_Start()
{
#ifdef COMMS_DEBUG_ENABLED
    UART_Debug_Start();
#endif
}

/* [] END OF FILE */
