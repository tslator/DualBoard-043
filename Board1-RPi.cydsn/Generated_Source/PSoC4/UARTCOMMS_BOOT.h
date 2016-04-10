/*******************************************************************************
* File Name: UARTCOMMS_BOOT.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UARTCOMMS_H)
#define CY_SCB_BOOT_UARTCOMMS_H

#include "UARTCOMMS_PVT.h"

#if (UARTCOMMS_SCB_MODE_I2C_INC)
    #include "UARTCOMMS_I2C.h"
#endif /* (UARTCOMMS_SCB_MODE_I2C_INC) */

#if (UARTCOMMS_SCB_MODE_EZI2C_INC)
    #include "UARTCOMMS_EZI2C.h"
#endif /* (UARTCOMMS_SCB_MODE_EZI2C_INC) */

#if (UARTCOMMS_SCB_MODE_SPI_INC || UARTCOMMS_SCB_MODE_UART_INC)
    #include "UARTCOMMS_SPI_UART.h"
#endif /* (UARTCOMMS_SCB_MODE_SPI_INC || UARTCOMMS_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define UARTCOMMS_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UARTCOMMS) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (UARTCOMMS_SCB_MODE_I2C_INC)
    #define UARTCOMMS_I2C_BTLDR_COMM_ENABLED     (UARTCOMMS_BTLDR_COMM_ENABLED && \
                                                            (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UARTCOMMS_I2C_SLAVE_CONST))
#else
     #define UARTCOMMS_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (UARTCOMMS_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (UARTCOMMS_SCB_MODE_EZI2C_INC)
    #define UARTCOMMS_EZI2C_BTLDR_COMM_ENABLED   (UARTCOMMS_BTLDR_COMM_ENABLED && \
                                                         UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define UARTCOMMS_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UARTCOMMS_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (UARTCOMMS_SCB_MODE_SPI_INC)
    #define UARTCOMMS_SPI_BTLDR_COMM_ENABLED     (UARTCOMMS_BTLDR_COMM_ENABLED && \
                                                            (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UARTCOMMS_SPI_SLAVE_CONST))
#else
        #define UARTCOMMS_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (UARTCOMMS_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (UARTCOMMS_SCB_MODE_UART_INC)
       #define UARTCOMMS_UART_BTLDR_COMM_ENABLED    (UARTCOMMS_BTLDR_COMM_ENABLED && \
                                                            (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (UARTCOMMS_UART_RX_DIRECTION && \
                                                              UARTCOMMS_UART_TX_DIRECTION)))
