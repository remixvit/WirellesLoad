/*******************************************************************************
* File Name: SCB2_BOOT.h
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

#if !defined(CY_SCB_BOOT_SCB2_H)
#define CY_SCB_BOOT_SCB2_H

#include "SCB2_PVT.h"

#if (SCB2_SCB_MODE_I2C_INC)
    #include "SCB2_I2C.h"
#endif /* (SCB2_SCB_MODE_I2C_INC) */

#if (SCB2_SCB_MODE_EZI2C_INC)
    #include "SCB2_EZI2C.h"
#endif /* (SCB2_SCB_MODE_EZI2C_INC) */

#if (SCB2_SCB_MODE_SPI_INC || SCB2_SCB_MODE_UART_INC)
    #include "SCB2_SPI_UART.h"
#endif /* (SCB2_SCB_MODE_SPI_INC || SCB2_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define SCB2_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SCB2) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (SCB2_SCB_MODE_I2C_INC)
    #define SCB2_I2C_BTLDR_COMM_ENABLED     (SCB2_BTLDR_COMM_ENABLED && \
                                                            (SCB2_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SCB2_I2C_SLAVE_CONST))
#else
     #define SCB2_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (SCB2_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (SCB2_SCB_MODE_EZI2C_INC)
    #define SCB2_EZI2C_BTLDR_COMM_ENABLED   (SCB2_BTLDR_COMM_ENABLED && \
                                                         SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define SCB2_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (SCB2_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (SCB2_SCB_MODE_SPI_INC)
    #define SCB2_SPI_BTLDR_COMM_ENABLED     (SCB2_BTLDR_COMM_ENABLED && \
                                                            (SCB2_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SCB2_SPI_SLAVE_CONST))
#else
        #define SCB2_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (SCB2_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (SCB2_SCB_MODE_UART_INC)
       #define SCB2_UART_BTLDR_COMM_ENABLED    (SCB2_BTLDR_COMM_ENABLED && \
                                                            (SCB2_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (SCB2_UART_RX_DIRECTION && \
                                                              SCB2_UART_TX_DIRECTION)))
#else
     #define SCB2_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (SCB2_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define SCB2_BTLDR_COMM_MODE_ENABLED    (SCB2_I2C_BTLDR_COMM_ENABLED   || \
                                                     SCB2_SPI_BTLDR_COMM_ENABLED   || \
                                                     SCB2_EZI2C_BTLDR_COMM_ENABLED || \
                                                     SCB2_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void SCB2_I2CCyBtldrCommStart(void);
    void SCB2_I2CCyBtldrCommStop (void);
    void SCB2_I2CCyBtldrCommReset(void);
    cystatus SCB2_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB2_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (SCB2_SCB_MODE_I2C_CONST_CFG)
        #define SCB2_CyBtldrCommStart   SCB2_I2CCyBtldrCommStart
        #define SCB2_CyBtldrCommStop    SCB2_I2CCyBtldrCommStop
        #define SCB2_CyBtldrCommReset   SCB2_I2CCyBtldrCommReset
        #define SCB2_CyBtldrCommRead    SCB2_I2CCyBtldrCommRead
        #define SCB2_CyBtldrCommWrite   SCB2_I2CCyBtldrCommWrite
    #endif /* (SCB2_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void SCB2_EzI2CCyBtldrCommStart(void);
    void SCB2_EzI2CCyBtldrCommStop (void);
    void SCB2_EzI2CCyBtldrCommReset(void);
    cystatus SCB2_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB2_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (SCB2_SCB_MODE_EZI2C_CONST_CFG)
        #define SCB2_CyBtldrCommStart   SCB2_EzI2CCyBtldrCommStart
        #define SCB2_CyBtldrCommStop    SCB2_EzI2CCyBtldrCommStop
        #define SCB2_CyBtldrCommReset   SCB2_EzI2CCyBtldrCommReset
        #define SCB2_CyBtldrCommRead    SCB2_EzI2CCyBtldrCommRead
        #define SCB2_CyBtldrCommWrite   SCB2_EzI2CCyBtldrCommWrite
    #endif /* (SCB2_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void SCB2_SpiCyBtldrCommStart(void);
    void SCB2_SpiCyBtldrCommStop (void);
    void SCB2_SpiCyBtldrCommReset(void);
    cystatus SCB2_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB2_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (SCB2_SCB_MODE_SPI_CONST_CFG)
        #define SCB2_CyBtldrCommStart   SCB2_SpiCyBtldrCommStart
        #define SCB2_CyBtldrCommStop    SCB2_SpiCyBtldrCommStop
        #define SCB2_CyBtldrCommReset   SCB2_SpiCyBtldrCommReset
        #define SCB2_CyBtldrCommRead    SCB2_SpiCyBtldrCommRead
        #define SCB2_CyBtldrCommWrite   SCB2_SpiCyBtldrCommWrite
    #endif /* (SCB2_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void SCB2_UartCyBtldrCommStart(void);
    void SCB2_UartCyBtldrCommStop (void);
    void SCB2_UartCyBtldrCommReset(void);
    cystatus SCB2_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SCB2_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (SCB2_SCB_MODE_UART_CONST_CFG)
        #define SCB2_CyBtldrCommStart   SCB2_UartCyBtldrCommStart
        #define SCB2_CyBtldrCommStop    SCB2_UartCyBtldrCommStop
        #define SCB2_CyBtldrCommReset   SCB2_UartCyBtldrCommReset
        #define SCB2_CyBtldrCommRead    SCB2_UartCyBtldrCommRead
        #define SCB2_CyBtldrCommWrite   SCB2_UartCyBtldrCommWrite
    #endif /* (SCB2_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_BTLDR_COMM_ENABLED)
    #if (SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void SCB2_CyBtldrCommStart(void);
        void SCB2_CyBtldrCommStop (void);
        void SCB2_CyBtldrCommReset(void);
        cystatus SCB2_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus SCB2_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SCB2)
        #define CyBtldrCommStart    SCB2_CyBtldrCommStart
        #define CyBtldrCommStop     SCB2_CyBtldrCommStop
        #define CyBtldrCommReset    SCB2_CyBtldrCommReset
        #define CyBtldrCommWrite    SCB2_CyBtldrCommWrite
        #define CyBtldrCommRead     SCB2_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SCB2) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SCB2_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define SCB2_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define SCB2_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define SCB2_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define SCB2_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef SCB2_SPI_BYTE_TO_BYTE
    #define SCB2_SPI_BYTE_TO_BYTE   (22u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef SCB2_UART_BYTE_TO_BYTE
    #define SCB2_UART_BYTE_TO_BYTE  (2500u)
#endif /* SCB2_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_SCB2_H) */


/* [] END OF FILE */
