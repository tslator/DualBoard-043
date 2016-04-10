/*******************************************************************************
* File Name: I2CIF_I2C_SLAVE.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C Slave mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2CIF_I2C_PVT.h"

#if(I2CIF_I2C_SLAVE_CONST)

/***************************************
*      I2C Slave Private Vars
***************************************/

volatile uint8 I2CIF_slStatus;          /* Slave Status */

/* Receive buffer variables */
volatile uint8 * I2CIF_slWrBufPtr;      /* Pointer to Receive buffer  */
volatile uint32  I2CIF_slWrBufSize;     /* Slave Receive buffer size  */
volatile uint32  I2CIF_slWrBufIndex;    /* Slave Receive buffer Index */

/* Transmit buffer variables */
volatile uint8 * I2CIF_slRdBufPtr;      /* Pointer to Transmit buffer  */
volatile uint32  I2CIF_slRdBufSize;     /* Slave Transmit buffer size  */
volatile uint32  I2CIF_slRdBufIndex;    /* Slave Transmit buffer Index */
volatile uint32  I2CIF_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
volatile uint8   I2CIF_slOverFlowCount; /* Slave Transmit Overflow counter */

#if (I2CIF_I2C_CUSTOM_ADDRESS_HANDLER_CONST)

    uint32 (*I2CIF_customAddressHandler)(void) = NULL;


    /*******************************************************************************
    * Function Name: I2CIF_SetI2cAddressCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the I2C slave interrupt handler during
    *  the I2C interrupt address processing. This function should be used when
    *  multiple I2C addresses need to be decoded or general call address supported.
    *  The registered function must return decision whether to ACK or NACK address.
    *  Only one I2C address handler is supported, which is the function provided
    *  by the most recent call.
    *  At initialization time no I2C address handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CIF_SetI2cAddressCustomInterruptHandler(uint32 (*func) (void))
    {
        /* Register custom address handler */
        I2CIF_customAddressHandler = func;
    }
