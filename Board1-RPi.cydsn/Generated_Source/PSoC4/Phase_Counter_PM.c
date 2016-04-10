/*******************************************************************************
* File Name: Phase_Counter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Phase_Counter.h"

static Phase_Counter_backupStruct Phase_Counter_backup;


/*******************************************************************************
* Function Name: Phase_Counter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Phase_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Phase_Counter_SaveConfig(void) 
{
    #if (!Phase_Counter_UsingFixedFunction)

        Phase_Counter_backup.CounterUdb = Phase_Counter_ReadCounter();

        #if(!Phase_Counter_ControlRegRemoved)
            Phase_Counter_backup.CounterControlRegister = Phase_Counter_ReadControlRegister();
        #endif /* (!Phase_Counter_ControlRegRemoved) */

    #endif /* (!Phase_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Phase_Counter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Phase_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Phase_Counter_RestoreConfig(void) 
{      
    #if (!Phase_Counter_UsingFixedFunction)

       Phase_Counter_WriteCounter(Phase_Counter_backup.CounterUdb);

        #if(!Phase_Counter_ControlRegRemoved)
            Phase_Counter_WriteControlRegister(Phase_Counter_backup.CounterControlRegister);
        #endif /* (!Phase_Counter_ControlRegRemoved) */

    #endif /* (!Phase_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Phase_Counter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Phase_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Phase_Counter_Sleep(void) 
{
    #if(!Phase_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Phase_Counter_CTRL_ENABLE == (Phase_Counter_CONTROL & Phase_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Phase_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Phase_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Phase_Counter_backup.CounterEnableState = 1u;
        if(Phase_Counter_backup.CounterEnableState != 0u)
        {
            Phase_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Phase_Counter_ControlRegRemoved) */
    
    Phase_Counter_Stop();
    Phase_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Phase_Counter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Phase_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Phase_Counter_Wakeup(void) 
{
    Phase_Counter_RestoreConfig();
    #if(!Phase_Counter_ControlRegRemoved)
        if(Phase_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Phase_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Phase_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
