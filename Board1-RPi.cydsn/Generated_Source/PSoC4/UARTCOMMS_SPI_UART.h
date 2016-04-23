/*******************************************************************************
* File Name: UARTCOMMS_SPI_UART.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_UARTCOMMS_H)
#define CY_SCB_SPI_UART_UARTCOMMS_H

#include "UARTCOMMS.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define UARTCOMMS_SPI_MODE                   (0u)
#define UARTCOMMS_SPI_SUB_MODE               (0u)
#define UARTCOMMS_SPI_CLOCK_MODE             (0u)
#define UARTCOMMS_SPI_OVS_FACTOR             (16u)
#define UARTCOMMS_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define UARTCOMMS_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define UARTCOMMS_SPI_RX_DATA_BITS_NUM       (8u)
#define UARTCOMMS_SPI_TX_DATA_BITS_NUM       (8u)
#define UARTCOMMS_SPI_WAKE_ENABLE            (0u)
#define UARTCOMMS_SPI_BITS_ORDER             (1u)
#define UARTCOMMS_SPI_TRANSFER_SEPARATION    (1u)
#define UARTCOMMS_SPI_NUMBER_OF_SS_LINES     (1u)
#define UARTCOMMS_SPI_RX_BUFFER_SIZE         (8u)
#define UARTCOMMS_SPI_TX_BUFFER_SIZE         (8u)

#define UARTCOMMS_SPI_INTERRUPT_MODE         (0u)

#define UARTCOMMS_SPI_INTR_RX_MASK           (0u)
#define UARTCOMMS_SPI_INTR_TX_MASK           (0u)

#define UARTCOMMS_SPI_RX_TRIGGER_LEVEL       (7u)
#define UARTCOMMS_SPI_TX_TRIGGER_LEVEL       (0u)

#define UARTCOMMS_SPI_BYTE_MODE_ENABLE       (0u)
#define UARTCOMMS_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define UARTCOMMS_SPI_SS0_POLARITY           (0u)
#define UARTCOMMS_SPI_SS1_POLARITY           (0u)
#define UARTCOMMS_SPI_SS2_POLARITY           (0u)
#define UARTCOMMS_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define UARTCOMMS_UART_SUB_MODE              (0u)
#define UARTCOMMS_UART_DIRECTION             (3u)
#define UARTCOMMS_UART_DATA_BITS_NUM         (8u)
#define UARTCOMMS_UART_PARITY_TYPE           (2u)
#define UARTCOMMS_UART_STOP_BITS_NUM         (2u)
#define UARTCOMMS_UART_OVS_FACTOR            (12u)
#define UARTCOMMS_UART_IRDA_LOW_POWER        (0u)
#define UARTCOMMS_UART_MEDIAN_FILTER_ENABLE  (0u)
#define UARTCOMMS_UART_RETRY_ON_NACK         (0u)
#define UARTCOMMS_UART_IRDA_POLARITY         (0u)
#define UARTCOMMS_UART_DROP_ON_FRAME_ERR     (0u)
#define UARTCOMMS_UART_DROP_ON_PARITY_ERR    (0u)
#define UARTCOMMS_UART_WAKE_ENABLE           (0u)
#define UARTCOMMS_UART_RX_BUFFER_SIZE        (8u)
#define UARTCOMMS_UART_TX_BUFFER_SIZE        (256u)
#define UARTCOMMS_UART_MP_MODE_ENABLE        (0u)
#define UARTCOMMS_UART_MP_ACCEPT_ADDRESS     (0u)
#define UARTCOMMS_UART_MP_RX_ADDRESS         (2u)
#define UARTCOMMS_UART_MP_RX_ADDRESS_MASK    (255u)

#define UARTCOMMS_UART_INTERRUPT_MODE        (1u)

#define UARTCOMMS_UART_INTR_RX_MASK          (0u)
#define UARTCOMMS_UART_INTR_TX_MASK          (0u)

#define UARTCOMMS_UART_RX_TRIGGER_LEVEL      (7u)
#define UARTCOMMS_UART_TX_TRIGGER_LEVEL      (0u)

#define UARTCOMMS_UART_BYTE_MODE_ENABLE      (0u)
#define UARTCOMMS_UART_CTS_ENABLE            (0u)
#define UARTCOMMS_UART_CTS_POLARITY          (0u)
#define UARTCOMMS_UART_RTS_ENABLE            (0u)
#define UARTCOMMS_UART_RTS_POLARITY          (0u)
#define UARTCOMMS_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define UARTCOMMS_SPI_SLAVE  (0u)
#define UARTCOMMS_SPI_MASTER (1u)

/* UART direction enum */
#define UARTCOMMS_UART_RX    (1u)
#define UARTCOMMS_UART_TX    (2u)
#define UARTCOMMS_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define UARTCOMMS_SPI_SLAVE_CONST        (1u)
    #define UARTCOMMS_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define UARTCOMMS_RX_DIRECTION           (1u)
    #define UARTCOMMS_TX_DIRECTION           (1u)
    #define UARTCOMMS_UART_RX_DIRECTION      (1u)
    #define UARTCOMMS_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define UARTCOMMS_INTERNAL_RX_SW_BUFFER   (0u)
    #define UARTCOMMS_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define UARTCOMMS_INTERNAL_RX_BUFFER_SIZE    (UARTCOMMS_rxBufferSize + 1u)
    #define UARTCOMMS_RX_BUFFER_SIZE             (UARTCOMMS_rxBufferSize)
    #define UARTCOMMS_TX_BUFFER_SIZE             (UARTCOMMS_txBufferSize)

    /* Return true if buffer is provided */
    #define UARTCOMMS_CHECK_RX_SW_BUFFER (NULL != UARTCOMMS_rxBuffer)
    #define UARTCOMMS_CHECK_TX_SW_BUFFER (NULL != UARTCOMMS_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define UARTCOMMS_SPI_WAKE_ENABLE_CONST  (1u)
    #define UARTCOMMS_CHECK_SPI_WAKE_ENABLE  (0u != UARTCOMMS_scbEnableWake)
    #define UARTCOMMS_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
        #define UARTCOMMS_SPI_UART_FIFO_SIZE             (UARTCOMMS_FIFO_SIZE)
        #define UARTCOMMS_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define UARTCOMMS_SPI_UART_FIFO_SIZE (UARTCOMMS_GET_FIFO_SIZE(UARTCOMMS_CTRL_REG & \
                                                                                    UARTCOMMS_CTRL_BYTE_MODE))

        #define UARTCOMMS_CHECK_UART_RTS_CONTROL_FLOW \
                    ((UARTCOMMS_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != UARTCOMMS_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(UARTCOMMS_UART_FLOW_CTRL_REG)))
    #endif /* (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (UARTCOMMS_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define UARTCOMMS_SPI_RX_DIRECTION (1u)
        #define UARTCOMMS_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
            #define UARTCOMMS_SPI_UART_FIFO_SIZE    (UARTCOMMS_FIFO_SIZE)
        #else
            #define UARTCOMMS_SPI_UART_FIFO_SIZE \
                                           UARTCOMMS_GET_FIFO_SIZE(UARTCOMMS_SPI_BYTE_MODE_ENABLE)

        #endif /* (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define UARTCOMMS_INTERNAL_SPI_RX_SW_BUFFER  (UARTCOMMS_SPI_RX_BUFFER_SIZE > \
                                                                UARTCOMMS_SPI_UART_FIFO_SIZE)
        #define UARTCOMMS_INTERNAL_SPI_TX_SW_BUFFER  (UARTCOMMS_SPI_TX_BUFFER_SIZE > \
                                                                UARTCOMMS_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define UARTCOMMS_INTERNAL_RX_SW_BUFFER  (UARTCOMMS_INTERNAL_SPI_RX_SW_BUFFER)
        #define UARTCOMMS_INTERNAL_TX_SW_BUFFER  (UARTCOMMS_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define UARTCOMMS_INTERNAL_RX_BUFFER_SIZE    (UARTCOMMS_SPI_RX_BUFFER_SIZE + 1u)
        #define UARTCOMMS_RX_BUFFER_SIZE             (UARTCOMMS_SPI_RX_BUFFER_SIZE)
        #define UARTCOMMS_TX_BUFFER_SIZE             (UARTCOMMS_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define UARTCOMMS_SPI_WAKE_ENABLE_CONST  (0u != UARTCOMMS_SPI_WAKE_ENABLE)
        #define UARTCOMMS_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define UARTCOMMS_UART_RX_DIRECTION (0u != (UARTCOMMS_UART_DIRECTION & UARTCOMMS_UART_RX))
        #define UARTCOMMS_UART_TX_DIRECTION (0u != (UARTCOMMS_UART_DIRECTION & UARTCOMMS_UART_TX))

        /* Get FIFO size */
        #if (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
            #define UARTCOMMS_SPI_UART_FIFO_SIZE    (UARTCOMMS_FIFO_SIZE)
        #else
            #define UARTCOMMS_SPI_UART_FIFO_SIZE \
                                           UARTCOMMS_GET_FIFO_SIZE(UARTCOMMS_UART_BYTE_MODE_ENABLE)
        #endif /* (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define UARTCOMMS_INTERNAL_UART_RX_SW_BUFFER  (UARTCOMMS_UART_RX_BUFFER_SIZE > \
                                                                UARTCOMMS_SPI_UART_FIFO_SIZE)
        #define UARTCOMMS_INTERNAL_UART_TX_SW_BUFFER  (UARTCOMMS_UART_TX_BUFFER_SIZE > \
                                                                    UARTCOMMS_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define UARTCOMMS_INTERNAL_RX_SW_BUFFER  (UARTCOMMS_INTERNAL_UART_RX_SW_BUFFER)
        #define UARTCOMMS_INTERNAL_TX_SW_BUFFER  (UARTCOMMS_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define UARTCOMMS_INTERNAL_RX_BUFFER_SIZE    (UARTCOMMS_UART_RX_BUFFER_SIZE + 1u)
        #define UARTCOMMS_RX_BUFFER_SIZE             (UARTCOMMS_UART_RX_BUFFER_SIZE)
        #define UARTCOMMS_TX_BUFFER_SIZE             (UARTCOMMS_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define UARTCOMMS_SPI_WAKE_ENABLE_CONST  (0u)
        #define UARTCOMMS_UART_WAKE_ENABLE_CONST (0u != UARTCOMMS_UART_WAKE_ENABLE)

    #endif /* (UARTCOMMS_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define UARTCOMMS_SPI_SLAVE_CONST    (UARTCOMMS_SPI_MODE == UARTCOMMS_SPI_SLAVE)
    #define UARTCOMMS_SPI_MASTER_CONST   (UARTCOMMS_SPI_MODE == UARTCOMMS_SPI_MASTER)

    /* Direction */
    #define UARTCOMMS_RX_DIRECTION ((UARTCOMMS_SCB_MODE_SPI_CONST_CFG) ? \
                                            (UARTCOMMS_SPI_RX_DIRECTION) : (UARTCOMMS_UART_RX_DIRECTION))

    #define UARTCOMMS_TX_DIRECTION ((UARTCOMMS_SCB_MODE_SPI_CONST_CFG) ? \
                                            (UARTCOMMS_SPI_TX_DIRECTION) : (UARTCOMMS_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define UARTCOMMS_CHECK_RX_SW_BUFFER (UARTCOMMS_INTERNAL_RX_SW_BUFFER)
    #define UARTCOMMS_CHECK_TX_SW_BUFFER (UARTCOMMS_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST    (UARTCOMMS_INTERNAL_RX_SW_BUFFER)
    #define UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST    (UARTCOMMS_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define UARTCOMMS_CHECK_SPI_WAKE_ENABLE  (UARTCOMMS_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define UARTCOMMS_CHECK_UART_RTS_CONTROL_FLOW    (UARTCOMMS_SCB_MODE_UART_CONST_CFG && \
                                                             UARTCOMMS_UART_RTS_ENABLE)

