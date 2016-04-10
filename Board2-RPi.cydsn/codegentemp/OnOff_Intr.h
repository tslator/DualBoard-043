/*******************************************************************************
* File Name: OnOff_Intr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_OnOff_Intr_H)
#define CY_ISR_OnOff_Intr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void OnOff_Intr_Start(void);
void OnOff_Intr_StartEx(cyisraddress address);
void OnOff_Intr_Stop(void);

CY_ISR_PROTO(OnOff_Intr_Interrupt);

void OnOff_Intr_SetVector(cyisraddress address);
cyisraddress OnOff_Intr_GetVector(void);

void OnOff_Intr_SetPriority(uint8 priority);
uint8 OnOff_Intr_GetPriority(void);

void OnOff_Intr_Enable(void);
uint8 OnOff_Intr_GetState(void);
void OnOff_Intr_Disable(void);

void OnOff_Intr_SetPending(void);
void OnOff_Intr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the OnOff_Intr ISR. */
#define OnOff_Intr_INTC_VECTOR            ((reg32 *) OnOff_Intr__INTC_VECT)

/* Address of the OnOff_Intr ISR priority. */
#define OnOff_Intr_INTC_PRIOR             ((reg32 *) OnOff_Intr__INTC_PRIOR_REG)

/* Priority of the OnOff_Intr interrupt. */
#define OnOff_Intr_INTC_PRIOR_NUMBER      OnOff_Intr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable OnOff_Intr interrupt. */
#define OnOff_Intr_INTC_SET_EN            ((reg32 *) OnOff_Intr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the OnOff_Intr interrupt. */
#define OnOff_Intr_INTC_CLR_EN            ((reg32 *) OnOff_Intr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the OnOff_Intr interrupt state to pending. */
#define OnOff_Intr_INTC_SET_PD            ((reg32 *) OnOff_Intr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the OnOff_Intr interrupt. */
#define OnOff_Intr_INTC_CLR_PD            ((reg32 *) OnOff_Intr__INTC_CLR_PD_REG)



#endif /* CY_ISR_OnOff_Intr_H */


/* [] END OF FILE */
