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

#define TRACK_WIDTH (403.0) // millimeter
#define MILLIMETER_PER_REVOLUTION (479.0)
#define COUNTS_PER_REVOLUTION (36.0 * 4)  /* 36 teeth per revolution (4x encoder) */
#define MILLIMETER_PER_COUNT (MILLIMETER_PER_REVOLUTION/COUNTS_PER_REVOLUTION)

#define SAMPLE_RATE (20) /* Hz */
#define SAMPLE_PERIOD (1000/SAMPLE_RATE) /* milliseconds */

#define SAMPLE_MILLIMETER_PER_SECOND (SAMPLE_RATE * MILLIMETER_PER_COUNT)
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
    int32 left_count;
    int32 right_count;
    int32 delta_left_count;
    int32 delta_right_count;
    float delta_heading;
    float delta_dist;
    float delta_x_dist;
    float delta_y_dist;
    
    /* calculate delta left/right count */
    left_count = Encoder_GetLeftCount();
    right_count = Encoder_GetRightCount();    
    delta_left_count = left_count - last_left_count;
    delta_right_count = right_count - last_right_count;
    last_left_count = left_count;
    last_right_count = right_count;
    
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
    
    /* Update left/right, linear, and angular speeds
                count    sample    meter
       speed = ------- X ------ X ------
                sample    sec      count
    */
    left_speed = delta_left_count * SAMPLE_MILLIMETER_PER_SECOND;
    right_speed = delta_right_count * SAMPLE_MILLIMETER_PER_SECOND;

    linear_speed = ( right_speed + left_speed ) / 2;
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

int16 Odom_GetVelocity()
{
#ifdef LEFT_BOARD
    return (int16) left_speed;
#elif defined RIGHT_BOARD
    return (int16) right_speed;
#else
    #error "You haven't defined a board, e.g. LEFT_BOARD or RIGHT_BOARD"
#endif
}


/* [] END OF FILE */
