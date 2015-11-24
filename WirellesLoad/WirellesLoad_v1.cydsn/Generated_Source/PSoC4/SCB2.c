/*******************************************************************************
* File Name: SCB2.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if (SCB2_SCB_MODE_I2C_INC)
    #include "SCB2_I2C_PVT.h"
#endif /* (SCB2_SCB_MODE_I2C_INC) */

#if (SCB2_SCB_MODE_EZI2C_INC)
    #include "SCB2_EZI2C_PVT.h"
#endif /* (SCB2_SCB_MODE_EZI2C_INC) */

#if (SCB2_SCB_MODE_SPI_INC || SCB2_SCB_MODE_UART_INC)
    #include "SCB2_SPI_UART_PVT.h"
#endif /* (SCB2_SCB_MODE_SPI_INC || SCB2_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 SCB2_scbMode = SCB2_SCB_MODE_UNCONFIG;
    uint8 SCB2_scbEnableWake;
    uint8 SCB2_scbEnableIntr;

    /* I2C configuration variables */
    uint8 SCB2_mode;
    uint8 SCB2_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * SCB2_rxBuffer;
    uint8  SCB2_rxDataBits;
    uint32 SCB2_rxBufferSize;

    volatile uint8 * SCB2_txBuffer;
    uint8  SCB2_txDataBits;
    uint32 SCB2_txBufferSize;

    /* EZI2C configuration variables */
    uint8 SCB2_numberOfAddr;
    uint8 SCB2_subAddrSize;
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 SCB2_initVar = 0u;

#if (SCB2_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SCB2_CUSTOM_INTR_HANDLER)
    void (*SCB2_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_SCB2_CUSTOM_INTR_HANDLER) */
#endif /* (SCB2_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void SCB2_ScbEnableIntr(void);
static void SCB2_ScbModeStop(void);
static void SCB2_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: SCB2_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_Init(void)
{
#if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SCB2_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SCB2_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (SCB2_SCB_MODE_I2C_CONST_CFG)
    SCB2_I2CInit();

#elif (SCB2_SCB_MODE_SPI_CONST_CFG)
    SCB2_SpiInit();

#elif (SCB2_SCB_MODE_UART_CONST_CFG)
    SCB2_UartInit();

#elif (SCB2_SCB_MODE_EZI2C_CONST_CFG)
    SCB2_EzI2CInit();

#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB2_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_Enable(void)
{
#if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!SCB2_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SCB2_CTRL_REG |= SCB2_CTRL_ENABLED;

        SCB2_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        SCB2_ScbModePostEnable();
    }
#else
    SCB2_CTRL_REG |= SCB2_CTRL_ENABLED;

    SCB2_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    SCB2_ScbModePostEnable();
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB2_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  SCB2_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void SCB2_Start(void)
{
    if (0u == SCB2_initVar)
    {
        SCB2_Init();
        SCB2_initVar = 1u; /* Component was initialized */
    }

    SCB2_Enable();
}


/*******************************************************************************
* Function Name: SCB2_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void SCB2_Stop(void)
{
#if (SCB2_SCB_IRQ_INTERNAL)
    SCB2_DisableInt();
#endif /* (SCB2_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    SCB2_ScbModeStop();

    /* Disable SCB IP */
    SCB2_CTRL_REG &= (uint32) ~SCB2_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    SCB2_SetTxInterruptMode(SCB2_NO_INTR_SOURCES);

#if (SCB2_SCB_IRQ_INTERNAL)
    SCB2_ClearPendingInt();
#endif /* (SCB2_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SCB2_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = SCB2_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~SCB2_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (SCB2_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SCB2_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: SCB2_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void SCB2_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = SCB2_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~SCB2_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (SCB2_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SCB2_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (SCB2_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: SCB2_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_SCB2_CUSTOM_INTR_HANDLER)
        SCB2_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_SCB2_CUSTOM_INTR_HANDLER) */
    }
