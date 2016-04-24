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
#include "encoder.h"
#include "time.h"
#include <math.h>

/* Add a link to the HB25 data sheet
   Ref: https://www.parallax.com/sites/default/files/downloads/HB-25-Motor-Controller-Guide-v1.3.pdf
 */

#define HB25_ENABLE_BIT (0)
#define HB25_PWM_BIT (1)
#define HB25_ENABLE (0)
#define HB25_DISABLE (1)

/* Note: While technically the motors are reverse relative to each other, it is clearer to hide this difference from
   the code.  Therefore, while the pwm values will be different, for a code perspective the functionality will be the 
   same between the boards driving the motors.  For example, the pwm constants refer to forward and reverse even though
   the actual values are different and the motors are moving oppositely.

                            Left    Right
        PWM_FULL_FORWARD |  2000  | 1000  |
        PWM_STOP         |  1500  | 1500  |
        PWM_FULL_REVERSE |  1000  | 2000  |
        PWM_DECREMENT    |   -1   |   1   |
        PWM_INCREMENT    |    1   |  -1   |
        PWM_CAL_STEP     |   10   |  10   |
        PWM_MIN          |  2000  | 1500  |
        PWM_MAX          |  1500  | 1000  |
 */

#define PWM_BUFFER (200)
#define MAX_PWM_VALUE  (2000)
#define MID_PWM_VALUE  (1500)
#define MIN_PWM_VALUE  (1000)

#ifdef LEFT_BOARD
/* Per the HB-25 data sheet: 
	1.0 ms Full Reverse 
	1.5 ms Neutral (Off) 
    2.0 ms Full Forward
    
   Note: The datasheet is in error, it should be 1000 ms, 1500 ms and 2000 ms
 */
#define PWM_MAX_FULL_FORWARD (MAX_PWM_VALUE)
#define PWM_MAX_FULL_REVERSE (MIN_PWM_VALUE)
#define PWM_FULL_FORWARD (PWM_MAX_FULL_FORWARD - PWM_BUFFER)
#define PWM_STOP         (MID_PWM_VALUE)    
#define PWM_FULL_REVERSE (PWM_MAX_FULL_REVERSE + PWM_BUFFER)
#define PWM_RANGE        (PWM_FULL_FORWARD - PWM_STOP)
#define PWM_DECREMENT    (-1)
#define PWM_INCREMENT    (1)
#define PWM_MIN          (PWM_FULL_FORWARD)
#define PWM_MAX          (PWM_STOP)   
#define CAL_PWM_EVAL(limit) (pwm > limit)
#define DELTA_X             (1.0 - (-1.0))
#define DELTA_Y             (PWM_FULL_FORWARD - PWM_FULL_REVERSE)
#define UNITY_TO_PWM(value) ( ((DELTA_Y * value)/DELTA_X) + MID_PWM_VALUE )
#elif defined RIGHT_BOARD
#define PWM_MAX_FULL_FORWARD (MIN_PWM_VALUE)
#define PWM_MAX_FULL_REVERSE (MAX_PWM_VALUE)
#define PWM_FULL_FORWARD (PWM_MAX_FULL_FORWARD + PWM_BUFFER)
#define PWM_STOP         (MID_PWM_VALUE)    
#define PWM_FULL_REVERSE (PWM_MAX_FULL_REVERSE - PWM_BUFFER)
#define PWM_RANGE        (PWM_FULL_REVERSE - PWM_STOP)
#define PWM_DECREMENT     (1)
#define PWM_INCREMENT    (-1)
#define PWM_MIN          (PWM_STOP)
#define PWM_MAX          (PWM_FULL_FORWARD)
#define CAL_PWM_EVAL(limit) (pwm < limit)
#define DELTA_X             (1.0 - (-1.0))
#define DELTA_Y             (PWM_FULL_FORWARD - PWM_FULL_REVERSE)
#define UNITY_TO_PWM(value) ( ((DELTA_Y * value)/DELTA_X) + MID_PWM_VALUE )
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"
#endif


// Empirical step value that balances time, space, and accuracy
#define PWM_CAL_STEP     (10)
/* Empirical values to allow the pwm to settle.  Probably not particularly relevant since the pwm is done via hardware
   but it doesn't hurt (just adds little more time to calibration
 */
#define PWM_SETTLE_TIME  (1000)

