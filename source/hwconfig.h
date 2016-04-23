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

#ifndef HWCONFIG_H
#define HWCONFIG_H
    
#include <project.h>
    
#define NUM_ULTRASONIC_SENSORS (4)
#define NUM_INFRARED_SENSORS (4)

#define BOARD_1_I2C_ADDRESS (0x08)
#define BOARD_2_I2C_ADDRESS (0x09)
    
// Note: Each board controls a motor and receives encoder feeback.  Additionally, code running on each board need to 
// know the encoder count of the other motor, i.e., available on the other board.
// There are two boards, i.e., BOARD_1 and BOARD_2 defined on the compile command line, and each board is assigned
// as either LEFT_BOARD or RIGHT_BOARD, the relevant I2C addresses, and direction (because of the mounting, one motor 
// rotates forward and the other backward when the robot is moving forward).
#ifdef BOARD_1
#define I2C_ADDRESS (BOARD_1_I2C_ADDRESS)
#define OTHER_BOARD_ADDR (BOARD_2_I2C_ADDRESS)
#define DIRECTION   (1)
#define LEFT_BOARD
#endif
#ifdef BOARD_2
#define I2C_ADDRESS (BOARD_2_I2C_ADDRESS)
#define OTHER_BOARD_ADDR (BOARD_1_I2C_ADDRESS)
#define DIRECTION   (-1)
#define RIGHT_BOARD
#endif
    
#define COMMS_DEBUG_ENABLED

#define MAX_MILLIMETERS_PER_SECOND (500)
#define MIN_MILLIMETERS_PER_SECOND (-500)

#define MAX_VELOCITY (MAX_MILLIMETERS_PER_SECOND)
#define SPEED_RANGE (2 * MAX_VELOCITY)
    
#define TRACK_WIDTH (403.0) // millimeter
#define MILLIMETER_PER_REVOLUTION (479.0)
#define COUNTS_PER_REVOLUTION (36.0 * 4)  /* 36 teeth per revolution (4x encoder) */
#define MILLIMETER_PER_COUNT (MILLIMETER_PER_REVOLUTION/COUNTS_PER_REVOLUTION)
#define COUNT_PER_MILLIMETER (COUNTS_PER_REVOLUTION/MILLIMETER_PER_REVOLUTION)


#define PID_BYPASS
//#define PID_TUNE
//#define STEP_RESPONSE
//#define PID_ITERATION

#ifdef PID_TUNE

#define DATA_COLLECT

#ifdef STEP_RESPONSE
#define STEP_SAMPLE_RATE (20)    
#define STEP_SAMPLE_PERIOD (1000/STEP_SAMPLE_RATE)
#define NUM_COLLECT_SAMPLES (STEP_SAMPLE_RATE * 6)
#define STEP_VELOCITY (508)
#endif

#ifdef PID_ITERATION
#define ITER_SAMPLE_RATE (20)    
#define ITER_SAMPLE_PERIOD (1000/ITER_SAMPLE_RATE)
#define NUM_COLLECT_SAMPLES (ITER_SAMPLE_RATE * 15)
#define ITER_VELOCITY (508)
#endif

#endif


#endif

/* [] END OF FILE */
