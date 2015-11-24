/*******************************************************************************
* File Name: SCB1.c
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

#include "SCB1_PVT.h"

#if (SCB1_SCB_MODE_I2C_INC)
    #include "SCB1_I2C_PVT.h"
#endif /* (SCB1_SCB_MODE_I2C_INC) */

#if (SCB1_SCB_MODE_EZI2C_INC)
    #include "SCB1_EZI2C_PVT.h"
#endif /* (SCB1_SCB_MODE_EZI2C_INC) */

#if (SCB1_SCB_MODE_SPI_INC || SCB1_SCB_MODE_UART_INC)
    #include "SCB1_SPI_UART_PVT.h"
#endif /* (SCB1_SCB_MODE_SPI_INC || SCB1_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 SCB1_scbMode = SCB1_SCB_MODE_UNCONFIG;
    uint8 SCB1_scbEnableWake;
    uint8 SCB1_scbEnableIntr;

    /* I2C configuration variables */
    uint8 SCB1_mode;
    uint8 SCB1_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * SCB1_rxBuffer;
    uint8  SCB1_rxDataBits;
    uint32 SCB1_rxBufferSize;

    volatile uint8 * SCB1_txBuffer;
    uint8  SCB1_txDataBits;
    uint32 SCB1_txBufferSize;

    /* EZI2C configuration variables */
    uint8 SCB1_numberOfAddr;
    uint8 SCB1_subAddrSize;
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 SCB1_initVar = 0u;

#if (SCB1_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SCB1_CUSTOM_INTR_HANDLER)
    void (*SCB1_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_SCB1_CUSTOM_INTR_HANDLER) */
