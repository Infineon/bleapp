/***************************************************************************//**
* \file CyBle.h
*
* \file CYBLE_Stack.h
* \version 3.61
*
* \brief
*  This file contains declaration of public BLE APIs other than those covered by
*  GAP, GATT and L2CAP specific APIs. Also specified are the defines, constants
*  and data structures required for the APIs.
* 
* Related Document:
*  BLE Standard Spec - CoreV4.2, CoreV4.1, CSS, CSAs, ESR05, ESR06
* 
********************************************************************************
* \copyright
* Copyright 2014-2019, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CYBLE_H_
#define CYBLE_H_


/***************************************
* Common stack includes
***************************************/

#include "cyfitter.h"
#include "cytypes.h"


/***************************************
* Constants
***************************************/

#define CYBLE_STACK_STATE_BUSY		   	0x01u
#define CYBLE_STACK_STATE_FREE		   	0x00u

/***************************************
* MACROS for User Event mask 
****************************************/
#define CYBLE_EVT_GAP_CONN_ESTB_MSK        	  0x01u
#define CYBLE_EVT_GAP_SCAN_REQ_RECVD_MSK      0x02u

#define CYBLE_ISR_BLESS_CONN_CLOSE_CE		0x0001u

#define CYBLE_ISR_BLESS_ADV_CLOSE           0x0002u 

/***************************************
* Retention data definition
***************************************/

/* Bluetooth Device Address size */
#define CYBLE_GAP_BD_ADDR_SIZE                                          (0x06u)

/***************************************
*  Memory pool configuration data defines
***************************************/

/* Size of internal data buffer structures */
#define CYBLE_STACK_BUFFER_MGR_UTIL_RAM_SZ                              (0x1Cu)

/* Default Max ACL Packet Size for LE-DATA packet both for */
#define CYBLE_LL_DEFAULT_MAX_SUPPORTED_ACL_BUFFER_SZ                    (0xFCu)

/* Default Max ACL Packet Size for Rx LE-DATA Packet
 * Formula: Default ACL Size (27 bytes) ~ AlignToWord(27) =  28
 * */
#define CYBLE_LL_DEFAULT_ACL_MAX_RX_BUFFER_SZ                           (0x1Cu)


/* 8 Additional Bytes = (4 bytes of MIC + 4 bytes of HCI header) */
#define CYBLE_LL_ACL_DATA_PACKET_OVERHEAD_SZ                            (0x08u)


/* Default Max ACL Packet Size for Tx LE-DATA Packet
 *
 * Formula: Default ACL Size (27 bytes) ~ AlignToWord(27) =  28
 *
 * */
#define CYBLE_LL_DEFAULT_ACL_MAX_TX_BUFFER_SZ                           (0x24u)


/* Number of Rx ACL Packet buffers, this shall not change
 * as this should not be user configurable parameter */
#define CYBLE_LL_DEFAULT_NUM_ACL_RX_PACKETS                             (0x04u)


/* Number of Tx ACL Packet buffers */
#define CYBLE_LL_DEFAULT_NUM_ACL_TX_PACKETS                             (0x04u)

/* Default Tx capability . If DLE is not enabled, this is Tx capability*/
#define CYBLE_LL_DEFAULT_TX_CAPABILITY                                  (0x1Bu)

/* Default Rx capability . If DLE is not enabled, this is Rx capability*/
#define CYBLE_LL_DEFAULT_RX_CAPABILITY                                  (0x1Bu)

/* Example for ACL Rx Packets User Configuration
 * 1) 
 * CYBLE_LL_DEFAULT_ACL_MAX_BUFFER_SZ can change as User can choose
 * to support Max RX packet, this should get change based on 
 * BLE Core 4.2 Data Length Configuration as per
 * "Max Supported Rx Octets" 
 * 
 * 2) 
 * CYBLE_LL_DEFAULT_NUM_ACL_RX_PACKETS shall be fixed to the defined value
 * */
#define CYBLE_LL_ACL_RX_HEAP_REQ        (CYBLE_LL_DEFAULT_NUM_ACL_RX_PACKETS * \
                            (                                                  \
                                 CYBLE_LL_DEFAULT_MAX_SUPPORTED_ACL_BUFFER_SZ + \
                                 CYBLE_LL_ACL_DATA_PACKET_OVERHEAD_SZ +    \
                                 CYBLE_MEM_EXT_SZ                           \
                            ))

/* Example for ACL Tx Packets User Configuration
 * 1) 
 * CYBLE_LL_DEFAULT_ACL_MAX_BUFFER_SZ can change as User can choose
 * to support Max TX packet size, this should get change based on 
 * BLE Core 4.2 Data Length Configuration as per
 * "Max Supported Tx Octets"
 *  
 *  CYBLE_LL_TOTAL_ACL_MAX_TX_BUFFER_SZ = "Max Supported Tx Octets" + 
 *  CYBLE_MEM_EXT_SZ (8 bytes = 4 bytes of MIC + 4 bytes of HCI header)
 *
 * 
 * 2) 
 * CYBLE_LL_DEFAULT_NUM_ACL_RX_PACKETS shall be fixed to the defined value
 * */
#define CYBLE_LL_ACL_TX_HEAP_REQ        (CYBLE_LL_DEFAULT_NUM_ACL_TX_PACKETS * \
                            (                                                  \
                                 CYBLE_LL_DEFAULT_MAX_SUPPORTED_ACL_BUFFER_SZ + \
                                 CYBLE_LL_ACL_DATA_PACKET_OVERHEAD_SZ +    \
                                 CYBLE_MEM_EXT_SZ                           \
                            ))

/* Internal RAM required for LE Data Length Extension Feature */
#define CYBLE_LL_DLE_HEAP_REQ                                           (0x50u)

/* Internal RAM required for LE Privacy Extension Feature */
#define CYBLE_LL_PRIVACY_HEAP_REQ                                       (0x54u)

/* Default RPA List Entry Size */
#define CYBLE_DEFAULT_RPA_LIST_SZ                                       (0x08u)

/* Default RPA List Entry Size 
 * DKSH: RPA list support is limited to 8 only for time being */
#define CYBLE_MAX_RPA_LIST_SZ                                           (0x08u)

/* Example for Total BLE Controller Heap Requirement */
#define CYBLE_LL_CONTROLLER_HEAP_REQ    ((CYBLE_LL_PRIVACY_HEAP_REQ * \
                                            CYBLE_DEFAULT_RPA_LIST_SZ) + \
                                            CYBLE_LL_DLE_HEAP_REQ + \
                                            CYBLE_LL_ACL_TX_HEAP_REQ + \
                                            CYBLE_LL_ACL_RX_HEAP_REQ)



/* Size of the heap when GATT MTU, L2CAP MTU, MPS sizes are specified as 23 Bytes */
#define CYBLE_DEFAULT_RAM_SIZE_SOC	    		        (16u + 1024u + 824u + 120u)    

/* Size of the heap when the BLE Stack is built in HCI mode */
#define CYBLE_DEFAULT_RAM_SIZE_HCI  		                    (16u + 824u + 120u)

#define CYBLE_MEM_EXT_SZ                                          (0x08u)

#define CYBLE_L2CAP_HDR_SZ                                        (0x04u)

/* Buffer size needed for L2cap PSM and CBFC channels */
#define CYBLE_L2CAP_PSM_SIZE                                         (40u)
#define CYBLE_L2CAP_CBFC_CHANNEL_SIZE                                (32u)

/* Size of the heap required for Secure connection feature 
 * This includes memory for SMP FSM, SMP Crypto tool box and ECC
 */
#define CYBLE_RAM_SIZE_SECURE_CONNECTIONS                            (860u)

/* Size of the heap required for DLE 
 * This will depend on configuration parameters. 
 * Exact formula to be provided yet.
 */
#define CYBLE_RAM_SIZE_DLE                                           (0u)
/* Size of the heap required for LL Privacy feature 
 * This will depend on configuration parameters. 
 * Exact formula to be provided yet.
 */
#define CYBLE_RAM_SIZE_PRIVACY_1_2                                   (0u)

/* Data Buffer Pool identifiers to support configurable parameters for L2CAP and
 * GATT in BLE Stack 
 * These data buffer pools need to be configured during BLE Stack
 * initialization. */

/* Data Buffer index for ATT/GATT Configured MTU Size */
#define CYBLE_STACK_APP_POOL_1_SZ            	                   	0x00u

/* Data Buffer index for L2CAP configuration for number of PSM Channels
 * */
#define CYBLE_STACK_APP_POOL_2_SZ		                           	0x01u

/* Data Buffer index for L2CAP configuration for number of CBFC Channels
 * */
#define CYBLE_STACK_APP_POOL_3_SZ                          			0x02u

/* Data Buffer index for L2CAP configured MTU Size */
#define CYBLE_STACK_APP_POOL_4_SZ                                   0x03u

/* Data Buffer index for L2CAP configured MPS Size */
#define CYBLE_STACK_APP_POOL_5_SZ                                   0x04u

/* Maximum Application Pool  */
#define CYBLE_STACK_APP_MIN_POOL                                   (CYBLE_STACK_APP_POOL_5_SZ + 1)

/* BLESS Radio normal gain mode for Rx and Tx */
#define CYBLE_BLESS_NORMAL_GAIN_MODE                                (0x00u)

/* BLESS Radio high gain mode for Rx and Tx */
#define CYBLE_BLESS_HIGH_GAIN_MODE                                  (0x01u)

#define CYBLE_GATT_MAX_ATTR_LEN_MIN_VAL                             (0x00u)

#define CYBLE_GATT_MIN_NO_OF_ATT_MTU_BUFF                         	(0x03u)

/* Max attribute size can be of 0xFFFF but Stack has limitation
 * on buffer creation as it requires additional 8 bytes and 
 * L2CAP header size (4 bytes)
 * */
#define CYBLE_GATT_MAX_ATTR_LEN_MAX_VAL                             (0xFFD0u)

#define CYBLE_L2CAP_MTU_MIN_VALUE                                   (0x17u)

/* Max L2CAP MTU or MPS size can be of 0xFFFF, but Stack has limitation
 * on buffer creation as it requires additional 8 bytes and 
 * L2CAP header size (4 bytes)
 * */
#define CYBLE_L2CAP_MTU_MAX_VALUE                                (0xFFD0u)

#define CYBLE_L2CAP_MPS_MIN_VALUE                CYBLE_L2CAP_MTU_MIN_VALUE

#define CYBLE_L2CAP_MPS_MAX_VALUE                CYBLE_L2CAP_MTU_MAX_VALUE

#define CYBLE_STACK_FLASH_STORAGE_SIZE           (0x09u + (0x9Cu * CYBLE_GAP_MAX_BONDED_DEVICE))


/* Feature mask for selective features for CYBLE_STACK_CONFIG_PARAM_T */
#define CYBLE_DLE_FEATURE_MASK                                     (0x01u)
#define CYBLE_PRIVACY_1_2_FEATURE_MASK                             (0x02u)
#ifdef CYBLE_PRIVACY_1_2_FEATURE_MASK
#define CYBLE_LL_PRIVACY_FEATURE_MASK                              (0x02u)
#endif /* CYBLE_PRIVACY_1_2_FEATURE_MASK */
#define CYBLE_SECURE_CONN_FEATURE_MASK                             (0x04u)

/* BLESS IP Version for BLE128, BLE256 **, *A revision compatible
 * with Bluetooth 4.1 Core Specification */
#define CYBLE_M0S8BLESS_IP_VERSION_4_1                             (0x01u)

/* BLESS IP Version for BLE256 *B, and future revision compatible
 * with Bluetooth 4.2 and higher version Core Specification */
#define CYBLE_M0S8BLESS_IP_VERSION_4_2                             (0x02u)
    
/***************************************
* Deprecated definitions
***************************************/

/* Event indicating connection update complete on the GAP Central.
	Do not use this for new designs. Use CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE
	instead */
#define CYBLE_EVT_GAPC_CONNECTION_UPDATE_COMPLETE	CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE

/* Application to provide or free memory */
#define CYBLE_ALLOC_MEMORY							(0x00u)
#define CYBLE_FREE_MEMORY							(0x01u)


/***************************************
* Enumerated Types and Structs
***************************************/

/**
 \addtogroup group_common_api_definitions
 @{
*/	
	
/** event callback function prototype to receive events from stack */
typedef void (*CYBLE_APP_CB_T)(uint8 event, void* evParam);

/** event callback function prototype to receive Bless State events from stack */
typedef void (*CYBLE_BLESS_CB_T)(uint32 event, void* evParam);

/** Application callback function prototype to notify when AES CMAC generation is completed */
typedef void (* AES_CMAC_APPL_CB) (void);
/** @} */

/**
 \addtogroup group_common_api_events
 @{
*/

