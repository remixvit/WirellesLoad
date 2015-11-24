/*******************************************************************************
* File Name: SCB2_SPI_UART_PVT.h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_SCB2_H)
#define CY_SCB_SPI_UART_PVT_SCB2_H

#include "SCB2_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (SCB2_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SCB2_rxBufferHead;
    extern volatile uint32  SCB2_rxBufferTail;
    extern volatile uint8   SCB2_rxBufferOverflow;
#endif /* (SCB2_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SCB2_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SCB2_txBufferHead;
    extern volatile uint32  SCB2_txBufferTail;
#endif /* (SCB2_INTERNAL_TX_SW_BUFFER_CONST) */

#if (SCB2_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SCB2_rxBufferInternal[SCB2_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SCB2_INTERNAL_RX_SW_BUFFER) */

#if (SCB2_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SCB2_txBufferInternal[SCB2_TX_BUFFER_SIZE];
#endif /* (SCB2_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void SCB2_SpiPostEnable(void);
void SCB2_SpiStop(void);

#if (SCB2_SCB_MODE_SPI_CONST_CFG)
    void SCB2_SpiInit(void);
#endif /* (SCB2_SCB_MODE_SPI_CONST_CFG) */

#if (SCB2_SPI_WAKE_ENABLE_CONST)
    void SCB2_SpiSaveConfig(void);
    void SCB2_SpiRestoreConfig(void);
#endif /* (SCB2_SPI_WAKE_ENABLE_CONST) */

void SCB2_UartPostEnable(void);
void SCB2_UartStop(void);

#if (SCB2_SCB_MODE_UART_CONST_CFG)
    void SCB2_UartInit(void);
#endif /* (SCB2_SCB_MODE_UART_CONST_CFG) */

#if (SCB2_UART_WAKE_ENABLE_CONST)
    void SCB2_UartSaveConfig(void);
    void SCB2_UartRestoreConfig(void);
#endif /* (SCB2_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in SCB2_SetPins() */
#define SCB2_UART_RX_PIN_ENABLE    (SCB2_UART_RX)
#define SCB2_UART_TX_PIN_ENABLE    (SCB2_UART_TX)

/* UART RTS and CTS position to be used in  SCB2_SetPins() */
#define SCB2_UART_RTS_PIN_ENABLE    (0x10u)
#define SCB2_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define SCB2_SpiUartEnableIntRx(intSourceMask)  SCB2_SetRxInterruptMode(intSourceMask)
#define SCB2_SpiUartEnableIntTx(intSourceMask)  SCB2_SetTxInterruptMode(intSourceMask)
uint32  SCB2_SpiUartDisableIntRx(void);
uint32  SCB2_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_SCB2_H) */


/* [] END OF FILE */
