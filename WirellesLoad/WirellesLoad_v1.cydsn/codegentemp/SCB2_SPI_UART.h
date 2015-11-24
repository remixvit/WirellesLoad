/*******************************************************************************
* File Name: SCB2_SPI_UART.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_SCB2_H)
#define CY_SCB_SPI_UART_SCB2_H

#include "SCB2.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define SCB2_SPI_MODE                   (1u)
#define SCB2_SPI_SUB_MODE               (0u)
#define SCB2_SPI_CLOCK_MODE             (0u)
#define SCB2_SPI_OVS_FACTOR             (16u)
#define SCB2_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define SCB2_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define SCB2_SPI_RX_DATA_BITS_NUM       (8u)
#define SCB2_SPI_TX_DATA_BITS_NUM       (8u)
#define SCB2_SPI_WAKE_ENABLE            (0u)
#define SCB2_SPI_BITS_ORDER             (1u)
#define SCB2_SPI_TRANSFER_SEPARATION    (1u)
#define SCB2_SPI_NUMBER_OF_SS_LINES     (1u)
#define SCB2_SPI_RX_BUFFER_SIZE         (8u)
#define SCB2_SPI_TX_BUFFER_SIZE         (8u)

#define SCB2_SPI_INTERRUPT_MODE         (0u)

#define SCB2_SPI_INTR_RX_MASK           (0u)
#define SCB2_SPI_INTR_TX_MASK           (0u)

#define SCB2_SPI_RX_TRIGGER_LEVEL       (7u)
#define SCB2_SPI_TX_TRIGGER_LEVEL       (0u)

#define SCB2_SPI_BYTE_MODE_ENABLE       (0u)
#define SCB2_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define SCB2_SPI_SS0_POLARITY           (0u)
#define SCB2_SPI_SS1_POLARITY           (0u)
#define SCB2_SPI_SS2_POLARITY           (0u)
#define SCB2_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define SCB2_UART_SUB_MODE              (0u)
#define SCB2_UART_DIRECTION             (3u)
#define SCB2_UART_DATA_BITS_NUM         (8u)
#define SCB2_UART_PARITY_TYPE           (2u)
#define SCB2_UART_STOP_BITS_NUM         (2u)
#define SCB2_UART_OVS_FACTOR            (12u)
#define SCB2_UART_IRDA_LOW_POWER        (0u)
#define SCB2_UART_MEDIAN_FILTER_ENABLE  (0u)
#define SCB2_UART_RETRY_ON_NACK         (0u)
#define SCB2_UART_IRDA_POLARITY         (0u)
#define SCB2_UART_DROP_ON_FRAME_ERR     (0u)
#define SCB2_UART_DROP_ON_PARITY_ERR    (0u)
#define SCB2_UART_WAKE_ENABLE           (0u)
#define SCB2_UART_RX_BUFFER_SIZE        (8u)
#define SCB2_UART_TX_BUFFER_SIZE        (8u)
#define SCB2_UART_MP_MODE_ENABLE        (0u)
#define SCB2_UART_MP_ACCEPT_ADDRESS     (0u)
#define SCB2_UART_MP_RX_ADDRESS         (2u)
#define SCB2_UART_MP_RX_ADDRESS_MASK    (255u)

#define SCB2_UART_INTERRUPT_MODE        (0u)

#define SCB2_UART_INTR_RX_MASK          (0u)
#define SCB2_UART_INTR_TX_MASK          (0u)

#define SCB2_UART_RX_TRIGGER_LEVEL      (7u)
#define SCB2_UART_TX_TRIGGER_LEVEL      (0u)

#define SCB2_UART_BYTE_MODE_ENABLE      (0u)
#define SCB2_UART_CTS_ENABLE            (0u)
#define SCB2_UART_CTS_POLARITY          (0u)
#define SCB2_UART_RTS_ENABLE            (0u)
#define SCB2_UART_RTS_POLARITY          (0u)
#define SCB2_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define SCB2_SPI_SLAVE  (0u)
#define SCB2_SPI_MASTER (1u)

/* UART direction enum */
#define SCB2_UART_RX    (1u)
#define SCB2_UART_TX    (2u)
#define SCB2_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define SCB2_SPI_SLAVE_CONST        (1u)
    #define SCB2_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define SCB2_RX_DIRECTION           (1u)
    #define SCB2_TX_DIRECTION           (1u)
    #define SCB2_UART_RX_DIRECTION      (1u)
    #define SCB2_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define SCB2_INTERNAL_RX_SW_BUFFER   (0u)
    #define SCB2_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define SCB2_INTERNAL_RX_BUFFER_SIZE    (SCB2_rxBufferSize + 1u)
    #define SCB2_RX_BUFFER_SIZE             (SCB2_rxBufferSize)
    #define SCB2_TX_BUFFER_SIZE             (SCB2_txBufferSize)

    /* Return true if buffer is provided */
    #define SCB2_CHECK_RX_SW_BUFFER (NULL != SCB2_rxBuffer)
    #define SCB2_CHECK_TX_SW_BUFFER (NULL != SCB2_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define SCB2_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define SCB2_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define SCB2_SPI_WAKE_ENABLE_CONST  (1u)
    #define SCB2_CHECK_SPI_WAKE_ENABLE  (0u != SCB2_scbEnableWake)
    #define SCB2_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
        #define SCB2_SPI_UART_FIFO_SIZE             (SCB2_FIFO_SIZE)
        #define SCB2_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define SCB2_SPI_UART_FIFO_SIZE (SCB2_GET_FIFO_SIZE(SCB2_CTRL_REG & \
                                                                                    SCB2_CTRL_BYTE_MODE))

        #define SCB2_CHECK_UART_RTS_CONTROL_FLOW \
                    ((SCB2_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != SCB2_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SCB2_UART_FLOW_CTRL_REG)))
    #endif /* (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (SCB2_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define SCB2_SPI_RX_DIRECTION (1u)
        #define SCB2_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
            #define SCB2_SPI_UART_FIFO_SIZE    (SCB2_FIFO_SIZE)
        #else
            #define SCB2_SPI_UART_FIFO_SIZE \
                                           SCB2_GET_FIFO_SIZE(SCB2_SPI_BYTE_MODE_ENABLE)

        #endif /* (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define SCB2_INTERNAL_SPI_RX_SW_BUFFER  (SCB2_SPI_RX_BUFFER_SIZE > \
                                                                SCB2_SPI_UART_FIFO_SIZE)
        #define SCB2_INTERNAL_SPI_TX_SW_BUFFER  (SCB2_SPI_TX_BUFFER_SIZE > \
                                                                SCB2_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define SCB2_INTERNAL_RX_SW_BUFFER  (SCB2_INTERNAL_SPI_RX_SW_BUFFER)
        #define SCB2_INTERNAL_TX_SW_BUFFER  (SCB2_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define SCB2_INTERNAL_RX_BUFFER_SIZE    (SCB2_SPI_RX_BUFFER_SIZE + 1u)
        #define SCB2_RX_BUFFER_SIZE             (SCB2_SPI_RX_BUFFER_SIZE)
        #define SCB2_TX_BUFFER_SIZE             (SCB2_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SCB2_SPI_WAKE_ENABLE_CONST  (0u != SCB2_SPI_WAKE_ENABLE)
        #define SCB2_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define SCB2_UART_RX_DIRECTION (0u != (SCB2_UART_DIRECTION & SCB2_UART_RX))
        #define SCB2_UART_TX_DIRECTION (0u != (SCB2_UART_DIRECTION & SCB2_UART_TX))

        /* Get FIFO size */
        #if (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
            #define SCB2_SPI_UART_FIFO_SIZE    (SCB2_FIFO_SIZE)
        #else
            #define SCB2_SPI_UART_FIFO_SIZE \
                                           SCB2_GET_FIFO_SIZE(SCB2_UART_BYTE_MODE_ENABLE)
        #endif /* (SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define SCB2_INTERNAL_UART_RX_SW_BUFFER  (SCB2_UART_RX_BUFFER_SIZE > \
                                                                SCB2_SPI_UART_FIFO_SIZE)
        #define SCB2_INTERNAL_UART_TX_SW_BUFFER  (SCB2_UART_TX_BUFFER_SIZE > \
                                                                    SCB2_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define SCB2_INTERNAL_RX_SW_BUFFER  (SCB2_INTERNAL_UART_RX_SW_BUFFER)
        #define SCB2_INTERNAL_TX_SW_BUFFER  (SCB2_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define SCB2_INTERNAL_RX_BUFFER_SIZE    (SCB2_UART_RX_BUFFER_SIZE + 1u)
        #define SCB2_RX_BUFFER_SIZE             (SCB2_UART_RX_BUFFER_SIZE)
        #define SCB2_TX_BUFFER_SIZE             (SCB2_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SCB2_SPI_WAKE_ENABLE_CONST  (0u)
        #define SCB2_UART_WAKE_ENABLE_CONST (0u != SCB2_UART_WAKE_ENABLE)

    #endif /* (SCB2_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define SCB2_SPI_SLAVE_CONST    (SCB2_SPI_MODE == SCB2_SPI_SLAVE)
    #define SCB2_SPI_MASTER_CONST   (SCB2_SPI_MODE == SCB2_SPI_MASTER)

    /* Direction */
    #define SCB2_RX_DIRECTION ((SCB2_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SCB2_SPI_RX_DIRECTION) : (SCB2_UART_RX_DIRECTION))

    #define SCB2_TX_DIRECTION ((SCB2_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SCB2_SPI_TX_DIRECTION) : (SCB2_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define SCB2_CHECK_RX_SW_BUFFER (SCB2_INTERNAL_RX_SW_BUFFER)
    #define SCB2_CHECK_TX_SW_BUFFER (SCB2_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define SCB2_INTERNAL_RX_SW_BUFFER_CONST    (SCB2_INTERNAL_RX_SW_BUFFER)
    #define SCB2_INTERNAL_TX_SW_BUFFER_CONST    (SCB2_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define SCB2_CHECK_SPI_WAKE_ENABLE  (SCB2_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define SCB2_CHECK_UART_RTS_CONTROL_FLOW    (SCB2_SCB_MODE_UART_CONST_CFG && \
                                                             SCB2_UART_RTS_ENABLE)

