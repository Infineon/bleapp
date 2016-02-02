/***************************************************************************//**
* \file CYBLE.c
* \version 2.30
* 
* \brief
*  This file contains the source code for the Common APIs of the BLE Component.
* 
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ble_eventHandler.h"
#include "ble_HAL_PVT.h"
#include <stdlib.h>


/***************************************
* Function Prototypes
***************************************/

#if(CYBLE_GATT_ROLE_SERVER)
    #if(CYBLE_GAP_ROLE_PERIPHERAL)
        static void CyBle_ChangeAdLocalName(const char8 name[], uint8 dest);
    #endif /* (CYBLE_GAP_ROLE_PERIPHERAL) */
#endif /* (CYBLE_GATT_ROLE_SERVER) */
    

/***************************************
* Global Variables
***************************************/

/* Indicates whether the BLE has been initialized. The variable is initialized to
   0 and set to 1 the first time CyBle_Start() is called. This allows the component
   to restart without reinitialization after the first call to the CyBle_Start() 
   routine. If reinitialization of the component is required, the variable should 
   be set to 0 before the CyBle_Start() routine is called. Alternatively, the BLE
   can be reinitialized by calling the CyBle_Init() function.
*/
uint8  cyBle_initVar = 0u;

/* Allocate RAM memory for stack. This buffer could be reused by application when 
   BLE component is stopped. For export mode buffer is allocated in heap.
*/
#if(CYBLE_SHARING_MODE_EXPORT)
    
uint8 *cyBle_stackMemoryRam = NULL;

#else

CYBLE_CYALIGNED_BEGIN uint8 cyBle_stackMemoryRam[CYBLE_STACK_RAM_SIZE] CYBLE_CYALIGNED_END;

#endif  /* CYBLE_SHARING_MODE_EXPORT */

#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)

CYBLE_GAPP_DISC_PARAM_T cyBle_discoveryParam =
{
    0x0020u,    /* uint16 advertising_interval_min */
    0x0030u,    /* uint16 advertising_interval_max */
    CYBLE_GAPP_CONNECTABLE_UNDIRECTED_ADV, /* uint8 advertising_type */
    0x00u,      /* uint8 own_addr_type */
    0x00u,      /* uint8 direct_addr_type */
    {0x00u, 0x00u, 0x00u, 0x50u, 0xA0u, 0x00u}, /* uint8* direct_addr */
    0x07u,      /* uint8 advertising_channel_map */
    0x00u,      /* uint8 advertising_filter_policy */
};

CYBLE_GAPP_DISC_DATA_T cyBle_discoveryData =
{
    { 0x02u, 0x01u, 0x06u, 0x07u, 0x09u, 0x63u, 0x61u,
    0x70u, 0x6Cu, 0x65u, 0x64u, 0x11u, 0x07u, 0xF0u, 0x34u,
    0x9Bu, 0x5Fu, 0x80u, 0x00u, 0x00u, 0x80u, 0x00u, 0x10u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u }, /* uint8 advertising_data[CYBLE_MAX_ADV_DATA_LEN] */
    0x1Du,      /* uint8 adv_data_length */
};

CYBLE_GAPP_SCAN_RSP_DATA_T cyBle_scanRspData =
{
    { 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u }, /* uint8 scan_rsp_data[CYBLE_MAX_SCAN_RSP_DATA_LEN] */
    0x00u,      /* uint8 scan_rsp_data_length */
};

/* This variable of type CYBLE_GAPP_DISC_MODE_INFO_T is present only when 
   the BLE component is configured for Peripheral GAP role or Central and 
   Peripheral GAP role. It contains the Advertisement settings and also the 
   Advertisement and Scan response data parameters entered in the customizer.
   This variable can be used by advanced users to change Advertisement settings,
   Advertisement or Scan response data in runtime. 
*/
CYBLE_GAPP_DISC_MODE_INFO_T cyBle_discoveryModeInfo =
{
    0x02u,      /* uint8 discMode */
    &cyBle_discoveryParam,
    &cyBle_discoveryData,
    &cyBle_scanRspData,
    0x0000u,    /* uint16 advTo */
};


#endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */

#if(CYBLE_GAP_ROLE_CENTRAL)
    
CYBLE_GAPC_CONN_PARAM_T cyBle_connectionParameters;

/* Connecting timeout is set to 30 seconds in CyBle_Init function. 
   Not zero value starts timer in CyBle_GapcConnectDevice API.
*/
uint16 cyBle_connectingTimeout;
    
#endif /* CYBLE_GAP_ROLE_CENTRAL */

#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)
    

    
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */

#if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))

uint8 cyBle_peerBonding;
uint8 cyBle_pendingFlashWrite;
    
#endif  /* (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */

CYBLE_CALLBACK_T CyBle_ApplCallback;
CYBLE_GAP_BD_ADDR_T cyBle_deviceAddress = {{0x00u, 0x00u, 0x00u, 0x50u, 0xA0u, 0x00u}, 0x00u };
CYBLE_GAP_BD_ADDR_T * cyBle_sflashDeviceAddress = CYBLE_SFLASH_DEVICE_ADDRESS_PTR;

#if(CYBLE_MODE_PROFILE)
    #if defined(__ARMCC_VERSION)
        CY_ALIGN(CYDEV_FLS_ROW_SIZE) const uint8 cyBle_StackFlashptr[CYBLE_STACK_FLASH_SIZE] = {0u};
    #elif defined (__GNUC__)
        const uint8 cyBle_StackFlashptr[CYBLE_STACK_FLASH_SIZE] CY_ALIGN(CYDEV_FLS_ROW_SIZE) = {0u};
    #elif defined (__ICCARM__)
        #pragma data_alignment=CY_FLASH_SIZEOF_ROW
        const uint8 cyBle_StackFlashptr[CYBLE_STACK_FLASH_SIZE] = {0u};
    #endif  /* (__ARMCC_VERSION) */
