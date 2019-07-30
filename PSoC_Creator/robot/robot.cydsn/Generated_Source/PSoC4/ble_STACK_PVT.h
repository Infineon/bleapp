/***************************************************************************//**
* \file CYBLE_STACK_PVT.h
* \version 3.61
*
* \brief
*  Contains the function prototypes and constants for the HAL section
*  of the BLE component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2019, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/** \cond IGNORE */

#if !defined(CY_BLE_CYBLE_STACK_PVT_H)
#define CY_BLE_CYBLE_STACK_PVT_H

#include "BLE_eventHandler.h"

/***************************************
*     Data Struct Definitions
***************************************/
typedef struct
{
    uint32  timerPeriod; /* In ms */
    uint8   timerMode;   /* One shot, continuous. */
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

/* Mapping functions for stack size optimization */
#if(CYBLE_MODE_PROFILE)
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_tbx_local_pubkey_generate_complete(void);
    void CyBle_Hal_smp_sc_cmac_complete(void);
    void CyBle_Hal_EccPointMult(void);
#if(CYBLE_SECURE_CONN_FEATURE_ENABLED)
    CYBLE_API_RESULT_T CyBle_Hal_pairing_local_public_key_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_remote_key_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_check_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_keypress_notification_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_rand_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_confirm_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_lr_confirming_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_lr_confirming_handler(void *param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_tbx_dhkey_generate_complete(void* param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_local_P256_public_key(uint8 param);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_DHkey(void  * param1, void  * param2);
    CYBLE_API_RESULT_T CyBle_Hal_se_smp_sc_user_passkey_handler(void *param1, void *param2);
    CYBLE_API_RESULT_T CyBle_Hal_mapping_validate_p256_pub_key_pair(void *param1);
#else
    CYBLE_API_RESULT_T CyBle_Hal_pairing_local_public_key_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_remote_key_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_check_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_keypress_notification_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_rand_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_confirm_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_lr_confirming_handler(void *param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_tbx_dhkey_generate_complete(void* param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_local_P256_public_key(uint8 param CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_DHkey(void * param1 CYBLE_UNUSED_ATTR,
                                                               void * param2 CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_se_smp_sc_user_passkey_handler(void *param1 CYBLE_UNUSED_ATTR, 
                                                                void *param2 CYBLE_UNUSED_ATTR);
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_validate_p256_pub_key_pair (void *param1 CYBLE_UNUSED_ATTR);                                                                
                                                                
#endif /* (CYBLE_SECURE_CONN_FEATURE_ENABLED) */
#endif  /* CYBLE_MODE_PROFILE */

#if(CYBLE_SECURE_CONN_FEATURE_ENABLED)
    uint16 BLE_CMP_FTR_API_lec_hci_handle_read_local_P256_public_key_command(void *param);
    uint16 BLE_CMP_FTR_API_lec_hci_handle_generate_DHkey_command(void *param);
#else
    uint16 BLE_CMP_FTR_API_lec_hci_handle_read_local_P256_public_key_command(void *param CYBLE_UNUSED_ATTR);
    uint16 BLE_CMP_FTR_API_lec_hci_handle_generate_DHkey_command(void *param CYBLE_UNUSED_ATTR);
#endif /* CYBLE_SECURE_CONN_FEATURE_ENABLED*/
    

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


/* Align buffer size value to 4 */
#define CYBLE_STACK_ALIGN_TO_4(x)       ((((x) & 3u) == 0u) ?    \
                                        (x) :                    \
                                        (((x) - ((x) & 3u)) + 4u))

#endif /* CY_BLE_CYBLE_STACK_PVT_H  */

/** \endcond */

/* [] END OF FILE */
