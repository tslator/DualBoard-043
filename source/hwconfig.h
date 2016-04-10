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
    
#define NUM_ULTRASONIC_SENSORS (4)
#define NUM_INFRARED_SENSORS (4)

// Note: The boards control motors that are opposite to each other which means that one motor is going forward and the
// other is going backwards.  Since both boards use common code we need a way to reverse the count.  Multiplying by 1,
// the forward case (BOARD_1), and multiplying by -1, the reverse case.
#ifdef BOARD_1
#define I2C_ADDRESS (0x08)
#define DIRECTION   (-1)
#define RIGHT_BOARD
#define OTHER_BOARD_ADDR (0x09)
#endif
#ifdef BOARD_2
#define I2C_ADDRESS (0x09)
#define DIRECTION   (1)
#define LEFT_BOARD
#define OTHER_BOARD_ADDR (0x08)
#endif
    
#define COMMS_DEBUG_ENABLED
    
#define MAX_VELOCITY (1000) // millimeter per second
#define SPEED_RANGE (2 * MAX_VELOCITY)
    

#endif

/* [] END OF FILE */
