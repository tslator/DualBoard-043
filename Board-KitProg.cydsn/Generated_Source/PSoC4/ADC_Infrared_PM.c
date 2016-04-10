/*******************************************************************************
* File Name: ADC_Infrared_PM.c
* Version 2.20
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_Infrared.h"


/***************************************
* Local data allocation
***************************************/

static ADC_Infrared_BACKUP_STRUCT  ADC_Infrared_backup =
{
    ADC_Infrared_DISABLED
};


/*******************************************************************************
* Function Name: ADC_Infrared_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_Infrared_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_Infrared_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_Infrared_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_Infrared_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_Infrared_backup - modified.
*
*******************************************************************************/
void ADC_Infrared_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    ADC_Infrared_SAR_DFT_CTRL_REG |= ADC_Infrared_ADFT_OVERRIDE;
    if((ADC_Infrared_SAR_CTRL_REG  & ADC_Infrared_ENABLE) != 0u)
    {
        if((ADC_Infrared_SAR_SAMPLE_CTRL_REG & ADC_Infrared_CONTINUOUS_EN) != 0u)
        {
            ADC_Infrared_backup.enableState = ADC_Infrared_ENABLED | ADC_Infrared_STARTED;
        }
        else
        {
            ADC_Infrared_backup.enableState = ADC_Infrared_ENABLED;
        }
        ADC_Infrared_StopConvert();
        ADC_Infrared_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((ADC_Infrared_SAR_CTRL_REG & ADC_Infrared_BOOSTPUMP_EN) != 0u)
        {
            ADC_Infrared_SAR_CTRL_REG &= (uint32)~ADC_Infrared_BOOSTPUMP_EN;
            ADC_Infrared_backup.enableState |= ADC_Infrared_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        ADC_Infrared_backup.enableState = ADC_Infrared_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_Infrared_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_Infrared_backup - used.
*
*******************************************************************************/
void ADC_Infrared_Wakeup(void)
{
    ADC_Infrared_SAR_DFT_CTRL_REG &= (uint32)~ADC_Infrared_ADFT_OVERRIDE;
    if(ADC_Infrared_backup.enableState != ADC_Infrared_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((ADC_Infrared_backup.enableState & ADC_Infrared_BOOSTPUMP_ENABLED) != 0u)
        {
            ADC_Infrared_SAR_CTRL_REG |= ADC_Infrared_BOOSTPUMP_EN;
        }
        ADC_Infrared_Enable();
        if((ADC_Infrared_backup.enableState & ADC_Infrared_STARTED) != 0u)
        {
            ADC_Infrared_StartConvert();
        }
    }
}
/* [] END OF FILE */