/** Host stack events.
   * Generic events: 0x01 to 0x1F
   * GAP events: 0x20 to 0x3F
   * GATT events: 0x40 to 0x6F
   * L2CAP events: 0x70 to 0x7F  
   * Future use: 0x80 to 0xFF
*/
typedef enum
{
    /** This event is triggered by BLE stack when stack is in a bad state, Restarting stack is the 
	only way to get out of the state */
    CYBLE_EVT_HOST_INVALID = 0x00u,

    /* Range for Generic events - 0x01 to 0x1F */

    /** This event is received when BLE stack is initialized and turned ON by invoking CyBle_StackInit () function.*/
    CYBLE_EVT_STACK_ON = 0x01u,

    /** This event is received when there is a timeout and application needs to handle the event. 
       Timeout reason is defined by CYBLE_TO_REASON_CODE_T. */
    CYBLE_EVT_TIMEOUT,

    /** This event indicates that some internal hardware error has occurred. Reset of the hardware may be required. */
    CYBLE_EVT_HARDWARE_ERROR,

    /** This event is triggered by 'Host Stack' if 'Controller' responds with an error code for any HCI command.
       Event parameter returned will be an HCI error code as defined in Bluetooth 4.1 core specification, Volume 2,
       Part D, section 1.3 or User can refer CYBLE_HCI_ERROR_T for HCI error codes. This event will be received only 
       if there is an error. */
    CYBLE_EVT_HCI_STATUS,

    /** This event is triggered by host stack if BLE stack is busy or not. 
       Event Parameter corresponding to this event will indicate the state of BLE stack's internal protocol buffers
       for the application to safely initiate data transactions (GATT, GAP Security, and L2CAP transactions)
       with the peer BLE device.
       Event parameter is of type uint8.

        * CYBLE_STACK_STATE_BUSY (0x01) = CYBLE_STACK_STATE_BUSY indicates application that BLE stack's internal buffers
        *                   are about to be filled, and the remaining buffers are required to respond peer BLE device
        *                   After this event, application shall not initiate (GATT, GAP Security and L2CAP data transactions). 
        *                   However application shall respond to peer initiated transactions to prevent BLE protocol timeouts
        *                   to occur.
        *                   Application initiated data transactions can be resumed after CYBLE_EVT_STACK_BUSY_STATUS
        *                   event with parameter 'CYBLE_STACK_STATE_FREE' is received.
        *
        * CYBLE_STACK_STATE_FREE (0x00) = CYBLE_STACK_STATE_FREE indicates application that pending transactions are completed
        *                   and sufficient buffers are available to process application initiated transactions.
        *                   The 'CYBLE_EVT_STACK_BUSY_STATUS' event with 'CYBLE_STACK_STATE_FREE' is indicated to 
        *                   application if BLE Stack's internal buffer state has transitioned from 'CYBLE_STACK_STATE_BUSY'
        *                   to 'CYBLE_STACK_STATE_FREE'.
        *
       To increase BLE stack's internal buffers count and achieve better throughput for attribute MTU greater then 32, 
       use MaxAttrNoOfBuffer parameter in the Expression view of the Advanced tab.    
    */
    CYBLE_EVT_STACK_BUSY_STATUS,
	
	/** This event is received when stack wants application to provide memory to process remote request.
       Event parameter is of type CYBLE_MEMORY_REQUEST_T.
       This event is automatically handled by the component for the CYBLE_PREPARED_WRITE_REQUEST request. 
       The component allocates sufficient memory for the long write request with assumption that attribute MTU size 
       is negotiated to the minimum possible value. Application could use dynamic memory allocation to save static 
       RAM memory consumption. To enable this event for application level, set EnableExternalPrepWriteBuff parameter
       in the Expression view of the Advanced tab to the true.    
    */
	CYBLE_EVT_MEMORY_REQUEST,

    /* Range for GAP events - 0x20 to 0x3F */

    /** This event is triggered every time a device is discovered; pointer to structure of type CYBLE_GAPC_ADV_REPORT_T 
        is returned as the event parameter. */
    CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT = 0x20u,

    /** This event is received by Peripheral and Central devices. When it is received by Peripheral, peripheral 
        needs to Call CyBle_GappAuthReqReply() to reply to authentication request from Central.

        When this event is received by Central, that means the slave has requested Central to initiate authentication
        procedure. Central needs to call CyBle_GappAuthReq() to initiate authentication procedure.
        Pointer to structure of type CYBLE_GAP_AUTH_INFO_T is returned as the event parameter. */
    CYBLE_EVT_GAP_AUTH_REQ,

    /** This event indicates that the device has to send passkey to be used during the pairing procedure. 
       CyBle_GapAuthPassKeyReply() is required to be called with valid parameters on receiving this event.

       Refer to Bluetooth Core Spec. 4.1, Part H, Section 2.3.5.1 Selecting STK Generation Method.

       Nothing is returned as part of the event parameter. */
    CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST,

    /** This event indicates that the device needs to display passkey during the pairing procedure.

       Refer to Bluetooth Core Spec. 4.1, Part H, Section 2.3.5.1 Selecting STK Generation Method.

       Pointer to data of type 'uint32' is returned as part of the event parameter. Passkey can
       be any 6-decimal-digit value. */
    CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST,

     /** This event indicates that the authentication procedure has been completed.

     The event parameter contains the security information as defined by CYBLE_GAP_AUTH_INFO_T.
     This event is generated at the end of the following three operations:
    	* Authentication is initiated with a newly connected device
    	* Encryption is initiated with a connected device that is already bonded
    	* Re-Encryption is initiated with a connected device with link already encrypted
     During encryption/re-encryption, the Encryption Information exchanged during the pairing process
     is used to encrypt/re-encrypt the link. As this does not modify any of the authentication 
     parameters with which the devices were paired, this event is generated with NULL event data
     and the result of the encryption operation. */
    CYBLE_EVT_GAP_AUTH_COMPLETE,

    /** Authentication process failed between two devices. The return value of type 
       CYBLE_GAP_AUTH_FAILED_REASON_T indicates the reason for failure. */
    CYBLE_EVT_GAP_AUTH_FAILED,

    /** Peripheral device has started/stopped advertising. 
       This event is generated after making a call to CyBle_GappEnterDiscoveryMode and 
       CyBle_GappExitDiscoveryMode functions. The event parameter contains the status
       which is of type 'uint8'.
       
       If the data is '0x00', it indicates 'success'; Anything else indicates 'failure'. */
    CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP,
    
    /** This event is generated at the GAP Peripheral end after connection is completed with peer Central device.
    	For GAP Central device, this event is generated as in acknowledgment of receiving this event successfully
    	by BLE Controller. Once connection is done, no more event is required but if fails to establish connection,
    	'CYBLE_EVT_GAP_DEVICE_DISCONNECTED' is passed to application. ' CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE'
    	event is triggered instead of 'CYBLE_EVT_GAP_DEVICE_CONNECTED', if Link Layer Privacy is enabled in component customizer.   
	Event parameter is a pointer to a structure of type CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T. */
    CYBLE_EVT_GAP_DEVICE_CONNECTED,

	/** Disconnected from remote device or failed to establish connection. Parameter returned with the event 
	contains pointer to the reason for disconnection, which is of type uint8. For details refer
	core spec 4.2, vol2, part D or User can refer CYBLE_HCI_ERROR_T for HCI error codes */
    CYBLE_EVT_GAP_DEVICE_DISCONNECTED,

    /** Encryption change event for active connection. 'evParam' can be decoded as
         * evParam[0] = 0x00 -> Encryption OFF
         * evParam[0] = 0x01 -> Encryption ON
    	 * Any other value of evParam[0] -> Error
     
       This is an informative event for application when there is a change in encryption. 
       Application may choose to ignore it. */
    CYBLE_EVT_GAP_ENCRYPT_CHANGE,

    /** This event is generated at the GAP Central and the Peripheral end after connection parameter update
		is requested from the host to the controller. Event parameter is a pointer to a structure of type CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T. */
    CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE,

    /** Central device has started/stopped scanning. 
       This event is generated after making a call to CyBle_GapcStartDiscovery and 
       CyBle_GapcStopDiscovery APIs. The event parameter contains the status, which is of type 'uint8'.
       
       If the data is '0x00', it indicates 'success'; Anything else indicates 'failure'. */
    CYBLE_EVT_GAPC_SCAN_START_STOP,

    /** Indication that the SMP keys exchange with peer device is complete, the event handler
       is expected to store the peer device keys, especially IRK which is used to resolve the
       peer device after the connection establishment.
       
       Event parameter returns data of type CYBLE_GAP_SMP_KEY_DIST_T containing the peer device keys. */
    CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT,
    
    /** This event indicates that the device needs to display passkey during 
        secure connection pairing procedure. CyBle_GapAuthPassKeyReply() is
        required to be called with valid parameters on receiving this event.
        Since no key to be entered by the user for Numeric comparison, 
        parameter passkey for the function CyBle_GapAuthPassKeyReply will be 
        ignored.
        Event parameter is a pointer to a 6 digit Passkey value. */
    CYBLE_EVT_GAP_NUMERIC_COMPARISON_REQUEST,
    
    /** This event is generated when keypress (Secure connections) is received
       from peer device. */
    CYBLE_EVT_GAP_KEYPRESS_NOTIFICATION,

    /** This event is generated when OOB generation for Secure connections is complete.  
       Event parameter is of type 'CYBLE_GAP_OOB_DATA_T' */
    CYBLE_EVT_GAP_OOB_GENERATED_NOTIFICATION,
    
    /** The LE Data Length Change event notifies the Host of a change to either the maximum Payload length or 
       the maximum transmission time of Data Channel PDUs in either direction. The values reported are the maximum
       that will actually be used on the connection following the change. Event parameter is of type 
       'CYBLE_GAP_CONN_DATA_LENGTH_T' */
    CYBLE_EVT_GAP_DATA_LENGTH_CHANGE,

    /** The LE Enhanced Connection Complete event indicates application that a new connection has been created when 
        Link Layer Privacy is enabled in component customizer. 
       Event parameter is of type 'CYBLE_GAP_ENHANCE_CONN_COMPLETE_T' */
    CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE,
	
    /** The LE Direct Advertising Report event indicates that directed advertisements have been received where 
       the advertiser is using a resolvable private address for the InitA field in the ADV_DIRECT_IND PDU and the
       Scanning_Filter_Policy is equal to 0x02 or 0x03. Event parameter is of type 'CYBLE_GAPC_DIRECT_ADV_REPORT_T' */
    CYBLE_EVT_GAPC_DIRECT_ADV_REPORT,

    /** SMP negotiated auth info event is raised as soon as SMP has completed pairing properties (feature exchange)
     * negotiation. The event parameter is CYBLE_GAP_AUTH_INFO_T. CYBLE_GAP_AUTH_INFO_T will have the 
     * negotiated parameter, the pairing should either pass with these negotiated parameters or may fail. This event
     * is applicable to both GAP Central and GAP Peripheral devices. In GAP Peripheral, this event is called from 
     * API function CyBle_GappAuthReqReply context.
     */
    CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO,

	/**	This event is generated when connection got established */
	CYBLE_EVT_GAP_CONN_ESTB,

	/** SCAN_REQ received event 
	 *  User has to explicitly call CyBle_SetAppEventMask() by setting scan req event mask
	 */
	CYBLE_EVT_GAP_SCAN_REQ_RECVD,

	/**	This event is generated when in the CYBLE_EVT_GAP_AUTH_REQ component event handler CyBle_GappAuthReqReply()
        returned not CYBLE_ERROR_OK value. It's possible when the bonded device is full and application tries to initiate 
        pairing with bonding enabled. Event parameter is of type 'CYBLE_API_RESULT_T'. Application will have to handle this event by removing an oldest (or any other) 
        device from the bond list and call CyBle_GappAuthReqReply() function again. */
    CYBLE_EVT_GAP_AUTH_REQ_REPLY_ERR,

	/** This event is generated when the local P-256 public-private key pair generation is completed and new keys
	    are stored in the BLE Stack for SC pairing procedure.
	    Event parameter is a pointer to structure of type CYBLE_GAP_SMP_LOCAL_P256_KEYS. */
	CYBLE_EVT_GAP_SMP_LOC_P256_KEYS_GEN_AND_SET_COMPLETE,

    /* Range for GATT events - 0x40 to 6F */

    /** The event is received by the Client when the Server cannot perform the requested 
       operation and sends out an error response. Event parameter is a pointer to a structure
       of type CYBLE_GATTC_ERR_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_ERROR_RSP = 0x40u,

    /** This event is generated at the GAP Peripheral end after connection is completed with peer Central device.
    	For GAP Central device, this event is generated as in acknowledgment of receiving this event successfully
    	by BLE Controller. Once connection is done, no more event is required but if fails to establish connection,
    	'CYBLE_EVT_GATT_DISCONNECT_IND' is passed to application.      
	Event parameter is a pointer to a structure of type CYBLE_CONN_HANDLE_T. */
    CYBLE_EVT_GATT_CONNECT_IND,

    /** GATT is disconnected. Nothing is returned as part of the event parameter. */
    CYBLE_EVT_GATT_DISCONNECT_IND,

    /** 'GATT MTU Exchange Request' received from GATT client device. Event parameter 
       contains the MTU size of type CYBLE_GATT_XCHG_MTU_PARAM_T. */
    CYBLE_EVT_GATTS_XCNHG_MTU_REQ,

    /** 'GATT MTU Exchange Response' received from server device. Event parameter is a
       pointer to a structure of type CYBLE_GATT_XCHG_MTU_PARAM_T. */
    CYBLE_EVT_GATTC_XCHNG_MTU_RSP,

    /** 'Read by Group Type Response' received from server device. Event parameter
       is a pointer to a structure of type CYBLE_GATTC_READ_BY_GRP_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP,

    /** 'Read by Type Response' received from server device. Event parameter is a
       pointer to a structure of type CYBLE_GATTC_READ_BY_TYPE_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_READ_BY_TYPE_RSP,

    /** 'Find Information Response' received from server device. Event parameter is
       a pointer to a structure of type 'CYBLE_GATTC_FIND_INFO_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_FIND_INFO_RSP,

    /** 'Find by Type Value Response' received from server device. Event parameter is
       a pointer to a structure of type CYBLE_GATTC_FIND_BY_TYPE_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP,

    /** 'Read Response' from server device. Event parameter is a pointer to a
       structure of type CYBLE_GATTC_READ_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_READ_RSP,

    /** 'Read Blob Response' from server. Event parameter is a pointer to a
       structure of type CYBLE_GATTC_READ_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_READ_BLOB_RSP,

    /** 'Read Multiple Responses' from server. Event parameter is a pointer
       to a structure of type CYBLE_GATTC_READ_RSP_PARAM_T. The 'actualLen' field
       should be ignored as it is unused in this event response. */
    CYBLE_EVT_GATTC_READ_MULTI_RSP,

    /** 'Write Request' from client device. Event parameter is a pointer to
       a structure of type CYBLE_GATTS_WRITE_REQ_PARAM_T . */
    CYBLE_EVT_GATTS_WRITE_REQ,

    /** 'Write Response' from server device. Event parameter is a pointer
       to a structure of type CYBLE_CONN_HANDLE_T. */
    CYBLE_EVT_GATTC_WRITE_RSP,

    /** 'Write Command' Request from client device. Event parameter is a 
       pointer to a structure of type CYBLE_GATTS_WRITE_CMD_REQ_PARAM_T. */
    CYBLE_EVT_GATTS_WRITE_CMD_REQ,

    /** 'Prepare Write' Request from client device. Event parameter is a
       pointer to a structure of type CYBLE_GATTS_PREP_WRITE_REQ_PARAM_T. */
    CYBLE_EVT_GATTS_PREP_WRITE_REQ, 

    /** 'Execute Write' request from client device. Event parameter is a
       pointer to a structure of type 'CYBLE_GATTS_EXEC_WRITE_REQ_T'
       This event will be triggered before GATT DB is modified. GATT Db will be updated 
       only if there is no error condition provided by application. In case of error condition triggered
       during stack validation, partial write will occur. Write will be canceled from that handle where 
       error has occurred and error response corresponding to that handle will be sent to remote.
       If at any point of time 'CYBLE_GATT_EXECUTE_WRITE_CANCEL_FLAG' is received in 
       execWriteFlag fields of 'CYBLE_GATTS_EXEC_WRITE_REQ_T' structure, then all previous 
       writes are canceled. For execute cancel scenario, all elements of 
       'CYBLE_GATTS_EXEC_WRITE_REQ_T' should be ignored except execWriteFlag and connHandle.
     */
    CYBLE_EVT_GATTS_EXEC_WRITE_REQ,

    /** 'Execute Write' response from server device. Event parameter is a
       pointer to a structure of type CYBLE_GATTC_EXEC_WRITE_RSP_T. */
    CYBLE_EVT_GATTC_EXEC_WRITE_RSP,

    /** Notification data received from server device. Event parameter
       is a pointer to a structure of type CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T. */
    CYBLE_EVT_GATTC_HANDLE_VALUE_NTF,

    /** Indication data received from server device. Event parameter is
       a pointer to a structure of type CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T. */
    CYBLE_EVT_GATTC_HANDLE_VALUE_IND,

    /** Confirmation to indication response from client device. Event
       parameter is a pointer to a structure of type CYBLE_CONN_HANDLE_T. */
    CYBLE_EVT_GATTS_HANDLE_VALUE_CNF,

    /** Confirmation to indication response from client device. Event
       parameter is a pointer to a structure of type CYBLE_GATTS_SIGNED_WRITE_CMD_REQ_PARAM_T. 
       if value.val parameter is set to Zero, then signature is not matched and ignored by stack */
    CYBLE_EVT_GATTS_DATA_SIGNED_CMD_REQ,

    /** Event indicating that GATT group procedure has stopped or completed, this event occurs
       only if application has called CyBle_GattcStopCmd API function. 
       Event parameters shall be ignored */
    CYBLE_EVT_GATTC_STOP_CMD_COMPLETE,

   /** Event parameter type is CYBLE_GATTS_CHAR_VAL_READ_REQ_T. It is triggered on server side 
       when client sends read request and when characteristic has CYBLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT 
       property set. This event could be ignored by application unless it need to response by error response which
       needs to be set in gattErrorCode field of event parameter. Application can update attribute value
	   when this event is received */
    CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ,

	/** Event indicates that GATT long procedure is end and stack will not send any further
    * requests to peer. Either this event or 'CYBLE_EVT_GATTC_ERROR_RSP' will be received
    * by application. This event may get triggered for below GATT long procedures:
    * 	1. CyBle_GattcDiscoverAllPrimaryServices
	* 	2. CyBle_GattcDiscoverPrimaryServiceByUuid
	* 	3. CyBle_GattcFindIncludedServices
	* 	4. CyBle_GattcDiscoverAllCharacteristics
	* 	5. CyBle_GattcDiscoverCharacteristicByUuid
	* 	6. CyBle_GattcDiscoverAllCharacteristicDescriptors
	* 	7. CyBle_GattcReadLongCharacteristicValues
	* 	8. CyBle_GattcReadLongCharacteristicDescriptors	\n
	* 	Event parameter is ATT opcode for the corresponding long GATT Procedure.
	*/
	CYBLE_EVT_GATTC_LONG_PROCEDURE_END,

    /* Range for L2CAP events - 0x70 to 0x7F */

    /** This event indicates the connection parameter update received
       from the remote device. The application is expected to reply to L2CAP using the
       CyBle_L2capLeConnectionParamUpdateResponse() function to respond to the remote
       device, whether parameters are accepted or rejected.
       
       Event Parameter pointer points to data of type 'CYBLE_GAP_CONN_UPDATE_PARAM_T' */
    CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ = 0x70u,

    /** This event indicates the connection parameter update response received
       from the master. Event Parameter pointer points to data with two possible values:
    	* Accepted = 0x0000
    	* Rejected  = 0x0001

       Data is of type unit16. */
    CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP,

    /** This event indicates that the request send over l2cap signaling has been
       rejected. Event parameter is a pointer to a structure of type
       CYBLE_L2CAP_COMMAND_REJ_REASON_T. */
    CYBLE_EVT_L2CAP_COMMAND_REJ,

    /** This event is used to inform application of the incoming L2CAP CBFC
       Connection Request. Event parameter is a pointer to a structure of type
       CYBLE_L2CAP_CBFC_CONN_IND_PARAM_T is returned. */
    CYBLE_EVT_L2CAP_CBFC_CONN_IND,

    /** This event is used to inform application of the L2CAP CBFC Connection
       Response/Confirmation. Event parameter is a pointer to a structure of
       type CYBLE_L2CAP_CBFC_CONN_CNF_PARAM_T is returned. */
    CYBLE_EVT_L2CAP_CBFC_CONN_CNF,

    /** This event is used to inform application of the L2CAP CBFC Disconnection
       Request received from the Peer device. Event parameter is a pointer to
       Local CID of type unit16. */
    CYBLE_EVT_L2CAP_CBFC_DISCONN_IND,

    /** This event is used to inform application of the L2CAP CBFC Disconnection
       confirmation/Response received from the Peer device. Event parameter is a
       pointer to a structure of type CYBLE_L2CAP_CBFC_DISCONN_CNF_PARAM_T. */
    CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF,

    /** This event is used to inform application of data received over L2CAP
       CBFC channel. Event parameter is a pointer to a structure of type
       CYBLE_L2CAP_CBFC_RX_PARAM_T. */
    CYBLE_EVT_L2CAP_CBFC_DATA_READ,

    /** This event is used to inform the application of receive credits reached
       low mark. After receiving L2CAP data/payload from peer device for a
       specification Channel, the available credits are calculated.
       
       If the credit count goes below the low mark, this event is called to inform
       the application of the condition, so that if the application wants it can
       send more credits to the peer device.
       
       Event parameter is a pointer to a structure of type
       CYBLE_L2CAP_CBFC_LOW_RX_CREDIT_PARAM_T. */
    CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND,

    /** This event is used to inform application of having received transmit
       credits. This event is called on receiving LE Flow Control Credit from peer
       device.
       
       Event parameter is a pointer to a structure of type
       CYBLE_L2CAP_CBFC_LOW_TX_CREDIT_PARAM_T.
       
       If the 'result' field of the received data is non-zero, this indicates an
       error. If the sum of 'credit' field value and the previously available credit
       at the peer device receiving credit information exceeds 65535, it indicates a
       'credit overflow' error.
       
       In case of error, the peer device receiving this event should initiate
       disconnection of the L2CAP channel by invoking CyBle_L2capDisconnectReq () 
       function. */
    CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND,

    /** This event is used to inform application of data transmission completion over L2CAP CBFC
       channel. Event parameter is of type 'CYBLE_L2CAP_CBFC_DATA_WRITE_PARAM_T'.
       L2CAP CBFC application must wait for this event before transmitting the next CBFC L2CAP data.
       Application can send next data only when CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND event is received for 
       previous sent data and CYBLE_EVT_STACK_BUSY_STATUS is received with status CYBLE_STACK_STATE_FREE.
       
       This event will be deprecated in future. It is only kept for backward compatibility.
       It is not recommended to be used by new design */
    CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND,

#ifdef CYBLE_HOST_QUALIFICATION
	/** Tester to manipulate pairing request or response PDU. Event parameter is a pointer to 1 bytes data.
	    Tester can manipulate the bits of the byte */
	CYBLE_EVT_QUAL_SMP_PAIRING_REQ_RSP = 0x80u,

	/** Tester to manipulate local Public Key. Event parameter is a pointer to local public key of size 64 Bytes.
		Tester can manipulate the bits/bytes */
	CYBLE_EVT_QUAL_SMP_LOCAL_PUBLIC_KEY,

	/** Tester to assign pairing failed error code. Event parameter is a pointer to 16 bits value.
		Tester should assign error code to lower bits */
	CYBLE_EVT_QUAL_SMP_PAIRING_FAILED_CMD,

#endif /* CYBLE_HOST_QUALIFICATION */

    /*##Range for for future use - 0x90 to 0xFF*/

    /** This event is used to inform application that flash write is pending
        Stack internal data structures are modified and require backup. */
    CYBLE_EVT_PENDING_FLASH_WRITE = 0xFA,

    /** LE PING Authentication Timeout Event to indicate that peer device has not responded
        with the valid MIC packet within the application configured ping authentication time. */
    CYBLE_EVT_LE_PING_AUTH_TIMEOUT = 0xFB,

	
	/** This event is used to inform application that an HCI event has been received from controller.
	    Event parameter is of type 'CYBLE_HCI_PKT_PARAMS_T'	 

	    This event will only be trigger when user register for SoftTransport by calling CyBle_HciSoftTransportEnable() */
	CYBLE_EVT_HCI_PKT,

	/** This event is used to inform application that bonding information stored in flash is corrupted. */
    CYBLE_EVT_FLASH_CORRUPT,
	
	/** Maximum value of CYBLE_EVENT_T type */
    CYBLE_EVT_MAX = 0xFF

}CYBLE_EVENT_T;
/** Alias of CYBLE_EVENT_T, which is used internally by Stack */
#define CYBLE_EVT_HOST_STACK_T CYBLE_EVENT_T
/** @} */

