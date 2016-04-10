/*******************************************************************************
* File Name: Encoder_Pins.c  
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
#include "Encoder_Pins.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Encoder_Pins_PC =   (Encoder_Pins_PC & \
                                (uint32)(~(uint32)(Encoder_Pins_DRIVE_MODE_IND_MASK << (Encoder_Pins_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Encoder_Pins_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Encoder_Pins_Write
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
void Encoder_Pins_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Encoder_Pins_DR & (uint8)(~Encoder_Pins_MASK));
    drVal = (drVal | ((uint8)(value << Encoder_Pins_SHIFT) & Encoder_Pins_MASK));
    Encoder_Pins_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Encoder_Pins_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Encoder_Pins_DM_STRONG     Strong Drive 
*  Encoder_Pins_DM_OD_HI      Open Drain, Drives High 
*  Encoder_Pins_DM_OD_LO      Open Drain, Drives Low 
*  Encoder_Pins_DM_RES_UP     Resistive Pull Up 
*  Encoder_Pins_DM_RES_DWN    Resistive Pull Down 
*  Encoder_Pins_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Encoder_Pins_DM_DIG_HIZ    High Impedance Digital 
*  Encoder_Pins_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Encoder_Pins_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Encoder_Pins__0__SHIFT, mode);
	SetP4PinDriveMode(Encoder_Pins__1__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Encoder_Pins_Read
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
*  Macro Encoder_Pins_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Encoder_Pins_Read(void) 
{
    return (uint8)((Encoder_Pins_PS & Encoder_Pins_MASK) >> Encoder_Pins_SHIFT);
}


/*******************************************************************************
* Function Name: Encoder_Pins_ReadDataReg
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
uint8 Encoder_Pins_ReadDataReg(void) 
{
    return (uint8)((Encoder_Pins_DR & Encoder_Pins_MASK) >> Encoder_Pins_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Encoder_Pins_INTSTAT) 

    /*******************************************************************************
    * Function Name: Encoder_Pins_ClearInterrupt
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
    uint8 Encoder_Pins_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Encoder_Pins_INTSTAT & Encoder_Pins_MASK);
		Encoder_Pins_INTSTAT = maskedStatus;
        return maskedStatus >> Encoder_Pins_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
