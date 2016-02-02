/***************************************************************************//**
* \file CYBLE_StackL2cap.h
* \version 2.30
* 
* \brief
*  This file contains the L2CAP APIs of the BLE Host Stack IP
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
 \addtogroup group_common_api_l2cap_definitions
 @{
*/


#ifndef CY_BLE_CYBLE_STACK_L2CAP_H
#define CY_BLE_CYBLE_STACK_L2CAP_H


/***************************************
* Common stack includes
***************************************/

#include "BLE_StackGap.h"


/***************************************
* Exported Constants
***************************************/

#ifdef L2CAP_SUPPORT_CBFC_MODE

/* Protocol and Service Multiplexers (PSMs) */
#define CYBLE_L2CAP_PSM_SDP                         0x0001u
#define CYBLE_L2CAP_PSM_RFCOMM                      0x0003u
#define CYBLE_L2CAP_PSM_TCS_BIN                     0x0005u
#define CYBLE_L2CAP_PSM_TCS_BIN_CORDLESS            0x0007u
#define CYBLE_L2CAP_PSM_BNEP                        0x000Fu
#define CYBLE_L2CAP_PSM_HID_CONTROL                 0x0011u
#define CYBLE_L2CAP_PSM_HID_INTERRUPT               0x0013u
#define CYBLE_L2CAP_PSM_UPNP                        0x0015u
#define CYBLE_L2CAP_PSM_AVCTP                       0x0017u
#define CYBLE_L2CAP_PSM_AVDTP                       0x0019u
#define CYBLE_L2CAP_PSM_AVCTP_BROWSING              0x001Bu
#define CYBLE_L2CAP_PSM_UDI_C_PLANE                 0x001Du
#define CYBLE_L2CAP_PSM_ATT                         0x001Fu
#define CYBLE_L2CAP_PSM_3DSP                        0x0021u
#define CYBLE_L2CAP_PSM_LE_PSM_IPSP                 0x0023u
    
/* L2CAP Invalid PSM */
#define CYBLE_L2CAP_PSM_INVALID                     0x0000u

/* L2CAP Header Size */
#define CYBLE_L2CAP_HDR_LEN                         4u
#define CYBLE_L2CAP_CREDIT_MODE_HDR_LEN             6u

/* L2CAP Connect Results */
#define CYBLE_L2CAP_CONNECTION_SUCCESSFUL                     			0x0000u
#define CYBLE_L2CAP_CONNECTION_PENDING                        			0x0001u
#define CYBLE_L2CAP_CONNECTION_REFUSED_PSM_UNSUPPORTED        			0x0002u
#define CYBLE_L2CAP_CONNECTION_REFUSED_SECURITY_BLOCK         			0x0003u
#define CYBLE_L2CAP_CONNECTION_REFUSED_NO_RESOURCE            			0x0004u
#define CYBLE_L2CAP_CONNECTION_REFUSED_AUTHENTICATION_INSUFFICIENT      0x0005u
#define CYBLE_L2CAP_CONNECTION_REFUSED_AUTHORIZATION_INSUFFICIENT       0x0006u
#define CYBLE_L2CAP_CONNECTION_REFUSED_ENC_KEY_SIZE_INSUFFICIENT        0x0007u

    
    
/*##Response codes for Connection parameter update request */

/* Connection Parameters accepted */
#define CYBLE_L2CAP_CONN_PARAM_ACCEPTED   			0x0000u

/* Connection Parameters rejected */
#define CYBLE_L2CAP_CONN_PARAM_REJECTED   			0x0001u

/* Config Parameter index for PSM */
#define CYBLE_L2CAP_CONFIG_POS_PSM            	    0x00u

/* Config Parameter index for CBFC Channel */
#define CYBLE_L2CAP_CONFIG_POS_CHANNEL	            0x01u

/* Config Parameter index for L2CAP Signalling timeout */
#define CYBLE_L2CAP_CONFIG_POS_SIG_TO	            0x02u


