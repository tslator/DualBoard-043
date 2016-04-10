/*******************************************************************************
* File Name: HB25_PWM_1.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the HB25_PWM_1
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_HB25_PWM_1_H)
#define CY_TCPWM_HB25_PWM_1_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} HB25_PWM_1_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  HB25_PWM_1_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define HB25_PWM_1_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define HB25_PWM_1_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define HB25_PWM_1_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define HB25_PWM_1_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define HB25_PWM_1_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define HB25_PWM_1_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define HB25_PWM_1_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define HB25_PWM_1_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define HB25_PWM_1_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define HB25_PWM_1_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define HB25_PWM_1_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define HB25_PWM_1_TC_RUN_MODE                    (0lu)
#define HB25_PWM_1_TC_COUNTER_MODE                (0lu)
#define HB25_PWM_1_TC_COMP_CAP_MODE               (2lu)
#define HB25_PWM_1_TC_PRESCALER                   (0lu)

/* Signal modes */
#define HB25_PWM_1_TC_RELOAD_SIGNAL_MODE          (0lu)
#define HB25_PWM_1_TC_COUNT_SIGNAL_MODE           (3lu)
#define HB25_PWM_1_TC_START_SIGNAL_MODE           (0lu)
#define HB25_PWM_1_TC_STOP_SIGNAL_MODE            (0lu)
#define HB25_PWM_1_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define HB25_PWM_1_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define HB25_PWM_1_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define HB25_PWM_1_TC_START_SIGNAL_PRESENT        (0lu)
#define HB25_PWM_1_TC_STOP_SIGNAL_PRESENT         (0lu)
#define HB25_PWM_1_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define HB25_PWM_1_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define HB25_PWM_1_PWM_KILL_EVENT                 (0lu)
#define HB25_PWM_1_PWM_STOP_EVENT                 (0lu)
#define HB25_PWM_1_PWM_MODE                       (4lu)
#define HB25_PWM_1_PWM_OUT_N_INVERT               (0lu)
#define HB25_PWM_1_PWM_OUT_INVERT                 (0lu)
#define HB25_PWM_1_PWM_ALIGN                      (0lu)
#define HB25_PWM_1_PWM_RUN_MODE                   (0lu)
#define HB25_PWM_1_PWM_DEAD_TIME_CYCLE            (0lu)
#define HB25_PWM_1_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define HB25_PWM_1_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define HB25_PWM_1_PWM_COUNT_SIGNAL_MODE          (3lu)
#define HB25_PWM_1_PWM_START_SIGNAL_MODE          (0lu)
#define HB25_PWM_1_PWM_STOP_SIGNAL_MODE           (0lu)
#define HB25_PWM_1_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define HB25_PWM_1_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define HB25_PWM_1_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define HB25_PWM_1_PWM_START_SIGNAL_PRESENT       (0lu)
#define HB25_PWM_1_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define HB25_PWM_1_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define HB25_PWM_1_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define HB25_PWM_1_TC_PERIOD_VALUE                (65535lu)
#define HB25_PWM_1_TC_COMPARE_VALUE               (65535lu)
#define HB25_PWM_1_TC_COMPARE_BUF_VALUE           (65535lu)
#define HB25_PWM_1_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define HB25_PWM_1_PWM_PERIOD_VALUE               (20000lu)
#define HB25_PWM_1_PWM_PERIOD_BUF_VALUE           (65535lu)
#define HB25_PWM_1_PWM_PERIOD_SWAP                (0lu)
#define HB25_PWM_1_PWM_COMPARE_VALUE              (1500lu)
#define HB25_PWM_1_PWM_COMPARE_BUF_VALUE          (65535lu)
#define HB25_PWM_1_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define HB25_PWM_1__LEFT 0
#define HB25_PWM_1__RIGHT 1
#define HB25_PWM_1__CENTER 2
#define HB25_PWM_1__ASYMMETRIC 3

#define HB25_PWM_1__X1 0
#define HB25_PWM_1__X2 1
#define HB25_PWM_1__X4 2

#define HB25_PWM_1__PWM 4
#define HB25_PWM_1__PWM_DT 5
#define HB25_PWM_1__PWM_PR 6

