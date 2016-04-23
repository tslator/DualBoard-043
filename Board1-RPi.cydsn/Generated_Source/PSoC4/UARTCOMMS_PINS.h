/*******************************************************************************
* File Name: UARTCOMMS_PINS.h
* Version 3.10
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

#if !defined(CY_SCB_PINS_UARTCOMMS_H)
#define CY_SCB_PINS_UARTCOMMS_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define UARTCOMMS_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define UARTCOMMS_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define UARTCOMMS_REMOVE_TX_SDA_MISO_PIN      (1u)
#define UARTCOMMS_REMOVE_CTS_SCLK_PIN      (1u)
#define UARTCOMMS_REMOVE_RTS_SS0_PIN      (1u)
#define UARTCOMMS_REMOVE_SS1_PIN                 (1u)
#define UARTCOMMS_REMOVE_SS2_PIN                 (1u)
#define UARTCOMMS_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define UARTCOMMS_REMOVE_I2C_PINS                (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_PINS         (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define UARTCOMMS_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define UARTCOMMS_REMOVE_SPI_SLAVE_PINS          (1u)
#define UARTCOMMS_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define UARTCOMMS_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define UARTCOMMS_REMOVE_UART_TX_PIN             (0u)
#define UARTCOMMS_REMOVE_UART_RX_TX_PIN          (1u)
#define UARTCOMMS_REMOVE_UART_RX_PIN             (0u)
#define UARTCOMMS_REMOVE_UART_RX_WAKE_PIN        (1u)
#define UARTCOMMS_REMOVE_UART_RTS_PIN            (1u)
#define UARTCOMMS_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define UARTCOMMS_RX_WAKE_SCL_MOSI_PIN (0u == UARTCOMMS_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define UARTCOMMS_RX_SCL_MOSI_PIN     (0u == UARTCOMMS_REMOVE_RX_SCL_MOSI_PIN)
#define UARTCOMMS_TX_SDA_MISO_PIN     (0u == UARTCOMMS_REMOVE_TX_SDA_MISO_PIN)
#define UARTCOMMS_CTS_SCLK_PIN     (0u == UARTCOMMS_REMOVE_CTS_SCLK_PIN)
#define UARTCOMMS_RTS_SS0_PIN     (0u == UARTCOMMS_REMOVE_RTS_SS0_PIN)
#define UARTCOMMS_SS1_PIN                (0u == UARTCOMMS_REMOVE_SS1_PIN)
#define UARTCOMMS_SS2_PIN                (0u == UARTCOMMS_REMOVE_SS2_PIN)
#define UARTCOMMS_SS3_PIN                (0u == UARTCOMMS_REMOVE_SS3_PIN)

/* Mode defined pins */
#define UARTCOMMS_I2C_PINS               (0u == UARTCOMMS_REMOVE_I2C_PINS)
#define UARTCOMMS_SPI_MASTER_PINS        (0u == UARTCOMMS_REMOVE_SPI_MASTER_PINS)
#define UARTCOMMS_SPI_MASTER_SCLK_PIN    (0u == UARTCOMMS_REMOVE_SPI_MASTER_SCLK_PIN)
#define UARTCOMMS_SPI_MASTER_MOSI_PIN    (0u == UARTCOMMS_REMOVE_SPI_MASTER_MOSI_PIN)
#define UARTCOMMS_SPI_MASTER_MISO_PIN    (0u == UARTCOMMS_REMOVE_SPI_MASTER_MISO_PIN)
#define UARTCOMMS_SPI_MASTER_SS0_PIN     (0u == UARTCOMMS_REMOVE_SPI_MASTER_SS0_PIN)
#define UARTCOMMS_SPI_MASTER_SS1_PIN     (0u == UARTCOMMS_REMOVE_SPI_MASTER_SS1_PIN)
#define UARTCOMMS_SPI_MASTER_SS2_PIN     (0u == UARTCOMMS_REMOVE_SPI_MASTER_SS2_PIN)
#define UARTCOMMS_SPI_MASTER_SS3_PIN     (0u == UARTCOMMS_REMOVE_SPI_MASTER_SS3_PIN)
#define UARTCOMMS_SPI_SLAVE_PINS         (0u == UARTCOMMS_REMOVE_SPI_SLAVE_PINS)
#define UARTCOMMS_SPI_SLAVE_MOSI_PIN     (0u == UARTCOMMS_REMOVE_SPI_SLAVE_MOSI_PIN)
#define UARTCOMMS_SPI_SLAVE_MISO_PIN     (0u == UARTCOMMS_REMOVE_SPI_SLAVE_MISO_PIN)
#define UARTCOMMS_UART_TX_PIN            (0u == UARTCOMMS_REMOVE_UART_TX_PIN)
#define UARTCOMMS_UART_RX_TX_PIN         (0u == UARTCOMMS_REMOVE_UART_RX_TX_PIN)
#define UARTCOMMS_UART_RX_PIN            (0u == UARTCOMMS_REMOVE_UART_RX_PIN)
#define UARTCOMMS_UART_RX_WAKE_PIN       (0u == UARTCOMMS_REMOVE_UART_RX_WAKE_PIN)
#define UARTCOMMS_UART_RTS_PIN           (0u == UARTCOMMS_REMOVE_UART_RTS_PIN)
#define UARTCOMMS_UART_CTS_PIN           (0u == UARTCOMMS_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN)
    #include "UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (UARTCOMMS_RX_SCL_MOSI) */