/**
 \addtogroup group_common_api_events
 @{
*/
/** HCI Error codes defined by BT Spec */
typedef enum
{
    /** Command success */
   	CYBLE_HCI_COMMAND_SUCCEEDED = 0x00u,

    /** Unknown HCI Command */
    CYBLE_HCI_UNKNOWN_HCI_COMMAND_ERROR,

	/** Unknown Connection Identifier */
    CYBLE_HCI_NO_CONNECTION_ERROR,

	/** Hardware Failure */
    CYBLE_HCI_HARDWARE_FAILURE_ERROR,

	/** Page Timeout */
    CYBLE_HCI_PAGE_TIMEOUT_ERROR,

	/** Authentication Failure */
    CYBLE_HCI_AUTHENTICATION_FAILURE_ERROR,

	/** PIN or Key Missing */
    CYBLE_HCI_KEY_MISSING_ERROR,

	/** Memory Capacity Exceeded */
    CYBLE_HCI_MEMORY_FULL_ERROR,

	/** Connection Timeout */
    CYBLE_HCI_CONNECTION_TIMEOUT_ERROR,

	/** Connection Limit Exceeded */
    CYBLE_HCI_MAX_NUMBER_OF_CONNECTIONS_ERROR, 

	/** Synchronous Connection Limit to a Device Exceeded */
    CYBLE_HCI_MAX_SCO_CONNECTIONS_REACHED_ERROR, 

	/** ACL Connection Already Exists */
    CYBLE_HCI_ACL_CONNECTION_EXISTS_ERROR,

	/** Command Disallowed*/
    CYBLE_HCI_COMMAND_DISALLOWED_ERROR,

	/** Connection Rejected due to Limited resources */
    CYBLE_HCI_HOST_REJECTED_LIMITED_RESOURCES_ERROR,

	/** Connection Rejected due to Security Reasons */
    CYBLE_HCI_HOST_REJECTED_SECURITY_REASONS_ERROR,   

	/** Connection Rejected due to Unacceptable BD_ADDR */
    CYBLE_HCI_HOST_REJECTED_PERSONAL_DEVICE_ERROR, 

	/** Connection Accept Timeout Exceeded */
    CYBLE_HCI_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED_ERROR, 

	/** Unsupported Feature or Parameter Value */
    CYBLE_HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_ERROR, 

	/** Invalid HCI Command Parameters */
    CYBLE_HCI_INVALID_HCI_COMMAND_PARAMETERS_ERROR,

	/** remote user terminated Connection */
    CYBLE_HCI_CONNECTION_TERMINATED_USER_ERROR ,  

	/** Remote Device Terminated Connection due to Low Resources */
    CYBLE_HCI_CONNECTION_TERMINATED_LOW_RESOURCES_ERROR, 

	/** Remote Device Terminated Connection due to Power Off */
    CYBLE_HCI_CONNECTION_TERMINATED_POWER_OFF_ERROR , 

	/** Connection Terminated By Local Host */
    CYBLE_HCI_CONNECTION_TERMINATED_LOCAL_HOST_ERROR, 

	/** Repeated Attempts */
    CYBLE_HCI_REPEATED_ATTEMPTS_ERROR,    

	/** Pairing Not Allowed */
    CYBLE_HCI_PAIRING_NOT_ALLOWED_ERROR, 

	/** Unknown LMP PDU */
    CYBLE_HCI_UNKNOWN_LMP_PDU_ERROR, 

	/** Unsupported Remote Feature */
    CYBLE_HCI_UNSUPPORTED_REMOTE_FEATURE_ERROR,  

	/** SCO Offset Rejected */
    CYBLE_HCI_SCO_OFFSET_REJECTED_ERROR,     

	/** SCO Interval Rejected */
    CYBLE_HCI_SCO_INTERVAL_REJECTED_ERROR, 

	/** SCO Air Mode Rejected */
    CYBLE_HCI_SCO_AIR_MODE_REJECTED_ERROR,  

	/** Invalid LMP Parameters */
    CYBLE_HCI_INVALID_LMP_PARAMETERS_ERROR,  

	/** Invalid LL Parameters */
    CYBLE_HCI_INVALID_LL_PARAMETERS_ERROR = 0x01Eu,    

	/** Unspecified error */
    CYBLE_HCI_UNSPECIFIED_ERROR,                  

	/** Unsupported LMP Parameter Value */
    CYBLE_HCI_UNSUPPORTED_PARAMETER_VALUE_ERROR,   

	/** Unsupported LL Parameter Value */
    CYBLE_HCI_UNSUPPORTED_LL_PARAMETER_VALUE_ERROR = 0x20u,    

	/** Role Change Not Allowed */
    CYBLE_HCI_SWITCH_NOT_ALLOWED_ERROR,             

	/** LMP Response Timeout */
    CYBLE_HCI_LMP_RESPONSE_TIMEOUT_ERROR,      

	/** LL Response Timeout*/
	CYBLE_HCI_LL_RESPONSE_TEMEOUT_ERROR = 0x22u,

	/** LMP Error Transaction Collision */
    CYBLE_HCI_LMP_ERROR_TRANSACTION_COLLISION_ERROR,  

	/** LMP PDU Not Allowed */
    CYBLE_HCI_PDU_NOT_ALLOWED_ERROR,               

	/** Encryption Mode Not Acceptable */
    CYBLE_HCI_ENCRYPTION_MODE_NOT_ACCEPTABLE_ERROR,    

	/** Link Key cannot be changed */
    CYBLE_HCI_UNIT_KEY_USED_ERROR,       

	/** Requested QoS Not Supported */
    CYBLE_HCI_QOS_NOT_SUPPORTED_ERROR,  

	/** Instant Passed */
    CYBLE_HCI_INSTANT_PASSED_ERROR,          

	/** Pairing with unit key not supported */
    CYBLE_HCI_PAIRING_WITH_UNIT_KEY_NOT_SUPPPORTED_ERROR, 

    /** Different Transaction Collision */
    CYBLE_HCI_DIFFERENT_TRANSACTION_COLLISION,   

	/** QoS Unacceptable parameter */
    CYBLE_HCI_QOS_UNACCEPTABLE_PARAMETER = 0x2C, 

	/** QoS Rejected */
    CYBLE_HCI_QOS_REJECTED_ERROR, 

	/** Channel Classification Not Supported */
    CYBLE_HCI_CHANNEL_CLASSIFICATION_NOT_SUPPORTED,

	/** Insufficient security */
    CYBLE_HCI_INSUFFICIENT_SECURITY,  

	/** parameter out of mandatory range */
    CYBLE_HCI_PARAMETER_OUT_OF_MANDATORY_RANGE,   

	/** Role Switch Pending */
    CYBLE_HCI_ROLE_SWITCH_PENDING = 0x32,          

	/** Reserved Slot violate */
    CYBLE_HCI_RESERVED_SLOT_VIOLATION = 0x34,    

	/** Role switch failed */
    CYBLE_HCI_ROLE_SWITCH_FAILED,      

	/** Extended inquiry response too large */
    CYBLE_HCI_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE,   

	/** secure simple pairing not supported by host */
    CYBLE_HCI_SECURE_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST,  

	/** host busy pairing */
    CYBLE_HCI_HOST_BUSY_PAIRING,             

 	/** Connection Rejected due to No suitable channel found */
    CYBLE_HCI_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND, 

	/** Controller busy */
    CYBLE_HCI_CONTROLLER_BUSY,                           

	/** unacceptable connection interval */
    CYBLE_HCI_UNACCEPTABLE_CONNECTION_INTERVAL,                   

	/** unacceptable connection parameters */
    CYBLE_HCI_UNACCEPTABLE_CONNECTION_PARAMETERS = 0x3B,                   

	/** Directed Advertising Timeout */
    CYBLE_HCI_DIRECTED_ADVERTISING_TIMEOUT,                      

	/** Connection Terminated due to MIC Failure */
    CYBLE_HCI_CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE,          

	/** Connection failed to be established */
    CYBLE_HCI_CONNECTION_FAILED_TO_BE_ESTABLISHED,                

	/** MAC connection failed */
    CYBLE_HCI_MAC_CONNECTION_FAILED,                             

	/** Coarse Clock Adjustment Rejected 
	 *  but will try to adjust using clock 
	 */
    CYBLE_HCI_COARSE_CLOCK_ADJ_REJECTED_TRY_USING_CLOCK_DRAGGING,  

	/** INVALID HCI ERROR CODE */
    CYBLE_HCI_LAST_ENTRY_BLUETOOTH_ERROR_CODE,
}CYBLE_HCI_ERROR_T;
/** @} */