#define HB25_PWM_1__INVERSE 1
#define HB25_PWM_1__DIRECT 0

#define HB25_PWM_1__CAPTURE 2
#define HB25_PWM_1__COMPARE 0

#define HB25_PWM_1__TRIG_LEVEL 3
#define HB25_PWM_1__TRIG_RISING 0
#define HB25_PWM_1__TRIG_FALLING 1
#define HB25_PWM_1__TRIG_BOTH 2

#define HB25_PWM_1__INTR_MASK_TC 1
#define HB25_PWM_1__INTR_MASK_CC_MATCH 2
#define HB25_PWM_1__INTR_MASK_NONE 0
#define HB25_PWM_1__INTR_MASK_TC_CC 3

#define HB25_PWM_1__UNCONFIG 8
#define HB25_PWM_1__TIMER 1
#define HB25_PWM_1__QUAD 3
#define HB25_PWM_1__PWM_SEL 7

#define HB25_PWM_1__COUNT_UP 0
#define HB25_PWM_1__COUNT_DOWN 1
#define HB25_PWM_1__COUNT_UPDOWN0 2
#define HB25_PWM_1__COUNT_UPDOWN1 3


/* Prescaler */
#define HB25_PWM_1_PRESCALE_DIVBY1                ((uint32)(0u << HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_PRESCALE_DIVBY2                ((uint32)(1u << HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_PRESCALE_DIVBY4                ((uint32)(2u << HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_PRESCALE_DIVBY8                ((uint32)(3u << HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_PRESCALE_DIVBY16               ((uint32)(4u << HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_PRESCALE_DIVBY32               ((uint32)(5u << HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_PRESCALE_DIVBY64               ((uint32)(6u << HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_PRESCALE_DIVBY128              ((uint32)(7u << HB25_PWM_1_PRESCALER_SHIFT))

/* TCPWM set modes */
#define HB25_PWM_1_MODE_TIMER_COMPARE             ((uint32)(HB25_PWM_1__COMPARE         <<  \
                                                                  HB25_PWM_1_MODE_SHIFT))
#define HB25_PWM_1_MODE_TIMER_CAPTURE             ((uint32)(HB25_PWM_1__CAPTURE         <<  \
                                                                  HB25_PWM_1_MODE_SHIFT))
#define HB25_PWM_1_MODE_QUAD                      ((uint32)(HB25_PWM_1__QUAD            <<  \
                                                                  HB25_PWM_1_MODE_SHIFT))
#define HB25_PWM_1_MODE_PWM                       ((uint32)(HB25_PWM_1__PWM             <<  \
                                                                  HB25_PWM_1_MODE_SHIFT))
#define HB25_PWM_1_MODE_PWM_DT                    ((uint32)(HB25_PWM_1__PWM_DT          <<  \
                                                                  HB25_PWM_1_MODE_SHIFT))
#define HB25_PWM_1_MODE_PWM_PR                    ((uint32)(HB25_PWM_1__PWM_PR          <<  \
                                                                  HB25_PWM_1_MODE_SHIFT))

/* Quad Modes */
#define HB25_PWM_1_MODE_X1                        ((uint32)(HB25_PWM_1__X1              <<  \
                                                                  HB25_PWM_1_QUAD_MODE_SHIFT))
#define HB25_PWM_1_MODE_X2                        ((uint32)(HB25_PWM_1__X2              <<  \
                                                                  HB25_PWM_1_QUAD_MODE_SHIFT))
#define HB25_PWM_1_MODE_X4                        ((uint32)(HB25_PWM_1__X4              <<  \
                                                                  HB25_PWM_1_QUAD_MODE_SHIFT))

/* Counter modes */
#define HB25_PWM_1_COUNT_UP                       ((uint32)(HB25_PWM_1__COUNT_UP        <<  \
                                                                  HB25_PWM_1_UPDOWN_SHIFT))
#define HB25_PWM_1_COUNT_DOWN                     ((uint32)(HB25_PWM_1__COUNT_DOWN      <<  \
                                                                  HB25_PWM_1_UPDOWN_SHIFT))
#define HB25_PWM_1_COUNT_UPDOWN0                  ((uint32)(HB25_PWM_1__COUNT_UPDOWN0   <<  \
                                                                  HB25_PWM_1_UPDOWN_SHIFT))
