/*******************************************************************************
* File Name: UARTCOMMS_PM.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UARTCOMMS.h"
#include "UARTCOMMS_PVT.h"

#if(UARTCOMMS_SCB_MODE_I2C_INC)
    #include "UARTCOMMS_I2C_PVT.h"
#endif /* (UARTCOMMS_SCB_MODE_I2C_INC) */

#if(UARTCOMMS_SCB_MODE_EZI2C_INC)
    #include "UARTCOMMS_EZI2C_PVT.h"
#endif /* (UARTCOMMS_SCB_MODE_EZI2C_INC) */

#if(UARTCOMMS_SCB_MODE_SPI_INC || UARTCOMMS_SCB_MODE_UART_INC)
    #include "UARTCOMMS_SPI_UART_PVT.h"
#endif /* (UARTCOMMS_SCB_MODE_SPI_INC || UARTCOMMS_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UARTCOMMS_SCB_MODE_I2C_CONST_CFG   && (!UARTCOMMS_I2C_WAKE_ENABLE_CONST))   || \
   (UARTCOMMS_SCB_MODE_EZI2C_CONST_CFG && (!UARTCOMMS_EZI2C_WAKE_ENABLE_CONST)) || \
   (UARTCOMMS_SCB_MODE_SPI_CONST_CFG   && (!UARTCOMMS_SPI_WAKE_ENABLE_CONST))   || \
   (UARTCOMMS_SCB_MODE_UART_CONST_CFG  && (!UARTCOMMS_UART_WAKE_ENABLE_CONST)))

    UARTCOMMS_BACKUP_STRUCT UARTCOMMS_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UARTCOMMS_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UARTCOMMS_Sleep(void)
{
#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UARTCOMMS_SCB_WAKE_ENABLE_CHECK)
    {
        if(UARTCOMMS_SCB_MODE_I2C_RUNTM_CFG)
        {
            UARTCOMMS_I2CSaveConfig();
        }
        else if(UARTCOMMS_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UARTCOMMS_EzI2CSaveConfig();
        }
    #if(!UARTCOMMS_CY_SCBIP_V1)
        else if(UARTCOMMS_SCB_MODE_SPI_RUNTM_CFG)
        {
            UARTCOMMS_SpiSaveConfig();
        }
        else if(UARTCOMMS_SCB_MODE_UART_RUNTM_CFG)
        {
            UARTCOMMS_UartSaveConfig();
        }
    #endif /* (!UARTCOMMS_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UARTCOMMS_backup.enableState = (uint8) UARTCOMMS_GET_CTRL_ENABLED;

        if(0u != UARTCOMMS_backup.enableState)
        {
            UARTCOMMS_Stop();
        }
    }

#else

    #if (UARTCOMMS_SCB_MODE_I2C_CONST_CFG && UARTCOMMS_I2C_WAKE_ENABLE_CONST)
        UARTCOMMS_I2CSaveConfig();

    #elif (UARTCOMMS_SCB_MODE_EZI2C_CONST_CFG && UARTCOMMS_EZI2C_WAKE_ENABLE_CONST)
        UARTCOMMS_EzI2CSaveConfig();

    #elif (UARTCOMMS_SCB_MODE_SPI_CONST_CFG && UARTCOMMS_SPI_WAKE_ENABLE_CONST)
        UARTCOMMS_SpiSaveConfig();

    #elif (UARTCOMMS_SCB_MODE_UART_CONST_CFG && UARTCOMMS_UART_WAKE_ENABLE_CONST)
        UARTCOMMS_UartSaveConfig();

    #else

        UARTCOMMS_backup.enableState = (uint8) UARTCOMMS_GET_CTRL_ENABLED;

        if(0u != UARTCOMMS_backup.enableState)
        {
            UARTCOMMS_Stop();
        }

    #endif /* defined (UARTCOMMS_SCB_MODE_I2C_CONST_CFG) && (UARTCOMMS_I2C_WAKE_ENABLE_CONST) */

#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UARTCOMMS_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UARTCOMMS_Wakeup(void)
{
#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UARTCOMMS_SCB_WAKE_ENABLE_CHECK)
    {
        if(UARTCOMMS_SCB_MODE_I2C_RUNTM_CFG)
        {
            UARTCOMMS_I2CRestoreConfig();
        }
        else if(UARTCOMMS_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UARTCOMMS_EzI2CRestoreConfig();
        }
    #if(!UARTCOMMS_CY_SCBIP_V1)
        else if(UARTCOMMS_SCB_MODE_SPI_RUNTM_CFG)
        {
            UARTCOMMS_SpiRestoreConfig();
        }
        else if(UARTCOMMS_SCB_MODE_UART_RUNTM_CFG)
        {
            UARTCOMMS_UartRestoreConfig();
        }
    #endif /* (!UARTCOMMS_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UARTCOMMS_backup.enableState)
        {
            UARTCOMMS_Enable();
        }
    }

#else

    #if (UARTCOMMS_SCB_MODE_I2C_CONST_CFG  && UARTCOMMS_I2C_WAKE_ENABLE_CONST)
        UARTCOMMS_I2CRestoreConfig();

    #elif (UARTCOMMS_SCB_MODE_EZI2C_CONST_CFG && UARTCOMMS_EZI2C_WAKE_ENABLE_CONST)
        UARTCOMMS_EzI2CRestoreConfig();

    #elif (UARTCOMMS_SCB_MODE_SPI_CONST_CFG && UARTCOMMS_SPI_WAKE_ENABLE_CONST)
        UARTCOMMS_SpiRestoreConfig();

    #elif (UARTCOMMS_SCB_MODE_UART_CONST_CFG && UARTCOMMS_UART_WAKE_ENABLE_CONST)
        UARTCOMMS_UartRestoreConfig();

    #else

        if(0u != UARTCOMMS_backup.enableState)
        {
            UARTCOMMS_Enable();
        }

    #endif /* (UARTCOMMS_I2C_WAKE_ENABLE_CONST) */

#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
