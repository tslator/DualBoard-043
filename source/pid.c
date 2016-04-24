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

#define SAMPLE_RATE (20) // Hz
#define SAMPLE_PERIOD (1000/SAMPLE_RATE) /* milliseconds */

#define MIN_SAMPLE_RATE (0)
#define MAX_SAMPLE_RATE (1)

#ifdef LEFT_BOARD
#define DEFAULT_KP (0.3)
#define DEFAULT_KI (0.0)
#define DEFAULT_KD (0.0)
#elif defined RIGHT_BOARD
#define DEFAULT_KP (0.03)
#define DEFAULT_KI (0.003)
#define DEFAULT_KD (5)
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"    
#endif

static float p_gain = DEFAULT_KP;
static float i_gain = DEFAULT_KI;
static float d_gain = DEFAULT_KD;
static float p_error;
static float i_error;
static float d_error;
static float i_min = -1.0;
static float i_max = 1.0;
static float p_error_last = 0;


/*---------------------------------*/

static void PrintPid()
{
    //COMMS_DEBUG_PRINT(0, "v: %d, i: %d, o: %2.1f, a: %d\n\r", velocity, input, output, adjust);
    {
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%f,%f,%f,%f,\r\n", p_error, i_error, d_error, p_error_last);
    UART_Debug_PutString(buffer);
    }
}

void PID_Init()
{
}

void PID_Start()
{
    
}

static float PID_Calc(float error, float target, uint32 delta_time)
{
    float p_term;
    float i_term;
    float d_term;
    
    p_error = error;
    
    if (delta_time == 0)
    {
        return 0.0;
    }
    
    p_term = p_gain * p_error;
    
    i_error += delta_time * p_error;
    
    i_term  = i_gain * i_error;
    
    if (i_term > i_max && i_gain != 0)
    {
        i_term = i_max;
        i_error = i_term / i_gain;
    }
    else if (i_term < i_min && i_gain != 0)
    {
        i_term = i_min;
        i_error = i_term / i_gain;
    }
    
    d_error = (p_error - p_error_last) / delta_time;
    p_error_last = p_error;
    
    // Calculate derivative contribution to command 
    d_term = d_gain * d_error;
    
    PrintPid();
    return target + p_term + i_term + d_term;
}

void PID_Update()
{
    static uint32 last_time = 0;
    int16 target;
    uint32 delta_time;
    static float error;
    static int16 input;
    
    delta_time = millis() - last_time;
    if (delta_time > SAMPLE_PERIOD)
    {    
        last_time = millis();

        /* Commanded velocity is in mm/s.  This needs to be converted to a unity value between -1.0 and 1.0 where
           -1.0/1.0 are the maximum mm/s possible.
           For example, in theory, the motor can turn at a maximum of 95 RPM (1.58 RPS).  At .4787 m per revolution, 
           the motor will turn at .7563 m/s (756 mm/s).
        
           Q: Is it possible to determine the maximum controllable speed for the motor?  If so, from that we can know
              the maximum possible mm/s.
        
           Assume the maximum controllable speed for the motor is +/- 635 mm/s, in that case, -1.0 .. 1.0 maps to -635
           .. 635 mm/s
        
           value = mm/s / max mm/s = 200 mm/s / 635 mm/s = 0.315
        
           The PID calculation can then be done in unity with out the need for additional scaling.
        
           The wheel velocity is in mm/s so it needs to be converted to unity
        
        */
        
        #define ScaleToUnity(input, neg_max, pos_max) (input < 0 ? (input/neg_max) : (input/pos_max) )
        
        I2c_ReadVelocity(&target);
        target = 300;
        
        //PID_Sample(target);
        input = Encoder_GetWheelSpeed();
        
        float scaled_output = ScaleToUnity(target, -582.0, 565.0);
        
        float scaled_input = ScaleToUnity(input, -582.0, 565.0);
        float scaled_target = ScaleToUnity(target, -582.0, 565.0);
        error = scaled_target - scaled_input;
        /*
        if (error > 0.0001)
        {
            if (scaled_input > scaled_target)
            {
                scaled_output -= (scaled_input - scaled_target)/2;
            }
            
            if (scaled_input < scaled_target)
            {
                scaled_output += (scaled_target - scaled_input)/2;
            }
        }
        */
        float output = PID_Calc(error, scaled_target, delta_time);
        
        Motor_SetOutput(output);
    }
    
}

#ifdef DATA_COLLECT
/* Assuming sample rate of 40ms, 250 * 40ms = 10 seconds */
int16 response[NUM_COLLECT_SAMPLES] = {0};
uint16 response_index = 0;
#endif

#ifdef STEP_RESPONSE
static void StepResponse(int16 velocity)
{
    static uint32 last_time = 0;
    static uint32 delta_time;

    Motor_SetOutput(velocity);
    
    delta_time = millis() - last_time;
    if (delta_time > STEP_SAMPLE_PERIOD)
    {    
        last_time = millis();

        Encoder_Sample(delta_time);
#ifdef DATA_COLLECT
        response[response_index] = Encoder_GetWheelSpeed();
        if (response_index < NUM_COLLECT_SAMPLES)
        {
            response_index++;
        }
        else
        {
            Motor_SetOutput(0);
            response_index = 0;
        }
#endif    
    }
}
#endif

#ifdef PID_ITERATION
static void PidIteration(int16 velocity)
{
    static uint32 last_time = 0;
    static uint32 delta_time;

    delta_time = millis() - last_time;
    if (delta_time > ITER_SAMPLE_PERIOD)
    {    
        last_time = millis();
        Encoder_Sample(delta_time);
        PID_Sample(velocity);        
#ifdef DATA_COLLECT
        response[response_index] = Encoder_GetWheelSpeed();
        if (response_index < NUM_COLLECT_SAMPLES)
        {
            response_index++;
        }
        else
        {
            Motor_SetOutput(0);
            response_index = 0;
        }
#endif    
    }
}
#endif

#ifdef PID_TUNE
void PID_Tune()
{
    /* Get Step Response */
#ifdef STEP_RESPONSE
    StepResponse(STEP_VELOCITY);
#endif
#ifdef PID_ITERATION
    PidIteration(ITER_VELOCITY);
#endif
}
#endif

/* [] END OF FILE */
