/*******************************************************************************
* File Name: ADC_Infrared.h
* Version 2.30
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Sequencing Successive Approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ADC_SAR_SEQ_ADC_Infrared_H)
#define CY_ADC_SAR_SEQ_ADC_Infrared_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} ADC_Infrared_BACKUP_STRUCT;


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Clock Source setting constants */
#define ADC_Infrared__EXTERNAL 0
#define ADC_Infrared__INTERNAL 1

/*  Sample Mode setting constants */
#define ADC_Infrared__FREERUNNING 0
#define ADC_Infrared__HARDWARESOC 1

/*  Reference type setting constants */
#define ADC_Infrared__VDDA_2 0
#define ADC_Infrared__VDDA 1
#define ADC_Infrared__INTERNAL1024 2
#define ADC_Infrared__INTERNAL1024BYPASSED 3
#define ADC_Infrared__INTERNALVREF 4
#define ADC_Infrared__INTERNALVREFBYPASSED 5
#define ADC_Infrared__VDDA_2BYPASSED 6
#define ADC_Infrared__EXTERNALVREF 7

/* Input buffer gain setting constants */
#define ADC_Infrared__DISABLED 0
#define ADC_Infrared__ONE 1
#define ADC_Infrared__TWO 2
#define ADC_Infrared__FOUR 3
#define ADC_Infrared__EIGHT 4
#define ADC_Infrared__SIXTEEN 5

/* Negative input setting sonstants in single ended mode */
#define ADC_Infrared__VSS 0
#define ADC_Infrared__VREF 1
#define ADC_Infrared__OTHER 2

/* Compare mode setting constants:
*    Mode0 - Disable
*    Mode1 - Result < Low_Limit
*    Mode2 - Low_Limit <= Result < High_Limit
*    Mode3 - High_Limit <= Result
*    Mode4 - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define ADC_Infrared__MODE0 0
#define ADC_Infrared__MODE1 1
#define ADC_Infrared__MODE2 2
#define ADC_Infrared__MODE3 3

#define ADC_Infrared__RES8 0
#define ADC_Infrared__RES10 1

#define ADC_Infrared__RIGHT 0
#define ADC_Infrared__LEFT 1

#define ADC_Infrared__FSIGNED 1
#define ADC_Infrared__FUNSIGNED 0

#define ADC_Infrared__ACCUMULATE 0
#define ADC_Infrared__FIXEDRESOLUTION 1



/***************************************
*   Conditional Compilation Parameters
****************************************/ 

#define ADC_Infrared_CY_SAR_IP_VER0               	(0u)
#define ADC_Infrared_CY_SAR_IP_VER1               	(1u)

#if (CY_PSOC4_4100 || CY_PSOC4_4200)
    #define ADC_Infrared_CY_SAR_IP_VER              (ADC_Infrared_CY_SAR_IP_VER0)
#else /* Other devices */
    #define ADC_Infrared_CY_SAR_IP_VER              (ADC_Infrared_CY_SAR_IP_VER1)
#endif  /* (CY_PSOC4_4100 || CY_PSOC4_4200) */


/***************************************
*    Initial Parameter Constants
***************************************/
#define ADC_Infrared_DEFAULT_SAMPLE_MODE_SEL        (0u)
#define ADC_Infrared_DEFAULT_VREF_SEL               (7u)
#define ADC_Infrared_DEFAULT_NEG_INPUT_SEL          (1u)
#define ADC_Infrared_DEFAULT_ALT_RESOLUTION_SEL     (0u)
#define ADC_Infrared_DEFAULT_JUSTIFICATION_SEL      (0u)
#define ADC_Infrared_DEFAULT_DIFF_RESULT_FORMAT_SEL (0u)
#define ADC_Infrared_DEFAULT_SE_RESULT_FORMAT_SEL   (0u)
#define ADC_Infrared_DEFAULT_CLOCK_SOURCE           (1u)
#define ADC_Infrared_DEFAULT_VREF_MV_VALUE          (2500)
#define ADC_Infrared_DEFAULT_BUFFER_GAIN            (0u)
#define ADC_Infrared_DEFAULT_AVG_SAMPLES_NUM        (0u)
#define ADC_Infrared_DEFAULT_AVG_SAMPLES_DIV        (int16)(0x100u >> (7u - 0u))
#define ADC_Infrared_DEFAULT_AVG_MODE               (1u)
#define ADC_Infrared_MAX_RESOLUTION                 (12u)
#define ADC_Infrared_DEFAULT_LOW_LIMIT              (0u)
#define ADC_Infrared_DEFAULT_HIGH_LIMIT             (2047u)
#define ADC_Infrared_DEFAULT_COMPARE_MODE           (0u)
#define ADC_Infrared_DEFAULT_ACLKS_NUM              (4u)
#define ADC_Infrared_DEFAULT_BCLKS_NUM              (4u)
#define ADC_Infrared_DEFAULT_CCLKS_NUM              (4u)
#define ADC_Infrared_DEFAULT_DCLKS_NUM              (4u)
#define ADC_Infrared_TOTAL_CHANNELS_NUM             (4u)
#define ADC_Infrared_SEQUENCED_CHANNELS_NUM         (4u)
#define ADC_Infrared_DEFAULT_EN_CHANNELS            (15u)
#define ADC_Infrared_NOMINAL_CLOCK_FREQ             (1000000)
#define ADC_Infrared_INJ_CHANNEL_ENABLED            (0u)
#define ADC_Infrared_IRQ_REMOVE                     (0u)

