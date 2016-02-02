/***************************************************************************//**
* \file CYBLE_StackGatt.h
* \version 2.30
* 
* \brief
*  This file contains the GATT APIs of the BLE Host Stack IP
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

/**
 \addtogroup group_common_api_gatt_definitions
 @{
*/


#ifndef CY_BLE_CYBLE_GATT_STACK_H
#define CY_BLE_CYBLE_GATT_STACK_H

    
/***************************************
* Common stack includes
***************************************/

#include "cytypes.h"


/***************************************
* GATT Constants
***************************************/

/* ATT 16-bit UUID Size */
#define CYBLE_GATT_16_BIT_UUID_SIZE       		 2u

/* GATT 128-bit UUID Size */
#define CYBLE_GATT_128_BIT_UUID_SIZE             16u

/* GATT Identification for 16-bit UUID Format */
#define CYBLE_GATT_16_BIT_UUID_FORMAT           0x01u

/* GATT Identification for 128-bit UUID Format */
#define CYBLE_GATT_128_BIT_UUID_FORMAT          0x02u

/* GATT MTU Size */
#define CYBLE_GATT_DEFAULT_MTU         			23u
#define CYBLE_GATT_MAX_MTU         				512u

/* ATT Execute Write Cancel Flag */
#define CYBLE_GATT_EXECUTE_WRITE_CANCEL_FLAG   	0x00u

/* ATT Execute Write Execute Flag */
#define CYBLE_GATT_EXECUTE_WRITE_EXEC_FLAG     	0x01u

/* ATT Invalid Attribute Handle Value */
#define CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE    0x0000u

/* ATT Attribute Handle Start Range */
#define CYBLE_GATT_ATTR_HANDLE_START_RANGE      0x0001u

/* ATT Attribute Handle End Range */
#define CYBLE_GATT_ATTR_HANDLE_END_RANGE        0xFFFFu


/***************************************
* Enumerated Types
***************************************/

/** Opcode which has resulted in error */
typedef enum
{
	/** Error Response PDU */
	CYBLE_GATT_ERROR_RSP = 0x01u,

	/** Exchange GATT MTU Request PDU */
	CYBLE_GATT_XCNHG_MTU_REQ,

	/** Exchange GATT MTU Response PDU */
	CYBLE_GATT_XCHNG_MTU_RSP,

	/** Find Information Request PDU */
	CYBLE_GATT_FIND_INFO_REQ,

	/** Find Information Response PDU */
	CYBLE_GATT_FIND_INFO_RSP,

	/** Find By Type Value Request PDU */
	CYBLE_GATT_FIND_BY_TYPE_VALUE_REQ,

	/** Find By Type Value Response PDU */
	CYBLE_GATT_FIND_BY_TYPE_VALUE_RSP,

	/** Read By Type Request PDU */
	CYBLE_GATT_READ_BY_TYPE_REQ,

	/** Read By Type Response PDU */
	CYBLE_GATT_READ_BY_TYPE_RSP,

	/** Read Request PDU */
	CYBLE_GATT_READ_REQ,

	/** Read Response PDU */
	CYBLE_GATT_READ_RSP,

	/** Read Blob Request PDU */
	CYBLE_GATT_READ_BLOB_REQ,

	/** Read Blob Response PDU */
	CYBLE_GATT_READ_BLOB_RSP,

	/** Read Multiple Request PDU */
	CYBLE_GATT_READ_MULTIPLE_REQ,

	/** Read Multiple Response PDU */
	CYBLE_GATT_READ_MULTIPLE_RSP,

	/** Read Group Type Request PDU */
	CYBLE_GATT_READ_BY_GROUP_REQ,

	/** Read Group Type Response PDU */
	CYBLE_GATT_READ_BY_GROUP_RSP,

	/** Write Request PDU */
	CYBLE_GATT_WRITE_REQ,

	/** Write Response PDU */
	CYBLE_GATT_WRITE_RSP,

	/** Write Command PDU */
	CYBLE_GATT_WRITE_CMD = 0x52u,

	/** Prepare Write Request PDU */
	CYBLE_GATT_PREPARE_WRITE_REQ = 0x16u,

	/** Prepare Write Response PDU */
	CYBLE_GATT_PREPARE_WRITE_RSP,

	/** Execute Write Request PDU */
	CYBLE_GATT_EXECUTE_WRITE_REQ,

	/** Execute Write Response PDU */
	CYBLE_GATT_EXECUTE_WRITE_RSP,

	/** Handle Value Notification PDU */
	CYBLE_GATT_HANDLE_VALUE_NTF = 0x1Bu,

	/** Handle Value Indication PDU */
	CYBLE_GATT_HANDLE_VALUE_IND = 0x1Du,

	/** Handle Value Confirmation PDU */
	CYBLE_GATT_HANDLE_VALUE_CNF = 0x1Eu,

	/**Signed Write Command PDU */
	CYBLE_GATT_SIGNED_WRITE_CMD = 0xD2,
    
	/** Unknown or Unhandled PDU */
	CYBLE_GATT_UNKNOWN_PDU_IND = 0xFFu

}CYBLE_GATT_PDU_T;

