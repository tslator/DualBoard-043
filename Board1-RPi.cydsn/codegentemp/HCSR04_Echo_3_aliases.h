/*******************************************************************************
* File Name: HCSR04_Echo_3.h  
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

#if !defined(CY_PINS_HCSR04_Echo_3_ALIASES_H) /* Pins HCSR04_Echo_3_ALIASES_H */
#define CY_PINS_HCSR04_Echo_3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HCSR04_Echo_3_0			(HCSR04_Echo_3__0__PC)
#define HCSR04_Echo_3_0_PS		(HCSR04_Echo_3__0__PS)
#define HCSR04_Echo_3_0_PC		(HCSR04_Echo_3__0__PC)
#define HCSR04_Echo_3_0_DR		(HCSR04_Echo_3__0__DR)
#define HCSR04_Echo_3_0_SHIFT	(HCSR04_Echo_3__0__SHIFT)
#define HCSR04_Echo_3_0_INTR	((uint16)((uint16)0x0003u << (HCSR04_Echo_3__0__SHIFT*2u)))

#define HCSR04_Echo_3_INTR_ALL	 ((uint16)(HCSR04_Echo_3_0_INTR))


#endif /* End Pins HCSR04_Echo_3_ALIASES_H */


/* [] END OF FILE */
