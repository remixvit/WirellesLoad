/*******************************************************************************
* File Name: SCB1_BOOT.c
* Version 3.0
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB1_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_BTLDR_COMM_ENABLED) && \
                                (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: SCB1_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB1_CyBtldrCommStart(void)
{
    if (SCB1_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB1_I2CCyBtldrCommStart();
    }
    else if (SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB1_EzI2CCyBtldrCommStart();
    }
#if (!SCB1_CY_SCBIP_V1)
    else if (SCB1_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB1_SpiCyBtldrCommStart();
    }
    else if (SCB1_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB1_UartCyBtldrCommStart();
    }
#endif /* (!SCB1_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: SCB1_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB1_CyBtldrCommStop(void)
{
    if (SCB1_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB1_I2CCyBtldrCommStop();
    }
    else if (SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB1_EzI2CCyBtldrCommStop();
    }
#if (!SCB1_CY_SCBIP_V1)
    else if (SCB1_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB1_SpiCyBtldrCommStop();
    }
    else if (SCB1_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB1_UartCyBtldrCommStop();
    }
#endif /* (!SCB1_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: SCB1_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB1_CyBtldrCommReset(void)
{
    if(SCB1_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB1_I2CCyBtldrCommReset();
    }
    else if(SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB1_EzI2CCyBtldrCommReset();
    }
#if (!SCB1_CY_SCBIP_V1)
    else if(SCB1_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB1_SpiCyBtldrCommReset();
    }
    else if(SCB1_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB1_UartCyBtldrCommReset();
    }
#endif /* (!SCB1_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: SCB1_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus SCB1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(SCB1_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = SCB1_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = SCB1_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!SCB1_CY_SCBIP_V1)
    else if(SCB1_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = SCB1_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(SCB1_SCB_MODE_UART_RUNTM_CFG)
    {
        status = SCB1_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!SCB1_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: SCB1_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus SCB1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(SCB1_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = SCB1_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = SCB1_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!SCB1_CY_SCBIP_V1)
    else if(SCB1_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = SCB1_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(SCB1_SCB_MODE_UART_RUNTM_CFG)
    {
        status = SCB1_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!SCB1_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */