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
           <------ Encoder ------>
      00           4         [encoder count]                contains the encoder count.  It will be written to by the
                                                            board that is measuring the encoder and read from by the 
                                                            other board to calculate odometry
      04           2         [control register]             the control register supports 
                                                                - Bit 0: enable the HB25 motors
                                                                - Bit 1: clear encoder count
                                                                - Bit 2: calibrate - requests the Psoc to start calibrating
                                                                - Bit 3: upload calibration
                                                                - Bit 4: download calibration
                                                                - Bit 5: validate calibration
      06           2         [commanded velocity]           commanded velocity is in units of millimeters/second
      08           2         [commanded accel]              commanded velocity in in units of millimeters/second^2
      10           2         [calibration port]             the register through which calibration is passed to the Psoc
                                                            when loading calibration from the Raspberry Pi and also how
                                                            calibration data is passed from the Psoc to the Raspberry Pi
                                                            for storage in a file
    ------------------------------ Read/Write Boundary --------------------------------------------
      12           2         [device status]                contains bits that represent the status of the Psoc device
                                                               - Bit 0: HB25 Motor Controller Initialized
                                                               - Bit 1: Calibrated - indicates whether the calibration
                                                                        values have been loaded; 0 - no, 1 - yes
                                                               - Bit 2: Calibrating - indicates when the Psoc is in
                                                                        calibration; 0 - no, 1 - yes
        <---- Left/Right Velocity ---->
      14           2         [wheel velocity]
      16           2         [count per second]
           <------ Odometry ------>
      14           4         [x distance]                   measured x distance
      18           4         [y distance]                   measured y distance
      22           4         [heading]                      measured heading
      26           4         [linear velocity]              measured linear velocity
      30           4         [angular velocity]             measured angular velocity
          <------ Ultrasonic ------>
      34          16         [ultrasonic distance]          ultrasonic distance is an array of 
                                                            distances from the ultrasonic sensors in 
                                                            centimeters, range 2 to 500
           <------ Infrared ------>
      50           8         [infrared distance]            infrared distance is an array of distances 
                                                            from the infrared sensors in centimeters, 
                                                            range 10 to 80
      58           1         [test]                         used for testing the i2c communication
 */

/* Define the portion of the I2C Slave that Read/Write */
typedef struct
{
    int32  encoder_count;
    uint16 control;
    int16  cmd_velocity;
    int16  cmd_acceleration;
    uint16 calibration_port;
} __attribute__ ((packed)) READWRITE_TYPE;

/* Define the odometry structure for communicating the position, heading and velocity of the wheel 
   Note: Each Psoc board controls a single wheel, but calculates and reports odometry for the robot
 */
typedef struct
{
    float x_dist;
    float y_dist;
    float heading;
    float linear_velocity;
    float angular_velocity;
} __attribute__ ((packed)) ODOMETRY;

/* Define the structure for ultrasonic sensors */
typedef struct
{
    uint16 values[NUM_ULTRASONIC_SENSORS];
} __attribute__ ((packed)) ULTRASONIC;

/* Define the structure for infrared sensors */
typedef struct
{
    uint8 values[NUM_INFRARED_SENSORS];
} __attribute__((packed)) INFRARED;

/* Define the I2C Slave that Read Only */
typedef struct
{
    uint16     status;
    int16      wheel_velocity;
    uint16     count_per_sec;
    ODOMETRY   odom;
    ULTRASONIC us;
    INFRARED   ir;
    uint8      test;
} __attribute__ ((packed)) READONLY_TYPE;

/* Define the I2C Slave data interface */
typedef struct
{
    READWRITE_TYPE read_write;
    /*---------R/W Boundary -----------*/
    READONLY_TYPE read_only;
} __attribute__ ((packed)) I2C_DATASTRUCT;


/* The following structure was created to allow the encoder count to be read from the other board.  The API doesn't
   provide for reading at an offset on the slave.  So, unfortunately, we need to read from offset 0 through the encoder
   count.

   Note: It is possible to move the encoder count to the read/write section of the slave.  Something to think about.
 */
typedef struct
{
    int32  count;
} __attribute__((packed)) SLAVE_DATA_TYPE;

/* Define the I2C Slave buffer (as seen by the slave on this Psoc) */
static I2C_DATASTRUCT i2c_buf;
/* Define the I2C Slave buffer (as seen by the master on this Psoc) */
static SLAVE_DATA_TYPE i2c_slave_data;
/* Define a persistant status that can be set and cleared */
static uint16 i2c_status;


/*----------------------------------------------------------------------------------------------------------------------

  Statis Functions

 ---------------------------------------------------------------------------------------------------------------------*/

/* This function performs the write portion of an I2C read 
   allowing the master to read the encoder count on the other Psoc 
 */
static uint8 MasterWriteSlave(uint8 addr, uint8 *buf, uint8 len)
{
    uint8 volatile status;
    
    status = I2C_Master_I2CMasterClearStatus();
    if(!(status & I2C_Master_I2C_MSTAT_ERR_XFER))
    {
        status = I2C_Master_I2CMasterWriteBuf(addr, buf, len, I2C_Master_I2C_MODE_COMPLETE_XFER);
        if(status == I2C_Master_I2C_MSTR_NO_ERROR)
        {
            /* wait for write complete and no error */
            do
            {
                status = I2C_Master_I2CMasterStatus();
            } while((status & (I2C_Master_I2C_MSTAT_WR_CMPLT | I2C_Master_I2C_MSTAT_ERR_XFER)) == 0u);
        }
        else
        {
            /* translate from I2C_Master_I2CMasterWriteBuf() error output to
            *  I2CM_I2CMasterStatus() error output */
            status = (uint8)I2C_Master_I2C_MSTAT_ERR_XFER;
        }
    }
    
    return status;
}