/** GATT profile error codes */
typedef enum
{
	/** No Error	*/
	CYBLE_GATT_ERR_NONE = 0x00u,

	/** Invalid Handle error code is used in the case when the ATT handle in the
	   ATT request PDU is invalid. */
	CYBLE_GATT_ERR_INVALID_HANDLE,

	/** Read Not Permitted error code is used in the case when the permission to
       read the value of an ATT handle is not permitted on the ATT server. */
	CYBLE_GATT_ERR_READ_NOT_PERMITTED,

	/** Write Not Permitted error code is used in the case when the permission to
       write the value of an ATT handle is not permitted on the ATT server. */
	CYBLE_GATT_ERR_WRITE_NOT_PERMITTED,

	/** Invalid PDU error code is used in the case when the format of the PDU sent
       from the ATT Client is incorrect. */
	CYBLE_GATT_ERR_INVALID_PDU,

	/** Insufficient Authentication error code is used in the case when
       an access to a handle is attempted on a un-authenticated link but the
       attribute requires that the link be authenticated before any client can access it. */
	CYBLE_GATT_ERR_INSUFFICIENT_AUTHENTICATION,

	/** Request not supported error code is used in the case when
       the server does not support the processing of an ATT request sent from the client. */
	CYBLE_GATT_ERR_REQUEST_NOT_SUPPORTED,

	/** Invalid Offset error code is used in the case when
       the offset sent by the client in the Read blob/Prepare Write Request is
       invalid with respect to the length of the value in the server. */
	CYBLE_GATT_ERR_INVALID_OFFSET,

	/** Insufficient Authorization error code is used in the case when
       the ATT server does not Authorize the client and hence prohibiting the
       client from reading the handle value. */
	CYBLE_GATT_ERR_INSUFFICIENT_AUTHORIZATION,

	/** Write queue full error code is used when there is no more space left in the
       prepare write queue on the server to entertain any more prepare writes from a
       client. */
	CYBLE_GATT_ERR_PREPARE_WRITE_QUEUE_FULL,

	/** Attribute not found error is used when the ATT server cannot find any handles
       that belong to the Attribute type in the given range of handles that the
       client specified in its request. This error code can be sent to the client in
       response to the following request PDUs - Find Information, Find by Type Value,
       Read by Type, Read by Group Type requests. */
	CYBLE_GATT_ERR_ATTRIBUTE_NOT_FOUND,

	/** Attribute Not Long error code is used when the client tries to read or write
       a Attribute handle's value which cannot be read or written through Read Blob
       or multiple prepare write requests. */
	CYBLE_GATT_ERR_ATTRIBUTE_NOT_LONG,

	/** Insufficient encryption key size error code is used when the client tries to
       access an Attribute Handle's Value for which the link need to be encrypted
       with a key of certain minimum key size and the current link is encrypted
       with a key of lesser size than the minimum required. */
	CYBLE_GATT_ERR_INSUFFICIENT_ENC_KEY_SIZE,

	/**
      Invalid Attribute length error code is used when the Attribute value's
      length is not correct to process the request containing the value.
	*/
	CYBLE_GATT_ERR_INVALID_ATTRIBUTE_LEN,

	/**
      Unlikely error is used when the processing of the Attribute request has
      encountered an error that is not covered by any other error code.
	*/
	CYBLE_GATT_ERR_UNLIKELY_ERROR,

	/** Insufficient encryption error code is used when the client tries to read or
       write an Attribute handle which requires the link to be encrypted and the
       link is currently not encrypted. */
	CYBLE_GATT_ERR_INSUFFICIENT_ENCRYPTION,

	/** Unsupported Group Type error code is used when the Attribute type requested
       in the Read by Group Type request is not a valid grouping attribute on the
       server. */
	CYBLE_GATT_ERR_UNSUPPORTED_GROUP_TYPE,

	/** Insufficient Resources error code is used when the ATT server does not have
      enough resources such as memory etc. to process the request from the client. */
	CYBLE_GATT_ERR_INSUFFICIENT_RESOURCE = 0x11,
    
    /** Other Error Groups for ATT - GATT
     * Reserved: GATT-ATT Error codes 0x12 to 0x7F are reserved for 
     * Application Specific Error Code Range: 0x80 to 0x9F
     * Reserved: 0xA0 to 0xDF 
     * Common Profile & Service Error Code : 0xE0 to 0xFF 
     */

    /** Heart Rate Control Point Not Supported error code is used when a unsupported
       code is written into Heart Rate service Control Point characteristic. */
    CYBLE_GATT_ERR_HEART_RATE_CONTROL_POINT_NOT_SUPPORTED = 0x80u,
    
    /** The user data access is not permitted (i.e. the user has not given
       consent in order to access these data). */
    CYBLE_GATT_ERR_USER_DATA_ACCESS_NOT_PERMITTED = 0x80u,
    
    /** The notifications of the Cycling Power Vector characteristic cannot be sent 
       due to inappropriate connection parameters. */
    CYBLE_GATT_ERR_CPS_INAPPROPRIATE_CONNECTION_PARAMETERS = 0x80u,

	/** The value is considered invalid and outside of the range allowed by 
       the characteristic. */
	CYBLE_GATT_ERR_HTS_OUT_OF_RANGE = 0x80u,

    /** Procedure Already in Progress error code is used when a profile or service
       request cannot be serviced because an operation that has been previously
       triggered is still in progress. */
	CYBLE_GATTS_ERR_PROCEDURE_ALREADY_IN_PROGRESS = 0x80u,
    
    /** The Op Code Not Supported error code is used when a unsupported
       Op Code is written into Control Point characteristic. */
    CYBLE_GATT_ERR_OP_CODE_NOT_SUPPORTED = 0x80u,
    
    /** The Missing CRC error code is used when the CRC is missed in the 
       incoming characteristic value. */
    CYBLE_GATT_ERR_MISSING_CRC = 0x80u,
    
    /** Client Characteristic Configuration Descriptor Improperly Configured error
       code is used when a Client Characteristic Configuration descriptor is not
       configured according to the requirements of the profile or service. */
	CYBLE_GATTS_ERR_CCCD_IMPROPERLY_CONFIGURED = 0x81u,
    
    /** The Operation Failed error code is used when the device is unable to 
       complete a procedure for any reason. */
	CYBLE_GATTS_ERR_OPERATION_FAILED = 0x81u,
    
    /** The Invalid CRC error code is used when the CRC is invalid in the 
       incoming characteristic value. */
	CYBLE_GATT_ERR_INVALID_CRC = 0x81u,
	
	/** Command Not Supported used by the Alert Notification Server when the Client
       sends incorrect value of the Command ID or Category ID of to the Alert
       Notification Control Point Characteristic. */
    CYBLE_GATT_ERR_ANS_COMMAND_NOT_SUPPORTED = 0xA0u,
    
    /** Unknown command error code used by the Apple Notification Center Server when the Client
       sends unknown command value of the Apple Notification Center Service Control Point 
       Characteristic. */
    CYBLE_GATT_ERR_ANCS_UNKNOWN_COMMAND = 0xA0u,
    
    /** Invalid command error code used by the Apple Notification Center Server when the Client
       sends invalid command value of the Apple Notification Center Service Control Point 
       Characteristic. */
    CYBLE_GATT_ERR_ANCS_INVALID_COMMAND = 0xA1u,
    
    /** Invalid parameter error code used by the Apple Notification Center Server when the Client
       sends invalid parameter value of the Apple Notification Center Service Control Point 
       Characteristic. */
    CYBLE_GATT_ERR_ANCS_INVALID_PARAMETER = 0xA2u,
    
    /** Action failed error code used by the Apple Notification Center Server when some 
       Apple Notification Center Service Control Point Characteristic command processing goes wrong */
    CYBLE_GATT_ERR_ANCS_ACTION_FAILED = 0xA3u,

    /** Client Characteristic Configuration Descriptor Improperly Configured error
       code is used when a Client Characteristic Configuration descriptor is not
       configured according to the requirements of the profile or service. */
	CYBLE_GATT_ERR_CCCD_IMPROPERLY_CONFIGURED = 0xFDu,

	/** The Procedure Already in Progress error code is used when a profile or service
       request cannot be serviced because an operation that has been previously
       triggered is still in progress. */
	CYBLE_GATT_ERR_PROCEDURE_ALREADY_IN_PROGRESS = 0xFEu,
	
	/** Out of Range error code is used when an attribute value is out of range as
	   defined by a profile or service specification. */
	CYBLE_GATT_ERR_OUT_OF_RANGE = 0xFFu

}CYBLE_GATT_ERR_CODE_T;

