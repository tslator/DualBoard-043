/*******************************************************************************
* File Name: UART_Debug.h
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_UART_Debug_H
#define CY_SW_TX_UART_UART_Debug_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define UART_Debug_BAUD_RATE                      (115200u)
#define UART_Debug_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(UART_Debug_PIN_STATIC_MODE == 1u)
    void UART_Debug_Start(void) ;
#else
    void UART_Debug_StartEx(uint8 port, uint8 pin) ;
#endif /* (UART_Debug_PIN_STATIC_MODE == 1u) */

void UART_Debug_Stop(void) ;
void UART_Debug_PutChar(uint8 txDataByte) ;
void UART_Debug_PutString(const char8 string[]) ;
void UART_Debug_PutArray(const uint8 array[], uint32 byteCount) ;
void UART_Debug_PutHexByte(uint8 txHexByte) ;
void UART_Debug_PutHexInt(uint16 txHexInt) ;
void UART_Debug_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_UART_Debug_H */


/* [] END OF FILE */
