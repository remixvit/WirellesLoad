/*******************************************************************************
* File Name: SCB1_PM.c
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

#include "SCB1.h"
#include "SCB1_PVT.h"

#if(SCB1_SCB_MODE_I2C_INC)
    #include "SCB1_I2C_PVT.h"
#endif /* (SCB1_SCB_MODE_I2C_INC) */

#if(SCB1_SCB_MODE_EZI2C_INC)
    #include "SCB1_EZI2C_PVT.h"
#endif /* (SCB1_SCB_MODE_EZI2C_INC) */

#if(SCB1_SCB_MODE_SPI_INC || SCB1_SCB_MODE_UART_INC)
    #include "SCB1_SPI_UART_PVT.h"
#endif /* (SCB1_SCB_MODE_SPI_INC || SCB1_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SCB1_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SCB1_SCB_MODE_I2C_CONST_CFG   && (!SCB1_I2C_WAKE_ENABLE_CONST))   || \
   (SCB1_SCB_MODE_EZI2C_CONST_CFG && (!SCB1_EZI2C_WAKE_ENABLE_CONST)) || \
   (SCB1_SCB_MODE_SPI_CONST_CFG   && (!SCB1_SPI_WAKE_ENABLE_CONST))   || \
   (SCB1_SCB_MODE_UART_CONST_CFG  && (!SCB1_UART_WAKE_ENABLE_CONST)))

    SCB1_BACKUP_STRUCT SCB1_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SCB1_Sleep
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
void SCB1_Sleep(void)
{
#if(SCB1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SCB1_SCB_WAKE_ENABLE_CHECK)
    {
        if(SCB1_SCB_MODE_I2C_RUNTM_CFG)
        {
            SCB1_I2CSaveConfig();
        }
        else if(SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SCB1_EzI2CSaveConfig();
        }
    #if(!SCB1_CY_SCBIP_V1)
        else if(SCB1_SCB_MODE_SPI_RUNTM_CFG)
        {
            SCB1_SpiSaveConfig();
        }
        else if(SCB1_SCB_MODE_UART_RUNTM_CFG)
        {
            SCB1_UartSaveConfig();
        }
    #endif /* (!SCB1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SCB1_backup.enableState = (uint8) SCB1_GET_CTRL_ENABLED;

        if(0u != SCB1_backup.enableState)
        {
            SCB1_Stop();
        }
    }

#else

    #if (SCB1_SCB_MODE_I2C_CONST_CFG && SCB1_I2C_WAKE_ENABLE_CONST)
        SCB1_I2CSaveConfig();

    #elif (SCB1_SCB_MODE_EZI2C_CONST_CFG && SCB1_EZI2C_WAKE_ENABLE_CONST)
        SCB1_EzI2CSaveConfig();

    #elif (SCB1_SCB_MODE_SPI_CONST_CFG && SCB1_SPI_WAKE_ENABLE_CONST)
        SCB1_SpiSaveConfig();

    #elif (SCB1_SCB_MODE_UART_CONST_CFG && SCB1_UART_WAKE_ENABLE_CONST)
        SCB1_UartSaveConfig();

    #else

        SCB1_backup.enableState = (uint8) SCB1_GET_CTRL_ENABLED;

        if(0u != SCB1_backup.enableState)
        {
            SCB1_Stop();
        }

    #endif /* defined (SCB1_SCB_MODE_I2C_CONST_CFG) && (SCB1_I2C_WAKE_ENABLE_CONST) */

#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB1_Wakeup
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
void SCB1_Wakeup(void)
{
#if(SCB1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SCB1_SCB_WAKE_ENABLE_CHECK)
    {
        if(SCB1_SCB_MODE_I2C_RUNTM_CFG)
        {
            SCB1_I2CRestoreConfig();
        }
        else if(SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SCB1_EzI2CRestoreConfig();
        }
    #if(!SCB1_CY_SCBIP_V1)
        else if(SCB1_SCB_MODE_SPI_RUNTM_CFG)
        {
            SCB1_SpiRestoreConfig();
        }
        else if(SCB1_SCB_MODE_UART_RUNTM_CFG)
        {
            SCB1_UartRestoreConfig();
        }
    #endif /* (!SCB1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SCB1_backup.enableState)
        {
            SCB1_Enable();
        }
    }

#else

    #if (SCB1_SCB_MODE_I2C_CONST_CFG  && SCB1_I2C_WAKE_ENABLE_CONST)
        SCB1_I2CRestoreConfig();

    #elif (SCB1_SCB_MODE_EZI2C_CONST_CFG && SCB1_EZI2C_WAKE_ENABLE_CONST)
        SCB1_EzI2CRestoreConfig();

    #elif (SCB1_SCB_MODE_SPI_CONST_CFG && SCB1_SPI_WAKE_ENABLE_CONST)
        SCB1_SpiRestoreConfig();

    #elif (SCB1_SCB_MODE_UART_CONST_CFG && SCB1_UART_WAKE_ENABLE_CONST)
        SCB1_UartRestoreConfig();

    #else

        if(0u != SCB1_backup.enableState)
        {
            SCB1_Enable();
        }

    #endif /* (SCB1_I2C_WAKE_ENABLE_CONST) */

#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