#endif /* End (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* UARTCOMMS_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} UARTCOMMS_SPI_INIT_STRUCT;

/* UARTCOMMS_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} UARTCOMMS_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    void UARTCOMMS_SpiInit(const UARTCOMMS_SPI_INIT_STRUCT *config);
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(UARTCOMMS_SCB_MODE_SPI_INC)
    #define UARTCOMMS_SpiIsBusBusy() ((uint32) (0u != (UARTCOMMS_SPI_STATUS_REG & \
                                                              UARTCOMMS_SPI_STATUS_BUS_BUSY)))

    #if (UARTCOMMS_SPI_MASTER_CONST)
        void UARTCOMMS_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(UARTCOMMS_SPI_MASTER_CONST) */

    #if !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
        void UARTCOMMS_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */
#endif /* (UARTCOMMS_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    void UARTCOMMS_UartInit(const UARTCOMMS_UART_INIT_STRUCT *config);
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(UARTCOMMS_SCB_MODE_UART_INC)
    void UARTCOMMS_UartSetRxAddress(uint32 address);
    void UARTCOMMS_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(UARTCOMMS_UART_RX_DIRECTION)
        uint32 UARTCOMMS_UartGetChar(void);
        uint32 UARTCOMMS_UartGetByte(void);

        #if !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void UARTCOMMS_UartSetRtsPolarity(uint32 polarity);
            void UARTCOMMS_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */
    #endif /* (UARTCOMMS_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(UARTCOMMS_UART_TX_DIRECTION)
        #define UARTCOMMS_UartPutChar(ch)    UARTCOMMS_SpiUartWriteTxData((uint32)(ch))
        void UARTCOMMS_UartPutString(const char8 string[]);
        void UARTCOMMS_UartPutCRLF(uint32 txDataByte);

        #if !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void UARTCOMMS_UartEnableCts(void);
            void UARTCOMMS_UartDisableCts(void);
            void UARTCOMMS_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */
    #endif /* (UARTCOMMS_UART_TX_DIRECTION) */
