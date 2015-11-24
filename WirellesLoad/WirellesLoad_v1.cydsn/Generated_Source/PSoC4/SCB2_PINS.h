/*******************************************************************************
* File Name: SCB2_PINS.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_SCB2_H)
#define CY_SCB_PINS_SCB2_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define SCB2_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define SCB2_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define SCB2_REMOVE_TX_SDA_MISO_PIN      (1u)
#define SCB2_REMOVE_SCLK_PIN      (1u)
#define SCB2_REMOVE_SS0_PIN      (1u)
#define SCB2_REMOVE_SS1_PIN                 (1u)
#define SCB2_REMOVE_SS2_PIN                 (1u)
#define SCB2_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define SCB2_REMOVE_I2C_PINS                (1u)
#define SCB2_REMOVE_SPI_MASTER_PINS         (0u)
#define SCB2_REMOVE_SPI_MASTER_SCLK_PIN     (0u)
#define SCB2_REMOVE_SPI_MASTER_MOSI_PIN     (0u)
#define SCB2_REMOVE_SPI_MASTER_MISO_PIN     (0u)
#define SCB2_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define SCB2_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define SCB2_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define SCB2_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define SCB2_REMOVE_SPI_SLAVE_PINS          (1u)
#define SCB2_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define SCB2_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define SCB2_REMOVE_UART_TX_PIN             (1u)
#define SCB2_REMOVE_UART_RX_TX_PIN          (1u)
#define SCB2_REMOVE_UART_RX_PIN             (1u)
#define SCB2_REMOVE_UART_RX_WAKE_PIN        (1u)
#define SCB2_REMOVE_UART_RTS_PIN            (1u)
#define SCB2_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define SCB2_RX_WAKE_SCL_MOSI_PIN (0u == SCB2_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define SCB2_RX_SCL_MOSI_PIN     (0u == SCB2_REMOVE_RX_SCL_MOSI_PIN)
#define SCB2_TX_SDA_MISO_PIN     (0u == SCB2_REMOVE_TX_SDA_MISO_PIN)
#define SCB2_SCLK_PIN     (0u == SCB2_REMOVE_SCLK_PIN)
#define SCB2_SS0_PIN     (0u == SCB2_REMOVE_SS0_PIN)
#define SCB2_SS1_PIN                (0u == SCB2_REMOVE_SS1_PIN)
#define SCB2_SS2_PIN                (0u == SCB2_REMOVE_SS2_PIN)
#define SCB2_SS3_PIN                (0u == SCB2_REMOVE_SS3_PIN)

/* Mode defined pins */
#define SCB2_I2C_PINS               (0u == SCB2_REMOVE_I2C_PINS)
#define SCB2_SPI_MASTER_PINS        (0u == SCB2_REMOVE_SPI_MASTER_PINS)
#define SCB2_SPI_MASTER_SCLK_PIN    (0u == SCB2_REMOVE_SPI_MASTER_SCLK_PIN)
#define SCB2_SPI_MASTER_MOSI_PIN    (0u == SCB2_REMOVE_SPI_MASTER_MOSI_PIN)
#define SCB2_SPI_MASTER_MISO_PIN    (0u == SCB2_REMOVE_SPI_MASTER_MISO_PIN)
#define SCB2_SPI_MASTER_SS0_PIN     (0u == SCB2_REMOVE_SPI_MASTER_SS0_PIN)
#define SCB2_SPI_MASTER_SS1_PIN     (0u == SCB2_REMOVE_SPI_MASTER_SS1_PIN)
#define SCB2_SPI_MASTER_SS2_PIN     (0u == SCB2_REMOVE_SPI_MASTER_SS2_PIN)
#define SCB2_SPI_MASTER_SS3_PIN     (0u == SCB2_REMOVE_SPI_MASTER_SS3_PIN)
#define SCB2_SPI_SLAVE_PINS         (0u == SCB2_REMOVE_SPI_SLAVE_PINS)
#define SCB2_SPI_SLAVE_MOSI_PIN     (0u == SCB2_REMOVE_SPI_SLAVE_MOSI_PIN)
#define SCB2_SPI_SLAVE_MISO_PIN     (0u == SCB2_REMOVE_SPI_SLAVE_MISO_PIN)
#define SCB2_UART_TX_PIN            (0u == SCB2_REMOVE_UART_TX_PIN)
#define SCB2_UART_RX_TX_PIN         (0u == SCB2_REMOVE_UART_RX_TX_PIN)
#define SCB2_UART_RX_PIN            (0u == SCB2_REMOVE_UART_RX_PIN)
#define SCB2_UART_RX_WAKE_PIN       (0u == SCB2_REMOVE_UART_RX_WAKE_PIN)
#define SCB2_UART_RTS_PIN           (0u == SCB2_REMOVE_UART_RTS_PIN)
#define SCB2_UART_CTS_PIN           (0u == SCB2_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (SCB2_RX_WAKE_SCL_MOSI_PIN)
    #include "SCB2_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (SCB2_RX_SCL_MOSI) */

