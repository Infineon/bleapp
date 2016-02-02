/***************************************************************************//**
* \file CYBLE_StackGattServer.h
* \version 2.30
* 
* \brief
*  This file contains the GATT Server routines
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


#ifndef CY_BLE_CYBLE_STACK_GATT_SERVER_INTERNAL_H
#define CY_BLE_CYBLE_STACK_GATT_SERVER_INTERNAL_H


/***************************************
* Common stack includes
***************************************/

#include "BLE_StackGatt.h"


/***************************************
* Constants
***************************************/

#ifdef ATT_QUEUED_WRITE_SUPPORT
#define CYBLE_GATTS_PREP_WRITE_SUPPORT					0x01u
#define CYBLE_GATTS_PREP_WRITE_NOT_SUPPORT				0x00u
#define CYBLE_GATTS_FIRST_PREP_WRITE_REQ                1u
#endif


/***************************************
* Exported structures
***************************************/

/** Handle value notification data to be sent to Client */
typedef CYBLE_GATT_HANDLE_VALUE_PAIR_T CYBLE_GATTS_HANDLE_VALUE_NTF_T;

/** GATT handle value indication parameter type */
typedef CYBLE_GATT_HANDLE_VALUE_PAIR_T CYBLE_GATTS_HANDLE_VALUE_IND_T;

/** GATT Server Error Response parameter type */
typedef struct
{
    /** Handle in which error is generated */
    CYBLE_GATT_DB_ATTR_HANDLE_T    	attrHandle;

    /** Opcode which has resulted in Error 
       Information on ATT/GATT opcodes is available in the 
       Bluetooth specification.
    */
    uint8              				opcode;

    /** Error Code describing cause of error */
    CYBLE_GATT_ERR_CODE_T			errorCode;
	
}CYBLE_GATTS_ERR_PARAM_T;

/** Read response parameter to be sent to Client */
typedef CYBLE_GATT_VALUE_T CYBLE_GATTS_READ_RSP_PARAM_T;

/** Prepare write request parameter received from Client */
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 						connHandle; 			

	/** Base address of the queue where data is queued, Queue is of type 
	   CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T. 
	   Each baseAddr[currentPrepWriteReqCount-1].handleValuePair.value.val
	   provides the current data and baseAddr[0].handleValuePair.value.val
	   provides the base address of the data buffer where full value will be stored.
	   Application can calculate the total length based on each each array element.
	   i.e total length up current request = baseAddr[0].handleValuePair.value.len+
	   ....+baseAddr[currentPrepWriteReqCount-1].handleValuePair.value.len
	*/
    CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T 		*baseAddr;	

	/** Current count of prepare request from remote. This parameter can be used 
	   to access the data from 'baseAddr[]'. Array index will range from 0 to 
	   currentPrepWriteReqCount - 1 */	
	uint8	  									currentPrepWriteReqCount;

	/** Application provide GATT error code for the procedure. This is an o/p parameter */
    uint8 										gattErrorCode;	

}CYBLE_GATTS_PREP_WRITE_REQ_PARAM_T;

/** Execute Write result */
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 						connHandle; 

	/** Base address of the queue where data is queued. Queue is of type 
	   CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T. 
	   baseAddr[0].handleValuePair.value.val
	   provides the base address of the total data stored in prepare write
	   queue internally by stack. 
	   Application can calculate the total length based on each each array element.
	   i.e total length = baseAddr[0].handleValuePair.value.len+
	   ....+baseAddr[prepWriteReqCount-1].handleValuePair.value.len
	*/	
	CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T	  	*baseAddr;

	/** Total count of prepare request from remote. This parameter can be used 
	   to access the data from 'baseAddr[]'. array index will range from 0 to 
	   prepWriteReqCount - 1 */	
	uint8	  									prepWriteReqCount;

	/** Execute write flag received from remote */
    uint8 										execWriteFlag;

	/** Attribute Handle at which error occurred. This is an o/p param  */
    CYBLE_GATT_DB_ATTR_HANDLE_T	  				attrHandle;     
	
	/** Application provide GATT error code for the procedure. This is an o/p param */
    uint8 										gattErrorCode;

}CYBLE_GATTS_EXEC_WRITE_REQ_T;

/** Write request parameter received from Client */
typedef struct
{
	/** Connection handle */
	CYBLE_CONN_HANDLE_T 				connHandle; 

	/** handle value pair */
    CYBLE_GATT_HANDLE_VALUE_PAIR_T    	handleValPair; 
	
}CYBLE_GATTS_WRITE_REQ_PARAM_T;

