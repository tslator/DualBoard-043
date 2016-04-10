/*******************************************************************************
* File Name: DEBUG_UART.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUG_PVT.h"
#include "DEBUG_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const DEBUG_UART_INIT_STRUCT DEBUG_configUart =
    {
        DEBUG_UART_SUB_MODE,
        DEBUG_UART_DIRECTION,
        DEBUG_UART_DATA_BITS_NUM,
        DEBUG_UART_PARITY_TYPE,
        DEBUG_UART_STOP_BITS_NUM,
        DEBUG_UART_OVS_FACTOR,
        DEBUG_UART_IRDA_LOW_POWER,
        DEBUG_UART_MEDIAN_FILTER_ENABLE,
        DEBUG_UART_RETRY_ON_NACK,
        DEBUG_UART_IRDA_POLARITY,
        DEBUG_UART_DROP_ON_PARITY_ERR,
        DEBUG_UART_DROP_ON_FRAME_ERR,
        DEBUG_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        DEBUG_UART_MP_MODE_ENABLE,
        DEBUG_UART_MP_ACCEPT_ADDRESS,
        DEBUG_UART_MP_RX_ADDRESS,
        DEBUG_UART_MP_RX_ADDRESS_MASK,
        (uint32) DEBUG_SCB_IRQ_INTERNAL,
        DEBUG_UART_INTR_RX_MASK,
        DEBUG_UART_RX_TRIGGER_LEVEL,
        DEBUG_UART_INTR_TX_MASK,
        DEBUG_UART_TX_TRIGGER_LEVEL,
        (uint8) DEBUG_UART_BYTE_MODE_ENABLE,
        (uint8) DEBUG_UART_CTS_ENABLE,
        (uint8) DEBUG_UART_CTS_POLARITY,
        (uint8) DEBUG_UART_RTS_POLARITY,
        (uint8) DEBUG_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: DEBUG_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DEBUG_UartInit(const DEBUG_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (DEBUG_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (DEBUG_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

            /* Configure pins */
            DEBUG_SetPins(DEBUG_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            DEBUG_scbMode       = (uint8) DEBUG_SCB_MODE_UART;
            DEBUG_scbEnableWake = (uint8) config->enableWake;
            DEBUG_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            DEBUG_rxBuffer      =         config->rxBuffer;
            DEBUG_rxDataBits    = (uint8) config->dataBits;
            DEBUG_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            DEBUG_txBuffer      =         config->txBuffer;
            DEBUG_txDataBits    = (uint8) config->dataBits;
            DEBUG_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(DEBUG_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                DEBUG_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (DEBUG_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (DEBUG_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                DEBUG_CTRL_REG  = DEBUG_GET_CTRL_OVS(config->oversample);
            }

            DEBUG_CTRL_REG     |= DEBUG_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             DEBUG_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             DEBUG_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            DEBUG_UART_CTRL_REG = DEBUG_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            DEBUG_UART_RX_CTRL_REG = DEBUG_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        DEBUG_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        DEBUG_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        DEBUG_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        DEBUG_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(DEBUG_UART_PARITY_NONE != config->parity)
            {
               DEBUG_UART_RX_CTRL_REG |= DEBUG_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    DEBUG_UART_RX_CTRL_PARITY_ENABLED;
            }

            DEBUG_RX_CTRL_REG      = DEBUG_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                DEBUG_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                DEBUG_GET_UART_RX_CTRL_ENABLED(config->direction);

            DEBUG_RX_FIFO_CTRL_REG = DEBUG_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            DEBUG_RX_MATCH_REG     = DEBUG_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                DEBUG_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            DEBUG_UART_TX_CTRL_REG = DEBUG_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                DEBUG_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(DEBUG_UART_PARITY_NONE != config->parity)
            {
               DEBUG_UART_TX_CTRL_REG |= DEBUG_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    DEBUG_UART_TX_CTRL_PARITY_ENABLED;
            }

            DEBUG_TX_CTRL_REG      = DEBUG_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                DEBUG_GET_UART_TX_CTRL_ENABLED(config->direction);

            DEBUG_TX_FIFO_CTRL_REG = DEBUG_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
            DEBUG_UART_FLOW_CTRL_REG = DEBUG_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            DEBUG_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            DEBUG_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            DEBUG_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (DEBUG_ISR_NUMBER);
            CyIntSetPriority(DEBUG_ISR_NUMBER, DEBUG_ISR_PRIORITY);
            (void) CyIntSetVector(DEBUG_ISR_NUMBER, &DEBUG_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(DEBUG_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (DEBUG_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(DEBUG_RX_WAKE_ISR_NUMBER, DEBUG_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(DEBUG_RX_WAKE_ISR_NUMBER, &DEBUG_UART_WAKEUP_ISR);
        #endif /* (DEBUG_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            DEBUG_INTR_I2C_EC_MASK_REG = DEBUG_NO_INTR_SOURCES;
            DEBUG_INTR_SPI_EC_MASK_REG = DEBUG_NO_INTR_SOURCES;
            DEBUG_INTR_SLAVE_MASK_REG  = DEBUG_NO_INTR_SOURCES;
            DEBUG_INTR_MASTER_MASK_REG = DEBUG_NO_INTR_SOURCES;
            DEBUG_INTR_RX_MASK_REG     = config->rxInterruptMask;
            DEBUG_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            DEBUG_rxBufferHead     = 0u;
            DEBUG_rxBufferTail     = 0u;
            DEBUG_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            DEBUG_txBufferHead = 0u;
            DEBUG_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: DEBUG_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DEBUG_UartInit(void)
    {
        /* Configure UART interface */
        DEBUG_CTRL_REG = DEBUG_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        DEBUG_UART_CTRL_REG = DEBUG_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        DEBUG_UART_RX_CTRL_REG = DEBUG_UART_DEFAULT_UART_RX_CTRL;
        DEBUG_RX_CTRL_REG      = DEBUG_UART_DEFAULT_RX_CTRL;
        DEBUG_RX_FIFO_CTRL_REG = DEBUG_UART_DEFAULT_RX_FIFO_CTRL;
        DEBUG_RX_MATCH_REG     = DEBUG_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        DEBUG_UART_TX_CTRL_REG = DEBUG_UART_DEFAULT_UART_TX_CTRL;
        DEBUG_TX_CTRL_REG      = DEBUG_UART_DEFAULT_TX_CTRL;
        DEBUG_TX_FIFO_CTRL_REG = DEBUG_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
        DEBUG_UART_FLOW_CTRL_REG = DEBUG_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(DEBUG_SCB_IRQ_INTERNAL)
        CyIntDisable    (DEBUG_ISR_NUMBER);
        CyIntSetPriority(DEBUG_ISR_NUMBER, DEBUG_ISR_PRIORITY);
        (void) CyIntSetVector(DEBUG_ISR_NUMBER, &DEBUG_SPI_UART_ISR);
    #endif /* (DEBUG_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(DEBUG_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (DEBUG_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(DEBUG_RX_WAKE_ISR_NUMBER, DEBUG_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(DEBUG_RX_WAKE_ISR_NUMBER, &DEBUG_UART_WAKEUP_ISR);
    #endif /* (DEBUG_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        DEBUG_INTR_I2C_EC_MASK_REG = DEBUG_UART_DEFAULT_INTR_I2C_EC_MASK;
        DEBUG_INTR_SPI_EC_MASK_REG = DEBUG_UART_DEFAULT_INTR_SPI_EC_MASK;
        DEBUG_INTR_SLAVE_MASK_REG  = DEBUG_UART_DEFAULT_INTR_SLAVE_MASK;
        DEBUG_INTR_MASTER_MASK_REG = DEBUG_UART_DEFAULT_INTR_MASTER_MASK;
        DEBUG_INTR_RX_MASK_REG     = DEBUG_UART_DEFAULT_INTR_RX_MASK;
        DEBUG_INTR_TX_MASK_REG     = DEBUG_UART_DEFAULT_INTR_TX_MASK;

    #if(DEBUG_INTERNAL_RX_SW_BUFFER_CONST)
        DEBUG_rxBufferHead     = 0u;
        DEBUG_rxBufferTail     = 0u;
        DEBUG_rxBufferOverflow = 0u;
    #endif /* (DEBUG_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(DEBUG_INTERNAL_TX_SW_BUFFER_CONST)
        DEBUG_txBufferHead = 0u;
        DEBUG_txBufferTail = 0u;
    #endif /* (DEBUG_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: DEBUG_UartPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be 
*  controlled by the SCB UART.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DEBUG_UartPostEnable(void)
{
#if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)

#if (DEBUG_TX_SDA_MISO_PIN)
    if (DEBUG_CHECK_TX_SDA_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        DEBUG_SET_HSIOM_SEL(DEBUG_TX_SDA_MISO_HSIOM_REG, DEBUG_TX_SDA_MISO_HSIOM_MASK,
                                       DEBUG_TX_SDA_MISO_HSIOM_POS, DEBUG_HSIOM_UART_SEL);
    }
#endif /* (DEBUG_TX_SDA_MISO_PIN_PIN) */

#if (DEBUG_RTS_SS0_PIN)
    if (DEBUG_CHECK_RTS_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        DEBUG_SET_HSIOM_SEL(DEBUG_RTS_SS0_HSIOM_REG, DEBUG_RTS_SS0_HSIOM_MASK,
                                       DEBUG_RTS_SS0_HSIOM_POS, DEBUG_HSIOM_UART_SEL);
    }
#endif /* (DEBUG_RTS_SS0_PIN) */

#else
#if (DEBUG_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    DEBUG_SET_HSIOM_SEL(DEBUG_TX_HSIOM_REG, DEBUG_TX_HSIOM_MASK,
                                   DEBUG_TX_HSIOM_POS, DEBUG_HSIOM_UART_SEL);
#endif /* (DEBUG_UART_TX_PIN) */

#if (DEBUG_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    DEBUG_SET_HSIOM_SEL(DEBUG_RTS_HSIOM_REG, DEBUG_RTS_HSIOM_MASK,
                                   DEBUG_RTS_HSIOM_POS, DEBUG_HSIOM_UART_SEL);
#endif /* (DEBUG_UART_RTS_PIN) */

#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DEBUG_UartStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature to
*  not cause it to trigger after the component is enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DEBUG_UartStop(void)
{
#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (DEBUG_TX_SDA_MISO_PIN)
        if (DEBUG_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            DEBUG_SET_HSIOM_SEL(DEBUG_TX_SDA_MISO_HSIOM_REG, DEBUG_TX_SDA_MISO_HSIOM_MASK,
                                           DEBUG_TX_SDA_MISO_HSIOM_POS, DEBUG_HSIOM_GPIO_SEL);
        }
    #endif /* (DEBUG_TX_SDA_MISO_PIN_PIN) */

    #if (DEBUG_RTS_SS0_PIN)
        if (DEBUG_CHECK_RTS_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            DEBUG_uart_rts_spi_ss0_Write(DEBUG_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            DEBUG_SET_HSIOM_SEL(DEBUG_RTS_SS0_HSIOM_REG, DEBUG_RTS_SS0_HSIOM_MASK,
                                           DEBUG_RTS_SS0_HSIOM_POS, DEBUG_HSIOM_GPIO_SEL);
        }
    #endif /* (DEBUG_SS0_PIN) */

#else
    #if (DEBUG_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        DEBUG_SET_HSIOM_SEL(DEBUG_TX_HSIOM_REG, DEBUG_TX_HSIOM_MASK,
                                       DEBUG_TX_HSIOM_POS, DEBUG_HSIOM_GPIO_SEL);
    #endif /* (DEBUG_UART_TX_PIN) */

    #if (DEBUG_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        DEBUG_rts_Write(DEBUG_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        DEBUG_SET_HSIOM_SEL(DEBUG_RTS_HSIOM_REG, DEBUG_RTS_HSIOM_MASK,
                                       DEBUG_RTS_HSIOM_POS, DEBUG_HSIOM_GPIO_SEL);
    #endif /* (DEBUG_UART_RTS_PIN) */

#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (DEBUG_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    DEBUG_UART_RX_CTRL_REG &= (uint32) ~DEBUG_UART_RX_CTRL_SKIP_START;
#endif /* (DEBUG_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: DEBUG_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void DEBUG_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = DEBUG_RX_MATCH_REG;

    matchReg &= ((uint32) ~DEBUG_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & DEBUG_RX_MATCH_ADDR_MASK)); /* Set address  */

    DEBUG_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: DEBUG_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void DEBUG_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = DEBUG_RX_MATCH_REG;

    matchReg &= ((uint32) ~DEBUG_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << DEBUG_RX_MATCH_MASK_POS));

    DEBUG_RX_MATCH_REG = matchReg;
}


#if(DEBUG_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: DEBUG_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 DEBUG_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != DEBUG_SpiUartGetRxBufferSize())
        {
            rxData = DEBUG_SpiUartReadRxData();
        }

        if (DEBUG_CHECK_INTR_RX(DEBUG_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            DEBUG_ClearRxInterruptSource(DEBUG_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: DEBUG_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 DEBUG_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (DEBUG_CHECK_RX_SW_BUFFER)
        {
            DEBUG_DisableInt();
        }
        #endif

        if (0u != DEBUG_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (DEBUG_CHECK_RX_SW_BUFFER)
            {            
                DEBUG_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = DEBUG_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = DEBUG_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (DEBUG_CHECK_RX_SW_BUFFER)
            {
                DEBUG_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (DEBUG_GetRxInterruptSource() & DEBUG_INTR_RX_ERR);
        DEBUG_ClearRxInterruptSource(DEBUG_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: DEBUG_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   DEBUG_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   DEBUG_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DEBUG_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                DEBUG_UART_FLOW_CTRL_REG |= (uint32)  DEBUG_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                DEBUG_UART_FLOW_CTRL_REG &= (uint32) ~DEBUG_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: DEBUG_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DEBUG_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = DEBUG_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~DEBUG_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (DEBUG_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            DEBUG_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

#endif /* (DEBUG_UART_RX_DIRECTION) */


#if(DEBUG_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: DEBUG_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DEBUG_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            DEBUG_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: DEBUG_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DEBUG_UartPutCRLF(uint32 txDataByte)
    {
        DEBUG_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        DEBUG_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        DEBUG_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: DEBUGSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DEBUG_UartEnableCts(void)
        {
            DEBUG_UART_FLOW_CTRL_REG |= (uint32)  DEBUG_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: DEBUG_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DEBUG_UartDisableCts(void)
        {
            DEBUG_UART_FLOW_CTRL_REG &= (uint32) ~DEBUG_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: DEBUG_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   DEBUG_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   DEBUG_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DEBUG_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                DEBUG_UART_FLOW_CTRL_REG |= (uint32)  DEBUG_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                DEBUG_UART_FLOW_CTRL_REG &= (uint32) ~DEBUG_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */

#endif /* (DEBUG_UART_TX_DIRECTION) */


#if(DEBUG_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: DEBUG_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DEBUG_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        DEBUG_UART_RX_CTRL_REG |= DEBUG_UART_RX_CTRL_SKIP_START;

    #if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(DEBUG_MOSI_SCL_RX_WAKE_PIN)
            (void) DEBUG_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (DEBUG_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(DEBUG_UART_RX_WAKE_PIN)
            (void) DEBUG_rx_wake_ClearInterrupt();
        #endif /* (DEBUG_UART_RX_WAKE_PIN) */
    #endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(DEBUG_UART_RX_WAKEUP_IRQ)
        DEBUG_RxWakeClearPendingInt();
        DEBUG_RxWakeEnableInt();
    #endif /* (DEBUG_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: DEBUG_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DEBUG_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(DEBUG_UART_RX_WAKEUP_IRQ)
        DEBUG_RxWakeDisableInt();
    #endif /* (DEBUG_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (DEBUG_UART_WAKE_ENABLE_CONST) */


#if(DEBUG_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: DEBUG_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(DEBUG_UART_WAKEUP_ISR)
    {
    #ifdef DEBUG_UART_WAKEUP_ISR_ENTRY_CALLBACK
        DEBUG_UART_WAKEUP_ISR_EntryCallback();
    #endif /* DEBUG_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by DEBUG_UartRestoreConfig() call.
        */
    #if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(DEBUG_MOSI_SCL_RX_WAKE_PIN)
            (void) DEBUG_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (DEBUG_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(DEBUG_UART_RX_WAKE_PIN)
            (void) DEBUG_rx_wake_ClearInterrupt();
        #endif /* (DEBUG_UART_RX_WAKE_PIN) */
    #endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef DEBUG_UART_WAKEUP_ISR_EXIT_CALLBACK
        DEBUG_UART_WAKEUP_ISR_ExitCallback();
    #endif /* DEBUG_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (DEBUG_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