#define HB25_PWM_1_COUNT_UPDOWN1                  ((uint32)(HB25_PWM_1__COUNT_UPDOWN1   <<  \
                                                                  HB25_PWM_1_UPDOWN_SHIFT))

/* PWM output invert */
#define HB25_PWM_1_INVERT_LINE                    ((uint32)(HB25_PWM_1__INVERSE         <<  \
                                                                  HB25_PWM_1_INV_OUT_SHIFT))
#define HB25_PWM_1_INVERT_LINE_N                  ((uint32)(HB25_PWM_1__INVERSE         <<  \
                                                                  HB25_PWM_1_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define HB25_PWM_1_TRIG_RISING                    ((uint32)HB25_PWM_1__TRIG_RISING)
#define HB25_PWM_1_TRIG_FALLING                   ((uint32)HB25_PWM_1__TRIG_FALLING)
#define HB25_PWM_1_TRIG_BOTH                      ((uint32)HB25_PWM_1__TRIG_BOTH)
#define HB25_PWM_1_TRIG_LEVEL                     ((uint32)HB25_PWM_1__TRIG_LEVEL)

/* Interrupt mask */
#define HB25_PWM_1_INTR_MASK_TC                   ((uint32)HB25_PWM_1__INTR_MASK_TC)
#define HB25_PWM_1_INTR_MASK_CC_MATCH             ((uint32)HB25_PWM_1__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define HB25_PWM_1_CC_MATCH_SET                   (0x00u)
#define HB25_PWM_1_CC_MATCH_CLEAR                 (0x01u)
#define HB25_PWM_1_CC_MATCH_INVERT                (0x02u)
#define HB25_PWM_1_CC_MATCH_NO_CHANGE             (0x03u)
#define HB25_PWM_1_OVERLOW_SET                    (0x00u)
#define HB25_PWM_1_OVERLOW_CLEAR                  (0x04u)
#define HB25_PWM_1_OVERLOW_INVERT                 (0x08u)
#define HB25_PWM_1_OVERLOW_NO_CHANGE              (0x0Cu)
#define HB25_PWM_1_UNDERFLOW_SET                  (0x00u)
#define HB25_PWM_1_UNDERFLOW_CLEAR                (0x10u)
#define HB25_PWM_1_UNDERFLOW_INVERT               (0x20u)
#define HB25_PWM_1_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define HB25_PWM_1_PWM_MODE_LEFT                  (HB25_PWM_1_CC_MATCH_CLEAR        |   \
                                                         HB25_PWM_1_OVERLOW_SET           |   \
                                                         HB25_PWM_1_UNDERFLOW_NO_CHANGE)
#define HB25_PWM_1_PWM_MODE_RIGHT                 (HB25_PWM_1_CC_MATCH_SET          |   \
                                                         HB25_PWM_1_OVERLOW_NO_CHANGE     |   \
                                                         HB25_PWM_1_UNDERFLOW_CLEAR)
#define HB25_PWM_1_PWM_MODE_ASYM                  (HB25_PWM_1_CC_MATCH_INVERT       |   \
                                                         HB25_PWM_1_OVERLOW_SET           |   \
                                                         HB25_PWM_1_UNDERFLOW_CLEAR)

#if (HB25_PWM_1_CY_TCPWM_V2)
    #if(HB25_PWM_1_CY_TCPWM_4000)
        #define HB25_PWM_1_PWM_MODE_CENTER                (HB25_PWM_1_CC_MATCH_INVERT       |   \
                                                                 HB25_PWM_1_OVERLOW_NO_CHANGE     |   \
                                                                 HB25_PWM_1_UNDERFLOW_CLEAR)
    #else
        #define HB25_PWM_1_PWM_MODE_CENTER                (HB25_PWM_1_CC_MATCH_INVERT       |   \
                                                                 HB25_PWM_1_OVERLOW_SET           |   \
                                                                 HB25_PWM_1_UNDERFLOW_CLEAR)
    #endif /* (HB25_PWM_1_CY_TCPWM_4000) */
#else
    #define HB25_PWM_1_PWM_MODE_CENTER                (HB25_PWM_1_CC_MATCH_INVERT       |   \
                                                             HB25_PWM_1_OVERLOW_NO_CHANGE     |   \
                                                             HB25_PWM_1_UNDERFLOW_CLEAR)
#endif /* (HB25_PWM_1_CY_TCPWM_NEW) */

/* Command operations without condition */
#define HB25_PWM_1_CMD_CAPTURE                    (0u)
#define HB25_PWM_1_CMD_RELOAD                     (8u)
#define HB25_PWM_1_CMD_STOP                       (16u)
#define HB25_PWM_1_CMD_START                      (24u)

/* Status */
#define HB25_PWM_1_STATUS_DOWN                    (1u)
#define HB25_PWM_1_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   HB25_PWM_1_Init(void);
void   HB25_PWM_1_Enable(void);
void   HB25_PWM_1_Start(void);
void   HB25_PWM_1_Stop(void);

void   HB25_PWM_1_SetMode(uint32 mode);
void   HB25_PWM_1_SetCounterMode(uint32 counterMode);
void   HB25_PWM_1_SetPWMMode(uint32 modeMask);
void   HB25_PWM_1_SetQDMode(uint32 qdMode);

void   HB25_PWM_1_SetPrescaler(uint32 prescaler);
void   HB25_PWM_1_TriggerCommand(uint32 mask, uint32 command);
void   HB25_PWM_1_SetOneShot(uint32 oneShotEnable);
uint32 HB25_PWM_1_ReadStatus(void);

void   HB25_PWM_1_SetPWMSyncKill(uint32 syncKillEnable);
void   HB25_PWM_1_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   HB25_PWM_1_SetPWMDeadTime(uint32 deadTime);
void   HB25_PWM_1_SetPWMInvert(uint32 mask);

void   HB25_PWM_1_SetInterruptMode(uint32 interruptMask);
uint32 HB25_PWM_1_GetInterruptSourceMasked(void);
uint32 HB25_PWM_1_GetInterruptSource(void);
void   HB25_PWM_1_ClearInterrupt(uint32 interruptMask);
void   HB25_PWM_1_SetInterrupt(uint32 interruptMask);

void   HB25_PWM_1_WriteCounter(uint32 count);
uint32 HB25_PWM_1_ReadCounter(void);

uint32 HB25_PWM_1_ReadCapture(void);
uint32 HB25_PWM_1_ReadCaptureBuf(void);

void   HB25_PWM_1_WritePeriod(uint32 period);
uint32 HB25_PWM_1_ReadPeriod(void);
void   HB25_PWM_1_WritePeriodBuf(uint32 periodBuf);
uint32 HB25_PWM_1_ReadPeriodBuf(void);

void   HB25_PWM_1_WriteCompare(uint32 compare);
uint32 HB25_PWM_1_ReadCompare(void);
void   HB25_PWM_1_WriteCompareBuf(uint32 compareBuf);
uint32 HB25_PWM_1_ReadCompareBuf(void);

void   HB25_PWM_1_SetPeriodSwap(uint32 swapEnable);
void   HB25_PWM_1_SetCompareSwap(uint32 swapEnable);

void   HB25_PWM_1_SetCaptureMode(uint32 triggerMode);
void   HB25_PWM_1_SetReloadMode(uint32 triggerMode);
void   HB25_PWM_1_SetStartMode(uint32 triggerMode);
void   HB25_PWM_1_SetStopMode(uint32 triggerMode);
void   HB25_PWM_1_SetCountMode(uint32 triggerMode);

