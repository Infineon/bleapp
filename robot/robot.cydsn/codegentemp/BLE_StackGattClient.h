/***************************************************************************//**
* \file CYBLE_StackGattClient.h
* \version 2.30
* 
* \brief
*  This file contains the GATT Client routines
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


#ifndef CY_BLE_CYBLE_STACK_GATT_CLIENT_H
#define CY_BLE_CYBLE_STACK_GATT_CLIENT_H


/***************************************
* Common stack includes
***************************************/

#include "BLE_StackGatt.h"


/***************************************
* Exported structures and unions
***************************************/

/* Error Response parameter type received from Server 
    For error codes that are received during gatt discovery procedure, 
    Client may choose to disconnect the link.
    i.e. if client did not get the service of its choice, client may choose to disconnect.
    the link.*/
typedef struct
{
	/** Connection handle */ 
	CYBLE_CONN_HANDLE_T 			connHandle;

    /** Opcode which has resulted in Error */
    CYBLE_GATT_PDU_T    			opCode;

    /** Attribute Handle in which error is generated */
    CYBLE_GATT_DB_ATTR_HANDLE_T    	attrHandle;

    /** Error Code describing cause of error */
    CYBLE_GATT_ERR_CODE_T			errorCode;
	
}CYBLE_GATTC_ERR_RSP_PARAM_T;

/** GATT read by type request to be sent to Server */
typedef struct
{
	/** Handle Range */
    CYBLE_GATT_ATTR_HANDLE_RANGE_T  	range;     

	/** GATT UUID type */
    CYBLE_UUID_T           	  			uuid;   

   /** Format indicating, 16 bit or 128 bit UUIDs
	   * For 16bits UUID format - CYBLE_GATT_16_BIT_UUID_FORMAT (0x01)
	   * For 128bits UUID format - CYBLE_GATT_128_BIT_UUID_FORMAT (0x02)
    */
    uint8               			  	uuidFormat;    
	
}CYBLE_GATTC_READ_BY_TYPE_REQ_T;

/** GATT find info request to be sent to Server */
typedef CYBLE_GATT_ATTR_HANDLE_RANGE_T CYBLE_GATTC_FIND_INFO_REQ_T;

/** Signed Write command request to be sent to Server */
typedef CYBLE_GATT_HANDLE_VALUE_PAIR_T  CYBLE_GATTC_SIGNED_WRITE_CMD_REQ_T;

/** Read request to be sent to Server */
typedef CYBLE_GATT_DB_ATTR_HANDLE_T CYBLE_GATTC_READ_REQ_T;

/** Read blob request to be sent to Server */
typedef struct
{
	/** Handle on which Read Blob is requested */
    CYBLE_GATT_DB_ATTR_HANDLE_T    	attrHandle;	

	/** Value Offset from which the Read is Requested */
    uint16             				offset;	
	
}CYBLE_GATTC_READ_BLOB_REQ_T;

/** GATT handle list type */
typedef struct
{
    /** Handle list where the UUID with value Indicated is found */
    uint16    *handleList;

    /** Number of Handles in the list */
    uint16    listCount;

    /** Actual Number of Handles Packed. This is a output parameter */
    uint16    actualCount;

}CYBLE_GATTC_HANDLE_LIST_T;

/** Read multiple request to be sent to Server */
typedef CYBLE_GATTC_HANDLE_LIST_T CYBLE_GATTC_READ_MULT_REQ_T;

/** Write command request to be sent to Server */
typedef CYBLE_GATT_HANDLE_VALUE_PAIR_T  CYBLE_GATTC_WRITE_CMD_REQ_T;

/** Write request to be sent to Server */
typedef CYBLE_GATT_HANDLE_VALUE_PAIR_T CYBLE_GATTC_WRITE_REQ_T;

/** Prepare write request to be sent to Server */
typedef CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T CYBLE_GATTC_PREP_WRITE_REQ_T;

/** Read response parameter type received from server*/
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 			connHandle; 

	/** Attribute Value  */
    CYBLE_GATT_VALUE_T     			value;     
	
}CYBLE_GATTC_READ_RSP_PARAM_T;

/** Handle value notification data received from server */
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 					connHandle; 			

	/** handle value pair, actual length files needs to be ignored */
    CYBLE_GATT_HANDLE_VALUE_PAIR_T    		handleValPair; 
	
}CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T;

/** GATT handle value indication parameter received from server type */
typedef CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T;

/** Data Element for Group Response */
typedef struct
{
    /** atribute handle value pair */
    uint8              * attrValue;

    /** Length of each Attribute Data Element including the Handle Range */
    uint16             length;

    /** Total Length of Attribute Data */
    uint16             attrLen;
}CYBLE_GATTC_GRP_ATTR_DATA_LIST_T;


/** Read By Group Response received from Server*/
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 		  		connHandle; 

	/** Group attribute data list */
	CYBLE_GATTC_GRP_ATTR_DATA_LIST_T 	attrData;
	
}CYBLE_GATTC_READ_BY_GRP_RSP_PARAM_T;

