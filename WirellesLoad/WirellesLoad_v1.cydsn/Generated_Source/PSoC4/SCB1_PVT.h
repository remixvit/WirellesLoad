/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_SCB1_H)
#define CY_SCB_PVT_SCB1_H

#include "SCB1.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define SCB1_SetI2CExtClkInterruptMode(interruptMask) SCB1_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define SCB1_ClearI2CExtClkInterruptSource(interruptMask) SCB1_CLEAR_INTR_I2C_EC(interruptMask)
#define SCB1_GetI2CExtClkInterruptSource()                (SCB1_INTR_I2C_EC_REG)
#define SCB1_GetI2CExtClkInterruptMode()                  (SCB1_INTR_I2C_EC_MASK_REG)
#define SCB1_GetI2CExtClkInterruptSourceMasked()          (SCB1_INTR_I2C_EC_MASKED_REG)

#if (!SCB1_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define SCB1_SetSpiExtClkInterruptMode(interruptMask) \
                                                                SCB1_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define SCB1_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                SCB1_CLEAR_INTR_SPI_EC(interruptMask)
    #define SCB1_GetExtSpiClkInterruptSource()                 (SCB1_INTR_SPI_EC_REG)
    #define SCB1_GetExtSpiClkInterruptMode()                   (SCB1_INTR_SPI_EC_MASK_REG)
    #define SCB1_GetExtSpiClkInterruptSourceMasked()           (SCB1_INTR_SPI_EC_MASKED_REG)
#endif /* (!SCB1_CY_SCBIP_V1) */

#if(SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void SCB1_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (SCB1_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SCB1_CUSTOM_INTR_HANDLER)
    extern cyisraddress SCB1_customIntrHandler;
#endif /* !defined (CY_REMOVE_SCB1_CUSTOM_INTR_HANDLER) */
#endif /* (SCB1_SCB_IRQ_INTERNAL) */

extern SCB1_BACKUP_STRUCT SCB1_backup;

#if(SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 SCB1_scbMode;
    extern uint8 SCB1_scbEnableWake;
    extern uint8 SCB1_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 SCB1_mode;
    extern uint8 SCB1_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * SCB1_rxBuffer;
    extern uint8   SCB1_rxDataBits;
    extern uint32  SCB1_rxBufferSize;

    extern volatile uint8 * SCB1_txBuffer;
    extern uint8   SCB1_txDataBits;
    extern uint32  SCB1_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 SCB1_numberOfAddr;
    extern uint8 SCB1_subAddrSize;
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define SCB1_SCB_MODE_I2C_RUNTM_CFG     (SCB1_SCB_MODE_I2C      == SCB1_scbMode)
    #define SCB1_SCB_MODE_SPI_RUNTM_CFG     (SCB1_SCB_MODE_SPI      == SCB1_scbMode)
    #define SCB1_SCB_MODE_UART_RUNTM_CFG    (SCB1_SCB_MODE_UART     == SCB1_scbMode)
    #define SCB1_SCB_MODE_EZI2C_RUNTM_CFG   (SCB1_SCB_MODE_EZI2C    == SCB1_scbMode)
    #define SCB1_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (SCB1_SCB_MODE_UNCONFIG == SCB1_scbMode)

    /* Defines wakeup enable */
    #define SCB1_SCB_WAKE_ENABLE_CHECK       (0u != SCB1_scbEnableWake)
#endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!SCB1_CY_SCBIP_V1)
    #define SCB1_SCB_PINS_NUMBER    (7u)
#else
    #define SCB1_SCB_PINS_NUMBER    (2u)
#endif /* (!SCB1_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_SCB1_H) */


/* [] END OF FILE */