#if (UARTCOMMS_RX_SCL_MOSI_PIN)
    #include "UARTCOMMS_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (UARTCOMMS_RX_SCL_MOSI) */

#if (UARTCOMMS_TX_SDA_MISO_PIN)
    #include "UARTCOMMS_uart_tx_i2c_sda_spi_miso.h"
#endif /* (UARTCOMMS_TX_SDA_MISO) */

#if (UARTCOMMS_CTS_SCLK_PIN)
    #include "UARTCOMMS_uart_cts_spi_sclk.h"
#endif /* (UARTCOMMS_CTS_SCLK) */

#if (UARTCOMMS_RTS_SS0_PIN)
    #include "UARTCOMMS_uart_rts_spi_ss0.h"
#endif /* (UARTCOMMS_RTS_SS0_PIN) */

#if (UARTCOMMS_SS1_PIN)
    #include "UARTCOMMS_spi_ss1.h"
#endif /* (UARTCOMMS_SS1_PIN) */

#if (UARTCOMMS_SS2_PIN)
    #include "UARTCOMMS_spi_ss2.h"
#endif /* (UARTCOMMS_SS2_PIN) */

#if (UARTCOMMS_SS3_PIN)
    #include "UARTCOMMS_spi_ss3.h"
#endif /* (UARTCOMMS_SS3_PIN) */

#if (UARTCOMMS_I2C_PINS)
    #include "UARTCOMMS_scl.h"
    #include "UARTCOMMS_sda.h"
#endif /* (UARTCOMMS_I2C_PINS) */

#if (UARTCOMMS_SPI_MASTER_PINS)
#if (UARTCOMMS_SPI_MASTER_SCLK_PIN)
    #include "UARTCOMMS_sclk_m.h"
#endif /* (UARTCOMMS_SPI_MASTER_SCLK_PIN) */

#if (UARTCOMMS_SPI_MASTER_MOSI_PIN)
    #include "UARTCOMMS_mosi_m.h"
#endif /* (UARTCOMMS_SPI_MASTER_MOSI_PIN) */

#if (UARTCOMMS_SPI_MASTER_MISO_PIN)
    #include "UARTCOMMS_miso_m.h"
#endif /*(UARTCOMMS_SPI_MASTER_MISO_PIN) */
#endif /* (UARTCOMMS_SPI_MASTER_PINS) */

#if (UARTCOMMS_SPI_SLAVE_PINS)
    #include "UARTCOMMS_sclk_s.h"
    #include "UARTCOMMS_ss_s.h"

#if (UARTCOMMS_SPI_SLAVE_MOSI_PIN)
    #include "UARTCOMMS_mosi_s.h"
#endif /* (UARTCOMMS_SPI_SLAVE_MOSI_PIN) */

#if (UARTCOMMS_SPI_SLAVE_MISO_PIN)
    #include "UARTCOMMS_miso_s.h"
#endif /*(UARTCOMMS_SPI_SLAVE_MISO_PIN) */
#endif /* (UARTCOMMS_SPI_SLAVE_PINS) */

#if (UARTCOMMS_SPI_MASTER_SS0_PIN)
    #include "UARTCOMMS_ss0_m.h"
#endif /* (UARTCOMMS_SPI_MASTER_SS0_PIN) */

