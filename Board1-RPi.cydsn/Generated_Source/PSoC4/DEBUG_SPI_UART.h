/*******************************************************************************
* File Name: DEBUG_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_DEBUG_H)
#define CY_SCB_SPI_UART_DEBUG_H

#include "DEBUG.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define DEBUG_SPI_MODE                   (0u)
#define DEBUG_SPI_SUB_MODE               (0u)
#define DEBUG_SPI_CLOCK_MODE             (0u)
#define DEBUG_SPI_OVS_FACTOR             (16u)
#define DEBUG_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define DEBUG_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define DEBUG_SPI_RX_DATA_BITS_NUM       (8u)
#define DEBUG_SPI_TX_DATA_BITS_NUM       (8u)
#define DEBUG_SPI_WAKE_ENABLE            (0u)
#define DEBUG_SPI_BITS_ORDER             (1u)
#define DEBUG_SPI_TRANSFER_SEPARATION    (1u)
#define DEBUG_SPI_NUMBER_OF_SS_LINES     (1u)
#define DEBUG_SPI_RX_BUFFER_SIZE         (8u)
#define DEBUG_SPI_TX_BUFFER_SIZE         (8u)

#define DEBUG_SPI_INTERRUPT_MODE         (0u)

#define DEBUG_SPI_INTR_RX_MASK           (0u)
#define DEBUG_SPI_INTR_TX_MASK           (0u)

#define DEBUG_SPI_RX_TRIGGER_LEVEL       (7u)
#define DEBUG_SPI_TX_TRIGGER_LEVEL       (0u)

#define DEBUG_SPI_BYTE_MODE_ENABLE       (0u)
#define DEBUG_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define DEBUG_SPI_SS0_POLARITY           (0u)
#define DEBUG_SPI_SS1_POLARITY           (0u)
#define DEBUG_SPI_SS2_POLARITY           (0u)
#define DEBUG_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define DEBUG_UART_SUB_MODE              (0u)
#define DEBUG_UART_DIRECTION             (3u)
#define DEBUG_UART_DATA_BITS_NUM         (8u)
#define DEBUG_UART_PARITY_TYPE           (2u)
#define DEBUG_UART_STOP_BITS_NUM         (2u)
#define DEBUG_UART_OVS_FACTOR            (12u)
#define DEBUG_UART_IRDA_LOW_POWER        (0u)
#define DEBUG_UART_MEDIAN_FILTER_ENABLE  (0u)
#define DEBUG_UART_RETRY_ON_NACK         (0u)
#define DEBUG_UART_IRDA_POLARITY         (0u)
#define DEBUG_UART_DROP_ON_FRAME_ERR     (0u)
#define DEBUG_UART_DROP_ON_PARITY_ERR    (0u)
#define DEBUG_UART_WAKE_ENABLE           (0u)
#define DEBUG_UART_RX_BUFFER_SIZE        (8u)
#define DEBUG_UART_TX_BUFFER_SIZE        (8u)
#define DEBUG_UART_MP_MODE_ENABLE        (0u)
#define DEBUG_UART_MP_ACCEPT_ADDRESS     (0u)
#define DEBUG_UART_MP_RX_ADDRESS         (2u)
#define DEBUG_UART_MP_RX_ADDRESS_MASK    (255u)

#define DEBUG_UART_INTERRUPT_MODE        (0u)

#define DEBUG_UART_INTR_RX_MASK          (0u)
#define DEBUG_UART_INTR_TX_MASK          (0u)

#define DEBUG_UART_RX_TRIGGER_LEVEL      (7u)
#define DEBUG_UART_TX_TRIGGER_LEVEL      (0u)

#define DEBUG_UART_BYTE_MODE_ENABLE      (0u)
#define DEBUG_UART_CTS_ENABLE            (0u)
#define DEBUG_UART_CTS_POLARITY          (0u)
#define DEBUG_UART_RTS_ENABLE            (0u)
#define DEBUG_UART_RTS_POLARITY          (0u)
#define DEBUG_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define DEBUG_SPI_SLAVE  (0u)
#define DEBUG_SPI_MASTER (1u)

/* UART direction enum */
#define DEBUG_UART_RX    (1u)
#define DEBUG_UART_TX    (2u)
#define DEBUG_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define DEBUG_SPI_SLAVE_CONST        (1u)
    #define DEBUG_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define DEBUG_RX_DIRECTION           (1u)
    #define DEBUG_TX_DIRECTION           (1u)
    #define DEBUG_UART_RX_DIRECTION      (1u)
    #define DEBUG_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define DEBUG_INTERNAL_RX_SW_BUFFER   (0u)
    #define DEBUG_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define DEBUG_INTERNAL_RX_BUFFER_SIZE    (DEBUG_rxBufferSize + 1u)
    #define DEBUG_RX_BUFFER_SIZE             (DEBUG_rxBufferSize)
    #define DEBUG_TX_BUFFER_SIZE             (DEBUG_txBufferSize)

    /* Return true if buffer is provided */
    #define DEBUG_CHECK_RX_SW_BUFFER (NULL != DEBUG_rxBuffer)
    #define DEBUG_CHECK_TX_SW_BUFFER (NULL != DEBUG_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define DEBUG_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define DEBUG_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define DEBUG_SPI_WAKE_ENABLE_CONST  (1u)
    #define DEBUG_CHECK_SPI_WAKE_ENABLE  (0u != DEBUG_scbEnableWake)
    #define DEBUG_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
        #define DEBUG_SPI_UART_FIFO_SIZE             (DEBUG_FIFO_SIZE)
        #define DEBUG_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define DEBUG_SPI_UART_FIFO_SIZE (DEBUG_GET_FIFO_SIZE(DEBUG_CTRL_REG & \
                                                                                    DEBUG_CTRL_BYTE_MODE))

        #define DEBUG_CHECK_UART_RTS_CONTROL_FLOW \
                    ((DEBUG_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != DEBUG_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(DEBUG_UART_FLOW_CTRL_REG)))
    #endif /* (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (DEBUG_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define DEBUG_SPI_RX_DIRECTION (1u)
        #define DEBUG_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
            #define DEBUG_SPI_UART_FIFO_SIZE    (DEBUG_FIFO_SIZE)
        #else
            #define DEBUG_SPI_UART_FIFO_SIZE \
                                           DEBUG_GET_FIFO_SIZE(DEBUG_SPI_BYTE_MODE_ENABLE)

        #endif /* (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define DEBUG_INTERNAL_SPI_RX_SW_BUFFER  (DEBUG_SPI_RX_BUFFER_SIZE > \
                                                                DEBUG_SPI_UART_FIFO_SIZE)
        #define DEBUG_INTERNAL_SPI_TX_SW_BUFFER  (DEBUG_SPI_TX_BUFFER_SIZE > \
                                                                DEBUG_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define DEBUG_INTERNAL_RX_SW_BUFFER  (DEBUG_INTERNAL_SPI_RX_SW_BUFFER)
        #define DEBUG_INTERNAL_TX_SW_BUFFER  (DEBUG_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define DEBUG_INTERNAL_RX_BUFFER_SIZE    (DEBUG_SPI_RX_BUFFER_SIZE + 1u)
        #define DEBUG_RX_BUFFER_SIZE             (DEBUG_SPI_RX_BUFFER_SIZE)
        #define DEBUG_TX_BUFFER_SIZE             (DEBUG_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define DEBUG_SPI_WAKE_ENABLE_CONST  (0u != DEBUG_SPI_WAKE_ENABLE)
        #define DEBUG_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define DEBUG_UART_RX_DIRECTION (0u != (DEBUG_UART_DIRECTION & DEBUG_UART_RX))
        #define DEBUG_UART_TX_DIRECTION (0u != (DEBUG_UART_DIRECTION & DEBUG_UART_TX))

        /* Get FIFO size */
        #if (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
            #define DEBUG_SPI_UART_FIFO_SIZE    (DEBUG_FIFO_SIZE)
        #else
            #define DEBUG_SPI_UART_FIFO_SIZE \
                                           DEBUG_GET_FIFO_SIZE(DEBUG_UART_BYTE_MODE_ENABLE)
        #endif /* (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define DEBUG_INTERNAL_UART_RX_SW_BUFFER  (DEBUG_UART_RX_BUFFER_SIZE > \
                                                                DEBUG_SPI_UART_FIFO_SIZE)
        #define DEBUG_INTERNAL_UART_TX_SW_BUFFER  (DEBUG_UART_TX_BUFFER_SIZE > \
                                                                    DEBUG_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define DEBUG_INTERNAL_RX_SW_BUFFER  (DEBUG_INTERNAL_UART_RX_SW_BUFFER)
        #define DEBUG_INTERNAL_TX_SW_BUFFER  (DEBUG_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define DEBUG_INTERNAL_RX_BUFFER_SIZE    (DEBUG_UART_RX_BUFFER_SIZE + 1u)
        #define DEBUG_RX_BUFFER_SIZE             (DEBUG_UART_RX_BUFFER_SIZE)
        #define DEBUG_TX_BUFFER_SIZE             (DEBUG_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define DEBUG_SPI_WAKE_ENABLE_CONST  (0u)
        #define DEBUG_UART_WAKE_ENABLE_CONST (0u != DEBUG_UART_WAKE_ENABLE)

    #endif /* (DEBUG_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define DEBUG_SPI_SLAVE_CONST    (DEBUG_SPI_MODE == DEBUG_SPI_SLAVE)
    #define DEBUG_SPI_MASTER_CONST   (DEBUG_SPI_MODE == DEBUG_SPI_MASTER)

    /* Direction */
    #define DEBUG_RX_DIRECTION ((DEBUG_SCB_MODE_SPI_CONST_CFG) ? \
                                            (DEBUG_SPI_RX_DIRECTION) : (DEBUG_UART_RX_DIRECTION))

    #define DEBUG_TX_DIRECTION ((DEBUG_SCB_MODE_SPI_CONST_CFG) ? \
                                            (DEBUG_SPI_TX_DIRECTION) : (DEBUG_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define DEBUG_CHECK_RX_SW_BUFFER (DEBUG_INTERNAL_RX_SW_BUFFER)
    #define DEBUG_CHECK_TX_SW_BUFFER (DEBUG_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define DEBUG_INTERNAL_RX_SW_BUFFER_CONST    (DEBUG_INTERNAL_RX_SW_BUFFER)
    #define DEBUG_INTERNAL_TX_SW_BUFFER_CONST    (DEBUG_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define DEBUG_CHECK_SPI_WAKE_ENABLE  (DEBUG_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define DEBUG_CHECK_UART_RTS_CONTROL_FLOW    (DEBUG_SCB_MODE_UART_CONST_CFG && \
                                                             DEBUG_UART_RTS_ENABLE)

