/***************************************************************************//**
* \file CYBLE_Stack.h
* \version 2.30
* 
* \brief
*  This file contains declaration of public BLE APIs other than those covered by
*  GAP, GATT and L2CAP specific APIs. Also specified are the defines, constants
*  and data structures required for the APIs.
* 
* Related Document:
*  BLE Standard Spec - CoreV4.1, CSS, CSAs, ESR05, ESR06
* 
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#ifndef CY_BLE_CYBLE_STACK_H
#define CY_BLE_CYBLE_STACK_H


/***************************************
* Common stack includes
***************************************/

#include "cytypes.h"


/***************************************
* Constants
***************************************/

#define CYBLE_STACK_STATE_BUSY		   	0x01u

#define CYBLE_STACK_STATE_FREE		   	0x00u

/***************************************
* Retention data definition
***************************************/

/* Bluetooth Device Address size */
#define CYBLE_GAP_BD_ADDR_SIZE			                      (0x06u)

/***************************************
*  Memory pool configuration data defines
***************************************/

/* Size of internal data buffer structures */
#define CYBLE_STACK_BUFFER_MGR_UTIL_RAM_SZ                    (0x1Cu)

/* Size of the heap when GATT MTU, L2CAP MTU, MPS sizes are specified as 23 Bytes */
#define CYBLE_DEFAULT_RAM_SIZE_SOC				(16u + 1024u + 1224u)

/* Size of the heap when the BLE Stack is built in HCI mode */
#define CYBLE_DEFAULT_RAM_SIZE_HCI				        (16u + 1168u)

#define CYBLE_MEM_EXT_SZ                                          (0x08u)
#define CYBLE_L2CAP_HDR_SZ                                        (0x04u)

/* Buffer size needed for L2cap PSM and CBFC channels */
#define CYBLE_L2CAP_PSM_SIZE                                    (40u)
#define CYBLE_L2CAP_CBFC_CHANNEL_SIZE                           (64u)


/* Data Buffer Pool identifiers to support configurable parameters for L2CAP and
 * GATT in BLE Stack 
 * These data buffer pools need to be configured during BLE Stack
 * initialization. */

/* Data Buffer index for ATT/GATT Configured MTU Size */
#define CYBLE_STACK_APP_POOL_1_SZ            	                   	0x00u

/* Data Buffer index for GATT Server maximum attribute size */
#define CYBLE_STACK_APP_POOL_2_SZ	                               	0x01u

/* Data Buffer index for L2CAP configuration for number of PSM Channels
 * */
#define CYBLE_STACK_APP_POOL_3_SZ		                           	0x02u

/* Data Buffer index for L2CAP configuration for number of CBFC Channels
 * */
#define CYBLE_STACK_APP_POOL_4_SZ                          			0x03u

/* Data Buffer index for L2CAP configured MTU Size */
#define CYBLE_STACK_APP_POOL_5_SZ                                   0x04u

/* Data Buffer index for L2CAP configured MPS Size */
#define CYBLE_STACK_APP_POOL_6_SZ                                   0x05u

/* Maximum Application Pool  */
#define CYBLE_STACK_APP_MIN_POOL                                   (CYBLE_STACK_APP_POOL_6_SZ + 1)

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
#define CYBLE_GATT_MAX_ATTR_LEN_MAX_VAL                          (0xFFD0u)

#define CYBLE_L2CAP_MTU_MIN_VALUE                                  (0x17u)

/* Max L2CAP MTU or MPS size can be of 0xFFFF, but Stack has limitation
 * on buffer creation as it requires additional 8 bytes and 
 * L2CAP header size (4 bytes)
 * */
#define CYBLE_L2CAP_MTU_MAX_VALUE                                (0xFFD0u)

#define CYBLE_L2CAP_MPS_MIN_VALUE                CYBLE_L2CAP_MTU_MIN_VALUE

#define CYBLE_L2CAP_MPS_MAX_VALUE                CYBLE_L2CAP_MTU_MAX_VALUE

#define CYBLE_STACK_FLASH_STORAGE_SIZE           (0x09u + (0x59u * CYBLE_GAP_MAX_BONDED_DEVICE))


/***************************************
* Deprecated definitions
***************************************/

/* Event indicating connection update complete on the GAP Central.
	Do not use this for new designs. Use CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE
	instead */
#define CYBLE_EVT_GAPC_CONNECTION_UPDATE_COMPLETE	CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE

/***************************************
* Enumerated Types and Structs
***************************************/

/**
 \addtogroup group_common_api_definitions
 @{
*/	
	
/** event callback function prototype to receive events from stack */
typedef void (*CYBLE_APP_CB_T)(uint8 event, void* evParam);

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
       Part D, section 1.3. This event will be received only if there is an error. */
    CYBLE_EVT_HCI_STATUS,

    /** This event is triggered by host stack if BLE stack is busy or not. 
       Event Parameter corresponding to this event will indicate the state of BLE stack's internal protocol buffers
       for the application to safely initiate data transactions (GATT, GAP Security, and L2CAP transactions)
       with the peer BLE device.

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
        **/
    CYBLE_EVT_STACK_BUSY_STATUS,

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
    	'CYBLE_EVT_GAP_DEVICE_DISCONNECTED' is passed to application.      
	Event parameter is a pointer to a structure of type CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T. */
    CYBLE_EVT_GAP_DEVICE_CONNECTED,

	/** Disconnected from remote device or failed to establish connection. Parameter returned with the event 
	contains pointer to the reason for disconnection, which is of type uint8. For details refer
	core spec 4.2, vol2, part D */
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

    /* Range for GATT events - 0x40 to 6F */

    /** The event is received by the Client when the Server cannot perform the requested 
       operation and sends out an error response. Event parameter is a pointer to a structure
       of type CYBLE_GATTC_ERR_RSP_PARAM_T. */
    CYBLE_EVT_GATTC_ERROR_RSP = 0x40u,

    /** This event is generated at the GAP Peripheral end after connection is completed with peer Central device.
    	For GAP Central device, this event is generated as in acknowledgment of receiving this event successfully
    	by BLE Controller. Once connection is done, no more event is required but if fails to establish connection,
    	'CYBLE_EVT_GATT_DISCONNECT_IND' is passed to application.      
	Event parameter is a pointer to a structure of type CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T. */
    CYBLE_EVT_GATT_CONNECT_IND,

    /** GATT is disconnected. Nothing is returned as part of the event parameter. */
    CYBLE_EVT_GATT_DISCONNECT_IND,

    /** 'MTU Exchange Request' received from GATT client device. Event parameter
       contains the MTU size of type CYBLE_GATT_XCHG_MTU_PARAM_T. */
    CYBLE_EVT_GATTS_XCNHG_MTU_REQ,

    /** 'MTU Exchange Response' received from server device. Event parameter is a
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
       only if there is no error condition provided by application. Incase of error condition triggered
       during stack validation, partial write will occur. Write will be cancelled from that handle where 
       error has occurred and error response corresponding to that handle will be sent to remote.
       If at any point of time 'CYBLE_GATT_EXECUTE_WRITE_CANCEL_FLAG' is received in 
       execWriteFlag fields of 'CYBLE_GATTS_EXEC_WRITE_REQ_T' structure, then all previous 
       writes are cancelled. For execute cancel scenario, all elements of 
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
       only if application has called CyBle_GattcStopCmd API. 
       Event parameters shall be ignored */
    CYBLE_EVT_GATTC_STOP_CMD_COMPLETE,

    /** Event parameters for characteristic read value access event generated by
       BLE Stack upon an access of Characteristic value read for the
       characteristic definition which has CYBLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT
       property set. */
    CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ,

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
       channel. Event parameter is of type 'CYBLE_L2CAP_CBFC_DATA_WRITE_PARAM_T' 
       This event will be deprecated in future. It is only kept for backward compatibility.
       It is not recommended to be used by new design */
    CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND,

    /* Range for future use - 0x80 to 0xFF */

    /** This event is used to inform application that flash write is pending
       Stack internal data structures are modified and require backup .
       */
    CYBLE_EVT_PENDING_FLASH_WRITE = 0xFA,

    /** LE PING Authentication Timeout Event to indicate that peer device has not responded
       with the valid MIC packet within the application configured ping authentication time. */
    CYBLE_EVT_LE_PING_AUTH_TIMEOUT = 0xFB,

	/** Maximum value of CYBLE_EVENT_T type */
    CYBLE_EVT_MAX = 0xFF

}CYBLE_EVENT_T;

/** @} */

/**
 \addtogroup group_common_api_definitions
 @{
*/