/* Determines whether the configuration contains external negative input. */
#define ADC_Infrared_SINGLE_PRESENT                 (0u)
#define ADC_Infrared_CHANNELS_MODE                  (0u)
#define ADC_Infrared_MAX_CHANNELS_EN_MASK           (0xffffu >> (16u - ADC_Infrared_SEQUENCED_CHANNELS_NUM))


/***************************************
*        Function Prototypes
***************************************/

void ADC_Infrared_Start(void);
void ADC_Infrared_Stop(void);
void ADC_Infrared_Init(void);
void ADC_Infrared_Enable(void);
void ADC_Infrared_StartConvert(void);
void ADC_Infrared_StopConvert(void);
uint32 ADC_Infrared_IsEndConversion(uint32 retMode);
int16 ADC_Infrared_GetResult16(uint32 chan);
void ADC_Infrared_SetChanMask(uint32 mask);
void ADC_Infrared_SetLowLimit(uint32 lowLimit);
void ADC_Infrared_SetHighLimit(uint32 highLimit);
void ADC_Infrared_SetLimitMask(uint32 mask);
void ADC_Infrared_SetSatMask(uint32 mask);
void ADC_Infrared_SetOffset(uint32 chan, int16 offset);
void ADC_Infrared_SetGain(uint32 chan, int32 adcGain);
#if(ADC_Infrared_INJ_CHANNEL_ENABLED)
    void ADC_Infrared_EnableInjection(void);
#endif /* ADC_Infrared_INJ_CHANNEL_ENABLED */
#if(ADC_Infrared_DEFAULT_JUSTIFICATION_SEL == ADC_Infrared__RIGHT)
    int16 ADC_Infrared_CountsTo_mVolts(uint32 chan, int16 adcCounts);
    int32 ADC_Infrared_CountsTo_uVolts(uint32 chan, int16 adcCounts);
    float32 ADC_Infrared_CountsTo_Volts(uint32 chan, int16 adcCounts);
#endif /* End ADC_Infrared_DEFAULT_JUSTIFICATION_SEL == ADC_Infrared__RIGHT */
void ADC_Infrared_Sleep(void);
void ADC_Infrared_Wakeup(void);
void ADC_Infrared_SaveConfig(void);
void ADC_Infrared_RestoreConfig(void);

CY_ISR_PROTO( ADC_Infrared_ISR );


/**************************************
*           API Constants
**************************************/
/* Constants for Sleep mode states */
#define ADC_Infrared_DISABLED                   (0x00u)
#define ADC_Infrared_ENABLED                    (0x01u)
#define ADC_Infrared_STARTED                    (0x02u)
#define ADC_Infrared_BOOSTPUMP_ENABLED          (0x04u)

/*   Constants for IsEndConversion() "retMode" parameter  */
#define ADC_Infrared_RETURN_STATUS              (0x01u)
#define ADC_Infrared_WAIT_FOR_RESULT            (0x02u)
#define ADC_Infrared_RETURN_STATUS_INJ          (0x04u)
#define ADC_Infrared_WAIT_FOR_RESULT_INJ        (0x08u)

#define ADC_Infrared_MAX_FREQUENCY              (18000000)       /*18Mhz*/

#define ADC_Infrared_RESOLUTION_12              (12u)
#define ADC_Infrared_RESOLUTION_10              (10u)
#define ADC_Infrared_RESOLUTION_8               (8u)

#define ADC_Infrared_10US_DELAY                 (10u)

#define ADC_Infrared_10V_COUNTS                 (10.0F)
#define ADC_Infrared_10MV_COUNTS                (10000)
#define ADC_Infrared_10UV_COUNTS                (10000000L)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 ADC_Infrared_initVar;
extern volatile int16 ADC_Infrared_offset[ADC_Infrared_TOTAL_CHANNELS_NUM];
extern volatile int32 ADC_Infrared_countsPer10Volt[ADC_Infrared_TOTAL_CHANNELS_NUM];


/***************************************
*              Registers
***************************************/

#define ADC_Infrared_SAR_CTRL_REG                (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_CTRL )
#define ADC_Infrared_SAR_CTRL_PTR                ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_CTRL )

#define ADC_Infrared_SAR_SAMPLE_CTRL_REG         (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SAMPLE_CTRL )
#define ADC_Infrared_SAR_SAMPLE_CTRL_PTR         ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SAMPLE_CTRL )

#define ADC_Infrared_SAR_SAMPLE_TIME01_REG       (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SAMPLE_TIME01 )
#define ADC_Infrared_SAR_SAMPLE_TIME01_PTR       ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SAMPLE_TIME01 )

#define ADC_Infrared_SAR_SAMPLE_TIME23_REG       (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SAMPLE_TIME23 )
#define ADC_Infrared_SAR_SAMPLE_TIME23_PTR       ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SAMPLE_TIME23 )

#define ADC_Infrared_SAR_RANGE_THRES_REG         (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_THRES )
#define ADC_Infrared_SAR_RANGE_THRES_PTR         ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_THRES )

#define ADC_Infrared_SAR_RANGE_COND_REG          (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_COND )
#define ADC_Infrared_SAR_RANGE_COND_PTR          ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_COND )