#endif /* (SCB1_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void SCB1_ScbEnableIntr(void);
static void SCB1_ScbModeStop(void);
static void SCB1_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: SCB1_Init
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
void SCB1_Init(void)
{
#if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SCB1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SCB1_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (SCB1_SCB_MODE_I2C_CONST_CFG)
    SCB1_I2CInit();

#elif (SCB1_SCB_MODE_SPI_CONST_CFG)
    SCB1_SpiInit();

#elif (SCB1_SCB_MODE_UART_CONST_CFG)
    SCB1_UartInit();

#elif (SCB1_SCB_MODE_EZI2C_CONST_CFG)
    SCB1_EzI2CInit();

#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB1_Enable
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
void SCB1_Enable(void)
{
#if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!SCB1_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SCB1_CTRL_REG |= SCB1_CTRL_ENABLED;

        SCB1_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        SCB1_ScbModePostEnable();
    }
#else
    SCB1_CTRL_REG |= SCB1_CTRL_ENABLED;

    SCB1_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    SCB1_ScbModePostEnable();
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB1_Start
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
*  SCB1_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void SCB1_Start(void)
{
    if (0u == SCB1_initVar)
    {
        SCB1_Init();
        SCB1_initVar = 1u; /* Component was initialized */
    }

    SCB1_Enable();
}


/*******************************************************************************
* Function Name: SCB1_Stop
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
void SCB1_Stop(void)
{
#if (SCB1_SCB_IRQ_INTERNAL)
    SCB1_DisableInt();
#endif /* (SCB1_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    SCB1_ScbModeStop();

    /* Disable SCB IP */
    SCB1_CTRL_REG &= (uint32) ~SCB1_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    SCB1_SetTxInterruptMode(SCB1_NO_INTR_SOURCES);

#if (SCB1_SCB_IRQ_INTERNAL)
    SCB1_ClearPendingInt();
#endif /* (SCB1_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SCB1_SetRxFifoLevel
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
void SCB1_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = SCB1_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~SCB1_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (SCB1_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SCB1_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: SCB1_SetTxFifoLevel
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
void SCB1_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = SCB1_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~SCB1_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (SCB1_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SCB1_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (SCB1_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: SCB1_SetCustomInterruptHandler
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
    void SCB1_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_SCB1_CUSTOM_INTR_HANDLER)
        SCB1_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_SCB1_CUSTOM_INTR_HANDLER) */
    }
#endif /* (SCB1_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: SCB1_ScbModeEnableIntr
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
static void SCB1_ScbEnableIntr(void)
{
#if (SCB1_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != SCB1_scbEnableIntr)
        {
            SCB1_EnableInt();
        }

    #else
        SCB1_EnableInt();

    #endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (SCB1_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SCB1_ScbModePostEnable
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
static void SCB1_ScbModePostEnable(void)
{
#if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!SCB1_CY_SCBIP_V1)
    if (SCB1_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB1_SpiPostEnable();
    }
    else if (SCB1_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB1_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!SCB1_CY_SCBIP_V1) */

#elif (SCB1_SCB_MODE_SPI_CONST_CFG)
    SCB1_SpiPostEnable();

#elif (SCB1_SCB_MODE_UART_CONST_CFG)
    SCB1_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SCB1_ScbModeStop
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
static void SCB1_ScbModeStop(void)
{
#if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SCB1_SCB_MODE_I2C_RUNTM_CFG)
    {
        SCB1_I2CStop();
    }
    else if (SCB1_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SCB1_EzI2CStop();
    }
#if (!SCB1_CY_SCBIP_V1)
    else if (SCB1_SCB_MODE_SPI_RUNTM_CFG)
    {
        SCB1_SpiStop();
    }
    else if (SCB1_SCB_MODE_UART_RUNTM_CFG)
    {
        SCB1_UartStop();
    }
#endif /* (!SCB1_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (SCB1_SCB_MODE_I2C_CONST_CFG)
    SCB1_I2CStop();

#elif (SCB1_SCB_MODE_EZI2C_CONST_CFG)
    SCB1_EzI2CStop();

#elif (SCB1_SCB_MODE_SPI_CONST_CFG)
    SCB1_SpiStop();

#elif (SCB1_SCB_MODE_UART_CONST_CFG)
    SCB1_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SCB1_SetPins
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
    void SCB1_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [SCB1_SCB_PINS_NUMBER];
        uint32 pinsDm   [SCB1_SCB_PINS_NUMBER];

    #if (!SCB1_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!SCB1_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < SCB1_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = SCB1_HSIOM_DEF_SEL;
            pinsDm[i]    = SCB1_PIN_DM_ALG_HIZ;
        }

        if ((SCB1_SCB_MODE_I2C   == mode) ||
           (SCB1_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[SCB1_RX_SCL_MOSI_PIN_INDEX] = SCB1_HSIOM_I2C_SEL;
            hsiomSel[SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_HSIOM_I2C_SEL;

            pinsDm[SCB1_RX_SCL_MOSI_PIN_INDEX] = SCB1_PIN_DM_OD_LO;
            pinsDm[SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_PIN_DM_OD_LO;
        }
    #if (!SCB1_CY_SCBIP_V1)
        else if (SCB1_SCB_MODE_SPI == mode)
        {
            hsiomSel[SCB1_RX_SCL_MOSI_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;
            hsiomSel[SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;
            hsiomSel[SCB1_SCLK_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;

            if (SCB1_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[SCB1_RX_SCL_MOSI_PIN_INDEX] = SCB1_PIN_DM_DIG_HIZ;
                pinsDm[SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_PIN_DM_STRONG;
                pinsDm[SCB1_SCLK_PIN_INDEX] = SCB1_PIN_DM_DIG_HIZ;

            #if (SCB1_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[SCB1_SS0_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;
                pinsDm  [SCB1_SS0_PIN_INDEX] = SCB1_PIN_DM_DIG_HIZ;
            #endif /* (SCB1_SS0_PIN) */

            #if (SCB1_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= SCB1_TX_SDA_MISO_PIN_MASK;
            #endif /* (SCB1_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[SCB1_RX_SCL_MOSI_PIN_INDEX] = SCB1_PIN_DM_STRONG;
                pinsDm[SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_PIN_DM_DIG_HIZ;
                pinsDm[SCB1_SCLK_PIN_INDEX] = SCB1_PIN_DM_STRONG;

            #if (SCB1_SS0_PIN)
                hsiomSel [SCB1_SS0_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;
                pinsDm   [SCB1_SS0_PIN_INDEX] = SCB1_PIN_DM_STRONG;
                pinsInBuf |= SCB1_SS0_PIN_MASK;
            #endif /* (SCB1_SS0_PIN) */

            #if (SCB1_SS1_PIN)
                hsiomSel [SCB1_SS1_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;
                pinsDm   [SCB1_SS1_PIN_INDEX] = SCB1_PIN_DM_STRONG;
                pinsInBuf |= SCB1_SS1_PIN_MASK;
            #endif /* (SCB1_SS1_PIN) */

            #if (SCB1_SS2_PIN)
                hsiomSel [SCB1_SS2_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;
                pinsDm   [SCB1_SS2_PIN_INDEX] = SCB1_PIN_DM_STRONG;
                pinsInBuf |= SCB1_SS2_PIN_MASK;
            #endif /* (SCB1_SS2_PIN) */

            #if (SCB1_SS3_PIN)
                hsiomSel [SCB1_SS3_PIN_INDEX] = SCB1_HSIOM_SPI_SEL;
                pinsDm   [SCB1_SS3_PIN_INDEX] = SCB1_PIN_DM_STRONG;
                pinsInBuf |= SCB1_SS3_PIN_MASK;
            #endif /* (SCB1_SS3_PIN) */

                /* Disable input buffers */
            #if (SCB1_RX_SCL_MOSI_PIN)
                pinsInBuf |= SCB1_RX_SCL_MOSI_PIN_MASK;
            #endif /* (SCB1_RX_SCL_MOSI_PIN) */

             #if (SCB1_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= SCB1_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (SCB1_RX_WAKE_SCL_MOSI_PIN) */

            #if (SCB1_SCLK_PIN)
                pinsInBuf |= SCB1_SCLK_PIN_MASK;
            #endif /* (SCB1_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (SCB1_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_HSIOM_UART_SEL;
                pinsDm  [SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (SCB1_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[SCB1_RX_SCL_MOSI_PIN_INDEX] = SCB1_HSIOM_UART_SEL;
                    pinsDm  [SCB1_RX_SCL_MOSI_PIN_INDEX] = SCB1_PIN_DM_DIG_HIZ;
                }

                if (0u != (SCB1_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_HSIOM_UART_SEL;
                    pinsDm  [SCB1_TX_SDA_MISO_PIN_INDEX] = SCB1_PIN_DM_STRONG;

                #if (SCB1_TX_SDA_MISO_PIN)
                     pinsInBuf |= SCB1_TX_SDA_MISO_PIN_MASK;
                #endif /* (SCB1_TX_SDA_MISO_PIN) */
                }

            #if !(SCB1_CY_SCBIP_V0 || SCB1_CY_SCBIP_V1)
                if (SCB1_UART_MODE_STD == subMode)
                {
                    if (0u != (SCB1_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[SCB1_SCLK_PIN_INDEX] = SCB1_HSIOM_UART_SEL;
                        pinsDm  [SCB1_SCLK_PIN_INDEX] = SCB1_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (SCB1_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[SCB1_SS0_PIN_INDEX] = SCB1_HSIOM_UART_SEL;
                        pinsDm  [SCB1_SS0_PIN_INDEX] = SCB1_PIN_DM_STRONG;

                    #if (SCB1_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= SCB1_SS0_PIN_MASK;
                    #endif /* (SCB1_SS0_PIN) */
                    }
                }
            #endif /* !(SCB1_CY_SCBIP_V0 || SCB1_CY_SCBIP_V1) */
            }
        }
    #endif /* (!SCB1_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (SCB1_RX_WAKE_SCL_MOSI_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       SCB1_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       SCB1_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[SCB1_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SCB1_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[SCB1_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SCB1_SET_INP_DIS(SCB1_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     SCB1_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SCB1_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        SCB1_SET_INCFG_TYPE(SCB1_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        SCB1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        SCB1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        SCB1_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (SCB1_RX_WAKE_SCL_MOSI_PIN) */

    #if (SCB1_RX_SCL_MOSI_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_RX_SCL_MOSI_HSIOM_REG,
                                       SCB1_RX_SCL_MOSI_HSIOM_MASK,
                                       SCB1_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[SCB1_RX_SCL_MOSI_PIN_INDEX]);

        SCB1_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[SCB1_RX_SCL_MOSI_PIN_INDEX]);

    #if (!SCB1_CY_SCBIP_V1)
        SCB1_SET_INP_DIS(SCB1_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     SCB1_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SCB1_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!SCB1_CY_SCBIP_V1) */
    #endif /* (SCB1_RX_SCL_MOSI_PIN) */

    #if (SCB1_TX_SDA_MISO_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_TX_SDA_MISO_HSIOM_REG,
                                       SCB1_TX_SDA_MISO_HSIOM_MASK,
                                       SCB1_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[SCB1_TX_SDA_MISO_PIN_INDEX]);

        SCB1_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[SCB1_TX_SDA_MISO_PIN_INDEX]);

    #if (!SCB1_CY_SCBIP_V1)
        SCB1_SET_INP_DIS(SCB1_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     SCB1_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & SCB1_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!SCB1_CY_SCBIP_V1) */
    #endif /* (SCB1_RX_SCL_MOSI_PIN) */

    #if (SCB1_SCLK_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_SCLK_HSIOM_REG,
                                       SCB1_SCLK_HSIOM_MASK,
                                       SCB1_SCLK_HSIOM_POS,
                                       hsiomSel[SCB1_SCLK_PIN_INDEX]);

        SCB1_spi_sclk_SetDriveMode((uint8) pinsDm[SCB1_SCLK_PIN_INDEX]);

        SCB1_SET_INP_DIS(SCB1_spi_sclk_INP_DIS,
                                     SCB1_spi_sclk_MASK,
                                     (0u != (pinsInBuf & SCB1_SCLK_PIN_MASK)));
    #endif /* (SCB1_SCLK_PIN) */

    #if (SCB1_SS0_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_SS0_HSIOM_REG,
                                       SCB1_SS0_HSIOM_MASK,
                                       SCB1_SS0_HSIOM_POS,
                                       hsiomSel[SCB1_SS0_PIN_INDEX]);

        SCB1_spi_ss0_SetDriveMode((uint8) pinsDm[SCB1_SS0_PIN_INDEX]);

        SCB1_SET_INP_DIS(SCB1_spi_ss0_INP_DIS,
                                     SCB1_spi_ss0_MASK,
                                     (0u != (pinsInBuf & SCB1_SS0_PIN_MASK)));
    #endif /* (SCB1_SS0_PIN) */

    #if (SCB1_SS1_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_SS1_HSIOM_REG,
                                       SCB1_SS1_HSIOM_MASK,
                                       SCB1_SS1_HSIOM_POS,
                                       hsiomSel[SCB1_SS1_PIN_INDEX]);

        SCB1_spi_ss1_SetDriveMode((uint8) pinsDm[SCB1_SS1_PIN_INDEX]);

        SCB1_SET_INP_DIS(SCB1_spi_ss1_INP_DIS,
                                     SCB1_spi_ss1_MASK,
                                     (0u != (pinsInBuf & SCB1_SS1_PIN_MASK)));
    #endif /* (SCB1_SS1_PIN) */

    #if (SCB1_SS2_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_SS2_HSIOM_REG,
                                       SCB1_SS2_HSIOM_MASK,
                                       SCB1_SS2_HSIOM_POS,
                                       hsiomSel[SCB1_SS2_PIN_INDEX]);

        SCB1_spi_ss2_SetDriveMode((uint8) pinsDm[SCB1_SS2_PIN_INDEX]);

        SCB1_SET_INP_DIS(SCB1_spi_ss2_INP_DIS,
                                     SCB1_spi_ss2_MASK,
                                     (0u != (pinsInBuf & SCB1_SS2_PIN_MASK)));
    #endif /* (SCB1_SS2_PIN) */

    #if (SCB1_SS3_PIN)
        SCB1_SET_HSIOM_SEL(SCB1_SS3_HSIOM_REG,
                                       SCB1_SS3_HSIOM_MASK,
                                       SCB1_SS3_HSIOM_POS,
                                       hsiomSel[SCB1_SS3_PIN_INDEX]);

        SCB1_spi_ss3_SetDriveMode((uint8) pinsDm[SCB1_SS3_PIN_INDEX]);

        SCB1_SET_INP_DIS(SCB1_spi_ss3_INP_DIS,
                                     SCB1_spi_ss3_MASK,
                                     (0u != (pinsInBuf & SCB1_SS3_PIN_MASK)));
    #endif /* (SCB1_SS3_PIN) */
    }

#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (SCB1_CY_SCBIP_V0 || SCB1_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SCB1_I2CSlaveNackGeneration
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
    void SCB1_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (SCB1_CTRL_REG & SCB1_CTRL_EC_AM_MODE)) &&
            (0u == (SCB1_I2C_CTRL_REG & SCB1_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            SCB1_CTRL_REG &= ~SCB1_CTRL_EC_AM_MODE;
            SCB1_CTRL_REG |=  SCB1_CTRL_EC_AM_MODE;
        }

        SCB1_I2C_SLAVE_CMD_REG = SCB1_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (SCB1_CY_SCBIP_V0 || SCB1_CY_SCBIP_V1) */


/* [] END OF FILE */