/**
 \addtogroup group_common_api_definitions
 @{
*/

/** Common error codes received as API result */
typedef enum
{
    /** No Error occurred */
    CYBLE_ERROR_OK = 0x0000u,
    
    /** At least one of the input parameters is invalid */
    CYBLE_ERROR_INVALID_PARAMETER,
    
    /** Operation is not permitted */
    CYBLE_ERROR_INVALID_OPERATION,
    
    /** An internal error occurred in the stack */
    CYBLE_ERROR_MEMORY_ALLOCATION_FAILED,
    
    /** Insufficient resources to perform requested operation */
    CYBLE_ERROR_INSUFFICIENT_RESOURCES,
    
    /** OOB data not available */
    CYBLE_ERROR_OOB_NOT_AVAILABLE,
    
    /** Connection is required to perform requested operation. Connection not 
       present */
    CYBLE_ERROR_NO_CONNECTION,
    
    /** No device entity to perform requested operation */
    CYBLE_ERROR_NO_DEVICE_ENTITY,
    
    /** Attempted repeat operation is not allowed */
    CYBLE_ERROR_REPEATED_ATTEMPTS,
    
    /** GAP role is incorrect */
    CYBLE_ERROR_GAP_ROLE,
    
    /** Error reading TC power */
    CYBLE_ERROR_TX_POWER_READ,
    
    /** BLE Initialization failed */
    CYBLE_ERROR_BT_ON_NOT_COMPLETED,
    
    /** Security operation failed */
    CYBLE_ERROR_SEC_FAILED,

    /*L2CAP error codes*/
    
    /** L2CAP PSM encoding is incorrect */
    CYBLE_ERROR_L2CAP_PSM_WRONG_ENCODING = 0x000Du,
    
    /** L2CAP PSM has already been registered */
    CYBLE_ERROR_L2CAP_PSM_ALREADY_REGISTERED,
    
    /** L2CAP PSM has not been registered */
    CYBLE_ERROR_L2CAP_PSM_NOT_REGISTERED,
    
    /** L2CAPconnection entity not found */
    CYBLE_ERROR_L2CAP_CONNECTION_ENTITY_NOT_FOUND,
    
    /** L2CAP channel not found */
    CYBLE_ERROR_L2CAP_CHANNEL_NOT_FOUND,
    
    /** Specified PSM is out of range */
    CYBLE_ERROR_L2CAP_PSM_NOT_IN_RANGE,

    /**GATT DB error codes*/

    /** Invalid attribute handle */
    CYBLE_ERROR_GATT_DB_INVALID_ATTR_HANDLE,
    
    /* Other Codes.  */
    
    /** Device cannot be added to whitelist as it has already been added */
    CYBLE_ERROR_DEVICE_ALREADY_EXISTS = 0x0027u,
    
    /** Write to flash is not permitted */
    CYBLE_ERROR_FLASH_WRITE_NOT_PERMITED = 0x0028u,

	/** MIC Authentication failure */
	CYBLE_ERROR_MIC_AUTH_FAILED = 0x0029u,	

   /** Controller error codes. These come directly from controller (not host stack)*/

    /** Hardware Failure */
    CYBLE_ERROR_HARDWARE_FAILURE,

    /** Unsupported feature or parameter value */
    CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE,

    /** Error in flash Write */
    CYBLE_ERROR_FLASH_WRITE,
    
    /** LL same transaction collision */
    CYBLE_ERROR_LL_SAME_TRANSACTION_COLLISION,

	/** Controller Busy */
    CYBLE_ERROR_CONTROLLER_BUSY = 0x00FEu,
	
    /** All other errors not covered in the above list map to this error code */
    CYBLE_ERROR_MAX = 0x00FFu,

    /* Profile level API_RESULT codes */
    /** Characteristic notifications disabled */
    CYBLE_ERROR_NTF_DISABLED,

    /** Characteristic indications disabled */
    CYBLE_ERROR_IND_DISABLED,

    /** \cond IGNORE */    
    CYBLE_ERROR_CHAR_IS_NOT_DISCOVERED,
    /** \endcond */

    /** The state is not valid for current operation */
    CYBLE_ERROR_INVALID_STATE,
    
    /** Stack is Busy */
    CYBLE_ERROR_STACK_BUSY

}CYBLE_API_RESULT_T;

/** BLE power modes */
typedef enum
{
    /** Link Layer engine and Digital modem clocked from ECO. 
        The CPU can access the BLE Sub-System (BLESS) registers.
        This mode collectively denotes Tx Mode, Rx Mode, and 
        Idle mode of BLESS.
    */
    CYBLE_BLESS_ACTIVE = 0x01u,
    
    /** The clock to the link layer engine and digital modem
        is gated. The ECO continues to run to maintain the 
        link layer timing.
    */
    CYBLE_BLESS_SLEEP,
    
    /** The ECO is stopped and WCO is used to maintain link layer
        timing. RF transceiver is turned off completely to reduce
        leakage current. BLESS logic is kept powered ON from the
        SRSS deep sleep regulator for retention.
    */
    CYBLE_BLESS_DEEPSLEEP,
    
    /** External power is available but all internal LDOs are
        turned off.
    */
    CYBLE_BLESS_HIBERNATE,
    
    /** Invalid mode */
    CYBLE_BLESS_INVALID = 0xFFu
} CYBLE_LP_MODE_T;

/** BLESS Power enum reflecting power states supported by BLESS radio */
typedef enum
{
	/** BLESS state is ACTIVE */
    CYBLE_BLESS_STATE_ACTIVE = 0x01,
    /** BLESS state is EVENT_CLOSE */
    CYBLE_BLESS_STATE_EVENT_CLOSE,
    /** BLESS state is SLEEP */
    CYBLE_BLESS_STATE_SLEEP,
    /** BLESS state is ECO_ON */
    CYBLE_BLESS_STATE_ECO_ON,
    /** BLESS state is ECO_STABLE */
    CYBLE_BLESS_STATE_ECO_STABLE,
    /** BLESS state is DEEPSLEEP */
    CYBLE_BLESS_STATE_DEEPSLEEP,
    /** BLESS state is HIBERNATE */
    CYBLE_BLESS_STATE_HIBERNATE,
    /** BLESS state is INVALID */
    CYBLE_BLESS_STATE_INVALID = 0xFFu
} CYBLE_BLESS_STATE_T;

/** BLESS Power enum reflecting power level values supported by BLESS radio */
typedef enum
{
    /** ABS PWR = -18dBm, PA_Gain = 0x01 */
    CYBLE_LL_PWR_LVL_NEG_18_DBM = 0x01u, 
    /** ABS PWR = -12dBm, PA_Gain = 0x02 */
    CYBLE_LL_PWR_LVL_NEG_12_DBM,         
    /** ABS PWR = -6dBm, PA_Gain = 0x03 */
    CYBLE_LL_PWR_LVL_NEG_6_DBM,          
    /** ABS PWR = -3dBm, PA_Gain = 0x04 */
    CYBLE_LL_PWR_LVL_NEG_3_DBM,          
    /** ABS PWR = -2dBm, PA_Gain = 0x05 */
    CYBLE_LL_PWR_LVL_NEG_2_DBM,          
    /** ABS PWR = -1dBm, PA_Gain = 0x06 */
    CYBLE_LL_PWR_LVL_NEG_1_DBM,          
    /** ABS PWR = 0dBm, PA_Gain = 0x07 */
    CYBLE_LL_PWR_LVL_0_DBM,           
    /** ABS PWR = 3dBm, PA_Gain = 0x07,
     * PWR_GAIN level is same as 0 dBm, but
     * the ABS_PWR is amplified and applied for both
     * Connection and Advertising channel.
     * */
    CYBLE_LL_PWR_LVL_3_DBM,           
    /** ABS PWR = 3dBm, PA_Gain = 0x07 */
    CYBLE_LL_PWR_LVL_MAX
} CYBLE_BLESS_PWR_LVL_T;

/** BLE channel group ID */
typedef enum
{
    /** Advertisement channel type */
    CYBLE_LL_ADV_CH_TYPE = 0x00u,
    /** Connection channel type */
    CYBLE_LL_CONN_CH_TYPE,
    /** Maximum value of CYBLE_BLESS_PHY_CH_GRP_ID_T type */
    CYBLE_LL_MAX_CH_TYPE
} CYBLE_BLESS_PHY_CH_GRP_ID_T;

/** Structure to set/get BLE radio power */
typedef struct
{
    /** Output Power level */
    CYBLE_BLESS_PWR_LVL_T           blePwrLevelInDbm;
    /** Channel group ID for which power level is to be read/written */
    CYBLE_BLESS_PHY_CH_GRP_ID_T     bleSsChId;
} CYBLE_BLESS_PWR_IN_DB_T;

/** BLE WCO sleep clock accuracy configuration */
typedef enum
{
	/** SCA 251 to 500 PPM */
    CYBLE_LL_SCA_251_TO_500_PPM = 0x00u,
   	/** SCA 151 to 250 PPM */
    CYBLE_LL_SCA_151_TO_250_PPM,
    /** SCA 101 to 150 PPM */
    CYBLE_LL_SCA_101_TO_150_PPM,
    /** SCA 076 to 100 PPM */
    CYBLE_LL_SCA_076_TO_100_PPM,
    /** SCA 051 to 075 PPM */
    CYBLE_LL_SCA_051_TO_075_PPM,
    /** SCA 031 to 050 PPM */
    CYBLE_LL_SCA_031_TO_050_PPM,
    /** SCA 021 to 030 PPM */
    CYBLE_LL_SCA_021_TO_030_PPM,
    /** SCA 000 to 020 PPM */
    CYBLE_LL_SCA_000_TO_020_PPM,    
    /** Invalid PPM */
    CYBLE_LL_SCA_IN_PPM_INVALID
} CYBLE_BLESS_WCO_SCA_CFG_T;

/** BLE ECO clock divider */
typedef enum
{
    /** Link Layer clock divider = 1*/
    CYBLE_LL_ECO_CLK_DIV_1 = 0x00u,
	/** Link Layer clock divider = 2*/
	CYBLE_LL_ECO_CLK_DIV_2,
	/** Link Layer clock divider = 4*/
	CYBLE_LL_ECO_CLK_DIV_4,
	/** Link Layer clock divider = 8*/
	CYBLE_LL_ECO_CLK_DIV_8,
	/** Invalid Link Layer clock divider*/
	CYBLE_LL_ECO_CLK_DIV_INVALID
} CYBLE_BLESS_ECO_CLK_DIV_T;

/** BLE Stack memory request type */
typedef enum
{
	/** Memory requested for prepare write request */
	CYBLE_PREPARED_WRITE_REQUEST = 0x00u,

	/** Invalid request */
	CYBLE_INVALID_REQUEST
		
}CYBLE_PROTOCOL_REQ_T;

/** Memory request parameters */
typedef struct
{
    /** Protocol Request type*/
    CYBLE_PROTOCOL_REQ_T  	request;

    /** event parameter is generated to allocate memory or to free up previously allocated memory
    		CYBLE_ALLOC_MEMORY (0) = to allocate memory for request type, 
    		CYBLE_FREE_MEMORY (1) = free previously allocated memory for the request type */
    uint8					allocFree;

	/** This is an output parameter which application needs to fill and pass to BLE Stack as per below table:
	
	     request 						| memory							 
	 	 ------------				  	| ------------ 	
	     CYBLE_PREPARED_WRITE_REQUEST	| CYBLE_PREPARE_WRITE_REQUEST_MEMORY_T
	*/
	void					* configMemory;

} CYBLE_MEMORY_REQUEST_T;


/** BLE clock configuration parameters */
typedef struct
{
    /** Sleep Clock accuracy in PPM, 32Khz Cycles */
    CYBLE_BLESS_WCO_SCA_CFG_T  bleLlSca;
    /** Link Layer clock divider */
    CYBLE_BLESS_ECO_CLK_DIV_T  bleLlClockDiv;
    /** ECO crystal startup time in multiple of 62.5us */
    uint16 ecoXtalStartUpTime;
} CYBLE_BLESS_CLK_CFG_PARAMS_T;

/** This structure is used to hold version information of the BLE Stack Library */
typedef struct 
{
    /** The major version of the library */
    uint16 majorVersion;     
	/** The minor version of the library */
    uint16 minorVersion;     
	/** The patch number of the library */
    uint16 patch;            
	/** The build number of the library */
    uint16 buildNumber;

} CYBLE_STACK_LIB_VERSION_T;

/** @} */

/**
 \addtogroup group_common_api_gap_definitions
 @{
*/

/** Bluetooth Device Address  */
typedef struct
{
    /** Bluetooth device address */
    uint8     bdAddr[CYBLE_GAP_BD_ADDR_SIZE]; 
	/** public = 0, Random = 1 */
    uint8     type; 
}CYBLE_GAP_BD_ADDR_T;

/** @} */

/**
 \addtogroup group_common_api_definitions
 @{
*/

/** Set of buffers to be allocated by stack for stack operation */
typedef struct
{
    /** Size of the buffer chunk */
    uint16   bufferSize; 
	/** Number of the buffers units of 'bufferSize' */
    uint8   bufferUnits; 
} CYBLE_STK_APP_DATA_BUFF_T;


