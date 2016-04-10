/*******************************************************************************
* File Name: EZI2C_Slave_PM.c
* Version 3.0
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

#include "EZI2C_Slave.h"
#include "EZI2C_Slave_PVT.h"

#if(EZI2C_Slave_SCB_MODE_I2C_INC)
    #include "EZI2C_Slave_I2C_PVT.h"
#endif /* (EZI2C_Slave_SCB_MODE_I2C_INC) */

#if(EZI2C_Slave_SCB_MODE_EZI2C_INC)
    #include "EZI2C_Slave_EZI2C_PVT.h"
#endif /* (EZI2C_Slave_SCB_MODE_EZI2C_INC) */

#if(EZI2C_Slave_SCB_MODE_SPI_INC || EZI2C_Slave_SCB_MODE_UART_INC)
    #include "EZI2C_Slave_SPI_UART_PVT.h"
#endif /* (EZI2C_Slave_SCB_MODE_SPI_INC || EZI2C_Slave_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG || \
   (EZI2C_Slave_SCB_MODE_I2C_CONST_CFG   && (!EZI2C_Slave_I2C_WAKE_ENABLE_CONST))   || \
   (EZI2C_Slave_SCB_MODE_EZI2C_CONST_CFG && (!EZI2C_Slave_EZI2C_WAKE_ENABLE_CONST)) || \
   (EZI2C_Slave_SCB_MODE_SPI_CONST_CFG   && (!EZI2C_Slave_SPI_WAKE_ENABLE_CONST))   || \
   (EZI2C_Slave_SCB_MODE_UART_CONST_CFG  && (!EZI2C_Slave_UART_WAKE_ENABLE_CONST)))

    EZI2C_Slave_BACKUP_STRUCT EZI2C_Slave_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: EZI2C_Slave_Sleep
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
void EZI2C_Slave_Sleep(void)
{
#if(EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG)

    if(EZI2C_Slave_SCB_WAKE_ENABLE_CHECK)
    {
        if(EZI2C_Slave_SCB_MODE_I2C_RUNTM_CFG)
        {
            EZI2C_Slave_I2CSaveConfig();
        }
        else if(EZI2C_Slave_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            EZI2C_Slave_EzI2CSaveConfig();
        }
    #if(!EZI2C_Slave_CY_SCBIP_V1)
        else if(EZI2C_Slave_SCB_MODE_SPI_RUNTM_CFG)
        {
            EZI2C_Slave_SpiSaveConfig();
        }
        else if(EZI2C_Slave_SCB_MODE_UART_RUNTM_CFG)
        {
            EZI2C_Slave_UartSaveConfig();
        }
    #endif /* (!EZI2C_Slave_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        EZI2C_Slave_backup.enableState = (uint8) EZI2C_Slave_GET_CTRL_ENABLED;

        if(0u != EZI2C_Slave_backup.enableState)
        {
            EZI2C_Slave_Stop();
        }
    }

#else

    #if (EZI2C_Slave_SCB_MODE_I2C_CONST_CFG && EZI2C_Slave_I2C_WAKE_ENABLE_CONST)
        EZI2C_Slave_I2CSaveConfig();

    #elif (EZI2C_Slave_SCB_MODE_EZI2C_CONST_CFG && EZI2C_Slave_EZI2C_WAKE_ENABLE_CONST)
        EZI2C_Slave_EzI2CSaveConfig();

    #elif (EZI2C_Slave_SCB_MODE_SPI_CONST_CFG && EZI2C_Slave_SPI_WAKE_ENABLE_CONST)
        EZI2C_Slave_SpiSaveConfig();

    #elif (EZI2C_Slave_SCB_MODE_UART_CONST_CFG && EZI2C_Slave_UART_WAKE_ENABLE_CONST)
        EZI2C_Slave_UartSaveConfig();

    #else

        EZI2C_Slave_backup.enableState = (uint8) EZI2C_Slave_GET_CTRL_ENABLED;

        if(0u != EZI2C_Slave_backup.enableState)
        {
            EZI2C_Slave_Stop();
        }

    #endif /* defined (EZI2C_Slave_SCB_MODE_I2C_CONST_CFG) && (EZI2C_Slave_I2C_WAKE_ENABLE_CONST) */

#endif /* (EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: EZI2C_Slave_Wakeup
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
void EZI2C_Slave_Wakeup(void)
{
#if(EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG)

    if(EZI2C_Slave_SCB_WAKE_ENABLE_CHECK)
    {
        if(EZI2C_Slave_SCB_MODE_I2C_RUNTM_CFG)
        {
            EZI2C_Slave_I2CRestoreConfig();
        }
        else if(EZI2C_Slave_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            EZI2C_Slave_EzI2CRestoreConfig();
        }
    #if(!EZI2C_Slave_CY_SCBIP_V1)
        else if(EZI2C_Slave_SCB_MODE_SPI_RUNTM_CFG)
        {
            EZI2C_Slave_SpiRestoreConfig();
        }
        else if(EZI2C_Slave_SCB_MODE_UART_RUNTM_CFG)
        {
            EZI2C_Slave_UartRestoreConfig();
        }
    #endif /* (!EZI2C_Slave_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != EZI2C_Slave_backup.enableState)
        {
            EZI2C_Slave_Enable();
        }
    }

#else

    #if (EZI2C_Slave_SCB_MODE_I2C_CONST_CFG  && EZI2C_Slave_I2C_WAKE_ENABLE_CONST)
        EZI2C_Slave_I2CRestoreConfig();

    #elif (EZI2C_Slave_SCB_MODE_EZI2C_CONST_CFG && EZI2C_Slave_EZI2C_WAKE_ENABLE_CONST)
        EZI2C_Slave_EzI2CRestoreConfig();

    #elif (EZI2C_Slave_SCB_MODE_SPI_CONST_CFG && EZI2C_Slave_SPI_WAKE_ENABLE_CONST)
        EZI2C_Slave_SpiRestoreConfig();

    #elif (EZI2C_Slave_SCB_MODE_UART_CONST_CFG && EZI2C_Slave_UART_WAKE_ENABLE_CONST)
        EZI2C_Slave_UartRestoreConfig();

    #else

        if(0u != EZI2C_Slave_backup.enableState)
        {
            EZI2C_Slave_Enable();
        }

    #endif /* (EZI2C_Slave_I2C_WAKE_ENABLE_CONST) */

#endif /* (EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
