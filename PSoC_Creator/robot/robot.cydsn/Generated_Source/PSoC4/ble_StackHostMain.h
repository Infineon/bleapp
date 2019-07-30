/***************************************************************************//**
* \file CyBle_HostMain.h
*
* \file CYBLE_StackHostMain.h
* \version 3.61
*
* \brief
*  This file contains the constants of the BLE Host Stack IP
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


#ifndef CYBLE_HOST_MAIN_H_
#define CYBLE_HOST_MAIN_H_


    
/***************************************
* Common stack includes
***************************************/

#include "BLE_Stack.h"


/***************************************
* Exported structures
***************************************/

/**
 \addtogroup group_common_api_definitions
 @{
*/

/** BLE stack timeout. This is received with CYBLE_EVT_TIMEOUT event 
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
typedef void (*CYBLE_STACK_EV_CB_PF)(CYBLE_EVT_HOST_STACK_T event, void* evParam);


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
*  This API function must be called by application to backup stack data. If this API function is not 
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
*  flash. This API function must be called by application to backup application specific 
*  data. 
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
*   CYBLE_ERROR_INVALID_PARAMETER            | Invalid input parameter  
*   CYBLE_ERROR_FLASH_WRITE                  | Error in flash Write	
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
*  \param timeout: Timeout for which timer to be started.
*                  IF MSBit of timeout == 1 then resolution is in millisecs,
*                  ELSE resolution is seconds.
*  
*  This takes the assumption that no one would call timeout of,
*  say, 32000 seconds.
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

#endif /* CYBLE_HOST_MAIN_H_ */


/*EOF*/
