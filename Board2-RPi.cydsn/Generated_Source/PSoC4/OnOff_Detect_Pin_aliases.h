/*******************************************************************************
* File Name: OnOff_Detect_Pin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_OnOff_Detect_Pin_ALIASES_H) /* Pins OnOff_Detect_Pin_ALIASES_H */
#define CY_PINS_OnOff_Detect_Pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define OnOff_Detect_Pin_0			(OnOff_Detect_Pin__0__PC)
#define OnOff_Detect_Pin_0_PS		(OnOff_Detect_Pin__0__PS)
#define OnOff_Detect_Pin_0_PC		(OnOff_Detect_Pin__0__PC)
#define OnOff_Detect_Pin_0_DR		(OnOff_Detect_Pin__0__DR)
#define OnOff_Detect_Pin_0_SHIFT	(OnOff_Detect_Pin__0__SHIFT)
#define OnOff_Detect_Pin_0_INTR	((uint16)((uint16)0x0003u << (OnOff_Detect_Pin__0__SHIFT*2u)))

#define OnOff_Detect_Pin_INTR_ALL	 ((uint16)(OnOff_Detect_Pin_0_INTR))


#endif /* End Pins OnOff_Detect_Pin_ALIASES_H */


/* [] END OF FILE */
