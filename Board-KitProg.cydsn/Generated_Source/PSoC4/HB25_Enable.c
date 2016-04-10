/*******************************************************************************
* File Name: HB25_Enable.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "HB25_Enable.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        HB25_Enable_PC =   (HB25_Enable_PC & \
                                (uint32)(~(uint32)(HB25_Enable_DRIVE_MODE_IND_MASK << (HB25_Enable_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (HB25_Enable_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: HB25_Enable_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void HB25_Enable_Write(uint8 value) 
{
    uint8 drVal = (uint8)(HB25_Enable_DR & (uint8)(~HB25_Enable_MASK));
    drVal = (drVal | ((uint8)(value << HB25_Enable_SHIFT) & HB25_Enable_MASK));
    HB25_Enable_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: HB25_Enable_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  HB25_Enable_DM_STRONG     Strong Drive 
*  HB25_Enable_DM_OD_HI      Open Drain, Drives High 
*  HB25_Enable_DM_OD_LO      Open Drain, Drives Low 
*  HB25_Enable_DM_RES_UP     Resistive Pull Up 
*  HB25_Enable_DM_RES_DWN    Resistive Pull Down 
*  HB25_Enable_DM_RES_UPDWN  Resistive Pull Up/Down 
*  HB25_Enable_DM_DIG_HIZ    High Impedance Digital 
*  HB25_Enable_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void HB25_Enable_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(HB25_Enable__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: HB25_Enable_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro HB25_Enable_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 HB25_Enable_Read(void) 
{
    return (uint8)((HB25_Enable_PS & HB25_Enable_MASK) >> HB25_Enable_SHIFT);
}


/*******************************************************************************
* Function Name: HB25_Enable_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 HB25_Enable_ReadDataReg(void) 
{
    return (uint8)((HB25_Enable_DR & HB25_Enable_MASK) >> HB25_Enable_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(HB25_Enable_INTSTAT) 

    /*******************************************************************************
    * Function Name: HB25_Enable_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 HB25_Enable_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(HB25_Enable_INTSTAT & HB25_Enable_MASK);
		HB25_Enable_INTSTAT = maskedStatus;
        return maskedStatus >> HB25_Enable_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
