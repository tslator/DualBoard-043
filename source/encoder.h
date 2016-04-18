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
void Encoder_Update();
void Encoder_Reset();
/* Returns the calculated speed for both the left and right wheels
 */
void Encoder_GetLRSpeed(int16* left, int16* right);

/* Returns the calculated speed for the wheel attached to this board 
 */
int16 Encoder_GetWheelSpeed();

/* Returns the encoder count */
int32 Encoder_GetCount();

/* Returns the encoder count for both left and right wheels
 */
void Encoder_GetLRCount(int32* left, int32* right);

#endif
/* [] END OF FILE */