#endif /* (CYBLE_MODE_PROFILE) */


/******************************************************************************
* Function Name: CyBle_Init
***************************************************************************//**
*
*   Initializes the component with the parameters set in the customizer.
* 
*  \return
*   None
* 
******************************************************************************/
void CyBle_Init(void)
{
    cyBle_eventHandlerFlag = 0u;
    cyBle_busyStatus = CYBLE_STACK_STATE_FREE;

    #if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER) 
        cyBle_advertisingIntervalType = CYBLE_ADVERTISING_FAST; 
    #endif /* (CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)  */
    #if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)
        cyBle_scanningIntervalType = CYBLE_SCANNING_FAST; 
    #endif /* (CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER) */
        
    /* Init default connection parameters. 
       Application may change it before initiating a connection */
    #if(CYBLE_GAP_ROLE_CENTRAL)
        cyBle_connectionParameters.scanIntv = cyBle_discoveryInfo.scanIntv;
        cyBle_connectionParameters.scanWindow = cyBle_discoveryInfo.scanWindow;
        cyBle_connectionParameters.ownAddrType = cyBle_discoveryInfo.ownAddrType;
        cyBle_connectionParameters.initiatorFilterPolicy = cyBle_discoveryInfo.scanFilterPolicy;
        cyBle_connectionParameters.connIntvMin = CYBLE_GAPC_CONNECTION_INTERVAL_MIN;
        cyBle_connectionParameters.connIntvMax = CYBLE_GAPC_CONNECTION_INTERVAL_MAX;
        cyBle_connectionParameters.connLatency = CYBLE_GAPC_CONNECTION_SLAVE_LATENCY;
        cyBle_connectionParameters.supervisionTO = CYBLE_GAPC_CONNECTION_TIME_OUT;
        cyBle_connectionParameters.minCeLength = 0x0000u;
        cyBle_connectionParameters.maxCeLength = 0xFFFFu;
        
        cyBle_connectingTimeout = CYBLE_GAPC_CONNECTING_TIMEOUT;
    #endif /* CYBLE_GAP_ROLE_CENTRAL */

    CyBle_ServiceInit();

    #if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
        cyBle_pendingFlashWrite = 0u;
        cyBle_peerBonding = CYBLE_GAP_BONDING_NONE;
    #endif  /* (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */

}


/******************************************************************************
* Function Name: CyBle_ServiceInit
***************************************************************************//**
* 
*  Initializes all included services.
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_ServiceInit(void)
{
    #if(CYBLE_GATT_ROLE_CLIENT)
        (void)memset(&cyBle_gapc, 0, sizeof(cyBle_gapc));
        (void)memset(&cyBle_gattc, 0, sizeof(cyBle_gattc));
    #endif /* CYBLE_GATT_ROLE_CLIENT */
    
	#ifdef CYBLE_ANCS
        CyBle_AncsInit();
    #endif /* CYBLE_ANCS */
	
    #ifdef CYBLE_ANS
        CyBle_AnsInit();
    #endif /* CYBLE_ANS */
    
    #ifdef CYBLE_BAS
        CyBle_BasInit();
    #endif /* CYBLE_BAS */
    
    #ifdef CYBLE_BLS
        CyBle_BlsInit();
    #endif /* CYBLE_BLS */
    
    #ifdef CYBLE_BMS
        CyBle_BmsInit();
    #endif /* CYBLE_BMS */
    
    #ifdef CYBLE_CGMS
        CyBle_CgmsInit();
    #endif /* CYBLE_CGMS */

    #ifdef CYBLE_CPS
        CyBle_CpsInit();
    #endif /* CYBLE_CPS */

    #ifdef CYBLE_CSCS
        CyBle_CscsInit();
    #endif /* CYBLE_CSCS */
    
    #ifdef CYBLE_CTS
        CyBle_CtsInit();
    #endif /* CYBLE_CTS */

    #ifdef CYBLE_DIS
        CyBle_DisInit();
    #endif /* CYBLE_DIS */

    #ifdef CYBLE_ESS
        CyBle_EssInit();
    #endif /* CYBLE_ESS */
    
    #ifdef CYBLE_GLS
        CyBle_GlsInit();
    #endif /* CYBLE_GLS */
    
    #ifdef CYBLE_CUSTOM
        CyBle_CustomInit();
    #endif /* CYBLE_CUSTOM */

    #ifdef CYBLE_HIDS
        CyBle_HidsInit();
    #endif /* CYBLE_HIDS */

    #ifdef CYBLE_HRS
        CyBle_HrsInit();
    #endif /* CYBLE_HRS */
    
    #ifdef CYBLE_HTS
        CyBle_HtsInit();
    #endif /* CYBLE_RSCS */

    #ifdef CYBLE_IAS
        CyBle_IasInit();
    #endif /* CYBLE_IAS */

    #ifdef CYBLE_LLS
        CyBle_LlsInit();
    #endif /* CYBLE_LLS */

    #ifdef CYBLE_RTUS
        CyBle_RtusInit();
    #endif /* CYBLE_RTUS */

    #ifdef CYBLE_LNS
        CyBle_LnsInit();
    #endif /* CYBLE_LNS */
    
    #ifdef CYBLE_PASS
        CyBle_PassInit();
    #endif /* CYBLE_PASS */
    
    #ifdef CYBLE_RSCS
        CyBle_RscsInit();
    #endif /* CYBLE_RSCS */

    #ifdef CYBLE_SCPS
        CyBle_ScpsInit();
    #endif /* CYBLE_SCPS */
    
    #ifdef CYBLE_TPS
        CyBle_TpsInit();
    #endif /* CYBLE_TPS */
    
    #ifdef CYBLE_UDS
        CyBle_UdsInit();
    #endif /* CYBLE_UDS */

    #ifdef CYBLE_WPTS
        CyBle_WptsInit();
    #endif /* CYBLE_WPTS */

    #ifdef CYBLE_WSS
        CyBle_WssInit();
    #endif /* CYBLE_WSS */
}


