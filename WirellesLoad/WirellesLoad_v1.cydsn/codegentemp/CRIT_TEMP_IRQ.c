/*******************************************************************************
* File Name: CRIT_TEMP_IRQ.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "CRIT_TEMP_IRQ.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        CRIT_TEMP_IRQ_PC =   (CRIT_TEMP_IRQ_PC & \
                                (uint32)(~(uint32)(CRIT_TEMP_IRQ_DRIVE_MODE_IND_MASK << (CRIT_TEMP_IRQ_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (CRIT_TEMP_IRQ_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: CRIT_TEMP_IRQ_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void CRIT_TEMP_IRQ_Write(uint8 value) 
{
    uint8 drVal = (uint8)(CRIT_TEMP_IRQ_DR & (uint8)(~CRIT_TEMP_IRQ_MASK));
    drVal = (drVal | ((uint8)(value << CRIT_TEMP_IRQ_SHIFT) & CRIT_TEMP_IRQ_MASK));
    CRIT_TEMP_IRQ_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: CRIT_TEMP_IRQ_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  CRIT_TEMP_IRQ_DM_STRONG     Strong Drive 
*  CRIT_TEMP_IRQ_DM_OD_HI      Open Drain, Drives High 
*  CRIT_TEMP_IRQ_DM_OD_LO      Open Drain, Drives Low 
*  CRIT_TEMP_IRQ_DM_RES_UP     Resistive Pull Up 
*  CRIT_TEMP_IRQ_DM_RES_DWN    Resistive Pull Down 
*  CRIT_TEMP_IRQ_DM_RES_UPDWN  Resistive Pull Up/Down 
*  CRIT_TEMP_IRQ_DM_DIG_HIZ    High Impedance Digital 
*  CRIT_TEMP_IRQ_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void CRIT_TEMP_IRQ_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(CRIT_TEMP_IRQ__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: CRIT_TEMP_IRQ_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro CRIT_TEMP_IRQ_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 CRIT_TEMP_IRQ_Read(void) 
{
    return (uint8)((CRIT_TEMP_IRQ_PS & CRIT_TEMP_IRQ_MASK) >> CRIT_TEMP_IRQ_SHIFT);
}


/*******************************************************************************
* Function Name: CRIT_TEMP_IRQ_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 CRIT_TEMP_IRQ_ReadDataReg(void) 
{
    return (uint8)((CRIT_TEMP_IRQ_DR & CRIT_TEMP_IRQ_MASK) >> CRIT_TEMP_IRQ_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(CRIT_TEMP_IRQ_INTSTAT) 

    /*******************************************************************************
    * Function Name: CRIT_TEMP_IRQ_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 CRIT_TEMP_IRQ_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(CRIT_TEMP_IRQ_INTSTAT & CRIT_TEMP_IRQ_MASK);
		CRIT_TEMP_IRQ_INTSTAT = maskedStatus;
        return maskedStatus >> CRIT_TEMP_IRQ_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
