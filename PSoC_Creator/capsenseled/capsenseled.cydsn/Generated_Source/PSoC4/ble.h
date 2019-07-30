/***************************************************************************//**
* \file CYBLE.h
* \version 3.61
* 
* \brief
*  Contains the function prototypes and constants available to the BLE component.
* 
********************************************************************************
* \copyright
* Copyright 2014-2019, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_BLE_CYBLE_H)
#define CY_BLE_CYBLE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "CyFlash.h"


/***************************************
* Stack includes
***************************************/

#include "ble_Stack.h"
#include "ble_StackHostMain.h"
#include "ble_StackGap.h"
#include "ble_StackGattServer.h"
#include "ble_StackGattClient.h"
#include "ble_StackGattDb.h"
#include "ble_StackL2cap.h"


/***************************************
* Other Conditional Compilation Parameters
***************************************/
    
#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CYBLE_FLASH_ROW_ALIGNED __attribute__ ((aligned(CY_FLASH_SIZEOF_ROW)))
    #define CYBLE_CYPACKED 
    #define CYBLE_CYPACKED_ATTR __attribute__ ((packed))
    #define CYBLE_CYALIGNED_BEGIN
    #define CYBLE_CYALIGNED_END __attribute__ ((aligned))
    #define CYBLE_UNUSED_ATTR __attribute__ ((unused))
#elif defined(__ICCARM__)
    #define CYBLE_CYPACKED __packed
    #define CYBLE_CYPACKED_ATTR 
    #define CYBLE_UNUSED_ATTR
    #define CYBLE_CYALIGNED_BEGIN _Pragma("data_alignment=4")
    #define CYBLE_CYALIGNED_END
    /* For IAR data alignment is handled directly prior structure declaration */
#else
    #error Unsupported toolchain
#endif

#define CYBLE_MODE                                  (0u)
#define CYBLE_PROFILE                               (0u)
#define CYBLE_HCI                                   (1u)
#define CYBLE_MODE_PROFILE                          (CYBLE_MODE == CYBLE_PROFILE)
#define CYBLE_MODE_HCI                              (CYBLE_MODE == CYBLE_HCI)

#define CYBLE_HCI_TYPE                              (0u)
#define CYBLE_HCI_OVER_UART                         (0u)
#define CYBLE_HCI_OVER_SW                           (1u)

#define CYBLE_STACK_MODE                            (3u)
#define CYBLE_STACK_DEBUG                           (2u)
#define CYBLE_STACK_RELEASE                         (3u)
#define CYBLE_STACK_MODE_DEBUG                      (CYBLE_STACK_MODE == CYBLE_STACK_DEBUG)
#define CYBLE_STACK_MODE_RELEASE                    (CYBLE_STACK_MODE == CYBLE_STACK_RELEASE)
    
#define CYBLE_M0S8BLESS_VERSION                     (CYIPBLOCK_m0s8bless_VERSION)
#define CYBLE_M0S8BLESS_VERSION_2                   (CYBLE_M0S8BLESS_VERSION > 1u)
#define CYBLE_M0S8BLESS_VERSION_3                   (CYBLE_M0S8BLESS_VERSION > 2u)
    
#define CYBLE_EXT_PA_ENABLED                        (0x00u)
#define CYBLE_GAP_SECURITY_LEVEL_SECURE_CONN        (3u)


#if(CYBLE_MODE_PROFILE)
    #define CYBLE_AUTO_POPULATE_WHITELIST           (0x01u)
    #if(CYBLE_M0S8BLESS_VERSION_2)
        #define CYBLE_MAX_RESOLVABLE_DEVICES        (0x08u)
        #define CYBLE_ENABLE_LL_PRIVACY             (0x00u)
    #else
        #define CYBLE_MAX_RESOLVABLE_DEVICES        (0u)
        #define CYBLE_ENABLE_LL_PRIVACY             (0u)
    #endif /* CYBLE_M0S8BLESS_VERSION_2 */
    #define CYBLE_GAP_SECURITY_LEVEL                (0x00u)
#else
    #if(CYBLE_M0S8BLESS_VERSION_2)
        #define CYBLE_MAX_RESOLVABLE_DEVICES        (CYBLE_DEFAULT_RPA_LIST_SZ)    
        #define CYBLE_ENABLE_LL_PRIVACY             (1u)
    #else
        #define CYBLE_MAX_RESOLVABLE_DEVICES        (0u)
        #define CYBLE_ENABLE_LL_PRIVACY             (0u)
    #endif /* CYBLE_M0S8BLESS_VERSION_2 */
    #define CYBLE_GAP_SECURITY_LEVEL                (0x0u)
#endif /* CYBLE_MODE_PROFILE */

#define CYBLE_SHARING_NONE                          (0u)
#define CYBLE_SHARING_EXPORT                        (1u)
#define CYBLE_SHARING_IMPORT                        (2u)
#define CYBLE_SHARING_MODE                          (0u)  
#define CYBLE_SHARING_MODE_EXPORT                   (CYBLE_SHARING_MODE == CYBLE_SHARING_EXPORT)  
#define CYBLE_SHARING_MODE_IMPORT                   (CYBLE_SHARING_MODE == CYBLE_SHARING_IMPORT)  

#define CYBLE_FLASH_SIZE                            ((CYDEV_FLASH_SIZE >> 17u) & 0xff)  /* 1 - 128k, 2 - 256k */
#define CYBLE_PSVP_DEVICE                           (0u)

