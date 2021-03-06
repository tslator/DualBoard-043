/*******************************************************************************
* File Name: Encoder_Pins.h  
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

#if !defined(CY_PINS_Encoder_Pins_H) /* Pins Encoder_Pins_H */
#define CY_PINS_Encoder_Pins_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Encoder_Pins_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Encoder_Pins_Write(uint8 value) ;
void    Encoder_Pins_SetDriveMode(uint8 mode) ;
uint8   Encoder_Pins_ReadDataReg(void) ;
uint8   Encoder_Pins_Read(void) ;
uint8   Encoder_Pins_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Encoder_Pins_DRIVE_MODE_BITS        (3)
#define Encoder_Pins_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Encoder_Pins_DRIVE_MODE_BITS))

#define Encoder_Pins_DM_ALG_HIZ         (0x00u)
#define Encoder_Pins_DM_DIG_HIZ         (0x01u)
#define Encoder_Pins_DM_RES_UP          (0x02u)
#define Encoder_Pins_DM_RES_DWN         (0x03u)
#define Encoder_Pins_DM_OD_LO           (0x04u)
#define Encoder_Pins_DM_OD_HI           (0x05u)
#define Encoder_Pins_DM_STRONG          (0x06u)
#define Encoder_Pins_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Encoder_Pins_MASK               Encoder_Pins__MASK
#define Encoder_Pins_SHIFT              Encoder_Pins__SHIFT
#define Encoder_Pins_WIDTH              2u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Encoder_Pins_PS                     (* (reg32 *) Encoder_Pins__PS)
/* Port Configuration */
#define Encoder_Pins_PC                     (* (reg32 *) Encoder_Pins__PC)
/* Data Register */
#define Encoder_Pins_DR                     (* (reg32 *) Encoder_Pins__DR)
/* Input Buffer Disable Override */
#define Encoder_Pins_INP_DIS                (* (reg32 *) Encoder_Pins__PC2)


#if defined(Encoder_Pins__INTSTAT)  /* Interrupt Registers */

    #define Encoder_Pins_INTSTAT                (* (reg32 *) Encoder_Pins__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Encoder_Pins_DRIVE_MODE_SHIFT       (0x00u)
#define Encoder_Pins_DRIVE_MODE_MASK        (0x07u << Encoder_Pins_DRIVE_MODE_SHIFT)


#endif /* End Pins Encoder_Pins_H */


/* [] END OF FILE */
