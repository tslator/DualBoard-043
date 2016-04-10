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

#ifndef PID_H
#define PID_H
    
#include <project.h>

/*------------------------------------------------------------------------------------------------
 Description: Initializes the gain parameters and sample rate
 Parameters: Kp - proportional gain
             Ki - integral gain
             Kd - derivative gain
             sample_rate - how often the PID controller is updated
 Return: None
 ------------------------------------------------------------------------------------------------*/
void PID_Init(float Kp, float Ki, float Kd, uint8 sample_rate);

/*------------------------------------------------------------------------------------------------
 Description: Starts the PID controller
 Parameters: None
 Return: None
 ------------------------------------------------------------------------------------------------*/
void PID_Start();

/*------------------------------------------------------------------------------------------------
 Description: Updates the PID controller
 Parameters: None
 Return: None
 ------------------------------------------------------------------------------------------------*/
void PID_Update();

void PID_SetOutput();

#endif

/* [] END OF FILE */