/* Align buffer size value to 4 */
#define CYBLE_ALIGN_TO_4(x)                         ((((x) & 3u) == 0u) ? (x) : (((x) - ((x) & 3u)) + 4u))
    
#define CYBLE_GAP_ROLE                              (0x01u)
#define CYBLE_GAP_HCI                               (0x00u)
#define CYBLE_GAP_PERIPHERAL                        (0x01u)
#define CYBLE_GAP_CENTRAL                           (0x02u)
#define CYBLE_GAP_BOTH                              (CYBLE_GAP_CENTRAL | CYBLE_GAP_PERIPHERAL)
#define CYBLE_GAP_BROADCASTER                       (0x04u)
#define CYBLE_GAP_OBSERVER                          (0x08u)

#define CYBLE_GAP_ROLE_PERIPHERAL                   (0u != (CYBLE_GAP_ROLE & CYBLE_GAP_PERIPHERAL))
#define CYBLE_GAP_ROLE_CENTRAL                      (0u != (CYBLE_GAP_ROLE & CYBLE_GAP_CENTRAL))
#define CYBLE_GAP_ROLE_OBSERVER                     (0u != (CYBLE_GAP_ROLE & CYBLE_GAP_OBSERVER))
#define CYBLE_GAP_ROLE_BROADCASTER                  (0u != (CYBLE_GAP_ROLE & CYBLE_GAP_BROADCASTER))

#if(CYBLE_MODE_PROFILE)
    
#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
    #define CYBLE_FAST_ADV_INT_MIN                  (0x0020u)
    #define CYBLE_FAST_ADV_INT_MAX                  (0x0030u)
    #define CYBLE_FAST_ADV_TIMEOUT                  (0x0000u)
    #define CYBLE_SLOW_ADV_ENABLED                  (0x00u)
    #define CYBLE_SLOW_ADV_INT_MIN                  (0x0640u)
    #define CYBLE_SLOW_ADV_INT_MAX                  (0x4000u)
    #define CYBLE_SLOW_ADV_TIMEOUT                  (0x0096u)
    #define CYBLE_GAPP_CONNECTION_INTERVAL_MIN      (0x0006u)
    #define CYBLE_GAPP_CONNECTION_INTERVAL_MAX      (0x0028u)
    #define CYBLE_GAPP_CONNECTION_SLAVE_LATENCY     (0x0000u)
    #define CYBLE_GAPP_CONNECTION_TIME_OUT          (0x03E8u)
#endif /* CYBLE_GAP_ROLE_PERIPHERAL */

#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)
    #define CYBLE_FAST_SCAN_INTERVAL                (0x00u)
    #define CYBLE_FAST_SCAN_WINDOW                  (0x00u)
    #define CYBLE_FAST_SCAN_TIMEOUT                 (0x00u)
    #define CYBLE_SLOW_SCAN_ENABLED                 (0x00u)
    #define CYBLE_SLOW_SCAN_INTERVAL                (0x00u)
    #define CYBLE_SLOW_SCAN_WINDOW                  (0x00u)
    #define CYBLE_SLOW_SCAN_TIMEOUT                 (0x00u)
    #define CYBLE_GAPC_CONNECTION_INTERVAL_MIN      (0x0006u)
    #define CYBLE_GAPC_CONNECTION_INTERVAL_MAX      (0x0028u)
    #define CYBLE_GAPC_CONNECTION_SLAVE_LATENCY     (0x0000u)
    #define CYBLE_GAPC_CONNECTION_TIME_OUT          (0x03E8u)
#endif /* CYBLE_GAP_ROLE_CENTRAL */

#define SILICON_GENERATED_DEVICE_ADDRESS            (0x01u)

/*  Selected IO capability  
    CYBLE_GAP_IOCAP_DISPLAY_ONLY
    CYBLE_GAP_IOCAP_DISPLAY_YESNO
    CYBLE_GAP_IOCAP_KEYBOARD_ONLY
    CYBLE_GAP_IOCAP_NOINPUT_NOOUTPUT
    CYBLE_GAP_IOCAP_KEYBOARD_DISPLAY
*/
#define CYBLE_IO_CAPABILITY                         (CYBLE_GAP_IOCAP_DISPLAY_ONLY)
#define CYBLE_PAIRING_METHOD                        (0x00u)
#define CYBLE_BONDING_REQUIREMENT                   (0x00u)

/* Tx Power Level */
#define CYBLE_TX_POWER_LEVEL_ADV                    (CYBLE_LL_PWR_LVL_0_DBM)
#define CYBLE_TX_POWER_LEVEL_CONN                   (CYBLE_LL_PWR_LVL_0_DBM)

#define CYBLE_ADV_PKT_INDEX_FLAGS   (0x00u)
#define CYBLE_ADV_PKT_INDEX_LOCAL_NAME   (0x03u)
#define CYBLE_ADV_PKT_INDEX_SERVICE_UUID_128   (0x0Bu)




/* Strict pairing option */
#define CYBLE_STRICT_PAIRING                        (0x00u)
#define CYBLE_STRICT_PAIRING_ON                     (1)
#define CYBLE_STRICT_PAIRING_OFF                    (0)
#define CYBLE_STRICT_PAIRING_ENABLED                (CYBLE_STRICT_PAIRING == CYBLE_STRICT_PAIRING_ON)