#endif /* End (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* SCB2_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} SCB2_SPI_INIT_STRUCT;

/* SCB2_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} SCB2_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    void SCB2_SpiInit(const SCB2_SPI_INIT_STRUCT *config);
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SCB2_SCB_MODE_SPI_INC)
    #define SCB2_SpiIsBusBusy() ((uint32) (0u != (SCB2_SPI_STATUS_REG & \
                                                              SCB2_SPI_STATUS_BUS_BUSY)))

    #if (SCB2_SPI_MASTER_CONST)
        void SCB2_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(SCB2_SPI_MASTER_CONST) */

    #if !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
        void SCB2_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */
#endif /* (SCB2_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    void SCB2_UartInit(const SCB2_UART_INIT_STRUCT *config);
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SCB2_SCB_MODE_UART_INC)
    void SCB2_UartSetRxAddress(uint32 address);
    void SCB2_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(SCB2_UART_RX_DIRECTION)
        uint32 SCB2_UartGetChar(void);
        uint32 SCB2_UartGetByte(void);

        #if !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SCB2_UartSetRtsPolarity(uint32 polarity);
            void SCB2_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */
    #endif /* (SCB2_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(SCB2_UART_TX_DIRECTION)
        #define SCB2_UartPutChar(ch)    SCB2_SpiUartWriteTxData((uint32)(ch))
        void SCB2_UartPutString(const char8 string[]);
        void SCB2_UartPutCRLF(uint32 txDataByte);

        #if !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SCB2_UartEnableCts(void);
            void SCB2_UartDisableCts(void);
            void SCB2_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(SCB2_CY_SCBIP_V0 || SCB2_CY_SCBIP_V1) */
    #endif /* (SCB2_UART_TX_DIRECTION) */
