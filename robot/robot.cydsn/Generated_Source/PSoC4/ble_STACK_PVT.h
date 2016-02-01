/***************************************************************************//**
* \file CYBLE_STACK_PVT.h
* \version 2.30
*
* \brief
*  Contains the function prototypes and constants for the HAL section
*  of the BLE component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_BLE_CYBLE_STACK_PVT_H)
#define CY_BLE_CYBLE_STACK_PVT_H

#include "BLE_eventHandler.h"

/***************************************
*     Data Struct Definitions
***************************************/
typedef struct
{
    uint32  timerPeriod; /**< In ms */
    uint8   timerMode;   /**< One shot, continuous. */
} CyBLE_timerConfig;


/***************************************
*   Function Prototypes
***************************************/

void CyBLE_Bless_LlRegRead (const reg32 *blessAddr, uint16 *regValue);
void CyBLE_Bless_LlRegWrite (reg32 *blessAddr, const uint16 regValue);
void CyBLE_Bless_RfRegRead (const reg32 *blessAddr, uint16 *regValue);
void CyBLE_Bless_RfRegWrite (reg32 *blessAddr, const uint16 regValue);
void BLE_uart_Start (void);
void BLE_uart_Stop (void);
void BLE_uart_Transmit (const uint8 *dataBuf, uint8 length);
void CyBLE_BlessDeviceConfig(void);


/***************************************
*     Stack manager prototypes
***************************************/

/* Extern definitions for BLE Stack ISR handler */
extern void CyBle_BleSSInterruptHandler(void);

/* These APIs need to be renamed */

/* To be used only for HCI_MODE and in Debug mode
* where the logger serial port is enabled
*/
extern void PSOC4A_handle_transport_uart_tx_complete (void);

/* To be used only for HCI_MODE */
extern void PSOC4A_handle_transport_rx_byte(uint8 byte);


/* Handle timer interrupt */
extern void pf_timer_handle_tick (void);

#define CyBLE_pf_handle_uart_rx_data        PSOC4A_handle_transport_rx_byte
#define CyBLE_pf_handle_uart_tx_complt      PSOC4A_handle_transport_uart_tx_complete
#define CyBLE_pf_timer_tick_hdlr            pf_timer_handle_tick
#define CyBLE_pf_bless_event_hdlr           CyBle_BleSSInterruptHandler


/***************************************
*     Macros
***************************************/
#define CyBLE_INTR_TX_SUCCESS       0x00u
#define CyBLE_INTR_TX_DONE          0x00u
#define CyBLE_INTR_TX_OVERFLOW      0x01u

#define CyBLE_INTR_RX_SUCCESS       0x00u
#define CyBLE_INTR_RX_NOT_EMPTY     0x00u
#define CyBLE_INTR_RX_OVERFLOW      0x01u
#define CyBLE_INTR_RX_FRAME_ERROR   0x02u
#define CyBLE_INTR_RX_PARITY_ERROR  0x04u


#endif /* CY_BLE_CYBLE_STACK_PVT_H  */

/* [] END OF FILE */
