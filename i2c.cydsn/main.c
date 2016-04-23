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
#include <project.h>

static uint32 counter;
static uint32 *buffer;

#define EZI2C_SLAVE_ADDR (0x08)

static uint8 MasterWriteSlave(uint8 addr, uint8 *buf, uint8 len)
{
    uint8 volatile status;
    
    status = I2CM_I2CMasterClearStatus();
    if(!(status & I2CM_I2C_MSTAT_ERR_XFER))
    {
        status = I2CM_I2CMasterWriteBuf(addr, buf, len,
                                        I2CM_I2C_MODE_COMPLETE_XFER);
        if(status == I2CM_I2C_MSTR_NO_ERROR)
        {
            /* wait for write complete and no error */
            do
            {
                status = I2CM_I2CMasterStatus();
            } while((status & (I2CM_I2C_MSTAT_WR_CMPLT | I2CM_I2C_MSTAT_ERR_XFER)) == 0u);
        }
        else
        {
            /* translate from I2CM_I2CMasterWriteBuf() error output to
            *  I2CM_I2CMasterStatus() error output */
            status = (uint8)I2CM_I2C_MSTAT_ERR_XFER;
        }
    }
    
    return status;
}

static uint8 MasterReadSlave()
{
    uint8 volatile status; /* copy of EZI2C activity status */\
    uint8 offset = 0;
    uint32 value = 0;
    
    status = MasterWriteSlave(EZI2C_SLAVE_ADDR, &offset, 1);
    if(!(status & I2CM_I2C_MSTAT_ERR_XFER))
    {
        status = I2CM_I2CMasterClearStatus();
        if(!(status & I2CM_I2C_MSTAT_ERR_XFER))
        {
            status = I2CM_I2CMasterReadBuf(EZI2C_SLAVE_ADDR,
                                           (uint8 *) &value,
                                           4, 
                                           I2CM_I2C_MODE_COMPLETE_XFER);
            if(status == I2CM_I2C_MSTR_NO_ERROR)
            {
                /* wait for read complete and no error */
                do
                {
                    status = I2CM_I2CMasterStatus();
                } while((status & (I2CM_I2C_MSTAT_RD_CMPLT | I2CM_I2C_MSTAT_ERR_XFER)) == 0u);
                
                return value;
            }
            else
            {
                /* translate from I2CM_MasterReadBuf() error output to
                *  I2CM_MasterStatus() error output */
                status = (uint8)I2CM_I2C_MSTAT_ERR_XFER;
            }
        }
    }
    
    return 0xff;
}

int main()
{
    uint8 result;
    CyGlobalIntEnable; /* Enable global interrupts. */

    counter = 0;
    buffer = &counter;
    EZI2C_EzI2CSetBuffer1(4, 4, (uint8 *) buffer);
    EZI2C_Start();
    
    I2CM_Start();

    for(;;)
    {
        counter++;
        CyDelay(100);
        result = MasterReadSlave();
    }
}

/* [] END OF FILE */
