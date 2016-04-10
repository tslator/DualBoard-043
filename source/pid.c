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

#include <math.h>
#include "pid.h"
#include "encoder.h"
#include "motor.h"
#include "i2c.h"
#include "utils.h"
#include "debug.h"
#include "time.h"
#include "odom.h"

#define SAMPLE_RATE (20) // Hz
#define SAMPLE_PERIOD (1000/SAMPLE_RATE) /* milliseconds */

#define MIN_KP (0)
#define MAX_KP (1)
#define MIN_KI (0)
#define MAX_KI (1)
#define MIN_KD (0)
#define MAX_KD (1)
#define MIN_SAMPLE_RATE (0)
#define MAX_SAMPLE_RATE (1)

#define DEFAULT_KP (1.0)
#define DEFAULT_KI (0.5)
#define DEFAULT_KD (0.0)

static float Kp;
static float Ki;
static float Kd;

/*---------------------------------*/


typedef struct {
    double windup_guard;
    double proportional_gain;
    double integral_gain;
    double derivative_gain;
    double prev_error;
    double int_error;
    double control;
} PID;

static PID pid = {0.1, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD, 0.0, 0.01, 0.0};

void pid_calc(PID* pid, double curr_error)
{
    double diff;
    double p_term;
    double i_term;
    double d_term;
 
    // integration with windup guarding
    pid->int_error += curr_error;
    if (pid->int_error < -(pid->windup_guard))
        pid->int_error = -(pid->windup_guard);
    else if (pid->int_error > pid->windup_guard)
        pid->int_error = pid->windup_guard;
 
    // differentiation
    diff = curr_error - pid->prev_error;
 
    // scaling
    p_term = (pid->proportional_gain * curr_error);
    i_term = (pid->integral_gain     * pid->int_error);
    d_term = (pid->derivative_gain   * diff);
 
    // summation of terms
    pid->control = p_term + i_term + d_term;
 
    // save current error as previous error for next iteration
    pid->prev_error = curr_error;
}

void PID_Init(float p, float i, float d, uint8 sample_rate)
{
    Kp = p;
    Ki = i;
    Kd = d;
    sample_rate = constrain(sample_rate, MIN_SAMPLE_RATE, MAX_SAMPLE_RATE);
    pid.prev_error = 0;
    pid.int_error = 0;
}

void PID_Start()
{
    Kp = DEFAULT_KP;
    Ki = DEFAULT_KI;
    Kd = DEFAULT_KD;
}

static void PrintPid(PID *pid, int16 velocity)
{
    //COMMS_DEBUG_PRINT(0, "v: %d, i: %d, o: %2.1f, a: %d\n\r", velocity, input, output, adjust);
    {
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "\r\nc: %2.1f, dg: %2.1f, ie: %2.1f, ig: %2.1f, pe: %2.1f, pg: %2.1f, wg: %2.1f, v: %d", 
             pid->control, pid->derivative_gain, pid->int_error, pid->integral_gain,
             pid->prev_error, pid->proportional_gain, pid->windup_guard, velocity);
    UARTCOMMS_UartPutString(buffer);
    }
}

void PID_Update()
{
#ifndef PID_BYPASS
    static uint32 last_time = 0;
    static int16 new_velocity = 0;
    int16 velocity;
    int16 input = 0;
    uint32 delta_time;
    
    /* Read the velocity command */
    I2c_ReadVelocity(&velocity);
        
    delta_time = millis() - last_time;
    //if (DELTA_TIME(millis(), last_time, SAMPLE_PERIOD))
    if (delta_time > SAMPLE_PERIOD)
    {    
        last_time = millis();
        
        input = Odom_GetVelocity();       
        pid_calc(&pid, velocity - input); 
        new_velocity = input + pid.control;        
        Motor_SetOutput(new_velocity);
        PrintPid(&pid, new_velocity);
    }
    
#else
    Motor_SetOutput(velocity);
#endif
}


/* [] END OF FILE */