#else
     #define UARTCOMMS_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (UARTCOMMS_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define UARTCOMMS_BTLDR_COMM_MODE_ENABLED    (UARTCOMMS_I2C_BTLDR_COMM_ENABLED   || \
                                                     UARTCOMMS_SPI_BTLDR_COMM_ENABLED   || \
                                                     UARTCOMMS_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UARTCOMMS_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void UARTCOMMS_I2CCyBtldrCommStart(void);
    void UARTCOMMS_I2CCyBtldrCommStop (void);
    void UARTCOMMS_I2CCyBtldrCommReset(void);
    cystatus UARTCOMMS_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UARTCOMMS_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (UARTCOMMS_SCB_MODE_I2C_CONST_CFG)
        #define UARTCOMMS_CyBtldrCommStart   UARTCOMMS_I2CCyBtldrCommStart
        #define UARTCOMMS_CyBtldrCommStop    UARTCOMMS_I2CCyBtldrCommStop
        #define UARTCOMMS_CyBtldrCommReset   UARTCOMMS_I2CCyBtldrCommReset
        #define UARTCOMMS_CyBtldrCommRead    UARTCOMMS_I2CCyBtldrCommRead
        #define UARTCOMMS_CyBtldrCommWrite   UARTCOMMS_I2CCyBtldrCommWrite
    #endif /* (UARTCOMMS_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UARTCOMMS_EzI2CCyBtldrCommStart(void);
    void UARTCOMMS_EzI2CCyBtldrCommStop (void);
    void UARTCOMMS_EzI2CCyBtldrCommReset(void);
    cystatus UARTCOMMS_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UARTCOMMS_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (UARTCOMMS_SCB_MODE_EZI2C_CONST_CFG)
        #define UARTCOMMS_CyBtldrCommStart   UARTCOMMS_EzI2CCyBtldrCommStart
        #define UARTCOMMS_CyBtldrCommStop    UARTCOMMS_EzI2CCyBtldrCommStop
        #define UARTCOMMS_CyBtldrCommReset   UARTCOMMS_EzI2CCyBtldrCommReset
        #define UARTCOMMS_CyBtldrCommRead    UARTCOMMS_EzI2CCyBtldrCommRead
        #define UARTCOMMS_CyBtldrCommWrite   UARTCOMMS_EzI2CCyBtldrCommWrite
    #endif /* (UARTCOMMS_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UARTCOMMS_SpiCyBtldrCommStart(void);
    void UARTCOMMS_SpiCyBtldrCommStop (void);
    void UARTCOMMS_SpiCyBtldrCommReset(void);
    cystatus UARTCOMMS_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UARTCOMMS_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (UARTCOMMS_SCB_MODE_SPI_CONST_CFG)
        #define UARTCOMMS_CyBtldrCommStart   UARTCOMMS_SpiCyBtldrCommStart
        #define UARTCOMMS_CyBtldrCommStop    UARTCOMMS_SpiCyBtldrCommStop
        #define UARTCOMMS_CyBtldrCommReset   UARTCOMMS_SpiCyBtldrCommReset
        #define UARTCOMMS_CyBtldrCommRead    UARTCOMMS_SpiCyBtldrCommRead
        #define UARTCOMMS_CyBtldrCommWrite   UARTCOMMS_SpiCyBtldrCommWrite
    #endif /* (UARTCOMMS_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UARTCOMMS_UartCyBtldrCommStart(void);
    void UARTCOMMS_UartCyBtldrCommStop (void);
    void UARTCOMMS_UartCyBtldrCommReset(void);
    cystatus UARTCOMMS_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UARTCOMMS_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (UARTCOMMS_SCB_MODE_UART_CONST_CFG)
        #define UARTCOMMS_CyBtldrCommStart   UARTCOMMS_UartCyBtldrCommStart
        #define UARTCOMMS_CyBtldrCommStop    UARTCOMMS_UartCyBtldrCommStop
        #define UARTCOMMS_CyBtldrCommReset   UARTCOMMS_UartCyBtldrCommReset
        #define UARTCOMMS_CyBtldrCommRead    UARTCOMMS_UartCyBtldrCommRead
        #define UARTCOMMS_CyBtldrCommWrite   UARTCOMMS_UartCyBtldrCommWrite
    #endif /* (UARTCOMMS_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_BTLDR_COMM_ENABLED)
    #if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void UARTCOMMS_CyBtldrCommStart(void);
        void UARTCOMMS_CyBtldrCommStop (void);
        void UARTCOMMS_CyBtldrCommReset(void);
        cystatus UARTCOMMS_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UARTCOMMS_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UARTCOMMS)
        #define CyBtldrCommStart    UARTCOMMS_CyBtldrCommStart
        #define CyBtldrCommStop     UARTCOMMS_CyBtldrCommStop
        #define CyBtldrCommReset    UARTCOMMS_CyBtldrCommReset
        #define CyBtldrCommWrite    UARTCOMMS_CyBtldrCommWrite
        #define CyBtldrCommRead     UARTCOMMS_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UARTCOMMS) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UARTCOMMS_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define UARTCOMMS_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define UARTCOMMS_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define UARTCOMMS_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define UARTCOMMS_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef UARTCOMMS_SPI_BYTE_TO_BYTE
    #define UARTCOMMS_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef UARTCOMMS_UART_BYTE_TO_BYTE
    #define UARTCOMMS_UART_BYTE_TO_BYTE  (175u)
#endif /* UARTCOMMS_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_UARTCOMMS_H) */


/* [] END OF FILE */