/** GATT read by type response received from server*/
typedef CYBLE_GATTC_READ_BY_GRP_RSP_PARAM_T CYBLE_GATTC_READ_BY_TYPE_RSP_PARAM_T;

/** GATT find by type value response received from server*/
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 				connHandle; 

	/** Handle Range List */
    CYBLE_GATT_ATTR_HANDLE_RANGE_T		* range; 

	 /** Size of List */
    uint8              					count;  
	 
}CYBLE_GATTC_FIND_BY_TYPE_RSP_PARAM_T;

/** GATT list of Handle UUID pair parameter type */
typedef struct
{
	/** Handle - UUID Pair list
	   This is a packed byte stream, hence it needs to be unpacked and decoded. */
    uint8  	*list; 	

	/** Number of elements in the list in bytes */
    uint16  byteCount;
	
}CYBLE_GATTC_HANDLE_UUID_LIST_PARAM_T;

/** GATT find info response received from Server*/
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 					connHandle;
	
	/** Handle Value List */	
    CYBLE_GATTC_HANDLE_UUID_LIST_PARAM_T   	handleValueList;  

	/** Format indicating, 16 bit (0x01) or 128 bit (0x02) UUIDs */	
    uint8                   				uuidFormat;     	
	
}CYBLE_GATTC_FIND_INFO_RSP_PARAM_T;

/** GATT find by type value request to be sent to Server*/
typedef struct
{
	/** Attribute Value to Find */
    CYBLE_GATT_VALUE_T          	 	value; 

	/** Handle Range - Start and End Handle */
    CYBLE_GATT_ATTR_HANDLE_RANGE_T 		range;  

	/** 16-bit UUID to Find */
    CYBLE_UUID16          	 			uuid;     

}CYBLE_GATTC_FIND_BY_TYPE_VALUE_REQ_T;

/** Execute Write result */
typedef struct
{
	/**Connection handle*/
	CYBLE_CONN_HANDLE_T 			connHandle; 
	
	/** Result of the execute write request */
    uint8 							result;  	 

}CYBLE_GATTC_EXEC_WRITE_RSP_T;

/** @} */

/**
 \addtogroup group_common_api_gatt_client_functions
 @{
*/

/***************************************
* Exported APIs
***************************************/

