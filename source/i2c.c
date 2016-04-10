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

#include "i2c.h"
#include "time.h"
#include "hwconfig.h"
#include "utils.h"

/*
    I2C Communication Data Layout

    offset     num bytes     name                           description
      00           2         [control register]             the control register supports 
                                                                - Bit 0: enable/disable of the HB25 motors
                                                                - Bit 1: clear encoder count
      02           2         [commanded velocity]           commanded velocity is in units of millimeters/second
      04           2         [commanded accel]              commanded velocity in in units of millimeters/second^2
    ------------------------------ Read/Write Boundary --------------------------------------------
      06           2         [device status]                contains bits that represent the status of the Psoc device
                                                               - Bit 0: HB25 Motor Controller Initialized
                                                               - Bit 1: M4-ATX Power Off
           <------ Encoder ------>
      08           4         [encoder count]                contains the encoder count.  It will be written to by the
                                                            board that is measuring the encoder and read from by the 
                                                            other board to calculate odometry
           <------ Odometry ------>
      12           4         [x distance]                   measured x distance
      16           4         [y distance]                   measured y distance
      20           4         [heading]                      measured heading
      24           4         [linear velocity]              measured linear velocity
      28           4         [angular velocity]             measured angular velocity
          <------ Ultrasonic ------>
      32          16         [ultrasonic distance]          ultrasonic distance is an array of 
                                                            distances from the ultrasonic sensors in 
                                                            centimeters, range 2 to 500
           <------ Infrared ------>
      48           8         [infrared distance]            infrared distance is an array of distances 
                                                            from the infrared sensors in centimeters, 
                                                            range 10 to 80
      55           1         [test]                         used for testing the i2c communication
      56        [empty]
 */

typedef struct
{
    uint16 control;
    int16  cmd_velocity;
    int16  cmd_acceleration;    
} __attribute__ ((packed)) WRITEONLY_TYPE;

typedef struct
{
    float x_dist;
    float y_dist;
    float heading;
    float linear_velocity;
    float angular_velocity;
} __attribute__ ((packed)) ODOMETRY;

typedef struct
{
    uint16 values[NUM_ULTRASONIC_SENSORS];
} __attribute__ ((packed)) ULTRASONIC;

typedef struct
{
    uint8 values[NUM_INFRARED_SENSORS];
} __attribute__((packed)) INFRARED;

typedef struct
{
    uint16 status;
    int32  encoder_count;
    ODOMETRY   odom;
    ULTRASONIC us;
    INFRARED   ir;
    uint8      test;
} __attribute__ ((packed)) READWRITE_TYPE;

typedef struct
{
    WRITEONLY_TYPE write_only;
    /*---------R/W Boundary -----------*/
    READWRITE_TYPE read_write;
} __attribute__ ((packed)) I2C_DATASTRUCT;


/* The following structure was created to allow the encoder count to be read from the other board.  The API doesn't
   provide for reading at an offset on the slave.  Fortunately, the encoder count is the second value in the interface, 
   so it isn't necessary to read all of the slave values.

    The first size bytes of the slave are as follows:
       status        - 2 bytes 
       encoder count - 4 bytes
 */
typedef struct
{
    uint16 status;
    int32  count;
} __attribute__((packed)) SLAVE_DATA_TYPE;


static I2C_DATASTRUCT i2c_buf;
static uint16 i2c_status;
static SLAVE_DATA_TYPE i2c_slave_data;

void I2c_Init()
{
    memset( &i2c_buf, 0, sizeof(i2c_buf));
    I2C_Master_Init();
}

void I2c_Start()
{
    EZI2C_Slave_EzI2CSetAddress1(I2C_ADDRESS);
    EZI2C_Slave_EzI2CSetBuffer1(sizeof(i2c_buf), sizeof(i2c_buf.write_only), (volatile uint8 *) &i2c_buf);
    EZI2C_Slave_Start();
    
    //I2C_Master_I2CSlaveInitReadBuf((uint8 *) &i2c_slave_data, sizeof(i2c_slave_data)); 
    I2C_Master_Start();
}

uint16 I2c_ReadControl()
{
    uint16 value;
    
    value = i2c_buf.write_only.control;
    i2c_buf.write_only.control = 0;
    
    return value;
}

void I2c_SetStatusBit(uint8 bit)
{
    i2c_status |= bit;
    i2c_buf.read_write.status = i2c_status;
}

void I2c_ClearStatusBit(uint8 bit)
{
    i2c_status &= ~bit;
    i2c_buf.read_write.status = i2c_status;
}

void I2c_ReadVelocity(int16* velocity)
{
    *velocity = i2c_buf.write_only.cmd_velocity;
}

void I2c_ReadAcceleration(int16* accel)
{
    *accel = i2c_buf.write_only.cmd_acceleration;
}

void I2c_WriteCount(int32 count)
{
    i2c_buf.read_write.encoder_count = count;
}

int32 I2c_ReadCount()
{
    uint32 time_remaining = 10;
    SLAVE_DATA_TYPE slave;
        
    I2C_Master_I2CMasterReadBuf(OTHER_BOARD_ADDR, (uint8*) &i2c_slave_data, sizeof(i2c_slave_data), I2C_Master_I2C_MODE_COMPLETE_XFER);

    while(0u == (I2C_Master_I2CMasterStatus() & I2C_Master_I2C_MSTAT_RD_CMPLT) && time_remaining)
    {
        // Wait read to be completed
        --time_remaining;
    }
    
    // Clear I2C Master status
    I2C_Master_I2CMasterClearStatus();
        
    return slave.count;
}

void I2c_WriteUltrasonicDistance(uint8 offset, uint16 distance)
{
    i2c_buf.read_write.us.values[offset] = distance;
}

void I2c_WriteInfraredDistance(uint8 offset, uint8 distance)
{
    i2c_buf.read_write.ir.values[offset] = distance;
}

void I2c_WriteOdom(float x_dist, float y_dist, float heading, float linear_speed, float angular_speed)
{
    i2c_buf.read_write.odom.x_dist = x_dist;
    i2c_buf.read_write.odom.y_dist = y_dist;
    i2c_buf.read_write.odom.heading = heading;
    i2c_buf.read_write.odom.linear_velocity = linear_speed;
    i2c_buf.read_write.odom.angular_velocity = angular_speed;
}

void I2c_WriteTest()
{
    static uint32 last_time = 0;
    static uint8 test_count = 1;
    
    if (millis() - last_time > 1000)
    {
        last_time = millis();
        i2c_buf.read_write.test = test_count++;
    }
}

/* [] END OF FILE */
