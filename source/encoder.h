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

#ifndef ENCODER_H
#define ENCODER_H

#include <project.h>

void Encoder_Init();
void Encoder_Start();
int32 Encoder_GetLeftCount();
int32 Encoder_GetRightCount();
void Encoder_Reset();

#endif
/* [] END OF FILE */
