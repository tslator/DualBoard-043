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

#include "control.h"
#include "i2c.h"
#include "encoder.h"
#include "motor.h"
#include "time.h"

/* The purpose of this module is to handle control changes to the system.
   The only thing considered at this point is shutting down the motors properly.
 */

#define POWER_ON_MOTOR      (0x0001)
#define CLEAR_ENCODER_COUNT (0x0002)

static uint32 last_time;

void Control_Init()
{
    last_time = millis();
}

void Control_Start()
{    
    /* Note: I'm not sure what to do here, was thinking that this could be a way to enabled/disabled features at startup */
    uint16 control = I2c_ReadControl();
}

void Control_Update()
{
    uint8 motor_state;
    uint8 clear_encoder_count;
    uint16 control;
    
    control = I2c_ReadControl();
    
    motor_state = control & POWER_ON_MOTOR;
    if ( motor_state )
    {
        Motor_Start();
    }
    else
    {
        Motor_Stop();
    }
    
    clear_encoder_count = control & CLEAR_ENCODER_COUNT;
    if (clear_encoder_count)
    {
        Encoder_Reset();
    }
    
}

/* [] END OF FILE */