/* Security options from the customizer */
#define CYBLE_SECURITY_MODE                         ((0x00u == 0u) ? CYBLE_GAP_SEC_MODE_1 : CYBLE_GAP_SEC_MODE_2)
#define CYBLE_SECURITY_LEVEL                        (0x00u)
#define CYBLE_SECURITY_ENC_KEY_SIZE                 (0x10u)

#if (CYBLE_STRICT_PAIRING_ENABLED)
    #define CYBLE_STRICT_PAIRING_REQ_VALUE  \
        ((CYBLE_SECURITY_MODE == CYBLE_GAP_SEC_MODE_1) ? ((CYBLE_SECURITY_LEVEL == CYBLE_GAP_SEC_LEVEL_1) ? \
        (CYBLE_GAP_NO_SECURITY_REQUIREMENTS) : ((CYBLE_SECURITY_LEVEL == CYBLE_GAP_SEC_LEVEL_2) ? \
        (CYBLE_GAP_SEC_UNAUTH_PAIRING) : ((CYBLE_SECURITY_LEVEL == CYBLE_GAP_SEC_LEVEL_3) ? \
        (CYBLE_GAP_SEC_AUTH_PAIRING) : (CYBLE_GAP_SEC_SC_PAIRING_WITH_NO_MITM | CYBLE_GAP_SEC_SC_PAIRING_WITH_MITM)))) : \
        (CYBLE_GAP_NO_SECURITY_REQUIREMENTS))
#endif /* (CYBLE_STRICT_PAIRING_ENABLED) */

/* Stack buffers count */
#define CYBLE_GATT_MTU_BUFF_COUNT            (CYBLE_GATT_MIN_NO_OF_ATT_MTU_BUFF)
/* Additional buffers provided from customizer with default value equal to 1 */
#define CYBLE_GATT_MAX_ATTR_BUFF_COUNT       ((1 > 0u) ? (1 - 1u) : 0u)

/* GATT MTU Size */
#define CYBLE_GATT_MTU                      (0x0017u)
#define CYBLE_GATT_MTU_PLUS_L2CAP_MEM_EXT   (CYBLE_ALIGN_TO_4(CYBLE_GATT_MTU + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ))

/* GATT Maximum attribute length */
#define CYBLE_GATT_MAX_ATTR_LEN             ((0x000Fu == 0u) ? (1u) : (0x000Fu))
#define CYBLE_GATT_MAX_ATTR_LEN_PLUS_L2CAP_MEM_EXT \
                                    (CYBLE_ALIGN_TO_4(CYBLE_GATT_MAX_ATTR_LEN + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ))

/* Header length for prepare write request */
#define CYBLE_GATT_PREPARE_WRITE_HEADER_LEN (5u)
/* Header length for write request */
#define CYBLE_GATT_WRITE_HEADER_LEN         (3u)

/* Number of characteristics supporting reliable write property */
#define CYBLE_GATT_RELIABLE_CHAR_COUNT      (0x0000u)
/* The total length of characteristics with reliable write property */
#define CYBLE_GATT_RELIABLE_CHAR_LENGTH      (0x0000u)

#define CYBLE_GATT_PREPARE_LENGTH           ((CYBLE_GATT_RELIABLE_CHAR_LENGTH > CYBLE_GATT_MAX_ATTR_LEN) ? \
                                             CYBLE_GATT_RELIABLE_CHAR_LENGTH : CYBLE_GATT_MAX_ATTR_LEN)

/* Number of buffers required for prepare write request based on assumption that negotiated MTU
*  size is equal to the CYBLE_GATT_DEFAULT_MTU and all characteristics supporting reliable write
*  property must be written, in order, in a single operation. 
*  Buffer count is 0 when maximum attribute size is less then minimum MTU - 3.
*/
#define CYBLE_GATT_MAX_PREPARE_BUFF_COUNT   \
        (((CYBLE_GATT_MAX_ATTR_LEN <= (CYBLE_GATT_DEFAULT_MTU - CYBLE_GATT_WRITE_HEADER_LEN)) && \
            (CYBLE_GATT_RELIABLE_CHAR_COUNT == 0)) ? 0u : \
        ((CYBLE_GATT_PREPARE_LENGTH / (CYBLE_GATT_DEFAULT_MTU - CYBLE_GATT_PREPARE_WRITE_HEADER_LEN)) + \
        (((CYBLE_GATT_PREPARE_LENGTH % (CYBLE_GATT_DEFAULT_MTU - CYBLE_GATT_PREPARE_WRITE_HEADER_LEN)) > 0u) ?\
            1u : 0u)))

#define CYBLE_GATT_PREPARE_LENGTH_ALIGN     ((CYBLE_GATT_MAX_PREPARE_BUFF_COUNT == 0u) ? 0u : \
                                                CYBLE_ALIGN_TO_4(CYBLE_GATT_PREPARE_LENGTH))
            
/* Parameter to enable application to provide dynamically allocated buffer for prepare write request.  */            
#define CYBLE_GATT_ENABLE_EXTERNAL_PREP_WRITE_BUFF  (0u)
            
/* Buffer length for the data received during prepare write requests 
   For dynamic memory allocation by application level, set EnableExternalPrepWriteBuff parameter
   in the Expression view of the Advanced tab to the true.
*/            
#define CYBLE_GATT_PREPARE_WRITE_BUFF_LEN       ((CYBLE_GATT_ENABLE_EXTERNAL_PREP_WRITE_BUFF != 0u) ? 0u : \
                                (CYBLE_GATT_PREPARE_LENGTH_ALIGN + \
                                (CYBLE_GATT_MAX_PREPARE_BUFF_COUNT * sizeof(CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T))))

#define CYBLE_L2CAP_ENABLE                              (1u)

#if(CYBLE_L2CAP_ENABLE != 0u)
    /* L2CAP MTU Size */
    #define CYBLE_L2CAP_MTU                             (23u)
    /* L2CAP PMS Size */
    #define CYBLE_L2CAP_MPS                             (23u)
    #define CYBLE_L2CAP_MTU_MPS                         (CYBLE_L2CAP_MTU / CYBLE_L2CAP_MPS)
    /* Number of L2CAP Logical channels */
    #define CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT           (1u) 
    /* Number of L2CAP PSMs */
    #define CYBLE_L2CAP_PSM_COUNT                       (1u)
#else
    /* L2CAP MTU Size */
    #define CYBLE_L2CAP_MTU                             (0u)
    /* L2CAP PMS Size */
    #define CYBLE_L2CAP_MPS                             (0u)
    #define CYBLE_L2CAP_MTU_MPS                         (0u)
    /* Number of L2CAP Logical channels */
    #define CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT           (0u) 
    /* Number of L2CAP PSMs */
    #define CYBLE_L2CAP_PSM_COUNT                       (0u)
#endif  /* CYBLE_L2CAP_ENABLE != 0u */

/* L2CAP RAM buffer sizes */
#define CYBLE_L2CAP_MTU_PLUS_L2CAP_MEM_EXT  (CYBLE_ALIGN_TO_4(CYBLE_L2CAP_MTU + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ))
#define CYBLE_L2CAP_MPS_PLUS_L2CAP_MEM_EXT  (CYBLE_ALIGN_TO_4(CYBLE_L2CAP_MPS + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ))
#define CYBLE_L2CAP_PSM_PLUS_L2CAP_MEM_EXT  (CYBLE_ALIGN_TO_4((CYBLE_L2CAP_PSM_SIZE + CYBLE_MEM_EXT_SZ) *\
                                                CYBLE_L2CAP_PSM_COUNT))
#define CYBLE_L2CAP_CBFC_PLUS_L2CAP_MEM_EXT (CYBLE_ALIGN_TO_4((CYBLE_L2CAP_CBFC_CHANNEL_SIZE + CYBLE_MEM_EXT_SZ) *\
                                                CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT))

#endif /* CYBLE_MODE_PROFILE */

/* LL max data length */
#define CYBLE_LL_MAX_SUPPORTED_TX_PAYLOAD_SIZE          (251u)
#define CYBLE_LL_MAX_SUPPORTED_RX_PAYLOAD_SIZE          (251u)
#define CYBLE_LL_MIN_SUPPORTED_TX_PAYLOAD_SIZE          (27u)
#define CYBLE_LL_MIN_SUPPORTED_RX_PAYLOAD_SIZE          (27u)
#define CYBLE_LL_MAX_TX_TIME                            (0x0848u)

#if(CYBLE_MODE_PROFILE)
    #if(CYBLE_M0S8BLESS_VERSION_2)
        #define CYBLE_LL_MAX_TX_PAYLOAD_SIZE            (0x1Bu)
        #define CYBLE_LL_MAX_RX_PAYLOAD_SIZE            (0x1Bu)
    #else   /* For 4.1 silicon use minimum payload size */
        #define CYBLE_LL_MAX_TX_PAYLOAD_SIZE            (CYBLE_LL_MIN_SUPPORTED_TX_PAYLOAD_SIZE)
        #define CYBLE_LL_MAX_RX_PAYLOAD_SIZE            (CYBLE_LL_MIN_SUPPORTED_RX_PAYLOAD_SIZE)
    #endif  /* CYBLE_M0S8BLESS_VERSION_2 */
#else   /* Use maximum payload size for HCI mode */
    #if(CYBLE_M0S8BLESS_VERSION_2)
        #define CYBLE_LL_MAX_TX_PAYLOAD_SIZE            (CYBLE_LL_MAX_SUPPORTED_TX_PAYLOAD_SIZE)
        #define CYBLE_LL_MAX_RX_PAYLOAD_SIZE            (CYBLE_LL_MAX_SUPPORTED_RX_PAYLOAD_SIZE)
    #else   /* For 4.1 silicon use minimum payload size */
        #define CYBLE_LL_MAX_TX_PAYLOAD_SIZE            (CYBLE_LL_MIN_SUPPORTED_TX_PAYLOAD_SIZE)
        #define CYBLE_LL_MAX_RX_PAYLOAD_SIZE            (CYBLE_LL_MIN_SUPPORTED_RX_PAYLOAD_SIZE)
    #endif  /* CYBLE_M0S8BLESS_VERSION_2 */
#endif /* CYBLE_MODE_PROFILE */

