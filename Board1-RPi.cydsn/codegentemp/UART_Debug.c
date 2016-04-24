/*******************************************************************************
* File Name: UART_Debug.c
* Version 1.50
*
* Description:
*  This file provides the source code to the API for the Software Transmit UART.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_Debug_PVT.h"

#if(UART_Debug_PIN_STATIC_MODE == 1u)
    uint32 UART_Debug_pinNumber = UART_Debug_PIN_NUMBER;
    uint32 UART_Debug_pinPortNumber = UART_Debug_PIN_PORT_NUMBER;
    #if(CY_PSOC3)
        uint32 pdata UART_Debug_pinDrAdress = UART_Debug_PIN_DR;
    #else
        uint32 UART_Debug_pinDrAdress = UART_Debug_PIN_DR;
    #endif /* (CY_PSOC3) */
#else
    uint32 UART_Debug_pinNumber;
    uint32 UART_Debug_pinPortNumber;
    #if(CY_PSOC3)
        uint32 pdata UART_Debug_pinDrAdress;
    #else
        uint32 UART_Debug_pinDrAdress;
    #endif /* (CY_PSOC3) */
#endif /* (UART_Debug_PIN_STATIC_MODE == 1u) */


#if(UART_Debug_PIN_STATIC_MODE == 1u)
    /*******************************************************************************
    * Function Name: UART_Debug_Start
    ********************************************************************************
    *
    * Summary:
    *  Empty function. Included for consistency with other
    *  components. This API is not available when PinAssignmentMethod
    *  is set to Dynamic.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_Debug_Start(void) 
    {

    }
#else
    /*******************************************************************************
    * Function Name: UART_Debug_StartEx
    ********************************************************************************
    *
    * Summary:
    *  Configures the SW Tx UART to use the pin specified
    *  by the parameters. This API is only available when
    *  PinAssignmentMethod is set to Dynamic.
    *
    * Parameters:
    *  port:  Port number for dynamic pin assignment
    *  pin:   Pin number for dynamic pin assignment
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_Debug_StartEx(uint8 port, uint8 pin) 
    {
        uint32 portConfigAddr;

        #if (CY_PSOC4)
            uint32 portDataRegAddr;
        #endif /* (CY_PSOC4) */

        if ((pin <= UART_Debug_MAX_PIN_NUMBER) && (port <= UART_Debug_MAX_PORT_NUMBER))
        {
            #if (!CY_PSOC4)
                portConfigAddr = UART_Debug_PORT_CNF_BASE;
                portConfigAddr += ((uint32)port * (UART_Debug_MAX_PIN_NUMBER + 1u)) + pin;
                CyPins_SetPinDriveMode(portConfigAddr, CY_PINS_DM_STRONG);
                CyPins_SetPin(portConfigAddr);
                UART_Debug_pinDrAdress = portConfigAddr;
            #else
                portConfigAddr = UART_Debug_PORT_CNF_BASE + (UART_Debug_PORT_CNF_SIZE * port) +
                                                                                UART_Debug_PORT_CNF_MODE_OFFSET;
                CY_SYS_PINS_SET_DRIVE_MODE(portConfigAddr, pin, CY_SYS_PINS_DM_STRONG);
                portDataRegAddr = UART_Debug_PORT_CNF_BASE + (UART_Debug_PORT_CNF_SIZE * port) +
                                                                                UART_Debug_PORT_CNF_DR_OFFSET;
                CY_SYS_PINS_SET_PIN(portDataRegAddr, pin);
                UART_Debug_pinDrAdress = portDataRegAddr;
            #endif /* (!CY_PSOC4) */
            UART_Debug_pinNumber = pin;
            UART_Debug_pinPortNumber = port;
        }
    }
#endif /* (UART_Debug_PIN_STATIC_MODE == 1u) */


/*******************************************************************************
* Function Name: UART_Debug_Stop
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_Debug_Stop(void) 
{

}


/*******************************************************************************
* Function Name: UART_Debug_PutString
********************************************************************************
*
* Summary:
*  Sends a NULL terminated string via the Tx pin.
*
* Parameters:
*  string: Pointer to the null terminated string to send
*
* Return:
*  None
*
*******************************************************************************/
void UART_Debug_PutString(const char8 string[]) 
{
    uint8 stringIndex = 1u;
    char8 current = *string;

    /* Until null is reached, print next character */
    while((char8) '\0' != current)
    {
        UART_Debug_PutChar((uint8)current);
        current = string[stringIndex];
        stringIndex++;
    }
}


/*******************************************************************************
* Function Name: UART_Debug_PutArray
********************************************************************************
*
* Summary:
*  Sends byteCount bytes from a memory array via the Tx pin.
*
* Parameters:
*  data: Pointer to the memory array
*  byteCount: Number of bytes to be transmitted
*
* Return:
*  None
*
*******************************************************************************/
void UART_Debug_PutArray(const uint8 array[], uint32 byteCount) 
{
    uint32 arrayIndex;

    for (arrayIndex = 0u; arrayIndex < byteCount; arrayIndex++)
    {
        UART_Debug_PutChar(array[arrayIndex]);
    }
}


/*******************************************************************************
* Function Name: UART_Debug_PutHexByte
********************************************************************************
*
* Summary:
*  Sends a byte in Hex representation (two characters, uppercase for A-F) via
*  the Tx pin.
*
* Parameters:
*  TxHexByte: The byte to be converted to ASCII characters and
*             sent via the Tx pin.
*
* Return:
*  None
*
*******************************************************************************/
void UART_Debug_PutHexByte(uint8 txHexByte) 
{
    static char8 const CYCODE UART_Debug_hex[] = "0123456789ABCDEF";

    UART_Debug_PutChar((uint8) UART_Debug_hex[txHexByte >> UART_Debug_BYTE_UPPER_NIBBLE_SHIFT]);
    UART_Debug_PutChar((uint8) UART_Debug_hex[txHexByte & UART_Debug_BYTE_LOWER_NIBBLE_MASK]);
}


/*******************************************************************************
* Function Name: UART_Debug_PutHexInt
********************************************************************************
*
* Summary:
*  Sends a 16-bit unsigned integer in Hex representation (four characters,
*  uppercase for A-F) via the Tx pin.
*
* Parameters:
*  TxHexInt: The uint16 to be converted to ASCII characters and sent via
*            the Tx pin.
*
* Return:
*  None
*
*******************************************************************************/
void UART_Debug_PutHexInt(uint16 txHexInt) 
{
    UART_Debug_PutHexByte((uint8)(txHexInt >> UART_Debug_U16_UPPER_BYTE_SHIFT));
    UART_Debug_PutHexByte((uint8)(txHexInt & UART_Debug_U16_LOWER_BYTE_MASK));
}


/*******************************************************************************
* Function Name: UART_Debug_PutCRLF
********************************************************************************
*
* Summary:
*  Sends a carriage return (0x0D) and a line feed (0x0A) via the Tx pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_Debug_PutCRLF(void) 
{
    UART_Debug_PutChar(0x0Du);
    UART_Debug_PutChar(0x0Au);
}


/* [] END OF FILE */