void   HB25_PWM_1_SaveConfig(void);
void   HB25_PWM_1_RestoreConfig(void);
void   HB25_PWM_1_Sleep(void);
void   HB25_PWM_1_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define HB25_PWM_1_BLOCK_CONTROL_REG              (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define HB25_PWM_1_BLOCK_CONTROL_PTR              ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define HB25_PWM_1_COMMAND_REG                    (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define HB25_PWM_1_COMMAND_PTR                    ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define HB25_PWM_1_INTRRUPT_CAUSE_REG             (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define HB25_PWM_1_INTRRUPT_CAUSE_PTR             ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define HB25_PWM_1_CONTROL_REG                    (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__CTRL )
#define HB25_PWM_1_CONTROL_PTR                    ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__CTRL )
#define HB25_PWM_1_STATUS_REG                     (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__STATUS )
#define HB25_PWM_1_STATUS_PTR                     ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__STATUS )
#define HB25_PWM_1_COUNTER_REG                    (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__COUNTER )
#define HB25_PWM_1_COUNTER_PTR                    ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__COUNTER )
#define HB25_PWM_1_COMP_CAP_REG                   (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__CC )
#define HB25_PWM_1_COMP_CAP_PTR                   ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__CC )
#define HB25_PWM_1_COMP_CAP_BUF_REG               (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__CC_BUFF )
#define HB25_PWM_1_COMP_CAP_BUF_PTR               ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__CC_BUFF )
#define HB25_PWM_1_PERIOD_REG                     (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__PERIOD )
#define HB25_PWM_1_PERIOD_PTR                     ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__PERIOD )
#define HB25_PWM_1_PERIOD_BUF_REG                 (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define HB25_PWM_1_PERIOD_BUF_PTR                 ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define HB25_PWM_1_TRIG_CONTROL0_REG              (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define HB25_PWM_1_TRIG_CONTROL0_PTR              ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define HB25_PWM_1_TRIG_CONTROL1_REG              (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define HB25_PWM_1_TRIG_CONTROL1_PTR              ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define HB25_PWM_1_TRIG_CONTROL2_REG              (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define HB25_PWM_1_TRIG_CONTROL2_PTR              ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define HB25_PWM_1_INTERRUPT_REQ_REG              (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR )
#define HB25_PWM_1_INTERRUPT_REQ_PTR              ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR )
#define HB25_PWM_1_INTERRUPT_SET_REG              (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR_SET )
#define HB25_PWM_1_INTERRUPT_SET_PTR              ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR_SET )
#define HB25_PWM_1_INTERRUPT_MASK_REG             (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR_MASK )
#define HB25_PWM_1_INTERRUPT_MASK_PTR             ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR_MASK )
#define HB25_PWM_1_INTERRUPT_MASKED_REG           (*(reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR_MASKED )
#define HB25_PWM_1_INTERRUPT_MASKED_PTR           ( (reg32 *) HB25_PWM_1_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define HB25_PWM_1_MASK                           ((uint32)HB25_PWM_1_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define HB25_PWM_1_RELOAD_CC_SHIFT                (0u)
#define HB25_PWM_1_RELOAD_PERIOD_SHIFT            (1u)
#define HB25_PWM_1_PWM_SYNC_KILL_SHIFT            (2u)
#define HB25_PWM_1_PWM_STOP_KILL_SHIFT            (3u)
#define HB25_PWM_1_PRESCALER_SHIFT                (8u)
#define HB25_PWM_1_UPDOWN_SHIFT                   (16u)
#define HB25_PWM_1_ONESHOT_SHIFT                  (18u)
#define HB25_PWM_1_QUAD_MODE_SHIFT                (20u)
#define HB25_PWM_1_INV_OUT_SHIFT                  (20u)
#define HB25_PWM_1_INV_COMPL_OUT_SHIFT            (21u)
#define HB25_PWM_1_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define HB25_PWM_1_RELOAD_CC_MASK                 ((uint32)(HB25_PWM_1_1BIT_MASK        <<  \
                                                                            HB25_PWM_1_RELOAD_CC_SHIFT))
#define HB25_PWM_1_RELOAD_PERIOD_MASK             ((uint32)(HB25_PWM_1_1BIT_MASK        <<  \
                                                                            HB25_PWM_1_RELOAD_PERIOD_SHIFT))
#define HB25_PWM_1_PWM_SYNC_KILL_MASK             ((uint32)(HB25_PWM_1_1BIT_MASK        <<  \
                                                                            HB25_PWM_1_PWM_SYNC_KILL_SHIFT))
#define HB25_PWM_1_PWM_STOP_KILL_MASK             ((uint32)(HB25_PWM_1_1BIT_MASK        <<  \
                                                                            HB25_PWM_1_PWM_STOP_KILL_SHIFT))