/***************************************
* Exported Enumerations
***************************************/

/** Reason for command reject event - CYBLE_EVT_L2CAP_COMMAND_REJ */
typedef enum
{
	/** Command Not Understood */
	CYBLE_L2CAP_COMMAND_NOT_UNDERSTOOD = 0x0000u,
	
	/** Signaling L2CAP MTU exceeded */
	CYBLE_L2CAP_SIGNALLING_MTU_EXCEEDED,
	
	/** Invalid Connection Identifier in request */
	CYBLE_L2CAP_INVALID_CID_IN_REQUEST

}CYBLE_L2CAP_COMMAND_REJ_REASON_T;

/** The result code of call back structures for L2CAP */
typedef enum
{
	/** Operation Successful */
	CYBLE_L2CAP_RESULT_SUCCESS = 0x0000u,

	/** Command timeout,  if l2cap signaling channel timeout occurs, app should disconnect.*/
	CYBLE_L2CAP_RESULT_COMMAND_TIMEOUT = 0x2318u,

	/** Invalid sdu length */
	CYBLE_L2CAP_RESULT_INCORRECT_SDU_LENGTH = 0x2347u,

	/** Not enough credit to perform this operation */
	CYBLE_L2CAP_RESULT_NOT_ENOUGH_CREDITS = 0x2371u,
	
	/** Credit overflow. Total credit exceeded 65535 (maximum) */
	CYBLE_L2CAP_RESULT_CREDIT_OVERFLOW = 0x2373u,
	
	/** Invalid credit value, receive credit is Zero */
	CYBLE_L2CAP_RESULT_UNACCEPTABLE_CREDIT_VALUE = 0x2374u

}CYBLE_L2CAP_RESULT_PARAM_T;


/***************************************
* Exported data types
***************************************/

/** L2CAP Credit based flow Connection parameter */
typedef struct 
{
  /** L2CAP MTU - Maximum SDU Size
 
       The L2CAP MTU field specifies the maximum SDU size (in octets) that the L2CAP
       layer entity sending the LE Credit Based Connection Request can receive
       on this channel. L2CAP implementations shall support a minimum L2CAP MTU size
       of 23 octets. */
    uint16   mtu;

  /** MPS - Maximum PDU Size 
 
       The MPS field specifies the maximum payload size (in octets) that the
       L2CAP layer entity sending the LE Credit Based Connection Request is
       capable of receiving on this channel. L2CAP implementations shall support
       a minimum MPS of 23 octets and may support an MPS up to 65488 octets. */
    uint16   mps;

  /** Initial number of Credits
 
       The initial credit value indicates the number of LE-frames that the peer
       device can send to the L2CAP layer entity sending the LE Credit Based
       Connection Request. The initial credit value shall be in the range of 0 to
       65535. */
    uint16   credit;

}CYBLE_L2CAP_CBFC_CONNECT_PARAM_T;

/** Connect indication parameter*/
typedef struct
{
	/** bd handle of the remote device */
	uint8 								bdHandle;

	/** Local CID */
	uint16 								lCid; 

	/** PSM value for the Protocol */
	uint16 								psm; 

	/** L2CAP Credit based flow Connection parameter */
	CYBLE_L2CAP_CBFC_CONNECT_PARAM_T 	connParam;

}CYBLE_L2CAP_CBFC_CONN_IND_PARAM_T;

/** Connect confirmation parameter*/
typedef struct
{
	/** bd handle of the remote device */
	uint8 								bdHandle;

	/** Local CID*/
	uint16 								lCid; 

	/** Response codes for Connection parameter update request */
	uint16 								response; 

	/** L2CAP Credit based flow Connection parameter */
	CYBLE_L2CAP_CBFC_CONNECT_PARAM_T 	connParam;

}CYBLE_L2CAP_CBFC_CONN_CNF_PARAM_T;