#if (SCB2_RX_SCL_MOSI_PIN)
    #include "SCB2_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (SCB2_RX_SCL_MOSI) */

#if (SCB2_TX_SDA_MISO_PIN)
    #include "SCB2_uart_tx_i2c_sda_spi_miso.h"
#endif /* (SCB2_TX_SDA_MISO) */

#if (SCB2_SCLK_PIN)
    #include "SCB2_spi_sclk.h"
#endif /* (SCB2_SCLK) */

#if (SCB2_SS0_PIN)
    #include "SCB2_spi_ss0.h"
#endif /* (SCB2_SS0_PIN) */

#if (SCB2_SS1_PIN)
    #include "SCB2_spi_ss1.h"
#endif /* (SCB2_SS1_PIN) */

#if (SCB2_SS2_PIN)
    #include "SCB2_spi_ss2.h"
#endif /* (SCB2_SS2_PIN) */

#if (SCB2_SS3_PIN)
    #include "SCB2_spi_ss3.h"
#endif /* (SCB2_SS3_PIN) */

#if (SCB2_I2C_PINS)
    #include "SCB2_scl.h"
    #include "SCB2_sda.h"
#endif /* (SCB2_I2C_PINS) */

#if (SCB2_SPI_MASTER_PINS)
#if (SCB2_SPI_MASTER_SCLK_PIN)
    #include "SCB2_sclk_m.h"
#endif /* (SCB2_SPI_MASTER_SCLK_PIN) */

#if (SCB2_SPI_MASTER_MOSI_PIN)
    #include "SCB2_mosi_m.h"
#endif /* (SCB2_SPI_MASTER_MOSI_PIN) */

#if (SCB2_SPI_MASTER_MISO_PIN)
    #include "SCB2_miso_m.h"
#endif /*(SCB2_SPI_MASTER_MISO_PIN) */
#endif /* (SCB2_SPI_MASTER_PINS) */

#if (SCB2_SPI_SLAVE_PINS)
    #include "SCB2_sclk_s.h"
    #include "SCB2_ss_s.h"

#if (SCB2_SPI_SLAVE_MOSI_PIN)
    #include "SCB2_mosi_s.h"
#endif /* (SCB2_SPI_SLAVE_MOSI_PIN) */

#if (SCB2_SPI_SLAVE_MISO_PIN)
    #include "SCB2_miso_s.h"
#endif /*(SCB2_SPI_SLAVE_MISO_PIN) */
#endif /* (SCB2_SPI_SLAVE_PINS) */

#if (SCB2_SPI_MASTER_SS0_PIN)
    #include "SCB2_ss0_m.h"
#endif /* (SCB2_SPI_MASTER_SS0_PIN) */

