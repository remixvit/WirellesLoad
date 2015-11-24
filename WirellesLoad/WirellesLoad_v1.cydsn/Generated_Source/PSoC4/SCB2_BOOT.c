/*******************************************************************************
* File Name: SCB2_BOOT.c
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

#include "SCB2_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_BTLDR_COMM_ENABLED) && \
                                (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: SCB2_CyBtldrCommStart
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
void SCB2_CyBtldrCommStart(void)
{
    if (SCB2_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB2_I2CCyBtldrCommStart();
    }
    else if (SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB2_EzI2CCyBtldrCommStart();
    }
#if (!SCB2_CY_SCBIP_V1)
    else if (SCB2_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB2_SpiCyBtldrCommStart();
    }
    else if (SCB2_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB2_UartCyBtldrCommStart();
    }
#endif /* (!SCB2_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: SCB2_CyBtldrCommStop
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
void SCB2_CyBtldrCommStop(void)
{
    if (SCB2_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB2_I2CCyBtldrCommStop();
    }
    else if (SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB2_EzI2CCyBtldrCommStop();
    }
#if (!SCB2_CY_SCBIP_V1)
    else if (SCB2_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB2_SpiCyBtldrCommStop();
    }
    else if (SCB2_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB2_UartCyBtldrCommStop();
    }
#endif /* (!SCB2_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: SCB2_CyBtldrCommReset
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
void SCB2_CyBtldrCommReset(void)
{
    if(SCB2_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB2_I2CCyBtldrCommReset();
    }
    else if(SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB2_EzI2CCyBtldrCommReset();
    }
#if (!SCB2_CY_SCBIP_V1)
    else if(SCB2_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB2_SpiCyBtldrCommReset();
    }
    else if(SCB2_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB2_UartCyBtldrCommReset();
    }
#endif /* (!SCB2_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: SCB2_CyBtldrCommRead
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
cystatus SCB2_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(SCB2_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = SCB2_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = SCB2_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!SCB2_CY_SCBIP_V1)
    else if(SCB2_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = SCB2_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(SCB2_SCB_MODE_UART_RUNTM_CFG)
    {
        status = SCB2_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!SCB2_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: SCB2_CyBtldrCommWrite
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
cystatus SCB2_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(SCB2_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = SCB2_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = SCB2_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!SCB2_CY_SCBIP_V1)
    else if(SCB2_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = SCB2_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(SCB2_SCB_MODE_UART_RUNTM_CFG)
    {
        status = SCB2_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!SCB2_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