/** @} */

/**
 \addtogroup group_common_api_definitions
 @{
*/

/***************************************
* Exported data structures
***************************************/

/** GATT 16 Bit UUID */
typedef uint16 		CYBLE_UUID16;

#ifdef GATT_SUPPORT_128_BIT_UUID

/** GATT 128 Bit UUID type */
typedef struct
{
    uint8   value[CYBLE_GATT_128_BIT_UUID_SIZE];
}CYBLE_UUID128_T;

#endif /*GATT_SUPPORT_128_BIT_UUID*/

/** GATT UUID type*/
typedef union
{
	/** 16 Bit UUID */
    CYBLE_UUID16    	uuid16;

#ifdef GATT_SUPPORT_128_BIT_UUID
	/** 128 Bit UUID */
    CYBLE_UUID128_T   	uuid128;
#endif /*GATT_SUPPORT_128_BIT_UUID*/

}CYBLE_UUID_T;

/** @} */

/**
 \addtogroup group_common_api_gatt_definitions
 @{
*/

/** GATT BD Attribute Handle Type */
typedef uint16 		CYBLE_GATT_DB_ATTR_HANDLE_T;

/** @} */

/**
 \addtogroup group_common_api_definitions
 @{
*/

/** Connection Handle */
typedef struct
{
    /** Identifies the peer device(s) bonded or in current connection. Stack supports CYBLE_GAP_MAX_BONDED_DEVICE+1 devices.
       first device connected is assinged value CYBLE_GAP_MAX_BONDED_DEVICE. If previous 
       device is bonded then current device will be assigned value CYBLE_GAP_MAX_BONDED_DEVICE-1, 
       else CYBLE_GAP_MAX_BONDED_DEVICE.
    */
    uint8     	bdHandle;

    /** Identifies the ATT Instance. Current implementation supports only one att instance (0) due to availability
       of only on fixed channel for att. This parameter is introduced as part of connection handle to keep the 
       interface unchanged event if new Bluetooth spect defines more fixed channels for ATT payload. 
    */
    uint8       attId;

}CYBLE_CONN_HANDLE_T;

