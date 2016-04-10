/*******************************************************************************
* File Name: .h
* Version 3.10
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

#if !defined(CY_SCB_PVT_I2CIF_H)
#define CY_SCB_PVT_I2CIF_H

#include "I2CIF.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define I2CIF_SetI2CExtClkInterruptMode(interruptMask) I2CIF_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define I2CIF_ClearI2CExtClkInterruptSource(interruptMask) I2CIF_CLEAR_INTR_I2C_EC(interruptMask)
#define I2CIF_GetI2CExtClkInterruptSource()                (I2CIF_INTR_I2C_EC_REG)
#define I2CIF_GetI2CExtClkInterruptMode()                  (I2CIF_INTR_I2C_EC_MASK_REG)
#define I2CIF_GetI2CExtClkInterruptSourceMasked()          (I2CIF_INTR_I2C_EC_MASKED_REG)

#if (!I2CIF_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define I2CIF_SetSpiExtClkInterruptMode(interruptMask) \
                                                                I2CIF_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define I2CIF_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                I2CIF_CLEAR_INTR_SPI_EC(interruptMask)
    #define I2CIF_GetExtSpiClkInterruptSource()                 (I2CIF_INTR_SPI_EC_REG)
    #define I2CIF_GetExtSpiClkInterruptMode()                   (I2CIF_INTR_SPI_EC_MASK_REG)
    #define I2CIF_GetExtSpiClkInterruptSourceMasked()           (I2CIF_INTR_SPI_EC_MASKED_REG)
#endif /* (!I2CIF_CY_SCBIP_V1) */

#if(I2CIF_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void I2CIF_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (I2CIF_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_I2CIF_CUSTOM_INTR_HANDLER)
    extern cyisraddress I2CIF_customIntrHandler;
#endif /* !defined (CY_REMOVE_I2CIF_CUSTOM_INTR_HANDLER) */
#endif /* (I2CIF_SCB_IRQ_INTERNAL) */

extern I2CIF_BACKUP_STRUCT I2CIF_backup;

#if(I2CIF_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 I2CIF_scbMode;
    extern uint8 I2CIF_scbEnableWake;
    extern uint8 I2CIF_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 I2CIF_mode;
    extern uint8 I2CIF_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * I2CIF_rxBuffer;
    extern uint8   I2CIF_rxDataBits;
    extern uint32  I2CIF_rxBufferSize;

    extern volatile uint8 * I2CIF_txBuffer;
    extern uint8   I2CIF_txDataBits;
    extern uint32  I2CIF_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 I2CIF_numberOfAddr;
    extern uint8 I2CIF_subAddrSize;
#endif /* (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(I2CIF_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define I2CIF_SCB_MODE_I2C_RUNTM_CFG     (I2CIF_SCB_MODE_I2C      == I2CIF_scbMode)
    #define I2CIF_SCB_MODE_SPI_RUNTM_CFG     (I2CIF_SCB_MODE_SPI      == I2CIF_scbMode)
    #define I2CIF_SCB_MODE_UART_RUNTM_CFG    (I2CIF_SCB_MODE_UART     == I2CIF_scbMode)
    #define I2CIF_SCB_MODE_EZI2C_RUNTM_CFG   (I2CIF_SCB_MODE_EZI2C    == I2CIF_scbMode)
    #define I2CIF_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (I2CIF_SCB_MODE_UNCONFIG == I2CIF_scbMode)

    /* Defines wakeup enable */
    #define I2CIF_SCB_WAKE_ENABLE_CHECK       (0u != I2CIF_scbEnableWake)
#endif /* (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!I2CIF_CY_SCBIP_V1)
    #define I2CIF_SCB_PINS_NUMBER    (7u)
#else
    #define I2CIF_SCB_PINS_NUMBER    (2u)
#endif /* (!I2CIF_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_I2CIF_H) */


/* [] END OF FILE */