#endif /* (SCB2_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(SCB2_RX_DIRECTION)
    uint32 SCB2_SpiUartReadRxData(void);
    uint32 SCB2_SpiUartGetRxBufferSize(void);
    void   SCB2_SpiUartClearRxBuffer(void);
#endif /* (SCB2_RX_DIRECTION) */

/* Common APIs TX direction */
#if(SCB2_TX_DIRECTION)
    void   SCB2_SpiUartWriteTxData(uint32 txData);
    void   SCB2_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 SCB2_SpiUartGetTxBufferSize(void);
    void   SCB2_SpiUartClearTxBuffer(void);
#endif /* (SCB2_TX_DIRECTION) */

CY_ISR_PROTO(SCB2_SPI_UART_ISR);

#if(SCB2_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(SCB2_UART_WAKEUP_ISR);
#endif /* (SCB2_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   SCB2_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 SCB2_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   SCB2_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 SCB2_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(SCB2_INTERNAL_RX_SW_BUFFER_CONST)
        #define SCB2_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    SCB2_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define SCB2_GetWordFromRxBuffer(idx) SCB2_rxBufferInternal[(idx)]

    #endif /* (SCB2_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(SCB2_INTERNAL_TX_SW_BUFFER_CONST)
        #define SCB2_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        SCB2_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define SCB2_GetWordFromTxBuffer(idx) SCB2_txBufferInternal[(idx)]

    #endif /* (SCB2_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (SCB2_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define SCB2_SPI_MODE_MOTOROLA      (0x00u)