/** @} */

/**
 \addtogroup group_common_api_gatt_definitions
 @{
*/

/* Abstracts Variable Length Values for GATT.

    Apart from data, and length, 'actual length' is needed so that GATT can
    indicate to the application actual length of data processed for a PDU.
  
    Is used in multiple commands - see CYBLE_GATT_READ_RSP,
    CYBLE_GATT_FIND_BY_TYPE_VALUE_REQ, CYBLE_GATT_READ_BLOB_RSP etc.
  
    In GATT Read Response for example, if the attribute length is 30 octects
    and the GATT MTU is 23 octets, then only first 22 octets can be sent by GATT,
    therefore actual length will be 22 (GATT MTU-1).
    However, if the GATT MTU is configured to be 54 for example, all 30 octets
    can be transmitted and the actual length will be 30.
    
    Actual length should be derived as -
    actualLen = length>(GATT MTU-1) ? (GATT MTU-1):len
  
    In case multiple values are being packed, the actual length processed will
    depend on the available MTU. */
typedef struct
{
    /** Pointer to the value to be packed */
    uint8*   val;

    /** Length of Value to be packed */
    uint16   len;

    /** Out Parameter Indicating Actual Length Packed and sent over the air. Actual length
       can be less than or equal to the 'len' parameter value. This provides information
       to application that what is the actual length of data that is transmitted over the 
       air. Each GATT procedures defines different length of data that can ne transmitted 
       over the air. If application sends more than that, all data may not transmitted over air.*/
    uint16   actualLen;

}CYBLE_GATT_VALUE_T;

