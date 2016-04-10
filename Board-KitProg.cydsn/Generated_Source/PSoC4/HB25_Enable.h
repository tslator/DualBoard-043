/*******************************************************************************
* File Name: HB25_Enable.h  
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

#if !defined(CY_PINS_HB25_Enable_H) /* Pins HB25_Enable_H */
#define CY_PINS_HB25_Enable_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HB25_Enable_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    HB25_Enable_Write(uint8 value) ;
void    HB25_Enable_SetDriveMode(uint8 mode) ;
uint8   HB25_Enable_ReadDataReg(void) ;
uint8   HB25_Enable_Read(void) ;
uint8   HB25_Enable_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HB25_Enable_DRIVE_MODE_BITS        (3)
#define HB25_Enable_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HB25_Enable_DRIVE_MODE_BITS))

#define HB25_Enable_DM_ALG_HIZ         (0x00u)
#define HB25_Enable_DM_DIG_HIZ         (0x01u)
#define HB25_Enable_DM_RES_UP          (0x02u)
#define HB25_Enable_DM_RES_DWN         (0x03u)
#define HB25_Enable_DM_OD_LO           (0x04u)
#define HB25_Enable_DM_OD_HI           (0x05u)
#define HB25_Enable_DM_STRONG          (0x06u)
#define HB25_Enable_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define HB25_Enable_MASK               HB25_Enable__MASK
#define HB25_Enable_SHIFT              HB25_Enable__SHIFT
#define HB25_Enable_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HB25_Enable_PS                     (* (reg32 *) HB25_Enable__PS)
/* Port Configuration */
#define HB25_Enable_PC                     (* (reg32 *) HB25_Enable__PC)
/* Data Register */
#define HB25_Enable_DR                     (* (reg32 *) HB25_Enable__DR)
/* Input Buffer Disable Override */
#define HB25_Enable_INP_DIS                (* (reg32 *) HB25_Enable__PC2)


#if defined(HB25_Enable__INTSTAT)  /* Interrupt Registers */

    #define HB25_Enable_INTSTAT                (* (reg32 *) HB25_Enable__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define HB25_Enable_DRIVE_MODE_SHIFT       (0x00u)
#define HB25_Enable_DRIVE_MODE_MASK        (0x07u << HB25_Enable_DRIVE_MODE_SHIFT)


#endif /* End Pins HB25_Enable_H */


/* [] END OF FILE */
