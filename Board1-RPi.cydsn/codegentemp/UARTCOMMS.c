/*******************************************************************************
* File Name: UARTCOMMS.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UARTCOMMS_PVT.h"

#if (UARTCOMMS_SCB_MODE_I2C_INC)
    #include "UARTCOMMS_I2C_PVT.h"
#endif /* (UARTCOMMS_SCB_MODE_I2C_INC) */

#if (UARTCOMMS_SCB_MODE_EZI2C_INC)
    #include "UARTCOMMS_EZI2C_PVT.h"
#endif /* (UARTCOMMS_SCB_MODE_EZI2C_INC) */

#if (UARTCOMMS_SCB_MODE_SPI_INC || UARTCOMMS_SCB_MODE_UART_INC)
    #include "UARTCOMMS_SPI_UART_PVT.h"
#endif /* (UARTCOMMS_SCB_MODE_SPI_INC || UARTCOMMS_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 UARTCOMMS_scbMode = UARTCOMMS_SCB_MODE_UNCONFIG;
    uint8 UARTCOMMS_scbEnableWake;
    uint8 UARTCOMMS_scbEnableIntr;

    /* I2C configuration variables */
    uint8 UARTCOMMS_mode;
    uint8 UARTCOMMS_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * UARTCOMMS_rxBuffer;
    uint8  UARTCOMMS_rxDataBits;
    uint32 UARTCOMMS_rxBufferSize;

    volatile uint8 * UARTCOMMS_txBuffer;
    uint8  UARTCOMMS_txDataBits;
    uint32 UARTCOMMS_txBufferSize;

    /* EZI2C configuration variables */
    uint8 UARTCOMMS_numberOfAddr;
    uint8 UARTCOMMS_subAddrSize;
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 UARTCOMMS_initVar = 0u;

#if (UARTCOMMS_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UARTCOMMS_CUSTOM_INTR_HANDLER)
    void (*UARTCOMMS_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_UARTCOMMS_CUSTOM_INTR_HANDLER) */
#endif /* (UARTCOMMS_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void UARTCOMMS_ScbEnableIntr(void);
static void UARTCOMMS_ScbModeStop(void);
static void UARTCOMMS_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: UARTCOMMS_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UARTCOMMS_Init(void)
{
#if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    if (UARTCOMMS_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        UARTCOMMS_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (UARTCOMMS_SCB_MODE_I2C_CONST_CFG)
    UARTCOMMS_I2CInit();

#elif (UARTCOMMS_SCB_MODE_SPI_CONST_CFG)
    UARTCOMMS_SpiInit();

#elif (UARTCOMMS_SCB_MODE_UART_CONST_CFG)
    UARTCOMMS_UartInit();

#elif (UARTCOMMS_SCB_MODE_EZI2C_CONST_CFG)
    UARTCOMMS_EzI2CInit();

#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UARTCOMMS_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UARTCOMMS_Enable(void)
{
#if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!UARTCOMMS_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        UARTCOMMS_CTRL_REG |= UARTCOMMS_CTRL_ENABLED;

        UARTCOMMS_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        UARTCOMMS_ScbModePostEnable();
    }
#else
    UARTCOMMS_CTRL_REG |= UARTCOMMS_CTRL_ENABLED;

    UARTCOMMS_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    UARTCOMMS_ScbModePostEnable();
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UARTCOMMS_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  UARTCOMMS_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void UARTCOMMS_Start(void)
{
    if (0u == UARTCOMMS_initVar)
    {
        UARTCOMMS_Init();
        UARTCOMMS_initVar = 1u; /* Component was initialized */
    }

    UARTCOMMS_Enable();
}


/*******************************************************************************
* Function Name: UARTCOMMS_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void UARTCOMMS_Stop(void)
{
#if (UARTCOMMS_SCB_IRQ_INTERNAL)
    UARTCOMMS_DisableInt();
#endif /* (UARTCOMMS_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    UARTCOMMS_ScbModeStop();

    /* Disable SCB IP */
    UARTCOMMS_CTRL_REG &= (uint32) ~UARTCOMMS_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    UARTCOMMS_SetTxInterruptMode(UARTCOMMS_NO_INTR_SOURCES);

#if (UARTCOMMS_SCB_IRQ_INTERNAL)
    UARTCOMMS_ClearPendingInt();
#endif /* (UARTCOMMS_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: UARTCOMMS_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void UARTCOMMS_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = UARTCOMMS_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~UARTCOMMS_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (UARTCOMMS_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    UARTCOMMS_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: UARTCOMMS_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void UARTCOMMS_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = UARTCOMMS_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~UARTCOMMS_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (UARTCOMMS_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    UARTCOMMS_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (UARTCOMMS_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: UARTCOMMS_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UARTCOMMS_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_UARTCOMMS_CUSTOM_INTR_HANDLER)
        UARTCOMMS_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_UARTCOMMS_CUSTOM_INTR_HANDLER) */
    }