/* 
    Calibration Constants

    Number of entries depends on the range and step size, e.g., smaller step more values and vice versa
 */
#define MAX_NUM_CAL_ENTRY (PWM_RANGE/PWM_CAL_STEP)
#define MIN_CAL_ENTRY (0)
#define MAX_CAL_ENTRY (MAX_NUM_CAL_ENTRY - 1)

/* The number of samples to take when measuring speed */
#define MAX_SPEED_SAMPLES (5)

#define CAL_PWM_START (PWM_FULL_FORWARD)
#define CAL_PWM_END (PWM_STOP)
#define CAL_PWM_STEP (PWM_DECREMENT*PWM_CAL_STEP)

#define CAL_VAL_CPS_START (20)
#define CAL_VAL_STEP (10)
#define CAL_VAL_NUM_SAMPLES (2)
#define CAL_VAL_SAMPLE_PERIOD (250) // milliseconds

/* Structure used to capture pwm and cps samples during calibration
 */
typedef struct
{
    int16 cps;
    uint16 pwm;
} CALIBRATION_ENTRY;

/* Mapping between count/sec and pwm derived during calibration
 */
static CALIBRATION_ENTRY cal_cps_to_pwm[MAX_NUM_CAL_ENTRY];

/* Count/Second to PWM Map

    Per the motor specification (https://www.parallax.com/product/28962):
        Approx. Max Speed: 95 RPM (1.53 RPS)
        Encoder Resolution: 36 position (quadrature encoding yields 144 counts per revolution)
        Wheel Circumference: 479 mm

    From the above, the motor has a max count/sec of 228 and max speed of 733 mm/s.  
    Empirical measurement gives a usable range of 0 .. 200 count/s and 655 mm/s.  Typically, the calibration captures a
    max count/sec between 180-190.  Your mileage may vary :-)

 */
#define MIN_CPS_VALUE (1)
#define MAX_CPS_VALUE (200)

#define MAX_NUM_CPS_ENTRY (MAX_CPS_VALUE)
#define MIN_CPS_ENTRY (0)
#define MAX_CPS_ENTRY (MAX_NUM_CPS_ENTRY - 1)


    
static uint8 cps_to_pwm_last_entry;

void Motor_Init()
{
    int ii;
    
    HB25_Enable_Pin_Write(HB25_DISABLE);
    
    // Initialize the balance of the array
    for (ii = MIN_CAL_ENTRY; ii < MAX_NUM_CAL_ENTRY; ++ii)
    {
        /* Need to figure out how to handle min/max for right motor case */
        cal_cps_to_pwm[ii].pwm = PWM_MIN;
        cal_cps_to_pwm[ii].cps = -1;
    }
    
    // Note: map_cps_to_pwm contains default pwm values and so it should not be initialized
    
    // Find the last non-stop value entry in the cps-to-pwm map
    for (ii = MAX_CPS_ENTRY; ii > MIN_CPS_ENTRY; --ii)
    {
        if (map_cps_to_pwm[ii] != PWM_STOP)
        {
            cps_to_pwm_last_entry = ii;
            break;
        }
    }
        
}

void Motor_Start()
{
    /* Enable the power on the HB-25 motor 
       Note: The HB-25 has a specific initialization sequence that is handled in hardware (see HB-25 reference).  All 
       that is necessary in software is to enable power to the HB-25 motor controller and start the PWM.  The PWM will 
       be enabled on to the HB-25 signal pin when initialization completes.
     */
    HB25_Enable_Pin_Write(HB25_ENABLE);    
    HB25_PWM_Start();
    Motor_SetOutput(0);
}

//void Motor_SetOutput(int16 value)
void Motor_SetOutput(float value)
/* Translate value, in millimeter per second to pwm via count/sec mapping
 */
{
    uint16 pwm;
    
    /* Map unity to pwm 
    
        -1.0 ... 1.0
        1000 ... 2000
    
         y = f(x), where y is 1000 ... 2000 and x is -1.0 ... 1.0
    
      Left Wheel          Right Wheel
        x      y            x    y
       -1.0   1000        -1.0  2000
        0.0   1500         0.0  1500
        1.0   2000         1.0  1000
    
      Yleft = 500x + 1500
      Yright = -500x + 1500
    
    */
    
    pwm = UNITY_TO_PWM(value);
    
    HB25_PWM_WriteCompare(pwm);
}

