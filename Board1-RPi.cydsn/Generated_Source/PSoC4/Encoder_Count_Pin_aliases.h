/*******************************************************************************
* File Name: Encoder_Count_Pin.h  
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

#if !defined(CY_PINS_Encoder_Count_Pin_ALIASES_H) /* Pins Encoder_Count_Pin_ALIASES_H */
#define CY_PINS_Encoder_Count_Pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Encoder_Count_Pin_0			(Encoder_Count_Pin__0__PC)
#define Encoder_Count_Pin_0_PS		(Encoder_Count_Pin__0__PS)
#define Encoder_Count_Pin_0_PC		(Encoder_Count_Pin__0__PC)
#define Encoder_Count_Pin_0_DR		(Encoder_Count_Pin__0__DR)
#define Encoder_Count_Pin_0_SHIFT	(Encoder_Count_Pin__0__SHIFT)
#define Encoder_Count_Pin_0_INTR	((uint16)((uint16)0x0003u << (Encoder_Count_Pin__0__SHIFT*2u)))

#define Encoder_Count_Pin_INTR_ALL	 ((uint16)(Encoder_Count_Pin_0_INTR))


#endif /* End Pins Encoder_Count_Pin_ALIASES_H */


/* [] END OF FILE */
