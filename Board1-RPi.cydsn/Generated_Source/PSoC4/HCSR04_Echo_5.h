/*******************************************************************************
* File Name: HCSR04_Echo_5.h  
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

#if !defined(CY_PINS_HCSR04_Echo_5_H) /* Pins HCSR04_Echo_5_H */
#define CY_PINS_HCSR04_Echo_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HCSR04_Echo_5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    HCSR04_Echo_5_Write(uint8 value) ;
void    HCSR04_Echo_5_SetDriveMode(uint8 mode) ;
uint8   HCSR04_Echo_5_ReadDataReg(void) ;
uint8   HCSR04_Echo_5_Read(void) ;
uint8   HCSR04_Echo_5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HCSR04_Echo_5_DRIVE_MODE_BITS        (3)
#define HCSR04_Echo_5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HCSR04_Echo_5_DRIVE_MODE_BITS))

#define HCSR04_Echo_5_DM_ALG_HIZ         (0x00u)
#define HCSR04_Echo_5_DM_DIG_HIZ         (0x01u)
#define HCSR04_Echo_5_DM_RES_UP          (0x02u)
#define HCSR04_Echo_5_DM_RES_DWN         (0x03u)
#define HCSR04_Echo_5_DM_OD_LO           (0x04u)
#define HCSR04_Echo_5_DM_OD_HI           (0x05u)
#define HCSR04_Echo_5_DM_STRONG          (0x06u)
#define HCSR04_Echo_5_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define HCSR04_Echo_5_MASK               HCSR04_Echo_5__MASK
#define HCSR04_Echo_5_SHIFT              HCSR04_Echo_5__SHIFT
#define HCSR04_Echo_5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HCSR04_Echo_5_PS                     (* (reg32 *) HCSR04_Echo_5__PS)
/* Port Configuration */
#define HCSR04_Echo_5_PC                     (* (reg32 *) HCSR04_Echo_5__PC)
/* Data Register */
#define HCSR04_Echo_5_DR                     (* (reg32 *) HCSR04_Echo_5__DR)
/* Input Buffer Disable Override */
#define HCSR04_Echo_5_INP_DIS                (* (reg32 *) HCSR04_Echo_5__PC2)


#if defined(HCSR04_Echo_5__INTSTAT)  /* Interrupt Registers */

    #define HCSR04_Echo_5_INTSTAT                (* (reg32 *) HCSR04_Echo_5__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define HCSR04_Echo_5_DRIVE_MODE_SHIFT       (0x00u)
#define HCSR04_Echo_5_DRIVE_MODE_MASK        (0x07u << HCSR04_Echo_5_DRIVE_MODE_SHIFT)


#endif /* End Pins HCSR04_Echo_5_H */


/* [] END OF FILE */
