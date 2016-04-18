/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in _EZI2C mode.
*  Do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_EZI2C_PVT_EZI2C_Slave_H)
#define CY_SCB_EZI2C_PVT_EZI2C_Slave_H

#include "EZI2C_Slave_EZI2C.h"


/***************************************
*      EZI2C Private Vars
***************************************/

extern volatile uint8 EZI2C_Slave_curStatus;
extern uint8 EZI2C_Slave_fsmState;

/* Variables intended to be used with Buffer 1: Primary slave address */
extern volatile uint8 * EZI2C_Slave_dataBuffer1;
extern uint16 EZI2C_Slave_bufSizeBuf1;
extern uint16 EZI2C_Slave_protectBuf1;
extern uint8 EZI2C_Slave_offsetBuf1;
extern uint16 EZI2C_Slave_indexBuf1;

#if(EZI2C_Slave_SECONDARY_ADDRESS_ENABLE_CONST)
    extern uint8 EZI2C_Slave_addrBuf1;
    extern uint8 EZI2C_Slave_addrBuf2;

    /* Variables intended to be used with Buffer 2: Primary slave address */
    extern volatile uint8 * EZI2C_Slave_dataBuffer2;
    extern uint16 EZI2C_Slave_bufSizeBuf2;
    extern uint16 EZI2C_Slave_protectBuf2;
    extern uint8 EZI2C_Slave_offsetBuf2;
    extern uint16 EZI2C_Slave_indexBuf2;
#endif /* (EZI2C_Slave_SECONDARY_ADDRESS_ENABLE_CONST) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(EZI2C_Slave_SCB_MODE_EZI2C_CONST_CFG)
    void EZI2C_Slave_EzI2CInit(void);
#endif /* (EZI2C_Slave_SCB_MODE_EZI2C_CONST_CFG) */

void EZI2C_Slave_EzI2CStop(void);
#if(EZI2C_Slave_EZI2C_WAKE_ENABLE_CONST)
    void EZI2C_Slave_EzI2CSaveConfig(void);
    void EZI2C_Slave_EzI2CRestoreConfig(void);
#endif /* (EZI2C_Slave_EZI2C_WAKE_ENABLE_CONST) */

#endif /* (CY_SCB__EZI2C_PVT_EZI2C_Slave_H) */


/* [] END OF FILE */