/* This function performs the read portion of an I2C read 
   allowing the master to read the encoder count on the other Psoc
 */
static uint8 MasterReadSlave(uint8 address, uint8 offset, uint8 len, uint8 *buf)
{
    uint8 volatile status; /* copy of EZI2C activity status */
    
    status = MasterWriteSlave(address, &offset, 1);
    if(!(status & I2C_Master_I2C_MSTAT_ERR_XFER))
    {
        status = I2C_Master_I2CMasterClearStatus();
        if(!(status & I2C_Master_I2C_MSTAT_ERR_XFER))
        {
            status = I2C_Master_I2CMasterReadBuf(address, 
                                                 buf, 
                                                 len, 
                                                 I2C_Master_I2C_MODE_COMPLETE_XFER);
            if(status == I2C_Master_I2C_MSTR_NO_ERROR)
            {
                /* wait for read complete and no error */
                do
                {
                    status = I2C_Master_I2CMasterStatus();
                } while((status & (I2C_Master_I2C_MSTAT_RD_CMPLT | I2C_Master_I2C_MSTAT_ERR_XFER)) == 0u);                
            }
            else
            {
                /* translate from I2C_Master_MasterReadBuf() error output to
                *  I2CM_MasterStatus() error output */
                status = (uint8)I2C_Master_I2C_MSTAT_ERR_XFER;
            }
        }
    }
    
    return status;
}

/*----------------------------------------------------------------------------------------------------------------------

  Public Functions

 ---------------------------------------------------------------------------------------------------------------------*/

void I2c_Init()
{
    memset( &i2c_buf, 0, sizeof(i2c_buf));
    memset( &i2c_slave_data, 0, sizeof(i2c_slave_data));
    i2c_status = 0;
}

void I2c_Start()
{
    EZI2C_Slave_EzI2CSetAddress1(I2C_ADDRESS);
    EZI2C_Slave_EzI2CSetBuffer1(sizeof(i2c_buf), sizeof(i2c_buf.read_only), (volatile uint8 *) &i2c_buf);
    EZI2C_Slave_Start();
    
    I2C_Master_Start();    
}

void I2c_WriteCount(int32 count)
{
    i2c_buf.read_write.encoder_count = count;
}

int32 I2c_ReadCount()
{
    uint16 status;
    uint32 retries_remaining = 10;

    do
    {
        status = MasterReadSlave(OTHER_BOARD_ADDR, 0, sizeof(i2c_slave_data), (uint8 *) &i2c_slave_data);
    }
    while (status == I2C_Master_I2C_MSTAT_ERR_XFER && retries_remaining--);
    
    if (retries_remaining == 0)
    {
        i2c_slave_data.count = 0;
    }
    
    return i2c_slave_data.count;
}

uint16 I2c_ReadControl()
{
    uint16 value;
    
    value = i2c_buf.read_write.control;
    i2c_buf.read_write.control = 0;
    
    //value |= CONTROL_ENABLE_CALIBRATION_BIT;
    //value |= CONTROL_VALIDATE_CALIBRATION_BIT;
    
    return value;
}

void I2c_ReadVelocity(int16* velocity)
{
    *velocity = i2c_buf.read_write.cmd_velocity;
    *velocity = 400;
}

void I2c_ReadAcceleration(int16* accel)
{
    *accel = i2c_buf.read_write.cmd_acceleration;
}

void I2c_WriteCalReg(uint16 value)
{
    i2c_buf.read_write.calibration_port = value;
}

uint16 I2c_ReadCalReg()
{
    return i2c_buf.read_write.calibration_port;
}

void I2c_SetStatusBit(uint8 bit)
{
    i2c_status |= bit;
    i2c_buf.read_only.status = i2c_status;
}

void I2c_ClearStatusBit(uint8 bit)
{
    i2c_status &= ~bit;
    i2c_buf.read_only.status = i2c_status;
}

void I2c_WriteWheelVelocity(int16 velocity)
{
    i2c_buf.read_only.wheel_velocity = velocity;
}

void I2c_WriteCountPerSecond(int16 count_per_sec)
{
    i2c_buf.read_only.count_per_sec = count_per_sec;
}

void I2c_WriteOdom(float x_dist, float y_dist, float heading, float linear_speed, float angular_speed)
{
    i2c_buf.read_only.odom.x_dist = x_dist;
    i2c_buf.read_only.odom.y_dist = y_dist;
    i2c_buf.read_only.odom.heading = heading;
    i2c_buf.read_only.odom.linear_velocity = linear_speed;
    i2c_buf.read_only.odom.angular_velocity = angular_speed;
}

void I2c_WriteUltrasonicDistance(uint8 offset, uint16 distance)
{
    i2c_buf.read_only.us.values[offset] = distance;
}

void I2c_WriteInfraredDistance(uint8 offset, uint8 distance)
{
    i2c_buf.read_only.ir.values[offset] = distance;
}

void I2c_WriteTest()
{
    static uint32 last_time = 0;
    static uint8 test_count = 1;
    
    if (millis() - last_time > 1000)
    {
        last_time = millis();
        i2c_buf.read_only.test = test_count++;
    }
}

/* [] END OF FILE */
