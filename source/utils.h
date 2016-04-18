#ifndef UTILS_H
#define UTILS_H
    
#include <project.h>

/* Clear bit a in value b */
#define CLEAR_BIT(a, b) ((~(1<<a)) & (b))
/* Set bit a in value b */
#define SET_BIT(a, b) ((1<<a) | (b))
/* Get bit a in value b */
#define GET_BIT(a, b) ((b>>a) & (1))

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#define constrain(a, b, c) (min(max(a, b), c))
// Scale X -> Y
//    X          Y
//  -----    = -----  => y = x * y range / x range
//  x range    y range
#define scale_integer(x, x_range, y_range) ( (int32) (x * y_range) / (int32) x_range )
#define scale_float(x, x_range, y_range) ( (float) (x * y_range) / (float) x_range )

#define abs(x)  ( x < 0 ? -x : x )
    
    
typedef struct _moving_average_tag
{
    int32 n;
    int32 last;
} MOVING_AVERAGE_TYPE;
    
int32 MovingAverage(MOVING_AVERAGE_TYPE* ma, int32 value);

int16 TwoBytesToInt16(uint8* bytes);
uint16 TwoBytesToUint16(uint8* bytes);
uint32 FourBytesToUint32(uint8* bytes);
int32 FourBytesToInt32(uint8* bytes);
void Int32ToFourBytes(int32 value, uint8* bytes);
void Uint16ToTwoBytes(uint16 value, uint8* bytes);
void FloatToFourBytes(float value, uint8* bytes);


#endif