#if (SCB2_SPI_MASTER_SS1_PIN)
    #include "SCB2_ss1_m.h"
#endif /* (SCB2_SPI_MASTER_SS1_PIN) */

#if (SCB2_SPI_MASTER_SS2_PIN)
    #include "SCB2_ss2_m.h"
#endif /* (SCB2_SPI_MASTER_SS2_PIN) */

#if (SCB2_SPI_MASTER_SS3_PIN)
    #include "SCB2_ss3_m.h"
#endif /* (SCB2_SPI_MASTER_SS3_PIN) */

#if (SCB2_UART_TX_PIN)
    #include "SCB2_tx.h"
#endif /* (SCB2_UART_TX_PIN) */

#if (SCB2_UART_RX_TX_PIN)
    #include "SCB2_rx_tx.h"
#endif /* (SCB2_UART_RX_TX_PIN) */

#if (SCB2_UART_RX_PIN)
    #include "SCB2_rx.h"
#endif /* (SCB2_UART_RX_PIN) */

#if (SCB2_UART_RX_WAKE_PIN)
    #include "SCB2_rx_wake.h"
#endif /* (SCB2_UART_RX_WAKE_PIN) */

#if (SCB2_UART_RTS_PIN)
    #include "SCB2_rts.h"
#endif /* (SCB2_UART_RTS_PIN) */

#if (SCB2_UART_CTS_PIN)
    #include "SCB2_cts.h"
#endif /* (SCB2_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (SCB2_RX_WAKE_SCL_MOSI_PIN)
    #define SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) SCB2_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define SCB2_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) SCB2_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define SCB2_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (SCB2_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SCB2_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (SCB2_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define SCB2_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) SCB2_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SCB2_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) SCB2_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SCB2_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (SCB2_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define SCB2_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) SCB2_INTCFG_TYPE_MASK << \
                                      SCB2_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (SCB2_RX_WAKE_SCL_MOSI_PIN) */

#if (SCB2_RX_SCL_MOSI_PIN)
    #define SCB2_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) SCB2_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define SCB2_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SCB2_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define SCB2_RX_SCL_MOSI_HSIOM_MASK  (SCB2_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SCB2_RX_SCL_MOSI_HSIOM_POS   (SCB2_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (SCB2_RX_SCL_MOSI_PIN) */

#if (SCB2_TX_SDA_MISO_PIN)
    #define SCB2_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) SCB2_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define SCB2_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) SCB2_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define SCB2_TX_SDA_MISO_HSIOM_MASK  (SCB2_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define SCB2_TX_SDA_MISO_HSIOM_POS   (SCB2_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (SCB2_TX_SDA_MISO_PIN) */

#if (SCB2_SCLK_PIN)
    #define SCB2_SCLK_HSIOM_REG   (*(reg32 *) SCB2_spi_sclk__0__HSIOM)
    #define SCB2_SCLK_HSIOM_PTR   ( (reg32 *) SCB2_spi_sclk__0__HSIOM)
    #define SCB2_SCLK_HSIOM_MASK  (SCB2_spi_sclk__0__HSIOM_MASK)
    #define SCB2_SCLK_HSIOM_POS   (SCB2_spi_sclk__0__HSIOM_SHIFT)
#endif /* (SCB2_SCLK_PIN) */

#if (SCB2_SS0_PIN)
    #define SCB2_SS0_HSIOM_REG   (*(reg32 *) SCB2_spi_ss0__0__HSIOM)
    #define SCB2_SS0_HSIOM_PTR   ( (reg32 *) SCB2_spi_ss0__0__HSIOM)
    #define SCB2_SS0_HSIOM_MASK  (SCB2_spi_ss0__0__HSIOM_MASK)
    #define SCB2_SS0_HSIOM_POS   (SCB2_spi_ss0__0__HSIOM_SHIFT)
#endif /* (SCB2_SS0_PIN) */

