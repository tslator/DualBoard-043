/*******************************************************************************
* File Name: HB25_PWM_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "HB25_PWM.h"

static HB25_PWM_BACKUP_STRUCT HB25_PWM_backup;


/*******************************************************************************
* Function Name: HB25_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void HB25_PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: HB25_PWM_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void HB25_PWM_Sleep(void)
{
    if(0u != (HB25_PWM_BLOCK_CONTROL_REG & HB25_PWM_MASK))
    {
        HB25_PWM_backup.enableState = 1u;
    }
    else
    {
        HB25_PWM_backup.enableState = 0u;
    }

    HB25_PWM_Stop();
    HB25_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: HB25_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void HB25_PWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: HB25_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void HB25_PWM_Wakeup(void)
{
    HB25_PWM_RestoreConfig();

    if(0u != HB25_PWM_backup.enableState)
    {
        HB25_PWM_Enable();
    }
}


/* [] END OF FILE */
