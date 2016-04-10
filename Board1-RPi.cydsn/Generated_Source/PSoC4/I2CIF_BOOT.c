/*******************************************************************************
* File Name: I2CIF_BOOT.c
* Version 3.10
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2CIF_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_BTLDR_COMM_ENABLED) && \
                                (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: I2CIF_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CIF_CyBtldrCommStart(void)
{
    if (I2CIF_SCB_MODE_I2C_RUNTM_CFG)
    {
        I2CIF_I2CCyBtldrCommStart();
    }
    else if (I2CIF_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        I2CIF_EzI2CCyBtldrCommStart();
    }
#if (!I2CIF_CY_SCBIP_V1)
    else if (I2CIF_SCB_MODE_SPI_RUNTM_CFG)
    {
        I2CIF_SpiCyBtldrCommStart();
    }
    else if (I2CIF_SCB_MODE_UART_RUNTM_CFG)
    {
        I2CIF_UartCyBtldrCommStart();
    }
#endif /* (!I2CIF_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: I2CIF_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CIF_CyBtldrCommStop(void)
{
    if (I2CIF_SCB_MODE_I2C_RUNTM_CFG)
    {
        I2CIF_I2CCyBtldrCommStop();
    }
    else if (I2CIF_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        I2CIF_EzI2CCyBtldrCommStop();
    }
#if (!I2CIF_CY_SCBIP_V1)
    else if (I2CIF_SCB_MODE_SPI_RUNTM_CFG)
    {
        I2CIF_SpiCyBtldrCommStop();
    }
    else if (I2CIF_SCB_MODE_UART_RUNTM_CFG)
    {
        I2CIF_UartCyBtldrCommStop();
    }
#endif /* (!I2CIF_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: I2CIF_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CIF_CyBtldrCommReset(void)
{
    if(I2CIF_SCB_MODE_I2C_RUNTM_CFG)
    {
        I2CIF_I2CCyBtldrCommReset();
    }
    else if(I2CIF_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        I2CIF_EzI2CCyBtldrCommReset();
    }
#if (!I2CIF_CY_SCBIP_V1)
    else if(I2CIF_SCB_MODE_SPI_RUNTM_CFG)
    {
        I2CIF_SpiCyBtldrCommReset();
    }
    else if(I2CIF_SCB_MODE_UART_RUNTM_CFG)
    {
        I2CIF_UartCyBtldrCommReset();
    }
#endif /* (!I2CIF_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: I2CIF_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus I2CIF_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(I2CIF_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = I2CIF_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(I2CIF_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = I2CIF_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!I2CIF_CY_SCBIP_V1)
    else if(I2CIF_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = I2CIF_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(I2CIF_SCB_MODE_UART_RUNTM_CFG)
    {
        status = I2CIF_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!I2CIF_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: I2CIF_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus I2CIF_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(I2CIF_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = I2CIF_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(I2CIF_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = I2CIF_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!I2CIF_CY_SCBIP_V1)
    else if(I2CIF_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = I2CIF_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(I2CIF_SCB_MODE_UART_RUNTM_CFG)
    {
        status = I2CIF_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!I2CIF_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
