/*******************************************************************************
* File Name: SCB1_I2C.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB1_PVT.h"
#include "SCB1_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 SCB1_state;  /* Current state of I2C FSM */

#if(SCB1_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const SCB1_I2C_INIT_STRUCT SCB1_configI2C =
    {
        SCB1_I2C_MODE,
        SCB1_I2C_OVS_FACTOR_LOW,
        SCB1_I2C_OVS_FACTOR_HIGH,
        SCB1_I2C_MEDIAN_FILTER_ENABLE,
        SCB1_I2C_SLAVE_ADDRESS,
        SCB1_I2C_SLAVE_ADDRESS_MASK,
        SCB1_I2C_ACCEPT_ADDRESS,
        SCB1_I2C_WAKE_ENABLE,
        SCB1_I2C_BYTE_MODE_ENABLE,
        SCB1_I2C_DATA_RATE,
        SCB1_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: SCB1_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB1_I2CInit(const SCB1_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            SCB1_SetPins(SCB1_SCB_MODE_I2C, SCB1_DUMMY_PARAM,
                                     SCB1_DUMMY_PARAM);

            /* Store internal configuration */
            SCB1_scbMode       = (uint8) SCB1_SCB_MODE_I2C;
            SCB1_scbEnableWake = (uint8) config->enableWake;
            SCB1_scbEnableIntr = (uint8) SCB1_SCB_IRQ_INTERNAL;

            SCB1_mode          = (uint8) config->mode;
            SCB1_acceptAddr    = (uint8) config->acceptAddr;

        #if (SCB1_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            SCB1_SET_I2C_CFG_SDA_FILT_TRIM(SCB1_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (SCB1_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((SCB1_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= SCB1_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (SCB1_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                SCB1_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = SCB1_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                SCB1_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = SCB1_DIGITAL_FILTER_ENABLE;
            }

        #if (!SCB1_CY_SCBIP_V0)
            locEnableWake = (SCB1_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!SCB1_CY_SCBIP_V0) */

            /* Configure I2C interface */
            SCB1_CTRL_REG     = SCB1_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            SCB1_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            SCB1_GET_CTRL_EC_AM_MODE (locEnableWake);

            SCB1_I2C_CTRL_REG = SCB1_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    SCB1_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    SCB1_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    SCB1_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            SCB1_RX_CTRL_REG      = SCB1_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                SCB1_I2C_RX_CTRL;
            SCB1_RX_FIFO_CTRL_REG = SCB1_CLEAR_REG;

            /* Set default address and mask */
            SCB1_RX_MATCH_REG    = ((SCB1_I2C_SLAVE) ?
                                                (SCB1_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 SCB1_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (SCB1_CLEAR_REG));


            /* Configure TX direction */
            SCB1_TX_CTRL_REG      = SCB1_I2C_TX_CTRL;
            SCB1_TX_FIFO_CTRL_REG = SCB1_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (SCB1_ISR_NUMBER);
            CyIntSetPriority(SCB1_ISR_NUMBER, SCB1_ISR_PRIORITY);
            (void) CyIntSetVector(SCB1_ISR_NUMBER, &SCB1_I2C_ISR);

            /* Configure interrupt sources */
        #if(!SCB1_CY_SCBIP_V1)
            SCB1_INTR_SPI_EC_MASK_REG = SCB1_NO_INTR_SOURCES;
        #endif /* (!SCB1_CY_SCBIP_V1) */

            SCB1_INTR_I2C_EC_MASK_REG = SCB1_NO_INTR_SOURCES;
            SCB1_INTR_RX_MASK_REG     = SCB1_NO_INTR_SOURCES;
            SCB1_INTR_TX_MASK_REG     = SCB1_NO_INTR_SOURCES;

            SCB1_INTR_SLAVE_MASK_REG  = ((SCB1_I2C_SLAVE) ?
                            (SCB1_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             SCB1_I2C_INTR_SLAVE_MASK) : (SCB1_CLEAR_REG));

            SCB1_INTR_MASTER_MASK_REG = ((SCB1_I2C_MASTER) ?
                                                     (SCB1_I2C_INTR_MASTER_MASK) :
                                                     (SCB1_CLEAR_REG));

            /* Configure global variables */
            SCB1_state = SCB1_I2C_FSM_IDLE;

            /* Internal slave variables */
            SCB1_slStatus        = 0u;
            SCB1_slRdBufIndex    = 0u;
            SCB1_slWrBufIndex    = 0u;
            SCB1_slOverFlowCount = 0u;

            /* Internal master variables */
            SCB1_mstrStatus     = 0u;
            SCB1_mstrRdBufIndex = 0u;
            SCB1_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SCB1_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB1_I2CInit(void)
    {
    #if(SCB1_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        SCB1_SET_I2C_CFG_SDA_FILT_TRIM(SCB1_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (SCB1_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        SCB1_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        SCB1_CTRL_REG     = SCB1_I2C_DEFAULT_CTRL;
        SCB1_I2C_CTRL_REG = SCB1_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        SCB1_RX_CTRL_REG      = SCB1_I2C_DEFAULT_RX_CTRL;
        SCB1_RX_FIFO_CTRL_REG = SCB1_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        SCB1_RX_MATCH_REG     = SCB1_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        SCB1_TX_CTRL_REG      = SCB1_I2C_DEFAULT_TX_CTRL;
        SCB1_TX_FIFO_CTRL_REG = SCB1_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (SCB1_ISR_NUMBER);
        CyIntSetPriority(SCB1_ISR_NUMBER, SCB1_ISR_PRIORITY);
    #if(!SCB1_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(SCB1_ISR_NUMBER, &SCB1_I2C_ISR);
    #endif /* (SCB1_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!SCB1_CY_SCBIP_V1)
        SCB1_INTR_SPI_EC_MASK_REG = SCB1_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!SCB1_CY_SCBIP_V1) */

        SCB1_INTR_I2C_EC_MASK_REG = SCB1_I2C_DEFAULT_INTR_I2C_EC_MASK;
        SCB1_INTR_SLAVE_MASK_REG  = SCB1_I2C_DEFAULT_INTR_SLAVE_MASK;
        SCB1_INTR_MASTER_MASK_REG = SCB1_I2C_DEFAULT_INTR_MASTER_MASK;
        SCB1_INTR_RX_MASK_REG     = SCB1_I2C_DEFAULT_INTR_RX_MASK;
        SCB1_INTR_TX_MASK_REG     = SCB1_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        SCB1_state = SCB1_I2C_FSM_IDLE;

    #if(SCB1_I2C_SLAVE)
        /* Internal slave variable */
        SCB1_slStatus        = 0u;
        SCB1_slRdBufIndex    = 0u;
        SCB1_slWrBufIndex    = 0u;
        SCB1_slOverFlowCount = 0u;
    #endif /* (SCB1_I2C_SLAVE) */

    #if(SCB1_I2C_MASTER)
    /* Internal master variable */
        SCB1_mstrStatus     = 0u;
        SCB1_mstrRdBufIndex = 0u;
        SCB1_mstrWrBufIndex = 0u;
    #endif /* (SCB1_I2C_MASTER) */
    }
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SCB1_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB1_I2CStop(void)
{
    SCB1_state = SCB1_I2C_FSM_IDLE;
}


#if(SCB1_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SCB1_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables SCB1_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB1_I2CSaveConfig(void)
    {
    #if (!SCB1_CY_SCBIP_V0)
        #if (SCB1_I2C_MULTI_MASTER_SLAVE_CONST && SCB1_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (SCB1_CTRL_REG & SCB1_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                SCB1_Stop();
                SCB1_CTRL_REG |= SCB1_CTRL_EC_AM_MODE;
                SCB1_Enable();
            }
        #endif /* (SCB1_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (SCB1_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            SCB1_SCBCLK_Stop();
        #endif /* (SCB1_SCB_CLK_INTERNAL) */
    #endif /* (!SCB1_CY_SCBIP_V0) */

        SCB1_SetI2CExtClkInterruptMode(SCB1_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SCB1_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables SCB1_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB1_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        SCB1_SetI2CExtClkInterruptMode(SCB1_NO_INTR_SOURCES);

    #if (!SCB1_CY_SCBIP_V0)
        #if (SCB1_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            SCB1_SCBCLK_Start();
        #endif /* (SCB1_SCB_CLK_INTERNAL) */
    #endif /* (!SCB1_CY_SCBIP_V0) */
    }
#endif /* (SCB1_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