#define SCB2_SPI_MODE_TI_COINCIDES  (0x01u)
#define SCB2_SPI_MODE_TI_PRECEDES   (0x11u)
#define SCB2_SPI_MODE_NATIONAL      (0x02u)
#define SCB2_SPI_MODE_MASK          (0x03u)
#define SCB2_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define SCB2_SPI_MODE_NS_MICROWIRE  (SCB2_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define SCB2_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define SCB2_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define SCB2_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define SCB2_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define SCB2_BITS_ORDER_LSB_FIRST   (0u)
#define SCB2_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define SCB2_SPI_TRANSFER_SEPARATED     (0u)
#define SCB2_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define SCB2_SPI_SLAVE_SELECT0    (SCB2_SCB__SS0_POSISTION)
#define SCB2_SPI_SLAVE_SELECT1    (SCB2_SCB__SS1_POSISTION)
#define SCB2_SPI_SLAVE_SELECT2    (SCB2_SCB__SS2_POSISTION)
#define SCB2_SPI_SLAVE_SELECT3    (SCB2_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define SCB2_SPI_SS_ACTIVE_LOW  (0u)
#define SCB2_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define SCB2_UART_MODE_STD          (0u)
#define SCB2_UART_MODE_SMARTCARD    (1u)
#define SCB2_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define SCB2_UART_RX    (1u)
#define SCB2_UART_TX    (2u)
#define SCB2_UART_TX_RX (3u)

/* UART parity enum */
#define SCB2_UART_PARITY_EVEN   (0u)
#define SCB2_UART_PARITY_ODD    (1u)
#define SCB2_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define SCB2_UART_STOP_BITS_1   (2u)
#define SCB2_UART_STOP_BITS_1_5 (3u)
#define SCB2_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define SCB2_UART_IRDA_LP_OVS16     (16u)
#define SCB2_UART_IRDA_LP_OVS32     (32u)
#define SCB2_UART_IRDA_LP_OVS48     (48u)
#define SCB2_UART_IRDA_LP_OVS96     (96u)
#define SCB2_UART_IRDA_LP_OVS192    (192u)
#define SCB2_UART_IRDA_LP_OVS768    (768u)
#define SCB2_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define SCB2_UART_MP_MARK       (0x100u)
#define SCB2_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define SCB2_UART_CTS_ACTIVE_LOW    (0u)
#define SCB2_UART_CTS_ACTIVE_HIGH   (1u)
#define SCB2_UART_RTS_ACTIVE_LOW    (0u)
#define SCB2_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define SCB2_INTR_RX_ERR        (SCB2_INTR_RX_OVERFLOW    | \
                                             SCB2_INTR_RX_UNDERFLOW   | \
                                             SCB2_INTR_RX_FRAME_ERROR | \
                                             SCB2_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for SCB2_UartGetByte() */
#define SCB2_UART_RX_OVERFLOW       (SCB2_INTR_RX_OVERFLOW << 8u)
#define SCB2_UART_RX_UNDERFLOW      (SCB2_INTR_RX_UNDERFLOW << 8u)
#define SCB2_UART_RX_FRAME_ERROR    (SCB2_INTR_RX_FRAME_ERROR << 8u)
#define SCB2_UART_RX_PARITY_ERROR   (SCB2_INTR_RX_PARITY_ERROR << 8u)
#define SCB2_UART_RX_ERROR_MASK     (SCB2_UART_RX_OVERFLOW    | \
                                                 SCB2_UART_RX_UNDERFLOW   | \
                                                 SCB2_UART_RX_FRAME_ERROR | \
                                                 SCB2_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const SCB2_SPI_INIT_STRUCT  SCB2_configSpi;
    extern const SCB2_UART_INIT_STRUCT SCB2_configUart;