#if (UARTCOMMS_SPI_MASTER_SS1_PIN)
    #include "UARTCOMMS_ss1_m.h"
#endif /* (UARTCOMMS_SPI_MASTER_SS1_PIN) */

#if (UARTCOMMS_SPI_MASTER_SS2_PIN)
    #include "UARTCOMMS_ss2_m.h"
#endif /* (UARTCOMMS_SPI_MASTER_SS2_PIN) */

#if (UARTCOMMS_SPI_MASTER_SS3_PIN)
    #include "UARTCOMMS_ss3_m.h"
#endif /* (UARTCOMMS_SPI_MASTER_SS3_PIN) */

#if (UARTCOMMS_UART_TX_PIN)
    #include "UARTCOMMS_tx.h"
#endif /* (UARTCOMMS_UART_TX_PIN) */

#if (UARTCOMMS_UART_RX_TX_PIN)
    #include "UARTCOMMS_rx_tx.h"
#endif /* (UARTCOMMS_UART_RX_TX_PIN) */

#if (UARTCOMMS_UART_RX_PIN)
    #include "UARTCOMMS_rx.h"
#endif /* (UARTCOMMS_UART_RX_PIN) */

#if (UARTCOMMS_UART_RX_WAKE_PIN)
    #include "UARTCOMMS_rx_wake.h"
#endif /* (UARTCOMMS_UART_RX_WAKE_PIN) */

#if (UARTCOMMS_UART_RTS_PIN)
    #include "UARTCOMMS_rts.h"
#endif /* (UARTCOMMS_UART_RTS_PIN) */

#if (UARTCOMMS_UART_CTS_PIN)
    #include "UARTCOMMS_cts.h"
#endif /* (UARTCOMMS_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN)
    #define UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) UARTCOMMS_INTCFG_TYPE_MASK << \
                                      UARTCOMMS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN) */

#if (UARTCOMMS_RX_SCL_MOSI_PIN)
    #define UARTCOMMS_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) UARTCOMMS_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define UARTCOMMS_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UARTCOMMS_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define UARTCOMMS_RX_SCL_MOSI_HSIOM_MASK  (UARTCOMMS_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UARTCOMMS_RX_SCL_MOSI_HSIOM_POS   (UARTCOMMS_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_RX_SCL_MOSI_PIN) */

#if (UARTCOMMS_TX_SDA_MISO_PIN)
    #define UARTCOMMS_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) UARTCOMMS_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define UARTCOMMS_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) UARTCOMMS_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define UARTCOMMS_TX_SDA_MISO_HSIOM_MASK  (UARTCOMMS_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define UARTCOMMS_TX_SDA_MISO_HSIOM_POS   (UARTCOMMS_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_TX_SDA_MISO_PIN) */

#if (UARTCOMMS_CTS_SCLK_PIN)
    #define UARTCOMMS_CTS_SCLK_HSIOM_REG   (*(reg32 *) UARTCOMMS_uart_cts_spi_sclk__0__HSIOM)
    #define UARTCOMMS_CTS_SCLK_HSIOM_PTR   ( (reg32 *) UARTCOMMS_uart_cts_spi_sclk__0__HSIOM)
    #define UARTCOMMS_CTS_SCLK_HSIOM_MASK  (UARTCOMMS_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define UARTCOMMS_CTS_SCLK_HSIOM_POS   (UARTCOMMS_uart_cts_spi_sclk__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_CTS_SCLK_PIN) */

#if (UARTCOMMS_RTS_SS0_PIN)
    #define UARTCOMMS_RTS_SS0_HSIOM_REG   (*(reg32 *) UARTCOMMS_uart_rts_spi_ss0__0__HSIOM)
    #define UARTCOMMS_RTS_SS0_HSIOM_PTR   ( (reg32 *) UARTCOMMS_uart_rts_spi_ss0__0__HSIOM)
    #define UARTCOMMS_RTS_SS0_HSIOM_MASK  (UARTCOMMS_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define UARTCOMMS_RTS_SS0_HSIOM_POS   (UARTCOMMS_uart_rts_spi_ss0__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_RTS_SS0_PIN) */