#define ADC_Infrared_SAR_CHAN_EN_REG             (*(reg32 *) CYREG_SAR_CHAN_EN )
#define ADC_Infrared_SAR_CHAN_EN_PTR             ( (reg32 *) CYREG_SAR_CHAN_EN )

#define ADC_Infrared_SAR_START_CTRL_REG          (*(reg32 *) CYREG_SAR_START_CTRL )
#define ADC_Infrared_SAR_START_CTRL_PTR          ( (reg32 *) CYREG_SAR_START_CTRL )

#define ADC_Infrared_SAR_DFT_CTRL_REG            (*(reg32 *) CYREG_SAR_DFT_CTRL )
#define ADC_Infrared_SAR_DFT_CTRL_PTR            ( (reg32 *) CYREG_SAR_DFT_CTRL )

#define ADC_Infrared_SAR_CHAN_CONFIG_REG         (*(reg32 *) CYREG_SAR_CHAN_CONFIG00 )
#define ADC_Infrared_SAR_CHAN_CONFIG_PTR         ( (reg32 *) CYREG_SAR_CHAN_CONFIG00 )
#define ADC_Infrared_SAR_CHAN_CONFIG_IND         CYREG_SAR_CHAN_CONFIG00

#define ADC_Infrared_SAR_CHAN_WORK_REG           (*(reg32 *) CYREG_SAR_CHAN_WORK00 )
#define ADC_Infrared_SAR_CHAN_WORK_PTR           ( (reg32 *) CYREG_SAR_CHAN_WORK00 )

#define ADC_Infrared_SAR_CHAN_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT00 )
#define ADC_Infrared_SAR_CHAN_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT00 )
#define ADC_Infrared_SAR_CHAN_RESULT_IND         CYREG_SAR_CHAN_RESULT00

#define ADC_Infrared_SAR_CHAN0_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT00 )
#define ADC_Infrared_SAR_CHAN0_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT00 )

#define ADC_Infrared_SAR_CHAN1_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT01 )
#define ADC_Infrared_SAR_CHAN1_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT01 )

#define ADC_Infrared_SAR_CHAN2_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT02 )
#define ADC_Infrared_SAR_CHAN2_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT02 )

#define ADC_Infrared_SAR_CHAN3_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT03 )
#define ADC_Infrared_SAR_CHAN3_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT03 )

#define ADC_Infrared_SAR_CHAN4_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT04 )
#define ADC_Infrared_SAR_CHAN4_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT04 )

#define ADC_Infrared_SAR_CHAN5_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT05 )
#define ADC_Infrared_SAR_CHAN5_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT05 )

#define ADC_Infrared_SAR_CHAN6_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT06 )
#define ADC_Infrared_SAR_CHAN6_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT06 )

#define ADC_Infrared_SAR_CHAN7_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT07 )
#define ADC_Infrared_SAR_CHAN7_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT07 )

#if(ADC_Infrared_CY_SAR_IP_VER != ADC_Infrared_CY_SAR_IP_VER0)
    #define ADC_Infrared_SAR_CHAN8_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT08 )
    #define ADC_Infrared_SAR_CHAN8_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT08 )

    #define ADC_Infrared_SAR_CHAN9_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT09 )
    #define ADC_Infrared_SAR_CHAN9_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT09 )

    #define ADC_Infrared_SAR_CHAN10_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT010 )
    #define ADC_Infrared_SAR_CHAN10_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT010 )

    #define ADC_Infrared_SAR_CHAN11_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT011 )
    #define ADC_Infrared_SAR_CHAN11_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT011 )

    #define ADC_Infrared_SAR_CHAN12_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT012 )
    #define ADC_Infrared_SAR_CHAN12_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT012 )

    #define ADC_Infrared_SAR_CHAN13_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT013 )
    #define ADC_Infrared_SAR_CHAN13_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT013 )

    #define ADC_Infrared_SAR_CHAN14_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT014 )
    #define ADC_Infrared_SAR_CHAN14_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT014 )

    #define ADC_Infrared_SAR_CHAN15_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT015 )
    #define ADC_Infrared_SAR_CHAN15_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT015 )
#endif /* (ADC_Infrared_CY_SAR_IP_VER != ADC_Infrared_CY_SAR_IP_VER0) */

#define ADC_Infrared_SAR_CHAN_WORK_VALID_REG     (*(reg32 *) CYREG_SAR_CHAN_WORK_VALID)
#define ADC_Infrared_SAR_CHAN_WORK_VALID_PTR     ( (reg32 *) CYREG_SAR_CHAN_WORK_VALID)

#define ADC_Infrared_SAR_CHAN_RESULT_VALID_REG   ( *(reg32 *) CYREG_SAR_CHAN_RESULT_VALID )
#define ADC_Infrared_SAR_CHAN_RESULT_VALID_PTR   ( (reg32 *) CYREG_SAR_CHAN_RESULT_VALID )

#define ADC_Infrared_SAR_STATUS_REG              (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_STATUS )
#define ADC_Infrared_SAR_STATUS_PTR              ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_STATUS )

#define ADC_Infrared_SAR_AVG_START_REG           (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_AVG_STAT )
#define ADC_Infrared_SAR_AVG_START_PTR           ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_AVG_STAT )

#define ADC_Infrared_SAR_INTR_REG                (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR )
#define ADC_Infrared_SAR_INTR_PTR                ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR )

#define ADC_Infrared_SAR_INTR_SET_REG            (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_SET )
#define ADC_Infrared_SAR_INTR_SET_PTR            ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_SET )

#define ADC_Infrared_SAR_INTR_MASK_REG           (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_MASK )
#define ADC_Infrared_SAR_INTR_MASK_PTR           ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_MASK )

#define ADC_Infrared_SAR_INTR_MASKED_REG         (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_MASKED )
#define ADC_Infrared_SAR_INTR_MASKED_PTR         ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_MASKED )

#define ADC_Infrared_SAR_SATURATE_INTR_REG       (*(reg32 *) CYREG_SAR_SATURATE_INTR )
#define ADC_Infrared_SAR_SATURATE_INTR_PTR       ( (reg32 *) CYREG_SAR_SATURATE_INTR )

#define ADC_Infrared_SAR_SATURATE_INTR_SET_REG   (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SATURATE_INTR_SET )
#define ADC_Infrared_SAR_SATURATE_INTR_SET_PTR   ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SATURATE_INTR_SET )

#define ADC_Infrared_SAR_SATURATE_INTR_MASK_REG  (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )
#define ADC_Infrared_SAR_SATURATE_INTR_MASK_PTR  ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )

#define ADC_Infrared_SAR_SATURATE_INTR_MASKED_REG \
                                                 (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )
#define ADC_Infrared_SAR_SATURATE_INTR_MASKED_PTR \
                                                 ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )

#define ADC_Infrared_SAR_RANGE_INTR_REG          (*(reg32 *) CYREG_SAR_RANGE_INTR )
#define ADC_Infrared_SAR_RANGE_INTR_PTR          ( (reg32 *) CYREG_SAR_RANGE_INTR )

#define ADC_Infrared_SAR_RANGE_INTR_SET_REG      (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_INTR_SET )
#define ADC_Infrared_SAR_RANGE_INTR_SET_PTR      ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_INTR_SET )

#define ADC_Infrared_SAR_RANGE_INTR_MASK_REG     (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_INTR_MASK )
#define ADC_Infrared_SAR_RANGE_INTR_MASK_PTR     ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_INTR_MASK )

#define ADC_Infrared_SAR_RANGE_INTR_MASKED_REG   (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )
#define ADC_Infrared_SAR_RANGE_INTR_MASKED_PTR   ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )

#define ADC_Infrared_SAR_INTR_CAUSE_REG          (*(reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_CAUSE )
#define ADC_Infrared_SAR_INTR_CAUSE_PTR          ( (reg32 *) ADC_Infrared_cy_psoc4_sar__SAR_INTR_CAUSE )

#define ADC_Infrared_SAR_INJ_CHAN_CONFIG_REG     (*(reg32 *) CYREG_SAR_INJ_CHAN_CONFIG)
#define ADC_Infrared_SAR_INJ_CHAN_CONFIG_PTR     ( (reg32 *) CYREG_SAR_INJ_CHAN_CONFIG)

#define ADC_Infrared_SAR_INJ_RESULT_REG          (*(reg32 *) CYREG_SAR_INJ_RESULT )
#define ADC_Infrared_SAR_INJ_RESULT_PTR          ( (reg32 *) CYREG_SAR_INJ_RESULT )

#define ADC_Infrared_MUX_SWITCH0_REG             (*(reg32 *)  CYREG_SAR_MUX_SWITCH0 )
#define ADC_Infrared_MUX_SWITCH0_PTR             ( (reg32 *)  CYREG_SAR_MUX_SWITCH0 )

#define ADC_Infrared_MUX_SWITCH_HW_CTRL_REG      (*(reg32 *)  CYREG_SAR_MUX_SWITCH_HW_CTRL )
#define ADC_Infrared_MUX_SWITCH_HW_CTRL_PTR      ( (reg32 *)  CYREG_SAR_MUX_SWITCH_HW_CTRL )

#define ADC_Infrared_PUMP_CTRL_REG               (*(reg32 *)  CYREG_SAR_PUMP_CTRL )
#define ADC_Infrared_PUMP_CTRL_PTR               ( (reg32 *)  CYREG_SAR_PUMP_CTRL )

#define ADC_Infrared_ANA_TRIM_REG                (*(reg32 *)  CYREG_SAR_ANA_TRIM )
#define ADC_Infrared_ANA_TRIM_PTR                ( (reg32 *)  CYREG_SAR_ANA_TRIM )

#define ADC_Infrared_WOUNDING_REG                (*(reg32 *)  CYREG_SAR_WOUNDING )
#define ADC_Infrared_WOUNDING_PTR                ( (reg32 *)  CYREG_SAR_WOUNDING )


/**************************************
*       Register Constants
**************************************/
#define ADC_Infrared_INTC_NUMBER                (ADC_Infrared_IRQ__INTC_NUMBER)
#define ADC_Infrared_INTC_PRIOR_NUMBER          (ADC_Infrared_IRQ__INTC_PRIOR_NUM)

/* defines for CTRL register */
#define ADC_Infrared_VREF_INTERNAL1024          (0x00000040Lu)
#define ADC_Infrared_VREF_EXTERNAL              (0x00000050Lu)
#define ADC_Infrared_VREF_VDDA_2                (0x00000060Lu)
#define ADC_Infrared_VREF_VDDA                  (0x00000070Lu)
#define ADC_Infrared_VREF_INTERNAL1024BYPASSED  (0x000000C0Lu)
#define ADC_Infrared_VREF_VDDA_2BYPASSED        (0x000000E0Lu)
#define ADC_Infrared_VREF_INTERNALVREF          (0x00000000Lu)
#define ADC_Infrared_VREF_INTERNALVREFBYPASSED  (0x00000000Lu)

