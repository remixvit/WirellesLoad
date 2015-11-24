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

#if !defined(CY_SCB_PVT_SCB2_H)
#define CY_SCB_PVT_SCB2_H

#include "SCB2.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define SCB2_SetI2CExtClkInterruptMode(interruptMask) SCB2_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define SCB2_ClearI2CExtClkInterruptSource(interruptMask) SCB2_CLEAR_INTR_I2C_EC(interruptMask)
#define SCB2_GetI2CExtClkInterruptSource()                (SCB2_INTR_I2C_EC_REG)
#define SCB2_GetI2CExtClkInterruptMode()                  (SCB2_INTR_I2C_EC_MASK_REG)
#define SCB2_GetI2CExtClkInterruptSourceMasked()          (SCB2_INTR_I2C_EC_MASKED_REG)

#if (!SCB2_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define SCB2_SetSpiExtClkInterruptMode(interruptMask) \
                                                                SCB2_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define SCB2_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                SCB2_CLEAR_INTR_SPI_EC(interruptMask)
    #define SCB2_GetExtSpiClkInterruptSource()                 (SCB2_INTR_SPI_EC_REG)
    #define SCB2_GetExtSpiClkInterruptMode()                   (SCB2_INTR_SPI_EC_MASK_REG)
    #define SCB2_GetExtSpiClkInterruptSourceMasked()           (SCB2_INTR_SPI_EC_MASKED_REG)
#endif /* (!SCB2_CY_SCBIP_V1) */

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void SCB2_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (SCB2_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SCB2_CUSTOM_INTR_HANDLER)
    extern cyisraddress SCB2_customIntrHandler;
#endif /* !defined (CY_REMOVE_SCB2_CUSTOM_INTR_HANDLER) */
#endif /* (SCB2_SCB_IRQ_INTERNAL) */

extern SCB2_BACKUP_STRUCT SCB2_backup;

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 SCB2_scbMode;
    extern uint8 SCB2_scbEnableWake;
    extern uint8 SCB2_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 SCB2_mode;
    extern uint8 SCB2_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * SCB2_rxBuffer;
    extern uint8   SCB2_rxDataBits;
    extern uint32  SCB2_rxBufferSize;

    extern volatile uint8 * SCB2_txBuffer;
    extern uint8   SCB2_txDataBits;
    extern uint32  SCB2_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 SCB2_numberOfAddr;
    extern uint8 SCB2_subAddrSize;
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define SCB2_SCB_MODE_I2C_RUNTM_CFG     (SCB2_SCB_MODE_I2C      == SCB2_scbMode)
    #define SCB2_SCB_MODE_SPI_RUNTM_CFG     (SCB2_SCB_MODE_SPI      == SCB2_scbMode)
    #define SCB2_SCB_MODE_UART_RUNTM_CFG    (SCB2_SCB_MODE_UART     == SCB2_scbMode)
    #define SCB2_SCB_MODE_EZI2C_RUNTM_CFG   (SCB2_SCB_MODE_EZI2C    == SCB2_scbMode)
    #define SCB2_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (SCB2_SCB_MODE_UNCONFIG == SCB2_scbMode)

    /* Defines wakeup enable */
    #define SCB2_SCB_WAKE_ENABLE_CHECK       (0u != SCB2_scbEnableWake)
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!SCB2_CY_SCBIP_V1)
    #define SCB2_SCB_PINS_NUMBER    (7u)
#else
    #define SCB2_SCB_PINS_NUMBER    (2u)
#endif /* (!SCB2_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_SCB2_H) */


/* [] END OF FILE */