#define CYBLE_LL_MAX_TX_PAYLOAD_BUFFER_SZ               CYBLE_ALIGN_TO_4(CYBLE_LL_MAX_TX_PAYLOAD_SIZE)
#define CYBLE_LL_MAX_RX_PAYLOAD_BUFFER_SZ               CYBLE_ALIGN_TO_4(CYBLE_LL_MAX_RX_PAYLOAD_SIZE)
#if((CYBLE_LL_MAX_TX_PAYLOAD_SIZE > CYBLE_LL_MIN_SUPPORTED_TX_PAYLOAD_SIZE) ||\
    (CYBLE_LL_MAX_RX_PAYLOAD_SIZE > CYBLE_LL_MIN_SUPPORTED_RX_PAYLOAD_SIZE))
    #define CYBLE_DLE_FEATURE                           (CYBLE_DLE_FEATURE_MASK)
    #define CYBLE_LL_DLE_HEAP_SZ                        (CYBLE_LL_DLE_HEAP_REQ)
#else
    #define CYBLE_DLE_FEATURE                           (0u)
    #define CYBLE_LL_DLE_HEAP_SZ                        (0u)
#endif /* DLE enabled */

#if(CYBLE_ENABLE_LL_PRIVACY > 0u)
    #define CYBLE_LL_PRIVACY_FEATURE                    (CYBLE_LL_PRIVACY_FEATURE_MASK)
    #define CYBLE_LL_PRIVACY_HEAP_SZ                    (CYBLE_LL_PRIVACY_HEAP_REQ)
#else
    #define CYBLE_LL_PRIVACY_FEATURE                    (0u)
    #define CYBLE_LL_PRIVACY_HEAP_SZ                    (0u)
#endif /* CYBLE_MAX_RESOLVABLE_DEVICES > 0u */

#if(CYBLE_GAP_SECURITY_LEVEL == CYBLE_GAP_SECURITY_LEVEL_SECURE_CONN)
    #define CYBLE_SECURE_CONN_FEATURE                   (CYBLE_SECURE_CONN_FEATURE_MASK)
    #define CYBLE_RAM_SECURE_CONNECTIONS_SZ             (CYBLE_RAM_SIZE_SECURE_CONNECTIONS)
#else
    #define CYBLE_SECURE_CONN_FEATURE                   (0u)
    #define CYBLE_RAM_SECURE_CONNECTIONS_SZ             (0u)
#endif /* CYBLE_GAP_SECURITY_LEVEL == CYBLE_GAP_SECURITY_LEVEL_SECURE_CONN */

#define CYBLE_DLE_FEATURE_ENABLED                       (CYBLE_DLE_FEATURE != 0u)
#define CYBLE_LL_PRIVACY_FEATURE_ENABLED                (CYBLE_LL_PRIVACY_FEATURE != 0u)
#define CYBLE_SECURE_CONN_FEATURE_ENABLED               (CYBLE_SECURE_CONN_FEATURE != 0u)

#define CYBLE_LL_ACL_TX_HEAP_SZ        (CYBLE_LL_DEFAULT_NUM_ACL_TX_PACKETS *  \
                                        (                                      \
                                         CYBLE_LL_MAX_TX_PAYLOAD_BUFFER_SZ +   \
                                         CYBLE_LL_ACL_DATA_PACKET_OVERHEAD_SZ +\
                                         CYBLE_MEM_EXT_SZ                      \
                                        ))

#define CYBLE_LL_ACL_RX_HEAP_SZ        (CYBLE_LL_DEFAULT_NUM_ACL_RX_PACKETS *  \
                                        (                                      \
                                         CYBLE_LL_MAX_RX_PAYLOAD_BUFFER_SZ +   \
                                         CYBLE_LL_ACL_DATA_PACKET_OVERHEAD_SZ +\
                                         CYBLE_MEM_EXT_SZ                      \
                                        ))


#define CYBLE_LL_CONTROLLER_HEAP_REQ_COMP    ((CYBLE_LL_PRIVACY_HEAP_SZ * CYBLE_MAX_RESOLVABLE_DEVICES) + \
                                                CYBLE_LL_DLE_HEAP_SZ +    \
                                                CYBLE_LL_ACL_TX_HEAP_SZ + \
                                                CYBLE_LL_ACL_RX_HEAP_SZ + \
                                                CYBLE_RAM_SECURE_CONNECTIONS_SZ)


/* RAM memory size required for stack */
#if(CYBLE_MODE_PROFILE)
    #define CYBLE_STACK_RAM_SIZE   (CYBLE_ALIGN_TO_4(CYBLE_DEFAULT_RAM_SIZE_SOC + CYBLE_LL_CONTROLLER_HEAP_REQ_COMP + \
              (CYBLE_GATT_MTU_PLUS_L2CAP_MEM_EXT * (CYBLE_GATT_MTU_BUFF_COUNT + CYBLE_GATT_MAX_ATTR_BUFF_COUNT)) +\
              (CYBLE_L2CAP_PSM_PLUS_L2CAP_MEM_EXT * CYBLE_L2CAP_PSM_COUNT) +\
              (CYBLE_L2CAP_CBFC_PLUS_L2CAP_MEM_EXT * 2 * CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT) +\
              (CYBLE_L2CAP_MTU_PLUS_L2CAP_MEM_EXT * CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT) +\
              (CYBLE_L2CAP_MPS_PLUS_L2CAP_MEM_EXT * CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT *\
              (CYBLE_L2CAP_MTU_MPS)) +\
              (CYBLE_STACK_BUFFER_MGR_UTIL_RAM_SZ * CYBLE_STACK_APP_MIN_POOL) +\
              (CYBLE_GATT_PREPARE_WRITE_BUFF_LEN)))   /* This buffer must always be the latest */