#endif /* End (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* DEBUG_SPI_INIT_STRUCT */
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
} DEBUG_SPI_INIT_STRUCT;

/* DEBUG_UART_INIT_STRUCT */
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
} DEBUG_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    void DEBUG_SpiInit(const DEBUG_SPI_INIT_STRUCT *config);
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(DEBUG_SCB_MODE_SPI_INC)
    #define DEBUG_SpiIsBusBusy() ((uint32) (0u != (DEBUG_SPI_STATUS_REG & \
                                                              DEBUG_SPI_STATUS_BUS_BUSY)))

    #if (DEBUG_SPI_MASTER_CONST)
        void DEBUG_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(DEBUG_SPI_MASTER_CONST) */

    #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
        void DEBUG_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */
#endif /* (DEBUG_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    void DEBUG_UartInit(const DEBUG_UART_INIT_STRUCT *config);
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(DEBUG_SCB_MODE_UART_INC)
    void DEBUG_UartSetRxAddress(uint32 address);
    void DEBUG_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(DEBUG_UART_RX_DIRECTION)
        uint32 DEBUG_UartGetChar(void);
        uint32 DEBUG_UartGetByte(void);

        #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void DEBUG_UartSetRtsPolarity(uint32 polarity);
            void DEBUG_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */
    #endif /* (DEBUG_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(DEBUG_UART_TX_DIRECTION)
        #define DEBUG_UartPutChar(ch)    DEBUG_SpiUartWriteTxData((uint32)(ch))
        void DEBUG_UartPutString(const char8 string[]);
        void DEBUG_UartPutCRLF(uint32 txDataByte);

        #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void DEBUG_UartEnableCts(void);
            void DEBUG_UartDisableCts(void);
            void DEBUG_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */
    #endif /* (DEBUG_UART_TX_DIRECTION) */
