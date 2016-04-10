/*******************************************************************************
* File Name: HCSR04_Clock.h
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

#if !defined(CY_CLOCK_HCSR04_Clock_H)
#define CY_CLOCK_HCSR04_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void HCSR04_Clock_StartEx(uint32 alignClkDiv);
#define HCSR04_Clock_Start() \
    HCSR04_Clock_StartEx(HCSR04_Clock__PA_DIV_ID)

#else

void HCSR04_Clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void HCSR04_Clock_Stop(void);

void HCSR04_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 HCSR04_Clock_GetDividerRegister(void);
uint8  HCSR04_Clock_GetFractionalDividerRegister(void);

#define HCSR04_Clock_Enable()                         HCSR04_Clock_Start()
#define HCSR04_Clock_Disable()                        HCSR04_Clock_Stop()
#define HCSR04_Clock_SetDividerRegister(clkDivider, reset)  \
    HCSR04_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define HCSR04_Clock_SetDivider(clkDivider)           HCSR04_Clock_SetDividerRegister((clkDivider), 1u)
#define HCSR04_Clock_SetDividerValue(clkDivider)      HCSR04_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define HCSR04_Clock_DIV_ID     HCSR04_Clock__DIV_ID

#define HCSR04_Clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define HCSR04_Clock_CTRL_REG   (*(reg32 *)HCSR04_Clock__CTRL_REGISTER)
#define HCSR04_Clock_DIV_REG    (*(reg32 *)HCSR04_Clock__DIV_REGISTER)

#define HCSR04_Clock_CMD_DIV_SHIFT          (0u)
#define HCSR04_Clock_CMD_PA_DIV_SHIFT       (8u)
#define HCSR04_Clock_CMD_DISABLE_SHIFT      (30u)
#define HCSR04_Clock_CMD_ENABLE_SHIFT       (31u)

#define HCSR04_Clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << HCSR04_Clock_CMD_DISABLE_SHIFT))
#define HCSR04_Clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << HCSR04_Clock_CMD_ENABLE_SHIFT))

#define HCSR04_Clock_DIV_FRAC_MASK  (0x000000F8u)
#define HCSR04_Clock_DIV_FRAC_SHIFT (3u)
#define HCSR04_Clock_DIV_INT_MASK   (0xFFFFFF00u)
#define HCSR04_Clock_DIV_INT_SHIFT  (8u)

#else 

#define HCSR04_Clock_DIV_REG        (*(reg32 *)HCSR04_Clock__REGISTER)
#define HCSR04_Clock_ENABLE_REG     HCSR04_Clock_DIV_REG
#define HCSR04_Clock_DIV_FRAC_MASK  HCSR04_Clock__FRAC_MASK
#define HCSR04_Clock_DIV_FRAC_SHIFT (16u)
#define HCSR04_Clock_DIV_INT_MASK   HCSR04_Clock__DIVIDER_MASK
#define HCSR04_Clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_HCSR04_Clock_H) */

/* [] END OF FILE */