#else
    #define CYBLE_STACK_RAM_SIZE     (CYBLE_DEFAULT_RAM_SIZE_HCI + CYBLE_LL_CONTROLLER_HEAP_REQ_COMP)
#endif /* CYBLE_MODE_PROFILE */  

#if(CYBLE_MODE_PROFILE)
    #define CYBLE_STACK_FLASH_SIZE   (CYBLE_STACK_FLASH_STORAGE_SIZE)
#endif /* (CYBLE_MODE_PROFILE) */


/***************************************
* Enumerated Types and Structs
***************************************/

/**
 \addtogroup group_common_api_gap_definitions
 @{
*/

/** Stack mode defines */


/** Advertisement SIG assigned numbers */
typedef enum
{
    /**Flags*/
    CYBLE_GAP_ADV_FLAGS = 0x01u,

    /**Incomplete List of 16-bit Service Class UUIDs*/
    CYBLE_GAP_ADV_INCOMPL_16UUID,

    /**Complete List of 16-bit Service Class UUIDs*/
    CYBLE_GAP_ADV_COMPL_16UUID,

    /**Incomplete List of 32-bit Service Class UUIDs*/
    CYBLE_GAP_ADV_INCOMPL_32_UUID,

    /**Complete List of 32-bit Service Class UUIDs*/
    CYBLE_GAP_ADV_COMPL_32_UUID,

    /**Incomplete List of 128-bit Service Class UUIDs*/
    CYBLE_GAP_ADV_INCOMPL_128_UUID,

    /**Complete List of 128-bit Service Class UUIDs*/
    CYBLE_GAP_ADV_COMPL_128_UUID,

    /**Shortened Local Name*/
    CYBLE_GAP_ADV_SHORT_NAME,

    /**Complete Local Name*/
    CYBLE_GAP_ADV_COMPL_NAME,

    /**Tx Power Level*/
    CYBLE_GAP_ADV_TX_PWR_LVL,

    /**Class of Device*/
    CYBLE_GAP_ADV_CLASS_OF_DEVICE = 0x0Du,

    /**Simple Pairing Hash C*/
    CYBLE_GAP_ADV_SMPL_PAIR_HASH_C,

    /**Simple Pairing Randomizer R*/
    CYBLE_GAP_ADV_SMPL_PAIR_RANDOM_R,

    /**Device ID*/
    CYBLE_GAP_ADV_DEVICE_ID,

    /**Security Manager TK Value*/
    CYBLE_GAP_ADV_SCRT_MNGR_TK_VAL = 0x10u,

    /** Security Manager Out of Band Flags */
    CYBLE_GAP_ADV_SCRT_MNGR_OOB_FLAGS,

    /** Slave Connection Interval Range */
    CYBLE_GAP_ADV_SLAVE_CONN_INTRV_RANGE,

    /** List of 16-bit Service Solicitation UUIDs*/
    CYBLE_GAP_ADV_SOLICIT_16UUID = 0x14u,

    /**List of 128-bit Service Solicitation UUIDs*/
    CYBLE_GAP_ADV_SOLICIT_128UUID,

    /**Service Data - 16-bit UUID*/
    CYBLE_GAP_ADV_SRVC_DATA_16UUID,

    /** Public Target Address */
    CYBLE_GAP_ADV_PUBLIC_TARGET_ADDR,

    /** Random Target Address */
    CYBLE_GAP_ADV_RANDOM_TARGET_ADDR,

    /** Appearance */
    CYBLE_GAP_ADV_APPEARANCE,

    /** Advertising Interval */
    CYBLE_GAP_ADV_ADVERT_INTERVAL,

    /** LE Bluetooth Device Address */
    CYBLE_GAP_ADV_LE_BT_DEVICE_ADDR,

    /** LE Role */
    CYBLE_GAP_ADV_LE_ROLE,

    /** Simple Pairing Hash C-256 */
    CYBLE_GAP_ADV_SMPL_PAIR_HASH_C256,

    /** Simple Pairing Randomizer R-256 */
    CYBLE_GAP_ADV_SMPL_PAIR_RANDOM_R256,

    /**List of 32-bit Service Solicitation UUIDs*/
    CYBLE_GAP_ADV_SOLICIT_32UUID,

    /**Service Data - 32-bit UUID*/
    CYBLE_GAP_ADV_SRVC_DATA_32UUID,

    /**Service Data - 128-bit UUID*/
    CYBLE_GAP_ADV_SRVC_DATA_128UUID,

    /** 3D Information Data */
    CYBLE_GAP_ADV_3D_INFO_DATA = 0x3D

}CYBLE_GAP_ADV_ASSIGN_NUMBERS;

/** @} */
/***************************************
* Type Definitions
***************************************/

/**
 \addtogroup group_common_api_definitions
 @{
*/

/** Event callback function prototype to receive events from BLE component */
typedef void (* CYBLE_CALLBACK_T) (uint32 eventCode, void *eventParam);

/** @} */

/***************************************
* API Constants
***************************************/