#endif /* (DEBUG_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(DEBUG_RX_DIRECTION)
    uint32 DEBUG_SpiUartReadRxData(void);
    uint32 DEBUG_SpiUartGetRxBufferSize(void);
    void   DEBUG_SpiUartClearRxBuffer(void);
#endif /* (DEBUG_RX_DIRECTION) */

/* Common APIs TX direction */
#if(DEBUG_TX_DIRECTION)
    void   DEBUG_SpiUartWriteTxData(uint32 txData);
    void   DEBUG_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 DEBUG_SpiUartGetTxBufferSize(void);
    void   DEBUG_SpiUartClearTxBuffer(void);
#endif /* (DEBUG_TX_DIRECTION) */

CY_ISR_PROTO(DEBUG_SPI_UART_ISR);

#if(DEBUG_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(DEBUG_UART_WAKEUP_ISR);
#endif /* (DEBUG_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   DEBUG_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 DEBUG_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   DEBUG_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 DEBUG_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(DEBUG_INTERNAL_RX_SW_BUFFER_CONST)
        #define DEBUG_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    DEBUG_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define DEBUG_GetWordFromRxBuffer(idx) DEBUG_rxBufferInternal[(idx)]

    #endif /* (DEBUG_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(DEBUG_INTERNAL_TX_SW_BUFFER_CONST)
        #define DEBUG_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        DEBUG_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define DEBUG_GetWordFromTxBuffer(idx) DEBUG_txBufferInternal[(idx)]

    #endif /* (DEBUG_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (DEBUG_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define DEBUG_SPI_MODE_MOTOROLA      (0x00u)