/** Disconnect confirmation parameter */
typedef struct
{
	/** Local CID */
	uint16 							lCid; 

	/** The result field indicates the outcome of the connection request. The result
	   value of 0x0000 indicates success while a non-zero value indicates the connection
	   request failed or is pending. */
	CYBLE_L2CAP_RESULT_PARAM_T 		result; 

}CYBLE_L2CAP_CBFC_DISCONN_CNF_PARAM_T;

/** Receive Data parameter */
typedef struct
{
	/** Local CID */
	uint16 							lCid; 

	/** A result value of 0x0000 indicates success, while a non-zero value
	   indicates an error condition (e.g. peer device violating credit flow, or L2CAP MTU size limit) */
	CYBLE_L2CAP_RESULT_PARAM_T 		result; 

	/** Received L2cap Data */
	uint8						*	rxData;
	
	/** Received L2cap Data Length */
	uint16		rxDataLength;

}CYBLE_L2CAP_CBFC_RX_PARAM_T;

/** Rx credit info parameter*/
typedef struct
{
	/** Local CID */
	uint16 		lCid; 

   /** The number of credits (LE-frames) */
	uint16 		credit; 

}CYBLE_L2CAP_CBFC_LOW_RX_CREDIT_PARAM_T;

/** Tx credit info parameter */
typedef struct
{
	/** Local CID */
	uint16 							lCid; 

	/** A result value of 0x0000 indicates success, while a non-zero value
	   indicates an error condition (e.g. credit overflow, if total number of credits
       crosses specification defined maximum limit of 0xFFFF) */
	CYBLE_L2CAP_RESULT_PARAM_T	   	result; 

   /** The number of credits (LE-frames) */
	uint16 							credit; 

}CYBLE_L2CAP_CBFC_LOW_TX_CREDIT_PARAM_T;

/** Data Write parameter*/
typedef struct
{
	/**Local CID*/
	uint16 							lCid; 

	/** The result field indicates the outcome of the connection request. The result
	value of 0x0000 indicates success while a non-zero value indicates the connection
	request failed or is pending. */
	CYBLE_L2CAP_RESULT_PARAM_T 		result; 

	/** Currently NULL. For future usage */
	uint8 							* buffer;

	/** Currently 0. For future usage */
	uint16 							bufferLength;	

}CYBLE_L2CAP_CBFC_DATA_WRITE_PARAM_T;

/** @} */

/***************************************
* Exported APIs
***************************************/