#endif /* (UARTCOMMS_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(UARTCOMMS_RX_DIRECTION)
    uint32 UARTCOMMS_SpiUartReadRxData(void);
    uint32 UARTCOMMS_SpiUartGetRxBufferSize(void);
    void   UARTCOMMS_SpiUartClearRxBuffer(void);
#endif /* (UARTCOMMS_RX_DIRECTION) */

/* Common APIs TX direction */
#if(UARTCOMMS_TX_DIRECTION)
    void   UARTCOMMS_SpiUartWriteTxData(uint32 txData);
    void   UARTCOMMS_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 UARTCOMMS_SpiUartGetTxBufferSize(void);
    void   UARTCOMMS_SpiUartClearTxBuffer(void);
#endif /* (UARTCOMMS_TX_DIRECTION) */

CY_ISR_PROTO(UARTCOMMS_SPI_UART_ISR);

#if(UARTCOMMS_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(UARTCOMMS_UART_WAKEUP_ISR);
#endif /* (UARTCOMMS_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   UARTCOMMS_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 UARTCOMMS_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   UARTCOMMS_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 UARTCOMMS_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST)
        #define UARTCOMMS_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    UARTCOMMS_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define UARTCOMMS_GetWordFromRxBuffer(idx) UARTCOMMS_rxBufferInternal[(idx)]

    #endif /* (UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST)
        #define UARTCOMMS_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        UARTCOMMS_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define UARTCOMMS_GetWordFromTxBuffer(idx) UARTCOMMS_txBufferInternal[(idx)]

    #endif /* (UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (UARTCOMMS_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define UARTCOMMS_SPI_MODE_MOTOROLA      (0x00u)
