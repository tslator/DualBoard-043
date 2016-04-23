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
 Parameters: None
 Return: None
 ------------------------------------------------------------------------------------------------*/
void PID_Init();

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

void PID_Tune();

#endif

/* [] END OF FILE */
