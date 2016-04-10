/*******************************************************************************
* File Name: Quadrature_Decode_Clock.h
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

#if !defined(CY_CLOCK_Quadrature_Decode_Clock_H)
#define CY_CLOCK_Quadrature_Decode_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Quadrature_Decode_Clock_StartEx(uint32 alignClkDiv);
#define Quadrature_Decode_Clock_Start() \
    Quadrature_Decode_Clock_StartEx(Quadrature_Decode_Clock__PA_DIV_ID)

#else

void Quadrature_Decode_Clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Quadrature_Decode_Clock_Stop(void);

void Quadrature_Decode_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Quadrature_Decode_Clock_GetDividerRegister(void);
uint8  Quadrature_Decode_Clock_GetFractionalDividerRegister(void);

#define Quadrature_Decode_Clock_Enable()                         Quadrature_Decode_Clock_Start()
#define Quadrature_Decode_Clock_Disable()                        Quadrature_Decode_Clock_Stop()
#define Quadrature_Decode_Clock_SetDividerRegister(clkDivider, reset)  \
    Quadrature_Decode_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define Quadrature_Decode_Clock_SetDivider(clkDivider)           Quadrature_Decode_Clock_SetDividerRegister((clkDivider), 1u)
#define Quadrature_Decode_Clock_SetDividerValue(clkDivider)      Quadrature_Decode_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Quadrature_Decode_Clock_DIV_ID     Quadrature_Decode_Clock__DIV_ID

#define Quadrature_Decode_Clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Quadrature_Decode_Clock_CTRL_REG   (*(reg32 *)Quadrature_Decode_Clock__CTRL_REGISTER)
#define Quadrature_Decode_Clock_DIV_REG    (*(reg32 *)Quadrature_Decode_Clock__DIV_REGISTER)

#define Quadrature_Decode_Clock_CMD_DIV_SHIFT          (0u)
#define Quadrature_Decode_Clock_CMD_PA_DIV_SHIFT       (8u)
#define Quadrature_Decode_Clock_CMD_DISABLE_SHIFT      (30u)
#define Quadrature_Decode_Clock_CMD_ENABLE_SHIFT       (31u)

#define Quadrature_Decode_Clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Quadrature_Decode_Clock_CMD_DISABLE_SHIFT))
#define Quadrature_Decode_Clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Quadrature_Decode_Clock_CMD_ENABLE_SHIFT))

#define Quadrature_Decode_Clock_DIV_FRAC_MASK  (0x000000F8u)
#define Quadrature_Decode_Clock_DIV_FRAC_SHIFT (3u)
#define Quadrature_Decode_Clock_DIV_INT_MASK   (0xFFFFFF00u)
#define Quadrature_Decode_Clock_DIV_INT_SHIFT  (8u)

#else 

#define Quadrature_Decode_Clock_DIV_REG        (*(reg32 *)Quadrature_Decode_Clock__REGISTER)
#define Quadrature_Decode_Clock_ENABLE_REG     Quadrature_Decode_Clock_DIV_REG
#define Quadrature_Decode_Clock_DIV_FRAC_MASK  Quadrature_Decode_Clock__FRAC_MASK
#define Quadrature_Decode_Clock_DIV_FRAC_SHIFT (16u)
#define Quadrature_Decode_Clock_DIV_INT_MASK   Quadrature_Decode_Clock__DIVIDER_MASK
#define Quadrature_Decode_Clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Quadrature_Decode_Clock_H) */

/* [] END OF FILE */
