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

#ifndef I2C_H
#define I2C_H

#include <project.h>
    
#define STATUS_ONOFF_DETECT_BIT (0x02)

void I2c_Init();
void I2c_Start();

uint16 I2c_ReadControl();
void I2c_ReadVelocity(int16* velocity);
void I2c_ReadAcceleration(int16* accel);
int32 I2c_ReadCount();
void I2c_SetStatusBit(uint8 bit);
void I2c_ClearStatusBit(uint8 bit);
void I2c_WriteCount(int32 count);
void I2c_WriteVelocity(int16 velocity_percent);
void I2c_WriteUltrasonicDistance(uint8 offset, uint16 distance);
void I2c_WriteInfraredDistance(uint8 offset, uint8 distance);
void I2c_WriteOdom(float x_dist, float y_dist, float heading, float linear_speed, float angular_speed);
void I2c_WriteTest();

#endif

/* [] END OF FILE */