/******************************************************************************
* Function Name: CyBle_Start
***************************************************************************//**
* 
*  This function initializes the BLE Stack, which consists of the BLE Stack 
*  Manager, BLE Controller, and BLE Host modules. It takes care of initializing
*  the Profile layer, schedulers, Timer and other platform related
*  resources required for the BLE component. It also registers the callback 
*  function for BLE events that will be registered in the BLE stack.
* 
*  Note that this function does not reset the BLE Stack.
* 
*  For HCI-Mode of operation, this function will not initialize the BLE Host 
*  module.
* 
*  Calling this function results in the generation of CYBLE_EVT_STACK_ON event
*  on successful initialization of the BLE Stack.
* 
*  \param callbackFunc: Event callback function to receive events from BLE stack.
*   CYBLE_CALLBACK_T is a function pointer type.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*  failed. Following are the possible error codes.
* 
*   <table>
*  	  <tr>
*       <th>Error codes</th>
*       <th>Description</th>
*     </tr>
*     <tr>
*       <td>CYBLE_ERROR_OK</td>
*       <td>On successful operation.</td>
*     </tr>
*     <tr>
*       <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*       <td>On passing a NULL pointer to the function when the BLE stack is not built in HCI mode. 
*			CYBLE_ERROR_INVALID_PARAMETER is never returned in HCI mode.</td>
*     </tr>
*     <tr>
*       <td>CYBLE_ERROR_REPEATED_ATTEMPTS</td>
*       <td>On invoking this function more than once without calling CyBle_Shutdown() 
*           function between calls to this function.</td>
*     </tr>
*     <tr>
*       <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*       <td>There is insufficient memory available.</td>
*     </tr>
*   </table>
* 
*  \globalvars
*   The CyBle_initVar variable is used to indicate initial
*   configuration of this component. The variable is initialized to zero (0u)
*   and set to one (1u) the first time CyBle_Start() is called. This
*   allows for component initialization without re-initialization in all
*   subsequent calls to the CyBle_Start() routine.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_Start(CYBLE_CALLBACK_T callbackFunc)
{
    CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
    
    #if(CYBLE_MODE_PROFILE)
    
    CYBLE_STK_APP_DATA_BUFF_T cyBle_stackDataBuff[CYBLE_STACK_BUF_COUNT] = 
    {
        {CYBLE_GATT_MTU_PLUS_L2CAP_MEM_EXT, CYBLE_GATT_MTU_BUF_COUNT},
        {CYBLE_GATT_MAX_ATTR_LEN_PLUS_L2CAP_MEM_EXT, 1u},
        {CYBLE_L2CAP_PSM_PLUS_L2CAP_MEM_EXT, CYBLE_L2CAP_PSM_COUNT},
        {CYBLE_L2CAP_CBFC_PLUS_L2CAP_MEM_EXT, CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT},
        {CYBLE_L2CAP_MTU_PLUS_L2CAP_MEM_EXT, CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT},
        {CYBLE_L2CAP_MPS_PLUS_L2CAP_MEM_EXT, CYBLE_L2CAP_LOGICAL_CHANNEL_COUNT * (CYBLE_L2CAP_MTU/CYBLE_L2CAP_MPS)}
    }; 

    #endif /* CYBLE_MODE_PROFILE */
    
    /* If not initialized then initialize all the required hardware and software */
    if(cyBle_initVar == 0u)
    {
        CyBle_Init();
        cyBle_initVar = 1u;
    }
    
    if(callbackFunc != NULL)
    {
    #if(CYBLE_SHARING_MODE_EXPORT)
        if(cyBle_stackMemoryRam == NULL)
        {
            cyBle_stackMemoryRam = (uint8 *)malloc(CYBLE_STACK_RAM_SIZE);
            if(cyBle_stackMemoryRam == NULL)
            {
                apiResult = CYBLE_ERROR_MEMORY_ALLOCATION_FAILED;
            } 
        }
    #endif /* CYBLE_SHARING_MODE_EXPORT */
        if(apiResult == CYBLE_ERROR_OK)
        {
            CyBle_ApplCallback = callbackFunc;
            
        #if(CYBLE_MODE_PROFILE)
            apiResult = CyBle_StackInit(&CyBle_EventHandler, cyBle_stackMemoryRam, CYBLE_STACK_RAM_SIZE, 
                cyBle_stackDataBuff, CYBLE_STACK_BUF_COUNT, cyBle_flashStorage.stackFlashptr, CYBLE_STACK_FLASH_SIZE);
        #else
            apiResult = CyBle_StackInit(&CyBle_EventHandler, cyBle_stackMemoryRam, CYBLE_STACK_RAM_SIZE,
                NULL, 0u, NULL, 0u);
        #endif /* CYBLE_MODE_PROFILE */

            if(apiResult == CYBLE_ERROR_OK)
            {
                CyBle_SetState(CYBLE_STATE_INITIALIZING);
                
            #if (CYBLE_GATT_ROLE_CLIENT)
                CyBle_SetClientState(CYBLE_CLIENT_STATE_DISCONNECTED);
            #endif /* CYBLE_GATT_ROLE_CLIENT */
                
            #if(CYBLE_GATT_ROLE_SERVER)
                apiResult = CyBle_GattsDbRegister(cyBle_gattDB, CYBLE_GATT_DB_INDEX_COUNT, CYBLE_GATT_DB_MAX_VALUE_LEN);
            #endif /* CYBLE_GATT_ROLE_SERVER */
            }
        }
    }
    else
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }

    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_Stop