void Motor_Stop()
{
    HB25_PWM_Stop();
    HB25_Enable_Pin_Write(HB25_DISABLE);
}

static int16 CalculateAverageCountPerSec(uint8 samples, uint16 delay)
{
    uint8 ii;
    int32 count_start;
    int32 count_end;
    int32 deltas = 0;
    
    for (ii = 0; ii < samples; ++ii)
    {
        count_start = Encoder_GetCount();
        CyDelay(delay);
        count_end = Encoder_GetCount();
        deltas += count_end - count_start;
    }
    deltas /= samples;
    return (abs(deltas) * MS_IN_SEC) / delay;
}

void Motor_Calibrate()
/* The purpose of calibration is to find the maximum controllable PWM value

   Calibration is performed in three steps:

    1. Run the motor over the range of PWM values, calculating the speed at each pwm sample and storing the maximum 
       value in both forward and reverse.

 */
{
    uint16 pwm;
    int16 meas_cps;
    static int16 max_fwd_meas_cps;
    static int16 max_rvs_meas_cps;
    static uint16 max_pwm;
    static uint16 min_pwm;
    
    /* Run the motor from stop to full forward pwm */
    
    max_fwd_meas_cps = 0;
    
    HB25_PWM_WriteCompare(PWM_STOP);
    
    for (pwm = PWM_STOP; pwm <= PWM_FULL_FORWARD; pwm += 20)
    {   
        HB25_PWM_WriteCompare(pwm);
        /* Allow the motor to settle before measuing the speed.  Same thing here as above regarding how long.  Above
           the motor was stopped, here we're just changing the speed to be slightly slower.  I would have thought 100-
           200ms would be sufficient, but, again, 1sec gives the best and more accurate results.
         */
        CyDelay(PWM_SETTLE_TIME);

        /* Measure the speed and calculate an average
           Note: Averaging the delta counts proved more consistent than averaging cps
         */
        meas_cps = CalculateAverageCountPerSec(MAX_SPEED_SAMPLES, 200);
        if (meas_cps > max_fwd_meas_cps)
        {
            max_fwd_meas_cps = meas_cps;
            max_pwm = pwm;
        }
        
    }
    
    HB25_PWM_WriteCompare(PWM_STOP);
    
    for (pwm = PWM_STOP; pwm >= PWM_FULL_REVERSE; pwm -= 20)
    {   
        HB25_PWM_WriteCompare(pwm);
        /* Allow the motor to settle before measuing the speed.  Same thing here as above regarding how long.  Above
           the motor was stopped, here we're just changing the speed to be slightly slower.  I would have thought 100-
           200ms would be sufficient, but, again, 1sec gives the best and more accurate results.
         */
        CyDelay(PWM_SETTLE_TIME);

        /* Measure the speed and calculate an average
           Note: Averaging the delta counts proved more consistent than averaging cps
         */
        meas_cps = CalculateAverageCountPerSec(MAX_SPEED_SAMPLES, 200);
        if (meas_cps > max_rvs_meas_cps)
        {
            max_rvs_meas_cps = meas_cps;
            min_pwm = pwm;
        }
        
    }
    
    HB25_PWM_WriteCompare(PWM_STOP);
}

void Motor_ValidateCalibration()
{
    int ii;
    int16 meas_cps;
    static int16 values[20] = {0};
    uint8 index = 0;
    
    
    /* The following code tests that each entry selects a pwm value and results in a matching count/s wheel speed 
     */
    
    Encoder_Reset();
    
    for (ii = CAL_VAL_CPS_START; ii <= cps_to_pwm_last_entry; ii += CAL_VAL_STEP)
    {
        HB25_PWM_WriteCompare(map_cps_to_pwm[ii]);
        CyDelay(PWM_SETTLE_TIME);
        
        meas_cps = CalculateAverageCountPerSec(CAL_VAL_NUM_SAMPLES, CAL_VAL_SAMPLE_PERIOD);
        
        /* Report via the serial port the commanded cps and the meas_cps
          Commanded       Measured
            <cps>   ->   <meas_cps>
         */
        values[index] = meas_cps;
        index++;
    }
    
    HB25_PWM_WriteCompare(PWM_STOP);      
}

void Motor_GetCalValues(int16** cal_values, uint16* num_entries)
{
    *cal_values = (int16 *) map_cps_to_pwm;
    *num_entries = cps_to_pwm_last_entry + 1;
}

/* [] END OF FILE */
