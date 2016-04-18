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

#include "hwconfig.h"
#include "odom.h"
#include "encoder.h"
#include "math.h"
#include "time.h"
#include "i2c.h"
#include "utils.h"

#define SAMPLE_RATE (10) /* Hz */
#define SAMPLE_PERIOD (1000/SAMPLE_RATE) /* milliseconds */

#define MILLIMETER_COUNT_SAMPLE_MILLIMETER (MILLIMETER_PER_COUNT / TRACK_WIDTH)

static int32 last_left_count;
static int32 last_right_count;
static float heading;
static float x_dist;
static float y_dist;
static float linear_speed;
static float angular_speed;
static float left_speed;
static float right_speed;

void Odom_Init()
{
    last_left_count = 0;
    last_right_count = 0;
    heading = 0;
    x_dist = 0;
    y_dist = 0;
    linear_speed = 0;
    angular_speed = 0;
    left_speed = 0;
    right_speed = 0;
}

void Odom_Start()
{
}

void calc_odom()
/*
    Calculate the following:
        heading
            Requires: left/right delta count
        x/y distance
            Requires: heading and dist per count
        linear/angular velocity
            Requires: left/right delta count, left/right speed and track width
 */
{
    static int32 last_left_count;
    static int32 last_right_count;
    int32 left_count;
    int32 right_count;
    int32 delta_left_count;
    int32 delta_right_count;
    float delta_heading;
    float delta_dist;
    float delta_x_dist;
    float delta_y_dist;
    int16 left_speed;
    int16 right_speed;
    
    Encoder_GetLRSpeed(&left_speed, &right_speed);
    Encoder_GetLRCount(&left_count, &right_count);
    
    delta_left_count = left_count - last_left_count;
    delta_right_count = right_count - last_right_count;
    
    Encoder_GetLRCount(&last_left_count, &last_right_count);
    
    /* Calculate heading, limit heading to -Pi <= heading < Pi, and update
                       delta count diff   meter   sample
       delta heading = ----------------- X ----- X ------
                          sample           count   meter
    */
    delta_heading = (delta_right_count - delta_left_count) * MILLIMETER_COUNT_SAMPLE_MILLIMETER;
    heading += delta_heading;

    // Calculate x/y distance and update
    delta_dist = 0.5 * (delta_left_count + delta_right_count) * MILLIMETER_PER_COUNT;
    delta_x_dist = delta_dist * cos(heading);
    delta_y_dist = delta_dist * sin(heading);

    x_dist += delta_x_dist;
    y_dist += delta_y_dist;
    
    linear_speed = (right_speed + left_speed) / 2;
    angular_speed = (right_speed - left_speed) / TRACK_WIDTH;
    
    I2c_WriteOdom(x_dist, y_dist, heading, linear_speed, angular_speed);
        
}

void Odom_Update()
{
    static uint32 last_odom_time = 0;
    uint32 delta_time;
    
    delta_time = millis() - last_odom_time;
    if (delta_time > SAMPLE_PERIOD)
    {
        last_odom_time = millis();
        calc_odom();
    }
}

/* [] END OF FILE */
