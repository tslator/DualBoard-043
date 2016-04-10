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

#include <stdlib.h>
#include "hwconfig.h"
#include "encoder.h"
#include "i2c.h"

CY_ISR( Phase_Counter_Interrupt_Handler )
{
    /* Not sure what to do here.  This interrupt occurs on terminal count which basically means rollover.  For now, 
       just clear the interrupt.
    
       These are the status provided in the status register:
    
        [7]: Unused (0) 
        [6]: FIFO not empty 
        [5]: FIFO full 
        [4]: Capture status 
        [3]: Underflow status 
        [2]: Overflow status 
        [1]: A0 Zero status 
        [0]: Compare output
    
     */
    (void) Phase_Counter_ReadStatusRegister();
}

void Encoder_Init()
{
    Phase_Counter_WriteCounter(0);
}

void Encoder_Start()
{
    PhaseCounter_Intr_StartEx( Phase_Counter_Interrupt_Handler );    
}

int32 Encoder_GetLeftCount()
{
#ifdef LEFT_BOARD
    // The counter is a 32-bit (unsigned) value, but the encoder count is interpretted as a signed value
    return (int32) Phase_Counter_ReadCounter();
#elif defined RIGHT_BOARD
    return I2c_ReadCount();
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"
#endif
}

int32 Encoder_GetRightCount()
{
#ifdef LEFT_BOARD
    return I2c_ReadCount();
#elif defined RIGHT_BOARD
    // The counter is a 32-bit (unsigned) value, but the encoder count is interpretted as a signed value
    return (int32) Phase_Counter_ReadCounter();
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"
#endif
}

void Encoder_Reset()
{
    Phase_Counter_WriteCounter(0);
}

/* [] END OF FILE */