#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define SCB2_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & SCB2_INTR_SLAVE_SPI_BUS_ERROR)
#define SCB2_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & SCB2_INTR_MASTER_SPI_DONE)
#define SCB2_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SCB2_INTR_SLAVE_SPI_BUS_ERROR)

#define SCB2_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SCB2_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define SCB2_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((SCB2_UART_IRDA_LP_OVS16   == (oversample)) ? SCB2_CTRL_OVS_IRDA_LP_OVS16 : \
         ((SCB2_UART_IRDA_LP_OVS32   == (oversample)) ? SCB2_CTRL_OVS_IRDA_LP_OVS32 : \
          ((SCB2_UART_IRDA_LP_OVS48   == (oversample)) ? SCB2_CTRL_OVS_IRDA_LP_OVS48 : \
           ((SCB2_UART_IRDA_LP_OVS96   == (oversample)) ? SCB2_CTRL_OVS_IRDA_LP_OVS96 : \
            ((SCB2_UART_IRDA_LP_OVS192  == (oversample)) ? SCB2_CTRL_OVS_IRDA_LP_OVS192 : \
             ((SCB2_UART_IRDA_LP_OVS768  == (oversample)) ? SCB2_CTRL_OVS_IRDA_LP_OVS768 : \
              ((SCB2_UART_IRDA_LP_OVS1536 == (oversample)) ? SCB2_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          SCB2_CTRL_OVS_IRDA_LP_OVS16)))))))

#define SCB2_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (SCB2_UART_RX & (direction))) ? \
                                                                     (SCB2_RX_CTRL_ENABLED) : (0u))

