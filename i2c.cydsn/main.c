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
#include <project.h>

static uint8 buffer[1];

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    memset(buffer, 0, sizeof(buffer));
    
    EZI2C_1_EzI2CSetBuffer1(1, 1, buffer);
    EZI2C_1_Start();

    for(;;)
    {
        buffer[0]++;
        CyDelay(500);
    }
}

/* [] END OF FILE */