#define UARTCOMMS_SPI_MODE_TI_COINCIDES  (0x01u)
#define UARTCOMMS_SPI_MODE_TI_PRECEDES   (0x11u)
#define UARTCOMMS_SPI_MODE_NATIONAL      (0x02u)
#define UARTCOMMS_SPI_MODE_MASK          (0x03u)
#define UARTCOMMS_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define UARTCOMMS_SPI_MODE_NS_MICROWIRE  (UARTCOMMS_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define UARTCOMMS_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define UARTCOMMS_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define UARTCOMMS_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define UARTCOMMS_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define UARTCOMMS_BITS_ORDER_LSB_FIRST   (0u)
#define UARTCOMMS_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define UARTCOMMS_SPI_TRANSFER_SEPARATED     (0u)
#define UARTCOMMS_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define UARTCOMMS_SPI_SLAVE_SELECT0    (UARTCOMMS_SCB__SS0_POSISTION)
#define UARTCOMMS_SPI_SLAVE_SELECT1    (UARTCOMMS_SCB__SS1_POSISTION)
#define UARTCOMMS_SPI_SLAVE_SELECT2    (UARTCOMMS_SCB__SS2_POSISTION)
#define UARTCOMMS_SPI_SLAVE_SELECT3    (UARTCOMMS_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define UARTCOMMS_SPI_SS_ACTIVE_LOW  (0u)
#define UARTCOMMS_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define UARTCOMMS_UART_MODE_STD          (0u)
#define UARTCOMMS_UART_MODE_SMARTCARD    (1u)
#define UARTCOMMS_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define UARTCOMMS_UART_RX    (1u)
#define UARTCOMMS_UART_TX    (2u)
#define UARTCOMMS_UART_TX_RX (3u)

