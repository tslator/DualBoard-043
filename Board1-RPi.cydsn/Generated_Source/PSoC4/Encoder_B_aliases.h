/*******************************************************************************
* File Name: Encoder_B.h  
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

#if !defined(CY_PINS_Encoder_B_ALIASES_H) /* Pins Encoder_B_ALIASES_H */
#define CY_PINS_Encoder_B_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Encoder_B_0			(Encoder_B__0__PC)
#define Encoder_B_0_PS		(Encoder_B__0__PS)
#define Encoder_B_0_PC		(Encoder_B__0__PC)
#define Encoder_B_0_DR		(Encoder_B__0__DR)
#define Encoder_B_0_SHIFT	(Encoder_B__0__SHIFT)
#define Encoder_B_0_INTR	((uint16)((uint16)0x0003u << (Encoder_B__0__SHIFT*2u)))

#define Encoder_B_INTR_ALL	 ((uint16)(Encoder_B_0_INTR))


#endif /* End Pins Encoder_B_ALIASES_H */


/* [] END OF FILE */