#if (SCB2_SS1_PIN)
    #define SCB2_SS1_HSIOM_REG      (*(reg32 *) SCB2_spi_ss1__0__HSIOM)
    #define SCB2_SS1_HSIOM_PTR      ( (reg32 *) SCB2_spi_ss1__0__HSIOM)
    #define SCB2_SS1_HSIOM_MASK     (SCB2_spi_ss1__0__HSIOM_MASK)
    #define SCB2_SS1_HSIOM_POS      (SCB2_spi_ss1__0__HSIOM_SHIFT)
#endif /* (SCB2_SS1_PIN) */

#if (SCB2_SS2_PIN)
    #define SCB2_SS2_HSIOM_REG     (*(reg32 *) SCB2_spi_ss2__0__HSIOM)
    #define SCB2_SS2_HSIOM_PTR     ( (reg32 *) SCB2_spi_ss2__0__HSIOM)
    #define SCB2_SS2_HSIOM_MASK    (SCB2_spi_ss2__0__HSIOM_MASK)
    #define SCB2_SS2_HSIOM_POS     (SCB2_spi_ss2__0__HSIOM_SHIFT)
#endif /* (SCB2_SS2_PIN) */

#if (SCB2_SS3_PIN)
    #define SCB2_SS3_HSIOM_REG     (*(reg32 *) SCB2_spi_ss3__0__HSIOM)
    #define SCB2_SS3_HSIOM_PTR     ( (reg32 *) SCB2_spi_ss3__0__HSIOM)
    #define SCB2_SS3_HSIOM_MASK    (SCB2_spi_ss3__0__HSIOM_MASK)
    #define SCB2_SS3_HSIOM_POS     (SCB2_spi_ss3__0__HSIOM_SHIFT)
#endif /* (SCB2_SS3_PIN) */

#if (SCB2_I2C_PINS)
    #define SCB2_SCL_HSIOM_REG     (*(reg32 *) SCB2_scl__0__HSIOM)
    #define SCB2_SCL_HSIOM_PTR     ( (reg32 *) SCB2_scl__0__HSIOM)
    #define SCB2_SCL_HSIOM_MASK    (SCB2_scl__0__HSIOM_MASK)
    #define SCB2_SCL_HSIOM_POS     (SCB2_scl__0__HSIOM_SHIFT)

    #define SCB2_SDA_HSIOM_REG     (*(reg32 *) SCB2_sda__0__HSIOM)
    #define SCB2_SDA_HSIOM_PTR     ( (reg32 *) SCB2_sda__0__HSIOM)
    #define SCB2_SDA_HSIOM_MASK    (SCB2_sda__0__HSIOM_MASK)
    #define SCB2_SDA_HSIOM_POS     (SCB2_sda__0__HSIOM_SHIFT)
#endif /* (SCB2_I2C_PINS) */

#if (SCB2_SPI_MASTER_SCLK_PIN)
    #define SCB2_SCLK_M_HSIOM_REG   (*(reg32 *) SCB2_sclk_m__0__HSIOM)
    #define SCB2_SCLK_M_HSIOM_PTR   ( (reg32 *) SCB2_sclk_m__0__HSIOM)
    #define SCB2_SCLK_M_HSIOM_MASK  (SCB2_sclk_m__0__HSIOM_MASK)
    #define SCB2_SCLK_M_HSIOM_POS   (SCB2_sclk_m__0__HSIOM_SHIFT)
#endif /* (SCB2_SPI_MASTER_SCLK_PIN) */

#if (SCB2_SPI_MASTER_SS0_PIN)
    #define SCB2_SS0_M_HSIOM_REG    (*(reg32 *) SCB2_ss0_m__0__HSIOM)
    #define SCB2_SS0_M_HSIOM_PTR    ( (reg32 *) SCB2_ss0_m__0__HSIOM)
    #define SCB2_SS0_M_HSIOM_MASK   (SCB2_ss0_m__0__HSIOM_MASK)
    #define SCB2_SS0_M_HSIOM_POS    (SCB2_ss0_m__0__HSIOM_SHIFT)
