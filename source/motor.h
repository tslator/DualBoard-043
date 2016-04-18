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

#ifndef MOTOR_H
#define MOTOR_H

#include <project.h>

void Motor_Init();
void Motor_Start();
void Motor_SetOutput(int16 value);
void Motor_Stop();
void Motor_Calibrate();
void Motor_GetCalValues(int16** cal_values, uint16* num_entries);
void Motor_ValidateCalibration();

#endif

/* [] END OF FILE */