#define CYBLE_AD_TYPE_MORE16UUID                    (0x02u)
#define CYBLE_AD_TYPE_CMPL16UUID                    (0x03u)
#define CYBLE_AD_TYPE_MORE32UUID                    (0x04u)
#define CYBLE_AD_TYPE_CMPL32UUID                    (0x05u)
#define CYBLE_AD_TYPE_MORE128UUID                   (0x06u)
#define CYBLE_AD_TYPE_CMPL128UUID                   (0x07u)

#define CYBLE_DISCOVERY_IDLE                        (0x00u)
#define CYBLE_DISCOVERY_SERVICE                     (0x01u)
#define CYBLE_DISCOVERY_CHAR                        (0x02u)
#define CYBLE_DISCOVERY_DESCR                       (0x03u)
#define CYBLE_DISCOVERY_DONE                        (0x04u)

/* CyBle_NextCharDscrDiscovery parameters */
#define CYBLE_DISCOVERY_INIT                        (0x00u)
#define CYBLE_DISCOVERY_CONTINUE                    (0x01u)

#define CYBLE_SFLASH_DIE_X_MASK                     (0x3Fu)
#define CYBLE_SFLASH_DIE_X_BITS                     (6u)
#define CYBLE_SFLASH_DIE_Y_MASK                     (0x3Fu)
#define CYBLE_SFLASH_DIE_Y_BITS                     (6u)
#define CYBLE_SFLASH_DIE_XY_BITS                    (CYBLE_SFLASH_DIE_X_BITS + CYBLE_SFLASH_DIE_Y_BITS)
#define CYBLE_SFLASH_DIE_WAFER_MASK                 (0x1Fu)
#define CYBLE_SFLASH_DIE_WAFER_BITS                 (5u)
#define CYBLE_SFLASH_DIE_XYWAFER_BITS               (CYBLE_SFLASH_DIE_XY_BITS + CYBLE_SFLASH_DIE_WAFER_BITS)
#define CYBLE_SFLASH_DIE_LOT_MASK                   (0x7Fu)
#define CYBLE_SFLASH_DIE_LOT_BITS                   (7u)

#define CYBLE_SFLASH_DIE_X_REG                      ( *(uint8 *) CYREG_SFLASH_DIE_X)
#define CYBLE_SFLASH_DIE_Y_REG                      ( *(uint8 *) CYREG_SFLASH_DIE_Y)
#define CYBLE_SFLASH_DIE_WAFER_REG                  ( *(uint8 *) CYREG_SFLASH_DIE_WAFER)
#define CYBLE_SFLASH_DIE_LOT_REG                    ( *(uint8 *) CYREG_SFLASH_DIE_LOT0)

/* Device address stored by user in ROW4 of the SFLASH */
#define CYBLE_SFLASH_DEVICE_ADDRESS_PTR             ( (CYBLE_GAP_BD_ADDR_T *) (CYREG_SFLASH_MACRO_0_FREE_SFLASH0))

#define CYBLE_AD_STRUCTURE_MAX_LENGTH               (31u)

/* AD types for complete and shortened local name */
#define CYBLE_SHORT_LOCAL_NAME                      (8u)
#define CYBLE_COMPLETE_LOCAL_NAME                   (9u)

#define CYBLE_ADVERTISING_FAST                      (0x00u)
#define CYBLE_ADVERTISING_SLOW                      (0x01u)
#define CYBLE_ADVERTISING_CUSTOM                    (0x02u)

#define CYBLE_SCANNING_FAST                         (0x00u)
#define CYBLE_SCANNING_SLOW                         (0x01u)
#define CYBLE_SCANNING_CUSTOM                       (0x02u)

#define CYBLE_BONDING_YES                           (0x00u)
#define CYBLE_BONDING_NO                            (0x01u)

#define CYBLE_PENDING_STACK_FLASH_WRITE_BIT         (0x01u)
#define CYBLE_PENDING_CCCD_FLASH_WRITE_BIT          (0x02u)
#define CYBLE_PENDING_CCCD_FLASH_CLEAR_BIT          (0x04u)
#define CYBLE_PENDING_CCCD_FLASH_CLEAR_ALL_BIT      (0x08u)
#define CYBLE_PENDING_CCCD_FLASH_CLEAR_MASK         \
                                        (CYBLE_PENDING_CCCD_FLASH_CLEAR_BIT | CYBLE_PENDING_CCCD_FLASH_CLEAR_ALL_BIT)

/* GAP Advertisement Flags */
#define CYBLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE     (0x01u)   /* LE Limited Discoverable Mode. */
#define CYBLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE     (0x02u)   /* LE General Discoverable Mode. */
#define CYBLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED     (0x04u)   /* BR/EDR not supported. */
#define CYBLE_GAP_ADV_FLAG_LE_BR_EDR_CONTROLLER     (0x08u)   /* Simultaneous LE and BR/EDR, Controller. */
#define CYBLE_GAP_ADV_FLAG_LE_BR_EDR_HOST           (0x10u)   /* Simultaneous LE and BR/EDR, Host. */
#define CYBLE_GAP_ADV_FLAGS_PACKET_LENGTH           (0x02u)

/* GAP Advertising interval min and max */
#define CYBLE_GAP_ADV_ADVERT_INTERVAL_MIN           (0x0020u) /* Minimum Advertising interval in 625 us units, i.e. 
                                                                20 ms. */
#define CYBLE_GAP_ADV_ADVERT_INTERVAL_NONCON_MIN    (0x00A0u) /* Minimum Advertising interval in 625 us units for non 
                                                                 connectable mode, i.e. 100 ms. */