***************************************************************************//**
* 
*  This function stops any ongoing operation in the BLE Stack and forces the 
*  BLE Stack to shut down. The only function that can be called after calling
*  this function is CyBle_Start(). 
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_Stop(void)
{
    CyBle_Shutdown();                         /* Stop all ongoing activities */
    CyBle_SetState(CYBLE_STATE_STOPPED);
    #if(CYBLE_SHARING_MODE_EXPORT)
        if(cyBle_stackMemoryRam != NULL)
        {
            free(cyBle_stackMemoryRam);
        }
    #endif /* CYBLE_SHARING_MODE_EXPORT */
}


#if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))

    
/******************************************************************************
* Function Name: CyBle_StoreBondingData
***************************************************************************//**
* 
*  This function writes the new bonding data from RAM to the dedicated Flash 
*  location as defined by the component. It performs data comparing between RAM
*  and Flash before writing to Flash. If there is no change between RAM and Flash
*  data, then no write is performed. It writes only one flash row in one call.
*  Application should keep calling this function till API return CYBLE_ERROR_OK. 
*  This function is available only when Bonding requirement is selected in
*  Security settings.    
* 
*  \param isForceWrite:  If value is set to 0, then stack will check if flash write 
*                 is permissible. 
*  
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*
*   Errors codes                         | Description
*   ----------------------------------   | ------------------------------------
*   CYBLE_ERROR_OK                       | On successful operation
*   CYBLE_ERROR_FLASH_WRITE_NOT_PERMITED | Flash Write is not complete
*    
*  \sideeffect
*   For BLE devices with 128K of Flash memory this API will automatically 
*   modify the clock settings for the device.
*   Writing to flash requires changes to be done to the IMO (set to 48 MHz)
*   and HFCLK (source set to IMO) settings. The configuration is restored before
*   returning. This will impact the operation of most of the hardware in the
*   device.
* 
*  \globalvars
*   The ble_pendingFlashWrite variable is used to detect status
*   of pending write to flash operation for stack data and CCCD.
*   This API automatically clears pending bits after write operation complete.
*     
******************************************************************************/
CYBLE_API_RESULT_T CyBle_StoreBondingData(uint8 isForceWrite)
{
    CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
    
    /* Store Stack data */
    if((cyBle_pendingFlashWrite & CYBLE_PENDING_STACK_FLASH_WRITE_BIT) != 0u)
    {
        apiResult = CyBle_StoreStackData(isForceWrite);
        if(apiResult == CYBLE_ERROR_OK)
        {
            cyBle_pendingFlashWrite &= (uint8)~CYBLE_PENDING_STACK_FLASH_WRITE_BIT;
            /* Change apiResult if there are more pending data to store */
            if((cyBle_pendingFlashWrite & CYBLE_PENDING_CCCD_FLASH_WRITE_BIT) != 0u)
            {
                apiResult = CYBLE_ERROR_FLASH_WRITE_NOT_PERMITED;
            }
        }
    }
#if(CYBLE_GATT_DB_CCCD_COUNT != 0u)
    /* Store CCCD values */
    if( ((apiResult == CYBLE_ERROR_OK) || (isForceWrite != 0u)) && 
        ((cyBle_pendingFlashWrite & CYBLE_PENDING_CCCD_FLASH_WRITE_BIT) != 0u) &&
        (cyBle_connHandle.bdHandle <= CYBLE_GAP_MAX_BONDED_DEVICE))
    {
        apiResult = CyBle_StoreAppData(cyBle_attValuesCCCD, cyBle_flashStorage.attValuesCCCDFlashMemory[cyBle_connHandle.bdHandle], 
                                       CYBLE_GATT_DB_CCCD_COUNT, isForceWrite);
        if(apiResult == CYBLE_ERROR_OK)
        {
            cyBle_pendingFlashWrite &= (uint8)~CYBLE_PENDING_CCCD_FLASH_WRITE_BIT;
        }
    }
#endif /* CYBLE_GATT_DB_CCCD_COUNT != 0u */
    return(apiResult);
}


#endif /* (CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */


#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)

    /******************************************************************************
    *  Function Name: CyBle_GappStartAdvertisement
    ***************************************************************************//**
    *     
    *  This function is used to start the advertisement using the advertisement data 
    *  set in the component customizer's GUI. After invoking this API, the device 
    *  will be available for connection by the devices configured for GAP central 
    *  role. It is only included if the device is configured for GAP Peripheral or 
    *  GAP Peripheral + Central role.
    *  
    *  On start of advertisement, GAP Peripheral receives the
    *  CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP event. The following events are 
    *  possible on invoking this function:
    *  
    *  * CYBLE_EVT_GAP_DEVICE_CONNECTED: If the device connects to remote GAP 
    *                                      Central device
    *  * CYBLE_EVT_TIMEOUT: If no device in GAP Central mode connects to this 
    *                       device within the specified timeout limit. Stack 
    *                       automatically initiate stop advertising when Slow 
    *                       advertising was initiated, or starts Slow advertising
    *                       after Fast advertising timeout occur.
    *  * CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP: If device started or stopped
    *                                               advertising. Use CyBle_GetState()
    *                                               to determine the state. Sequential 
    *                                               advertising could be started when
    *                                               CYBLE_STATE_DISCONNECTED state is
    *                                               returned.
    * 
    *  \param advertisingIntervalType: Fast or slow advertising interval with timings
    *                                 entered in Advertising settings section of the
    *                                 customizer.
    *  * CYBLE_ADVERTISING_FAST   0x00u
    *  * CYBLE_ADVERTISING_SLOW   0x01u
    *  * CYBLE_ADVERTISING_CUSTOM 0x02u
    * 
    * \return
    *  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
    *  failed. Following are the possible error codes.
    * 
    *   Errors codes                      |  Description
    *   --------------------------------- |  --------------------------------
    *   CYBLE_ERROR_OK                    |  On successful operation.
    *   CYBLE_ERROR_INVALID_PARAMETER     |  On passing an invalid parameter.
    *   CYBLE_ERROR_INVALID_STATE         |  On calling this API not in Disconnected state.
    *
    * 
    *******************************************************************************/
    CYBLE_API_RESULT_T CyBle_GappStartAdvertisement(uint8 advertisingIntervalType)
    {
        CYBLE_API_RESULT_T apiResult;
        
        if(advertisingIntervalType > CYBLE_ADVERTISING_CUSTOM)
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
        else if((CYBLE_STATE_DISCONNECTED == CyBle_GetState()) && ((cyBle_eventHandlerFlag & CYBLE_START_FLAG) == 0u))
        {   
            if(advertisingIntervalType == CYBLE_ADVERTISING_FAST)
            {
                cyBle_discoveryModeInfo.advTo = CYBLE_FAST_ADV_TIMEOUT;
                cyBle_discoveryModeInfo.advParam->advIntvMin = CYBLE_FAST_ADV_INT_MIN;
                cyBle_discoveryModeInfo.advParam->advIntvMax = CYBLE_FAST_ADV_INT_MAX;
            }
            else if(advertisingIntervalType == CYBLE_ADVERTISING_SLOW)
            {
                cyBle_discoveryModeInfo.advTo = CYBLE_SLOW_ADV_TIMEOUT;
                cyBle_discoveryModeInfo.advParam->advIntvMin = CYBLE_SLOW_ADV_INT_MIN;
                cyBle_discoveryModeInfo.advParam->advIntvMax = CYBLE_SLOW_ADV_INT_MAX;
            }       
            else /* Do not update advertising intervals */
            {
            }
            cyBle_advertisingIntervalType = advertisingIntervalType;
            apiResult = CyBle_GappEnterDiscoveryMode(&cyBle_discoveryModeInfo);
        
            if(CYBLE_ERROR_OK == apiResult)
            {
                cyBle_eventHandlerFlag |= CYBLE_START_FLAG;
            }
        }
        else
        {
            apiResult = CYBLE_ERROR_INVALID_STATE;
        }

        return (apiResult);
    }

    
    /******************************************************************************
    * Function Name: CyBle_GappStopAdvertisement
    ***************************************************************************//**
    * 
    *   This function can be used to exit from discovery mode. After the execution 
    *   of this function, there will no longer be any advertisements. On stopping 
    *   advertising, GAP Peripheral receives CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP
    *   event. It is expected that the application layer tracks the function call 
    *   performed before occurrence of this event as this event can occur on making 
    *   a call to Cy_BleGappStartAdvertisement(), CyBle_GappEnterDiscoveryMode(), 
    *   or CyBle_GappStartAdvertisement() functions as well.
    *   
    *   The following event occurs on invoking this function:
    *   * CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP
    * 
    *  \return
    *   None
    * 
    *******************************************************************************/
    void CyBle_GappStopAdvertisement(void)
    {
        CyBle_GappExitDiscoveryMode();
        cyBle_eventHandlerFlag |= CYBLE_STOP_FLAG;
    }
    
    
    /******************************************************************************
    * Function Name: CyBle_ChangeAdDeviceAddress
    ***************************************************************************//**
    * 
    *  This API is used to set the Bluetooth device address into the advertisement 
    *  or scan response data structure.
    * 
    *  \param bdAddr: Bluetooth Device address. The variable is of type CYBLE_GAP_BD_ADDR_T
    *  \param dest: 0 - selects advertisement structure, not zero value selects scan 
    *               response structure.
    * 
    * \return
    *  None
    *  
    *******************************************************************************/
    void CyBle_ChangeAdDeviceAddress(const CYBLE_GAP_BD_ADDR_T* bdAddr, uint8 dest)
    {
        uint8 i;
        uint8 *destBuffer = NULL;
        
        if(dest == 0u)      /* Destination - advertising structure */
        {
            #ifdef CYBLE_ADV_PKT_INDEX_BLUETOOTH_DEVICE_ADDRESS
                destBuffer = &cyBle_discoveryData.advData[CYBLE_ADV_PKT_INDEX_BLUETOOTH_DEVICE_ADDRESS + 2u];
            #endif /* CYBLE_ADV_PKT_INDEX_BLUETOOTH_DEVICE_ADDRESS */
        }
        else                /* Destination - scan response structure */
        {
            #ifdef CYBLE_SCN_PKT_INDEX_BLUETOOTH_DEVICE_ADDRESS
                destBuffer = &cyBle_scanRspData.scanRspData[CYBLE_SCN_PKT_INDEX_BLUETOOTH_DEVICE_ADDRESS + 2u];
            #endif /* CYBLE_SCN_PKT_INDEX_BLUETOOTH_DEVICE_ADDRESS */    
        }
        
        if(destBuffer != NULL)
        {
            /* Update Device Address type */
            destBuffer[0u] = bdAddr->type;
            
            for(i = 0u; i < CYBLE_GAP_BD_ADDR_SIZE; i++)
            {
                destBuffer[i + 1u] = bdAddr->bdAddr[i];
            }
        }
    }
  
#endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */


#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)

    /******************************************************************************
    * Function Name: CyBle_GapcStartScan
    ***************************************************************************//**
    * 
    *   This function is used for discovering GAP peripheral devices that are 
    *   available for connection. It performs the scanning routine using the 
    *   parameters entered in the component's customizer.
    *   
    *   As soon as the discovery operation starts, CYBLE_EVT_GAPC_SCAN_START_STOP 
    *   event is generated. The CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT event is 
    *   generated when a GAP peripheral device is located. There are three discovery
    *   procedures can be selected in the customizer's GUI:
    *   
    *   * Observation procedure: A device performing the observer role receives only
    *                            advertisement data from devices irrespective of 
    *                            their discoverable mode settings. Advertisement 
    *                            data received is provided by the event,      
    *                            CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT. This procedure
    *                            requires the scanType sub parameter to be passive
    *                            scanning. 
    *   
    *   * Limited Discovery procedure: A device performing the limited discovery
    *                                  procedure receives advertisement data and 
    *                                  scan# response data from devices in the 
    *                                  limited discoverable mode only. Received data
    *                                  is provided by the event, 
    *                                  CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT. This 
    *                                  procedure requires the scanType sub-parameter 
    *                                  to be active scanning.
    *   
    *   * General Discovery procedure: A device performing the general discovery 
    *                                  procedure receives the advertisement data and
    *                                  scan response data from devices in both 
    *                                  limited discoverable mode and the general 
    *                                  discoverable mode. Received data is provided
    *                                  by the event,
    *                                  CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT. This 
    *                                  procedure requires the scanType sub-parameter
    *                                  to be active scanning.
    *   
    *   Every Advertisement / Scan response packet received results in a new event, 
    *   CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT.
    *   If 'scanTo' sub-parameter is a non-zero value, then upon commencement of 
    *   discovery procedure and elapsed time = 'scanTo', CYBLE_EVT_TIMEOUT event
    *   is generated with the event parameter indicating CYBLE_GAP_SCAN_TO.
    *   Possible generated events are:
    *   * CYBLE_EVT_GAPC_SCAN_START_STOP: If a device started or stopped scanning. 
    *                                     Use CyBle_GetState() to determine the 
    *                                     state. Sequential scanning could be 
    *                                     started when CYBLE_STATE_DISCONNECTED 
    *                                     state is returned. 
    *   * CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT 
    *   * CYBLE_EVT_TIMEOUT (CYBLE_GAP_SCAN_TO)
    * 
    *   \param scanningIntervalType:  Fast or slow scanning interval with
    *       timings entered in Scan settings section of the customizer.
    * 	  * CYBLE_SCANNING_FAST   0x00u
    * 	  * CYBLE_SCANNING_SLOW   0x01u
    * 	  * CYBLE_SCANNING_CUSTOM 0x02u
    * 
    * \return
    *  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
    *  failed. Following are the possible error codes.
    *
    *   Errors codes                       | Description
    *   ---------------------------------- | -----------------------------------
    *   CYBLE_ERROR_OK                     | On successful operation.
    *   CYBLE_ERROR_STACK_INTERNAL         | An error occurred in the BLE stack.
    *   CYBLE_ERROR_INVALID_PARAMETER      | On passing an invalid parameter.
    *  
    *******************************************************************************/
    CYBLE_API_RESULT_T CyBle_GapcStartScan(uint8 scanningIntervalType)
    {
        CYBLE_API_RESULT_T apiResult;

        if(scanningIntervalType > CYBLE_SCANNING_CUSTOM)
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
        else
        {
            if(scanningIntervalType == CYBLE_SCANNING_FAST)
            {
                cyBle_discoveryInfo.scanTo = CYBLE_FAST_SCAN_TIMEOUT;
                cyBle_discoveryInfo.scanIntv = CYBLE_FAST_SCAN_INTERVAL;
                cyBle_discoveryInfo.scanWindow = CYBLE_FAST_SCAN_WINDOW;
            }
            else if(scanningIntervalType == CYBLE_SCANNING_SLOW)
            {
                cyBle_discoveryInfo.scanTo = CYBLE_SLOW_SCAN_TIMEOUT;
                cyBle_discoveryInfo.scanIntv = CYBLE_SLOW_SCAN_INTERVAL;
                cyBle_discoveryInfo.scanWindow = CYBLE_SLOW_SCAN_WINDOW;
            }       
            else /* Do not update scanning intervals */
            {
            }
            
            cyBle_scanningIntervalType = scanningIntervalType;
            apiResult = CyBle_GapcStartDiscovery(&cyBle_discoveryInfo);
        
            if(CYBLE_ERROR_OK == apiResult)
            {
                cyBle_eventHandlerFlag |= CYBLE_START_FLAG;
            }
        }
       
        return (apiResult);
    }
    
    
    /******************************************************************************
    * Function Name: CyBle_GapcStopScan
    ***************************************************************************//**
    * 
    *   This function used to stop the discovery of devices. On stopping discovery
    *   operation, CYBLE_EVT_GAPC_SCAN_START_STOP event is generated. Application
    *   layer needs to keep track of the function call made before receiving this
    *   event to associate this event with either the start or stop discovery
    *   function.
    * 
    *   Possible events generated are:
    *    * CYBLE_EVT_GAPC_SCAN_START_STOP
    * 
    *  \return
    *   None
    * 
    *******************************************************************************/
    void CyBle_GapcStopScan(void)
    {
        CyBle_GapcStopDiscovery();
        
        cyBle_eventHandlerFlag |= CYBLE_STOP_FLAG;
    }

    
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */


