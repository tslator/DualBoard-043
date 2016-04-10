/*******************************************************************************
* File Name: HB25_PWM_Pin_1.h  
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

#if !defined(CY_PINS_HB25_PWM_Pin_1_H) /* Pins HB25_PWM_Pin_1_H */
#define CY_PINS_HB25_PWM_Pin_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HB25_PWM_Pin_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    HB25_PWM_Pin_1_Write(uint8 value) ;
void    HB25_PWM_Pin_1_SetDriveMode(uint8 mode) ;
uint8   HB25_PWM_Pin_1_ReadDataReg(void) ;
uint8   HB25_PWM_Pin_1_Read(void) ;
uint8   HB25_PWM_Pin_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HB25_PWM_Pin_1_DRIVE_MODE_BITS        (3)
#define HB25_PWM_Pin_1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HB25_PWM_Pin_1_DRIVE_MODE_BITS))

#define HB25_PWM_Pin_1_DM_ALG_HIZ         (0x00u)
#define HB25_PWM_Pin_1_DM_DIG_HIZ         (0x01u)
#define HB25_PWM_Pin_1_DM_RES_UP          (0x02u)
#define HB25_PWM_Pin_1_DM_RES_DWN         (0x03u)
#define HB25_PWM_Pin_1_DM_OD_LO           (0x04u)
#define HB25_PWM_Pin_1_DM_OD_HI           (0x05u)
#define HB25_PWM_Pin_1_DM_STRONG          (0x06u)
#define HB25_PWM_Pin_1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define HB25_PWM_Pin_1_MASK               HB25_PWM_Pin_1__MASK
#define HB25_PWM_Pin_1_SHIFT              HB25_PWM_Pin_1__SHIFT
#define HB25_PWM_Pin_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HB25_PWM_Pin_1_PS                     (* (reg32 *) HB25_PWM_Pin_1__PS)
/* Port Configuration */
#define HB25_PWM_Pin_1_PC                     (* (reg32 *) HB25_PWM_Pin_1__PC)
/* Data Register */
#define HB25_PWM_Pin_1_DR                     (* (reg32 *) HB25_PWM_Pin_1__DR)
/* Input Buffer Disable Override */
#define HB25_PWM_Pin_1_INP_DIS                (* (reg32 *) HB25_PWM_Pin_1__PC2)


#if defined(HB25_PWM_Pin_1__INTSTAT)  /* Interrupt Registers */

    #define HB25_PWM_Pin_1_INTSTAT                (* (reg32 *) HB25_PWM_Pin_1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define HB25_PWM_Pin_1_DRIVE_MODE_SHIFT       (0x00u)
#define HB25_PWM_Pin_1_DRIVE_MODE_MASK        (0x07u << HB25_PWM_Pin_1_DRIVE_MODE_SHIFT)


#endif /* End Pins HB25_PWM_Pin_1_H */


/* [] END OF FILE */
