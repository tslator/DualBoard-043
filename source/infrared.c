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
#include <stdio.h>
#include "infrared.h"
#include "debug.h"
#include "time.h"
#include "i2c.h"
#include "utils.h"
#include "hwconfig.h"

/* The Sharp IR sensors have a range of 10 to 80 cm.  Working backward, this limits the ADC values as follows:

ADC    Voltage        Pow          cm           mm
327  0.399169922  2.875203044  80.10315682  801.0315682
350  0.427246094  2.659011307  74.08005503  740.8005503
375  0.457763672  2.456192932  68.42953508  684.2953508
...
1950 2.380371094  0.368857512  10.27637027  102.7637027
1995 2.435302734  0.359305694  10.01025665  100.1025665
 */
#define ADC_MIN_VALUE (327)
#define ADC_MAX_VALUE (1995)

/* External voltage reference */
#define ADC_REFERENCE (2.5)
/* ADC range is 2 * Vref */
#define ADC_FULL_RANGE (ADC_REFERENCE * 2)
/* ADC 16-bit resolution */
#define ADC_RESOLUTION (4096.0)
/* Interpolation equation and constants taken from here: 
       https://www.tindie.com/products/upgradeindustries/sharp-10-80cm-infrared-distance-sensor-gp2y0a21yk0f/
 */
#define SHARP_IR_SENSOR_INTERPOLATION_CONST_1 (27.86)
#define SHARP_IR_SENSOR_INTERPOLATION_CONST_2 (-1.15)

/* ADC measurements are taken continuously.  Sampling (or reporting) is done every 100ms */
#define SAMPLE_PERIOD (100) /* ms */

static uint32 last_time;

void Infrared_Init()
{
    last_time = 0;
}

void Infrared_Start()
{
    ADC_Infrared_Start();
}

void Infrared_Measure()
{
    int8 ii;
    uint16 result;
    float voltage;
    float distance;
    uint32 adc_result;
    
    ADC_Infrared_StartConvert();
    /* The way this should work is that the call will block until all channels are read which shouldn't take very long
       Running without any connected hardware causes this routine to hang forever, so maybe its because there is no
       hardware or there may be something else.  For now, using RETURN_STATUS -- revisit when hardware is connected.
     */
    //ADC_Infrared_IsEndConversion(ADC_Infrared_WAIT_FOR_RESULT);
    adc_result = ADC_Infrared_IsEndConversion(ADC_Infrared_RETURN_STATUS);
    if (!adc_result)
    {
        return;
    }
    
    if (millis() - last_time > SAMPLE_PERIOD)
    {
        last_time = millis();
        for (ii = 0; ii < NUM_INFRARED_SENSORS; ++ii)
        {
            result = ADC_Infrared_GetResult16(ii);
            result = constrain(result, ADC_MIN_VALUE, ADC_MAX_VALUE);
            voltage = (result * ADC_FULL_RANGE) / ADC_RESOLUTION;
            distance = SHARP_IR_SENSOR_INTERPOLATION_CONST_1 * pow(voltage, SHARP_IR_SENSOR_INTERPOLATION_CONST_2);
            //COMMS_DEBUG_PRINT(0, "ir distance %f\n\r", distance);
            I2c_WriteInfraredDistance(ii, distance);
        }
    }
}

void Infrared_Test()
{
    int8 ii;
    uint16 result;
    float voltage;
    float distance;
    static uint32 last_time;
    
    
    ADC_Infrared_StartConvert();
    ADC_Infrared_IsEndConversion(ADC_Infrared_WAIT_FOR_RESULT);

    if (millis() - last_time > 500)
    {
        last_time = millis();
        for (ii = 0; ii < 1; ++ii)
        {
            result = ADC_Infrared_GetResult16(ii);
            result = constrain(result, 327, 1995);
            
            voltage = (result * 5.0) / 4096.0;
            distance = 27.86 * pow(voltage, -1.15);
            COMMS_DEBUG_PRINT(0, "%d:%d,%d,%d\n\r", ii, result, (uint16)voltage*100, (uint16)distance*10);
        }
    }
    
}


/* [] END OF FILE */
