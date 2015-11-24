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

#include <Project.h>


typedef struct
{
    uint8 Temp;
    uint8 Crit_Temp;
    uint8 Opt;
    uint8 Button;
    uint8 NRF;
}InterruptStruct;
volatile InterruptStruct ExtInt;

CY_ISR(ExtInter_Head);

void InterruptAction(void);
/* [] END OF FILE */
