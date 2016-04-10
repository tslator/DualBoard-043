/*******************************************************************************
* File Name: UARTCOMMS_SPI_UART_INT.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UARTCOMMS_PVT.h"
#include "UARTCOMMS_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (UARTCOMMS_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: UARTCOMMS_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(UARTCOMMS_SPI_UART_ISR)
{
#if (UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (UARTCOMMS_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (UARTCOMMS_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef UARTCOMMS_SPI_UART_ISR_ENTRY_CALLBACK
    UARTCOMMS_SPI_UART_ISR_EntryCallback();
#endif /* UARTCOMMS_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != UARTCOMMS_customIntrHandler)
    {
        UARTCOMMS_customIntrHandler();
    }

    #if (UARTCOMMS_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        UARTCOMMS_ClearSpiExtClkInterruptSource(UARTCOMMS_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (UARTCOMMS_CHECK_RX_SW_BUFFER)
    {
        if (UARTCOMMS_CHECK_INTR_RX_MASKED(UARTCOMMS_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (UARTCOMMS_rxBufferHead + 1u);

                /* Adjust local head index */
                if (UARTCOMMS_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == UARTCOMMS_rxBufferTail)
                {
                    #if (UARTCOMMS_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        UARTCOMMS_INTR_RX_MASK_REG &= ~UARTCOMMS_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) UARTCOMMS_RX_FIFO_RD_REG;
                        UARTCOMMS_rxBufferOverflow = (uint8) UARTCOMMS_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    UARTCOMMS_PutWordInRxBuffer(locHead, UARTCOMMS_RX_FIFO_RD_REG);

                    /* Move head index */
                    UARTCOMMS_rxBufferHead = locHead;
                }
            }
            while(0u != UARTCOMMS_GET_RX_FIFO_ENTRIES);

            UARTCOMMS_ClearRxInterruptSource(UARTCOMMS_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (UARTCOMMS_CHECK_TX_SW_BUFFER)
    {
        if (UARTCOMMS_CHECK_INTR_TX_MASKED(UARTCOMMS_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (UARTCOMMS_txBufferHead != UARTCOMMS_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (UARTCOMMS_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (UARTCOMMS_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    UARTCOMMS_TX_FIFO_WR_REG = UARTCOMMS_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    UARTCOMMS_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    UARTCOMMS_DISABLE_INTR_TX(UARTCOMMS_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (UARTCOMMS_SPI_UART_FIFO_SIZE != UARTCOMMS_GET_TX_FIFO_ENTRIES);

            UARTCOMMS_ClearTxInterruptSource(UARTCOMMS_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef UARTCOMMS_SPI_UART_ISR_EXIT_CALLBACK
    UARTCOMMS_SPI_UART_ISR_ExitCallback();
#endif /* UARTCOMMS_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (UARTCOMMS_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