#define HB25_PWM_1_PRESCALER_MASK                 ((uint32)(HB25_PWM_1_8BIT_MASK        <<  \
                                                                            HB25_PWM_1_PRESCALER_SHIFT))
#define HB25_PWM_1_UPDOWN_MASK                    ((uint32)(HB25_PWM_1_2BIT_MASK        <<  \
                                                                            HB25_PWM_1_UPDOWN_SHIFT))
#define HB25_PWM_1_ONESHOT_MASK                   ((uint32)(HB25_PWM_1_1BIT_MASK        <<  \
                                                                            HB25_PWM_1_ONESHOT_SHIFT))
#define HB25_PWM_1_QUAD_MODE_MASK                 ((uint32)(HB25_PWM_1_3BIT_MASK        <<  \
                                                                            HB25_PWM_1_QUAD_MODE_SHIFT))
#define HB25_PWM_1_INV_OUT_MASK                   ((uint32)(HB25_PWM_1_2BIT_MASK        <<  \
                                                                            HB25_PWM_1_INV_OUT_SHIFT))
#define HB25_PWM_1_MODE_MASK                      ((uint32)(HB25_PWM_1_3BIT_MASK        <<  \
                                                                            HB25_PWM_1_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define HB25_PWM_1_CAPTURE_SHIFT                  (0u)
#define HB25_PWM_1_COUNT_SHIFT                    (2u)
#define HB25_PWM_1_RELOAD_SHIFT                   (4u)
#define HB25_PWM_1_STOP_SHIFT                     (6u)
#define HB25_PWM_1_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define HB25_PWM_1_CAPTURE_MASK                   ((uint32)(HB25_PWM_1_2BIT_MASK        <<  \
                                                                  HB25_PWM_1_CAPTURE_SHIFT))
#define HB25_PWM_1_COUNT_MASK                     ((uint32)(HB25_PWM_1_2BIT_MASK        <<  \
                                                                  HB25_PWM_1_COUNT_SHIFT))
#define HB25_PWM_1_RELOAD_MASK                    ((uint32)(HB25_PWM_1_2BIT_MASK        <<  \
                                                                  HB25_PWM_1_RELOAD_SHIFT))
#define HB25_PWM_1_STOP_MASK                      ((uint32)(HB25_PWM_1_2BIT_MASK        <<  \
                                                                  HB25_PWM_1_STOP_SHIFT))
#define HB25_PWM_1_START_MASK                     ((uint32)(HB25_PWM_1_2BIT_MASK        <<  \
                                                                  HB25_PWM_1_START_SHIFT))

/* MASK */
#define HB25_PWM_1_1BIT_MASK                      ((uint32)0x01u)
#define HB25_PWM_1_2BIT_MASK                      ((uint32)0x03u)
#define HB25_PWM_1_3BIT_MASK                      ((uint32)0x07u)
#define HB25_PWM_1_6BIT_MASK                      ((uint32)0x3Fu)
#define HB25_PWM_1_8BIT_MASK                      ((uint32)0xFFu)
#define HB25_PWM_1_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define HB25_PWM_1_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define HB25_PWM_1_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(HB25_PWM_1_QUAD_ENCODING_MODES     << HB25_PWM_1_QUAD_MODE_SHIFT))       |\
         ((uint32)(HB25_PWM_1_CONFIG                  << HB25_PWM_1_MODE_SHIFT)))

#define HB25_PWM_1_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(HB25_PWM_1_PWM_STOP_EVENT          << HB25_PWM_1_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(HB25_PWM_1_PWM_OUT_INVERT          << HB25_PWM_1_INV_OUT_SHIFT))         |\
         ((uint32)(HB25_PWM_1_PWM_OUT_N_INVERT        << HB25_PWM_1_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(HB25_PWM_1_PWM_MODE                << HB25_PWM_1_MODE_SHIFT)))

#define HB25_PWM_1_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(HB25_PWM_1_PWM_RUN_MODE         << HB25_PWM_1_ONESHOT_SHIFT))
            
#define HB25_PWM_1_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(HB25_PWM_1_PWM_ALIGN            << HB25_PWM_1_UPDOWN_SHIFT))

#define HB25_PWM_1_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(HB25_PWM_1_PWM_KILL_EVENT      << HB25_PWM_1_PWM_SYNC_KILL_SHIFT))