#if (UARTCOMMS_SS1_PIN)
    #define UARTCOMMS_SS1_HSIOM_REG      (*(reg32 *) UARTCOMMS_spi_ss1__0__HSIOM)
    #define UARTCOMMS_SS1_HSIOM_PTR      ( (reg32 *) UARTCOMMS_spi_ss1__0__HSIOM)
    #define UARTCOMMS_SS1_HSIOM_MASK     (UARTCOMMS_spi_ss1__0__HSIOM_MASK)
    #define UARTCOMMS_SS1_HSIOM_POS      (UARTCOMMS_spi_ss1__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SS1_PIN) */

#if (UARTCOMMS_SS2_PIN)
    #define UARTCOMMS_SS2_HSIOM_REG     (*(reg32 *) UARTCOMMS_spi_ss2__0__HSIOM)
    #define UARTCOMMS_SS2_HSIOM_PTR     ( (reg32 *) UARTCOMMS_spi_ss2__0__HSIOM)
    #define UARTCOMMS_SS2_HSIOM_MASK    (UARTCOMMS_spi_ss2__0__HSIOM_MASK)
    #define UARTCOMMS_SS2_HSIOM_POS     (UARTCOMMS_spi_ss2__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SS2_PIN) */

#if (UARTCOMMS_SS3_PIN)
    #define UARTCOMMS_SS3_HSIOM_REG     (*(reg32 *) UARTCOMMS_spi_ss3__0__HSIOM)
    #define UARTCOMMS_SS3_HSIOM_PTR     ( (reg32 *) UARTCOMMS_spi_ss3__0__HSIOM)
    #define UARTCOMMS_SS3_HSIOM_MASK    (UARTCOMMS_spi_ss3__0__HSIOM_MASK)
    #define UARTCOMMS_SS3_HSIOM_POS     (UARTCOMMS_spi_ss3__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SS3_PIN) */

#if (UARTCOMMS_I2C_PINS)
    #define UARTCOMMS_SCL_HSIOM_REG     (*(reg32 *) UARTCOMMS_scl__0__HSIOM)
    #define UARTCOMMS_SCL_HSIOM_PTR     ( (reg32 *) UARTCOMMS_scl__0__HSIOM)
    #define UARTCOMMS_SCL_HSIOM_MASK    (UARTCOMMS_scl__0__HSIOM_MASK)
    #define UARTCOMMS_SCL_HSIOM_POS     (UARTCOMMS_scl__0__HSIOM_SHIFT)

    #define UARTCOMMS_SDA_HSIOM_REG     (*(reg32 *) UARTCOMMS_sda__0__HSIOM)
    #define UARTCOMMS_SDA_HSIOM_PTR     ( (reg32 *) UARTCOMMS_sda__0__HSIOM)
    #define UARTCOMMS_SDA_HSIOM_MASK    (UARTCOMMS_sda__0__HSIOM_MASK)
    #define UARTCOMMS_SDA_HSIOM_POS     (UARTCOMMS_sda__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_I2C_PINS) */

#if (UARTCOMMS_SPI_MASTER_SCLK_PIN)
    #define UARTCOMMS_SCLK_M_HSIOM_REG   (*(reg32 *) UARTCOMMS_sclk_m__0__HSIOM)
    #define UARTCOMMS_SCLK_M_HSIOM_PTR   ( (reg32 *) UARTCOMMS_sclk_m__0__HSIOM)
    #define UARTCOMMS_SCLK_M_HSIOM_MASK  (UARTCOMMS_sclk_m__0__HSIOM_MASK)
    #define UARTCOMMS_SCLK_M_HSIOM_POS   (UARTCOMMS_sclk_m__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SPI_MASTER_SCLK_PIN) */

#if (UARTCOMMS_SPI_MASTER_SS0_PIN)
    #define UARTCOMMS_SS0_M_HSIOM_REG    (*(reg32 *) UARTCOMMS_ss0_m__0__HSIOM)
    #define UARTCOMMS_SS0_M_HSIOM_PTR    ( (reg32 *) UARTCOMMS_ss0_m__0__HSIOM)
    #define UARTCOMMS_SS0_M_HSIOM_MASK   (UARTCOMMS_ss0_m__0__HSIOM_MASK)
    #define UARTCOMMS_SS0_M_HSIOM_POS    (UARTCOMMS_ss0_m__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SPI_MASTER_SS0_PIN) */