/** Write command request parameter received from Client */
typedef CYBLE_GATTS_WRITE_REQ_PARAM_T  CYBLE_GATTS_WRITE_CMD_REQ_PARAM_T;

/** Signed Write command request parameter received from Client */
typedef CYBLE_GATTS_WRITE_REQ_PARAM_T  CYBLE_GATTS_SIGNED_WRITE_CMD_REQ_PARAM_T;

/** Prepare write response parameter to be sent to Client */
typedef CYBLE_GATT_HANDLE_VALUE_OFFSET_PARAM_T CYBLE_GATTS_PREP_WRITE_RSP_PARAM_T;

/* Event parameters for characteristic read value access
 * even generated by BLE Stack upon an access of Characteristic value
 * read for the characteristic definition which has 
 * CYBLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT property set.
 **/
typedef struct
{
    /** Connection handle */
    CYBLE_CONN_HANDLE_T             connHandle;

    /** Attribute Handle*/
    CYBLE_GATT_DB_ATTR_HANDLE_T     attrHandle;

    /** Output Param: Profile/Service specific error code,
     * profile or application need to change this 
     * to service specific error based on service/profile
     * requirements. */
    CYBLE_GATT_ERR_CODE_T           gattErrorCode;

}CYBLE_GATTS_CHAR_VAL_READ_REQ_T;

/** @} */

/**
 \addtogroup group_common_api_gatt_server_functions
 @{
*/

/***************************************
* Exported APIs
***************************************/