/** Configuration structure for Data Length Extension feature */
typedef struct
{
    /** DLE max Tx capability */
    uint16   dleMaxTxCapability;

    /** DLE max Rx capability */
    uint16   dleMaxRxCapability;

    /** DLE number of Tx buffers*/
    uint8   dleNumTxBuffer;
} CYBLE_DLE_CONFIG_PARAM_T;

/** Configuration structure for LL Privacy feature */
typedef struct
{
    /** Maximum number of possible entries in resolving list */
    uint8   resolvingListSize;
} CYBLE_PRIVACY_1_2_CONFIG_PARAM_T;

/**
 * Configuration structure for enabling selective features 
 * and passing associated parameters.
 */
typedef struct
{
    /** Configuration parameter for DLE feature */
    CYBLE_DLE_CONFIG_PARAM_T           *dleConfig;

    /** Configuration parameter for LL Privacy feature */
    CYBLE_PRIVACY_1_2_CONFIG_PARAM_T   *privacyConfig;

    /** The feature set mask used to control usage of 
     * specified feature in BLE stack. If a feature is not selected
     * then associated parameter pointer can be NULL.
     */
    uint16                             feature_mask;
} CYBLE_STACK_CONFIG_PARAM_T;

/**
 * Structure containing the parameters required for AES CMAC Generation 
 */
typedef struct
{
    /** pointer to message for which AES CMAC has to be calculated, LSB should be first */
    uint8               *buffer;
    /** size of the message buffer */
    uint16              size;
    /** AES CMAC 128-bit Key, LSB should be first */
    uint8               *key;
    /** output-parameter, Buffer to hold generated MAC of 16 bytes. Output is LSB first */
    uint8               *mac;
    /** Callback to notify when the AES-CMAC generation is completed. Once this callback is 
     * called, check for the output-parameter, which contains generated cmac
	 */
    AES_CMAC_APPL_CB    appl_callback;
                        
}CYBLE_AES_CMAC_GENERATE_PARAM_T;

/**
 * Structure for Registering Bless event mask 
 * and associated callback.
 */
typedef struct
{
	/** Bless state Event mask */
	uint32 BlessStateMask;

	/** User callback function */
	CYBLE_BLESS_CB_T bless_evt_app_cb;
	
}CYBLE_BLESS_EVENT_PARAM_T;

/**
 * DTM Payload sequence in SoC mode
 */
typedef enum
{
	/** PRBS9 sequence '11111111100000111101…’ 
	    (in transmission order) as described 
	    in [Vol 6] Part F, Section 4.1.5 */
	CYBLE_PAYLOAD_VAL_ZERO,

	/** Repeated ‘11110000’ (in transmission order) 
		sequence as described
		in [Vol 6] Part F, Section 4.1.5 */
	CYBLE_PAYLOAD_VAL_ONE,

	/** Repeated ‘10101010’ (in transmission order) 
		sequence as described
		in [Vol 6] Part F, Section 4.1.5 */
	CYBLE_PAYLOAD_VAL_TWO,

	/** PRBS15 sequence as described in 
		[Vol 6] Part F, Section 4.1.5 */
	CYBLE_PAYLOAD_VAL_THREE,

	/** Repeated ‘11111111’ (in transmission order) sequence */
	CYBLE_PAYLOAD_VAL_FOUR,

	/** Repeated ‘00000000’ (in transmission order) sequence */
	CYBLE_PAYLOAD_VAL_FIVE,

	/** Repeated ‘00001111’ (in transmission order) sequence */
	CYBLE_PAYLOAD_VAL_SIX,

	/** Repeated ‘01010101’ (in transmission order) sequence */
	CYBLE_PAYLOAD_VAL_SEVEN,
	
}CYBLE_PKT_PAYLOAD_T;

/**
 * DTM test parameters in SoC mode
 */
typedef struct
{
	/** "N = (F – 2402) / 2 Range: 0x00 – 0x27. 
		Frequency Range : 2402 MHz to 2480 MHz" */
	uint8 tx_frequency;

	/** length of the test data */
	uint8 length_of_test_data;

	/** payload sequence */
	CYBLE_PKT_PAYLOAD_T packet_payload;
	
}CYBLE_TRANSMITTER_TEST_PARAMS_T;

/**
 * HCI Packet type enum
 */
typedef enum
{
	/** HCI Command packet type */
    CYBLE_HCI_CMD_PKT_TYPE=0x1,

	/** HCI ACL data packet type */
    CYBLE_HCI_ACL_DATA_PKT_TYPE,

	/** HCI Synchronous packet type */
    CYBLE_HCI_SYNC_DATA_PKT_TYPE,

	/** HCI Event packet type */
    CYBLE_HCI_EVENT_PKT_TYPE,
    
}CYBLE_HCI_PKT_TYPE_T;

/**
 * structure containing params for HCI command
 */
typedef struct
{
	/** HCI packet type */
	CYBLE_HCI_PKT_TYPE_T pkt_type;

	/** length of the command */
	uint16 length;

	/** Command buffer*/
	uint8 *buffer;
	
}CYBLE_HCI_PKT_PARAMS_T;

/** @} */


/***************************************
* Global Function Declarations
***************************************/


/******************************************************************************

* Function Name: CyBle_StackSetFeatureConfig
***************************************************************************//**
*
* This API function sets the configuration for Bluetooth 4.2 features in BLE Stack to
* initialize the corresponding data structures and data buffers to support
* the features. BLE Stack will create the data buffers for Data length extension
* feature, LE Privacy 1_2 and Secure connections as specified in the parameters
* during time of initialization in CyBle_StackInit() API function.
*
* This is a blocking function. No event is generated on calling this function.
*
* \param configParam: pointer to CYBLE_STACK_CONFIG_PARAM_T. This structure contains
*                     pointers to config params for individual features. Individual
*                     feature configuration structures can be NULL is that feature is 
*                     not selected.
*
* \param featureHeapReq: Out parameter for returning memory requirement for selected features.
*
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                     | Description
*  ------------                     | -----------
*  CYBLE_ERROR_OK                   | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER    | Invalid configuration parameters passed or invalid combination of configParam and featureMask
*  CYBLE_ERROR_INVALID_OPERATION    | Invoked after successful stack initialization
*
* \note 
* In case of BLE SOC-Mode of operation, Stack will autonomously intiatiate DLE procedure (with max supported txoctet)
* after connection establishement when DLE feature is enabled and dleMaxTxCapability is greater than CYBLE_LL_DEFAULT_TX_CAPABILITY.
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StackSetFeatureConfig
(
    const CYBLE_STACK_CONFIG_PARAM_T       *configParam,
    uint16                                 *featureHeapReq
);


/******************************************************************************
* Function Name: CyBle_StackGetFeatureConfig
*******************************************************************************
*
* This API function is used to get Bluetooth 4.2 features configuration made to BLE Stack 
* during Stack initialization. For more details about configuration please 
* refer API function CyBle_StackSetFeatureConfig.
*
* This is a blocking function. No event is generated on calling this function.
*
* \param configParam: pointer to CYBLE_STACK_CONFIG_PARAM_T. This structure
*                     contains pointers to config params for individual 
*                     features. Application shall provide memory for this
*                     configuration structure.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                      | Description
*  ------------                      | -----------
*  CYBLE_ERROR_OK                    | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER     | Invalid input parameter. 
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StackGetFeatureConfig
(
    CYBLE_STACK_CONFIG_PARAM_T       *configParam
);


/******************************************************************************
* Function Name: CyBle_StackInit
***************************************************************************//**
* 
* This function initializes the BLE Stack and needs to be called from higher
* layer initialization routine only once before invoking any other BLE Stack
* function. It includes initialization of BLE Stack Manager, BLE Controller and
* BLE Host Stack modules which make up the BLE Stack.
*
* For HCI-Mode of operation, this function will not initialize BLE Host Stack
* module.
*
* This is a non-blocking function. A call to this function results in the
* generation of CYBLE_EVT_STACK_ON event on successful initialization of the
* BLE Stack.
*   
*     
*  \param CyBLEApplCbFunc: Event callback function to receive events from BLE Stack.
*                  CYBLE_APP_CB_T is a function pointer type. Application is not expected to call 
*                  stack APIs in the stack call back context. Stack execution should be allowed to
*                  return unless Stack API function explicitly mentions otherwise.
*
*                  Following APIs should not be called from BLE Stack callback context but can be called from
*                   'CYBLE_EVT_GATTC_ERROR_RSP' or 'CYBLE_EVT_GATTC_LONG_PROCEDURE_END' events
*                   or any not long procedure events.
*                     1.  CyBle_GattcDiscoverAllPrimaryServices
*                     2.  CyBle_GattcDiscoverPrimaryServiceByUuid
*                     3.  CyBle_GattcFindIncludedServices
*                     4.  CyBle_GattcDiscoverAllCharacteristics
*                     5.  CyBle_GattcDiscoverCharacteristicByUuid
*                     6.  CyBle_GattcDiscoverAllCharacteristicDescriptors
*                     7.  CyBle_GattcReadLongCharacteristicValues
*                     8.  CyBle_GattcWriteLongCharacteristicValues
*                     9.  CyBle_GattcReliableWrites
*                     10. CyBle_GattcReadLongCharacteristicDescriptors
*                     11. CyBle_GattcWriteLongCharacteristicDescriptors
*              
*  \param memoryHeapPtr: Pointer to an array of bytes to be allocated by the BLE component.
*  				(or the application, if the component's initialization function
* 				 is not used). The size of the memory to be allocated is as
* 				 given below for non - HCI mode build of the BLE Stack -
* 				 
* 				 (CYBLE_DEFAULT_RAM_SIZE_SOC + Accumulative memory for all dataBuff units
* 				 + CYBLE_STACK_BUFFER_MGR_UTIL_RAM_SZ * totalDataBufferPools
* 				 
* 				 Where, CYBLE_DEFAULT_RAM_SIZE_SOC is a define that is available from
* 				 the BLE Stack. Starting address of the memoryHeapPtr should be 4 bytes aligned and 
* 				 size of the total memory should be divisible by 4.
* 
*                  Accumulative memory for "single databuff instance" = 
*                    (dataBuff.bufferSize * dataBuff.bufferUnits)
* 
*                  totalDataBufferPools is "numOfDataBuffSet"
* 				 
* 				 If HCI mode BLE stack is used, the memory to be allocated should
* 				 be of size 'CYBLE_DEFAULT_RAM_SIZE_HCI'.
* 
*  \param totalHeapSz: Size of the total heap memory pointer by memoryHeapPtr. totalHeapSz shall be
*              the accumulated value of every dataBuff elements. To compute total size, each elements'
*              size shall be rounded to next 4 byte boundary value.
*
*              For example typical value can be computed in following manner:
*              
*              Size for buffer pool #1 to be added =         
*              ((CYBLE_ALIGN_TO_4(Size of GATT MTU) + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ)  *\
*              noOfBuffer)
*
*              Note that the buffer pool size for each chunk may not be 4 byte boundary align,
*              and it should be as per user configuration. BLE Stack's buffer management utility
*              internally align it to higher 4 byte boundary.
* 
*  \param dataBuff: array of structures of type CYBLE_STK_APP_DATA_BUFF_T. Ignored in case of HCI mode.
* 
*  \param totalDataBufferPools: Number of data buffer sets in the array. Ignored in case of HCI mode.
* 
*  Array dataBuff [totalDataBufferPools] shall provide the information to Stack based on the below table -

*  <table>
*  <tr>
*    <th>Array index</th>
*    <th>Application configuration param</th>
*    <th>bufferSize</th>
*    <th>noOfBuffer</th>
*  </tr>
*  <tr>
*    <td>0</td>
*    <td>GATT MTU</td>
*    <td>Size of MTU + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ</td>
*    <td>2</td>
*  </tr>
*  <tr>
*    <td>1</td>
*    <td>Number of PSM supported</td>
*    <td>((CYBLE_L2CAP_PSM_SIZE + CYBLE_MEM_EXT_SZ) * no of PSM supported)</td>
*    <td>No of PSM supported</td>
*  </tr>
*  <tr>
*    <td>2</td>
*    <td>Number of L2cap CBFC logical</td>
*    <td>((CYBLE_L2CAP_CBFC_CHANNEL_SIZE + CYBLE_MEM_EXT_SZ) * No of L2cap logical channels)</td>
*    <td>2 * No of L2cap logical channels</td>
*  </tr>
*  <tr>
*    <td>3</td>
*    <td>L2cap mtu (0x17 to 0xFFD0u)</td>
*    <td>Size of L2CAP MTU + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ</td>
*    <td>No of L2cap logical channels</td>
*  </tr>
*  <tr>
*    <td>4</td>
*    <td>L2cap mps (0x17 to 0xFFD0u)</td>
*    <td>Size of MPS + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ</td>
*    <td>(No of L2cap logical channels)*(Size of L2CAP MTU / Size of MPS (if not Zero))</td>
*  </tr>
*  </table>
* 
* 	Index position is fixed for each data buffer corresponding to configuration parameters.
*   First four buffers of with valid size (shall be > 12) corresponding to each field are required
*   for BLE_SOC mode operation, otherwise stack will throw error.
* 
*   'dataBuff' will be modified by stack. If application wants to reuse dataBuff, application should keep a copy of it.
*
* 	* No of buffers can be increased from 1 to 10 to achieve better throughput if mtu>32.
* 	   This is based on application throughput requirement.
* 
*  \param bleStackFlashPointer: Pointer to an array of bytes to be allocated by the BLE component for the storing the
*                         persistent data into the flash. Pointer provided is should be aligned to the flash
*                         boundary.
* 
*  \param bleStackFlashSize: Size of the total flash memory pointed by bleStackFlashPointer
* 
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>BLE Stack Mode</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>
*    - On passing a "NULL" pointer to the function in place of CyBLEApplCbFunc parameter if the BLE stack is not built
* 		  in HCI mode. CYBLE_ERROR_INVALID_PARAMETER is not returned in HCI mode for this condition.
* 	 - On passing a "NULL" pointer to the function in place of memoryHeapPtr 
*    - If maxMtuSize is less than 23 or greater than 512. CYBLE_ERROR_INVALID_PARAMETER is not returned 
*         in HCI mode for this condition.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_REPEATED_ATTEMPTS</td>
*    <td>On invoking this function more than once without calling CyBle_Shutdown() function between calls to 
*        this function if the BLE stack is not built in HCI mode.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed.</td>
*  </tr>
*  </table>
*     
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StackInit
(
    CYBLE_APP_CB_T 					CyBleAppCbFunc,
    uint8 							*memoryHeapPtr,
    uint16 							totalHeapSz,
    CYBLE_STK_APP_DATA_BUFF_T 		*dataBuff,
    uint8 							totalDataBufferPools,
    const uint8                     *bleStackFlashPointer,
    uint32                          bleStackFlashSize
);

                
/******************************************************************************
* Function Name: CyBle_Shutdown
***************************************************************************//**
*  This function stops any ongoing operation on the BLE Stack and forces the BLE
*  Stack to shut down. The only function that can be called after calling this
*  function is CyBle_StackInit. On calling this function, BLE Radio is turned 
*  off; whitelist and bonded device list are retained and can be used on
*  re-initializing the BLE Stack.
* 
*  This is a blocking function. No event is generated on calling this function.
* 
* \return
*  None
* 				
******************************************************************************/
void CyBle_Shutdown(void);