#define ADC_Infrared_NEG_VSSA_KELVIN            (0x00000000Lu)
#define ADC_Infrared_NEG_VSSA                   (0x00000200Lu)
#define ADC_Infrared_NEG_VREF                   (0x00000E00Lu)
#if(ADC_Infrared_TOTAL_CHANNELS_NUM > 1u)
    #define ADC_Infrared_NEG_OTHER              (uint16)((uint16)ADC_Infrared_cy_psoc4_sarmux_8__VNEG << 9u)
#else
    #define ADC_Infrared_NEG_OTHER              (0)
#endif /* ADC_Infrared_TOTAL_CHANNELS_NUM > 1u */

#define ADC_Infrared_SAR_HW_CTRL_NEGVREF        (0x00002000Lu)

#define ADC_Infrared_BOOSTPUMP_EN               (0x00100000Lu)

#define ADC_Infrared_NORMAL_PWR                 (0x00000000Lu)
#define ADC_Infrared_HALF_PWR                   (0x01000000Lu)
#define ADC_Infrared_MORE_PWR                   (0x02000000Lu)
#define ADC_Infrared_QUARTER_PWR                (0x03000000Lu)
#define ADC_Infrared_DEEPSLEEP_ON               (0x08000000Lu)

#define ADC_Infrared_DSI_SYNC_CONFIG            (0x10000000Lu)
#define ADC_Infrared_DSI_MODE                   (0x20000000Lu)
#define ADC_Infrared_SWITCH_DISABLE             (0x40000000Lu)
#define ADC_Infrared_ENABLE                     (0x80000000Lu)

/* defines for STATUS register */
#define ADC_Infrared_STATUS_BUSY                (0x80000000Lu)

/* defines for SAMPLE_CTRL register */
#define ADC_Infrared_ALT_RESOLUTION_10BIT       (0x00000001Lu)
#define ADC_Infrared_ALT_RESOLUTION_8BIT        (0x00000000Lu)

#define ADC_Infrared_DATA_ALIGN_LEFT            (0x00000002Lu)
#define ADC_Infrared_DATA_ALIGN_RIGHT           (0x00000000Lu)

#define ADC_Infrared_SE_SIGNED_RESULT           (0x00000004Lu)
#define ADC_Infrared_SE_UNSIGNED_RESULT         (0x00000000Lu)

#define ADC_Infrared_DIFF_SIGNED_RESULT         (0x00000008Lu)
#define ADC_Infrared_DIFF_UNSIGNED_RESULT       (0x00000000Lu)

#define ADC_Infrared_AVG_CNT_OFFSET             (4u)
#define ADC_Infrared_AVG_CNT_MASK               (0x00000070Lu)
#define ADC_Infrared_AVG_SHIFT                  (0x00000080Lu)

#define ADC_Infrared_CONTINUOUS_EN              (0x00010000Lu)
#define ADC_Infrared_DSI_TRIGGER_EN             (0x00020000Lu)
#define ADC_Infrared_DSI_TRIGGER_LEVEL          (0x00040000Lu)
#define ADC_Infrared_DSI_SYNC_TRIGGER           (0x00080000Lu)
#define ADC_Infrared_EOS_DSI_OUT_EN             (0x80000000Lu)

/* defines for SAMPLE_TIME01 / SAMPLE_TIME23 registers */
#define ADC_Infrared_SAMPLE_TIME13_OFFSET       (16u)
#define ADC_Infrared_SAMPLE_TIME02_MASK         (0x000003FFLu)
#define ADC_Infrared_SAMPLE_TIME13_MASK         (0x03FF0000Lu)

/* defines for RANGE_THRES registers */
#define ADC_Infrared_RANGE_HIGH_OFFSET          (16u)
#define ADC_Infrared_RANGE_HIGH_MASK            (0xFFFF0000Lu)
#define ADC_Infrared_RANGE_LOW_MASK             (0x0000FFFFLu)

/* defines for RANGE_COND register */
/* Compare mode setting constants:
*    BELOW   - Result < Low_Limit
*    INSIDE  - Low_Limit <= Result < High_Limit
*    ABOVE   - High_Limit <= Result
*    OUTSIDE - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define ADC_Infrared_CMP_MODE_BELOW             (0x00000000Lu)
#define ADC_Infrared_CMP_MODE_INSIDE            (0x40000000Lu)
#define ADC_Infrared_CMP_MODE_ABOVE             (0x80000000Lu)
#define ADC_Infrared_CMP_MODE_OUTSIDE           (0xC0000000Lu)
#define ADC_Infrared_CMP_OFFSET                 (30u)

/* defines for _START_CTRL register */
#define ADC_Infrared_FW_TRIGGER                 (0x00000001Lu)

/* defines for DFT_CTRL register */
#define ADC_Infrared_DLY_INC                    (0x00000001Lu)
#define ADC_Infrared_HIZ                        (0x00000002Lu)
#define ADC_Infrared_DFT_INC_MASK               (0x000F0000Lu)
#define ADC_Infrared_DFT_OUTC_MASK              (0x00700000Lu)
#define ADC_Infrared_SEL_CSEL_DFT_MASK          (0x0F000000Lu)

