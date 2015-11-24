/*******************************************************************************
* File Name: SCB2_PM.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB2.h"
#include "SCB2_PVT.h"

#if(SCB2_SCB_MODE_I2C_INC)
    #include "SCB2_I2C_PVT.h"
#endif /* (SCB2_SCB_MODE_I2C_INC) */

#if(SCB2_SCB_MODE_EZI2C_INC)
    #include "SCB2_EZI2C_PVT.h"
#endif /* (SCB2_SCB_MODE_EZI2C_INC) */

#if(SCB2_SCB_MODE_SPI_INC || SCB2_SCB_MODE_UART_INC)
    #include "SCB2_SPI_UART_PVT.h"
#endif /* (SCB2_SCB_MODE_SPI_INC || SCB2_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SCB2_SCB_MODE_I2C_CONST_CFG   && (!SCB2_I2C_WAKE_ENABLE_CONST))   || \
   (SCB2_SCB_MODE_EZI2C_CONST_CFG && (!SCB2_EZI2C_WAKE_ENABLE_CONST)) || \
   (SCB2_SCB_MODE_SPI_CONST_CFG   && (!SCB2_SPI_WAKE_ENABLE_CONST))   || \
   (SCB2_SCB_MODE_UART_CONST_CFG  && (!SCB2_UART_WAKE_ENABLE_CONST)))

    SCB2_BACKUP_STRUCT SCB2_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SCB2_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_Sleep(void)
{
#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SCB2_SCB_WAKE_ENABLE_CHECK)
    {
        if(SCB2_SCB_MODE_I2C_RUNTM_CFG)
        {
            SCB2_I2CSaveConfig();
        }
        else if(SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SCB2_EzI2CSaveConfig();
        }
    #if(!SCB2_CY_SCBIP_V1)
        else if(SCB2_SCB_MODE_SPI_RUNTM_CFG)
        {
            SCB2_SpiSaveConfig();
        }
        else if(SCB2_SCB_MODE_UART_RUNTM_CFG)
        {
            SCB2_UartSaveConfig();
        }
    #endif /* (!SCB2_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SCB2_backup.enableState = (uint8) SCB2_GET_CTRL_ENABLED;

        if(0u != SCB2_backup.enableState)
        {
            SCB2_Stop();
        }
    }

#else

    #if (SCB2_SCB_MODE_I2C_CONST_CFG && SCB2_I2C_WAKE_ENABLE_CONST)
        SCB2_I2CSaveConfig();

    #elif (SCB2_SCB_MODE_EZI2C_CONST_CFG && SCB2_EZI2C_WAKE_ENABLE_CONST)
        SCB2_EzI2CSaveConfig();

    #elif (SCB2_SCB_MODE_SPI_CONST_CFG && SCB2_SPI_WAKE_ENABLE_CONST)
        SCB2_SpiSaveConfig();

    #elif (SCB2_SCB_MODE_UART_CONST_CFG && SCB2_UART_WAKE_ENABLE_CONST)
        SCB2_UartSaveConfig();

    #else

        SCB2_backup.enableState = (uint8) SCB2_GET_CTRL_ENABLED;

        if(0u != SCB2_backup.enableState)
        {
            SCB2_Stop();
        }

    #endif /* defined (SCB2_SCB_MODE_I2C_CONST_CFG) && (SCB2_I2C_WAKE_ENABLE_CONST) */

#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB2_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_Wakeup(void)
{
#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SCB2_SCB_WAKE_ENABLE_CHECK)
    {
        if(SCB2_SCB_MODE_I2C_RUNTM_CFG)
        {
            SCB2_I2CRestoreConfig();
        }
        else if(SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SCB2_EzI2CRestoreConfig();
        }
    #if(!SCB2_CY_SCBIP_V1)
        else if(SCB2_SCB_MODE_SPI_RUNTM_CFG)
        {
            SCB2_SpiRestoreConfig();
        }
        else if(SCB2_SCB_MODE_UART_RUNTM_CFG)
        {
            SCB2_UartRestoreConfig();
        }
    #endif /* (!SCB2_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SCB2_backup.enableState)
        {
            SCB2_Enable();
        }
    }

#else

    #if (SCB2_SCB_MODE_I2C_CONST_CFG  && SCB2_I2C_WAKE_ENABLE_CONST)
        SCB2_I2CRestoreConfig();

    #elif (SCB2_SCB_MODE_EZI2C_CONST_CFG && SCB2_EZI2C_WAKE_ENABLE_CONST)
        SCB2_EzI2CRestoreConfig();

    #elif (SCB2_SCB_MODE_SPI_CONST_CFG && SCB2_SPI_WAKE_ENABLE_CONST)
        SCB2_SpiRestoreConfig();

    #elif (SCB2_SCB_MODE_UART_CONST_CFG && SCB2_UART_WAKE_ENABLE_CONST)
        SCB2_UartRestoreConfig();

    #else

        if(0u != SCB2_backup.enableState)
        {
            SCB2_Enable();
        }

    #endif /* (SCB2_I2C_WAKE_ENABLE_CONST) */

#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