#endif /* (SCB2_SPI_MASTER_SS0_PIN) */

#if (SCB2_SPI_MASTER_SS1_PIN)
    #define SCB2_SS1_M_HSIOM_REG    (*(reg32 *) SCB2_ss1_m__0__HSIOM)
    #define SCB2_SS1_M_HSIOM_PTR    ( (reg32 *) SCB2_ss1_m__0__HSIOM)
    #define SCB2_SS1_M_HSIOM_MASK   (SCB2_ss1_m__0__HSIOM_MASK)
    #define SCB2_SS1_M_HSIOM_POS    (SCB2_ss1_m__0__HSIOM_SHIFT)
#endif /* (SCB2_SPI_MASTER_SS1_PIN) */

#if (SCB2_SPI_MASTER_SS2_PIN)
    #define SCB2_SS2_M_HSIOM_REG    (*(reg32 *) SCB2_ss2_m__0__HSIOM)
    #define SCB2_SS2_M_HSIOM_PTR    ( (reg32 *) SCB2_ss2_m__0__HSIOM)
    #define SCB2_SS2_M_HSIOM_MASK   (SCB2_ss2_m__0__HSIOM_MASK)
    #define SCB2_SS2_M_HSIOM_POS    (SCB2_ss2_m__0__HSIOM_SHIFT)
#endif /* (SCB2_SPI_MASTER_SS2_PIN) */

#if (SCB2_SPI_MASTER_SS3_PIN)
    #define SCB2_SS3_M_HSIOM_REG    (*(reg32 *) SCB2_ss3_m__0__HSIOM)
    #define SCB2_SS3_M_HSIOM_PTR    ( (reg32 *) SCB2_ss3_m__0__HSIOM)
    #define SCB2_SS3_M_HSIOM_MASK   (SCB2_ss3_m__0__HSIOM_MASK)
    #define SCB2_SS3_M_HSIOM_POS    (SCB2_ss3_m__0__HSIOM_SHIFT)
#endif /* (SCB2_SPI_MASTER_SS3_PIN) */

#if (SCB2_UART_TX_PIN)
    #define SCB2_TX_HSIOM_REG   (*(reg32 *) SCB2_tx__0__HSIOM)
    #define SCB2_TX_HSIOM_PTR   ( (reg32 *) SCB2_tx_0__HSIOM)
    #define SCB2_TX_HSIOM_MASK  (SCB2_tx__0__HSIOM_MASK)
    #define SCB2_TX_HSIOM_POS   (SCB2_tx__0__HSIOM_SHIFT)
#endif /* (SCB2_UART_TX_PIN) */

#if (SCB2_UART_RTS_PIN)
    #define SCB2_RTS_HSIOM_REG  (*(reg32 *) SCB2_rts__0__HSIOM)
    #define SCB2_RTS_HSIOM_PTR  ( (reg32 *) SCB2_rts__0__HSIOM)
    #define SCB2_RTS_HSIOM_MASK (SCB2_rts__0__HSIOM_MASK)
    #define SCB2_RTS_HSIOM_POS  (SCB2_rts__0__HSIOM_SHIFT)
#endif /* (SCB2_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define SCB2_HSIOM_DEF_SEL      (0x00u)
#define SCB2_HSIOM_GPIO_SEL     (0x00u)
#define SCB2_HSIOM_UART_SEL     (0x09u)
#define SCB2_HSIOM_I2C_SEL      (0x0Eu)
#define SCB2_HSIOM_SPI_SEL      (0x0Fu)

#define SCB2_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define SCB2_RX_SCL_MOSI_PIN_INDEX       (0u)
#define SCB2_TX_SDA_MISO_PIN_INDEX       (1u)
#define SCB2_SCLK_PIN_INDEX       (2u)
#define SCB2_SS0_PIN_INDEX       (3u)
#define SCB2_SS1_PIN_INDEX                  (4u)
#define SCB2_SS2_PIN_INDEX                  (5u)
#define SCB2_SS3_PIN_INDEX                  (6u)