/* UART parity enum */
#define UARTCOMMS_UART_PARITY_EVEN   (0u)
#define UARTCOMMS_UART_PARITY_ODD    (1u)
#define UARTCOMMS_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define UARTCOMMS_UART_STOP_BITS_1   (2u)
#define UARTCOMMS_UART_STOP_BITS_1_5 (3u)
#define UARTCOMMS_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define UARTCOMMS_UART_IRDA_LP_OVS16     (16u)
#define UARTCOMMS_UART_IRDA_LP_OVS32     (32u)
#define UARTCOMMS_UART_IRDA_LP_OVS48     (48u)
#define UARTCOMMS_UART_IRDA_LP_OVS96     (96u)
#define UARTCOMMS_UART_IRDA_LP_OVS192    (192u)
#define UARTCOMMS_UART_IRDA_LP_OVS768    (768u)
#define UARTCOMMS_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define UARTCOMMS_UART_MP_MARK       (0x100u)
#define UARTCOMMS_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define UARTCOMMS_UART_CTS_ACTIVE_LOW    (0u)
#define UARTCOMMS_UART_CTS_ACTIVE_HIGH   (1u)
#define UARTCOMMS_UART_RTS_ACTIVE_LOW    (0u)
#define UARTCOMMS_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define UARTCOMMS_INTR_RX_ERR        (UARTCOMMS_INTR_RX_OVERFLOW    | \
                                             UARTCOMMS_INTR_RX_UNDERFLOW   | \
                                             UARTCOMMS_INTR_RX_FRAME_ERROR | \
                                             UARTCOMMS_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for UARTCOMMS_UartGetByte() */
#define UARTCOMMS_UART_RX_OVERFLOW       (UARTCOMMS_INTR_RX_OVERFLOW << 8u)
#define UARTCOMMS_UART_RX_UNDERFLOW      (UARTCOMMS_INTR_RX_UNDERFLOW << 8u)
#define UARTCOMMS_UART_RX_FRAME_ERROR    (UARTCOMMS_INTR_RX_FRAME_ERROR << 8u)
#define UARTCOMMS_UART_RX_PARITY_ERROR   (UARTCOMMS_INTR_RX_PARITY_ERROR << 8u)
#define UARTCOMMS_UART_RX_ERROR_MASK     (UARTCOMMS_UART_RX_OVERFLOW    | \
                                                 UARTCOMMS_UART_RX_UNDERFLOW   | \
                                                 UARTCOMMS_UART_RX_FRAME_ERROR | \
                                                 UARTCOMMS_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const UARTCOMMS_SPI_INIT_STRUCT  UARTCOMMS_configSpi;
    extern const UARTCOMMS_UART_INIT_STRUCT UARTCOMMS_configUart;
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define UARTCOMMS_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & UARTCOMMS_INTR_SLAVE_SPI_BUS_ERROR)
#define UARTCOMMS_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & UARTCOMMS_INTR_MASTER_SPI_DONE)
#define UARTCOMMS_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~UARTCOMMS_INTR_SLAVE_SPI_BUS_ERROR)

#define UARTCOMMS_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~UARTCOMMS_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define UARTCOMMS_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((UARTCOMMS_UART_IRDA_LP_OVS16   == (oversample)) ? UARTCOMMS_CTRL_OVS_IRDA_LP_OVS16 : \
         ((UARTCOMMS_UART_IRDA_LP_OVS32   == (oversample)) ? UARTCOMMS_CTRL_OVS_IRDA_LP_OVS32 : \
          ((UARTCOMMS_UART_IRDA_LP_OVS48   == (oversample)) ? UARTCOMMS_CTRL_OVS_IRDA_LP_OVS48 : \
           ((UARTCOMMS_UART_IRDA_LP_OVS96   == (oversample)) ? UARTCOMMS_CTRL_OVS_IRDA_LP_OVS96 : \
            ((UARTCOMMS_UART_IRDA_LP_OVS192  == (oversample)) ? UARTCOMMS_CTRL_OVS_IRDA_LP_OVS192 : \
             ((UARTCOMMS_UART_IRDA_LP_OVS768  == (oversample)) ? UARTCOMMS_CTRL_OVS_IRDA_LP_OVS768 : \
              ((UARTCOMMS_UART_IRDA_LP_OVS1536 == (oversample)) ? UARTCOMMS_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          UARTCOMMS_CTRL_OVS_IRDA_LP_OVS16)))))))