/**
 \addtogroup group_common_api_l2cap_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_L2capCbfcRegisterPsm
***************************************************************************//**
* 
*  This function registers a new upper layer protocol or PSM to L2CAP, along 
*  with the set of callbacks for the L2CAP Credit Based Flow Control mode. This
*  is a blocking function. No event is generated on calling this function.
* 
*  Refer Bluetooth 4.1 core specification, Volume 3, Part A, section 3.4 
*  for more details about credit based flow control mode of operation.
* 
*  \param l2capPsm: PSM value of the higher-level protocol 
*  \param creditLwm: Upper Layer defined Receive Credit Low Mark
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
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
*   <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*   <td>If 'l2capPsm' is 0</td>
*  </tr>
*  <tr>
*   <td>CYBLE_ERROR_INSUFFICIENT_RESOURCES</td>
*    <td>Cannot register more than one PSM</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_L2CAP_PSM_WRONG_ENCODING</td>
*    <td>PSM value must be an odd number and the Most Significant 
         Byte must have Least Significant Bit value set to '0'. 
		 If PSM does not follow this guideline, this return code is generated.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_L2CAP_PSM_ALREADY_REGISTERED</td>
*    <td>PSM already Registered</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capCbfcRegisterPsm
           (
               uint16 l2capPsm,
               uint16 creditLwm
           );


/******************************************************************************
* Function Name: CyBle_L2capCbfcUnregisterPsm
***************************************************************************//**
* 
*  This function de-registers an upper layer protocol or LE_PSM from L2CAP for 
*  the L2CAP Credit Based Flow Control mode. This is a blocking function. No 
*  event is generated on calling this function.
* 
*  \param l2capPsm: PSM value of the higher-level protocol 
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
*   CYBLE_ERROR_L2CAP_PSM_WRONG_ENCODING | L2CAP PSM value specified is incorrect or does not exist
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capCbfcUnregisterPsm (uint16 l2capPsm);


/******************************************************************************
* Function Name: CyBle_L2capCbfcConnectReq
***************************************************************************//**
* 
*  This L2CAP function initiates L2CAP channel establishment procedure in Credit
*  Based Flow Control (CBFC) mode. Connection establishment is initiated to the
*  specified remote Bluetooth device, for the specified PSM representing an 
*  upper layer protocol above L2CAP. This is a non-blocking function.
* 
*  At the receiver's end, CYBLE_EVT_L2CAP_CBFC_CONN_IND event is generated.
*  In response to this call, CYBLE_EVT_L2CAP_CBFC_CONN_CNF event is generated
*  at the sender's end.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part A, section 4.22 for
*  more details about this operation.
* 
*  \param bdHandle: Peer device handle.
*  \param remotePsm: Remote PSM, representing the upper layer protocol above L2CAP.
*  \param localPsm: Local PSM, representing the upper layer protocol above L2CAP.
*  \param param: This parameter must be a pointer to the 
*          CYBLE_L2CAP_CBFC_CONNECT_PARAM_T variable containing the connection
*          parameters for the L2CAP channel.
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                        	 | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | If "param" is NULL
*   CYBLE_ERROR_INSUFFICIENT_RESOURCES   | Insufficient resources
*   CYBLE_L2CAP_PSM_NOT_REGISTERED       | PSM not Registered
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capCbfcConnectReq
           (
                uint8        					 bdHandle,
                uint16                    		 remotePsm,
                uint16                    		 localPsm,
                CYBLE_L2CAP_CBFC_CONNECT_PARAM_T  * param
           );


/******************************************************************************
* Function Name: CyBle_L2capCbfcConnectRsp
***************************************************************************//**
* 
*  This L2CAP function enables an upper layer protocol to respond to L2CAP 
*  connection request for LE Credit Based Flow Control mode of the specified PSM
*  from the specified remote Bluetooth device. This is a non-blocking function. 
*  It is mandatory that the upper layer PSM always responds back by calling this
*  function upon receiving CBFC Connection Request 
*  (CYBLE_EVT_L2CAP_CBFC_CONN_IND) event.
* 
*  The channel is established (opened) only when the PSM concerned responds back
*  with an event indicating success (CYBLE_EVT_L2CAP_CBFC_CONN_CNF, at the peer
*  device's end). Otherwise, the channel establishment request from the peer 
*  will be rejected by L2CAP with appropriate result and status as received 
*  from the upper layer PSM.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part A, section 4.23
*  for more details about this operation.
* 
*  \param localCid: This parameter specifies the local L2CAP channel end-point for this
*             new L2CAP channel. On receipt of L2CAP Connect Request command 
*             from the peer, local L2CAP will temporarily create a channel. 
*             This parameter identifies the new channel. If the upper layer PSM 
*             chooses to reject this connection, this temporary channel will be 
*             closed.
*  \param response: This parameter specifies the response of the upper layer for the
*             new L2CAP channel establishment request from the peer. It must be
*             set to a value as specified in L2CAP Connect Result Codes. Refer
*             to Bluetooth 4.1 core specification, Volume 3, Part A, section 
*             4.23 for more details.
*  \param param: This parameter must be a pointer to the 
*          CYBLE_L2CAP_CBFC_CONNECT_PARAM_T variable containing the connection
*          parameters for the L2CAP channel.
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                                      | Description
*  ------------                                      | -----------
*   CYBLE_ERROR_OK                                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER                    | If "param" is NULL
*   CYBLE_ERROR_L2CAP_CONNECTION_ENTITY_NOT_FOUND    | Connection entity is not found
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capCbfcConnectRsp
           (
                uint16 								localCid,
                uint16 								response,
                CYBLE_L2CAP_CBFC_CONNECT_PARAM_T 	* param
           );


/******************************************************************************
* Function Name: CyBle_L2capCbfcSendFlowControlCredit
***************************************************************************//**
* 
*  This L2CAP function enables an upper layer protocol to send LE Flow Control 
*  Credit packet to peer Bluetooth device, when it is capable of receiving
*  additional LE-frames. This is a non-blocking function.
* 
*  This function is invoked when the device is expecting more data from the peer
*  device and it gets an event indicating that the peer device is low on credits
*  CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND for which it needs to respond by sending
*  credits by invoking this function. Once the peer device receives these credits,
*  it gets CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND event indicating the same. It is
*  the responsibility of the application layer of the device sending the credit
*  to keep track of the total number of credits and making sure that it does
*  not exceed 65535.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part A, section 4.24 for
*  more details about this operation.
* 
* \param localCid: This parameter specifies the local channel end-point for the L2CAP 
*            channel. For the initiator of L2CAP channel establishment, this must
*            be set to the value indicated by the CYBLE_EVT_L2CAP_CBFC_CONN_CNF
*            event. For the responder, the upper layer protocol obtains this 
*            value when it receives the event CYBLE_EVT_L2CAP_CBFC_CONN_IND.
* 
* \param credit: The credit value field represents number of credits the receiving 
*          device can increment. The credit value field is a number between 1 and
*          65535.
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*  ------------                              | -----------
*   CYBLE_ERROR_OK                           | On successful operation
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED     | Memory allocation failed
*   CYBLE_L2CAP_CONNECTION_ENTITY_NOT_FOUND  | L2CAP connection instance is not present
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capCbfcSendFlowControlCredit
           (
                uint16 	localCid,
                uint16 	credit
           );


/******************************************************************************
* Function Name: CyBle_L2capChannelDataWrite
***************************************************************************//**
* 
*  This function sends a data packet on the L2CAP CBFC channel. This is a 
*  blocking function. 
* 
*  This API generates 'CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND' event which 
*  is kept for backward compatibility and the user should handle CYBLE_API_RESULT_T
*  to determine whether the last data packet was sent out properly.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part A, section 3.4 for 
*  more details about this operation.
* 
*  \param bdHandle: Peer device handle.
*  \param localCid: This parameter specifies the local channel end-point for the L2CAP
*             channel. For the initiator of L2CAP channel establishment, this 
*             must be set to the value indicated by the 
*             CYBLE_EVT_L2CAP_CBFC_CONN_CNF event. For the responder, the upper
*             layer protocol obtains this value when it receives the event
*             CYBLE_EVT_L2CAP_CBFC_CONN_IND.
*  \param buffer: Buffer containing packet to be sent.
*  \param bufferLen: L2CAP Data Packet length. It shall be of lesser than the size
*             of both local L2CAP MTU & peer L2CAP MTU size.
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*  ------------                              | -----------
*   CYBLE_ERROR_OK                           | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER            | If "buffer" is NULL
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED     | Memory allocation failed
*   CYBLE_ERROR_NO_CONNECTION                | No Link Layer connection is present
*   CYBLE_L2CAP_CHANNEL_NOT_FOUND            | No L2ACP channel found corresponding to CID
*   CYBLE_L2CAP_NOT_ENOUGH_CREDITS           | Not Enough Credits to transfer data
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capChannelDataWrite
            (
                 uint8			 bdHandle,
                 uint16          localCid,
                 uint8*          buffer,
                 uint16          bufferLen
            );


/******************************************************************************
* Function Name: CyBle_L2capDisconnectReq
***************************************************************************//**
* 
*  This function initiates sending of an L2CAP Disconnect Request 
*  (CYBLE_EVT_L2CAP_CBFC_DISCONN_IND event received by the peer device) command 
*  to the remote L2CAP entity to initiate disconnection of the referred L2CAP 
*  channel. This is a non-blocking function.
* 
*  Disconnection of the L2CAP channel always succeeds - either by reception of 
*  the L2CAP Disconnect Response from the peer, or by timeout. In any case, 
*  L2CAP will confirm disconnection of the channel, by calling the 
*  CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF event.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part A, section 4.6 for
*  more details about this operation.
* 
* \param localCid: This parameter specifies the local channel end-point for the L2CAP
*            channel.
*            * For initiator of L2CAP channel establishment, this must be set to
*               the value indicated by the event CYBLE_EVT_L2CAP_CBFC_CONN_CNF.
*            * For the responder, the upper layer protocol obtains this value
*               when it receives the event CYBLE_EVT_L2CAP_CBFC_CONN_IND.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*  ------------                              | -----------
*   CYBLE_ERROR_OK                           | On successful operation
*   CYBLE_ERROR_INVALID_OPERATION            | No Link Layer connection is present
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED     | Memory allocation failed
*   CYBLE_L2CAP_CONNECTION_ENTITY_NOT_FOUND  | No connection entity found which can be disconnected	
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capDisconnectReq
           (
                 uint16  localCid
           );

#endif /*L2CAP_SUPPORT_CBFC_MODE*/