/******************************************************************************
* Function Name: CyBle_GattcStopCmd
***************************************************************************//**
* 
*  This function is used by the GATT Client to stop any of the following ongoing 
*  GATT procedures:
*   1.  CyBle_GattcDiscoverAllPrimaryServices()
*   2.  CyBle_GattcDiscoverPrimaryServiceByUuid()
*   3.  CyBle_GattcFindIncludedServices()
*   4.  CyBle_GattcDiscoverAllCharacteristics()
*   5.  CyBle_GattcDiscoverCharacteristicByUuid()
*   6.  CyBle_GattcDiscoverAllCharacteristicDescriptors()
*   7.  CyBle_GattcReadLongCharacteristicValues()
*   8.  CyBle_GattcWriteLongCharacteristicValues()
*   9.  CyBle_GattcReliableWrites()
*   10. CyBle_GattcReadLongCharacteristicDescriptors()
*   11. CyBle_GattcWriteLongCharacteristicDescriptors()
*   .
*  If none of the above procedures is ongoing, then this command will be ignored.
*  This function has no effect on ATT procedures other than those listed above.
*  
*  If the user intends to start a new GATT procedure including those listed above
*  and there is an ongoing GATT procedure (any one from the above list), the user
*  needs to call this function to stop the ongoing GATT procedure and then invoke
*  the desired GATT procedure.
*  This is a blocking function. No event is generated on calling this function.
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattcStopCmd(void);


/******************************************************************************
* Function Name: CyBle_GattcExchangeMtuReq
***************************************************************************//**
* 
*  This function is used by the GATT Client to send Maximum Transmitted Unit
*  (GATT MTU) supported by the GATT Client. This is a non-blocking function.
* 
*  Default GATT MTU size as per Bluetooth 4.1 core specification is 23 bytes. If
*  the GATT Client supports a size greater than the default, it has to invoke
*  this function with the desired GATT MTU size. This function should only be
*  initiated once during a connection.
* 
*  Refer to  Bluetooth 4.1 core specification, Volume 3, Part G, section 4.3.1
*  for more details on GATT MTU exchange operation.
* 
*  This function call results in CYBLE_EVT_GATTS_XCNHG_MTU_REQ event at the
*  GATT Server's end in response to which the GATT Server is expected to send
*  its GATT MTU size.
* 
*  The CYBLE_EVT_GATTC_XCHNG_MTU_RSP event is generated at the
*  GATT Client's end on receiving GATT MTU response from the GATT Server.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param mtu: Size of GATT MTU. Max GATT MTU supported by BLE stack is 256 Bytes.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  <table>
*  <tr>
*    <th>Error codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>'connHandle' value does not represent any existing entry in the Stack or, 
         'mtu' has a value which is greater than that set on calling CyBle_StackInit function</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>This operation is not permitted</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcExchangeMtuReq
(
	CYBLE_CONN_HANDLE_T			connHandle, 
	uint16 						mtu
);


/******************************************************************************
* Function Name: CyBle_GattcDiscoverAllPrimaryServices
***************************************************************************//**
* 
*  This function is used by the GATT Client to discover all the primary services 
*  on a GATT Server to which it is connected. This is a non-blocking function.
* 
*  Internally, this function initiates multiple Read By Group Type Requests to
*  the peer device in response to which it receives Read By Group Type Responses.
*  Each Read By Group Type Response results in 
*  CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP event, which is propagated to the 
*  application layer for handling.
* 
*  Primary service discovery is complete when Error Response 
*  (CYBLE_EVT_GATTC_ERROR_RSP) is received and the Error Code is set to Attribute
*  Not Found or when the End Group Handle in the Read by Group Type Response is
*  0xFFFF. Completion of this operation is notified to the upper layer(s) using
*  CYBLE_EVT_GATTC_ERROR_RSP with error code updated appropriately.
* 
*  It is permitted to end the above stated sequence of operations early if the
*  desired primary service is found prior to discovering all the primary services
*  on the GATT Server. This can be achieved by calling the CyBle_GattcStopCmd() 
*  function.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.4.1 for
*  more details on this sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type
*               CYBLE_CONN_HANDLE_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcDiscoverAllPrimaryServices
(
	CYBLE_CONN_HANDLE_T				connHandle
);


/******************************************************************************
* Function Name: CyBle_GattcDiscoverPrimaryServiceByUuid
***************************************************************************//**
* 
*  This function is used by the GATT Client to discover a specific primary
*  service on a GATT Server, to which it is connected, when only the Service
*  UUID is known. This is a non-blocking function.
* 
*  Internally, this function initiates multiple Find By Type Value Requests with
*  the Attribute Type parameter set to the UUID for Primary Service and the
*  Attribute Value set to the 16-bit Bluetooth UUID or 128-bit UUID for the
*  specific primary service. Each Find By Type Value Response received from the
*  peer device is passed to the application as 
*  CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP event.
* 
*  The sequence of operations is complete when the Error Response is received
*  and the Error Code is set to Attribute Not Found or when the End Group 
*  Handle in the Find By Type Value Response is 0xFFFF. Completion of this 
*  function is notified to upper layer using CYBLE_EVT_GATTC_ERROR_RSP event
*  with the error code updated appropriately.
* 
*  It is permitted to end the function early by calling the CyBle_GattcStopCmd()
*  function if a desired primary service is found prior to discovery of all the
*  primary services of the specified service UUID supported on the GATT Server.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.4.2 
*  for more details on this sequence of operations.
*     
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param value: Parameter is of type CYBLE_GATT_VALUE_T, where,
*          1. 'value.val' should point to uint8 array containing the UUID to 
*              look for. UUID can be 16 or 128 bit.
*          2. 'value.len' should be set to 2 if the 16 bit UUID is to be found.
*              The length should be set to 16 if 128 bit UUID is to be found.
*          3. 'value.actualLen' is an unused parameter and should be ignored 
*              as it is unused.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcDiscoverPrimaryServiceByUuid
(
	CYBLE_CONN_HANDLE_T				connHandle, 
	CYBLE_GATT_VALUE_T				value
);


/******************************************************************************
* Function Name: CyBle_GattcFindIncludedServices
***************************************************************************//**
* 
*  This function is used by the GATT Client to find Included Service
*  declarations within a GATT Service to which it is connected. This is a 
*  non-blocking function.
* 
*  Internally, multiple Read By Type Requests are sent to the peer device in
*  response to which Read By Type Responses are received 
*  (CYBLE_EVT_GATTC_READ_BY_TYPE_RSP) and passed to the application layer.
* 
*  When Read By Type Response data does not contain the service UUID,
*  indicating the service UUID is a 128-bit UUID, the application layer can
*  choose to get the service UUID by performing the following steps:
*  1. Stop ongoing GATT operation by invoking CyBle_GattcStopCmd()
*  2. Send Read Request by invoking the function 
*      CyBle_GattcReadCharacteristicValue() with the read request handle set to
*      the attribute handle of the included service. Handle associated events. 
*  3. Re-initiate CyBle_GattcFindIncludedServices function, setting the start
*      handle to the attribute handle which is placed next to the one used in
*      the above step.
* 
*  It is permitted to end the function early if a desired included service is
*  found prior to discovering all the included services of the specified
*  service supported on the server by calling the CyBle_GattcStopCmd() 
*  function. If the CyBle_GattcStopCmd() function is not invoked, completion of
*  this function is notified to the upper layer using CYBLE_EVT_GATTC_ERROR_RSP.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.5.1 
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param range: Pointer to the handle range of type CYBLE_GATT_ATTR_HANDLE_RANGE_T 
*          for which relationship discovery has to be performed
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
*     
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcFindIncludedServices
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATT_ATTR_HANDLE_RANGE_T  	* range
);


/******************************************************************************
* Function Name: CyBle_GattcDiscoverAllCharacteristics
***************************************************************************//**
* 
*  This function is used by the GATT Client to find all characteristic
*  declarations within a service definition on a GATT Server connect to it when
*  only the service handle range is known. This is a non-blocking function.
* 
*  Internally, multiple Read By Type Requests are sent to the GATT Server in
*  response to which Read By Type Responses are received. Each response results
*  in the event CYBLE_EVT_GATTC_READ_BY_TYPE_RSP, which is passed to the 
*  application layer for handling.
* 
*  It is permitted to end the function early by calling the CyBle_GattcStopCmd() 
*  function if a desired characteristic is found prior to discovering all the
*  characteristics of the specified service supported on the GATT Server.
*  Completion of this function is notified to upper layer using
*  CYBLE_EVT_GATTC_ERROR_RSP event.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.6.1 for
*  more details on the sequence of operations.
*     
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param range: Parameter is of type CYBLE_GATT_ATTR_HANDLE_RANGE_T where:
*          1. 'range.startHandle' can be set to the start handle of the desired primary service.
*          2. 'range.endHandle' can be set to the end handle of the desired primary service.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcDiscoverAllCharacteristics
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATT_ATTR_HANDLE_RANGE_T		range
);


/******************************************************************************
* Function Name: CyBle_GattcDiscoverCharacteristicByUuid
***************************************************************************//**
* 
*  This function is used by the GATT Client to discover service characteristics
*  on a GATT Server when only the service handle ranges are known and the
*  characteristic UUID is known. This is a non-blocking function.
* 
*  Internally, multiple Read By Type Requests are sent to the peer device in
*  response to which Read By Type Responses are received. Each of these responses
*  results in the event CYBLE_EVT_GATTC_READ_BY_TYPE_RSP, which is passed to the
*  application layer for further processing.
* 
*  It is permitted to end the function early by calling the CyBle_GattcStopCmd() 
*  function if a desired characteristic is found prior to discovering all the
*  characteristics for the specified service supported on the GATT Server. 
*  Completion of this function is notified to upper layer using 
*  CYBLE_EVT_GATTC_ERROR_RSP event.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.6.2
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param readByTypeReqParam: Pointer to a variable of type 
*                       CYBLE_GATTC_READ_BY_TYPE_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcDiscoverCharacteristicByUuid
(
	CYBLE_CONN_HANDLE_T						connHandle, 
	CYBLE_GATTC_READ_BY_TYPE_REQ_T			* readByTypeReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcDiscoverAllCharacteristicDescriptors
***************************************************************************//**
* 
*  This function is used by the GATT Client to find all the characteristic
*  descriptors. This is a non-blocking function.
* 
*  Internally, multiple Find Information Requests are sent to the peer device in
*  response to which Find Information Responses are received by the GATT Client.
*  Each of these responses generate CYBLE_EVT_GATTC_FIND_INFO_RSP event at the
*  GATT Client end which is propagated to the application layer for further
*  processing.
* 
*  It is permitted to end the function early by calling the CyBle_GattcStopCmd()
*  function if desired Characteristic Descriptor is found prior to discovering 
*  all the characteristic descriptors of the specified characteristic. Completion
*  of this function is notified to upper layer using CYBLE_EVT_GATTC_ERROR_RSP
*  event.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.7.1 for
*  more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param findInfoReqParam: Pointer to a variable of type CYBLE_GATTC_FIND_INFO_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcDiscoverAllCharacteristicDescriptors
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTC_FIND_INFO_REQ_T			* findInfoReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcReadCharacteristicValue
***************************************************************************//**
* 
*  This function reads a Characteristic Value from a GATT Server when the GATT
*  Client knows the Characteristic Value Handle. This is a non-blocking function.
* 
*  Internally, Read Request is sent to the peer device in response to which Read
*  Response is received. This response results in CYBLE_EVT_GATTC_READ_RSP event
*  which is propagated to the application for handling the event data. An Error
*  Response (CYBLE_EVT_GATTC_ERROR_RSP event at the GATT Client's end) is sent
*  by the GATT Server in response to the Read Request on insufficient 
*  authentication or insufficient authorization or insufficient encryption key
*  size is caused by the GATT Client, or if a read operation is not permitted on
*  the Characteristic Value. The Error Code parameter is set as specified in
*  the Attribute Protocol.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.8.1
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type
*               CYBLE_CONN_HANDLE_T.
*  \param readReqParam: Pointer to a variable of type CYBLE_GATTC_READ_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReadCharacteristicValue
(
	CYBLE_CONN_HANDLE_T				connHandle, 
	CYBLE_GATTC_READ_REQ_T			readReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcReadUsingCharacteristicUuid
***************************************************************************//**
* 
*  This function reads a Characteristic Value from the GATT Server when the GATT
*  Client only knows the characteristic UUID and does not know the handle of the
*  characteristic. This is a non-blocking function.
* 
*  Internally, Read By Type Request is sent to the peer device in response to
*  which Read By Type Response is received by the GATT Client. This results in
*  CYBLE_EVT_GATTC_READ_BY_TYPE_RSP event, which is propagated to the application
*  layer for further handling.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.8.2 for
*  more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param readByTypeReqParam: Parameter is of type CYBLE_GATTC_READ_BY_TYPE_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReadUsingCharacteristicUuid
(
	CYBLE_CONN_HANDLE_T						connHandle, 
	CYBLE_GATTC_READ_BY_TYPE_REQ_T			* readByTypeReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcReadLongCharacteristicValues
***************************************************************************//**
* 
*  This function reads a Characteristic Value from the GATT Server when the GATT
*  Client knows the Characteristic Value Handle and the length of the
*  Characteristic Value is longer than can be sent in a single Read Response
*  Attribute Protocol message. This is a non-blocking function.
* 
*  Internally multiple Read Blob Requests are sent to the peer device in response
*  to which Read Blob Responses are received. For each Read Blob Request, a Read
*  Blob Response event is received (CYBLE_EVT_GATTC_READ_BLOB_RSP) with a
*  portion of the Characteristic Value contained in the Part Attribute Value
*  parameter. These events are propagated to the application layer
*  for further processing. Each read blob response will return up to (GATT MTU-1) bytes of
*  data. If the size of characteristic value field is an integral multiple of (GATT MTU-1)
*  then the operation terminates with an error response event, where the error code is
*  CYBLE_GATT_ERR_INVALID_OFFSET. If the size of the characteristic value field is
*  not an integral multiple of (GATT MTU-1), the last read blob response will return
*  data bytes which are less than (GATT MTU-1). The application needs to monitor these two
*  conditions before proceeding with the initiation of any other GATT operation.
* 
*  An Error Response event (CYBLE_EVT_GATTC_ERROR_RSP) is sent by the GATT Server
*  in response to the Read Blob Request if insufficient authentication, 
*  insufficient authorization, insufficient encryption key size is used by the
*  client, or if a read operation is not permitted on the Characteristic Value.
*  The Error Code parameter is set as specified in the Attribute Protocol.
* 
*  If the Characteristic Value is not longer than (GATT MTU - 1), an Error Response
*  with the Error Code set to Attribute Not Long is received by the GATT Client
*  on the first Read Blob Request.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.8.3
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param readblobReqParam: Pointer to a variable of type CYBLE_GATTC_READ_BLOB_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReadLongCharacteristicValues
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTC_READ_BLOB_REQ_T			* readBlobReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcReadMultipleCharacteristicValues
***************************************************************************//**
* 
*  This function reads multiple Characteristic Values from a GATT Server when
*  the GATT Client knows the Characteristic Value Handles. This is a 
*  non-blocking function.
* 
*  Internally, Read Multiple Request is sent to the peer device in response to
*  which Read Multiple Response is received. This results in C
*  YBLE_EVT_GATTC_READ_MULTI_RSP event, which is propagated to the application
*  layer.
* 
*  An Error Response event is sent by the server (CYBLE_EVT_GATTC_ERROR_RSP) in
*  response to the Read Multiple Request if insufficient authentication, 
*  insufficient authorization, insufficient encryption key size is used by the
*  client, or if a read operation is not permitted on any of the Characteristic
*  Values. The Error Code parameter is set as specified in the Attribute
*  Protocol.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.8.4
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param readMultiReqParam: Pointer to a variable of type CYBLE_GATTC_READ_MULT_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReadMultipleCharacteristicValues
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTC_READ_MULT_REQ_T			* readMultiReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcWriteWithoutResponse
***************************************************************************//**
* 
*  This function writes a Characteristic Value to a GATT Server when the GATT
*  Client knows the Characteristic Value Handle and the client does not need an
*  acknowledgement that the write was successfully performed. This is a blocking
*  function. No event is generated on calling this function.
* 
*  Internally, Write Command is sent to the GATT Server and nothing is
*  received in response from the GATT Server.
* 
*  Refer Bluetooth 4.1 core specification, Volume 3, Part G, section 4.9.1
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param writeCmdReqParam: Pointer to a variable of type CYBLE_GATTC_WRITE_CMD_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcWriteWithoutResponse
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTC_WRITE_CMD_REQ_T			* writeCmdReqParam
);


#ifdef ATT_SIGNED_WRITE_SUPPORT

/******************************************************************************
* Function Name: CyBle_GattcSignedWriteWithoutRsp
***************************************************************************//**
* 
*  This function writes a Characteristic Value to a server when the client knows
*  the Characteristic Value Handle and the ATT Bearer is not encrypted. This 
*  procedure shall only be used if the Characteristic Properties
*  authenticated bit is enabled and the client and server device share a bond
*  as defined in Bluetooth Spec4.1 [Vol. 3] Part C, Generic Access Profile.
* 
*  This function only writes the first (ATT_MTU - 15) octets of an 
*  Attribute Value. This function cannot be used to write a long Attribute.
* 
*  Internally, Signed Write Command is used.
*  Refer Bluetooth Spec4.1 Security Manager [Vol. 3] Part H, Section 2.4.5.
* 
*  If the authenticated Characteristic Value that is written is the wrong size, 
*  has an invalid value as defined by the profile, or the signed value does not
*  authenticate the client, then the write shall not succeed and no error shall
*  be generated by the server.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param signedWriteWithoutRspParam: Pointer to a variable of type 
*                               CYBLE_GATTC_SIGNED_WRITE_CMD_REQ_T
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_INSUFFICIENT_RESOURCES   | BLE stack out of resource
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcSignedWriteWithoutRsp
(
	CYBLE_CONN_HANDLE_T			  			connHandle, 
	CYBLE_GATTC_SIGNED_WRITE_CMD_REQ_T		* signedWriteWithoutRspParam
);


#endif /*ATT_SIGNED_WRITE_SUPPORT*/