/**
\addtogroup group_common_api_core_functions
@{
*/

/******************************************************************************
* Function Name: CyBle_SoftReset
***************************************************************************//**
* 
* 	
*  This function resets the BLE Stack, including BLE sub-system hardware 
*  registers. BLE Stack transitions to idle mode. This function can be used to
*  reset the BLE Stack if the BLE Stack turns unresponsive due to incomplete 
*  transfers with the peer BLE device. 
* 
*  A call to this function results in the generation of CYBLE_EVT_STACK_ON event 
*  on successful BLE Stack Reset.
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes          		  |	Description
*   ------------          		  |	-----------
*   CYBLE_ERROR_OK        		  |	On successful operation
*   CYBLE_ERROR_INVALID_OPERATION | This error occurs if this function is invoked before invoking CyBle_StackInit function.
*     
******************************************************************************/
CYBLE_API_RESULT_T CyBle_SoftReset(void);


/******************************************************************************
* Function Name: CyBle_EnterLPM
***************************************************************************//**
* 
* 	
*  This function requests the underlying BLE modules such as BLE Controller, BLE
*  Host Stack and BLE Stack manger to enter into one of the supported low power
*  modes. Application should use this function to put Bluetooth Low Energy 
*  Sub-System (BLESS) to Low Power Mode (LPM).
* 
*  BLE Stack enters and exits low power modes based on its current state and 
*  hence the application should consider the BLE Stack LPM state before putting
*  the CPU or the overall device into LPM. This function attempts to set the
*  requested low power mode and if that is not possible, it tries to set the 
*  next higher low-power-mode. This behavior is due to the requirement that the
*  application will always try to use the lowest power mode when there is nothing
*  that it needs to process. Note that the CPU will not be able to access the 
*  BLESS registers when BLESS is in deep sleep mode.
* 
*  BLE Stack has the following power modes:
*   1. Active
*   2. Sleep (Low Power Mode)
*   3. DeepSleep with ECO Off (Low Power Mode)
*   4. Hibernate (Low Power Mode)
* 
*   Note that certain conditions may prevent BLE sub system from entering a 
*   particular low power mode.
*  
*   __Active Mode__
*
*   Bluetooth Low Energy Sub System (BLESS) has three sub-modes in Active mode:
*    1. Idle
*    2. Transmit Mode, and
*    3. Receive Mode
* 
*   These modes draw full current from the device and the CPU has full access to
*   its registers.
*   
*   __Sleep Mode__
*
*   The clock to the link layer engine and digital modem is gated and the 
*   (External Crystal Oscillator) ECO continues to run to maintain the link layer
*   timing. The application cannot enter sleep mode if a Transmit or Receive is 
*   in progress.
* 
*   __Deep Sleep with ECO Off Mode__
*
*   The ECO is stopped and Watch Crystal Oscillator (WCO) is used to maintain
*   link layer timing. All the regulators in the Radio Frequency (RF) transceiver
*   are turned off to reduce leakage current and BLESS logic is kept powered ON
*   from the System Resources Sub System (SRSS) deep-sleep regulator for retention
*   of current BLESS state information. This mode can be entered from either Idle 
*   (Active) or Sleep mode. It should be entered when the next scheduled activity 
*   instant in time domain is greater than the Deep Sleep total wakeup time 
*   (typically 2ms).
* 
*   NOTE: If application is using ECO as source of HFCLK for higher clock accuracy
*   and calls this API function to move BLESS to Deep Sleep mode then HFCLK accuracy and
*   frequency would be impacted as this API function switches HFCLK source from ECO to IMO.
*   On BLESS wakeup, the HFCLK source would be switched back to ECO.
*
*   Recommendation is that application turns on IMO and sets it as HFCLK source before 
*   calling this API function. Upon wakeup due to sources other than BLESS, application can turn
*   on ECO and switch HFCLK source to ECO. Pseudo code of recommendation is given below.
*
*   Pseudo Code:
*      Turn on IMO and switch HFCLK to IMO
*      CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
*      CySysPmDeepSleep();
*      If exit is not due to BLE and application need to use ECO 
*      then turn on ECO and switch HFCLK source to ECO.
*
*   __Hibernate mode__
*
*   The application layer should invoke this function with the Hibernate Mode 
*   option to put the BLE Stack in to hibernate mode. If this mode is set, the 
*   micro-controller can be put in to Hibernate Mode by the application layer. 
*   This mode ensures that BLE Sub-system is completely idle and no procedures
*   such ADV, SCAN and CONNECTION are active.
* 
*  The following table indicates the allowed sleep modes for the complete system
*  (BLE Sub-system and the micro-controller). Modes marked In 'X' are the allowed
*  combinations. The application layer should make sure that the invalid modes
*  are not entered in to:
*  
*   |BLE Stack LPM / PSoC4A-BLE LPM   |  Active   |  Sleep   |  DeepSleep  | Hibernate | 
*   |---------------------------------|-----------|----------|-------------|-----------|
*   |  Active                         |     X     |          |             |           |
*   |  Sleep                          |     X     |    X     |             |           |
*   |  DeepSleep (ECO OFF)            |     X     |    X     |      X      |           |
*   |  Hibernate                      |           |          |             |     X     | 
* 
*  The application layer is responsible for putting the BLE Sub-system and the 
*  micro-controller in to the desired sleep modes. Upon entering the requested
*  sleep mode combination, the BLE Sub-system and the micro-controller are woken
*  up by an interrupt every advertisement interval(in case of a GAP Peripheral)
*  or connection interval (in case of GAP Central). On wakeup, if the application
*  needs to transmit some data, appropriate function(s) including the Stack 
*  functions need to be invoked. This needs to be followed by a call to the 
*  function CyBle_ProcessEvents, which handles all pending transmit and receive
*  operations. The application can now put the complete system back in to one of
*  the sleep modes. The application should ensure that the above invalid states
*  are never encountered.
* 
*  Application shall also ensure that BLE Sub-system's low power entry and
*  low power exit interrupts are processed in realtime and not blocked. It is
*  recommended that BLE Sub-system interrupt should be of higher priority.
*  If BLE Sub-system interrupts are blocked for longer time ( > 200us ),
*  BLE Sub-system can violate Bluetooth specification timing for wakeup where ECO
*  is required to perform BLE radio operation. It can also result in race 
*  condition where BLE Stack waits for interrupt as ECO is not started correctly
*  and BLE Sub system enters in unknown state, BLE Stack gets stuck in busy loop.
* 
*  This is a blocking function. In process of entering in BLESS Deep Sleep Mode,
*  BLE Stack puts CPU in Sleep Mode to save power while polling for entry
*  indication to BLESS DSM. No event is generated on calling this function.
*  Based on the return code from this function, the application layer should 
*  decide on the sleep mode for the complete system. For example, if the return
*  code is CYBLE_BLESS_DEEPSLEEP, the application can choose to call system wide
*  DeepSleep mode function. 
* 
*  \param pwrMode: The power mode that the component is intended to 
*  enter. The allowed values are,
*  * CYBLE_BLESS_SLEEP
*  * CYBLE_BLESS_DEEPSLEEP
*  
* \return 
*  CYBLE_LP_MODE_T: The actual power mode that BLE stack is now set to. 
* 
******************************************************************************/
CYBLE_LP_MODE_T CyBle_EnterLPM(CYBLE_LP_MODE_T pwrMode);


/******************************************************************************
* Function Name: CyBle_ExitLPM
***************************************************************************//**
* 
*  Application can asynchronously wake up the BLE Stack from low power using
*  this function. The wake up is not performed for the entire chip. This is a
*  blocking call and returns when BLE Stack has come out of LPM, and in process
*  of waking up from BLESS Deep Sleep Mode, BLE Stack puts CPU in Sleep Mode to
*  save power while polling for wakeup indication from BLESS. No event is
*  generated on calling this function. It has no effect if it is invoked when
*  the BLE Stack is already in active mode.
* 
* \return 
* CYBLE_LP_MODE_T: The actual power mode that BLE stack is now set to. Expected
*                  return value is CYBLE_BLESS_ACTIVE.
* 
******************************************************************************/
CYBLE_LP_MODE_T CyBle_ExitLPM(void);


/******************************************************************************
* Function Name: CyBle_ProcessEvents
***************************************************************************//**
* 	
*  This function checks the internal task queue in the BLE Stack, and pending
*  operation of the BLE Stack, if any. This needs to be called at least once
*  every interval 't' where:
*   1. 't' is equal to connection interval or scan interval, whichever is
*       smaller, if the device is in GAP Central mode of operation, or
*   2. 't' is equal to connection interval or advertisement interval,
*       whichever is smaller, if the device is in GAP Peripheral mode
*       of operation. 
* 
*  On calling every interval 't', all pending operations of the BLE Stack are
*  processed. This is a blocking function and returns only after processing all
*  pending events of the BLE Stack Care should be taken to prevent this call
*  from any kind of starvation; on starvation, events may be dropped by the
*  stack. All the events generated will be propagated to higher layers of the
*  BLE Stack and to the Application layer only after making a call to this
*  function.
* 
*  Call to this function can wakeup BLESS from Low Power Mode, and in process
*  of waking up from BLESS Deep Sleep Mode, BLE Stack puts CPU in Sleep Mode to
*  save power while polling for wakeup indication from BLESS. This can occur if
*  the caller function has pending data or control transactions to be performed
*  in BLE Stack that need to be programmed to BLESS in CyBle_ProcessEvents() 
*  context and BLESS is in Low Power Mode.
* 
* \return 
*  None
* 
******************************************************************************/
void CyBle_ProcessEvents(void);


/******************************************************************************
* Function Name: CyBle_SetDeviceAddress
***************************************************************************//**
* 
* This function sets the Bluetooth device address into BLE Stack's memory.
* This address shall be used for all BLE procedures unless explicitly changed by application.
* The application layer needs to call this function every time an address change is required. 
* Bluetooth 4.1 Core specification [3.12] specifies that the Bluetooth device can change its
* private address periodically, with the period being decided by the
* application; there are no limits specified on this period. The application
* layer should maintain its own timers in order to do this.
*
* User should call 'CyBle_GapSetIdAddress' API function to set identity address if 'CyBle_SetDeviceAddress'
* API function is used to set public or random static address.
*  This is a blocking function. No event is generated on calling this function.
*  This API function will be obsolete in future.
* 
*  \param bdAddr: Bluetooth Device address retrieved from the BLE stack gets stored
*           to a variable pointed to by this pointer. The variable is of type
*           CYBLE_GAP_BD_ADDR_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_SetDeviceAddress(CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
* Function Name: CyBle_GetDeviceAddress
***************************************************************************//**
* 
*  This API function reads the BD device address from BLE Controller's memory. This
*  address shall be used for BLE procedures unless explicitly indicated by BLE
*  Host through HCI commands. This is a blocking function and it returns
*  immediately with the required value.
*         
*  \param bdAddr: Pointer to the CYBLE_GAP_BD_ADDR_T structure variable. It has two 
*           fields where,
*          * bdAddr.addr: Bluetooth Device address buffer that is populated with
*             the device address data from BLE stack.
*          * bdAddr.type: Caller function should fill the "address type" to
*             retrieve appropriate address.   
*          .
*          Caller function should use bdAddr.type = 0x00 to get the "Public
*          Device Address" which is currently set. \n
*          Caller function use bdAddr.type = 0x01 to get the "Random Device
*          Address" which is currently set.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER	 | On specifying NULL as input parameter.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GetDeviceAddress(CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
* Function Name: CyBle_GetRssi
***************************************************************************//**
* 
*  This function reads the recorded Received Signal Strength Indicator (RSSI) 
*  value for the last successfully received packet from the BLE radio 
*  sub-system. This is a blocking function. No event is generated on calling
*  this function.
* 
* \return
*  int8: The RSSI value of the responding device.
*
*   Information     | Description
*   -----------     | -----------
*   Range           | -85 <= N <= 5
*   Note            | The value is in dBm.
*     
******************************************************************************/
int8 CyBle_GetRssi(void);


/******************************************************************************
* Function Name: CyBle_GetTxPowerLevel
***************************************************************************//**
* 
*  This function reads the transmit power of the BLE radio for the given BLE
*  sub-system channel group. This is a blocking function. No event is generated
*  on calling this function.
*     
*  \param bleSsPwrLvl: Pointer to a variable of type CYBLE_BLESS_PWR_IN_DB_T where, 
*                * bleSsPwrLvl -> blePwrLevelInDbm 
*                   indicates Output Power level in dBm
*                   returned by the function.
*                * bleSsPwrLvl -> bleSsChId indicates
*                   Channel group for which power level
*                   is to be read. This needs to be set
*                   before calling the function. The
*                   value can be advertisement channels
*                   (CYBLE_LL_ADV_CH_TYPE) or data
*                   channels (CYBLE_LL_CONN_CH_TYPE). 
* 
*                   If bleSsPwrLvl->blePwrLevelInDbm is greater than 0dBm, then the
*                   power level is applicable to both advertisement and 
*                   connection channel.                  
*
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GetTxPowerLevel(CYBLE_BLESS_PWR_IN_DB_T *bleSsPwrLvl);


/******************************************************************************
* Function Name: CyBle_SetTxPowerLevel
***************************************************************************//**
* 
* 	
*  This function sets the transmit power of the BLE radio for given BLE 
*  sub-system channel group. This is a blocking function. No event is generated
*  on calling this function.
* 
*  \param bleSsPwrLvl: Pointer to a variable of type 'CYBLE_BLESS_PWR_IN_DB_T' where, 
*                * bleSsPwrLvl -> blePwrLevelInDbm indicates Output Power level
*                  in dBm to be set by the function. 
*                * bleSsPwrLvl -> bleSsChId indicates Channel group for which
*                  power level is to be set. The value can be advertisement
*                  channels (CYBLE_LL_ADV_CH_TYPE) or data channels 
*                  (CYBLE_LL_CONN_CH_TYPE).
* 
*   NOTE: The set power level is applicable to both advertisement and connection channel 
*         for the following scenarios 
*           - bleSsPwrLvl->blePwrLevelInDbm is greater than 0dB  
*           - Before calling this API function Tx power level is 3dB  
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*    Errors codes                    | Description
*    ------------                    | -----------
*    CYBLE_ERROR_OK                  | On successful operation.
*    CYBLE_ERROR_INVALID_PARAMETER   | On specifying NULL as input parameter.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_SetTxPowerLevel (CYBLE_BLESS_PWR_IN_DB_T *bleSsPwrLvl);


/******************************************************************************
* Function Name: CyBle_GetBleClockCfgParam
***************************************************************************//**
* 	
*  This function reads the clock configuration parameter of BLE sub-system. This
*  is a blocking function. No event is generated on calling this function. The
*  following parameters related to the BLE sub-system clock are set by this
*  function:
* 
*  __Sleep Clock accuracy__

*   Sleep clock accuracy (SCA) in PPM. This parameter indicates the sleep clock
*   accuracy in PPM as described in the following table. It is set in the BLE
*   Stack and is used for BLE Connection operation while creating LE connection
*   with the peer device.
* 
*     Sleep Clock Accuracy Enum Field       | PPM Range Translation (PPM)
*     -------------------------------       | ---------------------------
*     CYBLE_LL_SCA_251_TO_500_PPM			| 251 - 500
*     CYBLE_LL_SCA_151_TO_250_PPM			| 151 - 250
*     CYBLE_LL_SCA_101_TO_150_PPM			| 101 - 150
*     CYBLE_LL_SCA_076_TO_100_PPM			| 76 - 100
*     CYBLE_LL_SCA_051_TO_075_PPM			| 51 - 75
*     CYBLE_LL_SCA_031_TO_050_PPM			| 31 - 50
*     CYBLE_LL_SCA_021_TO_030_PPM			| 21 - 30
*     CYBLE_LL_SCA_000_TO_020_PPM			|  0 - 20
* 
*   Refer to Bluetooth Core Specification 4.1 Volume 6, Chapter 4.5.7 for more
*   details on how the SCA is used.
* 
*  __Link Layer clock divider__

*   This input decides the frequency of the clock to the link layer. A lower
*   clock frequency results in lower power consumption. Default clock frequency
*   for the operation is 24 MHz. BLESS supports 24 MHz, 12 MHz and 8 MHz clock
*   configurations. Based on the end application requirement (how frequent the 
*   communication is expected to be), this parameter needs to be set.
* 
*  __ecoXtalStartUpTime__
*   ECO startup time specifies the value in the unit of 62.5 us
*   (16 KHz clock cycles). This value is programmed in BLESS WAKE_UP config register,
*   to configure the wakeup time required by ECO.
*   Max value for ECO startup time field can be 79u units = (79 * 62.5) us
*
*  \param bleSsClockConfig: Pointer to a variable of type CYBLE_BLESS_CLK_CFG_PARAMS_T
*   to which the existing clock configuration is stored.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*    Errors codes                    | Description
*    ------------                    | -----------
*    CYBLE_ERROR_OK                  | On successful operation.
*    CYBLE_ERROR_INVALID_PARAMETER   | On specifying NULL as input parameter.
* 
******************************************************************************/   
CYBLE_API_RESULT_T CyBle_GetBleClockCfgParam 
                        (CYBLE_BLESS_CLK_CFG_PARAMS_T *bleSsClockConfig);