/******************************************************************************
* Function Name: CyBle_GattsNotification
***************************************************************************//**
* 
*  This function sends a notification to the peer device when the GATT Server
*  is configured to notify a Characteristic Value to the GATT Client without
*  expecting any Attribute Protocol layer acknowledgment that the notification
*  was successfully received. This is a non-blocking function.
* 
*  On enabling notification successfully for a specific attribute, if the GATT server has an
*  updated value to be notified to the GATT Client, it sends out a 'Handle Value
*  Notification' which results in CYBLE_EVT_GATTC_HANDLE_VALUE_NTF event at the
*  GATT Client's end.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.10 for
*  more details on notifications.
*  
*  \param connHandle: Connection handle to identify the peer GATT entity, of type
*              CYBLE_CONN_HANDLE_T.
*  \param ntfParam: Pointer to structure of type CYBLE_GATTS_HANDLE_VALUE_NTF_T which is same as 
* 		 CYBLE_GATT_HANDLE_VALUE_PAIR_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | 'connHandle' value does not represent any existing entry in the Stack
*   CYBLE_ERROR_INVALID_OPERATION        | This operation is not permitted as BLE Stack is busy processing previous requests.
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattsNotification
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTS_HANDLE_VALUE_NTF_T		* ntfParam
);


/******************************************************************************
* Function Name: CyBle_GattsIndication
***************************************************************************//**
* 
*  This function sends an indication to the peer device when the GATT Server is
*  configured to indicate a Characteristic Value to the GATT Client and expects
*  an Attribute Protocol layer acknowledgement that the indication was 
*  successfully received. This is a non-blocking function.
* 
*  On enabling indication successfully, if the GATT server has an updated value to be 
*  indicated to the GATT Client, it sends out a 'Handle Value Indication' which
*  results in CYBLE_EVT_GATTC_HANDLE_VALUE_IND event at the GATT Client's end.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.11 for
*  more details on Indications.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*               CYBLE_CONN_HANDLE_T.
*  \param indParam: Pointer to structure of type CYBLE_GATTS_HANDLE_VALUE_IND_T which is same as 
* 		 CYBLE_GATT_HANDLE_VALUE_PAIR_T.
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
CYBLE_API_RESULT_T CyBle_GattsIndication
(
	CYBLE_CONN_HANDLE_T					connHandle, 
	CYBLE_GATTS_HANDLE_VALUE_IND_T		* indParam
);


/******************************************************************************
* Function Name: CyBle_GattsErrorRsp
***************************************************************************//**
* 
*  This function sends an error response to the peer device. The Error Response
*  is used to state that a given request cannot be performed, and to provide the
*  reason as defined in 'CYBLE_GATT_ERR_CODE_T'. This is a non-blocking function.
* 
*  Note that the 'Write Command' initiated by GATT Client does not generate an
*  'Error Response' from the GATT Server's end. The GATT Client gets 
*  CYBLE_EVT_GATTC_ERROR_RSP event on receiving error response.
* 
*  Refer Bluetooth 4.1 core specification, Volume 3, Part F, section 3.4.1.1 for
*  more details on Error Response operation.
*  
*  \param connHandle: Connection handle to identify the peer GATT entity, of type
*               CYBLE_CONN_HANDLE_T.
*  \param errRspParam: Pointer to structure of type CYBLE_GATTS_ERR_PARAM_T.
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
CYBLE_API_RESULT_T CyBle_GattsErrorRsp
(
	CYBLE_CONN_HANDLE_T			connHandle, 
	CYBLE_GATTS_ERR_PARAM_T		* errRspParam
);


/******************************************************************************
* Function Name: CyBle_GattsExchangeMtuRsp
***************************************************************************//**
* 
* This function sends the GATT Server's GATT MTU size to the GATT Client. This
* function has to be invoked in response to an Exchange GATT MTU Request received
* from the GATT Client. The GATT Server's GATT MTU size should be greater than or 
* equal to the default GATT MTU size (23 bytes). This is a non-blocking function.
* 
* The peer GATT Client receives CYBLE_EVT_GATTC_XCHNG_MTU_RSP event on executing
* this function on the GATT Server.
* 
* Refer to Bluetooth 4.1 core specification, Volume 3, Part G, section 4.3.1 for
* more details on exchange of GATT MTU.
* 
*  \param connHandle: Connection handle to identify the peer GATT entity, of type 
*              CYBLE_CONN_HANDLE_T.
*  \param mtu: Size of GATT MTU, of type uint16
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
*    <td>If 'l2capPsm' is 0</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INSUFFICIENT_RESOURCES</td>
*    <td>Cannot register more than one PSM</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_L2CAP_PSM_WRONG_ENCODING</td>
*    <td>PSM value must be an odd number and the Most Significant Byte 
         must have Least Significant Bit value set to '0'. If PSM does not 
		 follow this guideline, this return code is generated.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_L2CAP_PSM_ALREADY_REGISTERED</td>
*    <td>PSM already Registered</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattsExchangeMtuRsp
(
	CYBLE_CONN_HANDLE_T			connHandle, 
	uint16 						mtu
);


#ifdef ATT_QUEUED_WRITE_SUPPORT

/******************************************************************************
* Function Name: CyBle_GattsPrepWriteReqSupport
***************************************************************************//**
* 
*  This API needs to be called after getting CYBLE_EVT_GATTS_PREP_WRITE_REQ 
*  event from the BLE Stack to support prepare write request operation. 
*  This API should be called only once during one Long/reliable write session. 
*  This needs to be called from the same event call back context. 
*  This is a non-blocking function.
* 
*  On receiving CYBLE_EVT_GATTS_PREP_WRITE_REQ, returning from the event handler
*  without calling this function will result in prepare write response being 
*  sent to the peer device rejecting the prepare write operation. 
*  CYBLE_GATT_ERR_REQUEST_NOT_SUPPORTED error code will be sent to client.
* 
*  \param prepWriteSupport: If prepare write operation  is supported by the application
*                     then the application layer should set this variable to 
*                     CYBLE_GATTS_PREP_WRITE_SUPPORT. Any other value will 
*                     result in the device rejecting the prepare write operation.
*                     Allowed values for this parameter
*                      * CYBLE_GATTS_PREP_WRITE_SUPPORT
*                      * CYBLE_GATTS_PREP_WRITE_NOT_SUPPORT
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattsPrepWriteReqSupport
(
	uint8	 	prepWriteSupport
);


#endif /* ATT_QUEUED_WRITE_SUPPORT */


/******************************************************************************
* Function Name: CyBle_GattsWriteRsp
***************************************************************************//**
* 
*  This function sends a Write Response from a GATT Server to the GATT Client.
*  This is a non-blocking function. This function has to be invoked in
*  response to a valid Write Request event from the GATT Client
*  (CYBLE_EVT_GATTS_WRITE_REQ) to acknowledge that the attribute has been
*  successfully written.
* 
*  The Write Response has to be sent after the attribute value is written or 
*  saved by the GATT Server. Write Response results in CYBLE_EVT_GATTC_WRITE_RSP
*  event at the GATT Client's end.
* 
* \param connHandle: Connection handle to identify the peer GATT entity, of type
* 	         CYBLE_CONN_HANDLE_T.
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
CYBLE_API_RESULT_T CyBle_GattsWriteRsp
(
	CYBLE_CONN_HANDLE_T	 connHandle 
);

/** @} */
#endif /*CY_BLE_CYBLE_STACK_GATT_SERVER_INTERNAL_H*/


 /*EOF*/
