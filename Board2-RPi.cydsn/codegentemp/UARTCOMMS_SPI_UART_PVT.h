/*******************************************************************************
* File Name: UARTCOMMS_SPI_UART_PVT.h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_UARTCOMMS_H)
#define CY_SCB_SPI_UART_PVT_UARTCOMMS_H

#include "UARTCOMMS_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UARTCOMMS_rxBufferHead;
    extern volatile uint32  UARTCOMMS_rxBufferTail;
    extern volatile uint8   UARTCOMMS_rxBufferOverflow;
#endif /* (UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UARTCOMMS_txBufferHead;
    extern volatile uint32  UARTCOMMS_txBufferTail;
#endif /* (UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UARTCOMMS_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UARTCOMMS_rxBufferInternal[UARTCOMMS_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UARTCOMMS_INTERNAL_RX_SW_BUFFER) */

#if (UARTCOMMS_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UARTCOMMS_txBufferInternal[UARTCOMMS_TX_BUFFER_SIZE];
#endif /* (UARTCOMMS_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UARTCOMMS_SpiPostEnable(void);
void UARTCOMMS_SpiStop(void);

#if (UARTCOMMS_SCB_MODE_SPI_CONST_CFG)
    void UARTCOMMS_SpiInit(void);
#endif /* (UARTCOMMS_SCB_MODE_SPI_CONST_CFG) */

#if (UARTCOMMS_SPI_WAKE_ENABLE_CONST)
    void UARTCOMMS_SpiSaveConfig(void);
    void UARTCOMMS_SpiRestoreConfig(void);
#endif /* (UARTCOMMS_SPI_WAKE_ENABLE_CONST) */

void UARTCOMMS_UartPostEnable(void);
void UARTCOMMS_UartStop(void);

#if (UARTCOMMS_SCB_MODE_UART_CONST_CFG)
    void UARTCOMMS_UartInit(void);
#endif /* (UARTCOMMS_SCB_MODE_UART_CONST_CFG) */

#if (UARTCOMMS_UART_WAKE_ENABLE_CONST)
    void UARTCOMMS_UartSaveConfig(void);
    void UARTCOMMS_UartRestoreConfig(void);
#endif /* (UARTCOMMS_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UARTCOMMS_SetPins() */
#define UARTCOMMS_UART_RX_PIN_ENABLE    (UARTCOMMS_UART_RX)
#define UARTCOMMS_UART_TX_PIN_ENABLE    (UARTCOMMS_UART_TX)

/* UART RTS and CTS position to be used in  UARTCOMMS_SetPins() */
#define UARTCOMMS_UART_RTS_PIN_ENABLE    (0x10u)
#define UARTCOMMS_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UARTCOMMS_SpiUartEnableIntRx(intSourceMask)  UARTCOMMS_SetRxInterruptMode(intSourceMask)
#define UARTCOMMS_SpiUartEnableIntTx(intSourceMask)  UARTCOMMS_SetTxInterruptMode(intSourceMask)
uint32  UARTCOMMS_SpiUartDisableIntRx(void);
uint32  UARTCOMMS_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UARTCOMMS_H) */


/* [] END OF FILE */
