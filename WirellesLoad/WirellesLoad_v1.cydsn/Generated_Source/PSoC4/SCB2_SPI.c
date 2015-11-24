/*******************************************************************************
* File Name: SCB2_SPI.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB2_PVT.h"
#include "SCB2_SPI_UART_PVT.h"

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const SCB2_SPI_INIT_STRUCT SCB2_configSpi =
    {
        SCB2_SPI_MODE,
        SCB2_SPI_SUB_MODE,
        SCB2_SPI_CLOCK_MODE,
        SCB2_SPI_OVS_FACTOR,
        SCB2_SPI_MEDIAN_FILTER_ENABLE,
        SCB2_SPI_LATE_MISO_SAMPLE_ENABLE,
        SCB2_SPI_WAKE_ENABLE,
        SCB2_SPI_RX_DATA_BITS_NUM,
        SCB2_SPI_TX_DATA_BITS_NUM,
        SCB2_SPI_BITS_ORDER,
        SCB2_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) SCB2_SCB_IRQ_INTERNAL,
        SCB2_SPI_INTR_RX_MASK,
        SCB2_SPI_RX_TRIGGER_LEVEL,
        SCB2_SPI_INTR_TX_MASK,
        SCB2_SPI_TX_TRIGGER_LEVEL,
        (uint8) SCB2_SPI_BYTE_MODE_ENABLE,
        (uint8) SCB2_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) SCB2_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: SCB2_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the SPI operation.
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
    void SCB2_SpiInit(const SCB2_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            SCB2_SetPins(SCB2_SCB_MODE_SPI, config->mode, SCB2_DUMMY_PARAM);

            /* Store internal configuration */
            SCB2_scbMode       = (uint8) SCB2_SCB_MODE_SPI;
            SCB2_scbEnableWake = (uint8) config->enableWake;
            SCB2_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SCB2_rxBuffer      =         config->rxBuffer;
            SCB2_rxDataBits    = (uint8) config->rxDataBits;
            SCB2_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            SCB2_txBuffer      =         config->txBuffer;
            SCB2_txDataBits    = (uint8) config->txDataBits;
            SCB2_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure SPI interface */
            SCB2_CTRL_REG     = SCB2_GET_CTRL_OVS(config->oversample)           |
                                            SCB2_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            SCB2_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            SCB2_CTRL_SPI;

            SCB2_SPI_CTRL_REG = SCB2_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            SCB2_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          SCB2_SPI_MODE_TI_PRECEDES_MASK) |
                                            SCB2_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            SCB2_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            SCB2_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            SCB2_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            SCB2_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            SCB2_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            SCB2_RX_CTRL_REG     =  SCB2_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                SCB2_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                SCB2_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                SCB2_SPI_RX_CTRL;

            SCB2_RX_FIFO_CTRL_REG = SCB2_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            SCB2_TX_CTRL_REG      = SCB2_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                SCB2_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                SCB2_SPI_TX_CTRL;

            SCB2_TX_FIFO_CTRL_REG = SCB2_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (SCB2_ISR_NUMBER);
            CyIntSetPriority(SCB2_ISR_NUMBER, SCB2_ISR_PRIORITY);
            (void) CyIntSetVector(SCB2_ISR_NUMBER, &SCB2_SPI_UART_ISR);

            /* Configure interrupt sources */
            SCB2_INTR_I2C_EC_MASK_REG = SCB2_NO_INTR_SOURCES;
            SCB2_INTR_SPI_EC_MASK_REG = SCB2_NO_INTR_SOURCES;
            SCB2_INTR_SLAVE_MASK_REG  = SCB2_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            SCB2_INTR_MASTER_MASK_REG = SCB2_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            SCB2_INTR_RX_MASK_REG     = SCB2_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            SCB2_INTR_TX_MASK_REG     = SCB2_GET_SPI_INTR_TX_MASK(config->txInterruptMask);

            /* Set active SS0 */
            SCB2_SpiSetActiveSlaveSelect(SCB2_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            SCB2_rxBufferHead     = 0u;
            SCB2_rxBufferTail     = 0u;
            SCB2_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            SCB2_txBufferHead = 0u;
            SCB2_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SCB2_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the SPI operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiInit(void)
    {
        /* Configure SPI interface */
        SCB2_CTRL_REG     = SCB2_SPI_DEFAULT_CTRL;
        SCB2_SPI_CTRL_REG = SCB2_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        SCB2_RX_CTRL_REG      = SCB2_SPI_DEFAULT_RX_CTRL;
        SCB2_RX_FIFO_CTRL_REG = SCB2_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        SCB2_TX_CTRL_REG      = SCB2_SPI_DEFAULT_TX_CTRL;
        SCB2_TX_FIFO_CTRL_REG = SCB2_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(SCB2_SCB_IRQ_INTERNAL)
            CyIntDisable    (SCB2_ISR_NUMBER);
            CyIntSetPriority(SCB2_ISR_NUMBER, SCB2_ISR_PRIORITY);
            (void) CyIntSetVector(SCB2_ISR_NUMBER, &SCB2_SPI_UART_ISR);
    #endif /* (SCB2_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        SCB2_INTR_I2C_EC_MASK_REG = SCB2_SPI_DEFAULT_INTR_I2C_EC_MASK;
        SCB2_INTR_SPI_EC_MASK_REG = SCB2_SPI_DEFAULT_INTR_SPI_EC_MASK;
        SCB2_INTR_SLAVE_MASK_REG  = SCB2_SPI_DEFAULT_INTR_SLAVE_MASK;
        SCB2_INTR_MASTER_MASK_REG = SCB2_SPI_DEFAULT_INTR_MASTER_MASK;
        SCB2_INTR_RX_MASK_REG     = SCB2_SPI_DEFAULT_INTR_RX_MASK;
        SCB2_INTR_TX_MASK_REG     = SCB2_SPI_DEFAULT_INTR_TX_MASK;

        /* Set active SS0 for master */
    #if (SCB2_SPI_MASTER_CONST)
        SCB2_SpiSetActiveSlaveSelect(SCB2_SPI_SLAVE_SELECT0);
    #endif /* (SCB2_SPI_MASTER_CONST) */

    #if(SCB2_INTERNAL_RX_SW_BUFFER_CONST)
        SCB2_rxBufferHead     = 0u;
        SCB2_rxBufferTail     = 0u;
        SCB2_rxBufferOverflow = 0u;
    #endif /* (SCB2_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(SCB2_INTERNAL_TX_SW_BUFFER_CONST)
        SCB2_txBufferHead = 0u;
        SCB2_txBufferTail = 0u;
    #endif /* (SCB2_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SCB2_SpiPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_SpiPostEnable(void)
{
#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SCB2_CHECK_SPI_MASTER)
    {
    #if (SCB2_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SCLK_HSIOM_REG, SCB2_SCLK_HSIOM_MASK,
                                       SCB2_SCLK_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
    #endif /* (SCB2_SCLK_PIN) */

    #if (SCB2_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS0_HSIOM_REG, SCB2_SS0_HSIOM_MASK,
                                       SCB2_SS0_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
    #endif /* (SCB2_SS0_PIN) */

    #if (SCB2_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS1_HSIOM_REG, SCB2_SS1_HSIOM_MASK,
                                       SCB2_SS1_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
    #endif /* (SCB2_SS1_PIN) */

    #if (SCB2_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS2_HSIOM_REG, SCB2_SS2_HSIOM_MASK,
                                       SCB2_SS2_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
    #endif /* (SCB2_SS2_PIN) */

    #if (SCB2_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS3_HSIOM_REG, SCB2_SS3_HSIOM_MASK,
                                       SCB2_SS3_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
    #endif /* (SCB2_SS3_PIN) */
    }

#else

#if (SCB2_SPI_MASTER_SCLK_PIN)
    /* Set SCB SPI to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SCLK_M_HSIOM_REG, SCB2_SCLK_M_HSIOM_MASK,
                                   SCB2_SCLK_M_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
#endif /* (SCB2_MISO_SDA_TX_PIN_PIN) */

#if (SCB2_SPI_MASTER_SS0_PIN)
    /* Set SCB SPI to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS0_M_HSIOM_REG, SCB2_SS0_M_HSIOM_MASK,
                                   SCB2_SS0_M_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
#endif /* (SCB2_SPI_MASTER_SS0_PIN) */

#if (SCB2_SPI_MASTER_SS1_PIN)
    /* Set SCB SPI to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS1_M_HSIOM_REG, SCB2_SS1_M_HSIOM_MASK,
                                   SCB2_SS1_M_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
#endif /* (SCB2_SPI_MASTER_SS1_PIN) */

#if (SCB2_SPI_MASTER_SS2_PIN)
    /* Set SCB SPI to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS2_M_HSIOM_REG, SCB2_SS2_M_HSIOM_MASK,
                                   SCB2_SS2_M_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
#endif /* (SCB2_SPI_MASTER_SS2_PIN) */

#if (SCB2_SPI_MASTER_SS3_PIN)
    /* Set SCB SPI to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS3_M_HSIOM_REG, SCB2_SS3_M_HSIOM_MASK,
                                   SCB2_SS3_M_HSIOM_POS, SCB2_HSIOM_SPI_SEL);
#endif /* (SCB2_SPI_MASTER_SS3_PIN) */

#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB2_SpiStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) to
*  keep them inactive after the block is disabled. The output pins are
*  controlled by the GPIO data register.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_SpiStop(void)
{
#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SCB2_CHECK_SPI_MASTER)
    {
    #if (SCB2_SCLK_PIN)
        /* Set output pin state after block is disabled */
        SCB2_spi_sclk_Write(SCB2_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SCLK_HSIOM_REG, SCB2_SCLK_HSIOM_MASK,
                                       SCB2_SCLK_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
    #endif /* (SCB2_MISO_SDA_TX_PIN_PIN) */

    #if (SCB2_SS0_PIN)
        /* Set output pin state after block is disabled */
        SCB2_spi_ss0_Write(SCB2_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS0_HSIOM_REG, SCB2_SS0_HSIOM_MASK,
                                       SCB2_SS0_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
    #endif /* (SCB2_SS0_PIN) */

    #if (SCB2_SS1_PIN)
        /* Set output pin state after block is disabled */
        SCB2_spi_ss1_Write(SCB2_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS1_HSIOM_REG, SCB2_SS1_HSIOM_MASK,
                                       SCB2_SS1_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
    #endif /* (SCB2_SS1_PIN) */

    #if (SCB2_SS2_PIN)
        /* Set output pin state after block is disabled */
        SCB2_spi_ss2_Write(SCB2_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS2_HSIOM_REG, SCB2_SS2_HSIOM_MASK,
                                       SCB2_SS2_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
    #endif /* (SCB2_SS2_PIN) */

    #if (SCB2_SS3_PIN)
        /* Set output pin state after block is disabled */
        SCB2_spi_ss3_Write(SCB2_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB2_SET_HSIOM_SEL(SCB2_SS3_HSIOM_REG, SCB2_SS3_HSIOM_MASK,
                                       SCB2_SS3_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
    #endif /* (SCB2_SS3_PIN) */
    }

#else

#if (SCB2_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    SCB2_sclk_m_Write(SCB2_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SCLK_M_HSIOM_REG, SCB2_SCLK_M_HSIOM_MASK,
                                   SCB2_SCLK_M_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
#endif /* (SCB2_MISO_SDA_TX_PIN_PIN) */

#if (SCB2_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    SCB2_ss0_m_Write(SCB2_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS0_M_HSIOM_REG, SCB2_SS0_M_HSIOM_MASK,
                                   SCB2_SS0_M_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
#endif /* (SCB2_SPI_MASTER_SS0_PIN) */

#if (SCB2_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    SCB2_ss1_m_Write(SCB2_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS1_M_HSIOM_REG, SCB2_SS1_M_HSIOM_MASK,
                                   SCB2_SS1_M_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
#endif /* (SCB2_SPI_MASTER_SS1_PIN) */

#if (SCB2_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    SCB2_ss2_m_Write(SCB2_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS2_M_HSIOM_REG, SCB2_SS2_M_HSIOM_MASK,
                                   SCB2_SS2_M_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
#endif /* (SCB2_SPI_MASTER_SS2_PIN) */

#if (SCB2_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    SCB2_ss3_m_Write(SCB2_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB2_SET_HSIOM_SEL(SCB2_SS3_M_HSIOM_REG, SCB2_SS3_M_HSIOM_MASK,
                                   SCB2_SS3_M_HSIOM_POS, SCB2_HSIOM_GPIO_SEL);
#endif /* (SCB2_SPI_MASTER_SS3_PIN) */

#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SCB2_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: SCB2_SetActiveSlaveSelect
    ********************************************************************************
    *
    * Summary:
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set)
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    * Parameters:
    *  slaveSelect: slave select line which will be active while the following
    *               transfer.
    *   SCB2_SPI_SLAVE_SELECT0 - Slave select 0
    *   SCB2_SPI_SLAVE_SELECT1 - Slave select 1
    *   SCB2_SPI_SLAVE_SELECT2 - Slave select 2
    *   SCB2_SPI_SLAVE_SELECT3 - Slave select 3
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = SCB2_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~SCB2_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  SCB2_GET_SPI_CTRL_SS(slaveSelect);

        SCB2_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (SCB2_SPI_MASTER_CONST) */


#if !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SCB2_SpiSetSlaveSelectPolarity
    ********************************************************************************
    *
    * Summary:
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  This function does not check that these conditions are met.
    *
    * Parameters:
    *  slaveSelect: slave select line to change active polarity.
    *   SCB2_SPI_SLAVE_SELECT0 - Slave select 0
    *   SCB2_SPI_SLAVE_SELECT1 - Slave select 1
    *   SCB2_SPI_SLAVE_SELECT2 - Slave select 2
    *   SCB2_SPI_SLAVE_SELECT3 - Slave select 3
    *
    *  polarity: active polarity of slave select line.
    *   SCB2_SPI_SS_ACTIVE_LOW  - Slave select is active low
    *   SCB2_SPI_SS_ACTIVE_HIGH - Slave select is active high
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = SCB2_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            SCB2_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            SCB2_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */


#if(SCB2_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SCB2_SpiSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiSaveConfig(void)
    {
        SCB2_ClearSpiExtClkInterruptSource(SCB2_INTR_SPI_EC_WAKE_UP);
        SCB2_SetSpiExtClkInterruptMode(SCB2_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SCB2_SpiRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiRestoreConfig(void)
    {
        SCB2_SetSpiExtClkInterruptMode(SCB2_NO_INTR_SOURCES);
    }
#endif /* (SCB2_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
