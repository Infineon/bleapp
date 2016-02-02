/***************************************************************************//**
* \file CYBLE_StackHostMain.h
* \version 2.30
* 
* \brief
*  This file contains the constants of the BLE Host Stack IP
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
 \addtogroup group_common_api_definitions
 @{
*/


#ifndef CY_BLE_CYBLE_STACK_HOST_MAIN_H
#define CY_BLE_CYBLE_STACK_HOST_MAIN_H

    
/***************************************
* Common stack includes
***************************************/

#include "BLE_Stack.h"
    

/***************************************
* Constants
***************************************/

/* enable all features */
#define GAP_CENTRAL
#define GAP_PERIPHERAL
#define GATT_SUPPORT_128_BIT_UUID
#define GATT_SERVER
#define GATT_CLIENT
#define ATT_HANDLE_VALUE_NOTIFICATION_SUPPORT
#define ATT_HANDLE_VALUE_INDICATION_SUPPORT
#define ATT_MTU_EXCHANGE_SUPPORT
#define ATT_FIND_INFO_SUPPORT
#define ATT_FIND_BY_TYPE_VALUE_SUPPORT
#define ATT_READ_BY_TYPE_SUPPORT
#define ATT_READ_REQUEST_SUPPORT
#define ATT_READ_BLOB_SUPPORT
#define ATT_READ_MULTIPLE_SUPPORT
#define ATT_READ_BY_GROUP_TYPE_SUPPORT
#define ATT_WRITE_REQUEST_SUPPORT
#define ATT_WRITE_COMMAND_SUPPORT
#define ATT_QUEUED_WRITE_SUPPORT
#define ATT_SIGNED_WRITE_SUPPORT    
#define HOST_RESOLVE_PVT_ADDR
#define L2CAP_SUPPORT_CBFC_MODE

#define CYBLE_STACK_STATE_BUSY		   	0x01u
#define CYBLE_STACK_STATE_FREE		   	0x00u


/***************************************
* Exported structures
***************************************/

/* BLE stack timeout. This is received with CYBLE_EVT_TIMEOUT event 
    It is application's responsibility to disconnect or keep the channel on depends on type of timeouts.
    i.e. GATT procedure timeout: Application may choose to disconnect.*/
typedef enum
{
	/** Advertisement time set by application has expired */
	CYBLE_GAP_ADV_MODE_TO = 0x01u,
	
	/** Scan time set by application has expired */
	CYBLE_GAP_SCAN_TO,

	/** GATT procedure timeout */
	CYBLE_GATT_RSP_TO,

	/** Generic timeout */
	CYBLE_GENERIC_TO
	
}CYBLE_TO_REASON_CODE_T;

/** @} */

/**Event callback function prototype to receive events from stack */
typedef void (*CYBLE_STACK_EV_CB_PF)(CYBLE_EVENT_T event, void* evParam);


/***************************************
* Exported APIs
***************************************/

/**
 \addtogroup group_common_api_core_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_StoreStackData
***************************************************************************//**
* 
*  This function instructs Stack to backup Stack internal RAM data into flash.
*  This API must be called by application to backup stack data. If this API is not 
*  called appropriately, stack internal data structure will not be available on
*  power cycle.
*     
*  \param isForceWrite: If value is set to 0, then stack will check if flash write is
*                permissible. If value is set to 1, application should exit
*                low power mode by calling CyBle_ExitLPM().
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*  failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*  ------------                              | -----------
*   CYBLE_ERROR_OK                           | On successful operation
*   CYBLE_ERROR_FLASH_WRITE_NOT_PERMITED     | Flash Write is not permitted or not completely written
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StoreStackData(uint8 isForceWrite);


/******************************************************************************
* Function Name: CyBle_StoreAppData 
***************************************************************************//**
* 
*  This function instructs the Stack to backup application specific data into 
*  flash. This API must be called by application to backup application specific 
*  data. If this API is not called appropriately, data will not be available on
*  power cycle.
*     
*  \param srcBuff: Source buffer
*  \param destAddr: Destination address
*  \param buffLen: Length of srcData
*  \param isForceWrite: If value is set to 0, then stack will check if flash write 
*                 is permissible. If value is set to 1, application should exit
*                 low power mode by calling CyBle_ExitLPM()
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*   ------------                             | -----------
*   CYBLE_ERROR_OK                           | On successful operation
*   CYBLE_ERROR_FLASH_WRITE_NOT_PERMITED     | Flash Write is not permitted
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StoreAppData 
(
	uint8 			* srcBuff,
	const uint8 	destAddr[],
	uint32  		buffLen,
	uint8 			isForceWrite
);


/** \cond IGNORE */
/******************************************************************************
* Function Name: CyBle_StartTimer 
***************************************************************************//**
* 
*  This function provides timer start utility to BLE-Component. BLE-Component can  
*  use this timer for certain operation like deferring writing CCCD to flash.  
*  This function should not be used for generic purpose as the timer ticks are  
*  updated only when there are LL activities. BLE stack internally takes care for 
*  timing requirement for GATT, GAP and L2CAP signaling on going procedures.
* 
*  \param timeout: Timeout for which timer to be started in seconds.
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*   ------------                             | -----------
*   CYBLE_ERROR_OK                           | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER	         | Timeout is set to zero	
*   CYBLE_ERROR_INVALID_OPERATION            | On failed operation
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StartTimer (uint16 timeout);


/******************************************************************************
* Function Name: CyBle_StopTimer 
***************************************************************************//**
* 
*  This function provides timer stop utility to BLE-Component. BLE-Component can  
*  use this timer for certain operation like deferring writing CCCD to flash.  
*  This function should not be used for generic purpose as the timer ticks are  
*  updated only when there are LL activities. BLE stack internally takes care for 
*  timing requirement for GATT, GAP and L2CAP signaling on going procedures.
* 
*  void
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*   ------------                             | -----------
*   CYBLE_ERROR_OK                           | On successful operation
*   CYBLE_ERROR_INVALID_OPERATION            | On failed operation
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StopTimer (void);
/** \endcond */

/** @} */

#endif /* CY_BLE_CYBLE_STACK_HOST_MAIN_H */


/*EOF*/