/** GATT handle - value pair type */
typedef struct
{
	/** Attribute Value	*/
    CYBLE_GATT_VALUE_T          	value;      

	/** Attribute Handle of GATT DB */
    CYBLE_GATT_DB_ATTR_HANDLE_T	  	attrHandle;     

}CYBLE_GATT_HANDLE_VALUE_PAIR_T;

/** GATT Attribute Handle Range type */
typedef struct
{
	/** Start Handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T    startHandle; 

	/** End Handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T    endHandle;      

}CYBLE_GATT_ATTR_HANDLE_RANGE_T;

/** GATT MTU exchange parameter type */
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 	connHandle; 
	
	/** Client/Server Rx/Tx GATT MTU Size */
    uint16    					mtu;  	 

}CYBLE_GATT_XCHG_MTU_PARAM_T;

/** GATT Handle Value Pair along with offset type */
typedef struct
{
	/** Attribute Handle & Value to be Written */
    CYBLE_GATT_HANDLE_VALUE_PAIR_T    	handleValuePair;   

	/** Offset at which Write is to be performed */
    uint16                    			offset;    		

}CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T;

/** @} */

/**
 \addtogroup group_common_api_gatt_client_server_functions
 @{
*/
/***************************************
* Exported APIs
***************************************/

/******************************************************************************
* Function Name: CyBle_GattGetMtuSize
***************************************************************************//**
* 
*  This function provides the correct GATT MTU used by BLE stack. If function
*  is called after GATT MTU configuration procedure, it will provide the final
*  negotiated GATT MTU else default MTU (23 Bytes).
*     
*  \param mtu: buffer where Size of GATT MTU will be stored.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | If invalid parameter passed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattGetMtuSize(uint16* mtu);

/** @} */

#endif /* CY_BLE_CYBLE_GATT_STACK_H */


/*EOF*/