#define CYBLE_GAP_ADV_ADVERT_INTERVAL_MAX           (0x4000u) /* Maximum Advertising interval in 625 us units, i.e. 
                                                                 10.24 s. */
#define CYBLE_GAP_ADV_ADVERT_INTERVAL_PACKET_LENGTH (0x03u)

#define CYBLE_GAPC_CONNECTING_TIMEOUT               (30u)     /* Seconds */


/***************************************
* Private Function Prototypes
***************************************/

/** \cond IGNORE */
void CyBle_Init(void);
void CyBle_ServiceInit(void);
uint16 CyBle_Get16ByPtr(const uint8 ptr[]);
void CyBle_Set16ByPtr(uint8 ptr[], uint16 value);
/** \endcond */


/***************************************
* Function Prototypes
***************************************/

/**
 \addtogroup group_common_api_core_functions
 @{
*/

CYBLE_API_RESULT_T CyBle_Start(CYBLE_CALLBACK_T  callbackFunc);
void CyBle_Stop(void);

#if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
    CYBLE_API_RESULT_T CyBle_StoreBondingData(uint8 isForceWrite);
    CYBLE_API_RESULT_T CyBle_GapRemoveBondedDevice(CYBLE_GAP_BD_ADDR_T* bdAddr);
#endif /* (CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */

/** @} */

/**
 \addtogroup group_common_api_gap_peripheral_functions
 @{
*/

#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
    CYBLE_API_RESULT_T CyBle_GappStartAdvertisement(uint8 advertisingIntervalType);
    void CyBle_GappStopAdvertisement(void);
    void CyBle_ChangeAdDeviceAddress(const CYBLE_GAP_BD_ADDR_T* bdAddr, uint8 dest);
#endif /* CYBLE_GAP_ROLE_PERIPHERAL */

/** @} */

/**
 \addtogroup group_common_api_gap_central_functions
 @{
*/

#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)
    CYBLE_API_RESULT_T CyBle_GapcStartScan(uint8 scanningIntervalType);
    void CyBle_GapcStopScan(void);
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */

#if(CYBLE_GAP_ROLE_CENTRAL)
    CYBLE_API_RESULT_T CyBle_GapcConnectDevice(const CYBLE_GAP_BD_ADDR_T * address);
    CYBLE_API_RESULT_T CyBle_GapcCancelDeviceConnection(void);
#endif /* CYBLE_GAP_ROLE_CENTRAL */

/** @} */

/***************************************
* External data references
***************************************/

extern CYBLE_CALLBACK_T                             CyBle_ApplCallback;
extern uint8                                        cyBle_initVar;
#if(CYBLE_SHARING_MODE_EXPORT)
extern uint8                                        *cyBle_stackMemoryRam;
#else
extern uint8                                        cyBle_stackMemoryRam[CYBLE_STACK_RAM_SIZE];
#endif  /* CYBLE_SHARING_MODE_EXPORT */
extern volatile uint8                               cyBle_eventHandlerFlag;
extern CYBLE_GAP_BD_ADDR_T                          cyBle_deviceAddress;
extern CYBLE_GAP_BD_ADDR_T                          *cyBle_sflashDeviceAddress;
extern CYBLE_GAP_AUTH_INFO_T                        cyBle_authInfo;

#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)
    extern CYBLE_GAPC_DISC_INFO_T                   cyBle_discoveryInfo;
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */

#if(CYBLE_GAP_ROLE_CENTRAL)
    extern CYBLE_GAPC_CONN_PARAM_T                  cyBle_connectionParameters;
    extern uint16                                   cyBle_connectingTimeout;
    
#endif /* CYBLE_GAP_ROLE_CENTRAL */

#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
    extern CYBLE_GAPP_DISC_PARAM_T                  cyBle_discoveryParam;
    extern CYBLE_GAPP_DISC_DATA_T                   cyBle_discoveryData;
    extern CYBLE_GAPP_SCAN_RSP_DATA_T               cyBle_scanRspData;
    extern CYBLE_GAPP_DISC_MODE_INFO_T              cyBle_discoveryModeInfo;
#endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */

#if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))

/* This is a two-bit variable that contains status of pending write to flash operation. 
   This variable is initialized to zero in CyBle_Init() API function.
   CYBLE_PENDING_CCCD_FLASH_WRITE_BIT flag is set after write to CCCD event when 
   peer device supports bonding (cyBle_peerBonding == CYBLE_GAP_BONDING). 
   CYBLE_PENDING_STACK_FLASH_WRITE_BIT flag is set after CYBLE_EVT_PENDING_FLASH_WRITE event.
   CyBle_StoreBondingData() should be called to store pending bonding data.
   This function automatically clears pending bits after write operation complete. */
    extern uint8 cyBle_pendingFlashWrite;
    
/* Bonding type setting of peer device, CYBLE_GAP_BONDING_NONE or CYBLE_GAP_BONDING.
   It is initialized after pairing with peer device and used for cyBle_pendingFlashWrite variable 
   setting.
    */    
    extern uint8 cyBle_peerBonding;
    
#endif  /* (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define CYBLE_TX_POWER_LEVEL                        CYBLE_TX_POWER_LEVEL_ADV



#endif /* CY_BLE_CYBLE_H  */


/* [] END OF FILE */