#endif /* (I2CIF_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveStatus
********************************************************************************
*
* Summary:
*  Returns the I2C slave's communication status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C slave.
*
* Global variables:
*  I2CIF_slStatus - used to store current status of I2C slave.
*
*******************************************************************************/
uint32 I2CIF_I2CSlaveStatus(void)
{
    return((uint32) I2CIF_slStatus);
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveClearReadStatus
********************************************************************************
*
* Summary:
*  Clears the read status flags and returns their values. No other status flags
*  are affected.
*
* Parameters:
*  None
*
* Return:
*  Current read status of I2C slave.
*
* Global variables:
*  I2CIF_slStatus  - used to store current status of I2C slave.
*
*******************************************************************************/
uint32 I2CIF_I2CSlaveClearReadStatus(void)
{
    uint32 status;

    I2CIF_DisableInt();  /* Lock from interruption */

    /* Mask of transfer complete flag and error status */
    status = ((uint32) I2CIF_slStatus & I2CIF_I2C_SSTAT_RD_MASK);
    I2CIF_slStatus &= (uint8) ~I2CIF_I2C_SSTAT_RD_CLEAR;

    I2CIF_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveClearWriteStatus
********************************************************************************
*
* Summary:
*  Clears the write status flags and returns their values. No other status flags
*  are affected.
*
* Parameters:
*  None
*
* Return:
*  Current write status of I2C slave.
*
* Global variables:
*  I2CIF_slStatus  - used to store current status of I2C slave.
*
*******************************************************************************/
uint32 I2CIF_I2CSlaveClearWriteStatus(void)
{
    uint32 status;

    I2CIF_DisableInt();  /* Lock from interruption */

    /* Mask of transfer complete flag and Error status */
    status = ((uint32) I2CIF_slStatus & I2CIF_I2C_SSTAT_WR_MASK);
    I2CIF_slStatus &= (uint8) ~I2CIF_I2C_SSTAT_WR_CLEAR;

    I2CIF_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveSetAddress
********************************************************************************
*
* Summary:
*  Sets the I2C slave address.
*
* Parameters:
*  address: I2C slave address for the primary device. This value may be any
*  address between 0 and 127.
*
* Return:
*  None
*
*******************************************************************************/
void I2CIF_I2CSlaveSetAddress(uint32 address)
{
    uint32 matchReg;

    matchReg = I2CIF_RX_MATCH_REG;

    matchReg &= ((uint32) ~I2CIF_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  I2CIF_GET_I2C_8BIT_ADDRESS(address));

    I2CIF_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveSetAddressMask
********************************************************************************
*
* Summary:
*  Sets the I2C slave address mask.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void I2CIF_I2CSlaveSetAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = I2CIF_RX_MATCH_REG;

    matchReg &= ((uint32) ~I2CIF_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << I2CIF_RX_MATCH_MASK_POS));

    I2CIF_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveInitReadBuf
********************************************************************************
*
* Summary:
*  Sets the buffer pointer and size of the read buffer. This function also
*  resets the transfer count returned with the I2C_SlaveGetReadBufSize function.
*
* Parameters:
*  readBuf:  Pointer to the data buffer to be read by the master.
*  bufSize:  Size of the read buffer exposed to the I2C master.
*
* Return:
*  None
*
* Global variables:
*  I2CIF_slRdBufPtr   - used to store pointer to slave read buffer.
*  I2CIF_slRdBufSize  - used to store salve read buffer size.
*  I2CIF_slRdBufIndex - used to store current index within slave
*  read buffer.
*
* Side Effects:
*  If this function is called during a bus transaction, data from the previous
*  buffer location and the beginning of current buffer may be transmitted.
*
*******************************************************************************/
void I2CIF_I2CSlaveInitReadBuf(uint8 * rdBuf, uint32 bufSize)
{
    /* Check for proper buffer */
    if(NULL != rdBuf)
    {
        I2CIF_DisableInt();  /* Lock from interruption */

        I2CIF_slRdBufPtr      = (volatile uint8 *) rdBuf; /* Set buffer pointer  */
        I2CIF_slRdBufSize     = bufSize;                  /* Set buffer size     */
        I2CIF_slRdBufIndex    = 0u;                       /* Clear buffer index  */
        I2CIF_slRdBufIndexTmp = 0u;                       /* Clear buffer index  */

        I2CIF_EnableInt();   /* Release lock */
    }
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveInitWriteBuf
********************************************************************************
*
* Summary:
*  Sets the buffer pointer and size of the read buffer. This function also
*  resets the transfer count returned with the I2C_SlaveGetReadBufSize function.
*
* Parameters:
*  writeBuf:  Pointer to the data buffer to be read by the master.
*  bufSize:  Size of the buffer exposed to the I2C master.
*
* Return:
*  None
*
* Global variables:
*  I2CIF_slWrBufPtr   - used to store pointer to slave write buffer.
*  I2CIF_slWrBufSize  - used to store salve write buffer size.
*  I2CIF_slWrBufIndex - used to store current index within slave
*  write buffer.
*
* Side Effects:
*  If this function is called during a bus transaction, data from the previous
*  buffer location and the beginning of current buffer may be transmitted.
*
*******************************************************************************/
void I2CIF_I2CSlaveInitWriteBuf(uint8 * wrBuf, uint32 bufSize)
{
    /* Check buffer pointer */
    if(NULL != wrBuf)
    {
        I2CIF_DisableInt();  /* Lock from interruption */

        I2CIF_slWrBufPtr   = (volatile uint8 *) wrBuf; /* Set buffer pointer  */
        I2CIF_slWrBufSize  = bufSize;                  /* Set buffer size     */
        I2CIF_slWrBufIndex = 0u;                       /* Clear buffer index  */

        I2CIF_EnableInt();   /* Release lock */
    }
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveGetReadBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes read by the I2C master since an
*  I2C_SlaveInitReadBuf or I2C_SlaveClearReadBuf function was executed.
*  The maximum return value will be the size of the read buffer.
*
* Parameters:
*  None
*
* Return:
*  Bytes read by master.
*
* Global variables:
*  I2CIF_slRdBufIndex - used to store current index within slave
*  read buffer.
*
*******************************************************************************/
uint32 I2CIF_I2CSlaveGetReadBufSize(void)
{
    return(I2CIF_slRdBufIndex);
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveGetWriteBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes written by the I2C master since an
*  I2C_SlaveInitWriteBuf or I2C_SlaveClearWriteBuf function was executed.
*  The maximum return value will be the size of the write buffer.
*
* Parameters:
*  None
*
* Return:
*  Bytes written by master.
*
* Global variables:
*  I2CIF_slWrBufIndex - used to store current index within slave
*  write buffer.
*
*******************************************************************************/
uint32 I2CIF_I2CSlaveGetWriteBufSize(void)
{
    return(I2CIF_slWrBufIndex);
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveClearReadBuf
********************************************************************************
*
* Summary:
*  Resets the read pointer to the first byte in the read buffer. The next byte
*  read by the master will be the first byte in the read buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  I2CIF_slRdBufIndex - used to store current index within slave
*  read buffer.
*
*******************************************************************************/
void I2CIF_I2CSlaveClearReadBuf(void)
{
    I2CIF_slRdBufIndex = 0u;
}


/*******************************************************************************
* Function Name: I2CIF_I2CSlaveClearWriteBuf
********************************************************************************
*
* Summary:
*  Resets the write pointer to the first byte in the write buffer. The next byte
*  written by the master will be the first byte in the write buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  I2CIF_slWrBufIndex - used to store current index within slave
*  write buffer.
*
*******************************************************************************/
void I2CIF_I2CSlaveClearWriteBuf(void)
{
    I2CIF_slWrBufIndex = 0u;
}

#endif /* (I2CIF_I2C_SLAVE_CONST) */


/* [] END OF FILE */