#endif /* (SCB2_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: SCB2_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SCB2_ScbEnableIntr(void)
{
#if (SCB2_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != SCB2_scbEnableIntr)
        {
            SCB2_EnableInt();
        }

    #else
        SCB2_EnableInt();

    #endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (SCB2_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SCB2_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SCB2_ScbModePostEnable(void)
{
#if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!SCB2_CY_SCBIP_V1)
    if (SCB2_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB2_SpiPostEnable();
    }
    else if (SCB2_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB2_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!SCB2_CY_SCBIP_V1) */

#elif (SCB2_SCB_MODE_SPI_CONST_CFG)
    SCB2_SpiPostEnable();

#elif (SCB2_SCB_MODE_UART_CONST_CFG)
    SCB2_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB2_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SCB2_ScbModeStop(void)
{
#if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SCB2_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB2_I2CStop();
    }
    else if (SCB2_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB2_EzI2CStop();
    }
#if (!SCB2_CY_SCBIP_V1)
    else if (SCB2_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB2_SpiStop();
    }
    else if (SCB2_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB2_UartStop();
    }
#endif /* (!SCB2_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (SCB2_SCB_MODE_I2C_CONST_CFG)
    SCB2_I2CStop();

#elif (SCB2_SCB_MODE_EZI2C_CONST_CFG)
    SCB2_EzI2CStop();

#elif (SCB2_SCB_MODE_SPI_CONST_CFG)
    SCB2_SpiStop();

#elif (SCB2_SCB_MODE_UART_CONST_CFG)
    SCB2_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SCB2_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [SCB2_SCB_PINS_NUMBER];
        uint32 pinsDm   [SCB2_SCB_PINS_NUMBER];

    #if (!SCB2_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!SCB2_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < SCB2_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = SCB2_HSIOM_DEF_SEL;
            pinsDm[i]    = SCB2_PIN_DM_ALG_HIZ;
        }

        if ((SCB2_SCB_MODE_I2C   == mode) ||
           (SCB2_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[SCB2_RX_SCL_MOSI_PIN_INDEX] = SCB2_HSIOM_I2C_SEL;
            hsiomSel[SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_HSIOM_I2C_SEL;

            pinsDm[SCB2_RX_SCL_MOSI_PIN_INDEX] = SCB2_PIN_DM_OD_LO;
            pinsDm[SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_PIN_DM_OD_LO;
        }
    #if (!SCB2_CY_SCBIP_V1)
        else if (SCB2_SCB_MODE_SPI == mode)
        {
            hsiomSel[SCB2_RX_SCL_MOSI_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;
            hsiomSel[SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;
            hsiomSel[SCB2_SCLK_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;

            if (SCB2_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[SCB2_RX_SCL_MOSI_PIN_INDEX] = SCB2_PIN_DM_DIG_HIZ;
                pinsDm[SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_PIN_DM_STRONG;
                pinsDm[SCB2_SCLK_PIN_INDEX] = SCB2_PIN_DM_DIG_HIZ;

            #if (SCB2_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[SCB2_SS0_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;
                pinsDm  [SCB2_SS0_PIN_INDEX] = SCB2_PIN_DM_DIG_HIZ;
            #endif /* (SCB2_SS0_PIN) */

            #if (SCB2_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= SCB2_TX_SDA_MISO_PIN_MASK;
            #endif /* (SCB2_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[SCB2_RX_SCL_MOSI_PIN_INDEX] = SCB2_PIN_DM_STRONG;
                pinsDm[SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_PIN_DM_DIG_HIZ;
                pinsDm[SCB2_SCLK_PIN_INDEX] = SCB2_PIN_DM_STRONG;

            #if (SCB2_SS0_PIN)
                hsiomSel [SCB2_SS0_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;
                pinsDm   [SCB2_SS0_PIN_INDEX] = SCB2_PIN_DM_STRONG;
                pinsInBuf |= SCB2_SS0_PIN_MASK;
            #endif /* (SCB2_SS0_PIN) */

            #if (SCB2_SS1_PIN)
                hsiomSel [SCB2_SS1_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;
                pinsDm   [SCB2_SS1_PIN_INDEX] = SCB2_PIN_DM_STRONG;
                pinsInBuf |= SCB2_SS1_PIN_MASK;
            #endif /* (SCB2_SS1_PIN) */

            #if (SCB2_SS2_PIN)
                hsiomSel [SCB2_SS2_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;
                pinsDm   [SCB2_SS2_PIN_INDEX] = SCB2_PIN_DM_STRONG;
                pinsInBuf |= SCB2_SS2_PIN_MASK;
            #endif /* (SCB2_SS2_PIN) */

            #if (SCB2_SS3_PIN)
                hsiomSel [SCB2_SS3_PIN_INDEX] = SCB2_HSIOM_SPI_SEL;
                pinsDm   [SCB2_SS3_PIN_INDEX] = SCB2_PIN_DM_STRONG;
                pinsInBuf |= SCB2_SS3_PIN_MASK;
            #endif /* (SCB2_SS3_PIN) */

                /* Disable input buffers */
            #if (SCB2_RX_SCL_MOSI_PIN)
                pinsInBuf |= SCB2_RX_SCL_MOSI_PIN_MASK;
            #endif /* (SCB2_RX_SCL_MOSI_PIN) */

             #if (SCB2_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= SCB2_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (SCB2_RX_WAKE_SCL_MOSI_PIN) */

            #if (SCB2_SCLK_PIN)
                pinsInBuf |= SCB2_SCLK_PIN_MASK;
            #endif /* (SCB2_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (SCB2_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_HSIOM_UART_SEL;
                pinsDm  [SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (SCB2_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[SCB2_RX_SCL_MOSI_PIN_INDEX] = SCB2_HSIOM_UART_SEL;
                    pinsDm  [SCB2_RX_SCL_MOSI_PIN_INDEX] = SCB2_PIN_DM_DIG_HIZ;
                }

                if (0u != (SCB2_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_HSIOM_UART_SEL;
                    pinsDm  [SCB2_TX_SDA_MISO_PIN_INDEX] = SCB2_PIN_DM_STRONG;

                #if (SCB2_TX_SDA_MISO_PIN)
                     pinsInBuf |= SCB2_TX_SDA_MISO_PIN_MASK;
                #endif /* (SCB2_TX_SDA_MISO_PIN) */
                }

            #if !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
                if (SCB2_UART_MODE_STD == subMode)
                {
                    if (0u != (SCB2_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[SCB2_SCLK_PIN_INDEX] = SCB2_HSIOM_UART_SEL;
                        pinsDm  [SCB2_SCLK_PIN_INDEX] = SCB2_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (SCB2_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[SCB2_SS0_PIN_INDEX] = SCB2_HSIOM_UART_SEL;
                        pinsDm  [SCB2_SS0_PIN_INDEX] = SCB2_PIN_DM_STRONG;

                    #if (SCB2_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= SCB2_SS0_PIN_MASK;
                    #endif /* (SCB2_SS0_PIN) */
                    }
                }
            #endif /* !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */
            }
        }
    #endif /* (!SCB2_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (SCB2_RX_WAKE_SCL_MOSI_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       SCB2_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       SCB2_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[SCB2_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SCB2_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[SCB2_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SCB2_SET_INP_DIS(SCB2_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     SCB2_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SCB2_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        SCB2_SET_INCFG_TYPE(SCB2_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        SCB2_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        SCB2_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        SCB2_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (SCB2_RX_WAKE_SCL_MOSI_PIN) */

    #if (SCB2_RX_SCL_MOSI_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_RX_SCL_MOSI_HSIOM_REG,
                                       SCB2_RX_SCL_MOSI_HSIOM_MASK,
                                       SCB2_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[SCB2_RX_SCL_MOSI_PIN_INDEX]);

        SCB2_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[SCB2_RX_SCL_MOSI_PIN_INDEX]);

    #if (!SCB2_CY_SCBIP_V1)
        SCB2_SET_INP_DIS(SCB2_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     SCB2_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SCB2_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!SCB2_CY_SCBIP_V1) */
    #endif /* (SCB2_RX_SCL_MOSI_PIN) */

    #if (SCB2_TX_SDA_MISO_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_TX_SDA_MISO_HSIOM_REG,
                                       SCB2_TX_SDA_MISO_HSIOM_MASK,
                                       SCB2_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[SCB2_TX_SDA_MISO_PIN_INDEX]);

        SCB2_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[SCB2_TX_SDA_MISO_PIN_INDEX]);

    #if (!SCB2_CY_SCBIP_V1)
        SCB2_SET_INP_DIS(SCB2_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     SCB2_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & SCB2_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!SCB2_CY_SCBIP_V1) */
    #endif /* (SCB2_RX_SCL_MOSI_PIN) */

    #if (SCB2_SCLK_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_SCLK_HSIOM_REG,
                                       SCB2_SCLK_HSIOM_MASK,
                                       SCB2_SCLK_HSIOM_POS,
                                       hsiomSel[SCB2_SCLK_PIN_INDEX]);

        SCB2_spi_sclk_SetDriveMode((uint8) pinsDm[SCB2_SCLK_PIN_INDEX]);

        SCB2_SET_INP_DIS(SCB2_spi_sclk_INP_DIS,
                                     SCB2_spi_sclk_MASK,
                                     (0u != (pinsInBuf & SCB2_SCLK_PIN_MASK)));
    #endif /* (SCB2_SCLK_PIN) */

    #if (SCB2_SS0_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_SS0_HSIOM_REG,
                                       SCB2_SS0_HSIOM_MASK,
                                       SCB2_SS0_HSIOM_POS,
                                       hsiomSel[SCB2_SS0_PIN_INDEX]);

        SCB2_spi_ss0_SetDriveMode((uint8) pinsDm[SCB2_SS0_PIN_INDEX]);

        SCB2_SET_INP_DIS(SCB2_spi_ss0_INP_DIS,
                                     SCB2_spi_ss0_MASK,
                                     (0u != (pinsInBuf & SCB2_SS0_PIN_MASK)));
    #endif /* (SCB2_SS0_PIN) */

    #if (SCB2_SS1_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_SS1_HSIOM_REG,
                                       SCB2_SS1_HSIOM_MASK,
                                       SCB2_SS1_HSIOM_POS,
                                       hsiomSel[SCB2_SS1_PIN_INDEX]);

        SCB2_spi_ss1_SetDriveMode((uint8) pinsDm[SCB2_SS1_PIN_INDEX]);

        SCB2_SET_INP_DIS(SCB2_spi_ss1_INP_DIS,
                                     SCB2_spi_ss1_MASK,
                                     (0u != (pinsInBuf & SCB2_SS1_PIN_MASK)));
    #endif /* (SCB2_SS1_PIN) */

    #if (SCB2_SS2_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_SS2_HSIOM_REG,
                                       SCB2_SS2_HSIOM_MASK,
                                       SCB2_SS2_HSIOM_POS,
                                       hsiomSel[SCB2_SS2_PIN_INDEX]);

        SCB2_spi_ss2_SetDriveMode((uint8) pinsDm[SCB2_SS2_PIN_INDEX]);

        SCB2_SET_INP_DIS(SCB2_spi_ss2_INP_DIS,
                                     SCB2_spi_ss2_MASK,
                                     (0u != (pinsInBuf & SCB2_SS2_PIN_MASK)));
    #endif /* (SCB2_SS2_PIN) */

    #if (SCB2_SS3_PIN)
        SCB2_SET_HSIOM_SEL(SCB2_SS3_HSIOM_REG,
                                       SCB2_SS3_HSIOM_MASK,
                                       SCB2_SS3_HSIOM_POS,
                                       hsiomSel[SCB2_SS3_PIN_INDEX]);

        SCB2_spi_ss3_SetDriveMode((uint8) pinsDm[SCB2_SS3_PIN_INDEX]);

        SCB2_SET_INP_DIS(SCB2_spi_ss3_INP_DIS,
                                     SCB2_spi_ss3_MASK,
                                     (0u != (pinsInBuf & SCB2_SS3_PIN_MASK)));
    #endif /* (SCB2_SS3_PIN) */
    }

#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SCB2_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (SCB2_CTRL_REG & SCB2_CTRL_EC_AM_MODE)) &&
            (0u == (SCB2_I2C_CTRL_REG & SCB2_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            SCB2_CTRL_REG &= ~SCB2_CTRL_EC_AM_MODE;
            SCB2_CTRL_REG |=  SCB2_CTRL_EC_AM_MODE;
        }

        SCB2_I2C_SLAVE_CMD_REG = SCB2_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */


/* [] END OF FILE */