#endif /* (UARTCOMMS_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: UARTCOMMS_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void UARTCOMMS_ScbEnableIntr(void)
{
#if (UARTCOMMS_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != UARTCOMMS_scbEnableIntr)
        {
            UARTCOMMS_EnableInt();
        }

    #else
        UARTCOMMS_EnableInt();

    #endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (UARTCOMMS_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: UARTCOMMS_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void UARTCOMMS_ScbModePostEnable(void)
{
#if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!UARTCOMMS_CY_SCBIP_V1)
    if (UARTCOMMS_SCB_MODE_SPI_RUNTM_CFG)
    {
        UARTCOMMS_SpiPostEnable();
    }
    else if (UARTCOMMS_SCB_MODE_UART_RUNTM_CFG)
    {
        UARTCOMMS_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!UARTCOMMS_CY_SCBIP_V1) */

#elif (UARTCOMMS_SCB_MODE_SPI_CONST_CFG)
    UARTCOMMS_SpiPostEnable();

#elif (UARTCOMMS_SCB_MODE_UART_CONST_CFG)
    UARTCOMMS_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UARTCOMMS_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void UARTCOMMS_ScbModeStop(void)
{
#if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    if (UARTCOMMS_SCB_MODE_I2C_RUNTM_CFG)
    {
        UARTCOMMS_I2CStop();
    }
    else if (UARTCOMMS_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        UARTCOMMS_EzI2CStop();
    }
#if (!UARTCOMMS_CY_SCBIP_V1)
    else if (UARTCOMMS_SCB_MODE_SPI_RUNTM_CFG)
    {
        UARTCOMMS_SpiStop();
    }
    else if (UARTCOMMS_SCB_MODE_UART_RUNTM_CFG)
    {
        UARTCOMMS_UartStop();
    }
#endif /* (!UARTCOMMS_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (UARTCOMMS_SCB_MODE_I2C_CONST_CFG)
    UARTCOMMS_I2CStop();

#elif (UARTCOMMS_SCB_MODE_EZI2C_CONST_CFG)
    UARTCOMMS_EzI2CStop();

#elif (UARTCOMMS_SCB_MODE_SPI_CONST_CFG)
    UARTCOMMS_SpiStop();

#elif (UARTCOMMS_SCB_MODE_UART_CONST_CFG)
    UARTCOMMS_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: UARTCOMMS_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UARTCOMMS_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [UARTCOMMS_SCB_PINS_NUMBER];
        uint32 pinsDm   [UARTCOMMS_SCB_PINS_NUMBER];

    #if (!UARTCOMMS_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!UARTCOMMS_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < UARTCOMMS_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = UARTCOMMS_HSIOM_DEF_SEL;
            pinsDm[i]    = UARTCOMMS_PIN_DM_ALG_HIZ;
        }

        if ((UARTCOMMS_SCB_MODE_I2C   == mode) ||
           (UARTCOMMS_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX] = UARTCOMMS_HSIOM_I2C_SEL;
            hsiomSel[UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_HSIOM_I2C_SEL;

            pinsDm[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX] = UARTCOMMS_PIN_DM_OD_LO;
            pinsDm[UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_PIN_DM_OD_LO;
        }
    #if (!UARTCOMMS_CY_SCBIP_V1)
        else if (UARTCOMMS_SCB_MODE_SPI == mode)
        {
            hsiomSel[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;
            hsiomSel[UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;
            hsiomSel[UARTCOMMS_CTS_SCLK_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;

            if (UARTCOMMS_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX] = UARTCOMMS_PIN_DM_DIG_HIZ;
                pinsDm[UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;
                pinsDm[UARTCOMMS_CTS_SCLK_PIN_INDEX] = UARTCOMMS_PIN_DM_DIG_HIZ;

            #if (UARTCOMMS_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[UARTCOMMS_RTS_SS0_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;
                pinsDm  [UARTCOMMS_RTS_SS0_PIN_INDEX] = UARTCOMMS_PIN_DM_DIG_HIZ;
            #endif /* (UARTCOMMS_RTS_SS0_PIN) */

            #if (UARTCOMMS_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= UARTCOMMS_TX_SDA_MISO_PIN_MASK;
            #endif /* (UARTCOMMS_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;
                pinsDm[UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_PIN_DM_DIG_HIZ;
                pinsDm[UARTCOMMS_CTS_SCLK_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;

            #if (UARTCOMMS_RTS_SS0_PIN)
                hsiomSel [UARTCOMMS_RTS_SS0_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;
                pinsDm   [UARTCOMMS_RTS_SS0_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;
                pinsInBuf |= UARTCOMMS_RTS_SS0_PIN_MASK;
            #endif /* (UARTCOMMS_RTS_SS0_PIN) */

            #if (UARTCOMMS_SS1_PIN)
                hsiomSel [UARTCOMMS_SS1_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;
                pinsDm   [UARTCOMMS_SS1_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;
                pinsInBuf |= UARTCOMMS_SS1_PIN_MASK;
            #endif /* (UARTCOMMS_SS1_PIN) */

            #if (UARTCOMMS_SS2_PIN)
                hsiomSel [UARTCOMMS_SS2_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;
                pinsDm   [UARTCOMMS_SS2_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;
                pinsInBuf |= UARTCOMMS_SS2_PIN_MASK;
            #endif /* (UARTCOMMS_SS2_PIN) */

            #if (UARTCOMMS_SS3_PIN)
                hsiomSel [UARTCOMMS_SS3_PIN_INDEX] = UARTCOMMS_HSIOM_SPI_SEL;
                pinsDm   [UARTCOMMS_SS3_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;
                pinsInBuf |= UARTCOMMS_SS3_PIN_MASK;
            #endif /* (UARTCOMMS_SS3_PIN) */

                /* Disable input buffers */
            #if (UARTCOMMS_RX_SCL_MOSI_PIN)
                pinsInBuf |= UARTCOMMS_RX_SCL_MOSI_PIN_MASK;
            #endif /* (UARTCOMMS_RX_SCL_MOSI_PIN) */

             #if (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN) */

            #if (UARTCOMMS_CTS_SCLK_PIN)
                pinsInBuf |= UARTCOMMS_CTS_SCLK_PIN_MASK;
            #endif /* (UARTCOMMS_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (UARTCOMMS_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_HSIOM_UART_SEL;
                pinsDm  [UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (UARTCOMMS_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX] = UARTCOMMS_HSIOM_UART_SEL;
                    pinsDm  [UARTCOMMS_RX_SCL_MOSI_PIN_INDEX] = UARTCOMMS_PIN_DM_DIG_HIZ;
                }

                if (0u != (UARTCOMMS_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_HSIOM_UART_SEL;
                    pinsDm  [UARTCOMMS_TX_SDA_MISO_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;

                #if (UARTCOMMS_TX_SDA_MISO_PIN)
                     pinsInBuf |= UARTCOMMS_TX_SDA_MISO_PIN_MASK;
                #endif /* (UARTCOMMS_TX_SDA_MISO_PIN) */
                }

            #if !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
                if (UARTCOMMS_UART_MODE_STD == subMode)
                {
                    if (0u != (UARTCOMMS_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[UARTCOMMS_CTS_SCLK_PIN_INDEX] = UARTCOMMS_HSIOM_UART_SEL;
                        pinsDm  [UARTCOMMS_CTS_SCLK_PIN_INDEX] = UARTCOMMS_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (UARTCOMMS_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[UARTCOMMS_RTS_SS0_PIN_INDEX] = UARTCOMMS_HSIOM_UART_SEL;
                        pinsDm  [UARTCOMMS_RTS_SS0_PIN_INDEX] = UARTCOMMS_PIN_DM_STRONG;

                    #if (UARTCOMMS_RTS_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= UARTCOMMS_RTS_SS0_PIN_MASK;
                    #endif /* (UARTCOMMS_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */
            }
        }
    #endif /* (!UARTCOMMS_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        UARTCOMMS_SET_INP_DIS(UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        UARTCOMMS_SET_INCFG_TYPE(UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        UARTCOMMS_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN) */

    #if (UARTCOMMS_RX_SCL_MOSI_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_RX_SCL_MOSI_HSIOM_REG,
                                       UARTCOMMS_RX_SCL_MOSI_HSIOM_MASK,
                                       UARTCOMMS_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX]);

        UARTCOMMS_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[UARTCOMMS_RX_SCL_MOSI_PIN_INDEX]);

    #if (!UARTCOMMS_CY_SCBIP_V1)
        UARTCOMMS_SET_INP_DIS(UARTCOMMS_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     UARTCOMMS_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & UARTCOMMS_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!UARTCOMMS_CY_SCBIP_V1) */
    #endif /* (UARTCOMMS_RX_SCL_MOSI_PIN) */

    #if (UARTCOMMS_TX_SDA_MISO_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_TX_SDA_MISO_HSIOM_REG,
                                       UARTCOMMS_TX_SDA_MISO_HSIOM_MASK,
                                       UARTCOMMS_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[UARTCOMMS_TX_SDA_MISO_PIN_INDEX]);

        UARTCOMMS_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[UARTCOMMS_TX_SDA_MISO_PIN_INDEX]);

    #if (!UARTCOMMS_CY_SCBIP_V1)
        UARTCOMMS_SET_INP_DIS(UARTCOMMS_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     UARTCOMMS_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & UARTCOMMS_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!UARTCOMMS_CY_SCBIP_V1) */
    #endif /* (UARTCOMMS_RX_SCL_MOSI_PIN) */

    #if (UARTCOMMS_CTS_SCLK_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_CTS_SCLK_HSIOM_REG,
                                       UARTCOMMS_CTS_SCLK_HSIOM_MASK,
                                       UARTCOMMS_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[UARTCOMMS_CTS_SCLK_PIN_INDEX]);

        UARTCOMMS_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[UARTCOMMS_CTS_SCLK_PIN_INDEX]);

        UARTCOMMS_SET_INP_DIS(UARTCOMMS_uart_cts_spi_sclk_INP_DIS,
                                     UARTCOMMS_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & UARTCOMMS_CTS_SCLK_PIN_MASK)));
    #endif /* (UARTCOMMS_CTS_SCLK_PIN) */

    #if (UARTCOMMS_RTS_SS0_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_RTS_SS0_HSIOM_REG,
                                       UARTCOMMS_RTS_SS0_HSIOM_MASK,
                                       UARTCOMMS_RTS_SS0_HSIOM_POS,
                                       hsiomSel[UARTCOMMS_RTS_SS0_PIN_INDEX]);

        UARTCOMMS_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[UARTCOMMS_RTS_SS0_PIN_INDEX]);

        UARTCOMMS_SET_INP_DIS(UARTCOMMS_uart_rts_spi_ss0_INP_DIS,
                                     UARTCOMMS_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & UARTCOMMS_RTS_SS0_PIN_MASK)));
    #endif /* (UARTCOMMS_RTS_SS0_PIN) */

    #if (UARTCOMMS_SS1_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_SS1_HSIOM_REG,
                                       UARTCOMMS_SS1_HSIOM_MASK,
                                       UARTCOMMS_SS1_HSIOM_POS,
                                       hsiomSel[UARTCOMMS_SS1_PIN_INDEX]);

        UARTCOMMS_spi_ss1_SetDriveMode((uint8) pinsDm[UARTCOMMS_SS1_PIN_INDEX]);

        UARTCOMMS_SET_INP_DIS(UARTCOMMS_spi_ss1_INP_DIS,
                                     UARTCOMMS_spi_ss1_MASK,
                                     (0u != (pinsInBuf & UARTCOMMS_SS1_PIN_MASK)));
    #endif /* (UARTCOMMS_SS1_PIN) */

    #if (UARTCOMMS_SS2_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_SS2_HSIOM_REG,
                                       UARTCOMMS_SS2_HSIOM_MASK,
                                       UARTCOMMS_SS2_HSIOM_POS,
                                       hsiomSel[UARTCOMMS_SS2_PIN_INDEX]);

        UARTCOMMS_spi_ss2_SetDriveMode((uint8) pinsDm[UARTCOMMS_SS2_PIN_INDEX]);

        UARTCOMMS_SET_INP_DIS(UARTCOMMS_spi_ss2_INP_DIS,
                                     UARTCOMMS_spi_ss2_MASK,
                                     (0u != (pinsInBuf & UARTCOMMS_SS2_PIN_MASK)));
    #endif /* (UARTCOMMS_SS2_PIN) */

    #if (UARTCOMMS_SS3_PIN)
        UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_SS3_HSIOM_REG,
                                       UARTCOMMS_SS3_HSIOM_MASK,
                                       UARTCOMMS_SS3_HSIOM_POS,
                                       hsiomSel[UARTCOMMS_SS3_PIN_INDEX]);

        UARTCOMMS_spi_ss3_SetDriveMode((uint8) pinsDm[UARTCOMMS_SS3_PIN_INDEX]);

        UARTCOMMS_SET_INP_DIS(UARTCOMMS_spi_ss3_INP_DIS,
                                     UARTCOMMS_spi_ss3_MASK,
                                     (0u != (pinsInBuf & UARTCOMMS_SS3_PIN_MASK)));
    #endif /* (UARTCOMMS_SS3_PIN) */
    }

#endif /* (UARTCOMMS_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: UARTCOMMS_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UARTCOMMS_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (UARTCOMMS_CTRL_REG & UARTCOMMS_CTRL_EC_AM_MODE)) &&
            (0u == (UARTCOMMS_I2C_CTRL_REG & UARTCOMMS_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            UARTCOMMS_CTRL_REG &= ~UARTCOMMS_CTRL_EC_AM_MODE;
            UARTCOMMS_CTRL_REG |=  UARTCOMMS_CTRL_EC_AM_MODE;
        }

        UARTCOMMS_I2C_SLAVE_CMD_REG = UARTCOMMS_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (UARTCOMMS_CY_SCBIP_V0 || UARTCOMMS_CY_SCBIP_V1) */


/* [] END OF FILE */
