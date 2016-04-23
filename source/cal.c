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

#include "cal.h"
#include "motor.h"
#include "i2c.h"

/* An explanation for how calibration can work:
        1. Calibration data will be stored in a file on the Raspberry Pi
            Note: That eliminates the need for any type of NVRAM or additional peripheral hardware
        2. A calibration program will be run from the Raspberry Pi.  It will communicate with the Psoc
           boards over the I2C bus using the control register to invoke calibration and another address
            (2 bytes) to read each value from the Psoc.
            Note: There will be a known number of entries (150) in the calibration array
        3. To start calibration, the calibration program will set the calibration bit in the control
           register
        4. The Psoc will then set the calibration bit in the status register and start calibration
             a. Psoc with run the motor from full forward to stop
             b. Measure motor speed and calculate an average count/sec and capture min/max pwm values
             c. Store the pwm min/max values for each count/sec calulation
             d. Calculate an average pwm from the min/max values
             e. Interpolate between each sampled count/sec to fill out the PWM array
        5. The calibration program will poll the calibration bit in the status register waiting for it to
           be cleared
        6. The Psoc will clear the calibration bit in the status register when calibration is complete
            Note: It may be better to write the first calibration value into the calibration register before
                  clearing the calibration bit in the status register
        7. Now, how to handshake and transfer the data?
            a. After clearing the calibration bit of the status register, the Psoc will write a value from
                calibration array to the I2C calibration register and poll waiting for the value to be 
                cleared by the calibration program
            b. The calibration program will poll the calibration register waiting for its value to become
                non-zero.  After reading the calibration value, the calibration program will clear the 
                calibration register
            c. Steps a. and b. will repeat until all the values have been written
            d. After Psoc writes the last calibration value to the calibration register, it will write the
                value 0xFFFF signifying the end of the transmission.
 */

#define CAL_START_TRANSFER (0xFF00)
#define CAL_END_TRANSFER   (0xFFFF)
#define CAL_ACK_TRANSFER   (0x0000)

static void SendData(uint16 *cal_values, uint16 num_entries)
{
    int ii;
    
    I2c_WriteCalReg(CAL_START_TRANSFER);
    
    while (I2c_ReadCalReg() != CAL_ACK_TRANSFER);
    
    for (ii = 0; ii < num_entries; ++ii)
    {
        I2c_WriteCalReg(cal_values[ii]);
        while (I2c_ReadCalReg() != CAL_ACK_TRANSFER);
    }
    
    I2c_WriteCalReg(CAL_END_TRANSFER);    
    while (I2c_ReadCalReg() != CAL_ACK_TRANSFER);
}

static void RecvData(uint16 *cal_values, uint16 *num_entries)
{
    uint16 value;
    uint16 index;
    
    index = 0;
    
    while (I2c_ReadCalReg() != CAL_START_TRANSFER) ;
    
    while ( (value = I2c_ReadCalReg()) != CAL_END_TRANSFER)
    {
        // Acknowledge the transfer and store the value
        I2c_WriteCalReg(0);
        cal_values[index] = value;
    }
    I2c_WriteCalReg(0);
    *num_entries = index + 1;
}

void Cal_Init()
{
}

void Cal_Start()
{
    /* Note: The Psoc code contains defaults for all configurable parameters, so by definition it is calibrated with
       defaults and the calibrated bit is set.    
     */
    I2c_SetStatusBit(STATUS_CALIBRATED_BIT);
}

void Cal_Update()
{   
    /* Write to the serial that we are calibrating: CALIBRATING !!!! */
    
    I2c_ClearStatusBit(STATUS_CALIBRATED_BIT);
    I2c_SetStatusBit(STATUS_CALIBRATING_BIT);
    
    Motor_Calibrate();
    //Motor_ValidateCalibration();
    
    I2c_ClearStatusBit(STATUS_CALIBRATING_BIT);
    I2c_SetStatusBit(STATUS_CALIBRATED_BIT);

    /* Write to the serial that we are done: CALIBRATION COMPLETE !!!! */
}

void Cal_Download()
{
    uint16 *cal_values;
    uint16 num_entries;
    
    /* Write to the serial that we are loading calibration: LOADING CALIBRATION !!!! */
    
    Motor_GetCalValues((int16**) &cal_values, &num_entries);

    SendData(cal_values, num_entries);
    
    /* Write to the serial that we are done: LOAD COMPLETE !!!! */
}

void Cal_Upload()
/* Upload program will:
    1. send command to upload calibration data
    2. poll on status calibrated/calibrating bits (see above)
    3. send start transfer value
    4. send calibration values
        a. Psoc will read the value and set the calibration register to 0 to acknowledge the transfer
    5. send end transfer value    
 */
{
    uint16 *cal_values;
    uint16 num_entries;
    
    /* Write to the serial that we are loading calibration: LOADING CALIBRATION !!!! */
    
    I2c_ClearStatusBit(STATUS_CALIBRATED_BIT);
    I2c_SetStatusBit(STATUS_CALIBRATING_BIT);
    
    Motor_GetCalValues((int16**) &cal_values, &num_entries);
    
    RecvData(cal_values, &num_entries);
    
    I2c_ClearStatusBit(STATUS_CALIBRATING_BIT);
    I2c_SetStatusBit(STATUS_CALIBRATED_BIT);
    
    /* Write to the serial that we are done: LOAD COMPLETE !!!! */
}

void Cal_Validate()
{
    /* Write to the serial port that we are validating calibration: VALIDATING CALIBRATION !!! */
    
    Motor_ValidateCalibration();
    
    /* Write to the serial port that we are done: VALIDATION COMPLETE !!! */
}

/* [] END OF FILE */