#define SCB2_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << SCB2_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define SCB2_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << SCB2_RX_SCL_MOSI_PIN_INDEX)
#define SCB2_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << SCB2_TX_SDA_MISO_PIN_INDEX)
#define SCB2_SCLK_PIN_MASK     ((uint32) 0x01u << SCB2_SCLK_PIN_INDEX)
#define SCB2_SS0_PIN_MASK     ((uint32) 0x01u << SCB2_SS0_PIN_INDEX)
#define SCB2_SS1_PIN_MASK                ((uint32) 0x01u << SCB2_SS1_PIN_INDEX)
#define SCB2_SS2_PIN_MASK                ((uint32) 0x01u << SCB2_SS2_PIN_INDEX)
#define SCB2_SS3_PIN_MASK                ((uint32) 0x01u << SCB2_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define SCB2_INTCFG_TYPE_MASK           (0x03u)
#define SCB2_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define SCB2_PIN_DM_ALG_HIZ  (0u)
#define SCB2_PIN_DM_DIG_HIZ  (1u)
#define SCB2_PIN_DM_OD_LO    (4u)
#define SCB2_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define SCB2_DM_MASK    (0x7u)
#define SCB2_DM_SIZE    (3)
#define SCB2_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) SCB2_DM_MASK << (SCB2_DM_SIZE * (pos)))) >> \
                                                              (SCB2_DM_SIZE * (pos)) )

