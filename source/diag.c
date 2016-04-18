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

#include "diag.h"

void Diag_Init()
{

}

void Diag_Start()
{

}

void Diag_Update()
{
    // Used to monitor loop cycle time
    MainLoop_Pin_Write( ~MainLoop_Pin_Read() );
}

/* [] END OF FILE */
