/*******************************************************************************
* File Name: HB25_Enable_Pin.h  
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

#if !defined(CY_PINS_HB25_Enable_Pin_ALIASES_H) /* Pins HB25_Enable_Pin_ALIASES_H */
#define CY_PINS_HB25_Enable_Pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HB25_Enable_Pin_0			(HB25_Enable_Pin__0__PC)
#define HB25_Enable_Pin_0_PS		(HB25_Enable_Pin__0__PS)
#define HB25_Enable_Pin_0_PC		(HB25_Enable_Pin__0__PC)
#define HB25_Enable_Pin_0_DR		(HB25_Enable_Pin__0__DR)
#define HB25_Enable_Pin_0_SHIFT	(HB25_Enable_Pin__0__SHIFT)
#define HB25_Enable_Pin_0_INTR	((uint16)((uint16)0x0003u << (HB25_Enable_Pin__0__SHIFT*2u)))

#define HB25_Enable_Pin_INTR_ALL	 ((uint16)(HB25_Enable_Pin_0_INTR))


#endif /* End Pins HB25_Enable_Pin_ALIASES_H */


/* [] END OF FILE */