#define DEBUG_SPI_MODE_TI_COINCIDES  (0x01u)
#define DEBUG_SPI_MODE_TI_PRECEDES   (0x11u)
#define DEBUG_SPI_MODE_NATIONAL      (0x02u)
#define DEBUG_SPI_MODE_MASK          (0x03u)
#define DEBUG_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define DEBUG_SPI_MODE_NS_MICROWIRE  (DEBUG_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define DEBUG_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define DEBUG_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define DEBUG_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define DEBUG_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define DEBUG_BITS_ORDER_LSB_FIRST   (0u)
#define DEBUG_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define DEBUG_SPI_TRANSFER_SEPARATED     (0u)
#define DEBUG_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define DEBUG_SPI_SLAVE_SELECT0    (DEBUG_SCB__SS0_POSISTION)
#define DEBUG_SPI_SLAVE_SELECT1    (DEBUG_SCB__SS1_POSISTION)
#define DEBUG_SPI_SLAVE_SELECT2    (DEBUG_SCB__SS2_POSISTION)
#define DEBUG_SPI_SLAVE_SELECT3    (DEBUG_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define DEBUG_SPI_SS_ACTIVE_LOW  (0u)
#define DEBUG_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define DEBUG_UART_MODE_STD          (0u)
#define DEBUG_UART_MODE_SMARTCARD    (1u)
#define DEBUG_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define DEBUG_UART_RX    (1u)
#define DEBUG_UART_TX    (2u)
#define DEBUG_UART_TX_RX (3u)