#define UARTCOMMS_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (UARTCOMMS_UART_RX & (direction))) ? \
                                                                     (UARTCOMMS_RX_CTRL_ENABLED) : (0u))

#define UARTCOMMS_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (UARTCOMMS_UART_TX & (direction))) ? \
                                                                     (UARTCOMMS_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define UARTCOMMS_CTRL_SPI      (UARTCOMMS_CTRL_MODE_SPI)
#define UARTCOMMS_SPI_RX_CTRL   (UARTCOMMS_RX_CTRL_ENABLED)
#define UARTCOMMS_SPI_TX_CTRL   (UARTCOMMS_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define UARTCOMMS_SPI_SS_POLARITY \
             (((uint32) UARTCOMMS_SPI_SS0_POLARITY << UARTCOMMS_SPI_SLAVE_SELECT0) | \
              ((uint32) UARTCOMMS_SPI_SS1_POLARITY << UARTCOMMS_SPI_SLAVE_SELECT1) | \
              ((uint32) UARTCOMMS_SPI_SS2_POLARITY << UARTCOMMS_SPI_SLAVE_SELECT2) | \
              ((uint32) UARTCOMMS_SPI_SS3_POLARITY << UARTCOMMS_SPI_SLAVE_SELECT3))

#if(UARTCOMMS_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define UARTCOMMS_SPI_DEFAULT_CTRL \
                    (UARTCOMMS_GET_CTRL_OVS(UARTCOMMS_SPI_OVS_FACTOR) | \
                     UARTCOMMS_GET_CTRL_BYTE_MODE (UARTCOMMS_SPI_BYTE_MODE_ENABLE) | \
                     UARTCOMMS_GET_CTRL_EC_AM_MODE(UARTCOMMS_SPI_WAKE_ENABLE)      | \
                     UARTCOMMS_CTRL_SPI)

    #define UARTCOMMS_SPI_DEFAULT_SPI_CTRL \
                    (UARTCOMMS_GET_SPI_CTRL_CONTINUOUS    (UARTCOMMS_SPI_TRANSFER_SEPARATION)       | \
                     UARTCOMMS_GET_SPI_CTRL_SELECT_PRECEDE(UARTCOMMS_SPI_SUB_MODE &                   \
                                                                  UARTCOMMS_SPI_MODE_TI_PRECEDES_MASK)     | \
                     UARTCOMMS_GET_SPI_CTRL_SCLK_MODE     (UARTCOMMS_SPI_CLOCK_MODE)                | \
                     UARTCOMMS_GET_SPI_CTRL_LATE_MISO_SAMPLE(UARTCOMMS_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     UARTCOMMS_GET_SPI_CTRL_SCLK_CONTINUOUS(UARTCOMMS_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     UARTCOMMS_GET_SPI_CTRL_SSEL_POLARITY (UARTCOMMS_SPI_SS_POLARITY)               | \
                     UARTCOMMS_GET_SPI_CTRL_SUB_MODE      (UARTCOMMS_SPI_SUB_MODE)                  | \
                     UARTCOMMS_GET_SPI_CTRL_MASTER_MODE   (UARTCOMMS_SPI_MODE))

    /* RX direction */
    #define UARTCOMMS_SPI_DEFAULT_RX_CTRL \
                    (UARTCOMMS_GET_RX_CTRL_DATA_WIDTH(UARTCOMMS_SPI_RX_DATA_BITS_NUM)     | \
                     UARTCOMMS_GET_RX_CTRL_BIT_ORDER (UARTCOMMS_SPI_BITS_ORDER)           | \
                     UARTCOMMS_GET_RX_CTRL_MEDIAN    (UARTCOMMS_SPI_MEDIAN_FILTER_ENABLE) | \
                     UARTCOMMS_SPI_RX_CTRL)

    #define UARTCOMMS_SPI_DEFAULT_RX_FIFO_CTRL \
                    UARTCOMMS_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(UARTCOMMS_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define UARTCOMMS_SPI_DEFAULT_TX_CTRL \
                    (UARTCOMMS_GET_TX_CTRL_DATA_WIDTH(UARTCOMMS_SPI_TX_DATA_BITS_NUM) | \
                     UARTCOMMS_GET_TX_CTRL_BIT_ORDER (UARTCOMMS_SPI_BITS_ORDER)       | \
                     UARTCOMMS_SPI_TX_CTRL)

    #define UARTCOMMS_SPI_DEFAULT_TX_FIFO_CTRL \
                    UARTCOMMS_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(UARTCOMMS_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define UARTCOMMS_SPI_DEFAULT_INTR_SPI_EC_MASK   (UARTCOMMS_NO_INTR_SOURCES)

    #define UARTCOMMS_SPI_DEFAULT_INTR_I2C_EC_MASK   (UARTCOMMS_NO_INTR_SOURCES)
    #define UARTCOMMS_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (UARTCOMMS_SPI_INTR_RX_MASK & UARTCOMMS_INTR_SLAVE_SPI_BUS_ERROR)

    #define UARTCOMMS_SPI_DEFAULT_INTR_MASTER_MASK \
                    (UARTCOMMS_SPI_INTR_TX_MASK & UARTCOMMS_INTR_MASTER_SPI_DONE)

    #define UARTCOMMS_SPI_DEFAULT_INTR_RX_MASK \
                    (UARTCOMMS_SPI_INTR_RX_MASK & (uint32) ~UARTCOMMS_INTR_SLAVE_SPI_BUS_ERROR)

    #define UARTCOMMS_SPI_DEFAULT_INTR_TX_MASK \
                    (UARTCOMMS_SPI_INTR_TX_MASK & (uint32) ~UARTCOMMS_INTR_MASTER_SPI_DONE)

#endif /* (UARTCOMMS_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define UARTCOMMS_CTRL_UART      (UARTCOMMS_CTRL_MODE_UART)
#define UARTCOMMS_UART_RX_CTRL   (UARTCOMMS_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define UARTCOMMS_UART_TX_CTRL   (UARTCOMMS_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(UARTCOMMS_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(UARTCOMMS_UART_MODE_IRDA == UARTCOMMS_UART_SUB_MODE)

        #define UARTCOMMS_DEFAULT_CTRL_OVS   ((0u != UARTCOMMS_UART_IRDA_LOW_POWER) ?              \
                                (UARTCOMMS_UART_GET_CTRL_OVS_IRDA_LP(UARTCOMMS_UART_OVS_FACTOR)) : \
                                (UARTCOMMS_CTRL_OVS_IRDA_OVS16))

    #else

        #define UARTCOMMS_DEFAULT_CTRL_OVS   UARTCOMMS_GET_CTRL_OVS(UARTCOMMS_UART_OVS_FACTOR)

    #endif /* (UARTCOMMS_UART_MODE_IRDA == UARTCOMMS_UART_SUB_MODE) */

    #define UARTCOMMS_UART_DEFAULT_CTRL \
                                (UARTCOMMS_GET_CTRL_BYTE_MODE  (UARTCOMMS_UART_BYTE_MODE_ENABLE)  | \
                                 UARTCOMMS_GET_CTRL_ADDR_ACCEPT(UARTCOMMS_UART_MP_ACCEPT_ADDRESS) | \
                                 UARTCOMMS_DEFAULT_CTRL_OVS                                              | \
                                 UARTCOMMS_CTRL_UART)

    #define UARTCOMMS_UART_DEFAULT_UART_CTRL \
                                    (UARTCOMMS_GET_UART_CTRL_MODE(UARTCOMMS_UART_SUB_MODE))

    /* RX direction */
    #define UARTCOMMS_UART_DEFAULT_RX_CTRL_PARITY \
                                ((UARTCOMMS_UART_PARITY_NONE != UARTCOMMS_UART_PARITY_TYPE) ?      \
                                  (UARTCOMMS_GET_UART_RX_CTRL_PARITY(UARTCOMMS_UART_PARITY_TYPE) | \
                                   UARTCOMMS_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define UARTCOMMS_UART_DEFAULT_UART_RX_CTRL \
                    (UARTCOMMS_GET_UART_RX_CTRL_MODE(UARTCOMMS_UART_STOP_BITS_NUM)                    | \
                     UARTCOMMS_GET_UART_RX_CTRL_POLARITY(UARTCOMMS_UART_IRDA_POLARITY)                | \
                     UARTCOMMS_GET_UART_RX_CTRL_MP_MODE(UARTCOMMS_UART_MP_MODE_ENABLE)                | \
                     UARTCOMMS_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(UARTCOMMS_UART_DROP_ON_PARITY_ERR) | \
                     UARTCOMMS_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(UARTCOMMS_UART_DROP_ON_FRAME_ERR)   | \
                     UARTCOMMS_UART_DEFAULT_RX_CTRL_PARITY)

    #define UARTCOMMS_UART_DEFAULT_RX_CTRL \
                                (UARTCOMMS_GET_RX_CTRL_DATA_WIDTH(UARTCOMMS_UART_DATA_BITS_NUM)        | \
                                 UARTCOMMS_GET_RX_CTRL_MEDIAN    (UARTCOMMS_UART_MEDIAN_FILTER_ENABLE) | \
                                 UARTCOMMS_GET_UART_RX_CTRL_ENABLED(UARTCOMMS_UART_DIRECTION))

    #define UARTCOMMS_UART_DEFAULT_RX_FIFO_CTRL \
                                UARTCOMMS_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(UARTCOMMS_UART_RX_TRIGGER_LEVEL)

    #define UARTCOMMS_UART_DEFAULT_RX_MATCH_REG  ((0u != UARTCOMMS_UART_MP_MODE_ENABLE) ?          \
                                (UARTCOMMS_GET_RX_MATCH_ADDR(UARTCOMMS_UART_MP_RX_ADDRESS) | \
                                 UARTCOMMS_GET_RX_MATCH_MASK(UARTCOMMS_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define UARTCOMMS_UART_DEFAULT_TX_CTRL_PARITY (UARTCOMMS_UART_DEFAULT_RX_CTRL_PARITY)

    #define UARTCOMMS_UART_DEFAULT_UART_TX_CTRL \
                                (UARTCOMMS_GET_UART_TX_CTRL_MODE(UARTCOMMS_UART_STOP_BITS_NUM)       | \
                                 UARTCOMMS_GET_UART_TX_CTRL_RETRY_NACK(UARTCOMMS_UART_RETRY_ON_NACK) | \
                                 UARTCOMMS_UART_DEFAULT_TX_CTRL_PARITY)

    #define UARTCOMMS_UART_DEFAULT_TX_CTRL \
                                (UARTCOMMS_GET_TX_CTRL_DATA_WIDTH(UARTCOMMS_UART_DATA_BITS_NUM) | \
                                 UARTCOMMS_GET_UART_TX_CTRL_ENABLED(UARTCOMMS_UART_DIRECTION))

    #define UARTCOMMS_UART_DEFAULT_TX_FIFO_CTRL \
                                UARTCOMMS_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(UARTCOMMS_UART_TX_TRIGGER_LEVEL)

    #define UARTCOMMS_UART_DEFAULT_FLOW_CTRL \
                        (UARTCOMMS_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(UARTCOMMS_UART_RTS_FIFO_LEVEL) | \
                         UARTCOMMS_GET_UART_FLOW_CTRL_RTS_POLARITY (UARTCOMMS_UART_RTS_POLARITY)   | \
                         UARTCOMMS_GET_UART_FLOW_CTRL_CTS_POLARITY (UARTCOMMS_UART_CTS_POLARITY)   | \
                         UARTCOMMS_GET_UART_FLOW_CTRL_CTS_ENABLE   (UARTCOMMS_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define UARTCOMMS_UART_DEFAULT_INTR_I2C_EC_MASK  (UARTCOMMS_NO_INTR_SOURCES)
    #define UARTCOMMS_UART_DEFAULT_INTR_SPI_EC_MASK  (UARTCOMMS_NO_INTR_SOURCES)
    #define UARTCOMMS_UART_DEFAULT_INTR_SLAVE_MASK   (UARTCOMMS_NO_INTR_SOURCES)
    #define UARTCOMMS_UART_DEFAULT_INTR_MASTER_MASK  (UARTCOMMS_NO_INTR_SOURCES)
    #define UARTCOMMS_UART_DEFAULT_INTR_RX_MASK      (UARTCOMMS_UART_INTR_RX_MASK)
    #define UARTCOMMS_UART_DEFAULT_INTR_TX_MASK      (UARTCOMMS_UART_INTR_TX_MASK)

#endif /* (UARTCOMMS_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define UARTCOMMS_SPIM_ACTIVE_SS0    (UARTCOMMS_SPI_SLAVE_SELECT0)
#define UARTCOMMS_SPIM_ACTIVE_SS1    (UARTCOMMS_SPI_SLAVE_SELECT1)
#define UARTCOMMS_SPIM_ACTIVE_SS2    (UARTCOMMS_SPI_SLAVE_SELECT2)
#define UARTCOMMS_SPIM_ACTIVE_SS3    (UARTCOMMS_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_UARTCOMMS_H */


/* [] END OF FILE */