#ifdef GAP_PERIPHERAL

/******************************************************************************
* Function Name: CyBle_L2capLeConnectionParamUpdateRequest
***************************************************************************//**
* 
*  This function sends the connection parameter update request to the Master of
*  the link. This is a non-blocking function. This function can only be used 
*  from device connected in LE slave role.
* 
*  To send connection parameter update request from the master to the slave, 
*  use CyBle_GapcConnectionParamUpdateRequest() function. This function 
*  results in CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ event at the Master's end.
* 
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part A, section 4.20 for
*  more details about this operation.
* 
*  \param bdHandle: Peer device handle
*  \param connParam: Pointer to a variable of type CYBLE_GAP_CONN_UPDATE_PARAM_T which 
*              indicates the response to the Connection Parameter Update Request
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                        	 | -----------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER        | If "connParam" is NULL
*   CYBLE_ERROR_INVALID_OPERATION        | Connection Parameter Update Request is not allowed
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
*   CYBLE_ERROR_NO_CONNECTION            | No Link Layer connection is  present
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capLeConnectionParamUpdateRequest
           (
               	uint8  	     		 			bdHandle,
				CYBLE_GAP_CONN_UPDATE_PARAM_T	*connParam
           );


#endif /*GAP_PERIPHERAL*/


#ifdef GAP_CENTRAL

/******************************************************************************
* Function Name: CyBle_L2capLeConnectionParamUpdateResponse
***************************************************************************//**
* 
*  This API sends the connection parameter update response to slave. This API 
*  can only be used from device connected in LE master role.
* 
*  \param bdHandle: Peer device handle
*  \param result: This field indicates the response to the Connection Parameter Update
*           Request
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                           | Description
*  ------------                           |	-----------
*   CYBLE_ERROR_OK                        | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER	      | If 'result' is invalid (greater than connection parameter reject code i.e., 0x0001)
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  | Memory allocation failed
*   CYBLE_ERROR_NO_CONNECTION             | No Link Layer connection is present
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_L2capLeConnectionParamUpdateResponse
           (
               uint8  	     bdHandle,
               uint16        result
           );


#endif /*GAP_CENTRAL*/

/** @} */

#endif /*CY_BLE_CYBLE_STACK_L2CAP_H*/


/*EOF*/