#if(CYBLE_GAP_ROLE_CENTRAL)

    /******************************************************************************
    * Function Name: CyBle_GapcConnectDevice
    ***************************************************************************//**
    * 
    *  This function is used to send a connection request to the remote device with
    *  the connection parameters set in the component customizer. This function needs
    *  to be called only once after the target device is discovered by 
    *  CyBle_GapcStartScan() and further scanning has stopped. Scanning is 
    *  successfully stopped on invoking CyBle_GapcStopScan() and then receiving the
    *  event CYBLE_EVT_GAPC_SCAN_START_STOP with sub-parameter 'success' = 0x01u.
    *  
    *  On successful connection, the following events are generated at the GAP 
    *  Central device (as well as the GAP Peripheral device), in the following order.
    *  * CYBLE_EVT_GATT_CONNECT_IND
    *  * CYBLE_EVT_GAP_DEVICE_CONNECTED
    *  
    *  A procedure is considered to have timed out if a connection response packet is 
    *  not received within time set by cyBle_connectingTimeout global variable
    *  (30 seconds by default). CYBLE_EVT_TIMEOUT event with CYBLE_GENERIC_TO parameter
    *  will indicate about connection procedure timeout. Connection will automatically
    *  be canceled and state will be changed to CYBLE_STATE_DISCONNECTED.
    * 
    *  \param address: The device address of the remote device to connect to. 
    *  \param timeout: Timeout for which timer to be started in seconds.
    *  
    * \return
    *  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
    *  failed. Following are the possible error codes.
    *
    *   Errors codes                       | Description
    *   ------------                       | -----------
    *   CYBLE_ERROR_OK                     | On successful operation.
    *   CYBLE_ERROR_STACK_INTERNAL         | On error occurred in the BLE stack.
    *   CYBLE_ERROR_INVALID_PARAMETER      | On passing an invalid parameter.
    *   CYBLE_ERROR_INVALID_STATE          | On calling this API not in Disconnected state.
    *  
    ******************************************************************************/
    CYBLE_API_RESULT_T CyBle_GapcConnectDevice(const CYBLE_GAP_BD_ADDR_T * address)
    {
        CYBLE_API_RESULT_T apiResult;
        uint8 i;

        if(CYBLE_STATE_DISCONNECTED != CyBle_GetState())
        {
            apiResult = CYBLE_ERROR_INVALID_STATE;
        }
        else if(address == NULL)
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
        else
        {
            for(i = 0u; i < CYBLE_GAP_BD_ADDR_SIZE; i++)
            {
                cyBle_connectionParameters.peerBdAddr[i] = address->bdAddr[i];
            }
            cyBle_connectionParameters.peerAddrType = address -> type;
            apiResult = CyBle_GapcInitConnection(&cyBle_connectionParameters);
            
            if(CYBLE_ERROR_OK == apiResult)
            {
                CyBle_SetState(CYBLE_STATE_CONNECTING);
                if(cyBle_connectingTimeout != 0u)
                {
                    (void)CyBle_StartTimer(cyBle_connectingTimeout);
                }
            }
        }
        return (apiResult);
    }
    

    /******************************************************************************
    * Function Name: CyBle_GapcCancelDeviceConnection
    ***************************************************************************//**
    * 
    *  This function cancels a previously initiated connection with the remote 
    *  device. It is a blocking function. No event is generated on calling this 
    *  function. If the devices are already connected then this function should not
    *  be used. If you intend to disconnect from an existing connection, the function
    *  CyBle_GapDisconnect() should be used.
    * 
    * \return
    *  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
    *  failed. Following are the possible error codes.
    *
    *   Errors codes                       | Description
    *   ---------------------------------- | --------------------------------------
    *   CYBLE_ERROR_OK                     | On successful operation.
    *   CYBLE_ERROR_STACK_INTERNAL         | An error occurred in the BLE stack.
    *   CYBLE_ERROR_INVALID_OPERATION      | Device is already connected.
    *  
    *******************************************************************************/
    CYBLE_API_RESULT_T CyBle_GapcCancelDeviceConnection(void)
    {
        CYBLE_API_RESULT_T apiResult;
        
        apiResult = CyBle_GapcCancelConnection();
            
        if(cyBle_connectingTimeout != 0u)
        {
            (void)CyBle_StopTimer();
        }

        if(CYBLE_ERROR_OK == apiResult)
        {
            CyBle_SetState(CYBLE_STATE_DISCONNECTED);
        }
        return (apiResult);
    }    

    
#endif /* CYBLE_GAP_ROLE_CENTRAL */


#if(CYBLE_GATT_ROLE_SERVER)

#if(CYBLE_GAP_ROLE_PERIPHERAL)

        /******************************************************************************
        * Function Name: CyBle_ChangeAdLocalName
        ***************************************************************************//**
        *  This API is used to set the local device name in the advertisement or scan 
        *  response data structure.
        * 
        *  \param name: The local device name string to be set in advertisement data 
        *            structure.
        *  \param dest: 0 - advertisement structure, not zero value selects scan response
        *              structure.
        * 
        * \return
        *  None
        *  
        *******************************************************************************/
        static void CyBle_ChangeAdLocalName(const char8 name[], uint8 dest)
        {
            uint8 i;
            uint8 flag = 0u;
            uint8 adLength = 0u;
            uint8 byteCounter = 0u;
            uint8 *destBuffer;
            uint8 maxLength;
            
            if(dest == 0u)      /* Destination - advertising structure */
            {
                destBuffer = cyBle_discoveryData.advData;
                maxLength = cyBle_discoveryData.advDataLen;
            }
            else                /* Destination - scan response structure */
            {
                destBuffer = cyBle_scanRspData.scanRspData;
                maxLength = cyBle_scanRspData.scanRspDataLen;
            }
            
            while((byteCounter < maxLength) && (0u == flag))
            {
                adLength = destBuffer[byteCounter];
                
                if(0u != adLength)
                {
                    /* Increment byte counter so it can point to AD type */
                    byteCounter++;
                    
                    if((CYBLE_SHORT_LOCAL_NAME == destBuffer[byteCounter]) || 
                       (CYBLE_COMPLETE_LOCAL_NAME == destBuffer[byteCounter]))
                    {
                        /* Start of the Local Name AD type was fount. Set flag and exit the loop. */
                        flag = 1u;
                    }
                    else
                    {
                        byteCounter += adLength;
                    }
                }
                else
                {
                    /* The end of advertisement data structure was encountered though exit the loop. */
                    break;
                }
            }
            
            if(0u != flag)
            {
                /* Reuse "adLength" to hold location of the last character of local name in 
                   AD structure. */
                adLength += byteCounter;
                
                /* Increment byte counter to point to start of the local Name string */
                byteCounter++;
                
                for(i = byteCounter; ((i < (adLength)) && (CYBLE_NULL_CHARCTER != name[i - byteCounter])); i++)
                {
                    destBuffer[i] = (uint8)name[i - byteCounter];
                }
                
                /* This loop handles the case when new local name is shorted than old one.
                   In this case all remaining characters should be null characters. */
                while(adLength > i)
                {
                    /* Terminate string */
                    destBuffer[i] = (uint8)CYBLE_NULL_CHARCTER;
                    i++;
                }
            }
        }
        