/******************************************************************************
* Function Name: CyBle_GattcWriteCharacteristicValue
***************************************************************************//**
* 
*  This function writes a Characteristic Value to a GATT Server when the GATT
*  Client knows the Characteristic Value Handle. This is a non-blocking function.
* 
*  Internally, Write Request is sent to the GATT Server in response to which
*  Write Response is received. This results in the event
*  CYBLE_EVT_GATTC_WRITE_RSP, which indicates that the write operation succeeded.
* 
*  An Error Response event (CYBLE_EVT_GATTC_ERROR_RSP) is sent by the server in
*  response to the Write Request if insufficient authentication, insufficient
*  authorization, insufficient encryption key size is used by the client, or if
*  a write operation is not permitted on the Characteristic Value. The Error 
*  Code parameter is set as specified in the Attribute Protocol.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section
*  4.9.3 for more details on the sequence of operations.
*     
*  \param connHandle: Connection handle to identify the peer GATT entity, of type
*               CYBLE_CONN_HANDLE_T.
*  \param writeReqParam: Pointer to a variable of type CYBLE_GATTC_WRITE_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcWriteCharacteristicValue
(
	CYBLE_CONN_HANDLE_T				connHandle, 
	CYBLE_GATTC_WRITE_REQ_T			* writeReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcWriteLongCharacteristicValues
***************************************************************************//**
* 
*  This function writes a Characteristic Value to a GATT Server when the GATT
*  Client knows the Characteristic Value Handle but the length of the
*  Characteristic Value is longer than GATT MTU size and cannot be sent in a single
*  Write Request Attribute Protocol message. This is a non-blocking function.
* 
*  Internally, multiple Prepare Write Requests are sent to the GATT Server in
*  response to which Prepare Write Responses are received. No events are
*  generated by the BLE Stack during these operations.
* 
*  Prepare Write Requests are repeated until the complete Characteristic Value
*  has been transferred to the GATT Server, after which an Execute Write Request
*  is sent to the GATT Server to write the initially transferred value at the
*  GATT Server's end. This generates CYBLE_EVT_GATTS_EXEC_WRITE_REQ at the GATT
*  Server's end.
* 
*  Once the GATT Server responds, CYBLE_EVT_GATTC_EXEC_WRITE_RSP event
*  is generated at the GATT Client's end. The value associated with this event
*  has to be checked by the application layer to confirm that the long write
*  operation succeeded.
* 
*  An Error Response event CYBLE_EVT_GATTC_ERROR_RSP is
*  received by the GATT Client in response to the Prepare Write Request if
*  insufficient authentication, insufficient authorization, insufficient
*  encryption key size is used by the client, or if a write operation is not
*  permitted on the Characteristic Value. The Error Code parameter is set as
*  specified in the Attribute Protocol.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.9.4
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param writePrepReqParam: Pointer to a variable of type CYBLE_GATTC_PREP_WRITE_REQ_T,
*                      where 'writePrepReqParam->value.val' points to the actual
* 					 data to be written. 'writePrepReqParam' and all associated
* 					 variables need to be retained in memory by the calling
* 					 application until the GATT Write Long Characteristic Value
*                      operation is completed successfully.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcWriteLongCharacteristicValues
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTC_PREP_WRITE_REQ_T		* writePrepReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcReliableWrites
***************************************************************************//**
* 
*  This function writes a Characteristic Value to a GATT Server when the GATT
*  Client knows the Characteristic Value Handle, and assurance is required
*  that the correct Characteristic Value is going to be written by transferring
*  the Characteristic Value to be written in both directions before the write
*  is performed. This is a non-blocking function.
* 
*  Internally, multiple Prepare Write Requests are sent to the GATT Server in
*  response to which Prepare Write Responses are received. No events are 
*  generated by the BLE Stack during these operations.
* 
*  Prepare Write Requests are repeated until the complete Characteristic Value
*  has been transferred to the GATT Server, after which an Execute Write Request
*  is sent to the GATT Server to write the initially transferred value at the
*  GATT Server's end. This generates CYBLE_EVT_GATTS_EXEC_WRITE_REQ at the GATT
*  Server's end.
* 
*  Once the GATT Server responds, a CYBLE_EVT_GATTC_EXEC_WRITE_RSP event is
*  generated at the GATT Client's end. The value associated with this event has 
*  to be checked by the application layer to confirm that the long write 
*  operation succeeded. An Error Response event CYBLE_EVT_GATTC_ERROR_RSP is 
*  received by the GATT Client in response to the Prepare Write Request if 
*  insufficient authentication, insufficient authorization, insufficient 
*  encryption key size is used by the client, or if a write operation is not 
*  permitted on the Characteristic Value. The Error Code parameter is set as 
*  specified in the Attribute Protocol.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.9.5
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param writePrepReqParam: Pointer to a variable of type CYBLE_GATTC_PREP_WRITE_REQ_T.
*                      Since more than one writes are performed as part of this 
*                      function, the first array element of the array of type 
*                      CYBLE_GATTC_PREP_WRITE_REQ_T, which contains the values to
*                      be written, has to be specified. 'writePrepReqParam' and 
*                      all associated variables need to be retained in memory by
*                      the calling application until the GATT Reliable Write 
*                      operation is completed successfully.
*  \param numOfRequests: Number of requests. That is, the count of array of structures 
*                  of type CYBLE_GATTC_PREP_WRITE_REQ_T. Each array element 
*                  represents a value and the attribute to which the value has 
*                  to be written.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReliableWrites
(
	CYBLE_CONN_HANDLE_T				connHandle, 
	CYBLE_GATTC_PREP_WRITE_REQ_T	* writePrepReqParam,
	uint8							numOfRequests
);


/******************************************************************************
* Function Name: CyBle_GattcConfirmation
***************************************************************************//**
* 
*  This function sends confirmation to the GATT Server on receiving Handle Value
*  Indication event CYBLE_EVT_GATTC_HANDLE_VALUE_IND at the GATT Client's end.
*  This is a non-blocking function.
* 
*  This function call results in CYBLE_EVT_GATTS_HANDLE_VALUE_CNF event at the
*  GATT Server's end.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.11.1
*  for more details on the sequence of operations.
*     
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcConfirmation(CYBLE_CONN_HANDLE_T connHandle);


/******************************************************************************
* Function Name: CyBle_GattcReadCharacteristicDescriptors
***************************************************************************//**
* 
*  This function reads a characteristic descriptor from a GATT Server when the
*  GATT Client knows the Attribute handle from the characteristic descriptor
*  declaration. This is a non-blocking function.
* 
*  Internally, Read Request is sent to the peer device in response to which
*  Read Response is received. This response results in CYBLE_EVT_GATTC_READ_RSP
*  event, which is propagated to the application for handling the event data.
* 
*  An Error Response (CYBLE_EVT_GATTC_ERROR_RSP event at the GATT Client's end) 
*  is sent by the GATT Server in response to the Read Request on insufficient
*  authentication or insufficient authorization or insufficient encryption
*  key size is caused by the GATT Client, or if a read operation is not
*  permitted on the Characteristic Value. The Error Code parameter is set as
*  specified in the Attribute Protocol.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.12.1
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param readReqParam: Pointer to a variable of type CYBLE_GATTC_READ_REQ_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReadCharacteristicDescriptors
(
	CYBLE_CONN_HANDLE_T				connHandle, 
	CYBLE_GATTC_READ_REQ_T			readReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcReadLongCharacteristicDescriptors
***************************************************************************//**
* 
*  This function reads a characteristic descriptor from a GATT Server when the
*  GATT Client knows the Attribute handle from the characteristic descriptor
*  declaration and the length of the characteristic descriptor declaration is
*  longer than what can be sent in a single Read Response Attribute Protocol
*  message. This is a non-blocking function.
* 
*  Internally multiple Read Blob Requests are sent to the peer device in response
*  to which Read Blob Responses are received. For each Read Blob Request, a Read
*  Blob Response event is received (CYBLE_EVT_GATTC_READ_BLOB_RSP) with a portion
*  of the Characteristic Value contained in the Part Attribute Value parameter.
*  These events are propagated to the application layer for further processing.
*  Each read blob response will return up to (GATT MTU-1) bytes of data. If the size of 
*  characteristic descriptor field is an integral multiple of (GATT MTU-1) then the 
*  operation terminates with an error response event, where the error code is
*  CYBLE_GATT_ERR_INVALID_OFFSET. If the size of the characteristic descriptor
*  field is not an integral multiple of (GATT MTU-1), the last read blob response will
*  return data bytes which are less than (GATT MTU-1). The application needs to monitor 
*  these two conditions before proceeding with the initiation of any other GATT
*  operation.
* 
*  An Error Response event (CYBLE_EVT_GATTC_ERROR_RSP) is sent by the GATT Server
*  in response to the Read Blob Request if insufficient authentication,
*  insufficient authorization, insufficient encryption key size is used by the
*  client, or if a read operation is not permitted on the Characteristic Value.
*  The Error Code parameter is set as specified in the Attribute Protocol. If
*  the Characteristic Value is not longer than (GATT MTU - 1) an Error Response with
*  the Error Code set to Attribute Not Long is received by the GATT Client on
*  the first Read Blob Request.
* 
*  Refer to Bluetooth 4.1 core specification,
*  Volume 3, Part G, section 4.12.2 for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param readBlonReqParam: Pointer to a variable of type CYBLE_GATTC_READ_BLOB_REQ_T
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReadLongCharacteristicDescriptors
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTC_READ_BLOB_REQ_T			* readBlobReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcWriteCharacteristicDescriptors
***************************************************************************//**
* 
*  This function writes a characteristic descriptor value to a GATT Server
*  when the GATT Client knows the characteristic descriptor handle. This is a
*  non-blocking function.
* 
*  Internally, Write Request is sent to the GATT Server in response to which
*  Write Response is received. This results in the event 
*  CYBLE_EVT_GATTC_WRITE_RSP, which indicates that the write operation succeeded.
* 
*  An Error Response event (CYBLE_EVT_GATTC_ERROR_RSP) is sent by the server in
*  response to the Write Request if insufficient authentication, insufficient 
*  authorization, insufficient encryption key size is used by the client, or if
*  a write operation is not permitted on the Characteristic Value. The Error 
*  Code parameter is set as specified in the Attribute Protocol.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.12.3
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param writeReqParam:  Pointer to a variable of type CYBLE_GATTC_WRITE_REQ_T
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcWriteCharacteristicDescriptors
(
	CYBLE_CONN_HANDLE_T		  			connHandle, 
	CYBLE_GATTC_WRITE_REQ_T				* writeReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcWriteLongCharacteristicDescriptors
***************************************************************************//**
* 
*  This function writes a characteristic descriptor value to a GATT Server
*  when the GATT Client knows the characteristic descriptor handle but the
*  length of the characteristic descriptor value is longer than what can be
*  sent in a single Write Request Attribute Protocol message. This is a
*  non-blocking function.
* 
*  Internally, multiple Prepare Write Requests are sent
*  to the GATT Server in response to which Prepare Write Responses are
*  received. No events are generated by the BLE Stack during these operations.
* 
*  Prepare Write Requests are repeated until the complete Characteristic
*  Descriptor Value has been transferred to the GATT Server, after which an
*  Execute Write Request is sent to the GATT Server to write the initially
*  transferred value at the GATT Server's end. This generates
*  CYBLE_EVT_GATTS_EXEC_WRITE_REQ at the GATT Server's end.
* 
*  Once the GATT Server responds, CYBLE_EVT_GATTC_EXEC_WRITE_RSP' event is
*  generated at the GATT Client's end. The value associated with this event has
*  to be checked by the application layer to confirm that the long write operation
*  succeeded.
* 
*  An Error Response event CYBLE_EVT_GATTC_ERROR_RSP is received by the GATT
*  Client in response to the Prepare Write Request if insufficient
*  authentication, insufficient authorization, insufficient encryption key
*  size is used by the client, or if a write operation is not permitted on the
*  Characteristic Value. The Error Code parameter is set as specified in the
*  Attribute Protocol.
* 
*  Refer Bluetooth 4.1 core specification, Volume 3,
*  Part G, section 4.12.4 for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param writePrepReqParam: Pointer to a variable of type CYBLE_GATTC_PREP_WRITE_REQ_T,
*                      where 'writePrepReqParam->value.val' points to the actual
*                      data to be written. 'writePrepReqParam' and all 
*                      associated variables need to be retained in memory	by the
*                      calling application until the GATT Write Long 
*                      Characteristic Descriptor operation is completed 
*                      successfully.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcWriteLongCharacteristicDescriptors
(
	CYBLE_CONN_HANDLE_T			  			connHandle, 
	CYBLE_GATTC_PREP_WRITE_REQ_T			* writePrepReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcReadByTypeReq
***************************************************************************//**
* 
*  This function allows the user to send Read by type request to peer server
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.5.1 
*  for more details on the sequence of operations.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  readByTypeReqParam	: Pointer to a variable of type CYBLE_GATTC_READ_BY_TYPE_REQ_T,
* 					Where, the following needs to be set:
* 					readByTypeReqParam->range.startHandle
* 					readByTypeReqParam->range.endHandle
* 					readByTypeReqParam->uuidFormat (CYBLE_GATT_16_BIT_UUID_FORMAT or
* 													CYBLE_GATT_128_BIT_UUID_FORMAT)
* 					readByTypeReqParam->uuid.uuid16 or readByTypeReqParam->uuid.uuid128 
* 					based on the uuidFormat
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
*     
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcReadByTypeReq
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTC_READ_BY_TYPE_REQ_T  	* readByTypeReqParam
);


/******************************************************************************
* Function Name: CyBle_GattcSendExecuteWriteReq
***************************************************************************//**
* 
*  This function allows the user to send execute write request to remote server.
*  This function should be called if client has previously initiated long/reliable 
*  write operation and remote has send error response. Based on error response 
*  application may choose to execute all pending requests or cancel the request.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity of type 
*               CYBLE_CONN_HANDLE_T.
*  \param flag: Indicates whether Queued Write is to be executed (0x01) or canceled (0x00)
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not  represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
*     
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcSendExecuteWriteReq
(
	CYBLE_CONN_HANDLE_T		connHandle, 
	uint8  					flag
);

/** @} */

#endif /* CY_BLE_CYBLE_STACK_GATT_CLIENT_H */


/* EOF */