/* UART parity enum */
#define DEBUG_UART_PARITY_EVEN   (0u)
#define DEBUG_UART_PARITY_ODD    (1u)
#define DEBUG_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define DEBUG_UART_STOP_BITS_1   (2u)
#define DEBUG_UART_STOP_BITS_1_5 (3u)
#define DEBUG_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define DEBUG_UART_IRDA_LP_OVS16     (16u)
#define DEBUG_UART_IRDA_LP_OVS32     (32u)
#define DEBUG_UART_IRDA_LP_OVS48     (48u)
#define DEBUG_UART_IRDA_LP_OVS96     (96u)
#define DEBUG_UART_IRDA_LP_OVS192    (192u)
#define DEBUG_UART_IRDA_LP_OVS768    (768u)
#define DEBUG_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define DEBUG_UART_MP_MARK       (0x100u)
#define DEBUG_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define DEBUG_UART_CTS_ACTIVE_LOW    (0u)
#define DEBUG_UART_CTS_ACTIVE_HIGH   (1u)
#define DEBUG_UART_RTS_ACTIVE_LOW    (0u)
#define DEBUG_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define DEBUG_INTR_RX_ERR        (DEBUG_INTR_RX_OVERFLOW    | \
                                             DEBUG_INTR_RX_UNDERFLOW   | \
                                             DEBUG_INTR_RX_FRAME_ERROR | \
                                             DEBUG_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for DEBUG_UartGetByte() */
#define DEBUG_UART_RX_OVERFLOW       (DEBUG_INTR_RX_OVERFLOW << 8u)
#define DEBUG_UART_RX_UNDERFLOW      (DEBUG_INTR_RX_UNDERFLOW << 8u)
#define DEBUG_UART_RX_FRAME_ERROR    (DEBUG_INTR_RX_FRAME_ERROR << 8u)
#define DEBUG_UART_RX_PARITY_ERROR   (DEBUG_INTR_RX_PARITY_ERROR << 8u)
#define DEBUG_UART_RX_ERROR_MASK     (DEBUG_UART_RX_OVERFLOW    | \
                                                 DEBUG_UART_RX_UNDERFLOW   | \
                                                 DEBUG_UART_RX_FRAME_ERROR | \
                                                 DEBUG_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const DEBUG_SPI_INIT_STRUCT  DEBUG_configSpi;
    extern const DEBUG_UART_INIT_STRUCT DEBUG_configUart;
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define DEBUG_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & DEBUG_INTR_SLAVE_SPI_BUS_ERROR)
#define DEBUG_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & DEBUG_INTR_MASTER_SPI_DONE)
#define DEBUG_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~DEBUG_INTR_SLAVE_SPI_BUS_ERROR)

#define DEBUG_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~DEBUG_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define DEBUG_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((DEBUG_UART_IRDA_LP_OVS16   == (oversample)) ? DEBUG_CTRL_OVS_IRDA_LP_OVS16 : \
         ((DEBUG_UART_IRDA_LP_OVS32   == (oversample)) ? DEBUG_CTRL_OVS_IRDA_LP_OVS32 : \
          ((DEBUG_UART_IRDA_LP_OVS48   == (oversample)) ? DEBUG_CTRL_OVS_IRDA_LP_OVS48 : \
           ((DEBUG_UART_IRDA_LP_OVS96   == (oversample)) ? DEBUG_CTRL_OVS_IRDA_LP_OVS96 : \
            ((DEBUG_UART_IRDA_LP_OVS192  == (oversample)) ? DEBUG_CTRL_OVS_IRDA_LP_OVS192 : \
             ((DEBUG_UART_IRDA_LP_OVS768  == (oversample)) ? DEBUG_CTRL_OVS_IRDA_LP_OVS768 : \
              ((DEBUG_UART_IRDA_LP_OVS1536 == (oversample)) ? DEBUG_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          DEBUG_CTRL_OVS_IRDA_LP_OVS16)))))))

