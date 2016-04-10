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

#include "ultrasonic.h"
#include "i2c.h"
#include "utils.h"
#include "time.h"
#include "debug.h"
#include "hwconfig.h"

#define MAX_TIMEOUT_US (50000)

#define MIN_PULSE_US (114)
#define MAX_PULSE_US (23200)
#define AVG_SAMPLES (10)

#define PULSE_WIDTH_10US (10)
#define US_PER_CENTIMETER (58)

typedef struct _tag_sensors
{
    uint16 min_pulse;
    uint16 max_pulse;
    uint32 average;
    MOVING_AVERAGE_TYPE moving_average;
} SENSORS_TYPE;


static volatile uint8 captured = 0;
static volatile uint16 count;

static uint32 last_time = 0;
static uint32 last_print_time = 0;
static SENSORS_TYPE sensors[NUM_ULTRASONIC_SENSORS];

typedef void (*PIN_TRIGGER_WRITE_TYPE)(uint8 value);

static PIN_TRIGGER_WRITE_TYPE triggers[NUM_ULTRASONIC_SENSORS] = 
{
    HCSR04_Trigger_0_Write,
    HCSR04_Trigger_1_Write,
    HCSR04_Trigger_2_Write,
    HCSR04_Trigger_3_Write
    //HCSR04_Trigger_4_Write,
    //HCSR04_Trigger_5_Write,
    //HCSR04_Trigger_6_Write,
    //HCSR04_Trigger_7_Write
};

CY_ISR( InterruptHandler )
{
    count = HCSR04_Timer_ReadCounter();
    if (count >= MIN_PULSE_US)
    {
        count = min(count, MAX_PULSE_US);
        captured = 1;
    }
    
    HCSR04_Timer_ClearInterrupt( HCSR04_Timer_INTR_MASK_CC_MATCH );
}

static void PulseOut(uint16 width, uint8 offset)
{
    triggers[offset](0);
    triggers[offset](1);
    CyDelayUs(width);
    triggers[offset](0);
}

static uint8 WaitForPulseIn()
{
    last_time = millis();
    while (!captured && (millis() - last_time) < 10)
    {
    }
    
    return captured;
}

static uint16 CalcDistance(uint8 index)
{
    sensors[index].max_pulse = max(count, sensors[index].max_pulse);
    sensors[index].min_pulse = min(count, sensors[index].min_pulse);
    
    sensors[index].average = MovingAverage(&sensors[index].moving_average, count);
    
    return sensors[index].average/58;
}

void Ultrasonic_Init()
{
    uint8 ii;
    for (ii = 0; ii < NUM_ULTRASONIC_SENSORS; ++ii)
    {
        sensors[ii].average = 0;
        sensors[ii].min_pulse = MAX_PULSE_US;
        sensors[ii].max_pulse = MIN_PULSE_US;
        sensors[ii].moving_average.last = 0;
        sensors[ii].moving_average.n = AVG_SAMPLES;
    }
}

void Ultrasonic_Start()
{
    HCSR04_Timer_Start();
    HCSR04_Timeout_Intr_StartEx(InterruptHandler);
}

void Ultrasonic_Measure()
{
    uint8 ii;
    uint16 distance;
    uint8 result;
    
    for (ii = 0; ii < NUM_ULTRASONIC_SENSORS; ++ii)
    {
        /* Clear flag indicating a count has been captured */
        captured = 0;
        
        /* Select the echo pin via the mux */
        HCSR04_Control_Write(ii);
        
        /* Pulse the trigger pin */
        PulseOut(PULSE_WIDTH_10US, ii);
        
        /* Wait for the timer to count the input width */
        result = WaitForPulseIn();
        
        if (result)
        {
            distance = CalcDistance(ii);                
            I2c_WriteUltrasonicDistance(ii, distance);
            
            if (millis() - last_print_time > 1000)
            {
                last_print_time = millis();
                //COMMS_DEBUG_PRINT(0, "N: %d, X: %d, C: %ld\n\r", sensors[ii].min_pulse, sensors[ii].max_pulse, sensors[ii].average);
            }
            
        }
    }        
}


void Ultrasonic_Test()
{
    //uint16 pulse = 0;
    //uint16 distance = 0;
    //uint32 average = 0;
    //static uint16 max_pulse;
    //static uint16 min_pulse;
    uint8 ii;

    captured = 0;
    
    for (ii = 0; ii < 2; ++ii)
    {
        HCSR04_Control_Write(ii);
        PulseOut(10, ii);
        CyDelay(100);
    
#ifdef xxx
        while (!captured)
        {
            //DEBUG_PRINT(0, "Timer Count: %ld\n\r", HCSR04_Timer_ReadStatus());
            CyDelay(1);
        }
        
        if (!captured)
        {
            DEBUG_PRINT(0, "Timeout: %d\n\r", 500);
        }
        else
        {
            DEBUG_PRINT(0, "[%d] - C: %d\n\r", ii, count);
            if (count > max_pulse)
            {
                max_pulse = count;
            }
            if (count < min_pulse)
            {
                min_pulse = count;
            }
            average = MovingAverage(&ma, count);
        }
#endif
        
    }    
}

/* [] END OF FILE */
