/*******************************************************************************
* File Name: I2CIF_I2C.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2CIF_PVT.h"
#include "I2CIF_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 I2CIF_state;  /* Current state of I2C FSM */

#if(I2CIF_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const I2CIF_I2C_INIT_STRUCT I2CIF_configI2C =
    {
        I2CIF_I2C_MODE,
        I2CIF_I2C_OVS_FACTOR_LOW,
        I2CIF_I2C_OVS_FACTOR_HIGH,
        I2CIF_I2C_MEDIAN_FILTER_ENABLE,
        I2CIF_I2C_SLAVE_ADDRESS,
        I2CIF_I2C_SLAVE_ADDRESS_MASK,
        I2CIF_I2C_ACCEPT_ADDRESS,
        I2CIF_I2C_WAKE_ENABLE,
        I2CIF_I2C_BYTE_MODE_ENABLE,
        I2CIF_I2C_DATA_RATE,
        I2CIF_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: I2CIF_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
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
    void I2CIF_I2CInit(const I2CIF_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            I2CIF_SetPins(I2CIF_SCB_MODE_I2C, I2CIF_DUMMY_PARAM,
                                     I2CIF_DUMMY_PARAM);

            /* Store internal configuration */
            I2CIF_scbMode       = (uint8) I2CIF_SCB_MODE_I2C;
            I2CIF_scbEnableWake = (uint8) config->enableWake;
            I2CIF_scbEnableIntr = (uint8) I2CIF_SCB_IRQ_INTERNAL;

            I2CIF_mode          = (uint8) config->mode;
            I2CIF_acceptAddr    = (uint8) config->acceptAddr;

        #if (I2CIF_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            I2CIF_SET_I2C_CFG_SDA_FILT_TRIM(I2CIF_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (I2CIF_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((I2CIF_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= I2CIF_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (I2CIF_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                I2CIF_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = I2CIF_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                I2CIF_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = I2CIF_DIGITAL_FILTER_ENABLE;
            }

        #if (!I2CIF_CY_SCBIP_V0)
            locEnableWake = (I2CIF_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!I2CIF_CY_SCBIP_V0) */

            /* Configure I2C interface */
            I2CIF_CTRL_REG     = I2CIF_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            I2CIF_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            I2CIF_GET_CTRL_EC_AM_MODE (locEnableWake);

            I2CIF_I2C_CTRL_REG = I2CIF_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    I2CIF_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    I2CIF_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    I2CIF_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            I2CIF_RX_CTRL_REG      = I2CIF_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                I2CIF_I2C_RX_CTRL;
            I2CIF_RX_FIFO_CTRL_REG = I2CIF_CLEAR_REG;

            /* Set default address and mask */
            I2CIF_RX_MATCH_REG    = ((I2CIF_I2C_SLAVE) ?
                                                (I2CIF_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 I2CIF_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (I2CIF_CLEAR_REG));


            /* Configure TX direction */
            I2CIF_TX_CTRL_REG      = I2CIF_I2C_TX_CTRL;
            I2CIF_TX_FIFO_CTRL_REG = I2CIF_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (I2CIF_ISR_NUMBER);
            CyIntSetPriority(I2CIF_ISR_NUMBER, I2CIF_ISR_PRIORITY);
            (void) CyIntSetVector(I2CIF_ISR_NUMBER, &I2CIF_I2C_ISR);

            /* Configure interrupt sources */
        #if(!I2CIF_CY_SCBIP_V1)
            I2CIF_INTR_SPI_EC_MASK_REG = I2CIF_NO_INTR_SOURCES;
        #endif /* (!I2CIF_CY_SCBIP_V1) */

            I2CIF_INTR_I2C_EC_MASK_REG = I2CIF_NO_INTR_SOURCES;
            I2CIF_INTR_RX_MASK_REG     = I2CIF_NO_INTR_SOURCES;
            I2CIF_INTR_TX_MASK_REG     = I2CIF_NO_INTR_SOURCES;

            I2CIF_INTR_SLAVE_MASK_REG  = ((I2CIF_I2C_SLAVE) ?
                            (I2CIF_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             I2CIF_I2C_INTR_SLAVE_MASK) : (I2CIF_CLEAR_REG));

            I2CIF_INTR_MASTER_MASK_REG = ((I2CIF_I2C_MASTER) ?
                                                     (I2CIF_I2C_INTR_MASTER_MASK) :
                                                     (I2CIF_CLEAR_REG));

            /* Configure global variables */
            I2CIF_state = I2CIF_I2C_FSM_IDLE;

            /* Internal slave variables */
            I2CIF_slStatus        = 0u;
            I2CIF_slRdBufIndex    = 0u;
            I2CIF_slWrBufIndex    = 0u;
            I2CIF_slOverFlowCount = 0u;

            /* Internal master variables */
            I2CIF_mstrStatus     = 0u;
            I2CIF_mstrRdBufIndex = 0u;
            I2CIF_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: I2CIF_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CIF_I2CInit(void)
    {
    #if(I2CIF_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        I2CIF_SET_I2C_CFG_SDA_FILT_TRIM(I2CIF_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (I2CIF_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        I2CIF_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        I2CIF_CTRL_REG     = I2CIF_I2C_DEFAULT_CTRL;
        I2CIF_I2C_CTRL_REG = I2CIF_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        I2CIF_RX_CTRL_REG      = I2CIF_I2C_DEFAULT_RX_CTRL;
        I2CIF_RX_FIFO_CTRL_REG = I2CIF_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        I2CIF_RX_MATCH_REG     = I2CIF_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        I2CIF_TX_CTRL_REG      = I2CIF_I2C_DEFAULT_TX_CTRL;
        I2CIF_TX_FIFO_CTRL_REG = I2CIF_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (I2CIF_ISR_NUMBER);
        CyIntSetPriority(I2CIF_ISR_NUMBER, I2CIF_ISR_PRIORITY);
    #if(!I2CIF_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(I2CIF_ISR_NUMBER, &I2CIF_I2C_ISR);
    #endif /* (I2CIF_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!I2CIF_CY_SCBIP_V1)
        I2CIF_INTR_SPI_EC_MASK_REG = I2CIF_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!I2CIF_CY_SCBIP_V1) */

        I2CIF_INTR_I2C_EC_MASK_REG = I2CIF_I2C_DEFAULT_INTR_I2C_EC_MASK;
        I2CIF_INTR_SLAVE_MASK_REG  = I2CIF_I2C_DEFAULT_INTR_SLAVE_MASK;
        I2CIF_INTR_MASTER_MASK_REG = I2CIF_I2C_DEFAULT_INTR_MASTER_MASK;
        I2CIF_INTR_RX_MASK_REG     = I2CIF_I2C_DEFAULT_INTR_RX_MASK;
        I2CIF_INTR_TX_MASK_REG     = I2CIF_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        I2CIF_state = I2CIF_I2C_FSM_IDLE;

    #if(I2CIF_I2C_SLAVE)
        /* Internal slave variable */
        I2CIF_slStatus        = 0u;
        I2CIF_slRdBufIndex    = 0u;
        I2CIF_slWrBufIndex    = 0u;
        I2CIF_slOverFlowCount = 0u;
    #endif /* (I2CIF_I2C_SLAVE) */

    #if(I2CIF_I2C_MASTER)
    /* Internal master variable */
        I2CIF_mstrStatus     = 0u;
        I2CIF_mstrRdBufIndex = 0u;
        I2CIF_mstrWrBufIndex = 0u;
    #endif /* (I2CIF_I2C_MASTER) */
    }
#endif /* (I2CIF_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: I2CIF_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2CIF_I2CStop(void)
{
    I2CIF_state = I2CIF_I2C_FSM_IDLE;
}


#if(I2CIF_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: I2CIF_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables I2CIF_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CIF_I2CSaveConfig(void)
    {
    #if (!I2CIF_CY_SCBIP_V0)
        #if (I2CIF_I2C_MULTI_MASTER_SLAVE_CONST && I2CIF_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (I2CIF_CTRL_REG & I2CIF_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                I2CIF_Stop();
                I2CIF_CTRL_REG |= I2CIF_CTRL_EC_AM_MODE;
                I2CIF_Enable();
            }
        #endif /* (I2CIF_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (I2CIF_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            I2CIF_SCBCLK_Stop();
        #endif /* (I2CIF_SCB_CLK_INTERNAL) */
    #endif /* (!I2CIF_CY_SCBIP_V0) */

        I2CIF_SetI2CExtClkInterruptMode(I2CIF_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: I2CIF_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables I2CIF_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void I2CIF_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        I2CIF_SetI2CExtClkInterruptMode(I2CIF_NO_INTR_SOURCES);

    #if (!I2CIF_CY_SCBIP_V0)
        #if (I2CIF_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            I2CIF_SCBCLK_Start();
        #endif /* (I2CIF_SCB_CLK_INTERNAL) */
    #endif /* (!I2CIF_CY_SCBIP_V0) */
    }
#endif /* (I2CIF_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