/* configuration for clock speed > 9 Mhz based on
* characterization results
*/
#define ADC_Infrared_SEL_CSEL_DFT_CHAR          (0x03000000Lu)
#define ADC_Infrared_EN_CSEL_DFT                (0x10000000Lu)
#define ADC_Infrared_DCEN                       (0x20000000Lu)
#define ADC_Infrared_ADFT_OVERRIDE              (0x80000000Lu)

/* defines for CHAN_CONFIG / DIE_CHAN_CONFIG register
*  and channelsConfig parameter
*/
#define ADC_Infrared_SARMUX_VIRT_SELECT         (0x00000070Lu)
#define ADC_Infrared_DIFFERENTIAL_EN            (0x00000100Lu)
#define ADC_Infrared_ALT_RESOLUTION_ON          (0x00000200Lu)
#define ADC_Infrared_AVERAGING_EN               (0x00000400Lu)

#define ADC_Infrared_SAMPLE_TIME_SEL_SHIFT      (12u)
#define ADC_Infrared_SAMPLE_TIME_SEL_MASK       (0x00003000Lu)

#define ADC_Infrared_CHANNEL_CONFIG_MASK        (0x00003700Lu)

/* for CHAN_CONFIG only */
#define ADC_Infrared_DSI_OUT_EN                 (0x80000000Lu)

/* for INJ_CHAN_CONFIG only */
#define ADC_Infrared_INJ_TAILGATING             (0x40000000Lu)
#define ADC_Infrared_INJ_CHAN_EN                (0x80000000Lu)

/* defines for CHAN_WORK register */
#define ADC_Infrared_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define ADC_Infrared_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define ADC_Infrared_SAR_WRK_MAX_8BIT           (0x00000100Lu)

/* defines for CHAN_RESULT register */
#define ADC_Infrared_RESULT_MASK                (0x0000FFFFLu)
#define ADC_Infrared_SATURATE_INTR_MIR          (0x20000000Lu)
#define ADC_Infrared_RANGE_INTR_MIR             (0x40000000Lu)
#define ADC_Infrared_CHAN_RESULT_VALID_MIR      (0x80000000Lu)

/* defines for INTR_MASK register */
#define ADC_Infrared_EOS_MASK                   (0x00000001Lu)
#define ADC_Infrared_OVERFLOW_MASK              (0x00000002Lu)
#define ADC_Infrared_FW_COLLISION_MASK          (0x00000004Lu)
#define ADC_Infrared_DSI_COLLISION_MASK         (0x00000008Lu)
#define ADC_Infrared_INJ_EOC_MASK               (0x00000010Lu)
#define ADC_Infrared_INJ_SATURATE_MASK          (0x00000020Lu)
#define ADC_Infrared_INJ_RANGE_MASK             (0x00000040Lu)
#define ADC_Infrared_INJ_COLLISION_MASK         (0x00000080Lu)

/* defines for INJ_RESULT register */
#define ADC_Infrared_INJ_COLLISION_INTR_MIR     (0x10000000Lu)
#define ADC_Infrared_INJ_SATURATE_INTR_MIR      (0x20000000Lu)
#define ADC_Infrared_INJ_RANGE_INTR_MIR         (0x40000000Lu)
#define ADC_Infrared_INJ_EOC_INTR_MIR           (0x80000000Lu)

/* defines for MUX_SWITCH0 register */
#define ADC_Infrared_MUX_FW_VSSA_VMINUS         (0x00010000Lu)

/* defines for PUMP_CTRL register */
#define ADC_Infrared_PUMP_CTRL_ENABLED          (0x80000000Lu)

/* additional defines for channelsConfig parameter */
#define ADC_Infrared_IS_SATURATE_EN_MASK        (0x00000001Lu)
#define ADC_Infrared_IS_RANGE_CTRL_EN_MASK      (0x00000002Lu)

/* defines for WOUNDING register */
#define ADC_Infrared_WOUNDING_12BIT             (0x00000000Lu)
#define ADC_Infrared_WOUNDING_10BIT             (0x00000001Lu)
#define ADC_Infrared_WOUNDING_8BIT              (0x00000002Lu)

/* Trim value based on characterization */
#define ADC_Infrared_TRIM_COEF                  (2u)

#if(ADC_Infrared_MAX_RESOLUTION == ADC_Infrared_RESOLUTION_10)
    #define ADC_Infrared_ALT_WOUNDING           ADC_Infrared_WOUNDING_10BIT
#else
    #define ADC_Infrared_ALT_WOUNDING           ADC_Infrared_WOUNDING_8BIT
#endif /* ADC_Infrared_MAX_RESOLUTION == ADC_Infrared_RESOLUTION_10 */

#if(ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__VDDA_2)
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_VDDA_2
#elif(ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__VDDA)
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_VDDA
#elif(ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__INTERNAL1024)
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_INTERNAL1024
#elif(ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__INTERNAL1024BYPASSED)
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_INTERNAL1024BYPASSED
#elif(ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__INTERNALVREF)
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_INTERNALVREF
#elif(ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__INTERNALVREFBYPASSED)
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_INTERNALVREFBYPASSED
#elif(ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__VDDA_2BYPASSED)
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_VDDA_2BYPASSED
#else
    #define ADC_Infrared_DEFAULT_VREF_SOURCE    ADC_Infrared_VREF_EXTERNAL