/******************************************************************************
* Function Name: CyBle_SetBleClockCfgParam
***************************************************************************//**
* 
* 	
*  This function sets the clock configuration parameter of BLE sub-system. This
*  is a blocking function. No event is generated on calling this function. The
*  following parameters related to the BLE sub-system clock are set by this
*  function:
* 
*  __Sleep Clock accuracy__

*   Sleep clock accuracy (SCA) in PPM. This parameter indicates the sleep clock
*   accuracy in PPM as described in the following table. It is set in the BLE
*   Stack and is used for BLE Connection operation while creating LE connection
*   with the peer device.
*
*     Sleep Clock Accuracy Enum Field       | PPM Range Translation (PPM)
*     -------------------------------       | ---------------------------
*     CYBLE_LL_SCA_251_TO_500_PPM			| 251 - 500
*     CYBLE_LL_SCA_151_TO_250_PPM			| 151 - 250
*     CYBLE_LL_SCA_101_TO_150_PPM			| 101 - 150
*     CYBLE_LL_SCA_076_TO_100_PPM			| 76 - 100
*     CYBLE_LL_SCA_051_TO_075_PPM			| 51 - 75
*     CYBLE_LL_SCA_031_TO_050_PPM			| 31 - 50
*     CYBLE_LL_SCA_021_TO_030_PPM			| 21 - 30
*     CYBLE_LL_SCA_000_TO_020_PPM			|  0 - 20
* 
*   Refer to Bluetooth Core Specification 4.1 Volume 6, Chapter 4.5.7 for more
*   details on how the SCA is used.
* 
*  __Link Layer clock divider__

*   This input decides the frequency of the clock to the link layer. A lower
*   clock frequency results in lower power consumption. Default clock frequency
*   for the operation is 24MHz. BLESS supports 24MHz, 12MHz and 8MHz clock
*   configurations. Based on the end application requirement (how frequent the 
*   communication is expected to be), this parameter needs to be set.
* 
*  __ecoXtalStartUpTime__
*   ECO startup time specifies the value in the unit of 62.5us
*   (16KHz clock cycles). This value is programmed in BLESS WAKE_UP config register,
*   to configure the wakeup time required by ECO.
*   Max value for ECO startup time field can be 79u units = (79 * 62.5) us
*
*  \param bleSsClockConfig: Pointer to a variable of type CYBLE_BLESS_CLK_CFG_PARAMS_T
*                     from which the existing clock configuration is taken.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*    Errors codes	                 | Description
*    ------------                    | -----------
*    CYBLE_ERROR_OK                  | On successful operation.
*    CYBLE_ERROR_INVALID_PARAMETER   | On specifying NULL as input parameter.
*   
******************************************************************************/ 
CYBLE_API_RESULT_T CyBle_SetBleClockCfgParam 
                        (CYBLE_BLESS_CLK_CFG_PARAMS_T *bleSsClockConfig); 


/******************************************************************************
* Function Name: CyBle_GenerateRandomNumber
***************************************************************************//**
* 
*  This function generates 8-byte random number which complies with pseudo random
*  number generation in accordance with [FIPS PUB 140-2]. Random number
*  generation function is used during security procedure documented in Bluetooth
*  4.1 core specification, Volume 3, Part H. 
*  
*  This is a blocking function. No event is generated on calling this function.
*     
*  \param randomNumber: Pointer to a buffer of size 8 bytes in which the generated
*  random number gets stored.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*    Errors codes                    | Description
*    ------------                    | -----------
*    CYBLE_ERROR_OK                  | On successful operation.
*    CYBLE_ERROR_INVALID_PARAMETER   | On specifying NULL as input parameter.
* 
******************************************************************************/ 
CYBLE_API_RESULT_T CyBle_GenerateRandomNumber (uint8 *randomNumber);


/******************************************************************************
* Function Name: CyBle_AesEncrypt
***************************************************************************//**
* 
*  This function uses BLE sub-system AES engine to encrypt 128-bit of plain text
*  using the given AES key. The output of AES processing is copied to 
*  encryptedData buffer. Refer Bluetooth 4.1 core specification, Volume 3,
*  Part H, section 2.2 for more details on usage of AES key.
* 
*  This is a blocking function. No event is generated on calling this function.
* 
*  \param plainData: Pointer to the data containing plain text (128-bit) that is to be encrypted.
* 
*  \param aesKey: Pointer to the AES Key (128-bit) that is to be used for AES encryption.
* 
*  \param encryptedData: Pointer to the encrypted data (128-bit) that is output of AES
*                  module for given plainData and aesKey.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
* 
*    Errors codes                    | Description
*    ------------                    | -----------
*    CYBLE_ERROR_OK                  | On successful operation
*    CYBLE_ERROR_INVALID_PARAMETER   | On specifying NULL as input parameter
*
*     
******************************************************************************/ 
CYBLE_API_RESULT_T CyBle_AesEncrypt 
            (uint8 *plainData, uint8 *aesKey, uint8 *encryptedData);   


/******************************************************************************
* Function Name: CyBle_SetCeLengthParam
***************************************************************************//**
* 
*  This function sets the connection event duration related parameters that can
*  result in extension or truncation of LE connection event based on more data
*  (mdBit) bit status and 'ceLength' duration. Refer Bluetooth 4.1 core
*  specification, Volume 6, Part B, section 4.5 for more details on connection
*  states of BLE Link Layer.
* 
*  This is a blocking function. No event is generated on calling this function.
* 
*  BLE Stack uses the BLESS hardware (AES module) to encrypt/decrypt the data.
*  BLESS must be initialized before using this function. This function can safely
*  be used by the application in "single thread/task system" which is the case
*  with the current implementation of the BLE Stack. For multitasking systems,
*  this function must be used within the BLE task to ensure atomic operation.
*     
*  \param bdHandle: Peer device bdHandle.
* 
*  \param mdBit: 'More Data' bit to select more number of data packets in BLE Stack
*          buffer. A value of 0x01 indicates extension and a value of 0x00
*          indicates truncation.
* 
*  \param ceLength: CE length of connection event that can extend the connection event.
*             Details on this parameter are as given below:
*             - Value Range = 0x0000 to 0xFFFF
*             - Time Calculation = N x 0.625 ms
*             - Time Range = 0 ms to 40.959 ms
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*    Errors codes                    | Description
*    ------------                    | -----------
*    CYBLE_ERROR_OK                  | On successful operation
*    CYBLE_ERROR_INVALID_PARAMETER   | One of the input parameters is invalid
*    CYBLE_ERROR_NO_CONNECTION       | When controller can't find active connection using given bdHandle
*    CYBLE_ERROR_NO_DEVICE_ENTITY    | Invalid bdHandle or LE connection doesn't exist for link identified by bdHandle.

******************************************************************************/
CYBLE_API_RESULT_T CyBle_SetCeLengthParam 
            (uint8 bdHandle, uint8 mdBit, uint16 ceLength); 


/******************************************************************************
* Function Name: CyBle_WriteAuthPayloadTimeout
***************************************************************************//**
* 
*  This function sets the Authentication Payload timeout in BLE Controller for
*  LE_PING feature. Refer Bluetooth 4.1 core specification, Volume 6, Part B,
*  section 4.6.5 for LE Ping operation.
* 
*  This is a blocking function. No event is generated on calling this function.
*     
*  \param bdHandle: Peer device handle.
* 
*  \param authPayloadTimeout: Variable containing authentication timeout value to be
*                      written to BLE Controller. Details on this parameter are
*                      as given below:
*                      - Value Range = 0x0001 to 0xFFFF
*                      - Default Value (N) = 3000 (30 seconds)
*                      - Time Calculation = N x 10 ms
*                      - Time Range = 10 ms to 655,350 ms
*
*  Note: The time at which PING packet transmitted over the air is determined from the 
*        following formula (only in case of SlaveLatency is enabled)
*        (authPayloadTimeout - (4 * ((1 + SlaveLatency) * Connection Interval)))
*						
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | One of the input parameters is invalid
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted
*   CYBLE_ERROR_NO_CONNECTION        | When controller can't find active connection using given bdHandle
*   CYBLE_ERROR_NO_DEVICE_ENTITY     | Invalid bdHandle or LE connection doesn't exist for link identified by bdHandle.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_WriteAuthPayloadTimeout 
        (
            uint8 bdHandle, 
            uint16 authPayloadTimeout
        );


/******************************************************************************
* Function Name: CyBle_ReadAuthPayloadTimeout
***************************************************************************//**
* 
*  This function reads the Authentication Payload timeout set in BLE Controller
*  for LE_PING feature Refer Bluetooth 4.1 core specification, Volume 6, Part B,
*  section 4.6.5 for LE Ping operation.
* 
*  This is a blocking function. No event is generated on calling this function.
*     
*  \param bdHandle: Peer device handle
*  \param authPayloadTimeout: Pointer to a variable to which authentication timeout
*                       value, read from BLE Controller, is written.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | One of the input parameters is invalid.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted.
*   CYBLE_ERROR_NO_CONNECTION        | When controller can't find active connection using given bdHandle
*   CYBLE_ERROR_NO_DEVICE_ENTITY     | Invalid bdHandle or LE connection doesn't exist for link identified by bdHandle.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_ReadAuthPayloadTimeout 
        (
            uint8 bdHandle,
            uint16 *authPayloadTimeout
        );


/******************************************************************************
* Function Name: CyBle_GetStackLibraryVersion
***************************************************************************//**
* 
*  This function retrieves the version information of the BLE Stack library. This
*  is a blocking function. No event is generated on calling this function.
*     
* 	
*  \param stackVersion: Pointer to a variable of type CYBLE_STACK_LIB_VERSION_T
*                 containing the version information of the CYBLE Stack library.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | stackVersion is NULL.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GetStackLibraryVersion(CYBLE_STACK_LIB_VERSION_T*   stackVersion);
/******************************************************************************
* Function Name: CyBle_IsStackIdle
***************************************************************************//**
* 
*  This function is used to check BLE stack is idle or not. This API function returns CYBLE_ERROR_OK
*  if BLE Stack is idle. This function returns CYBLE_ERROR_STACK_BUSY if L2CAP TX data is queued 
*  for transmission, or any tasks are pending or hardware is busy. This function will not consider 
*  Rx path to decide stack is idle or not.
*
*  Note:
*  This API function should not be called from BLE Stack callback context.
*  
*  Use case example: Application can check before shut-down, BLE stack is idle or not.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | If Stack is idle
*   CYBLE_ERROR_STACK_BUSY           | If Stack is not idle.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_IsStackIdle(void);

/******************************************************************************
* Function Name: CyBle_GetBleSsState
***************************************************************************//**
* 
*  This function gets the BLE Subsystem's current operational mode. This state can be
*  used to manage system level power modes based on return value.
* 
*  \return
*  CYBLE_BLESS_STATE_T bleStackMode: CYBLE_BLESS_STATE_T has one of the following modes
*
*  <table>
*  <tr>
*    <th>BLE Stack Mode</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_BLESS_STATE_ACTIVE</td>
*    <td>BLE Sub System is in active mode, CPU can be in active mode or sleep mode.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_BLESS_STATE_EVENT_CLOSE</td>
*    <td>BLE Sub System radio and Link Layer hardware finishes Tx/Rx. After this state application can try 
*        putting BLE to Deep Sleep State to save power in rest of the BLE transmission event.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_BLESS_STATE_SLEEP</td>
*    <td>BLE Sub System is in sleep mode, CPU can be in sleep mode.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_BLESS_STATE_ECO_ON</td>
*    <td>BLE Sub System is in process of wakeup from Deep Sleep Mode and ECO(XTAL) is turned on. 
*        CPU can be put in Deep Sleep Mode.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_BLESS_STATE_ECO_STABLE</td>
*    <td>BLE Sub System is in process of wakeup from Deep Sleep Mode and ECO(XTAL) is stable. 
*        CPU can be put in sleep mode.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_BLESS_STATE_DEEPSLEEP</td>
*    <td>BLE Sub System is in Deep Sleep Mode. CPU can be put in Deep Sleep Mode.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_BLESS_STATE_HIBERNATE</td>
*    <td>BLE Sub System is in Hibernate Mode. CPU can be put in Deep Sleep Mode.</td>
*  </tr>
*  </table>
* 
\image html GetBleSsState_State_Diagram.bmp
\image rtf GetBleSsState_State_Diagram.bmp
******************************************************************************/
CYBLE_BLESS_STATE_T CyBle_GetBleSsState(void);