#if (SCB2_TX_SDA_MISO_PIN)
    #define SCB2_CHECK_TX_SDA_MISO_PIN_USED \
                (SCB2_PIN_DM_ALG_HIZ != \
                    SCB2_GET_P4_PIN_DM(SCB2_uart_tx_i2c_sda_spi_miso_PC, \
                                                   SCB2_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (SCB2_TX_SDA_MISO_PIN) */

#if (SCB2_SS0_PIN)
    #define SCB2_CHECK_SS0_PIN_USED \
                (SCB2_PIN_DM_ALG_HIZ != \
                    SCB2_GET_P4_PIN_DM(SCB2_spi_ss0_PC, \
                                                   SCB2_spi_ss0_SHIFT))
#endif /* (SCB2_SS0_PIN) */

/* Set bits-mask in register */
#define SCB2_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define SCB2_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define SCB2_SET_HSIOM_SEL(reg, mask, pos, sel) SCB2_SET_REGISTER_BITS(reg, mask, pos, sel)
#define SCB2_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        SCB2_SET_REGISTER_BITS(reg, mask, pos, intType)
#define SCB2_SET_INP_DIS(reg, mask, val) SCB2_SET_REGISTER_BIT(reg, mask, val)

/* SCB2_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  SCB2_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (SCB2_CY_SCBIP_V0)
#if (SCB2_I2C_PINS)
    #define SCB2_SET_I2C_SCL_DR(val) SCB2_scl_Write(val)

    #define SCB2_SET_I2C_SCL_HSIOM_SEL(sel) \
                          SCB2_SET_HSIOM_SEL(SCB2_SCL_HSIOM_REG,  \
                                                         SCB2_SCL_HSIOM_MASK, \
                                                         SCB2_SCL_HSIOM_POS,  \
                                                         (sel))
    #define SCB2_WAIT_SCL_SET_HIGH  (0u == SCB2_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (SCB2_RX_WAKE_SCL_MOSI_PIN)
    #define SCB2_SET_I2C_SCL_DR(val) \
                            SCB2_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define SCB2_SET_I2C_SCL_HSIOM_SEL(sel) \
                    SCB2_SET_HSIOM_SEL(SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   SCB2_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   SCB2_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define SCB2_WAIT_SCL_SET_HIGH  (0u == SCB2_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (SCB2_RX_SCL_MOSI_PIN)
    #define SCB2_SET_I2C_SCL_DR(val) \
                            SCB2_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define SCB2_SET_I2C_SCL_HSIOM_SEL(sel) \
                            SCB2_SET_HSIOM_SEL(SCB2_RX_SCL_MOSI_HSIOM_REG,  \
                                                           SCB2_RX_SCL_MOSI_HSIOM_MASK, \
                                                           SCB2_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define SCB2_WAIT_SCL_SET_HIGH  (0u == SCB2_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define SCB2_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define SCB2_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define SCB2_WAIT_SCL_SET_HIGH  (0u)
#endif /* (SCB2_I2C_PINS) */

/* SCB I2C: sda signal */
#if (SCB2_I2C_PINS)
    #define SCB2_WAIT_SDA_SET_HIGH  (0u == SCB2_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (SCB2_TX_SDA_MISO_PIN)
    #define SCB2_WAIT_SDA_SET_HIGH  (0u == SCB2_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define SCB2_WAIT_SDA_SET_HIGH  (0u)
#endif /* (SCB2_MOSI_SCL_RX_PIN) */
#endif /* (SCB2_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define SCB2_REMOVE_MOSI_SCL_RX_WAKE_PIN    SCB2_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define SCB2_REMOVE_MOSI_SCL_RX_PIN         SCB2_REMOVE_RX_SCL_MOSI_PIN
#define SCB2_REMOVE_MISO_SDA_TX_PIN         SCB2_REMOVE_TX_SDA_MISO_PIN
#ifndef SCB2_REMOVE_SCLK_PIN
#define SCB2_REMOVE_SCLK_PIN                SCB2_REMOVE_SCLK_PIN
#endif /* SCB2_REMOVE_SCLK_PIN */
#ifndef SCB2_REMOVE_SS0_PIN
#define SCB2_REMOVE_SS0_PIN                 SCB2_REMOVE_SS0_PIN
#endif /* SCB2_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define SCB2_MOSI_SCL_RX_WAKE_PIN   SCB2_RX_WAKE_SCL_MOSI_PIN
#define SCB2_MOSI_SCL_RX_PIN        SCB2_RX_SCL_MOSI_PIN
#define SCB2_MISO_SDA_TX_PIN        SCB2_TX_SDA_MISO_PIN
#ifndef SCB2_SCLK_PIN
#define SCB2_SCLK_PIN               SCB2_SCLK_PIN
#endif /* SCB2_SCLK_PIN */
#ifndef SCB2_SS0_PIN
#define SCB2_SS0_PIN                SCB2_SS0_PIN
#endif /* SCB2_SS0_PIN */

#if (SCB2_MOSI_SCL_RX_WAKE_PIN)
    #define SCB2_MOSI_SCL_RX_WAKE_HSIOM_REG     SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SCB2_MOSI_SCL_RX_WAKE_HSIOM_PTR     SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SCB2_MOSI_SCL_RX_WAKE_HSIOM_MASK    SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SCB2_MOSI_SCL_RX_WAKE_HSIOM_POS     SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SCB2_MOSI_SCL_RX_WAKE_INTCFG_REG    SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SCB2_MOSI_SCL_RX_WAKE_INTCFG_PTR    SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SCB2_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SCB2_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  SCB2_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (SCB2_RX_WAKE_SCL_MOSI_PIN) */

#if (SCB2_MOSI_SCL_RX_PIN)
    #define SCB2_MOSI_SCL_RX_HSIOM_REG      SCB2_RX_SCL_MOSI_HSIOM_REG
    #define SCB2_MOSI_SCL_RX_HSIOM_PTR      SCB2_RX_SCL_MOSI_HSIOM_PTR
    #define SCB2_MOSI_SCL_RX_HSIOM_MASK     SCB2_RX_SCL_MOSI_HSIOM_MASK
    #define SCB2_MOSI_SCL_RX_HSIOM_POS      SCB2_RX_SCL_MOSI_HSIOM_POS
#endif /* (SCB2_MOSI_SCL_RX_PIN) */

#if (SCB2_MISO_SDA_TX_PIN)
    #define SCB2_MISO_SDA_TX_HSIOM_REG      SCB2_TX_SDA_MISO_HSIOM_REG
    #define SCB2_MISO_SDA_TX_HSIOM_PTR      SCB2_TX_SDA_MISO_HSIOM_REG
    #define SCB2_MISO_SDA_TX_HSIOM_MASK     SCB2_TX_SDA_MISO_HSIOM_REG
    #define SCB2_MISO_SDA_TX_HSIOM_POS      SCB2_TX_SDA_MISO_HSIOM_REG
#endif /* (SCB2_MISO_SDA_TX_PIN_PIN) */

#if (SCB2_SCLK_PIN)
    #ifndef SCB2_SCLK_HSIOM_REG
    #define SCB2_SCLK_HSIOM_REG     SCB2_SCLK_HSIOM_REG
    #define SCB2_SCLK_HSIOM_PTR     SCB2_SCLK_HSIOM_PTR
    #define SCB2_SCLK_HSIOM_MASK    SCB2_SCLK_HSIOM_MASK
    #define SCB2_SCLK_HSIOM_POS     SCB2_SCLK_HSIOM_POS
    #endif /* SCB2_SCLK_HSIOM_REG */
#endif /* (SCB2_SCLK_PIN) */

#if (SCB2_SS0_PIN)
    #ifndef SCB2_SS0_HSIOM_REG
    #define SCB2_SS0_HSIOM_REG      SCB2_SS0_HSIOM_REG
    #define SCB2_SS0_HSIOM_PTR      SCB2_SS0_HSIOM_PTR
    #define SCB2_SS0_HSIOM_MASK     SCB2_SS0_HSIOM_MASK
    #define SCB2_SS0_HSIOM_POS      SCB2_SS0_HSIOM_POS
    #endif /* SCB2_SS0_HSIOM_REG */
#endif /* (SCB2_SS0_PIN) */

#define SCB2_MOSI_SCL_RX_WAKE_PIN_INDEX SCB2_RX_WAKE_SCL_MOSI_PIN_INDEX
#define SCB2_MOSI_SCL_RX_PIN_INDEX      SCB2_RX_SCL_MOSI_PIN_INDEX
#define SCB2_MISO_SDA_TX_PIN_INDEX      SCB2_TX_SDA_MISO_PIN_INDEX
#ifndef SCB2_SCLK_PIN_INDEX
#define SCB2_SCLK_PIN_INDEX             SCB2_SCLK_PIN_INDEX
#endif /* SCB2_SCLK_PIN_INDEX */
#ifndef SCB2_SS0_PIN_INDEX
#define SCB2_SS0_PIN_INDEX              SCB2_SS0_PIN_INDEX
#endif /* SCB2_SS0_PIN_INDEX */

#define SCB2_MOSI_SCL_RX_WAKE_PIN_MASK SCB2_RX_WAKE_SCL_MOSI_PIN_MASK
#define SCB2_MOSI_SCL_RX_PIN_MASK      SCB2_RX_SCL_MOSI_PIN_MASK
#define SCB2_MISO_SDA_TX_PIN_MASK      SCB2_TX_SDA_MISO_PIN_MASK
#ifndef SCB2_SCLK_PIN_MASK
#define SCB2_SCLK_PIN_MASK             SCB2_SCLK_PIN_MASK
#endif /* SCB2_SCLK_PIN_MASK */
#ifndef SCB2_SS0_PIN_MASK
#define SCB2_SS0_PIN_MASK              SCB2_SS0_PIN_MASK
#endif /* SCB2_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_SCB2_H) */


/* [] END OF FILE */
