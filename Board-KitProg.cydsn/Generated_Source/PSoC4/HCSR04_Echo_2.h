/*******************************************************************************
* File Name: HCSR04_Echo_2.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_HCSR04_Echo_2_H) /* Pins HCSR04_Echo_2_H */
#define CY_PINS_HCSR04_Echo_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HCSR04_Echo_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    HCSR04_Echo_2_Write(uint8 value) ;
void    HCSR04_Echo_2_SetDriveMode(uint8 mode) ;
uint8   HCSR04_Echo_2_ReadDataReg(void) ;
uint8   HCSR04_Echo_2_Read(void) ;
uint8   HCSR04_Echo_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HCSR04_Echo_2_DRIVE_MODE_BITS        (3)
#define HCSR04_Echo_2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HCSR04_Echo_2_DRIVE_MODE_BITS))

#define HCSR04_Echo_2_DM_ALG_HIZ         (0x00u)
#define HCSR04_Echo_2_DM_DIG_HIZ         (0x01u)
#define HCSR04_Echo_2_DM_RES_UP          (0x02u)
#define HCSR04_Echo_2_DM_RES_DWN         (0x03u)
#define HCSR04_Echo_2_DM_OD_LO           (0x04u)
#define HCSR04_Echo_2_DM_OD_HI           (0x05u)
#define HCSR04_Echo_2_DM_STRONG          (0x06u)
#define HCSR04_Echo_2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define HCSR04_Echo_2_MASK               HCSR04_Echo_2__MASK
#define HCSR04_Echo_2_SHIFT              HCSR04_Echo_2__SHIFT
#define HCSR04_Echo_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HCSR04_Echo_2_PS                     (* (reg32 *) HCSR04_Echo_2__PS)
/* Port Configuration */
#define HCSR04_Echo_2_PC                     (* (reg32 *) HCSR04_Echo_2__PC)
/* Data Register */
#define HCSR04_Echo_2_DR                     (* (reg32 *) HCSR04_Echo_2__DR)
/* Input Buffer Disable Override */
#define HCSR04_Echo_2_INP_DIS                (* (reg32 *) HCSR04_Echo_2__PC2)


#if defined(HCSR04_Echo_2__INTSTAT)  /* Interrupt Registers */

    #define HCSR04_Echo_2_INTSTAT                (* (reg32 *) HCSR04_Echo_2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define HCSR04_Echo_2_DRIVE_MODE_SHIFT       (0x00u)
#define HCSR04_Echo_2_DRIVE_MODE_MASK        (0x07u << HCSR04_Echo_2_DRIVE_MODE_SHIFT)


#endif /* End Pins HCSR04_Echo_2_H */


/* [] END OF FILE */
