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

#if !defined(CY_SCB_PVT_UARTCOMMS_H)
#define CY_SCB_PVT_UARTCOMMS_H

#include "UARTCOMMS.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UARTCOMMS_SetI2CExtClkInterruptMode(interruptMask) UARTCOMMS_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UARTCOMMS_ClearI2CExtClkInterruptSource(interruptMask) UARTCOMMS_CLEAR_INTR_I2C_EC(interruptMask)
#define UARTCOMMS_GetI2CExtClkInterruptSource()                (UARTCOMMS_INTR_I2C_EC_REG)
#define UARTCOMMS_GetI2CExtClkInterruptMode()                  (UARTCOMMS_INTR_I2C_EC_MASK_REG)
#define UARTCOMMS_GetI2CExtClkInterruptSourceMasked()          (UARTCOMMS_INTR_I2C_EC_MASKED_REG)

#if (!UARTCOMMS_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UARTCOMMS_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UARTCOMMS_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UARTCOMMS_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UARTCOMMS_CLEAR_INTR_SPI_EC(interruptMask)
    #define UARTCOMMS_GetExtSpiClkInterruptSource()                 (UARTCOMMS_INTR_SPI_EC_REG)
    #define UARTCOMMS_GetExtSpiClkInterruptMode()                   (UARTCOMMS_INTR_SPI_EC_MASK_REG)
    #define UARTCOMMS_GetExtSpiClkInterruptSourceMasked()           (UARTCOMMS_INTR_SPI_EC_MASKED_REG)
#endif /* (!UARTCOMMS_CY_SCBIP_V1) */

#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UARTCOMMS_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UARTCOMMS_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UARTCOMMS_CUSTOM_INTR_HANDLER)
    extern cyisraddress UARTCOMMS_customIntrHandler;
#endif /* !defined (CY_REMOVE_UARTCOMMS_CUSTOM_INTR_HANDLER) */
#endif /* (UARTCOMMS_SCB_IRQ_INTERNAL) */

extern UARTCOMMS_BACKUP_STRUCT UARTCOMMS_backup;

#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UARTCOMMS_scbMode;
    extern uint8 UARTCOMMS_scbEnableWake;
    extern uint8 UARTCOMMS_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UARTCOMMS_mode;
    extern uint8 UARTCOMMS_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UARTCOMMS_rxBuffer;
    extern uint8   UARTCOMMS_rxDataBits;
    extern uint32  UARTCOMMS_rxBufferSize;

    extern volatile uint8 * UARTCOMMS_txBuffer;
    extern uint8   UARTCOMMS_txDataBits;
    extern uint32  UARTCOMMS_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UARTCOMMS_numberOfAddr;
    extern uint8 UARTCOMMS_subAddrSize;
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UARTCOMMS_SCB_MODE_I2C_RUNTM_CFG     (UARTCOMMS_SCB_MODE_I2C      == UARTCOMMS_scbMode)
    #define UARTCOMMS_SCB_MODE_SPI_RUNTM_CFG     (UARTCOMMS_SCB_MODE_SPI      == UARTCOMMS_scbMode)
    #define UARTCOMMS_SCB_MODE_UART_RUNTM_CFG    (UARTCOMMS_SCB_MODE_UART     == UARTCOMMS_scbMode)
    #define UARTCOMMS_SCB_MODE_EZI2C_RUNTM_CFG   (UARTCOMMS_SCB_MODE_EZI2C    == UARTCOMMS_scbMode)
    #define UARTCOMMS_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UARTCOMMS_SCB_MODE_UNCONFIG == UARTCOMMS_scbMode)

    /* Defines wakeup enable */
    #define UARTCOMMS_SCB_WAKE_ENABLE_CHECK       (0u != UARTCOMMS_scbEnableWake)
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UARTCOMMS_CY_SCBIP_V1)
    #define UARTCOMMS_SCB_PINS_NUMBER    (7u)
#else
    #define UARTCOMMS_SCB_PINS_NUMBER    (2u)
#endif /* (!UARTCOMMS_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UARTCOMMS_H) */


/* [] END OF FILE */
