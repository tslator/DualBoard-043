/*******************************************************************************
* File Name: Enable_Pin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Enable_Pin_H) /* Pins Enable_Pin_H */
#define CY_PINS_Enable_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Enable_Pin_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Enable_Pin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Enable_Pin_Read(void);
void    Enable_Pin_Write(uint8 value);
uint8   Enable_Pin_ReadDataReg(void);
#if defined(Enable_Pin__PC) || (CY_PSOC4_4200L) 
    void    Enable_Pin_SetDriveMode(uint8 mode);
#endif
void    Enable_Pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   Enable_Pin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Enable_Pin_Sleep(void); 
void Enable_Pin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Enable_Pin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Enable_Pin_DRIVE_MODE_BITS        (3)
    #define Enable_Pin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Enable_Pin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Enable_Pin_SetDriveMode() function.
         *  @{
         */
        #define Enable_Pin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Enable_Pin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Enable_Pin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Enable_Pin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Enable_Pin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Enable_Pin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Enable_Pin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Enable_Pin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Enable_Pin_MASK               Enable_Pin__MASK
#define Enable_Pin_SHIFT              Enable_Pin__SHIFT
#define Enable_Pin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Enable_Pin_SetInterruptMode() function.
     *  @{
     */
        #define Enable_Pin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Enable_Pin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Enable_Pin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Enable_Pin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Enable_Pin__SIO)
    #define Enable_Pin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Enable_Pin__PC) && (CY_PSOC4_4200L)
    #define Enable_Pin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Enable_Pin_USBIO_DISABLE              ((uint32)(~Enable_Pin_USBIO_ENABLE))
    #define Enable_Pin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Enable_Pin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Enable_Pin_USBIO_ENTER_SLEEP          ((uint32)((1u << Enable_Pin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Enable_Pin_USBIO_SUSPEND_DEL_SHIFT)))
    #define Enable_Pin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Enable_Pin_USBIO_SUSPEND_SHIFT)))
    #define Enable_Pin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Enable_Pin_USBIO_SUSPEND_DEL_SHIFT)))
    #define Enable_Pin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Enable_Pin__PC)
    /* Port Configuration */
    #define Enable_Pin_PC                 (* (reg32 *) Enable_Pin__PC)
#endif
/* Pin State */
#define Enable_Pin_PS                     (* (reg32 *) Enable_Pin__PS)
/* Data Register */
#define Enable_Pin_DR                     (* (reg32 *) Enable_Pin__DR)
/* Input Buffer Disable Override */
#define Enable_Pin_INP_DIS                (* (reg32 *) Enable_Pin__PC2)

/* Interrupt configuration Registers */
#define Enable_Pin_INTCFG                 (* (reg32 *) Enable_Pin__INTCFG)
#define Enable_Pin_INTSTAT                (* (reg32 *) Enable_Pin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Enable_Pin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Enable_Pin__SIO)
    #define Enable_Pin_SIO_REG            (* (reg32 *) Enable_Pin__SIO)
#endif /* (Enable_Pin__SIO_CFG) */

/* USBIO registers */
#if !defined(Enable_Pin__PC) && (CY_PSOC4_4200L)
    #define Enable_Pin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Enable_Pin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Enable_Pin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Enable_Pin_DRIVE_MODE_SHIFT       (0x00u)
#define Enable_Pin_DRIVE_MODE_MASK        (0x07u << Enable_Pin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Enable_Pin_H */


/* [] END OF FILE */
