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

#include "utils.h"

int32 MovingAverage(MOVING_AVERAGE_TYPE* ma, int32 value)
/*
MA*[i]= MA*[i-1] +X[i] - MA*[i-1]/N

where MA* is the moving average*N. 

MA[i]= MA*[i]/N
*/
{
    int32 ma_curr;
    
    ma_curr = ma->last + value - ma->last/ma->n;
    ma->last = ma_curr;
    
    return ma_curr/ma->n;
}

void Uint16ToTwoBytes(uint16 value, uint8* bytes)
{
    bytes[0] = (uint8) (value & 0xFF00) >> 8;
    bytes[1] = (uint8) (value & 0x00FF);
}

void Uint32ToFourBytes(uint32 value, uint8* bytes)
{
    bytes[0] = (value & 0xFF000000) >> 24;
    bytes[1] = (value & 0x00FF0000) >> 16;
    bytes[2] = (value & 0x0000FF00) >> 8;
    bytes[3] = (value & 0x000000FF);
}

void Int32ToFourBytes(int32 value, uint8* bytes)
{
    Uint32ToFourBytes((uint32)value, bytes);
}

void FloatToFourBytes(float value, uint8* bytes)
{
    Uint32ToFourBytes(*((uint32*)&value), bytes);
}

uint16 TwoBytesToUint16(uint8* bytes)
{
    return (uint16) ( (bytes[0] << 8) + bytes[1] );
}

int16 TwoBytesInt16(uint8* bytes)
{
    return (int16) TwoBytesToUint16(bytes);
}

uint32 FourBytesToUint32(uint8* bytes)
{
    return (uint32) ( (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3] );
}

int32 FourBytesToInt32(uint8* bytes)
{
    return (int32) FourBytesToUint32(bytes);
}

/* [] END OF FILE */