#if (UARTCOMMS_SPI_MASTER_SS1_PIN)
    #define UARTCOMMS_SS1_M_HSIOM_REG    (*(reg32 *) UARTCOMMS_ss1_m__0__HSIOM)
    #define UARTCOMMS_SS1_M_HSIOM_PTR    ( (reg32 *) UARTCOMMS_ss1_m__0__HSIOM)
    #define UARTCOMMS_SS1_M_HSIOM_MASK   (UARTCOMMS_ss1_m__0__HSIOM_MASK)
    #define UARTCOMMS_SS1_M_HSIOM_POS    (UARTCOMMS_ss1_m__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SPI_MASTER_SS1_PIN) */

#if (UARTCOMMS_SPI_MASTER_SS2_PIN)
    #define UARTCOMMS_SS2_M_HSIOM_REG    (*(reg32 *) UARTCOMMS_ss2_m__0__HSIOM)
    #define UARTCOMMS_SS2_M_HSIOM_PTR    ( (reg32 *) UARTCOMMS_ss2_m__0__HSIOM)
    #define UARTCOMMS_SS2_M_HSIOM_MASK   (UARTCOMMS_ss2_m__0__HSIOM_MASK)
    #define UARTCOMMS_SS2_M_HSIOM_POS    (UARTCOMMS_ss2_m__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SPI_MASTER_SS2_PIN) */

#if (UARTCOMMS_SPI_MASTER_SS3_PIN)
    #define UARTCOMMS_SS3_M_HSIOM_REG    (*(reg32 *) UARTCOMMS_ss3_m__0__HSIOM)
    #define UARTCOMMS_SS3_M_HSIOM_PTR    ( (reg32 *) UARTCOMMS_ss3_m__0__HSIOM)
    #define UARTCOMMS_SS3_M_HSIOM_MASK   (UARTCOMMS_ss3_m__0__HSIOM_MASK)
    #define UARTCOMMS_SS3_M_HSIOM_POS    (UARTCOMMS_ss3_m__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_SPI_MASTER_SS3_PIN) */

#if (UARTCOMMS_UART_TX_PIN)
    #define UARTCOMMS_TX_HSIOM_REG   (*(reg32 *) UARTCOMMS_tx__0__HSIOM)
    #define UARTCOMMS_TX_HSIOM_PTR   ( (reg32 *) UARTCOMMS_tx_0__HSIOM)
    #define UARTCOMMS_TX_HSIOM_MASK  (UARTCOMMS_tx__0__HSIOM_MASK)
    #define UARTCOMMS_TX_HSIOM_POS   (UARTCOMMS_tx__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_UART_TX_PIN) */

#if (UARTCOMMS_UART_RTS_PIN)
    #define UARTCOMMS_RTS_HSIOM_REG  (*(reg32 *) UARTCOMMS_rts__0__HSIOM)
    #define UARTCOMMS_RTS_HSIOM_PTR  ( (reg32 *) UARTCOMMS_rts__0__HSIOM)
    #define UARTCOMMS_RTS_HSIOM_MASK (UARTCOMMS_rts__0__HSIOM_MASK)
    #define UARTCOMMS_RTS_HSIOM_POS  (UARTCOMMS_rts__0__HSIOM_SHIFT)
#endif /* (UARTCOMMS_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define UARTCOMMS_HSIOM_DEF_SEL      (0x00u)
#define UARTCOMMS_HSIOM_GPIO_SEL     (0x00u)
#define UARTCOMMS_HSIOM_UART_SEL     (0x09u)
#define UARTCOMMS_HSIOM_I2C_SEL      (0x0Eu)
#define UARTCOMMS_HSIOM_SPI_SEL      (0x0Fu)

#define UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define UARTCOMMS_RX_SCL_MOSI_PIN_INDEX       (0u)
#define UARTCOMMS_TX_SDA_MISO_PIN_INDEX       (1u)
#define UARTCOMMS_CTS_SCLK_PIN_INDEX       (2u)
#define UARTCOMMS_RTS_SS0_PIN_INDEX       (3u)
#define UARTCOMMS_SS1_PIN_INDEX                  (4u)
#define UARTCOMMS_SS2_PIN_INDEX                  (5u)
#define UARTCOMMS_SS3_PIN_INDEX                  (6u)

