/*******************************************************************************
* File Name: SCB1_BOOT.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_SCB1_H)
#define CY_SCB_BOOT_SCB1_H

#include "SCB1_PVT.h"

#if (SCB1_SCB_MODE_I2C_INC)
    #include "SCB1_I2C.h"
#endif /* (SCB1_SCB_MODE_I2C_INC) */

#if (SCB1_SCB_MODE_EZI2C_INC)
    #include "SCB1_EZI2C.h"
#endif /* (SCB1_SCB_MODE_EZI2C_INC) */

#if (SCB1_SCB_MODE_SPI_INC || SCB1_SCB_MODE_UART_INC)
    #include "SCB1_SPI_UART.h"
#endif /* (SCB1_SCB_MODE_SPI_INC || SCB1_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define SCB1_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SCB1) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (SCB1_SCB_MODE_I2C_INC)
    #define SCB1_I2C_BTLDR_COMM_ENABLED     (SCB1_BTLDR_COMM_ENABLED && \
                                                            (SCB1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SCB1_I2C_SLAVE_CONST))
#else
     #define SCB1_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (SCB1_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (SCB1_SCB_MODE_EZI2C_INC)
    #define SCB1_EZI2C_BTLDR_COMM_ENABLED   (SCB1_BTLDR_COMM_ENABLED && \
                                                         SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define SCB1_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (SCB1_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (SCB1_SCB_MODE_SPI_INC)
    #define SCB1_SPI_BTLDR_COMM_ENABLED     (SCB1_BTLDR_COMM_ENABLED && \
                                                            (SCB1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SCB1_SPI_SLAVE_CONST))
#else
        #define SCB1_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (SCB1_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (SCB1_SCB_MODE_UART_INC)
       #define SCB1_UART_BTLDR_COMM_ENABLED    (SCB1_BTLDR_COMM_ENABLED && \
                                                            (SCB1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (SCB1_UART_RX_DIRECTION && \
                                                              SCB1_UART_TX_DIRECTION)))
#else
     #define SCB1_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (SCB1_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define SCB1_BTLDR_COMM_MODE_ENABLED    (SCB1_I2C_BTLDR_COMM_ENABLED   || \
                                                     SCB1_SPI_BTLDR_COMM_ENABLED   || \
                                                     SCB1_EZI2C_BTLDR_COMM_ENABLED || \
                                                     SCB1_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void SCB1_I2CCyBtldrCommStart(void);
    void SCB1_I2CCyBtldrCommStop (void);
    void SCB1_I2CCyBtldrCommReset(void);
    cystatus SCB1_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB1_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (SCB1_SCB_MODE_I2C_CONST_CFG)
        #define SCB1_CyBtldrCommStart   SCB1_I2CCyBtldrCommStart
        #define SCB1_CyBtldrCommStop    SCB1_I2CCyBtldrCommStop
        #define SCB1_CyBtldrCommReset   SCB1_I2CCyBtldrCommReset
        #define SCB1_CyBtldrCommRead    SCB1_I2CCyBtldrCommRead
        #define SCB1_CyBtldrCommWrite   SCB1_I2CCyBtldrCommWrite
    #endif /* (SCB1_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void SCB1_EzI2CCyBtldrCommStart(void);
    void SCB1_EzI2CCyBtldrCommStop (void);
    void SCB1_EzI2CCyBtldrCommReset(void);
    cystatus SCB1_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB1_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (SCB1_SCB_MODE_EZI2C_CONST_CFG)
        #define SCB1_CyBtldrCommStart   SCB1_EzI2CCyBtldrCommStart
        #define SCB1_CyBtldrCommStop    SCB1_EzI2CCyBtldrCommStop
        #define SCB1_CyBtldrCommReset   SCB1_EzI2CCyBtldrCommReset
        #define SCB1_CyBtldrCommRead    SCB1_EzI2CCyBtldrCommRead
        #define SCB1_CyBtldrCommWrite   SCB1_EzI2CCyBtldrCommWrite
    #endif /* (SCB1_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void SCB1_SpiCyBtldrCommStart(void);
    void SCB1_SpiCyBtldrCommStop (void);
    void SCB1_SpiCyBtldrCommReset(void);
    cystatus SCB1_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB1_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (SCB1_SCB_MODE_SPI_CONST_CFG)
        #define SCB1_CyBtldrCommStart   SCB1_SpiCyBtldrCommStart
        #define SCB1_CyBtldrCommStop    SCB1_SpiCyBtldrCommStop
        #define SCB1_CyBtldrCommReset   SCB1_SpiCyBtldrCommReset
        #define SCB1_CyBtldrCommRead    SCB1_SpiCyBtldrCommRead
        #define SCB1_CyBtldrCommWrite   SCB1_SpiCyBtldrCommWrite
    #endif /* (SCB1_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void SCB1_UartCyBtldrCommStart(void);
    void SCB1_UartCyBtldrCommStop (void);
    void SCB1_UartCyBtldrCommReset(void);
    cystatus SCB1_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB1_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (SCB1_SCB_MODE_UART_CONST_CFG)
        #define SCB1_CyBtldrCommStart   SCB1_UartCyBtldrCommStart
        #define SCB1_CyBtldrCommStop    SCB1_UartCyBtldrCommStop
        #define SCB1_CyBtldrCommReset   SCB1_UartCyBtldrCommReset
        #define SCB1_CyBtldrCommRead    SCB1_UartCyBtldrCommRead
        #define SCB1_CyBtldrCommWrite   SCB1_UartCyBtldrCommWrite
    #endif /* (SCB1_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_BTLDR_COMM_ENABLED)
    #if (SCB1_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void SCB1_CyBtldrCommStart(void);
        void SCB1_CyBtldrCommStop (void);
        void SCB1_CyBtldrCommReset(void);
        cystatus SCB1_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus SCB1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (SCB1_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SCB1)
        #define CyBtldrCommStart    SCB1_CyBtldrCommStart
        #define CyBtldrCommStop     SCB1_CyBtldrCommStop
        #define CyBtldrCommReset    SCB1_CyBtldrCommReset
        #define CyBtldrCommWrite    SCB1_CyBtldrCommWrite
        #define CyBtldrCommRead     SCB1_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SCB1) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB1_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define SCB1_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define SCB1_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define SCB1_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define SCB1_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef SCB1_SPI_BYTE_TO_BYTE
    #define SCB1_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef SCB1_UART_BYTE_TO_BYTE
    #define SCB1_UART_BYTE_TO_BYTE  (2500u)
#endif /* SCB1_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_SCB1_H) */


/* [] END OF FILE */
