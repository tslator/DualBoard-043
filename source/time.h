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

#ifndef TIME_H
#define TIME_H
    
#include <project.h>

#define DELTA_TIME(n, l, p) ((n - l) > p ? 1 : 0)

void Time_Init();
void Time_Start();
uint32 millis();

#endif

/* [] END OF FILE */