#define UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define UARTCOMMS_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << UARTCOMMS_RX_SCL_MOSI_PIN_INDEX)
#define UARTCOMMS_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << UARTCOMMS_TX_SDA_MISO_PIN_INDEX)
#define UARTCOMMS_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << UARTCOMMS_CTS_SCLK_PIN_INDEX)
#define UARTCOMMS_RTS_SS0_PIN_MASK     ((uint32) 0x01u << UARTCOMMS_RTS_SS0_PIN_INDEX)
#define UARTCOMMS_SS1_PIN_MASK                ((uint32) 0x01u << UARTCOMMS_SS1_PIN_INDEX)
#define UARTCOMMS_SS2_PIN_MASK                ((uint32) 0x01u << UARTCOMMS_SS2_PIN_INDEX)
#define UARTCOMMS_SS3_PIN_MASK                ((uint32) 0x01u << UARTCOMMS_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define UARTCOMMS_INTCFG_TYPE_MASK           (0x03u)
#define UARTCOMMS_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define UARTCOMMS_PIN_DM_ALG_HIZ  (0u)
#define UARTCOMMS_PIN_DM_DIG_HIZ  (1u)
#define UARTCOMMS_PIN_DM_OD_LO    (4u)
#define UARTCOMMS_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define UARTCOMMS_DM_MASK    (0x7u)
#define UARTCOMMS_DM_SIZE    (3)
#define UARTCOMMS_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) UARTCOMMS_DM_MASK << (UARTCOMMS_DM_SIZE * (pos)))) >> \
                                                              (UARTCOMMS_DM_SIZE * (pos)) )

