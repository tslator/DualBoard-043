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
#include "utils.h"
#include "time.h"

static uint8 overflow = 0;
static uint8 underflow = 0;

static MOVING_AVERAGE_TYPE ma_left_delta_count;
static MOVING_AVERAGE_TYPE ma_right_delta_count;

static int16 left_wheel_velocity;
static int16 right_wheel_velocity;

static MOVING_AVERAGE_TYPE ma_left_wheel_velocity;
static MOVING_AVERAGE_TYPE ma_right_wheel_velocity;


CY_ISR( Phase_Counter_Interrupt_Handler )
{
    uint8 status;
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
    status = Phase_Counter_ReadStatusRegister();
    if (status & 0x04)
    {
        overflow = 1;
    }
    if (status & 0x08)
    {
        underflow = 1;
    }
}

#ifdef LEFT_BOARD
static int32 LeftCounterWrapper()
{
    return (int32) Phase_Counter_ReadCounter();
}
static int32 RightCounterWrapper()
{
    return I2c_ReadCount();
}
#define ReadCounter LeftCounterWrapper
#elif defined RIGHT_BOARD
static int32 RightCounterWrapper()
{
    return - ( (int32) Phase_Counter_ReadCounter() );
}
static int32 LeftCounterWrapper()
{
    return I2c_ReadCount();
}
#define ReadCounter RightCounterWrapper
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"
#endif

void Encoder_Init()
{
    Phase_Counter_WriteCounter(0);
    
    memset(&ma_left_delta_count, 0, sizeof(ma_left_delta_count));
    memset(&ma_right_delta_count, 0, sizeof(ma_right_delta_count));
    ma_left_delta_count.n = 10;
    ma_right_delta_count.n = 10;
    
    memset(&ma_left_wheel_velocity, 0, sizeof(ma_left_wheel_velocity));
    memset(&ma_right_wheel_velocity, 0, sizeof(ma_right_wheel_velocity));
    ma_left_wheel_velocity.n = 10;
    ma_right_wheel_velocity.n = 10;
    
    left_wheel_velocity = 0;
    right_wheel_velocity = 0;
}

void Encoder_Start()
{
    PhaseCounter_Intr_StartEx( Phase_Counter_Interrupt_Handler );    
}

void Encoder_Update()
{
    static int32 last_left_count = 0;
    static int32 last_right_count = 0;
    static uint32 last_capture_time = 0;
    static int16 left_count_per_second;
    static int16 right_count_per_second;
    static int32 left_count;
    static int32 right_count;
    static int32 left_delta_count;
    static int32 right_delta_count;
    static uint32 delta_time;


    left_count = LeftCounterWrapper();
    right_count = RightCounterWrapper();
    
    delta_time = millis() - last_capture_time;
    
    if (delta_time > 250)
    {
        last_capture_time = millis();
    
        left_delta_count = left_count - last_left_count;
        right_delta_count = right_count - last_right_count;

        last_left_count = LeftCounterWrapper();
        last_right_count = RightCounterWrapper();
        
        left_count_per_second = (left_delta_count * MS_IN_SEC) / (int32) delta_time;
        right_count_per_second =  (right_delta_count * MS_IN_SEC) / (int32) delta_time;

        /* Update left/right linear speeds
                    count     meter
           speed = ------- X -------
                     sec      count
        */
        left_wheel_velocity = MovingAverage(&ma_left_wheel_velocity, left_count_per_second * MILLIMETER_PER_COUNT);
        right_wheel_velocity = MovingAverage(&ma_right_wheel_velocity, right_count_per_second * MILLIMETER_PER_COUNT);
    
                    
#ifdef LEFT_BOARD
        I2c_WriteCount(LeftCounterWrapper());
        I2c_WriteCountPerSecond(left_count_per_second);
        I2c_WriteWheelVelocity(left_wheel_velocity);
#elif defined RIGHT_BOARD
        I2c_WriteCount(RightCounterWrapper());
        I2c_WriteCountPerSecond(right_count_per_second);
        I2c_WriteWheelVelocity(right_wheel_velocity);
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"
#endif

    }
}

void Encoder_GetLRSpeed(int16* left, int16* right)
{
    *left = left_wheel_velocity;
    *right = right_wheel_velocity;
}

int16 Encoder_GetWheelSpeed()
{
#ifdef LEFT_BOARD
    return left_wheel_velocity;
#elif defined RIGHT_BOARD
    return right_wheel_velocity;
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"
#endif
}

int32 Encoder_GetCount()
{
    return ReadCounter();
}

void Encoder_GetLRCount(int32* left, int32* right)
{
    *left = LeftCounterWrapper();
    *right = RightCounterWrapper();
}

void Encoder_Reset()
{
    Phase_Counter_WriteCounter(0);
}


/* [] END OF FILE */
