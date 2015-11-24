/*******************************************************************************
* File Name: Load.c  
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
#include "Load.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Load_PC =   (Load_PC & \
                                (uint32)(~(uint32)(Load_DRIVE_MODE_IND_MASK << (Load_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Load_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Load_Write
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
void Load_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Load_DR & (uint8)(~Load_MASK));
    drVal = (drVal | ((uint8)(value << Load_SHIFT) & Load_MASK));
    Load_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Load_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Load_DM_STRONG     Strong Drive 
*  Load_DM_OD_HI      Open Drain, Drives High 
*  Load_DM_OD_LO      Open Drain, Drives Low 
*  Load_DM_RES_UP     Resistive Pull Up 
*  Load_DM_RES_DWN    Resistive Pull Down 
*  Load_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Load_DM_DIG_HIZ    High Impedance Digital 
*  Load_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Load_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Load__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Load_Read
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
*  Macro Load_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Load_Read(void) 
{
    return (uint8)((Load_PS & Load_MASK) >> Load_SHIFT);
}


/*******************************************************************************
* Function Name: Load_ReadDataReg
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
uint8 Load_ReadDataReg(void) 
{
    return (uint8)((Load_DR & Load_MASK) >> Load_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Load_INTSTAT) 

    /*******************************************************************************
    * Function Name: Load_ClearInterrupt
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
    uint8 Load_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Load_INTSTAT & Load_MASK);
		Load_INTSTAT = maskedStatus;
        return maskedStatus >> Load_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
