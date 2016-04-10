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

#include "motor.h"
#include "utils.h"
#include "debug.h"
#include "hwconfig.h"

/* Add a link to the HB25 data sheet
   Ref:
 */

#define HB25_ENABLE_BIT (0)
#define HB25_PWM_BIT (1)
#define HB25_ENABLE (0)
#define HB25_DISABLE (1)

#define MIN_PWM_COUNT (800)
#define CNTR_PWM_COUNT (1500)
#define MAX_PWM_COUNT (2200)

#define PWM_PADDING (200)

#define REVERSE_PWM_COUNT (MAX_PWM_COUNT - PWM_PADDING)
#define STOP_PWM_COUNT (CNTR_PWM_COUNT)
#define FORWARD_PWM_COUNT (MIN_PWM_COUNT + PWM_PADDING)

#define MOTOR_DRIVE_ABSOLUTE_VALUE (100)
#define MIN_MOTOR_DRIVE (-MOTOR_DRIVE_ABSOLUTE_VALUE)
#define MAX_MOTOR_DRIVE (+MOTOR_DRIVE_ABSOLUTE_VALUE)
#define MID_VALUE (0)

#define MOTOR_RANGE (2 * MOTOR_DRIVE_ABSOLUTE_VALUE)
#define PWM_RANGE   (REVERSE_PWM_COUNT - FORWARD_PWM_COUNT)
//#define COUNT_RESOLUTION ((REVERSE_PWM_COUNT - FORWARD_PWM_COUNT)/MOTOR_RANGE)

/*
    Recommendation by Parallax:

    Safe Power-Up and Power-Down
    Remember, because the HB-25 responds to pulses like a servo, changing states on your microcontroller’s
    I/O pins at startup and shutdown can affect the HB-25 and set it into an unintended state. This includes
    the I/O pins changing between input and output as well as between output high and output low.
    If your microcontroller is powered up or powered down while the HB-25 is powered up, the
    HB-25 could receive a false trigger. To prevent this, use one of the following options:
    • Most reliable option:
    1. Power the microcontroller up first, using code that forces the program to wait until the
    HB-25 is powered up before sending pulses. Code examples are provided below.
    2. Power up the HB-25 for operation.
    3. When shutting down your application, cut off power to the HB-25 first.
    4. Power down your microcontroller last.
    • Or, power the HB-25 and the microcontroller at the same time using a double-post (dual-circuit)
    switch.
    • If there is the possibility that the HB-25 will be on before your microcontroller, use the example
    code as mentioned above to ensure that the HB-25 is properly initialized when the
    microcontroller is powered on. The I/O line connected to the HB-25 should be made LOW either
    before or immediately after the HB-25 powers up. If this does not happen the HB-25 may fail to
    respond to incoming pulses.
    If your application poses any potential safety risk and you need the HB-25 to shut off the motors when
    the microcontroller has lost power or has malfunctioned, enable the Timeout Feature described below
    before operation.

 */

void Motor_Init()
{
    HB25_Enable_Pin_Write(HB25_DISABLE);
}

void Motor_Start()
{
    /* Enable the power on the HB-25 motor 
       Note: The HB-25 has a specific initialization sequence that is handled in hardware.  All that is necessary in 
       software is to enable power to the HB-25 motor controller and start the PWM.  The PWM will be enabled on to the
       HB-25 signal pin when initialization completes.
     */
    HB25_Enable_Pin_Write(HB25_ENABLE);    
    HB25_PWM_Start();
}

void Motor_SetOutput(int16 value)
/* Incoming value units are millimeter per second.  It must be scaled to PWM range
 */
{
    uint16 pwm_compare;
    int32 scaled_value;
    
    scaled_value = DIRECTION * scale_integer(value, SPEED_RANGE, PWM_RANGE);    
    pwm_compare = constrain((uint16) (STOP_PWM_COUNT + scaled_value), (uint16) MIN_PWM_COUNT, (uint16) MAX_PWM_COUNT);
    
    //COMMS_DEBUG_PRINT(0, "v: %d, s: %ld, p: %d\n\r", value, scaled_value, pwm_compare);
    
    HB25_PWM_WriteCompare(pwm_compare);
}

void Motor_Stop()
{
    /* Reverse sequence to start:
        - Stop the PWM
        - Disable power to the HB-25
     */
    HB25_PWM_Stop();
    HB25_Enable_Pin_Write(HB25_DISABLE);
}

void Motor_Test()
{
}


/* [] END OF FILE */
