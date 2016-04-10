/*******************************************************************************
* File Name: I2CIF_BOOT.h
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

#if !defined(CY_SCB_BOOT_I2CIF_H)
#define CY_SCB_BOOT_I2CIF_H

#include "I2CIF_PVT.h"

#if (I2CIF_SCB_MODE_I2C_INC)
    #include "I2CIF_I2C.h"
#endif /* (I2CIF_SCB_MODE_I2C_INC) */

#if (I2CIF_SCB_MODE_EZI2C_INC)
    #include "I2CIF_EZI2C.h"
#endif /* (I2CIF_SCB_MODE_EZI2C_INC) */

#if (I2CIF_SCB_MODE_SPI_INC || I2CIF_SCB_MODE_UART_INC)
    #include "I2CIF_SPI_UART.h"
#endif /* (I2CIF_SCB_MODE_SPI_INC || I2CIF_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define I2CIF_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2CIF) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (I2CIF_SCB_MODE_I2C_INC)
    #define I2CIF_I2C_BTLDR_COMM_ENABLED     (I2CIF_BTLDR_COMM_ENABLED && \
                                                            (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             I2CIF_I2C_SLAVE_CONST))
#else
     #define I2CIF_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (I2CIF_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (I2CIF_SCB_MODE_EZI2C_INC)
    #define I2CIF_EZI2C_BTLDR_COMM_ENABLED   (I2CIF_BTLDR_COMM_ENABLED && \
                                                         I2CIF_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define I2CIF_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (I2CIF_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (I2CIF_SCB_MODE_SPI_INC)
    #define I2CIF_SPI_BTLDR_COMM_ENABLED     (I2CIF_BTLDR_COMM_ENABLED && \
                                                            (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             I2CIF_SPI_SLAVE_CONST))
#else
        #define I2CIF_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (I2CIF_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (I2CIF_SCB_MODE_UART_INC)
       #define I2CIF_UART_BTLDR_COMM_ENABLED    (I2CIF_BTLDR_COMM_ENABLED && \
                                                            (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (I2CIF_UART_RX_DIRECTION && \
                                                              I2CIF_UART_TX_DIRECTION)))
#else
     #define I2CIF_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (I2CIF_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define I2CIF_BTLDR_COMM_MODE_ENABLED    (I2CIF_I2C_BTLDR_COMM_ENABLED   || \
                                                     I2CIF_SPI_BTLDR_COMM_ENABLED   || \
                                                     I2CIF_EZI2C_BTLDR_COMM_ENABLED || \
                                                     I2CIF_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void I2CIF_I2CCyBtldrCommStart(void);
    void I2CIF_I2CCyBtldrCommStop (void);
    void I2CIF_I2CCyBtldrCommReset(void);
    cystatus I2CIF_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CIF_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (I2CIF_SCB_MODE_I2C_CONST_CFG)
        #define I2CIF_CyBtldrCommStart   I2CIF_I2CCyBtldrCommStart
        #define I2CIF_CyBtldrCommStop    I2CIF_I2CCyBtldrCommStop
        #define I2CIF_CyBtldrCommReset   I2CIF_I2CCyBtldrCommReset
        #define I2CIF_CyBtldrCommRead    I2CIF_I2CCyBtldrCommRead
        #define I2CIF_CyBtldrCommWrite   I2CIF_I2CCyBtldrCommWrite
    #endif /* (I2CIF_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void I2CIF_EzI2CCyBtldrCommStart(void);
    void I2CIF_EzI2CCyBtldrCommStop (void);
    void I2CIF_EzI2CCyBtldrCommReset(void);
    cystatus I2CIF_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CIF_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (I2CIF_SCB_MODE_EZI2C_CONST_CFG)
        #define I2CIF_CyBtldrCommStart   I2CIF_EzI2CCyBtldrCommStart
        #define I2CIF_CyBtldrCommStop    I2CIF_EzI2CCyBtldrCommStop
        #define I2CIF_CyBtldrCommReset   I2CIF_EzI2CCyBtldrCommReset
        #define I2CIF_CyBtldrCommRead    I2CIF_EzI2CCyBtldrCommRead
        #define I2CIF_CyBtldrCommWrite   I2CIF_EzI2CCyBtldrCommWrite
    #endif /* (I2CIF_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void I2CIF_SpiCyBtldrCommStart(void);
    void I2CIF_SpiCyBtldrCommStop (void);
    void I2CIF_SpiCyBtldrCommReset(void);
    cystatus I2CIF_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CIF_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (I2CIF_SCB_MODE_SPI_CONST_CFG)
        #define I2CIF_CyBtldrCommStart   I2CIF_SpiCyBtldrCommStart
        #define I2CIF_CyBtldrCommStop    I2CIF_SpiCyBtldrCommStop
        #define I2CIF_CyBtldrCommReset   I2CIF_SpiCyBtldrCommReset
        #define I2CIF_CyBtldrCommRead    I2CIF_SpiCyBtldrCommRead
        #define I2CIF_CyBtldrCommWrite   I2CIF_SpiCyBtldrCommWrite
    #endif /* (I2CIF_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void I2CIF_UartCyBtldrCommStart(void);
    void I2CIF_UartCyBtldrCommStop (void);
    void I2CIF_UartCyBtldrCommReset(void);
    cystatus I2CIF_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2CIF_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (I2CIF_SCB_MODE_UART_CONST_CFG)
        #define I2CIF_CyBtldrCommStart   I2CIF_UartCyBtldrCommStart
        #define I2CIF_CyBtldrCommStop    I2CIF_UartCyBtldrCommStop
        #define I2CIF_CyBtldrCommReset   I2CIF_UartCyBtldrCommReset
        #define I2CIF_CyBtldrCommRead    I2CIF_UartCyBtldrCommRead
        #define I2CIF_CyBtldrCommWrite   I2CIF_UartCyBtldrCommWrite
    #endif /* (I2CIF_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_BTLDR_COMM_ENABLED)
    #if (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void I2CIF_CyBtldrCommStart(void);
        void I2CIF_CyBtldrCommStop (void);
        void I2CIF_CyBtldrCommReset(void);
        cystatus I2CIF_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus I2CIF_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2CIF)
        #define CyBtldrCommStart    I2CIF_CyBtldrCommStart
        #define CyBtldrCommStop     I2CIF_CyBtldrCommStop
        #define CyBtldrCommReset    I2CIF_CyBtldrCommReset
        #define CyBtldrCommWrite    I2CIF_CyBtldrCommWrite
        #define CyBtldrCommRead     I2CIF_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2CIF) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2CIF_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define I2CIF_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define I2CIF_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define I2CIF_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define I2CIF_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef I2CIF_SPI_BYTE_TO_BYTE
    #define I2CIF_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef I2CIF_UART_BYTE_TO_BYTE
    #define I2CIF_UART_BYTE_TO_BYTE  (2500u)
#endif /* I2CIF_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_I2CIF_H) */


/* [] END OF FILE */