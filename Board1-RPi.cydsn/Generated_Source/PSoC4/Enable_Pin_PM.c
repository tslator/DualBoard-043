/*******************************************************************************
* File Name: Enable_Pin.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Enable_Pin.h"

static Enable_Pin_BACKUP_STRUCT  Enable_Pin_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Enable_Pin_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Enable_Pin_SUT.c usage_Enable_Pin_Sleep_Wakeup
*******************************************************************************/
void Enable_Pin_Sleep(void)
{
    #if defined(Enable_Pin__PC)
        Enable_Pin_backup.pcState = Enable_Pin_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Enable_Pin_backup.usbState = Enable_Pin_CR1_REG;
            Enable_Pin_USB_POWER_REG |= Enable_Pin_USBIO_ENTER_SLEEP;
            Enable_Pin_CR1_REG &= Enable_Pin_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Enable_Pin__SIO)
        Enable_Pin_backup.sioState = Enable_Pin_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Enable_Pin_SIO_REG &= (uint32)(~Enable_Pin_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Enable_Pin_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Enable_Pin_Sleep() for an example usage.
*******************************************************************************/
void Enable_Pin_Wakeup(void)
{
    #if defined(Enable_Pin__PC)
        Enable_Pin_PC = Enable_Pin_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Enable_Pin_USB_POWER_REG &= Enable_Pin_USBIO_EXIT_SLEEP_PH1;
            Enable_Pin_CR1_REG = Enable_Pin_backup.usbState;
            Enable_Pin_USB_POWER_REG &= Enable_Pin_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Enable_Pin__SIO)
        Enable_Pin_SIO_REG = Enable_Pin_backup.sioState;
    #endif
}


/* [] END OF FILE */
