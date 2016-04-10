/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdlib.h>
#include "encoder.h"
#include "utils.h"
#include "i2c.h"
#include "time.h"
#include "debug.h"

#define SAMPLE_RATE (20) /* Hz */
#define SAMPLE_PERIOD (1000/SAMPLE_RATE) /* milliseconds */
#define MILLIS_PER_SECOND (1000)

#define MILLIMETERS_PER_REVOLUTION (479.0) /* millimeters */
#define COUNTS_PER_REVOLUTION (36.0 * 4)  /* 36 teeth per revolution (4x encoder) */
#define MILLIMETERS_PER_COUNT (MILLIMETERS_PER_REVOLUTION/COUNTS_PER_REVOLUTION) /* millimeters */

/* Aliases for the encoder pins */
#define Pins_Encoder_A_Read() (Encoder_Pins_Read() & 0x01)
#define Pins_Encoder_B_Read() ((Encoder_Pins_Read() & 0x02) >> 1)

#define ENCODER_A (0x01)
#define ENCODER_B (0x02)
#define ENCODER_PINS_MASK   (ENCODER_A | ENCODER_B)

static volatile int32_t enc_count;
static volatile int32 last_enc_count;
static volatile int16 enc_velocity;
static volatile uint32 last_velocity_time;


// Encoder Lookup Table
//      sequence: 00 <-> 01 <-> 11 <-> 10 <-> 00 <-> 01 <-> 10 <-> 11 <-> ...
static const int8_t enc_states [] = { 0, /* 00 -> 00 : No Change    */
                                     -1, /* 00 -> 01 : CCW          */
                                      1, /* 00 -> 10 : CW           */
                                      0, /* 00 -> 11 : Can't Happen */
                                      1, /* 01 -> 00 : CW           */
                                      0, /* 01 -> 01 : No Change    */
                                      0, /* 01 -> 10 : Can't Happen */
                                     -1, /* 01 -> 11 : CCW          */
                                     -1, /* 10 -> 00 : CCW          */
                                      0, /* 10 -> 01 : Can't Happen */
                                      0, /* 10 -> 10 : No Change    */
                                      1, /* 10 -> 11 : CW           */
                                      0, /* 11 -> 00 : Can't Happen */
                                      1, /* 11 -> 01 : CW           */
                                     -1, /* 11 -> 10 : CCW          */
                                      0  /* 11 -> 11 : No Change    */
                                    };
static uint8 old_ab = 0;

CY_ISR( Encoder_Interrupt_Handler )
/* An interrupt can occur on either pin A or B
   When an interrupt occurs, 
    - clear the interrupt
    - capture the state of both A and B
    - calculate increment based on A/B state
 */
{       
    uint8 pins = 0;
    uint8 a_pin = 0;
    uint8 b_pin = 0;
    
    pins = Encoder_Pins_ClearInterrupt();
    
    if (pins & ENCODER_PINS_MASK )
    {
        a_pin = Pins_Encoder_A_Read();
        b_pin = Pins_Encoder_B_Read();
        
        old_ab <<= 2;
        old_ab |= (a_pin << 1) | b_pin;
        old_ab &= 0x0F;
        enc_count += DIRECTION * enc_states[old_ab];
        I2c_WriteCount(enc_count);
    }
}

void Encoder_Init()
{
    enc_count = 0;
    enc_velocity = 0;    
    last_velocity_time = 0;
    last_enc_count = 0;
}

void Encoder_Start()
{
    Encoder_Intr_StartEx( Encoder_Interrupt_Handler );    
}

int16 Encoder_GetVelocity()
{
    return enc_velocity;
}

int32 Encoder_GetCount()
{
    int32 value;
    Encoder_Intr_Disable();
    value = enc_count;
    Encoder_Intr_Enable();
    return value;
}

int32 Encoder_GetLeftCount()
{
#ifdef LEFT_BOARD
    return Encoder_GetCount();
#else
    return I2c_ReadCount();
#endif
}

int32 Encoder_GetRightCount()
{
#ifdef LEFT_BOARD
    return I2c_ReadCount();
#else
    return Encoder_GetCount();
#endif
}

void Encoder_Reset()
{
    Encoder_Intr_Disable();
    enc_count = 0;
    Encoder_Intr_Enable();
}

/* [] END OF FILE */
