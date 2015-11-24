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
#include <MyLib.h>

CY_ISR(ExtInter_Head)
{
	ExtInt.Temp = TEMP_IRQ_Read();
    ExtInt.Crit_Temp = CRIT_TEMP_IRQ_Read();
    ExtInt.Button = Button_Read();
    ExtInt.Opt = OPT_IRQ_Read();
    ExtInt.NRF = NRF_IRQ_Read();
}

void InterruptAction(void)
{
	
}

/* [] END OF FILE */