#define SCB2_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (SCB2_UART_TX & (direction))) ? \
                                                                     (SCB2_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define SCB2_CTRL_SPI      (SCB2_CTRL_MODE_SPI)
#define SCB2_SPI_RX_CTRL   (SCB2_RX_CTRL_ENABLED)
#define SCB2_SPI_TX_CTRL   (SCB2_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define SCB2_SPI_SS_POLARITY \
             (((uint32) SCB2_SPI_SS0_POLARITY << SCB2_SPI_SLAVE_SELECT0) | \
              ((uint32) SCB2_SPI_SS1_POLARITY << SCB2_SPI_SLAVE_SELECT1) | \
              ((uint32) SCB2_SPI_SS2_POLARITY << SCB2_SPI_SLAVE_SELECT2) | \
              ((uint32) SCB2_SPI_SS3_POLARITY << SCB2_SPI_SLAVE_SELECT3))

#if(SCB2_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define SCB2_SPI_DEFAULT_CTRL \
                    (SCB2_GET_CTRL_OVS(SCB2_SPI_OVS_FACTOR) | \
                     SCB2_GET_CTRL_BYTE_MODE (SCB2_SPI_BYTE_MODE_ENABLE) | \
                     SCB2_GET_CTRL_EC_AM_MODE(SCB2_SPI_WAKE_ENABLE)      | \
                     SCB2_CTRL_SPI)

    #define SCB2_SPI_DEFAULT_SPI_CTRL \
                    (SCB2_GET_SPI_CTRL_CONTINUOUS    (SCB2_SPI_TRANSFER_SEPARATION)       | \
                     SCB2_GET_SPI_CTRL_SELECT_PRECEDE(SCB2_SPI_SUB_MODE &                   \
                                                                  SCB2_SPI_MODE_TI_PRECEDES_MASK)     | \
                     SCB2_GET_SPI_CTRL_SCLK_MODE     (SCB2_SPI_CLOCK_MODE)                | \
                     SCB2_GET_SPI_CTRL_LATE_MISO_SAMPLE(SCB2_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     SCB2_GET_SPI_CTRL_SCLK_CONTINUOUS(SCB2_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     SCB2_GET_SPI_CTRL_SSEL_POLARITY (SCB2_SPI_SS_POLARITY)               | \
                     SCB2_GET_SPI_CTRL_SUB_MODE      (SCB2_SPI_SUB_MODE)                  | \
                     SCB2_GET_SPI_CTRL_MASTER_MODE   (SCB2_SPI_MODE))

    /* RX direction */
    #define SCB2_SPI_DEFAULT_RX_CTRL \
                    (SCB2_GET_RX_CTRL_DATA_WIDTH(SCB2_SPI_RX_DATA_BITS_NUM)     | \
                     SCB2_GET_RX_CTRL_BIT_ORDER (SCB2_SPI_BITS_ORDER)           | \
                     SCB2_GET_RX_CTRL_MEDIAN    (SCB2_SPI_MEDIAN_FILTER_ENABLE) | \
                     SCB2_SPI_RX_CTRL)

    #define SCB2_SPI_DEFAULT_RX_FIFO_CTRL \
                    SCB2_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SCB2_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define SCB2_SPI_DEFAULT_TX_CTRL \
                    (SCB2_GET_TX_CTRL_DATA_WIDTH(SCB2_SPI_TX_DATA_BITS_NUM) | \
                     SCB2_GET_TX_CTRL_BIT_ORDER (SCB2_SPI_BITS_ORDER)       | \
                     SCB2_SPI_TX_CTRL)

    #define SCB2_SPI_DEFAULT_TX_FIFO_CTRL \
                    SCB2_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SCB2_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define SCB2_SPI_DEFAULT_INTR_SPI_EC_MASK   (SCB2_NO_INTR_SOURCES)

    #define SCB2_SPI_DEFAULT_INTR_I2C_EC_MASK   (SCB2_NO_INTR_SOURCES)
    #define SCB2_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (SCB2_SPI_INTR_RX_MASK & SCB2_INTR_SLAVE_SPI_BUS_ERROR)

    #define SCB2_SPI_DEFAULT_INTR_MASTER_MASK \
                    (SCB2_SPI_INTR_TX_MASK & SCB2_INTR_MASTER_SPI_DONE)

    #define SCB2_SPI_DEFAULT_INTR_RX_MASK \
                    (SCB2_SPI_INTR_RX_MASK & (uint32) ~SCB2_INTR_SLAVE_SPI_BUS_ERROR)

    #define SCB2_SPI_DEFAULT_INTR_TX_MASK \
                    (SCB2_SPI_INTR_TX_MASK & (uint32) ~SCB2_INTR_MASTER_SPI_DONE)

#endif /* (SCB2_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define SCB2_CTRL_UART      (SCB2_CTRL_MODE_UART)
#define SCB2_UART_RX_CTRL   (SCB2_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define SCB2_UART_TX_CTRL   (SCB2_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(SCB2_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(SCB2_UART_MODE_IRDA == SCB2_UART_SUB_MODE)

        #define SCB2_DEFAULT_CTRL_OVS   ((0u != SCB2_UART_IRDA_LOW_POWER) ?              \
                                (SCB2_UART_GET_CTRL_OVS_IRDA_LP(SCB2_UART_OVS_FACTOR)) : \
                                (SCB2_CTRL_OVS_IRDA_OVS16))

    #else

        #define SCB2_DEFAULT_CTRL_OVS   SCB2_GET_CTRL_OVS(SCB2_UART_OVS_FACTOR)

    #endif /* (SCB2_UART_MODE_IRDA == SCB2_UART_SUB_MODE) */

    #define SCB2_UART_DEFAULT_CTRL \
                                (SCB2_GET_CTRL_BYTE_MODE  (SCB2_UART_BYTE_MODE_ENABLE)  | \
                                 SCB2_GET_CTRL_ADDR_ACCEPT(SCB2_UART_MP_ACCEPT_ADDRESS) | \
                                 SCB2_DEFAULT_CTRL_OVS                                              | \
                                 SCB2_CTRL_UART)

    #define SCB2_UART_DEFAULT_UART_CTRL \
                                    (SCB2_GET_UART_CTRL_MODE(SCB2_UART_SUB_MODE))

    /* RX direction */
    #define SCB2_UART_DEFAULT_RX_CTRL_PARITY \
                                ((SCB2_UART_PARITY_NONE != SCB2_UART_PARITY_TYPE) ?      \
                                  (SCB2_GET_UART_RX_CTRL_PARITY(SCB2_UART_PARITY_TYPE) | \
                                   SCB2_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define SCB2_UART_DEFAULT_UART_RX_CTRL \
                    (SCB2_GET_UART_RX_CTRL_MODE(SCB2_UART_STOP_BITS_NUM)                    | \
                     SCB2_GET_UART_RX_CTRL_POLARITY(SCB2_UART_IRDA_POLARITY)                | \
                     SCB2_GET_UART_RX_CTRL_MP_MODE(SCB2_UART_MP_MODE_ENABLE)                | \
                     SCB2_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(SCB2_UART_DROP_ON_PARITY_ERR) | \
                     SCB2_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(SCB2_UART_DROP_ON_FRAME_ERR)   | \
                     SCB2_UART_DEFAULT_RX_CTRL_PARITY)

    #define SCB2_UART_DEFAULT_RX_CTRL \
                                (SCB2_GET_RX_CTRL_DATA_WIDTH(SCB2_UART_DATA_BITS_NUM)        | \
                                 SCB2_GET_RX_CTRL_MEDIAN    (SCB2_UART_MEDIAN_FILTER_ENABLE) | \
                                 SCB2_GET_UART_RX_CTRL_ENABLED(SCB2_UART_DIRECTION))

    #define SCB2_UART_DEFAULT_RX_FIFO_CTRL \
                                SCB2_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SCB2_UART_RX_TRIGGER_LEVEL)

    #define SCB2_UART_DEFAULT_RX_MATCH_REG  ((0u != SCB2_UART_MP_MODE_ENABLE) ?          \
                                (SCB2_GET_RX_MATCH_ADDR(SCB2_UART_MP_RX_ADDRESS) | \
                                 SCB2_GET_RX_MATCH_MASK(SCB2_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define SCB2_UART_DEFAULT_TX_CTRL_PARITY (SCB2_UART_DEFAULT_RX_CTRL_PARITY)

    #define SCB2_UART_DEFAULT_UART_TX_CTRL \
                                (SCB2_GET_UART_TX_CTRL_MODE(SCB2_UART_STOP_BITS_NUM)       | \
                                 SCB2_GET_UART_TX_CTRL_RETRY_NACK(SCB2_UART_RETRY_ON_NACK) | \
                                 SCB2_UART_DEFAULT_TX_CTRL_PARITY)

    #define SCB2_UART_DEFAULT_TX_CTRL \
                                (SCB2_GET_TX_CTRL_DATA_WIDTH(SCB2_UART_DATA_BITS_NUM) | \
                                 SCB2_GET_UART_TX_CTRL_ENABLED(SCB2_UART_DIRECTION))

    #define SCB2_UART_DEFAULT_TX_FIFO_CTRL \
                                SCB2_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SCB2_UART_TX_TRIGGER_LEVEL)

    #define SCB2_UART_DEFAULT_FLOW_CTRL \
                        (SCB2_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SCB2_UART_RTS_FIFO_LEVEL) | \
                         SCB2_GET_UART_FLOW_CTRL_RTS_POLARITY (SCB2_UART_RTS_POLARITY)   | \
                         SCB2_GET_UART_FLOW_CTRL_CTS_POLARITY (SCB2_UART_CTS_POLARITY)   | \
                         SCB2_GET_UART_FLOW_CTRL_CTS_ENABLE   (SCB2_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define SCB2_UART_DEFAULT_INTR_I2C_EC_MASK  (SCB2_NO_INTR_SOURCES)
    #define SCB2_UART_DEFAULT_INTR_SPI_EC_MASK  (SCB2_NO_INTR_SOURCES)
    #define SCB2_UART_DEFAULT_INTR_SLAVE_MASK   (SCB2_NO_INTR_SOURCES)
    #define SCB2_UART_DEFAULT_INTR_MASTER_MASK  (SCB2_NO_INTR_SOURCES)
    #define SCB2_UART_DEFAULT_INTR_RX_MASK      (SCB2_UART_INTR_RX_MASK)
    #define SCB2_UART_DEFAULT_INTR_TX_MASK      (SCB2_UART_INTR_TX_MASK)

#endif /* (SCB2_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define SCB2_SPIM_ACTIVE_SS0    (SCB2_SPI_SLAVE_SELECT0)
#define SCB2_SPIM_ACTIVE_SS1    (SCB2_SPI_SLAVE_SELECT1)
#define SCB2_SPIM_ACTIVE_SS2    (SCB2_SPI_SLAVE_SELECT2)
#define SCB2_SPIM_ACTIVE_SS3    (SCB2_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_SCB2_H */


/* [] END OF FILE */