#endif /* (CYBLE_GAP_ROLE_PERIPHERAL) */  
    
    
    /******************************************************************************
    * Function Name: CyBle_GapSetLocalName
    ***************************************************************************//**
    *  This API is used to set the local device name - a Characteristic of the 
    *  GAP Service. If the characteristic length entered in the component customizer
    *  is shorter than the string specified by the "name" parameter, the local device
    *  name will be cut to the length specified in the customizer.
    * 
    *  \param name: The local device name string. The name string to be written as
    *              the local device name. It represents a UTF-8 encoded User
    *              Friendly Descriptive Name for the device. The length of the local
    *              device string is entered into the component customizer and it can
    *              be set to a value from 0 to 248 bytes. If the name contained in
    *              the parameter is shorter than the length from the customizer, the
    *              end of the name is indicated by a NULL octet (0x00).
    * 
    * \return
    *  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
    *  failed. Following are the possible error codes.
    *
    *   Errors codes                       | Description
    *   ------------                       | -----------
    *   CYBLE_ERROR_OK                     | Function completed successfully.
    *   CYBLE_ERROR_INVALID_PARAMETER      | On specifying NULL as input parameter
    *  
    *******************************************************************************/
    CYBLE_API_RESULT_T CyBle_GapSetLocalName(const char8 name[])
    {
        CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
        uint8 i;
        char8 *ptr;
        uint8 charLen;

        if(NULL != name)
        {
            /* Get the pointer to the Device Name characteristic  */
            ptr = (char8 *) CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_PTR(CYBLE_GAP_DEVICE_NAME_INDEX + 1u);

            /* First need to get the maximum length of the characteristic data in the GATT
                database to make sure there is enough place for the data. The length
                can't be longer than 248, so only the LSB of 16 bit of length is to
                be used. */
            charLen = (uint8)CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_MAX_LEN(CYBLE_GAP_DEVICE_NAME_INDEX + 1u);

            /* Copy name into characteristic */
            for(i = 0u; ((i < charLen) && (CYBLE_NULL_CHARCTER != name[i])); i++)
            {
                ptr[i] = name[i];
            }

            if(i < charLen)
            {
                /* Terminate string */
                ptr[i] = CYBLE_NULL_CHARCTER;
            }
            
            /* Set new actual length */
            
            /* Update device name in advertising and scan response structure */
            #if(CYBLE_GAP_ROLE_PERIPHERAL)
                CyBle_ChangeAdLocalName(name, 0u);
                CyBle_ChangeAdLocalName(name, 1u);
            #endif /* (CYBLE_GAP_ROLE_PERIPHERAL) */
        }
        else
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
        
        return(apiResult);
    }


    /******************************************************************************
    * Function Name: CyBle_GapGetLocalName
    ***************************************************************************//**
    *  
    *  This API is used to read the local device name - a Characteristic of the 
    *  GAP Service.
    * 
    * \param name: The local device name string. Used to read the local name to the
    *             given string array. It represents a UTF-8 encoded User Friendly 
    *             Descriptive Name for the device. The length of the local device
    *             string is entered into the component customizer and it can be set
    *             to a value from 0 to 248 bytes. If the name contained in the
    *             parameter is shorter than the length from the customizer, the end
    *             of the name is indicated by a NULL octet (0x00).
    * 
    * \return
    *  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
    *  failed. Following are the possible error codes.
    *
    *   Errors codes                       | Description
    *   ------------                       | -----------
    *   CYBLE_ERROR_OK                     | Function completed successfully.
    *   CYBLE_ERROR_INVALID_PARAMETER      | On specifying NULL as input parameter
    *
    *******************************************************************************/
    CYBLE_API_RESULT_T CyBle_GapGetLocalName(char8 name[])
    {
        CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
        uint8 charLen;
        uint8 i;
        char8 *ptr;

        if(NULL != name)
        {
            /* Get the pointer to the Device Name characteristic  */
            ptr = (char8 *) CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_PTR(CYBLE_GAP_DEVICE_NAME_INDEX + 1u);

            /* First need to get the length of the characteristic data in the GATT
                database to make sure there is enough place for the data. The length
                can't be longer than 248, so only the LSB of 16 bit of length is to
                be used. */
            charLen = (uint8)CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_LEN(CYBLE_GAP_DEVICE_NAME_INDEX + 1u);

            /* Copy name from characteristic */
            for(i = 0u; ((i < charLen) && (CYBLE_NULL_CHARCTER != ptr[i])); i++)
            {
                name[i] = ptr[i];
            }

            /* Terminate string */
            name[i] = CYBLE_NULL_CHARCTER;
        }
        else
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
        
        return(apiResult);
    }

#endif /* (CYBLE_GATT_ROLE_SERVER) */


/******************************************************************************
* Function Name: CyBle_Get16ByPtr
***************************************************************************//**
* 
*  Returns the two-bytes value by using a pointer to the LSB.
* 
*  \param ptr: Pointer to the LSB of two-bytes data (little endian).
* 
*  \return
*  uint16: Two-bytes data.
* 
******************************************************************************/
uint16 CyBle_Get16ByPtr(const uint8 ptr[])
{
    return ((uint16) ptr[0u] | ((uint16) (((uint16) ptr[1u]) << 8u)));
}


/******************************************************************************
* Function Name: CyBle_Set16ByPtr
***************************************************************************//**
* 
*  Sets the two-bytes value by using a pointer to the LSB.
* 
*  \param ptr:    Pointer to the LSB of two-bytes data (little endian).
*  \param value:  Two-bytes data to be written.
* 
*  \return
*  None
* 
******************************************************************************/
void CyBle_Set16ByPtr(uint8 ptr[], uint16 value)
{
    ptr[0u] = (uint8) value;
    ptr[1u] = (uint8) (value >> 8u);
}


/* [] END OF FILE */