#endif /* ADC_Infrared_DEFAULT_VREF_SEL == ADC_Infrared__VDDA_2 */

#if(ADC_Infrared_DEFAULT_NEG_INPUT_SEL == ADC_Infrared__VSS)
    /* Connect NEG input of SARADC to VSSA close to the SARADC for single channel mode */
    #if(ADC_Infrared_TOTAL_CHANNELS_NUM == 1u)
        #define ADC_Infrared_DEFAULT_SE_NEG_INPUT    ADC_Infrared_NEG_VSSA
    #else
        #define ADC_Infrared_DEFAULT_SE_NEG_INPUT    ADC_Infrared_NEG_VSSA_KELVIN
    #endif /* (ADC_Infrared_TOTAL_CHANNELS_NUM == 1u) */
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((ADC_Infrared_TOTAL_CHANNELS_NUM == 1u) && (ADC_Infrared_CHANNELS_MODE != 0u))
        #define ADC_Infrared_DEFAULT_MUX_SWITCH0     0u
    #else    /* miltiple channels or one single channel */
        #define ADC_Infrared_DEFAULT_MUX_SWITCH0     ADC_Infrared_MUX_FW_VSSA_VMINUS
    #endif /* (ADC_Infrared_TOTAL_CHANNELS_NUM == 1u) */
#elif(ADC_Infrared_DEFAULT_NEG_INPUT_SEL == ADC_Infrared__VREF)
    /* Do not connect VNEG to VREF when one channel in differential mode used */
    #if((ADC_Infrared_TOTAL_CHANNELS_NUM == 1u) && (ADC_Infrared_CHANNELS_MODE != 0u))
        #define ADC_Infrared_DEFAULT_SE_NEG_INPUT    0u
    #else    /* miltiple channels or one single channel */
        #define ADC_Infrared_DEFAULT_SE_NEG_INPUT    ADC_Infrared_NEG_VREF
    #endif /* (ADC_Infrared_TOTAL_CHANNELS_NUM == 1u) */
    #define ADC_Infrared_DEFAULT_MUX_SWITCH0     0u
#elif (ADC_Infrared_SINGLE_PRESENT != 0u)
    #define ADC_Infrared_DEFAULT_SE_NEG_INPUT    ADC_Infrared_NEG_OTHER
    #define ADC_Infrared_DEFAULT_MUX_SWITCH0     0u
#else
    #define ADC_Infrared_DEFAULT_SE_NEG_INPUT    0u
    #define ADC_Infrared_DEFAULT_MUX_SWITCH0     0u
#endif /* ADC_Infrared_DEFAULT_NEG_INPUT_SEL == ADC_Infrared__VREF */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(ADC_Infrared_TOTAL_CHANNELS_NUM == 1u)
    #define ADC_Infrared_DEFAULT_HW_CTRL_NEGVREF 0u
#else
    #define ADC_Infrared_DEFAULT_HW_CTRL_NEGVREF ADC_Infrared_SAR_HW_CTRL_NEGVREF
#endif /* (ADC_Infrared_TOTAL_CHANNELS_NUM == 1u) */


#if(ADC_Infrared_DEFAULT_ALT_RESOLUTION_SEL == ADC_Infrared__RES8)
    #define ADC_Infrared_DEFAULT_ALT_RESOLUTION     (ADC_Infrared_ALT_RESOLUTION_8BIT)
    #define ADC_Infrared_DEFAULT_MAX_WRK_ALT        (ADC_Infrared_SAR_WRK_MAX_8BIT)
#else
    #define ADC_Infrared_DEFAULT_ALT_RESOLUTION     (ADC_Infrared_ALT_RESOLUTION_10BIT)
    #define ADC_Infrared_DEFAULT_MAX_WRK_ALT        (ADC_Infrared_SAR_WRK_MAX_10BIT)
#endif /* End ADC_Infrared_DEFAULT_ALT_RESOLUTION_SEL == ADC_Infrared__RES8 */

#if(ADC_Infrared_DEFAULT_JUSTIFICATION_SEL == ADC_Infrared__RIGHT)
    #define ADC_Infrared_DEFAULT_JUSTIFICATION  ADC_Infrared_DATA_ALIGN_RIGHT
#else
    #define ADC_Infrared_DEFAULT_JUSTIFICATION  ADC_Infrared_DATA_ALIGN_LEFT
#endif /* ADC_Infrared_DEFAULT_JUSTIFICATION_SEL == ADC_Infrared__RIGHT */

#if(ADC_Infrared_DEFAULT_DIFF_RESULT_FORMAT_SEL == ADC_Infrared__FSIGNED)
    #define ADC_Infrared_DEFAULT_DIFF_RESULT_FORMAT ADC_Infrared_DIFF_SIGNED_RESULT
#else
    #define ADC_Infrared_DEFAULT_DIFF_RESULT_FORMAT ADC_Infrared_DIFF_UNSIGNED_RESULT
#endif /* ADC_Infrared_DEFAULT_DIFF_RESULT_FORMAT_SEL == ADC_Infrared__FSIGNED */

#if(ADC_Infrared_DEFAULT_SE_RESULT_FORMAT_SEL == ADC_Infrared__FSIGNED)
    #define ADC_Infrared_DEFAULT_SE_RESULT_FORMAT ADC_Infrared_SE_SIGNED_RESULT