#define DEBUG_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (DEBUG_UART_RX & (direction))) ? \
                                                                     (DEBUG_RX_CTRL_ENABLED) : (0u))

#define DEBUG_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (DEBUG_UART_TX & (direction))) ? \
                                                                     (DEBUG_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define DEBUG_CTRL_SPI      (DEBUG_CTRL_MODE_SPI)
#define DEBUG_SPI_RX_CTRL   (DEBUG_RX_CTRL_ENABLED)
#define DEBUG_SPI_TX_CTRL   (DEBUG_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define DEBUG_SPI_SS_POLARITY \
             (((uint32) DEBUG_SPI_SS0_POLARITY << DEBUG_SPI_SLAVE_SELECT0) | \
              ((uint32) DEBUG_SPI_SS1_POLARITY << DEBUG_SPI_SLAVE_SELECT1) | \
              ((uint32) DEBUG_SPI_SS2_POLARITY << DEBUG_SPI_SLAVE_SELECT2) | \
              ((uint32) DEBUG_SPI_SS3_POLARITY << DEBUG_SPI_SLAVE_SELECT3))

#if(DEBUG_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define DEBUG_SPI_DEFAULT_CTRL \
                    (DEBUG_GET_CTRL_OVS(DEBUG_SPI_OVS_FACTOR) | \
                     DEBUG_GET_CTRL_BYTE_MODE (DEBUG_SPI_BYTE_MODE_ENABLE) | \
                     DEBUG_GET_CTRL_EC_AM_MODE(DEBUG_SPI_WAKE_ENABLE)      | \
                     DEBUG_CTRL_SPI)

    #define DEBUG_SPI_DEFAULT_SPI_CTRL \
                    (DEBUG_GET_SPI_CTRL_CONTINUOUS    (DEBUG_SPI_TRANSFER_SEPARATION)       | \
                     DEBUG_GET_SPI_CTRL_SELECT_PRECEDE(DEBUG_SPI_SUB_MODE &                   \
                                                                  DEBUG_SPI_MODE_TI_PRECEDES_MASK)     | \
                     DEBUG_GET_SPI_CTRL_SCLK_MODE     (DEBUG_SPI_CLOCK_MODE)                | \
                     DEBUG_GET_SPI_CTRL_LATE_MISO_SAMPLE(DEBUG_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     DEBUG_GET_SPI_CTRL_SCLK_CONTINUOUS(DEBUG_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     DEBUG_GET_SPI_CTRL_SSEL_POLARITY (DEBUG_SPI_SS_POLARITY)               | \
                     DEBUG_GET_SPI_CTRL_SUB_MODE      (DEBUG_SPI_SUB_MODE)                  | \
                     DEBUG_GET_SPI_CTRL_MASTER_MODE   (DEBUG_SPI_MODE))

    /* RX direction */
    #define DEBUG_SPI_DEFAULT_RX_CTRL \
                    (DEBUG_GET_RX_CTRL_DATA_WIDTH(DEBUG_SPI_RX_DATA_BITS_NUM)     | \
                     DEBUG_GET_RX_CTRL_BIT_ORDER (DEBUG_SPI_BITS_ORDER)           | \
                     DEBUG_GET_RX_CTRL_MEDIAN    (DEBUG_SPI_MEDIAN_FILTER_ENABLE) | \
                     DEBUG_SPI_RX_CTRL)

    #define DEBUG_SPI_DEFAULT_RX_FIFO_CTRL \
                    DEBUG_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(DEBUG_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define DEBUG_SPI_DEFAULT_TX_CTRL \
                    (DEBUG_GET_TX_CTRL_DATA_WIDTH(DEBUG_SPI_TX_DATA_BITS_NUM) | \
                     DEBUG_GET_TX_CTRL_BIT_ORDER (DEBUG_SPI_BITS_ORDER)       | \
                     DEBUG_SPI_TX_CTRL)

    #define DEBUG_SPI_DEFAULT_TX_FIFO_CTRL \
                    DEBUG_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(DEBUG_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define DEBUG_SPI_DEFAULT_INTR_SPI_EC_MASK   (DEBUG_NO_INTR_SOURCES)

    #define DEBUG_SPI_DEFAULT_INTR_I2C_EC_MASK   (DEBUG_NO_INTR_SOURCES)
    #define DEBUG_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (DEBUG_SPI_INTR_RX_MASK & DEBUG_INTR_SLAVE_SPI_BUS_ERROR)

    #define DEBUG_SPI_DEFAULT_INTR_MASTER_MASK \
                    (DEBUG_SPI_INTR_TX_MASK & DEBUG_INTR_MASTER_SPI_DONE)

    #define DEBUG_SPI_DEFAULT_INTR_RX_MASK \
                    (DEBUG_SPI_INTR_RX_MASK & (uint32) ~DEBUG_INTR_SLAVE_SPI_BUS_ERROR)

    #define DEBUG_SPI_DEFAULT_INTR_TX_MASK \
                    (DEBUG_SPI_INTR_TX_MASK & (uint32) ~DEBUG_INTR_MASTER_SPI_DONE)

#endif /* (DEBUG_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define DEBUG_CTRL_UART      (DEBUG_CTRL_MODE_UART)
#define DEBUG_UART_RX_CTRL   (DEBUG_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define DEBUG_UART_TX_CTRL   (DEBUG_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(DEBUG_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(DEBUG_UART_MODE_IRDA == DEBUG_UART_SUB_MODE)

        #define DEBUG_DEFAULT_CTRL_OVS   ((0u != DEBUG_UART_IRDA_LOW_POWER) ?              \
                                (DEBUG_UART_GET_CTRL_OVS_IRDA_LP(DEBUG_UART_OVS_FACTOR)) : \
                                (DEBUG_CTRL_OVS_IRDA_OVS16))

    #else

        #define DEBUG_DEFAULT_CTRL_OVS   DEBUG_GET_CTRL_OVS(DEBUG_UART_OVS_FACTOR)

    #endif /* (DEBUG_UART_MODE_IRDA == DEBUG_UART_SUB_MODE) */

    #define DEBUG_UART_DEFAULT_CTRL \
                                (DEBUG_GET_CTRL_BYTE_MODE  (DEBUG_UART_BYTE_MODE_ENABLE)  | \
                                 DEBUG_GET_CTRL_ADDR_ACCEPT(DEBUG_UART_MP_ACCEPT_ADDRESS) | \
                                 DEBUG_DEFAULT_CTRL_OVS                                              | \
                                 DEBUG_CTRL_UART)

    #define DEBUG_UART_DEFAULT_UART_CTRL \
                                    (DEBUG_GET_UART_CTRL_MODE(DEBUG_UART_SUB_MODE))

    /* RX direction */
    #define DEBUG_UART_DEFAULT_RX_CTRL_PARITY \
                                ((DEBUG_UART_PARITY_NONE != DEBUG_UART_PARITY_TYPE) ?      \
                                  (DEBUG_GET_UART_RX_CTRL_PARITY(DEBUG_UART_PARITY_TYPE) | \
                                   DEBUG_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define DEBUG_UART_DEFAULT_UART_RX_CTRL \
                    (DEBUG_GET_UART_RX_CTRL_MODE(DEBUG_UART_STOP_BITS_NUM)                    | \
                     DEBUG_GET_UART_RX_CTRL_POLARITY(DEBUG_UART_IRDA_POLARITY)                | \
                     DEBUG_GET_UART_RX_CTRL_MP_MODE(DEBUG_UART_MP_MODE_ENABLE)                | \
                     DEBUG_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(DEBUG_UART_DROP_ON_PARITY_ERR) | \
                     DEBUG_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(DEBUG_UART_DROP_ON_FRAME_ERR)   | \
                     DEBUG_UART_DEFAULT_RX_CTRL_PARITY)

    #define DEBUG_UART_DEFAULT_RX_CTRL \
                                (DEBUG_GET_RX_CTRL_DATA_WIDTH(DEBUG_UART_DATA_BITS_NUM)        | \
                                 DEBUG_GET_RX_CTRL_MEDIAN    (DEBUG_UART_MEDIAN_FILTER_ENABLE) | \
                                 DEBUG_GET_UART_RX_CTRL_ENABLED(DEBUG_UART_DIRECTION))

    #define DEBUG_UART_DEFAULT_RX_FIFO_CTRL \
                                DEBUG_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(DEBUG_UART_RX_TRIGGER_LEVEL)

    #define DEBUG_UART_DEFAULT_RX_MATCH_REG  ((0u != DEBUG_UART_MP_MODE_ENABLE) ?          \
                                (DEBUG_GET_RX_MATCH_ADDR(DEBUG_UART_MP_RX_ADDRESS) | \
                                 DEBUG_GET_RX_MATCH_MASK(DEBUG_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define DEBUG_UART_DEFAULT_TX_CTRL_PARITY (DEBUG_UART_DEFAULT_RX_CTRL_PARITY)

    #define DEBUG_UART_DEFAULT_UART_TX_CTRL \
                                (DEBUG_GET_UART_TX_CTRL_MODE(DEBUG_UART_STOP_BITS_NUM)       | \
                                 DEBUG_GET_UART_TX_CTRL_RETRY_NACK(DEBUG_UART_RETRY_ON_NACK) | \
                                 DEBUG_UART_DEFAULT_TX_CTRL_PARITY)

    #define DEBUG_UART_DEFAULT_TX_CTRL \
                                (DEBUG_GET_TX_CTRL_DATA_WIDTH(DEBUG_UART_DATA_BITS_NUM) | \
                                 DEBUG_GET_UART_TX_CTRL_ENABLED(DEBUG_UART_DIRECTION))

    #define DEBUG_UART_DEFAULT_TX_FIFO_CTRL \
                                DEBUG_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(DEBUG_UART_TX_TRIGGER_LEVEL)

    #define DEBUG_UART_DEFAULT_FLOW_CTRL \
                        (DEBUG_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(DEBUG_UART_RTS_FIFO_LEVEL) | \
                         DEBUG_GET_UART_FLOW_CTRL_RTS_POLARITY (DEBUG_UART_RTS_POLARITY)   | \
                         DEBUG_GET_UART_FLOW_CTRL_CTS_POLARITY (DEBUG_UART_CTS_POLARITY)   | \
                         DEBUG_GET_UART_FLOW_CTRL_CTS_ENABLE   (DEBUG_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define DEBUG_UART_DEFAULT_INTR_I2C_EC_MASK  (DEBUG_NO_INTR_SOURCES)
    #define DEBUG_UART_DEFAULT_INTR_SPI_EC_MASK  (DEBUG_NO_INTR_SOURCES)
    #define DEBUG_UART_DEFAULT_INTR_SLAVE_MASK   (DEBUG_NO_INTR_SOURCES)
    #define DEBUG_UART_DEFAULT_INTR_MASTER_MASK  (DEBUG_NO_INTR_SOURCES)
    #define DEBUG_UART_DEFAULT_INTR_RX_MASK      (DEBUG_UART_INTR_RX_MASK)
    #define DEBUG_UART_DEFAULT_INTR_TX_MASK      (DEBUG_UART_INTR_TX_MASK)

#endif /* (DEBUG_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define DEBUG_SPIM_ACTIVE_SS0    (DEBUG_SPI_SLAVE_SELECT0)
#define DEBUG_SPIM_ACTIVE_SS1    (DEBUG_SPI_SLAVE_SELECT1)
#define DEBUG_SPIM_ACTIVE_SS2    (DEBUG_SPI_SLAVE_SELECT2)
#define DEBUG_SPIM_ACTIVE_SS3    (DEBUG_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_DEBUG_H */


/* [] END OF FILE */
