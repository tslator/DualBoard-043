/*******************************************************************************
* File Name: PWM_1MHz_1.h
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

#if !defined(CY_CLOCK_PWM_1MHz_1_H)
#define CY_CLOCK_PWM_1MHz_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void PWM_1MHz_1_StartEx(uint32 alignClkDiv);
#define PWM_1MHz_1_Start() \
    PWM_1MHz_1_StartEx(PWM_1MHz_1__PA_DIV_ID)

#else

void PWM_1MHz_1_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void PWM_1MHz_1_Stop(void);

void PWM_1MHz_1_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 PWM_1MHz_1_GetDividerRegister(void);
uint8  PWM_1MHz_1_GetFractionalDividerRegister(void);

#define PWM_1MHz_1_Enable()                         PWM_1MHz_1_Start()
#define PWM_1MHz_1_Disable()                        PWM_1MHz_1_Stop()
#define PWM_1MHz_1_SetDividerRegister(clkDivider, reset)  \
    PWM_1MHz_1_SetFractionalDividerRegister((clkDivider), 0u)
#define PWM_1MHz_1_SetDivider(clkDivider)           PWM_1MHz_1_SetDividerRegister((clkDivider), 1u)
#define PWM_1MHz_1_SetDividerValue(clkDivider)      PWM_1MHz_1_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define PWM_1MHz_1_DIV_ID     PWM_1MHz_1__DIV_ID

#define PWM_1MHz_1_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define PWM_1MHz_1_CTRL_REG   (*(reg32 *)PWM_1MHz_1__CTRL_REGISTER)
#define PWM_1MHz_1_DIV_REG    (*(reg32 *)PWM_1MHz_1__DIV_REGISTER)

#define PWM_1MHz_1_CMD_DIV_SHIFT          (0u)
#define PWM_1MHz_1_CMD_PA_DIV_SHIFT       (8u)
#define PWM_1MHz_1_CMD_DISABLE_SHIFT      (30u)
#define PWM_1MHz_1_CMD_ENABLE_SHIFT       (31u)

#define PWM_1MHz_1_CMD_DISABLE_MASK       ((uint32)((uint32)1u << PWM_1MHz_1_CMD_DISABLE_SHIFT))
#define PWM_1MHz_1_CMD_ENABLE_MASK        ((uint32)((uint32)1u << PWM_1MHz_1_CMD_ENABLE_SHIFT))

#define PWM_1MHz_1_DIV_FRAC_MASK  (0x000000F8u)
#define PWM_1MHz_1_DIV_FRAC_SHIFT (3u)
#define PWM_1MHz_1_DIV_INT_MASK   (0xFFFFFF00u)
#define PWM_1MHz_1_DIV_INT_SHIFT  (8u)

#else 

#define PWM_1MHz_1_DIV_REG        (*(reg32 *)PWM_1MHz_1__REGISTER)
#define PWM_1MHz_1_ENABLE_REG     PWM_1MHz_1_DIV_REG
#define PWM_1MHz_1_DIV_FRAC_MASK  PWM_1MHz_1__FRAC_MASK
#define PWM_1MHz_1_DIV_FRAC_SHIFT (16u)
#define PWM_1MHz_1_DIV_INT_MASK   PWM_1MHz_1__DIVIDER_MASK
#define PWM_1MHz_1_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_PWM_1MHz_1_H) */

/* [] END OF FILE */