#else
    #define ADC_Infrared_DEFAULT_SE_RESULT_FORMAT ADC_Infrared_SE_UNSIGNED_RESULT
#endif /* ADC_Infrared_DEFAULT_SE_RESULT_FORMAT_SEL == ADC_Infrared__FSIGNED */

#if(ADC_Infrared_DEFAULT_SAMPLE_MODE_SEL == ADC_Infrared__FREERUNNING)
    #define ADC_Infrared_DSI_TRIGGER        0u
#else /* Firmware trigger */
    #define ADC_Infrared_DSI_TRIGGER        (ADC_Infrared_DSI_TRIGGER_EN | ADC_Infrared_DSI_SYNC_TRIGGER)
#endif /* End ADC_Infrared_DEFAULT_SAMPLE_MODE == ADC_Infrared__FREERUNNING */

#if(ADC_Infrared_INJ_CHANNEL_ENABLED)
    #define ADC_Infrared_SAR_INTR_MASK      (ADC_Infrared_EOS_MASK | ADC_Infrared_INJ_EOC_MASK)
#else
    #define ADC_Infrared_SAR_INTR_MASK      (ADC_Infrared_EOS_MASK)
#endif /* ADC_Infrared_INJ_CHANNEL_ENABLED*/

#if(ADC_Infrared_DEFAULT_AVG_MODE == ADC_Infrared__FIXEDRESOLUTION)
    #define ADC_Infrared_AVG_SHIFT_MODE     ADC_Infrared_AVG_SHIFT
#else
    #define ADC_Infrared_AVG_SHIFT_MODE     0u
#endif /* End ADC_Infrared_DEFAULT_AVG_MODE */

#define ADC_Infrared_COMPARE_MODE           (uint32)((uint32)(ADC_Infrared_DEFAULT_COMPARE_MODE) \
                                                << ADC_Infrared_CMP_OFFSET)

#if(ADC_Infrared_TOTAL_CHANNELS_NUM > 1u)
    #define ADC_Infrared_DEFAULT_SWITCH_CONF    0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define ADC_Infrared_DEFAULT_SWITCH_CONF    ADC_Infrared_SWITCH_DISABLE
#endif /* End ADC_Infrared_TOTAL_CHANNELS_NUM > 1 */

#define ADC_Infrared_DEFAULT_POWER \
       ((ADC_Infrared_NOMINAL_CLOCK_FREQ > (ADC_Infrared_MAX_FREQUENCY / 4)) ? ADC_Infrared_NORMAL_PWR : \
       ((ADC_Infrared_NOMINAL_CLOCK_FREQ > (ADC_Infrared_MAX_FREQUENCY / 8)) ? ADC_Infrared_HALF_PWR : \
                                                                                       ADC_Infrared_QUARTER_PWR))

#define ADC_Infrared_DEFAULT_CTRL_REG_CFG       (ADC_Infrared_DEFAULT_VREF_SOURCE \
                                                   | ADC_Infrared_DEFAULT_SE_NEG_INPUT \
                                                   | ADC_Infrared_DEFAULT_HW_CTRL_NEGVREF \
                                                   | ADC_Infrared_DEFAULT_POWER \
                                                   | ADC_Infrared_DSI_SYNC_CONFIG \
                                                   | ADC_Infrared_DEFAULT_SWITCH_CONF)

#define ADC_Infrared_DEFAULT_SAMPLE_CTRL_REG_CFG (ADC_Infrared_DEFAULT_DIFF_RESULT_FORMAT \
                                                    | ADC_Infrared_DEFAULT_SE_RESULT_FORMAT \
                                                    | ADC_Infrared_DEFAULT_JUSTIFICATION \
                                                    | ADC_Infrared_DEFAULT_ALT_RESOLUTION \
                                           | (uint8)(ADC_Infrared_DEFAULT_AVG_SAMPLES_NUM \
                                                   << ADC_Infrared_AVG_CNT_OFFSET) \
                                                    | ADC_Infrared_AVG_SHIFT_MODE \
                                                    | ADC_Infrared_DSI_TRIGGER \
                                                    | ADC_Infrared_EOS_DSI_OUT_EN)

#define ADC_Infrared_DEFAULT_RANGE_THRES_REG_CFG (ADC_Infrared_DEFAULT_LOW_LIMIT \
            | (uint32)((uint32)ADC_Infrared_DEFAULT_HIGH_LIMIT << ADC_Infrared_RANGE_HIGH_OFFSET))

#define ADC_Infrared_DEFAULT_SAMPLE_TIME01_REG_CFG (ADC_Infrared_DEFAULT_ACLKS_NUM \
            | (uint32)((uint32)ADC_Infrared_DEFAULT_BCLKS_NUM << ADC_Infrared_SAMPLE_TIME13_OFFSET))

#define ADC_Infrared_DEFAULT_SAMPLE_TIME23_REG_CFG (ADC_Infrared_DEFAULT_CCLKS_NUM \
            | (uint32)((uint32)ADC_Infrared_DEFAULT_DCLKS_NUM << ADC_Infrared_SAMPLE_TIME13_OFFSET))


#endif /* End CY_ADC_SAR_SEQ_ADC_Infrared_H */


/* [] END OF FILE */
