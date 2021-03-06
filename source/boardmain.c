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
#include <stdio.h>
#include <project.h>
#include "control.h"
#include "i2c.h"
#include "pid.h"
#include "encoder.h"
#include "odom.h"
#include "motor.h"
#include "ultrasonic.h"
#include "infrared.h"
#include "time.h"
#include "debug.h"
#include "cal.h"
#include "diag.h"

int main()
{       
    CyGlobalIntEnable;      /* Enable global interrupts */
    
    /* Start this right away so that we debug as soon as possible */
    Debug_Init();
    Debug_Start();
    
    Diag_Init();
    Diag_Start();
        
    Control_Init();
    Time_Init();
    I2c_Init();
    Encoder_Init();
    Odom_Init();
    Motor_Init();
    Cal_Init();

    Control_Start();
    Time_Start();
    I2c_Start();
    PID_Start();
    Encoder_Start();
    Odom_Start();
    Motor_Start();
    Cal_Start();
    
    for(;;)
    {
#ifdef PID_TUNE
        PID_Tune();
#else    
        /* Update any control changes */
        Control_Update();
        /* Update encoder-related values */
        Encoder_Update();
        /* Update the odometry calculation */
        Odom_Update();
        /* Apply the velocity command to PID */
        PID_Update();
        /* Read the infrared sensors */
        Infrared_Measure();
        /* Read the ultrasonic sensors */
        Ultrasonic_Measure();
        /* Diagnostic update */
        Diag_Update();
#endif
    }
}

/* [] END OF FILE */