/** Common error codes received as API result */
typedef enum
{
    /** No Error occurred */
    CYBLE_ERROR_OK = 0x00u,
    
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

    /**L2CAP error codes*/
    
    /** L2CAP PSM encoding is incorrect */
    CYBLE_ERROR_L2CAP_PSM_WRONG_ENCODING = 0x0Du,
    
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
    CYBLE_ERROR_DEVICE_ALREADY_EXISTS = 0x27u,
    
    /** Write to flash is not permitted */
    CYBLE_ERROR_FLASH_WRITE_NOT_PERMITED = 0x28u,

	/** MIC Authentication failure */
	CYBLE_ERROR_MIC_AUTH_FAILED = 0x29u,	
    
    /** All other errors not covered in the above list map to this error code */
    CYBLE_ERROR_MAX = 0xFFu,

    /* Profile level API_RESULT codes will be here */
    /** Characteristic notifications disabled */
    CYBLE_ERROR_NTF_DISABLED,

    /** Characteristic indications disabled */
    CYBLE_ERROR_IND_DISABLED,

    /** \cond IGNORE */    
    CYBLE_ERROR_CHAR_IS_NOT_DISCOVERED,
    /** \endcond */

    /** The state is not valid for current operation */
    CYBLE_ERROR_INVALID_STATE
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
    CYBLE_BLESS_STATE_ACTIVE = 0x01,
    CYBLE_BLESS_STATE_EVENT_CLOSE,
    CYBLE_BLESS_STATE_SLEEP,
    CYBLE_BLESS_STATE_ECO_ON,
    CYBLE_BLESS_STATE_ECO_STABLE,
    CYBLE_BLESS_STATE_DEEPSLEEP,
    CYBLE_BLESS_STATE_HIBERNATE,
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
        PWR_GAIN level is same as 0 dBm, but
        the ABS_PWR is amplified and applied for both
        Connection and Advertising channel.
     */
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
    CYBLE_LL_SCA_251_TO_500_PPM = 0x00u,
    CYBLE_LL_SCA_151_TO_250_PPM,
    CYBLE_LL_SCA_101_TO_150_PPM,
    CYBLE_LL_SCA_076_TO_100_PPM,
    CYBLE_LL_SCA_051_TO_075_PPM,
    CYBLE_LL_SCA_031_TO_050_PPM,
    CYBLE_LL_SCA_021_TO_030_PPM,
    CYBLE_LL_SCA_000_TO_020_PPM,    
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
    uint8 majorVersion;     
	/** The minor version of the library */
    uint8 minorVersion;     
	/** The patch number of the library */
    uint8 patch;            
	/** The build number of the library */
    uint8 buildNumber;

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

/** @} */


/***************************************
* Global Function Declarations
***************************************/


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
*
* generation of CYBLE_EVT_STACK_ON event on successful initialization of the
* BLE Stack.
*   
*     
*  \param CyBLEApplCbFunc: Event callback function to receive events from BLE Stack.
*                   CYBLE_APP_CB_T is a function pointer type.
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
*    <td>ATT MTU</td>
*    <td>Size of MTU + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ</td>
*    <td>2</td>
*  </tr>
*  <tr>
*    <td>1</td>
*    <td>Maximum Gatt attribute length (Up to 0xFFD0u) Or Min size of 16u shall be provided for GATT Client role or 
		 other GAP, GATT roles where this field is not applicable</td>
*    <td>max attr length + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ</td>
*    <td>1</td>
*  </tr>
*  <tr>
*    <td>2</td>
*    <td>Number of PSM supported</td>
*    <td>CYBLE_L2CAP_PSM_SIZE + CYBLE_MEM_EXT_SZ</td>
*    <td>As per application requirement</td>
*  </tr>
*  <tr>
*    <td>3</td>
*    <td>Number of L2cap CBFC logical</td>
*    <td>CYBLE_L2CAP_CBFC_CHANNEL_SIZE + CYBLE_MEM_EXT_SZ</td>
*    <td>No of L2cap logical channels</td>
*  </tr>
*  <tr>
*    <td>4</td>
*    <td>L2cap mtu (0x17 to 0xFFD0u)</td>
*    <td>Size of L2CAP MTU + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ</td>
*    <td>No of L2cap logical channels</td>
*  </tr>
*  <tr>
*    <td>5</td>
*    <td>L2cap mps (0x17 to 0xFFD0u)</td>
*    <td>Size of MPS + CYBLE_MEM_EXT_SZ + CYBLE_L2CAP_HDR_SZ</td>
*    <td>(No of L2cap logical channels)*(Size of L2CAP MTU / Size of MPS)</td>
*  </tr>
*  </table>
* 
* 	Index position is fixed for each data buffer corresponding to configuration parameters.
*   First four buffers of with valid size (shall be > 12) corresponding to each field are required
*   for BLE_SOC mode operation, otherwise stack will throw error.
* 
* 	* No of buffers can be increased from 1 to 10 to achieve better throughput if mtu>32.
* 
* 	   This is based on application throughput requirement.
* 
*  \param bleStackFlashPointer: Pointer to an array of bytes to be allocated by the BLE component for the storing the
*                         persistant data into the flash. Pointer provided is should be aligned to the flash
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
/* Event callback function prototype to receive events from stack */
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
*  This is a blocking function. No event is generated on calling this function.
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

*   Bluetooth Low Energy Sub System (BLESS) has three sub-modes in Active mode:
*    1. Idle
*    2. Transmit Mode, and
*    3. Receive Mode
* 
*   These modes draw full current from the device and the CPU has full access to
*   its registers.
*   
*   __Sleep Mode__

*   The clock to the link layer engine and digital modem is gated and the 
*   (External Crystal Oscillator) ECO continues to run to maintain the link layer
*   timing. The application cannot enter sleep mode if a Transmit or Receive is 
*   in progress.
* 
*   __Deep Sleep with ECO Off Mode__

*   The ECO is stopped and Watch Crystal Oscillator (WCO) is used to maintain
*   link layer timing. All the regulators in the Radio Frequency (RF) transceiver
*   are turned off to reduce leakage current and BLESS logic is kept powered ON
*   from the System Resources Sub System (SRSS) deep-sleep regulator for retention
*   of current BLESS state information. This mode can be entered from either Idle 
*   (Active) or Sleep mode. It should be entered when the next scheduled activity 
*   instant in time domain is greater than the Deep Sleep total wakeup time 
*   (typically 2ms).
* 
*   __Hibernate mode__

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
*  save power while polling for wakeup indication from BLESS.No event is
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
*  This function sets the Bluetooth device address into BLE Controller's memory.
*  This address shall be used for BLE procedures unless explicitly indicated by
*  BLE Host through HCI commands. The application layer needs to call this
*  function every time an address change is required. Bluetooth 4.1 Core
*  specification [3.12] specifies that the Bluetooth device can change its
*  private address periodically, with the period being decided by the
*  application; there are no limits specified on this period. The application
*  layer should maintain its own timers in order to do this.
* 
*  This is a blocking function. No event is generated on calling this function.
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
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_SetDeviceAddress(CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
* Function Name: CyBle_GetDeviceAddress
***************************************************************************//**
* 
*  This API reads the BD device address from BLE Controller's memory. This
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
*                 If bleSsPwrLvl->blePwrLevelInDbm is greater than 0dBm, then the
*                 power level is applicable to both advertisement and 
*                 connection channel.                  
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
*                 If bleSsPwrLvl->blePwrLevelInDbm is greater than 0dBm, then the
*                 power level is applicable to both advertisement and 
*                 connection channel.
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
*
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
*
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
*    CYBLE_ERROR_NO_CONNECTION       | Connection does not exist
* 
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
* \return
*  CYBLE_API_RESULT_T: Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | One of the input parameters is invalid
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted
*   CYBLE_ERROR_NO_CONNECTION        | Connection does not exist
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
*   CYBLE_ERROR_NO_CONNECTION        | Connection does not exist.
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
* Function Name: CyBle_SetTxGainMode
***************************************************************************//**
* 
*  This function configures the Rx gain mode for BLESS radio for Rx operation.
* 	
*  \param bleSsGainMode: Gain mode setting for the output power
* 
*   BLESS RD Gain Mode            | Description
* 	------------------            | -----------
*   CYBLE_BLESS_NORMAL_GAIN_MODE  |	0x00u - BLESS Normal Gain Mode Tx Pwr Range -18dBm to 0 dBm Normal Rx Sensitivity
*   CYBLE_BLESS_HIGH_GAIN_MODE    | 0x01u - BLESS High Gain Mode Tx Pwr Range -18dBm to 3 dBm 3 dBm Additional Rx Sensitivity
*  
*  \return
*  none
*
******************************************************************************/
void CyBle_SetRxGainMode(uint8 bleSsGainMode);

/** @} */

#endif /* CY_BLE_CYBLE_STACK_H */


/*EOF*/
