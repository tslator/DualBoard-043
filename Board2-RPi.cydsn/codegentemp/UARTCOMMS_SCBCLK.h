/*******************************************************************************
* File Name: UARTCOMMS_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_UARTCOMMS_SCBCLK_H)
#define CY_CLOCK_UARTCOMMS_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void UARTCOMMS_SCBCLK_StartEx(uint32 alignClkDiv);
#define UARTCOMMS_SCBCLK_Start() \
    UARTCOMMS_SCBCLK_StartEx(UARTCOMMS_SCBCLK__PA_DIV_ID)

#else

void UARTCOMMS_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void UARTCOMMS_SCBCLK_Stop(void);

void UARTCOMMS_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 UARTCOMMS_SCBCLK_GetDividerRegister(void);
uint8  UARTCOMMS_SCBCLK_GetFractionalDividerRegister(void);

#define UARTCOMMS_SCBCLK_Enable()                         UARTCOMMS_SCBCLK_Start()
#define UARTCOMMS_SCBCLK_Disable()                        UARTCOMMS_SCBCLK_Stop()
#define UARTCOMMS_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    UARTCOMMS_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define UARTCOMMS_SCBCLK_SetDivider(clkDivider)           UARTCOMMS_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define UARTCOMMS_SCBCLK_SetDividerValue(clkDivider)      UARTCOMMS_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define UARTCOMMS_SCBCLK_DIV_ID     UARTCOMMS_SCBCLK__DIV_ID

#define UARTCOMMS_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define UARTCOMMS_SCBCLK_CTRL_REG   (*(reg32 *)UARTCOMMS_SCBCLK__CTRL_REGISTER)
#define UARTCOMMS_SCBCLK_DIV_REG    (*(reg32 *)UARTCOMMS_SCBCLK__DIV_REGISTER)

#define UARTCOMMS_SCBCLK_CMD_DIV_SHIFT          (0u)
#define UARTCOMMS_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define UARTCOMMS_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define UARTCOMMS_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define UARTCOMMS_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << UARTCOMMS_SCBCLK_CMD_DISABLE_SHIFT))
#define UARTCOMMS_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << UARTCOMMS_SCBCLK_CMD_ENABLE_SHIFT))

#define UARTCOMMS_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define UARTCOMMS_SCBCLK_DIV_FRAC_SHIFT (3u)
#define UARTCOMMS_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define UARTCOMMS_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define UARTCOMMS_SCBCLK_DIV_REG        (*(reg32 *)UARTCOMMS_SCBCLK__REGISTER)
#define UARTCOMMS_SCBCLK_ENABLE_REG     UARTCOMMS_SCBCLK_DIV_REG
#define UARTCOMMS_SCBCLK_DIV_FRAC_MASK  UARTCOMMS_SCBCLK__FRAC_MASK
#define UARTCOMMS_SCBCLK_DIV_FRAC_SHIFT (16u)
#define UARTCOMMS_SCBCLK_DIV_INT_MASK   UARTCOMMS_SCBCLK__DIVIDER_MASK
#define UARTCOMMS_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_UARTCOMMS_SCBCLK_H) */

/* [] END OF FILE */
