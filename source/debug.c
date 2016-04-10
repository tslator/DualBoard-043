#include "debug.h"

void Debug_Init()
{
    memset(formatted_string, 0, sizeof(formatted_string));
}

void Debug_Start()
{
#ifdef COMMS_DEBUG_ENABLED
    UARTCOMMS_Start();
#endif
}