#define HB25_PWM_1_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(HB25_PWM_1_PWM_DEAD_TIME_CYCLE  << HB25_PWM_1_PRESCALER_SHIFT))

#define HB25_PWM_1_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(HB25_PWM_1_PWM_PRESCALER        << HB25_PWM_1_PRESCALER_SHIFT))

#define HB25_PWM_1_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(HB25_PWM_1_TC_PRESCALER            << HB25_PWM_1_PRESCALER_SHIFT))       |\
         ((uint32)(HB25_PWM_1_TC_COUNTER_MODE         << HB25_PWM_1_UPDOWN_SHIFT))          |\
         ((uint32)(HB25_PWM_1_TC_RUN_MODE             << HB25_PWM_1_ONESHOT_SHIFT))         |\
         ((uint32)(HB25_PWM_1_TC_COMP_CAP_MODE        << HB25_PWM_1_MODE_SHIFT)))
        
#define HB25_PWM_1_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(HB25_PWM_1_QUAD_PHIA_SIGNAL_MODE   << HB25_PWM_1_COUNT_SHIFT))           |\
         ((uint32)(HB25_PWM_1_QUAD_INDEX_SIGNAL_MODE  << HB25_PWM_1_RELOAD_SHIFT))          |\
         ((uint32)(HB25_PWM_1_QUAD_STOP_SIGNAL_MODE   << HB25_PWM_1_STOP_SHIFT))            |\
         ((uint32)(HB25_PWM_1_QUAD_PHIB_SIGNAL_MODE   << HB25_PWM_1_START_SHIFT)))

#define HB25_PWM_1_PWM_SIGNALS_MODES                                                              \
        (((uint32)(HB25_PWM_1_PWM_SWITCH_SIGNAL_MODE  << HB25_PWM_1_CAPTURE_SHIFT))         |\
         ((uint32)(HB25_PWM_1_PWM_COUNT_SIGNAL_MODE   << HB25_PWM_1_COUNT_SHIFT))           |\
         ((uint32)(HB25_PWM_1_PWM_RELOAD_SIGNAL_MODE  << HB25_PWM_1_RELOAD_SHIFT))          |\
         ((uint32)(HB25_PWM_1_PWM_STOP_SIGNAL_MODE    << HB25_PWM_1_STOP_SHIFT))            |\
         ((uint32)(HB25_PWM_1_PWM_START_SIGNAL_MODE   << HB25_PWM_1_START_SHIFT)))

#define HB25_PWM_1_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(HB25_PWM_1_TC_CAPTURE_SIGNAL_MODE  << HB25_PWM_1_CAPTURE_SHIFT))         |\
         ((uint32)(HB25_PWM_1_TC_COUNT_SIGNAL_MODE    << HB25_PWM_1_COUNT_SHIFT))           |\
         ((uint32)(HB25_PWM_1_TC_RELOAD_SIGNAL_MODE   << HB25_PWM_1_RELOAD_SHIFT))          |\
         ((uint32)(HB25_PWM_1_TC_STOP_SIGNAL_MODE     << HB25_PWM_1_STOP_SHIFT))            |\
         ((uint32)(HB25_PWM_1_TC_START_SIGNAL_MODE    << HB25_PWM_1_START_SHIFT)))
        
#define HB25_PWM_1_TIMER_UPDOWN_CNT_USED                                                          \
                ((HB25_PWM_1__COUNT_UPDOWN0 == HB25_PWM_1_TC_COUNTER_MODE)                  ||\
                 (HB25_PWM_1__COUNT_UPDOWN1 == HB25_PWM_1_TC_COUNTER_MODE))

#define HB25_PWM_1_PWM_UPDOWN_CNT_USED                                                            \
                ((HB25_PWM_1__CENTER == HB25_PWM_1_PWM_ALIGN)                               ||\
                 (HB25_PWM_1__ASYMMETRIC == HB25_PWM_1_PWM_ALIGN))               
        
#define HB25_PWM_1_PWM_PR_INIT_VALUE              (1u)
#define HB25_PWM_1_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_HB25_PWM_1_H */

/* [] END OF FILE */
