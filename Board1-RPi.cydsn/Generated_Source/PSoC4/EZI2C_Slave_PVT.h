/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_EZI2C_Slave_H)
#define CY_SCB_PVT_EZI2C_Slave_H

#include "EZI2C_Slave.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define EZI2C_Slave_SetI2CExtClkInterruptMode(interruptMask) EZI2C_Slave_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define EZI2C_Slave_ClearI2CExtClkInterruptSource(interruptMask) EZI2C_Slave_CLEAR_INTR_I2C_EC(interruptMask)
#define EZI2C_Slave_GetI2CExtClkInterruptSource()                (EZI2C_Slave_INTR_I2C_EC_REG)
#define EZI2C_Slave_GetI2CExtClkInterruptMode()                  (EZI2C_Slave_INTR_I2C_EC_MASK_REG)
#define EZI2C_Slave_GetI2CExtClkInterruptSourceMasked()          (EZI2C_Slave_INTR_I2C_EC_MASKED_REG)

#if (!EZI2C_Slave_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define EZI2C_Slave_SetSpiExtClkInterruptMode(interruptMask) \
                                                                EZI2C_Slave_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define EZI2C_Slave_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                EZI2C_Slave_CLEAR_INTR_SPI_EC(interruptMask)
    #define EZI2C_Slave_GetExtSpiClkInterruptSource()                 (EZI2C_Slave_INTR_SPI_EC_REG)
    #define EZI2C_Slave_GetExtSpiClkInterruptMode()                   (EZI2C_Slave_INTR_SPI_EC_MASK_REG)
    #define EZI2C_Slave_GetExtSpiClkInterruptSourceMasked()           (EZI2C_Slave_INTR_SPI_EC_MASKED_REG)
#endif /* (!EZI2C_Slave_CY_SCBIP_V1) */

#if(EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void EZI2C_Slave_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (EZI2C_Slave_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_EZI2C_Slave_CUSTOM_INTR_HANDLER)
    extern cyisraddress EZI2C_Slave_customIntrHandler;
#endif /* !defined (CY_REMOVE_EZI2C_Slave_CUSTOM_INTR_HANDLER) */
#endif /* (EZI2C_Slave_SCB_IRQ_INTERNAL) */

extern EZI2C_Slave_BACKUP_STRUCT EZI2C_Slave_backup;

#if(EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 EZI2C_Slave_scbMode;
    extern uint8 EZI2C_Slave_scbEnableWake;
    extern uint8 EZI2C_Slave_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 EZI2C_Slave_mode;
    extern uint8 EZI2C_Slave_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * EZI2C_Slave_rxBuffer;
    extern uint8   EZI2C_Slave_rxDataBits;
    extern uint32  EZI2C_Slave_rxBufferSize;

    extern volatile uint8 * EZI2C_Slave_txBuffer;
    extern uint8   EZI2C_Slave_txDataBits;
    extern uint32  EZI2C_Slave_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 EZI2C_Slave_numberOfAddr;
    extern uint8 EZI2C_Slave_subAddrSize;
#endif /* (EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define EZI2C_Slave_SCB_MODE_I2C_RUNTM_CFG     (EZI2C_Slave_SCB_MODE_I2C      == EZI2C_Slave_scbMode)
    #define EZI2C_Slave_SCB_MODE_SPI_RUNTM_CFG     (EZI2C_Slave_SCB_MODE_SPI      == EZI2C_Slave_scbMode)
    #define EZI2C_Slave_SCB_MODE_UART_RUNTM_CFG    (EZI2C_Slave_SCB_MODE_UART     == EZI2C_Slave_scbMode)
    #define EZI2C_Slave_SCB_MODE_EZI2C_RUNTM_CFG   (EZI2C_Slave_SCB_MODE_EZI2C    == EZI2C_Slave_scbMode)
    #define EZI2C_Slave_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (EZI2C_Slave_SCB_MODE_UNCONFIG == EZI2C_Slave_scbMode)

    /* Defines wakeup enable */
    #define EZI2C_Slave_SCB_WAKE_ENABLE_CHECK       (0u != EZI2C_Slave_scbEnableWake)
#endif /* (EZI2C_Slave_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!EZI2C_Slave_CY_SCBIP_V1)
    #define EZI2C_Slave_SCB_PINS_NUMBER    (7u)
#else
    #define EZI2C_Slave_SCB_PINS_NUMBER    (2u)
#endif /* (!EZI2C_Slave_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_EZI2C_Slave_H) */


/* [] END OF FILE */