#if (UARTCOMMS_TX_SDA_MISO_PIN)
    #define UARTCOMMS_CHECK_TX_SDA_MISO_PIN_USED \
                (UARTCOMMS_PIN_DM_ALG_HIZ != \
                    UARTCOMMS_GET_P4_PIN_DM(UARTCOMMS_uart_tx_i2c_sda_spi_miso_PC, \
                                                   UARTCOMMS_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (UARTCOMMS_TX_SDA_MISO_PIN) */

#if (UARTCOMMS_RTS_SS0_PIN)
    #define UARTCOMMS_CHECK_RTS_SS0_PIN_USED \
                (UARTCOMMS_PIN_DM_ALG_HIZ != \
                    UARTCOMMS_GET_P4_PIN_DM(UARTCOMMS_uart_rts_spi_ss0_PC, \
                                                   UARTCOMMS_uart_rts_spi_ss0_SHIFT))
#endif /* (UARTCOMMS_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define UARTCOMMS_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define UARTCOMMS_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define UARTCOMMS_SET_HSIOM_SEL(reg, mask, pos, sel) UARTCOMMS_SET_REGISTER_BITS(reg, mask, pos, sel)
#define UARTCOMMS_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        UARTCOMMS_SET_REGISTER_BITS(reg, mask, pos, intType)
#define UARTCOMMS_SET_INP_DIS(reg, mask, val) UARTCOMMS_SET_REGISTER_BIT(reg, mask, val)

/* UARTCOMMS_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  UARTCOMMS_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (UARTCOMMS_CY_SCBIP_V0)
#if (UARTCOMMS_I2C_PINS)
    #define UARTCOMMS_SET_I2C_SCL_DR(val) UARTCOMMS_scl_Write(val)

    #define UARTCOMMS_SET_I2C_SCL_HSIOM_SEL(sel) \
                          UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_SCL_HSIOM_REG,  \
                                                         UARTCOMMS_SCL_HSIOM_MASK, \
                                                         UARTCOMMS_SCL_HSIOM_POS,  \
                                                         (sel))
    #define UARTCOMMS_WAIT_SCL_SET_HIGH  (0u == UARTCOMMS_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN)
    #define UARTCOMMS_SET_I2C_SCL_DR(val) \
                            UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define UARTCOMMS_SET_I2C_SCL_HSIOM_SEL(sel) \
                    UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define UARTCOMMS_WAIT_SCL_SET_HIGH  (0u == UARTCOMMS_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (UARTCOMMS_RX_SCL_MOSI_PIN)
    #define UARTCOMMS_SET_I2C_SCL_DR(val) \
                            UARTCOMMS_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define UARTCOMMS_SET_I2C_SCL_HSIOM_SEL(sel) \
                            UARTCOMMS_SET_HSIOM_SEL(UARTCOMMS_RX_SCL_MOSI_HSIOM_REG,  \
                                                           UARTCOMMS_RX_SCL_MOSI_HSIOM_MASK, \
                                                           UARTCOMMS_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define UARTCOMMS_WAIT_SCL_SET_HIGH  (0u == UARTCOMMS_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define UARTCOMMS_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define UARTCOMMS_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define UARTCOMMS_WAIT_SCL_SET_HIGH  (0u)
#endif /* (UARTCOMMS_I2C_PINS) */

/* SCB I2C: sda signal */
#if (UARTCOMMS_I2C_PINS)
    #define UARTCOMMS_WAIT_SDA_SET_HIGH  (0u == UARTCOMMS_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (UARTCOMMS_TX_SDA_MISO_PIN)
    #define UARTCOMMS_WAIT_SDA_SET_HIGH  (0u == UARTCOMMS_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define UARTCOMMS_WAIT_SDA_SET_HIGH  (0u)
#endif /* (UARTCOMMS_MOSI_SCL_RX_PIN) */
#endif /* (UARTCOMMS_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define UARTCOMMS_REMOVE_MOSI_SCL_RX_WAKE_PIN    UARTCOMMS_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define UARTCOMMS_REMOVE_MOSI_SCL_RX_PIN         UARTCOMMS_REMOVE_RX_SCL_MOSI_PIN
#define UARTCOMMS_REMOVE_MISO_SDA_TX_PIN         UARTCOMMS_REMOVE_TX_SDA_MISO_PIN
#ifndef UARTCOMMS_REMOVE_SCLK_PIN
#define UARTCOMMS_REMOVE_SCLK_PIN                UARTCOMMS_REMOVE_CTS_SCLK_PIN
#endif /* UARTCOMMS_REMOVE_SCLK_PIN */
#ifndef UARTCOMMS_REMOVE_SS0_PIN
#define UARTCOMMS_REMOVE_SS0_PIN                 UARTCOMMS_REMOVE_RTS_SS0_PIN
#endif /* UARTCOMMS_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define UARTCOMMS_MOSI_SCL_RX_WAKE_PIN   UARTCOMMS_RX_WAKE_SCL_MOSI_PIN
#define UARTCOMMS_MOSI_SCL_RX_PIN        UARTCOMMS_RX_SCL_MOSI_PIN
#define UARTCOMMS_MISO_SDA_TX_PIN        UARTCOMMS_TX_SDA_MISO_PIN
#ifndef UARTCOMMS_SCLK_PIN
#define UARTCOMMS_SCLK_PIN               UARTCOMMS_CTS_SCLK_PIN
#endif /* UARTCOMMS_SCLK_PIN */
#ifndef UARTCOMMS_SS0_PIN
#define UARTCOMMS_SS0_PIN                UARTCOMMS_RTS_SS0_PIN
#endif /* UARTCOMMS_SS0_PIN */

#if (UARTCOMMS_MOSI_SCL_RX_WAKE_PIN)
    #define UARTCOMMS_MOSI_SCL_RX_WAKE_HSIOM_REG     UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UARTCOMMS_MOSI_SCL_RX_WAKE_HSIOM_PTR     UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UARTCOMMS_MOSI_SCL_RX_WAKE_HSIOM_MASK    UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UARTCOMMS_MOSI_SCL_RX_WAKE_HSIOM_POS     UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UARTCOMMS_MOSI_SCL_RX_WAKE_INTCFG_REG    UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UARTCOMMS_MOSI_SCL_RX_WAKE_INTCFG_PTR    UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UARTCOMMS_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UARTCOMMS_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  UARTCOMMS_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (UARTCOMMS_RX_WAKE_SCL_MOSI_PIN) */

#if (UARTCOMMS_MOSI_SCL_RX_PIN)
    #define UARTCOMMS_MOSI_SCL_RX_HSIOM_REG      UARTCOMMS_RX_SCL_MOSI_HSIOM_REG
    #define UARTCOMMS_MOSI_SCL_RX_HSIOM_PTR      UARTCOMMS_RX_SCL_MOSI_HSIOM_PTR
    #define UARTCOMMS_MOSI_SCL_RX_HSIOM_MASK     UARTCOMMS_RX_SCL_MOSI_HSIOM_MASK
    #define UARTCOMMS_MOSI_SCL_RX_HSIOM_POS      UARTCOMMS_RX_SCL_MOSI_HSIOM_POS
#endif /* (UARTCOMMS_MOSI_SCL_RX_PIN) */

#if (UARTCOMMS_MISO_SDA_TX_PIN)
    #define UARTCOMMS_MISO_SDA_TX_HSIOM_REG      UARTCOMMS_TX_SDA_MISO_HSIOM_REG
    #define UARTCOMMS_MISO_SDA_TX_HSIOM_PTR      UARTCOMMS_TX_SDA_MISO_HSIOM_REG
    #define UARTCOMMS_MISO_SDA_TX_HSIOM_MASK     UARTCOMMS_TX_SDA_MISO_HSIOM_REG
    #define UARTCOMMS_MISO_SDA_TX_HSIOM_POS      UARTCOMMS_TX_SDA_MISO_HSIOM_REG
#endif /* (UARTCOMMS_MISO_SDA_TX_PIN_PIN) */

#if (UARTCOMMS_SCLK_PIN)
    #ifndef UARTCOMMS_SCLK_HSIOM_REG
    #define UARTCOMMS_SCLK_HSIOM_REG     UARTCOMMS_CTS_SCLK_HSIOM_REG
    #define UARTCOMMS_SCLK_HSIOM_PTR     UARTCOMMS_CTS_SCLK_HSIOM_PTR
    #define UARTCOMMS_SCLK_HSIOM_MASK    UARTCOMMS_CTS_SCLK_HSIOM_MASK
    #define UARTCOMMS_SCLK_HSIOM_POS     UARTCOMMS_CTS_SCLK_HSIOM_POS
    #endif /* UARTCOMMS_SCLK_HSIOM_REG */
#endif /* (UARTCOMMS_SCLK_PIN) */

#if (UARTCOMMS_SS0_PIN)
    #ifndef UARTCOMMS_SS0_HSIOM_REG
    #define UARTCOMMS_SS0_HSIOM_REG      UARTCOMMS_RTS_SS0_HSIOM_REG
    #define UARTCOMMS_SS0_HSIOM_PTR      UARTCOMMS_RTS_SS0_HSIOM_PTR
    #define UARTCOMMS_SS0_HSIOM_MASK     UARTCOMMS_RTS_SS0_HSIOM_MASK
    #define UARTCOMMS_SS0_HSIOM_POS      UARTCOMMS_RTS_SS0_HSIOM_POS
    #endif /* UARTCOMMS_SS0_HSIOM_REG */
#endif /* (UARTCOMMS_SS0_PIN) */

#define UARTCOMMS_MOSI_SCL_RX_WAKE_PIN_INDEX UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_INDEX
#define UARTCOMMS_MOSI_SCL_RX_PIN_INDEX      UARTCOMMS_RX_SCL_MOSI_PIN_INDEX
#define UARTCOMMS_MISO_SDA_TX_PIN_INDEX      UARTCOMMS_TX_SDA_MISO_PIN_INDEX
#ifndef UARTCOMMS_SCLK_PIN_INDEX
#define UARTCOMMS_SCLK_PIN_INDEX             UARTCOMMS_CTS_SCLK_PIN_INDEX
#endif /* UARTCOMMS_SCLK_PIN_INDEX */
#ifndef UARTCOMMS_SS0_PIN_INDEX
#define UARTCOMMS_SS0_PIN_INDEX              UARTCOMMS_RTS_SS0_PIN_INDEX
#endif /* UARTCOMMS_SS0_PIN_INDEX */

#define UARTCOMMS_MOSI_SCL_RX_WAKE_PIN_MASK UARTCOMMS_RX_WAKE_SCL_MOSI_PIN_MASK
#define UARTCOMMS_MOSI_SCL_RX_PIN_MASK      UARTCOMMS_RX_SCL_MOSI_PIN_MASK
#define UARTCOMMS_MISO_SDA_TX_PIN_MASK      UARTCOMMS_TX_SDA_MISO_PIN_MASK
#ifndef UARTCOMMS_SCLK_PIN_MASK
#define UARTCOMMS_SCLK_PIN_MASK             UARTCOMMS_CTS_SCLK_PIN_MASK
#endif /* UARTCOMMS_SCLK_PIN_MASK */
#ifndef UARTCOMMS_SS0_PIN_MASK
#define UARTCOMMS_SS0_PIN_MASK              UARTCOMMS_RTS_SS0_PIN_MASK
#endif /* UARTCOMMS_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_UARTCOMMS_H) */


/* [] END OF FILE */