/******************************************************************************
* Function Name: CyBle_AesCcmInit
***************************************************************************//**
* 
*  This function initializes the clocks and registers needed to used AEC 
*  CCM encryption / decryption functionality without initializing the complete BLE Stack.
*  This function must be called before calling CyBle_AesCcmEncrypt and/or CyBle_AesCcmDecrypt
*  function. This is a blocking function. No event is generated on calling this function.
* 
*  \return
*  None
* 
******************************************************************************/
void CyBle_AesCcmInit(void);

/******************************************************************************
* Function Name: CyBle_AesCcmEncrypt
***************************************************************************//**
* 
*  This function encrypts the given data. This function can only be invoked after
*  invoking 'CyBle_AesCcmInit' function. This is a blocking function. No event is
*  generated on calling this function.
* 
* 	
*  \param key: Pointer to an array of bytes holding the key. The array length to be
* 		allocated by the application should be 16 bytes.
*  \param nonce:	Pointer to an array of bytes. The array length to be allocated by the
*  		 application is 13 Bytes.
*  \param in_data: Pointer to an array of bytes to be encrypted. Size of the array
*  			should be equal to the value of 'length' parameter.
*  \param length: Length of the data to be encrypted, in Bytes. Valid value range
* 			is 1 to 27.
*  \param out_data: Pointer to an array of size 'length' where the encrypted data
*  			is stored.
*  \param out_mic: Pointer to an array of bytes (4 Bytes) to store the MIC value
*  			generated during encryption.
* 
*  \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                   |   Description
*   ------------                   |   -----------
*   CYBLE_ERROR_OK                 |   On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER  |   One of the inputs is a null pointer or the 'length' value is invalid	
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_AesCcmEncrypt(
    uint8 *key,
    uint8 *nonce,
    uint8 *in_data,
    uint8 length,
    uint8 *out_data,
	uint8 *out_mic
	);

/******************************************************************************
* Function Name: CyBle_AesCcmDecrypt
***************************************************************************//**
* 
*  This function decrypts the given data. This function can only be invoked after
*  invoking 'CyBle_AesCcmInit' function. This is a blocking function. No event is
*  generated on calling this function.
* 
* 	
*  \param key: Pointer to an array of bytes holding the key. The array length to be
* 		allocated by the application should be 16 bytes.
*  \param nonce:	Pointer to an array of bytes. The array length to be allocated by the
*  		 application is 13 Bytes.
*  \param in_data: Pointer to an array of bytes to be decrypted. Size of the array
*  			should be equal to the value of 'length' parameter.
*  \param length: Length of the data to be decrypted, in Bytes. Valid value range
* 			is 1 to 27.
*  \param out_data: Pointer to an array of size 'length' where the decrypted data
*  			is stored.
*  \param in_mic: Pointer to an array of bytes (4 Bytes) to provide the MIC value
* 			generated during encryption.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>One of the inputs is a null pointer or the 'length' value is invalid</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MIC_AUTH_FAILED</td>
*    <td>Data decryption has been done successfully but MIC based authorization check has failed. This error can
* 		 be ignored if MIC based authorization was not intended.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_AesCcmDecrypt(
    uint8 *key,
    uint8 *nonce,
    uint8 *in_data,
    uint8 length,
    uint8 *out_data,
	uint8 *in_mic
	);	
/******************************************************************************
* Function Name: CyBle_GenerateAesCmac
***************************************************************************//**
* 
*  This API function enables the application to generate the AES CMAC of 16 bytes, for given variable 
*  length message and CMAC Key.
    
*  After this API function call, if the return value is CYBLE_ERROR_OK, 
*  then callback given in the input parameter is called when the cmac generation is completed. 
*  Once this callback is called, check the output parameter cmac to get the generated cmac value.
* 	
*  \param cmacGenParam: pointer to structure containing parameters required for AES CMAC Generation.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>cmacGenParam is NULL or key is NULL or
*        mac, output parameter is NULL or
*        appl_callback is NULL or
*        if buffer is NULL when size is greater than zero
*	 </td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_STACK_INTERNAL</td>
*    <td>An error occurred in BLE stack</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GenerateAesCmac(CYBLE_AES_CMAC_GENERATE_PARAM_T *cmacGenParam);

/******************************************************************************
* Function Name: CyBle_SetAppEventMask
***************************************************************************//**
* 
*  This API function enables the application to Mask which Events user wants to receive 
*	
*    Currently supporting maskable events 
*		CYBLE_EVT_GAP_CONN_ESTB
*		CYBLE_EVT_GAP_SCAN_REQ_RECVD
*
*  \param UserEventMask: User Event Mask
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>UserEventMask is ZERO</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_SetAppEventMask(uint32 UserEventMask);


/******************************************************************************
* Function Name: CyBle_RegisterBlessInterruptCallback
***************************************************************************//**
* 
*   This API function will registers the callback function for BLESS Events and sets 
*   Event mask which BLESS Events user wants to receive 
*
*    Currently supporting events 
*		CYBLE_ISR_BLESS_CONN_CLOSE_CE 
*       CYBLE_ISR_BLESS_ADV_CLOSE
*
*
*	Note:
*		Application has to pay utmost care about not doing delayed processing
*		in event handler as the registered callback will get called from BLESS 
*		Interrupt Service Routine. 
*		
*		Application can set/clear flag which can be used for further processing
*		outside of the ISR context.
*
*		Event received through callback represents events received
*		as a whole at that point i.e., application won't receive individual
*		events.
* 		
*  \param BlessEventParams: pointer to structure CYBLE_BLESS_EVENT_PARAM_T
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>If NULL passed</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_RegisterBlessInterruptCallback
	(
		CYBLE_BLESS_EVENT_PARAM_T *BlessEventParams
	);


/******************************************************************************
* Function Name: CyBle_SetTxGainMode
***************************************************************************//**
* 
*  This function configures the Tx gain mode for BLESS radio for Tx operation. 
* 	
*  \param bleSsGainMode: Gain mode setting for the output power
* 
*   BLESS RD Gain Mode            | Description
* 	------------------            | -----------
*   CYBLE_BLESS_NORMAL_GAIN_MODE  | 0x00u - BLESS Normal Gain Mode Tx Pwr Range -18dBm to 0 dBm Normal Rx Sensitivity
*   CYBLE_BLESS_HIGH_GAIN_MODE    | 0x01u - BLESS High Gain Mode Tx Pwr Range -18dBm to 3 dBm 3 dBm Additional Rx Sensitivity
*  
*  \return
*  none
*
******************************************************************************/

void CyBle_SetTxGainMode(uint8 bleSsGainMode);


/******************************************************************************
* Function Name: CyBle_SetRxGainMode
***************************************************************************//**
* 
*  This function configures the Rx gain mode to select Higher or Lower Receive
*  Sensitivity for BLESS radio.
* 	
*  \param bleSsGainMode: Gain mode setting for the Receiver Sensitivity.
* 
*   BLESS RD Gain Mode            | Description
* 	------------------            | -----------
*   CYBLE_BLESS_NORMAL_GAIN_MODE  |	0x00u - BLESS Normal Gain Mode. Rx Sensitivity of -89dBm.
*   CYBLE_BLESS_HIGH_GAIN_MODE    | 0x01u - BLESS High Gain Mode. Rx Sensitivity of -91dBm.
*  
*  \return
*  none
*
******************************************************************************/
void CyBle_SetRxGainMode(uint8 bleSsGainMode);


/******************************************************************************
* Function Name: CyBle_SetSlaveLatencyMode
***************************************************************************//**
*
* This function overrides the default BLE Stack behavior for LE connection that
* is established with non zero slave latency. This API function can be used by application
* to force set quick transmission for a link related to specified 'bdHandle' during
* slave latency period. 
* 
* If the force quick transmit option is selected, the device will always respond
* all the Connection Events (CE) ignoring the slave latency. To re-enable BLE Stack
* control quick transmit behavior application should call this API function with force 
* quick transmit option set to zero.
*
* BLE Stack Control Policy: BLE Stack enables quick transmission whenever any
* data packet is queued in link layer. Upon successful transmission of data packet
* BLE Stack resets the quick transmit to enable latency for power save.
*
* BLE Stack also enables quick transmit whenever any real time LL Control PDU
* is received. Once the acknowledgment of the PDU is processed the quick transmit
* option is reset.
*
*
* \param bdHandle: bdHandle identifying LE connection for which force quick transmit
*                  option is to be set or reset.
*
*  \param setForceQuickTransmit: This parameter is used to set or reset the force quick transmit
*                                configuration in BLE Stack.\n
*  * '1': Set the quick transmit behavior, it gets set immediately and disables
*    over the air slave latency . This quick transmit setting remains true until
*    application gives control to BLE Stack for controlling quick transmit bit.
*  * '0': Reset the force quick transmit behavior in BLESS to allow BLE Stack to control
*    quick transmit behavior when slave latency is applied.
*
* \return
* CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                 | Description
*  ------------                 | -----------
*  CYBLE_ERROR_OK               | On successful operation.
*  CYBLE_ERROR_NO_CONNECTION    | When controller can't find active connection using given bdHandle
*  CYBLE_ERROR_NO_DEVICE_ENTITY | Invalid bdHandle or LE connection doesn't exist for link identified by bdHandle.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_SetSlaveLatencyMode(uint8 bdHandle, uint8 setForceQuickTransmit);


/******************************************************************************
* Function Name: CyBle_SetSeedForRandomGenerator
***************************************************************************//**
*
* As per security specification of Bluetooth, BLE stack uses pseudo random number 
* generator (Bluetooth core specification 4.2, Vol.2 Part H, Sec-2). Application 
* can generate random number using API function CyBle_GenerateRandomNumber. Seed for 
* random number generator with better entropy for randomness can be provided by 
* application using this API function. This function sets application specific seed for 
* DRBG (Deterministic Random number generator).
*  
*  \param seed: Seed for DRBG. Setting the seed to zero is functionally 
*               equivalent to not setting the application specific seed.
*
* \return
*  None.
*
******************************************************************************/
void CyBle_SetSeedForRandomGenerator(uint32 seed);


/******************************************************************************
* Function Name: CyBle_IsLLControlProcPending
***************************************************************************//**
*
* This function checks the Link Layer state for any pending real time
* control (LL_CHANNEL_MAP, LL_CONNECTION_UPDATE) procedure. When any such 
* procedure is pending in Link layer busy state it is indicated by Link Layer.
*
* Application using specific GAP API functions or L2CAP API functions that can result
* in initiation of real time procedures such as LL_CHANNEL_MAP, LL_CONNECTION_UPDATE
* can check the state of Link Layer to avoid any such rejection from BLE Stack.
*
* BLE Stack can reject the new request 
* If any LL control procedure is pending for completion this API function will return 
* CYBLE_ERROR_CONTROLLER_BUSY.
*
* \return
* CYBLE_API_RESULT_T: Return value indicates the Link Layer status for any pending
* real time procedure.
*
*  Errors codes                     | Description
*  ------------                     | -----------
*  CYBLE_ERROR_OK                   | Link Layer is Free.
*  CYBLE_ERROR_CONTROLLER_BUSY      | Link Layer Control Procedure is pending, no new LL control procedure can be initiated.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_IsLLControlProcPending(void);

/******************************************************************************
* Function Name: CyBle_StartTransmitterTest
***************************************************************************//**
* 
*  This API function Programs direct test mode TX test command parameters.
* 	
*  \param TransmitterTestParams: pointer to structure CYBLE_TRANSMITTER_TEST_PARAMS_T.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>TransmitterTestParams is NULL </td>
*  </tr>
*  </table>
* 
******************************************************************************/

CYBLE_API_RESULT_T CyBle_StartTransmitterTest
     (
          CYBLE_TRANSMITTER_TEST_PARAMS_T *TransmitterTestParams
     );

/******************************************************************************
* Function Name: CyBle_StartReceiverTest
***************************************************************************//**
* 
*  This API function Programs direct test mode RX test command parameters.
*  
*  \param RxFreq: Frequency for reception.
*                 N = (F – 2402)/2  Range: 0x00 – 0x27. 
                  Frequency Range : 2402 MHz to 2480 MHz.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>RxFreq is Out of Range </td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StartReceiverTest
     (
          uint8 RxFreq
     );

/******************************************************************************
* Function Name: CyBle_TestEnd
***************************************************************************//**
* 
*  This API function Programs the direct test end command to the hardware, it reads number
*  of successful packtes received from ll hardware.
*  
*  \param PacketCount: Pointer to a buffer of size 16 bytes in which the received 
*                      number of successful packets will be stored.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>PacketCount is NULL </td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_TestEnd
     (
          uint16 *PacketCount
     );

/******************************************************************************
* Function Name: CyBle_HciSendPacket
***************************************************************************//**
* 
*  This API function Sends HCI packet to Controller
*  
*  User should deallocate memory buffer passed as an input parameter,
*  after receiving an Event from the controller for command packet and 
*  after recieving Number Of Completed Packets event for data packet transmitted.  
*
*  \param HciPktParams: pointer to structure CYBLE_HCI_PKT_PARAMS_T.
* 
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>HciCmdParams is NULL </td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>Operation not permitted </td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed </td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HciSendPacket
	(
	     CYBLE_HCI_PKT_PARAMS_T *HciPktParams
	);

/** @} */

/** \cond IGNORE */

/******************************************************************************
* Function Name: CyBle_EnablePrivacyFeature
*******************************************************************************
*
* This function Enables Privacy features in
* controller. When this function is not called in the application, 
* Privacy features gets disabled and memory space used in the controller
* is relinquished.
*
* \return
*    None.
*
******************************************************************************/
void CyBle_EnablePrivacyFeature(void);


/******************************************************************************
* Function Name: CyBle_EnableDleFeature
*******************************************************************************
*
* This function Enables Data Length Extension features in
* controller. When this function is not called in the application, 
* DLE features gets disabled and memory space used in the controller
* is relinquished.
*
* \return
*    None.
*
******************************************************************************/
void CyBle_EnableDleFeature(void);

/******************************************************************************
* Function Name: CyBle_EnableDefaultDevicePrivacy
*******************************************************************************
*
* This function Enables Default device privacy i.e., loose privacy
* implementation.
*
* \return
*    None.
*
******************************************************************************/
void CyBle_EnableDefaultDevicePrivacy(void);


/******************************************************************************
* Function Name: CyBle_HciUartTransportEnable
*******************************************************************************
*
* This function Enables HCI UART transport
*
* \return
*    None.
*
******************************************************************************/

void CyBle_HciUartTransportEnable(void);

/******************************************************************************
* Function Name: CyBle_HciSoftTransportEnable
*******************************************************************************
*
* This function Enables HCI Software Transport
*
* \return
*    None.
*
******************************************************************************/

void CyBle_HciSoftTransportEnable(void);

/** \endcond */


#endif /* CYBLE_H_ */
/*EOF*/
