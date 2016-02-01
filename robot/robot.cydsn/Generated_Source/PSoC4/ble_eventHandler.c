/***************************************************************************//**
* \file CYBLE_eventHandler.c
* \version 2.30
* 
* \brief
*  This file contains the source code for the Event Handler State Machine
*  of the BLE Component.
* 
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLE_eventHandler.h"


/***************************************
* Private Function Prototypes
***************************************/

#if (CYBLE_GATT_ROLE_SERVER || CYBLE_GATT_ROLE_CLIENT)

static uint8 CyBle_IsDeviceAddressValid(const CYBLE_GAP_BD_ADDR_T *sflashDeviceAddress);

#endif /* CYBLE_GATT_ROLE_SERVER || CYBLE_GATT_ROLE_CLIENT */

static void CyBle_GattDisconnectEventHandler(void);
static void CyBle_TimeOutEventHandler(const CYBLE_TO_REASON_CODE_T *eventParam);
static void CyBle_GattConnectReqHandler(void);
static void CyBle_L2Cap_ConnParamUpdateRspEventHandler(uint16 response);
static void CyBle_GapConnUpdateCompleteEventHandler(const CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T *eventParam);


#if (CYBLE_GATT_ROLE_SERVER)

static void CyBle_WriteReqHandler(CYBLE_GATTS_WRITE_REQ_PARAM_T *eventParam);
static void CyBle_ValueConfirmation(const CYBLE_CONN_HANDLE_T *eventParam);

#endif /* CYBLE_GATT_ROLE_SERVER */

#if (CYBLE_GATT_ROLE_CLIENT)

static void CyBle_GapcDiscoverCharacteristicsEventHandler(CYBLE_DISC_CHAR_INFO_T *discCharInfo);
static CYBLE_GATT_ATTR_HANDLE_RANGE_T CyBle_GetCharRange(void);
static void CyBle_GattcWriteResponseEventHandler(const CYBLE_CONN_HANDLE_T *eventParam);
static void CyBle_NotificationEventHandler(CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T *eventParam);
static void CyBle_IndicationEventHandler(CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *eventParam);
static void CyBle_ReadResponseEventHandler(CYBLE_GATTC_READ_RSP_PARAM_T *eventParam);

#endif /* CYBLE_GATT_ROLE_CLIENT */


/***************************************
* Global Variables
***************************************/

/* This global variable is initialized after connection with peer device, 
   after CYBLE_EVT_GATT_CONNECT_IND event, and could be used by application code
   to send data to peer device. 
*/
CYBLE_CONN_HANDLE_T cyBle_connHandle;

volatile uint8 cyBle_eventHandlerFlag;
volatile uint8 cyBle_busyStatus;

#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER) 
    uint8 cyBle_advertisingIntervalType;
#endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER) */

#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER) 
    uint8 cyBle_scanningIntervalType;
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */

#if(CYBLE_GATT_ROLE_SERVER)
#if defined CYBLE_CTS_SERVER || defined CYBLE_ESS_SERVER
CYBLE_GATT_ERR_CODE_T cyBle_gattError;
#endif /* defined CYBLE_CTS_SERVER || defined CYBLE_ESS_SERVER */
#endif /* CYBLE_GATT_ROLE_SERVER */

#if(CYBLE_GATT_ROLE_CLIENT)
uint8 cyBle_disCount; /* Counter for discovery procedures */
static CYBLE_GATT_DB_ATTR_HANDLE_T cyBle_charEndHandle;
/* Discovery included service information, used for 128-bit UUID read response handle 
   and for continue discovery. 
*/
static CYBLE_DISC_INCL_INFO_T cyBle_discInclInfo;
#ifdef CYBLE_HIDS_CLIENT
    static uint8 disServiceIndex;      /* To discovery descriptors for multiple HID service instances */
#endif /* CYBLE_HIDS_CLIENT */

CYBLE_DISC_SRVC_INFO_T cyBle_serverInfo[CYBLE_SRVI_COUNT] = /*3*/
{
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_GAP_SERVICE},
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_GATT_SERVICE},
#ifdef CYBLE_ANCS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, 0x0000u},
#endif /* CYBLE_ANCS_CLIENT */
#ifdef CYBLE_ANS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, 
        CYBLE_UUID_ALERT_NOTIFICATION_SERVICE},
#endif /* CYBLE_ANS_CLIENT */
#ifdef CYBLE_BAS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_BAS_SERVICE},
    #if(CYBLE_BASC_SERVICE_COUNT > 1u) /* Generate it by GUI */
        
    #endif /* CYBLE_BASC_SERVICE_COUNT > 1u */
#endif /* CYBLE_BAS_CLIENT */
#ifdef CYBLE_BCS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_BODY_COMPOSITION_SERVICE},
#endif /* CYBLE_BCS_CLIENT */
#ifdef CYBLE_BLS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_BLOOD_PRESSURE_SERVICE},
#endif /* CYBLE_BLS_CLIENT */
#ifdef CYBLE_BMS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_BOND_MANAGEMENT_SERVICE},
#endif /* CYBLE_BMS_CLIENT */
#ifdef CYBLE_CGMS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_CGM_SERVICE},
#endif /* CYBLE_CGMS_CLIENT */
#ifdef CYBLE_CPS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_CPS_SERVICE},
#endif /* CYBLE_CPS_CLIENT */
#ifdef CYBLE_CSCS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, 
        CYBLE_UUID_CYCLING_SPEED_AND_CADENCE_SERVICE},
#endif /* CYBLE_CSCS_CLIENT */
#ifdef CYBLE_CTS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_CURRENT_TIME_SERVICE},
#endif /* CYBLE_CTS_CLIENT */
#ifdef CYBLE_CUSTOM_CLIENT
    
#endif /* CYBLE_CUSTOM_CLIENT */
#ifdef CYBLE_DIS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_DEVICE_INFO_SERVICE},
#endif /* CYBLE_DIS_CLIENT */
#ifdef CYBLE_ESS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, 
        CYBLE_UUID_ENVIRONMENTAL_SENSING_SERVICE},
#endif /* CYBLE_ESS_CLIENT */
#ifdef CYBLE_GLS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_GLUCOSE_SERVICE},
#endif /* CYBLE_GLS_CLIENT */
#ifdef CYBLE_HIDS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_HIDS_SERVICE},
    #if(CYBLE_HIDSC_SERVICE_COUNT > 1u) /* Generate it by GUI */
        
    #endif /* CYBLE_HIDSC_SERVICE_COUNT > 1u */
#endif /* CYBLE_HIDS_CLIENT */
#ifdef CYBLE_HRS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_HEART_RATE_SERVICE},
#endif /* CYBLE_HRS_CLIENT */
#ifdef CYBLE_HTS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_HEALTH_THERMOMETER_SERVICE},
#endif /* CYBLE_HTS_CLIENT */
#ifdef CYBLE_IAS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_IMMEDIATE_ALERT_SERVICE},
#endif /* CYBLE_IAS_CLIENT */
#ifdef CYBLE_LLS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_LINK_LOSS_SERVICE},
#endif /* CYBLE_LLS_CLIENT */
#ifdef CYBLE_LNS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_LOCATION_AND_NAVIGATION_SERVICE},
#endif /* CYBLE_LNS_CLIENT */
#ifdef CYBLE_NDCS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_NEXT_DST_CHANGE_SERVICE},
#endif /* CYBLE_NDCS_CLIENT */
#ifdef CYBLE_IPSS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_INTERNET_PROTOCOL_SUPPORT_SERVICE},
#endif /* CYBLE_IPSS_CLIENT */
#ifdef CYBLE_PASS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_PHONE_ALERT_STATUS_SERVICE},
#endif /* CYBLE_PASS_CLIENT */
#ifdef CYBLE_RSCS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_RUNNING_SPEED_AND_CADENCE_SERVICE},
#endif /* CYBLE_RSCS_CLIENT */
#ifdef CYBLE_RTUS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_REF_TIME_UPDATE_SERVICE},
#endif /* CYBLE_RTUS_CLIENT */
#ifdef CYBLE_SCPS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_SCAN_PARAM_SERVICE},
#endif /* CYBLE_SCPS_CLIENT */
#ifdef CYBLE_TPS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_TX_POWER_SERVICE},
#endif /* CYBLE_TPS_CLIENT */
#ifdef CYBLE_UDS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_USER_DATA_SERVICE},
#endif /* CYBLE_UDS_CLIENT */
#ifdef CYBLE_WSS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_WEIGHT_SCALE_SERVICE},
#endif /* CYBLE_WSS_CLIENT */
#ifdef CYBLE_WPTS_CLIENT
    {{CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE}, CYBLE_UUID_WIRELESS_POWER_TRANSFER_SERVICE},
#endif /* CYBLE_WPTS_CLIENT */
};

CYBLE_GAPC_T cyBle_gapc;

#endif /* CYBLE_GATT_ROLE_CLIENT */

/* Default device security */
CYBLE_GAP_AUTH_INFO_T cyBle_authInfo =
{
    (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_1 ), /* uint8 security */
    CYBLE_GAP_BONDING, /* uint8 bonding */
    0x10u,      /* uint8 ekeySize */
    CYBLE_GAP_AUTH_ERROR_NONE, /* CYBLE_AUTH_FAILED_REASON_T authErr */
};

#if(CYBLE_GATT_ROLE_SERVER)


/******************************************************************************    
* Function Name: CyBle_WriteReqHandler
***************************************************************************//**
* 
*  Handles the Write Request event from BLE stack.
* 
*  CYBLE_GATTS_WRITE_REQ_PARAM_T * eventParam - event parameter
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_WriteReqHandler(CYBLE_GATTS_WRITE_REQ_PARAM_T *eventParam)
{
    CYBLE_GATT_ERR_CODE_T gattErr;
#if defined CYBLE_CTS_SERVER || defined CYBLE_ESS_SERVER
    cyBle_gattError = CYBLE_GATT_ERR_NONE;
#endif /* defined CYBLE_CTS_SERVER || defined CYBLE_ESS_SERVER */
    
    gattErr = CyBle_GattsWriteEventHandler(eventParam);
#ifdef CYBLE_ANCS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_AncssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_ANCS_SERVER */
#ifdef CYBLE_ANS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_AnssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_ANS_SERVER */
#ifdef CYBLE_BAS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_BassWriteEventHandler(eventParam);
    }
#endif /* CYBLE_BAS_SERVER */
#ifdef CYBLE_BCS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_BcssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_BCS_SERVER */
#ifdef CYBLE_BLS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_BlssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_BLS_SERVER */
#ifdef CYBLE_BMS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_BmssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_BMS_SERVER */
#ifdef CYBLE_BTS_SERVER
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        gattErr = CyBle_BtsWriteEventHandler(eventParam);
    }
#endif /* CYBLE_BTS_SERVER */
#ifdef CYBLE_CGMS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_CgmssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_CGMS_SERVER */
#ifdef CYBLE_CPS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_CpssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_CPS_SERVER */
#ifdef CYBLE_CSCS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_CscssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_CSCS_SERVER */
#ifdef CYBLE_CTS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_CtssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_CTS_SERVER */
#ifdef CYBLE_ESS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_EsssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_ESS_SERVER */
#ifdef CYBLE_GLS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_GlssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_GLS_SERVER */
#ifdef CYBLE_HIDS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_HidssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_HIDS_SERVER */
#ifdef CYBLE_HRS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_HrssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_HRS_SERVER */
#ifdef CYBLE_HTS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_HtssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_HTS_SERVER */
#ifdef CYBLE_LLS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_LlssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_LLS_SERVER */
#ifdef CYBLE_LNS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_LnssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_LNS_SERVER */
#ifdef CYBLE_PASS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_PasssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_PASS_SERVER */
#ifdef CYBLE_RSCS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_RscssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_RSCS_SERVER */
#ifdef CYBLE_SCPS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_ScpssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_SCPS_SERVER */
#ifdef CYBLE_TPS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_TpssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_TPS_SERVER */
#ifdef CYBLE_UDS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_UdssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_UDS_SERVER */
#ifdef CYBLE_WPTS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_WptssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_WPTS_SERVER */
#ifdef CYBLE_WSS_SERVER
    if(((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u) && (gattErr == CYBLE_GATT_ERR_NONE))
    {
        gattErr = CyBle_WsssWriteEventHandler(eventParam);
    }
#endif /* CYBLE_WSS_SERVER */

    /* Send response when event was handled by service */
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) == 0u)
    {
        if(gattErr != CYBLE_GATT_ERR_NONE)
        {
            CYBLE_GATTS_ERR_PARAM_T err_param;
            
            err_param.opcode = (uint8) CYBLE_GATT_WRITE_REQ;
            err_param.attrHandle = eventParam->handleValPair.attrHandle;
            err_param.errorCode = gattErr;

            /* Send Error Response */
            (void)CyBle_GattsErrorRsp(eventParam->connHandle, &err_param);
        }
        else
        {
            (void)CyBle_GattsWriteRsp(eventParam->connHandle);
        }
    }
}


/****************************************************************************** 
* Function Name: CyBle_ValueConfirmation
***************************************************************************//**
* 
*  Handles the Value Confirmation request event from the BLE stack.
* 
*  \param eventParam: Pointer to a structure of type 'CYBLE_CONN_HANDLE_T'
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_ValueConfirmation(const CYBLE_CONN_HANDLE_T *eventParam)
{
    if(eventParam != NULL)
    {
    #ifdef CYBLE_BCS_SERVER
        CyBle_BcssConfirmationEventHandler(eventParam);
    #endif /* CYBLE_BCS_SERVER */
    #ifdef CYBLE_BLS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_BlssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_BLS_SERVER */
    
    #ifdef CYBLE_CGMS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_CgmssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_CGMS_SERVER */
    
    #ifdef CYBLE_CPS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_CpssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_CPS_SERVER */
    
    #ifdef CYBLE_CSCS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_CscssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_CSCS_SERVER */
    
    #ifdef CYBLE_ESS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_EsssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_ESS_SERVER */
    
    #ifdef CYBLE_GLS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_GlssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_GLS_SERVER */
    
    #ifdef CYBLE_HTS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_HtssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_HTS_SERVER */

    #ifdef CYBLE_LNS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_LnssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_LNS_SERVER */
    
    #ifdef CYBLE_RSCS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_RscssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_RSCS_SERVER */
    
    #ifdef CYBLE_UDS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_UdssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_UDS_SERVER */
    
    #ifdef CYBLE_WPTS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_WptssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_WPTS_SERVER */
    
    #ifdef CYBLE_WSS_SERVER
        if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
        {
            CyBle_WsssConfirmationEventHandler(eventParam);
        }
    #endif /* CYBLE_WSS_SERVER */
    }
}

#endif /* CYBLE_GATT_ROLE_SERVER */


#if (CYBLE_GATT_ROLE_CLIENT)

/****************************************************************************** 
* Function Name: CyBle_GattcWriteResponseEventHandler
***************************************************************************//**
* 
*  Handles the Write response event from the BLE stack.
* 
*  \param eventParam: Pointer to a structure of type 'CYBLE_CONN_HANDLE_T'
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_GattcWriteResponseEventHandler(const CYBLE_CONN_HANDLE_T *eventParam)
{
#ifdef CYBLE_ANCS_CLIENT
    CyBle_AncscWriteResponseEventHandler(eventParam);
#endif /* CYBLE_ANCS_CLIENT */

#ifdef CYBLE_ANS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_AnscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_ANS_CLIENT */

#ifdef CYBLE_BAS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BascWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BAS_CLIENT */

#ifdef CYBLE_BCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BcscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BCS_CLIENT */

#ifdef CYBLE_BLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BlscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BLS_CLIENT */

#ifdef CYBLE_BMS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BmscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BMS_CLIENT */

#ifdef CYBLE_CGMS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CgmscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_CGMS_CLIENT */

#ifdef CYBLE_CPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CpscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_CPS_CLIENT */

#ifdef CYBLE_CSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CscscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_CSCS_CLIENT */

#ifdef CYBLE_CTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CtscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_CTS_CLIENT */

#ifdef CYBLE_ESS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_EsscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_ESS_CLIENT */

#ifdef CYBLE_GLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_GlscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_GLS_CLIENT */

#ifdef CYBLE_HIDS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HidscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_HIDS_CLIENT */

#ifdef CYBLE_HRS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HrscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_HRS_CLIENT */

#ifdef CYBLE_HTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HtscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_HTS_CLIENT */

#ifdef CYBLE_LLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_LlscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_LLS_CLIENT */

#ifdef CYBLE_LNS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_LnscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_LNS_CLIENT */

#ifdef CYBLE_PASS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_PasscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_PASS_CLIENT */

#ifdef CYBLE_RSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_RscscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_RSCS_CLIENT */

#ifdef CYBLE_SCPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_ScpscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_SCPS_CLIENT */

#ifdef CYBLE_TPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_TpscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_TPS_CLIENT */

#ifdef CYBLE_UDS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_UdscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_UDS_CLIENT */
#ifdef CYBLE_WPTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_WptscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_WPTS_CLIENT */
#ifdef CYBLE_WSS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_WsscWriteResponseEventHandler(eventParam);
    }
#endif /* CYBLE_WSS_CLIENT */
}


/******************************************************************************    
* Function Name: CyBle_NotificationEventHandler
***************************************************************************//**
* 
*  Handles the Notification event from BLE stack.
* 
*  \param eventParam: event parameter
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_NotificationEventHandler(CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T *eventParam)
{
#ifdef CYBLE_ANCS_CLIENT
    CyBle_AncscNotificationEventHandler(eventParam);
#endif /* CYBLE_ANCS_CLIENT */
#ifdef CYBLE_ANS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_AnscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_ANS_CLIENT */
#ifdef CYBLE_BAS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BascNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_BAS_CLIENT */
#ifdef CYBLE_BLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BlscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_BLS_CLIENT */
#ifdef CYBLE_CGMS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CgmscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_CGMS_CLIENT */
#ifdef CYBLE_CPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CpscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_CPS_CLIENT */
#ifdef CYBLE_CSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CscscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_CSCS_CLIENT */
#ifdef CYBLE_CTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CtscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_CTS_CLIENT */
#ifdef CYBLE_ESS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_EsscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_ESS_CLIENT */
#ifdef CYBLE_GLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_GlscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_GLS_CLIENT */
#ifdef CYBLE_HIDS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HidscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_HIDS_CLIENT */
#ifdef CYBLE_HRS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HrscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_HRS_CLIENT */
#ifdef CYBLE_HTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HtscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_HTS_CLIENT */
#ifdef CYBLE_LNS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_LnscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_LNS_CLIENT */
#ifdef CYBLE_PASS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_PasscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_PASS_CLIENT */
#ifdef CYBLE_RSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_RscscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_RSCS_CLIENT */
#ifdef CYBLE_SCPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_ScpscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_SCPS_CLIENT */
#ifdef CYBLE_TPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_TpscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_TPS_CLIENT */
#ifdef CYBLE_UDS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_UdscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_UDS_CLIENT */
#ifdef CYBLE_WPTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_WptscNotificationEventHandler(eventParam);
    }
#endif /* CYBLE_WPTS_CLIENT */
}


/******************************************************************************    
* Function Name: CyBle_IndicationEventHandler
***************************************************************************//**
* 
*  Handles the Indication event from BLE stack.
* 
*  \param eventParam: event parameter
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_IndicationEventHandler(CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *eventParam)
{
#ifdef CYBLE_BCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BcscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_BCS_CLIENT */
#ifdef CYBLE_BLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BlscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_BLS_CLIENT */
#ifdef CYBLE_CGMS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CgmscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_CGMS_CLIENT */
#ifdef CYBLE_CPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CpscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_CPS_CLIENT */
#ifdef CYBLE_CSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CscscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_CSCS_CLIENT */
#ifdef CYBLE_ESS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_EsscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_ESS_CLIENT */
#ifdef CYBLE_GLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_GlscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_GLS_CLIENT */
#ifdef CYBLE_HTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HtscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_HTS_CLIENT */
#ifdef CYBLE_LNS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_LnscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_LNS_CLIENT */
#ifdef CYBLE_RSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_RscscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_RSCS_CLIENT */
#ifdef CYBLE_UDS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_UdscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_UDS_CLIENT */
#ifdef CYBLE_WPTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_WptscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_WPTS_CLIENT */
#ifdef CYBLE_WSS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_WsscIndicationEventHandler(eventParam);
    }
#endif /* CYBLE_WSS_CLIENT */
}



/******************************************************************************    
* Function Name: CyBle_ReadResponseEventHandler
***************************************************************************//**
* 
*  Handles the Read Response event from BLE stack.
* 
*  \param eventParam: event parameter
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_ReadResponseEventHandler(CYBLE_GATTC_READ_RSP_PARAM_T *eventParam)
{
#ifdef CYBLE_CUSTOM_CLIENT
    /* Read response with 128-bit included service uuid */
    if((CYBLE_CLIENT_STATE_INCL_DISCOVERING == CyBle_GetClientState()) &&
       (cyBle_discInclInfo.inclDefHandle != 0u))
    {
        CYBLE_DISC_SRVC128_INFO_T discServInfo;

        /* Store service range */
        discServInfo.range = cyBle_discInclInfo.inclHandleRange;
        (void)memcpy((void *) discServInfo.uuid.uuid128.value, (void *)eventParam->value.val, eventParam->value.len);
        CyBle_CustomcDiscoverServiceEventHandler(&discServInfo);
        
        /* Re-initiate CyBle_GattcFindIncludedServices function, setting the start
           handle to the attribute handle which is placed next to the one used in
           the above step.
        */
        discServInfo.range.startHandle = cyBle_discInclInfo.inclDefHandle + 1;
        discServInfo.range.endHandle = cyBle_serverInfo[cyBle_disCount].range.endHandle;
        if(discServInfo.range.startHandle <= discServInfo.range.endHandle)
        {
            if(CYBLE_ERROR_OK != CyBle_GattcFindIncludedServices(cyBle_connHandle, &discServInfo.range))
            {
                CyBle_ApplCallback(CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED, NULL);
                cyBle_eventHandlerFlag &= (uint8)~CYBLE_AUTO_DISCOVERY;
            }
        }
        else /* Continue discovery of the following service */
        {
            CyBle_NextInclDiscovery(CYBLE_DISCOVERY_CONTINUE);
        }
        
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
        cyBle_discInclInfo.inclDefHandle = 0u;
        
    }
#endif /* CYBLE_CUSTOM_CLIENT */
#ifdef CYBLE_ANCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_AncscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_ANCS_CLIENT */
#ifdef CYBLE_ANS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_AnscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_ANS_CLIENT */
#ifdef CYBLE_BAS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BascReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BAS_CLIENT */
#ifdef CYBLE_BLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BlscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BLS_CLIENT */
#ifdef CYBLE_BCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BcscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BCS_CLIENT */
#ifdef CYBLE_BMS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_BmscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BMS_CLIENT */
#ifdef CYBLE_CGMS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CgmscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_CGMS_CLIENT */
#ifdef CYBLE_CPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CpscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_CPS_CLIENT */
#ifdef CYBLE_CSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CscscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_CSCS_CLIENT */
#ifdef CYBLE_CTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_CtscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_BAS_CLIENT */
#ifdef CYBLE_DIS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_DiscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_DIS_CLIENT */
#ifdef CYBLE_ESS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_EsscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_ESS_CLIENT */
#ifdef CYBLE_GLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_GlscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_GLS_CLIENT */
#ifdef CYBLE_HIDS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HidscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_HIDS_CLIENT */
#ifdef CYBLE_HRS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HrscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_HRS_CLIENT */
#ifdef CYBLE_HTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_HtscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_HTS_CLIENT */
#ifdef CYBLE_LLS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_LlscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_LLS_CLIENT */
#ifdef CYBLE_LNS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_LnscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_LNS_CLIENT */
#ifdef CYBLE_NDCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_NdcscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_NDCS_CLIENT */
#ifdef CYBLE_PASS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_PasscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_PASS_CLIENT */
#ifdef CYBLE_RSCS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_RscscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_RSCS_CLIENT */
#ifdef CYBLE_RTUS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_RtuscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_RTUS_CLIENT */
#ifdef CYBLE_SCPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_ScpscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_SCPS_CLIENT */
#ifdef CYBLE_TPS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_TpscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_TPS_CLIENT */
#ifdef CYBLE_UDS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_UdscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_UDS_CLIENT */
#ifdef CYBLE_WPTS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_WptscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_WPTS_CLIENT */
#ifdef CYBLE_WSS_CLIENT
    if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
    {
        CyBle_WsscReadResponseEventHandler(eventParam);
    }
#endif /* CYBLE_WSS_CLIENT */
}
#endif /* CYBLE_GATT_ROLE_CLIENT */


/****************************************************************************** 
* Function Name: CyBle_DisconnectEventHandler
***************************************************************************//**
* 
*  Handles the GATT Disconnection event from the BLE stack.
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_GattDisconnectEventHandler(void)
{
    cyBle_connHandle.attId = 0u;
    cyBle_connHandle.bdHandle = 0u;
    
    #if (CYBLE_GATT_ROLE_CLIENT)
        if(CYBLE_CLIENT_STATE_DISCOVERED == CyBle_GetClientState())
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_DISCONNECTED_DISCOVERED);
        }
        else
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_DISCONNECTED);
        }
    #endif /* CYBLE_GATT_ROLE_CLIENT */
        
    #ifdef CYBLE_CPS_SERVER
        #if CYBLE_GAP_ROLE_BROADCASTER
            CyBle_CpssDisconnectEventHandler();
        #endif /* CYBLE_GAP_ROLE_BROADCASTER */
    #endif /* CYBLE_CPS_SERVER */

    #ifdef CYBLE_CPS_CLIENT
        CyBle_CpscDisconnectEventHandler();
    #endif /* CYBLE_CPS_CLIENT */

    #ifdef CYBLE_IAS_SERVER
        CyBle_IassDisconnectEventHandler();
    #endif /* CYBLE_IAS_SERVER */
    
    #ifdef CYBLE_GLS_SERVER
        CyBle_GlsInit();
    #endif /* CYBLE_GLS_SERVER */
    
    #ifdef CYBLE_LNS_SERVER
        CyBle_LnsInit();
    #endif /* CYBLE_LNS_SERVER */
    
    #ifdef CYBLE_UDS_SERVER
        CyBle_UdsInit();
    #endif /* CYBLE_UDS_SERVER */
}


/****************************************************************************** 
* Function Name: CyBle_TimeOutEventHandler
***************************************************************************//**
* 
*  Handles the CYBLE_EVT_TIMEOUT event from the BLE stack.
* 
*  \param eventParam: The pointer to a structure of type CYBLE_TO_REASON_CODE_T.
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_TimeOutEventHandler(const CYBLE_TO_REASON_CODE_T *eventParam)
{
    if(*eventParam == CYBLE_GATT_RSP_TO)
    {
    #if (CYBLE_GATT_ROLE_CLIENT)
        if((cyBle_eventHandlerFlag & CYBLE_AUTO_DISCOVERY) != 0u)
        {
            switch(CyBle_GetClientState())
            {
                case CYBLE_CLIENT_STATE_SRVC_DISCOVERING:
                    CyBle_ApplCallback(CYBLE_EVT_GATTC_SRVC_DISCOVERY_FAILED, NULL);
                    break;
                case CYBLE_CLIENT_STATE_INCL_DISCOVERING:
                    CyBle_ApplCallback(CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED, NULL);
                    break;
                case CYBLE_CLIENT_STATE_CHAR_DISCOVERING:
                    CyBle_ApplCallback(CYBLE_EVT_GATTC_CHAR_DISCOVERY_FAILED, NULL);
                    break;
                case CYBLE_CLIENT_STATE_DESCR_DISCOVERING:
                    CyBle_ApplCallback(CYBLE_EVT_GATTC_DESCR_DISCOVERY_FAILED, NULL);
                    break;
                default:        /* Other states should not be set in Auto discovery mode */
                    break;
            }
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_AUTO_DISCOVERY;
            CyBle_SetClientState(CYBLE_CLIENT_STATE_CONNECTED);
        }
    #endif /* CYBLE_GATT_ROLE_CLIENT */
    #ifdef CYBLE_CPS_SERVER
        CyBle_CpssTimeOutEventHandler();
    #endif /* CYBLE_CPS_SERVER */
    }
    
    /* Connection procedure timeout */
    if(*eventParam == CYBLE_GENERIC_TO)
    {
    #if(CYBLE_GAP_ROLE_CENTRAL)
        if(CYBLE_STATE_CONNECTING == CyBle_GetState())
        {
            (void)CyBle_GapcCancelDeviceConnection();
        }
    #endif /* CYBLE_GAP_ROLE_CENTRAL */
    }
}


/****************************************************************************** 
* Function Name: CyBle_GattConnectReqHandler
***************************************************************************//**
* 
*  Handles the GATT connect event from the BLE stack.
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_GattConnectReqHandler(void)
{
    #ifdef CYBLE_CGMS_SERVER
        CyBle_CgmsInit();
    #endif /* CYBLE_CGMS_SERVER */
    
    #ifdef CYBLE_CPS_SERVER
        CyBle_CpssConnectEventHandler();
    #endif /* CYBLE_CPS_SERVER */
    
    #ifdef CYBLE_CSCS_SERVER
            CyBle_CscsInit();
    #endif /* CYBLE_CSCS_SERVER */
    
    #ifdef CYBLE_LLS_SERVER
        CyBle_LlssConnectEventHandler();
    #endif /* CYBLE_LLS_SERVER */
    
    #ifdef CYBLE_HIDS_SERVER
        CyBle_HidssOnDeviceConnected();
    #endif /* CYBLE_HIDS_SERVER */

    #ifdef CYBLE_RSCS_SERVER
        CyBle_RscsInit();
    #endif /* CYBLE_RSCS_SERVER */
}


#if (CYBLE_GATT_ROLE_SERVER || CYBLE_GATT_ROLE_CLIENT)

/****************************************************************************** 
* Function Name: CyBle_IsDeviceAddressValid
***************************************************************************//**
* 
*  This function verifies that BLE public address has been programmed to SFLASH 
*  during manufacture.
* 
*  \param CYBLE_GAP_BD_ADDR_T *sflashDeviceAddress: the pointer to the BD address of 
*                                            type CYBLE_GAP_BD_ADDR_T. 
* 
* \return
*  Non zero value when a device address differs from the default SFLASH content.
* 
******************************************************************************/
static uint8 CyBle_IsDeviceAddressValid(const CYBLE_GAP_BD_ADDR_T *sflashDeviceAddress)
{
    uint8 i;
    uint8 sflashAddressValid = 0u;
    
    if(sflashDeviceAddress -> type == CYBLE_GAP_ADDR_TYPE_PUBLIC)  
    {
        for(i = 0u; i < CYBLE_GAP_BD_ADDR_SIZE; i++)
        {
            if(sflashDeviceAddress->bdAddr[i] != 0u)
            {
                sflashAddressValid = 1u;
                break;
            }
        }
    }
#if (CYBLE_M0S8BLESS_VERSION != 1)
    sflashAddressValid = 0u;
#endif
    
    return (sflashAddressValid);
}
#endif /* CYBLE_GATT_ROLE_SERVER || CYBLE_GATT_ROLE_CLIENT */


/****************************************************************************** 
* Function Name: CyBle_L2Cap_ConnParamUpdateRspHandler
***************************************************************************//**
* 
*  Handles the L2CAP connection parameter response event from
*  the BLE stack.
* 
*  \param response:
*      * Accepted = 0x0000
*      * Rejected = 0x0001
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_L2Cap_ConnParamUpdateRspEventHandler(uint16 response)
{
    #ifdef CYBLE_CPS_SERVER
        CyBle_CpssConnParamUpdateRspEventHandler(response);
    #endif /* CYBLE_CPS_SERVER */
    
    /* Unreferenced variable warning workaround */
    if(response != 0u)
    {
    }
}


/****************************************************************************** 
* Function Name: CyBle_GapConnUpdateCompleteEventHandler
***************************************************************************//**
* 
*  Handles the CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE event from
*  the BLE stack.
* 
*  \param eventParam: The pointer to the data structure specified by the event.
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_GapConnUpdateCompleteEventHandler(const CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T *eventParam)
{
    #ifdef CYBLE_CPS_SERVER
        CyBle_CpssConnUpdateCompleteEventHandler(eventParam);
    #endif /* CYBLE_CPS_SERVER */
    
    /* Unreferenced variable warning workaround */
    if(eventParam != 0u)
    {
    }
}


/****************************************************************************** 
* Function Name: CyBle_EventHandler
***************************************************************************//**
* 
*  Handles the events from the BLE stack
* 
*  \param eventCode:    the event code
*  \param eventParam:  the event parameters
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_EventHandler(uint8 eventCode, void *eventParam)
{
    cyBle_eventHandlerFlag |= CYBLE_CALLBACK;

    /* Common Profile event handling */
    switch(eventCode)
    {
        /**********************************************************
        * General events
        ************************************************************/
        case CYBLE_EVT_STACK_ON:
        #if(CYBLE_MODE_PROFILE)
        {
            CYBLE_BLESS_PWR_IN_DB_T bleSsPowerLevel;
            
            /* Set Tx Power Level for advertising and connection channels */
            bleSsPowerLevel.blePwrLevelInDbm = CYBLE_TX_POWER_LEVEL_ADV;
            bleSsPowerLevel.bleSsChId = CYBLE_LL_ADV_CH_TYPE;
            (void) CyBle_SetTxPowerLevel (&bleSsPowerLevel);
            bleSsPowerLevel.blePwrLevelInDbm = CYBLE_TX_POWER_LEVEL_CONN;
            bleSsPowerLevel.bleSsChId = CYBLE_LL_CONN_CH_TYPE;
            (void) CyBle_SetTxPowerLevel (&bleSsPowerLevel);
        }
        #endif /* CYBLE_MODE_PROFILE */
        #if (CYBLE_GATT_ROLE_SERVER || CYBLE_GATT_ROLE_CLIENT)
            /* Set device Address  */
            if(CyBle_IsDeviceAddressValid(cyBle_sflashDeviceAddress) != 0u)
            {
                (void) CyBle_SetDeviceAddress(cyBle_sflashDeviceAddress);
                #if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
                    CyBle_ChangeAdDeviceAddress(cyBle_sflashDeviceAddress, 0u);
                    CyBle_ChangeAdDeviceAddress(cyBle_sflashDeviceAddress, 1u);
                #endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */    
            }
            else
            {
            #if (SILICON_GENERATED_DEVICE_ADDRESS != 0u)
                cyBle_deviceAddress.bdAddr[0] = CYBLE_SFLASH_DIE_X_REG;
                cyBle_deviceAddress.bdAddr[1] = CYBLE_SFLASH_DIE_Y_REG;
                cyBle_deviceAddress.bdAddr[2] = CYBLE_SFLASH_DIE_WAFER_REG;
            #endif /* SILICON_GENERATED_DEVICE_ADDRESS != 0u */
                (void) CyBle_SetDeviceAddress(&cyBle_deviceAddress);
                #if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
                    CyBle_ChangeAdDeviceAddress(&cyBle_deviceAddress, 0u);
                    CyBle_ChangeAdDeviceAddress(&cyBle_deviceAddress, 1u);
                #endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */    
            }
            /* Set device IO Capability  */
            (void) CyBle_GapSetIoCap(CYBLE_IO_CAPABILITY);    
        #endif /* CYBLE_GATT_ROLE_SERVER || CYBLE_GATT_ROLE_CLIENT */
            CyBle_SetState(CYBLE_STATE_DISCONNECTED);
            break;
        case CYBLE_EVT_TIMEOUT:
            CyBle_TimeOutEventHandler((CYBLE_TO_REASON_CODE_T *)eventParam);
            break;
    	case CYBLE_EVT_STACK_BUSY_STATUS:
            cyBle_busyStatus = *(uint8 *)eventParam;
            break;

        /**********************************************************
        * GAP events
        ************************************************************/
        case CYBLE_EVT_GAP_AUTH_REQ:
        #if(CYBLE_MODE_PROFILE)
            if(0u == (cyBle_eventHandlerFlag & CYBLE_DISABLE_AUTOMATIC_AUTH))
            {
                /* If the responding device does not support pairing then the responding 
                   device shall respond using the Pairing Failed message with the error 
                   code "Pairing Not Supported" otherwise it responds with a Pairing 
                   Response message.
                */
                if(cyBle_authInfo.security == (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_1))
                {
                    cyBle_authInfo.authErr = CYBLE_GAP_AUTH_ERROR_PAIRING_NOT_SUPPORTED;
                }    
            #if(CYBLE_GAP_ROLE_PERIPHERAL)
                (void)CyBle_GappAuthReqReply(cyBle_connHandle.bdHandle, &cyBle_authInfo);
            #endif /* CYBLE_GAP_ROLE_PERIPHERAL */
            #if (CYBLE_GAP_ROLE_CENTRAL)
                (void)CyBle_GapAuthReq(cyBle_connHandle.bdHandle, &cyBle_authInfo);
            #endif /* CYBLE_GAP_ROLE_CENTRAL */
            }
        #endif /* CYBLE_MODE_PROFILE */
            break;
        
        case CYBLE_EVT_GAP_AUTH_COMPLETE:
        #if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
            cyBle_peerBonding = ((CYBLE_GAP_AUTH_INFO_T *)eventParam)->bonding;
        #endif  /* CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES */
            break;
        
        case CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE:
            CyBle_GapConnUpdateCompleteEventHandler((const CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T *)eventParam);
            break;
            
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            CyBle_GapConnUpdateCompleteEventHandler((const CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T *)eventParam);
            #if(CYBLE_GAP_ROLE_CENTRAL)
                if(cyBle_connectingTimeout != 0u)
                {
                   (void)CyBle_StopTimer();
                }
            #endif /* CYBLE_GAP_ROLE_CENTRAL */
            CyBle_SetState(CYBLE_STATE_CONNECTED);
            break;

        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_SetState(CYBLE_STATE_DISCONNECTED);
            break;
        #if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
            
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            #ifdef CYBLE_CPS_SERVER
                #if(CYBLE_GAP_ROLE_BROADCASTER)
                    CyBle_CpssAdvertisementStartStopEventHandler();
                #endif /* CYBLE_GAP_ROLE_BROADCASTER */
            #endif /* CYBLE_CPS_SERVER */
            
            if((CYBLE_STATE_CONNECTED != CyBle_GetState()) && ((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u))
            {
                /* After CyBle_GappStartAdvertisement first event indicates that advertising has been started */
                if(0u != (cyBle_eventHandlerFlag & CYBLE_START_FLAG))
                {
                    CyBle_SetState(CYBLE_STATE_ADVERTISING);
                    cyBle_eventHandlerFlag &= (uint8)~CYBLE_START_FLAG;
                }
                /* When application initiated stop advertisement */
                else if(0u != (cyBle_eventHandlerFlag & CYBLE_STOP_FLAG))
                {
                    CyBle_SetState(CYBLE_STATE_DISCONNECTED);  
                    cyBle_eventHandlerFlag &= (uint8)~CYBLE_STOP_FLAG;
                }
                else /* Following event indicates that advertising has been stopped */
                {
                    if(CYBLE_STATE_ADVERTISING == CyBle_GetState())
                    {
                        CyBle_SetState(CYBLE_STATE_DISCONNECTED);
                    #if ((CYBLE_SLOW_ADV_ENABLED != 0u) && (CYBLE_FAST_ADV_TIMEOUT != 0u))
                        if(cyBle_advertisingIntervalType == CYBLE_ADVERTISING_FAST)
                        {
                            /* When fast advertising time out occur: Start slow advertising */
                            if(CYBLE_ERROR_OK == CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_SLOW))
                            {
                                CyBle_SetState(CYBLE_STATE_ADVERTISING);
                            }
                        }
                    #endif /* CYBLE_SLOW_ADV_ENABLED */
                    }
                }
            }
            break;
        #endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */
        
        #if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)    
        case CYBLE_EVT_GAPC_SCAN_START_STOP:
            #ifdef CYBLE_CPS_CLIENT
                CyBle_CpscScanStartStopEventHandler();
            #endif /* CYBLE_CPS_CLIENT */
            
            if((CYBLE_STATE_CONNECTED != CyBle_GetState()) && ((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u))
            {
                /* After CyBle_GapcStartScan first event indicates that scanning has been started */
                if(0u != (cyBle_eventHandlerFlag & CYBLE_START_FLAG))
                {
                    CyBle_SetState(CYBLE_STATE_SCANNING);
                    cyBle_eventHandlerFlag &= (uint8)~CYBLE_START_FLAG;
                }
                /* When application initiated stop scanning */
                else if(0u != (cyBle_eventHandlerFlag & CYBLE_STOP_FLAG))
                {
                    CyBle_SetState(CYBLE_STATE_DISCONNECTED);  
                    cyBle_eventHandlerFlag &= (uint8)~CYBLE_STOP_FLAG;
                }
                else /* Following event indicates that scanning has been stopped by stack */
                {
                    if(CYBLE_STATE_SCANNING == CyBle_GetState())
                    {
                        CyBle_SetState(CYBLE_STATE_DISCONNECTED);  
                    #if ((CYBLE_SLOW_SCAN_ENABLED != 0u) && (CYBLE_FAST_SCAN_TIMEOUT != 0u))
                        if(cyBle_scanningIntervalType == CYBLE_SCANNING_FAST)
                        {
                            /* When fast scanning time out occur: Start slow scanning */
                            if(CYBLE_ERROR_OK == CyBle_GapcStartScan(CYBLE_SCANNING_SLOW))
                            {
                                CyBle_SetState(CYBLE_STATE_SCANNING);
                            }
                        }
                    #endif /* CYBLE_SLOW_SCAN_ENABLED */
                    }
                }
            }
            break;
        #endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */

        /**********************************************************
        * L2AP events 
        ************************************************************/
        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
            CyBle_L2Cap_ConnParamUpdateRspEventHandler(*(uint16 *)eventParam);
            break;
        
        /**********************************************************
        * GATT events
        ************************************************************/        
        case CYBLE_EVT_GATT_CONNECT_IND:
            cyBle_connHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
            
        #if((CYBLE_GATT_ROLE_SERVER) && (CYBLE_GATT_DB_CCCD_COUNT != 0u))
            /* Init CCCD values in RAM */
        	(void) memcpy (cyBle_attValuesCCCD, cyBle_flashStorage.attValuesCCCDFlashMemory[cyBle_connHandle.bdHandle], 
                            CYBLE_GATT_DB_CCCD_COUNT);
        #endif /* CYBLE_GATT_ROLE_SERVER */
        
        #if (CYBLE_GATT_ROLE_CLIENT)
            CyBle_SetClientState(CYBLE_CLIENT_STATE_CONNECTED);
        #endif /* CYBLE_GATT_ROLE_CLIENT */
        
            CyBle_GattConnectReqHandler();
            break;

        case CYBLE_EVT_GATT_DISCONNECT_IND:
            CyBle_GattDisconnectEventHandler();
            break;

    #if((CYBLE_GATT_ROLE_SERVER) || (CYBLE_GATT_ROLE_CLIENT))
        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
            {
                uint16 cyBle_mtuSize;
                if(CYBLE_GATT_MTU > ((CYBLE_GATT_XCHG_MTU_PARAM_T *)eventParam)->mtu)
                {
                    cyBle_mtuSize = ((CYBLE_GATT_XCHG_MTU_PARAM_T *)eventParam)->mtu;
                }
                else
                {
                    cyBle_mtuSize = CYBLE_GATT_MTU;
                }
                (void)CyBle_GattsExchangeMtuRsp(((CYBLE_GATT_XCHG_MTU_PARAM_T *)eventParam)->connHandle, cyBle_mtuSize);
            }
            break;
    #endif /* CYBLE_GATT_ROLE_SERVER || CYBLE_GATT_ROLE_CLIENT */
    
    #if (CYBLE_GATT_ROLE_CLIENT)
        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
        #ifdef CYBLE_CPS_CLIENT
                CyBle_CpscScanProcessEventHandler((CYBLE_GAPC_ADV_REPORT_T *)eventParam);
        #endif /* CYBLE_CPS_CLIENT */
            break;
    #endif /* CYBLE_GATT_ROLE_CLIENT */

    #if(CYBLE_GATT_ROLE_SERVER)
        case CYBLE_EVT_GATTS_WRITE_REQ:
            CyBle_WriteReqHandler((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam);
            break;

        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
        #ifdef CYBLE_IAS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                (void)CyBle_IassWriteCmdEventHandler((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_IAS_SERVER */
        #ifdef CYBLE_HIDS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                (void)CyBle_HidssWriteEventHandler((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_HIDS_SERVER */
        #ifdef CYBLE_PASS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                (void)CyBle_PasssWriteCmdEventHandler((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_PASS_SERVER */
        #ifdef CYBLE_RTUS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                (void)CyBle_RtussWriteCmdEventHandler((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_RTUS_SERVER */
        #ifdef CYBLE_SCPS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                (void)CyBle_ScpssWriteEventHandler((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_SCPS_SERVER */
            break;
        
        case CYBLE_EVT_GATTS_PREP_WRITE_REQ:
        #ifdef CYBLE_BMS_SERVER
            CyBle_BmssPrepareWriteRequestEventHandler((CYBLE_GATTS_PREP_WRITE_REQ_PARAM_T *)eventParam);
        #endif /* CYBLE_BMS_SERVER */
        #ifdef CYBLE_BTS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_BtssPrepareWriteRequestEventHandler((CYBLE_GATTS_PREP_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_BTS_SERVER */
        #ifdef CYBLE_ESS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_EsssPrepareWriteRequestEventHandler((CYBLE_GATTS_PREP_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_ESS_SERVER */
		#ifdef CYBLE_UDS_SERVER
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_UdssPrepareWriteRequestEventHandler((CYBLE_GATTS_PREP_WRITE_REQ_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_UDS_SERVER */
            break;

        case CYBLE_EVT_GATTS_EXEC_WRITE_REQ:
        #ifdef CYBLE_BMS_SERVER
            CyBle_BmssExecuteWriteRequestEventHandler((CYBLE_GATTS_EXEC_WRITE_REQ_T *)eventParam);
        #endif /* CYBLE_BMS_SERVER */
        #ifdef CYBLE_BTS_SERVER
            CyBle_BtssExecuteWriteRequestEventHandler((CYBLE_GATTS_EXEC_WRITE_REQ_T *)eventParam);
        #endif /* CYBLE_BTS_SERVER */
        #ifdef CYBLE_ESS_SERVER
            CyBle_EsssExecuteWriteRequestEventHandler((CYBLE_GATTS_EXEC_WRITE_REQ_T *)eventParam);
        #endif /* CYBLE_ESS_SERVER */
		#ifdef CYBLE_UDS_SERVER
            CyBle_UdssExecuteWriteRequestEventHandler((CYBLE_GATTS_EXEC_WRITE_REQ_T *)eventParam);
        #endif /* CYBLE_UDS_SERVER */
            break;
        
        case CYBLE_EVT_GATTS_HANDLE_VALUE_CNF:
            CyBle_ValueConfirmation((CYBLE_CONN_HANDLE_T *)eventParam);
            break;
            
        case CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
        #ifdef CYBLE_UDS_SERVER
            CyBle_UdssReadRequestEventHandler((CYBLE_GATTS_CHAR_VAL_READ_REQ_T *)eventParam);
        #endif /* CYBLE_UDS_SERVER */
            break;
            
    #endif /* CYBLE_GATT_ROLE_SERVER */

    #if (CYBLE_GATT_ROLE_CLIENT)
        
        case CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP:
            CyBle_ReadByGroupEventHandler((CYBLE_GATTC_READ_BY_GRP_RSP_PARAM_T *)eventParam);
            break;

        case CYBLE_EVT_GATTC_READ_BY_TYPE_RSP:
            CyBle_ReadByTypeEventHandler((CYBLE_GATTC_READ_BY_TYPE_RSP_PARAM_T *)eventParam);
            break;

        case CYBLE_EVT_GATTC_READ_BLOB_RSP:
        #ifdef CYBLE_ESS_CLIENT
            CyBle_EsscReadLongRespEventHandler((CYBLE_GATTC_READ_RSP_PARAM_T *)eventParam);
        #endif /* CYBLE_ESS_CLIENT */
        #ifdef CYBLE_UDS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_UdscReadLongRespEventHandler((CYBLE_GATTC_READ_RSP_PARAM_T *)eventParam);
            }
        #endif /* CYBLE_UDS_CLIENT */
            break;
        
        case CYBLE_EVT_GATTC_FIND_INFO_RSP:
            CyBle_FindInfoEventHandler((CYBLE_GATTC_FIND_INFO_RSP_PARAM_T *)eventParam);
            break;

        case CYBLE_EVT_GATTC_ERROR_RSP:
            CyBle_ErrorResponseEventHandler((CYBLE_GATTC_ERR_RSP_PARAM_T *)eventParam);
            break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF:
            CyBle_NotificationEventHandler((CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T *)eventParam);
            break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_IND:
            CyBle_GattcIndicationEventHandler((CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *)eventParam);
            CyBle_IndicationEventHandler((CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *)eventParam);
        
            /* Respond with a Handle Value Confirmation when request handled */
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) == 0u)
            {
                (void)CyBle_GattcConfirmation(((CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *)eventParam)->connHandle);
            }
            break;
        
        case CYBLE_EVT_GATTC_READ_RSP:
            CyBle_ReadResponseEventHandler((CYBLE_GATTC_READ_RSP_PARAM_T *)eventParam);
            break;

        case CYBLE_EVT_GATTC_WRITE_RSP:
            CyBle_GattcWriteResponseEventHandler((CYBLE_CONN_HANDLE_T *)eventParam);
            break;
            
        case CYBLE_EVT_GATTC_EXEC_WRITE_RSP:
        #ifdef CYBLE_BMS_CLIENT
            CyBle_BmscExecuteWriteResponseEventHandler((CYBLE_GATTC_EXEC_WRITE_RSP_T *)eventParam);
        #endif /* CYBLE_BMS_CLIENT */
        #ifdef CYBLE_ESS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_EsscExecuteWriteResponseEventHandler((CYBLE_GATTC_EXEC_WRITE_RSP_T *)eventParam);
            }
        #endif /* CYBLE_ESS_CLIENT */
        #ifdef CYBLE_UDS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_UdscExecuteWriteResponseEventHandler((CYBLE_GATTC_EXEC_WRITE_RSP_T *)eventParam);
            }
        #endif /* CYBLE_UDS_CLIENT */
            break;
            
    #endif /* CYBLE_GATT_ROLE_CLIENT */

    #if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))

        case CYBLE_EVT_PENDING_FLASH_WRITE:
            cyBle_pendingFlashWrite |= CYBLE_PENDING_STACK_FLASH_WRITE_BIT;
            break;
        
    #endif  /* (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */
    
        default:
            break;
    }

    if(0u != (cyBle_eventHandlerFlag & (CYBLE_CALLBACK | CYBLE_ENABLE_ALL_EVENTS))) 
    {
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
        CyBle_ApplCallback((uint32)eventCode, eventParam);
    }
}


#if (CYBLE_GATT_ROLE_CLIENT)


/****************************************************************************** 
* Function Name: CyBle_ReadByGroupEventHandler
***************************************************************************//**
* 
*  Handles the Read By Group Response Event during an automatic server discovery
*  process.
* 
*  \param eventParam:  the event parameters for a Read By Group Response
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_ReadByGroupEventHandler(CYBLE_GATTC_READ_BY_GRP_RSP_PARAM_T *eventParam)
{
    uint16 j;
    uint16 dataLength;
    uint16 attrLength;
    uint16 i;
    CYBLE_DISC_SRVC128_INFO_T* discServInfo = NULL;
    uint8 flag;
    if((CYBLE_CLIENT_STATE_SRVC_DISCOVERING == CyBle_GetClientState()) &&
        ((cyBle_eventHandlerFlag & CYBLE_AUTO_DISCOVERY) != 0u))
    {
        dataLength = eventParam->attrData.length;

        if((dataLength == CYBLE_DISC_SRVC_INFO_LEN) || (dataLength == CYBLE_DISC_SRVC_INFO_128_LEN))
        {
            attrLength = eventParam->attrData.attrLen;

            for(i = 0u; i < attrLength; i += dataLength)
            {
                discServInfo = (CYBLE_DISC_SRVC128_INFO_T *)(eventParam->attrData.attrValue + i);
                flag = 0u;

                if(dataLength == CYBLE_DISC_SRVC_INFO_LEN)
                {
					for(j = 0u; (j < (uint16)CYBLE_SRVI_COUNT) && (flag == 0u); j++)
                    {
                        if(cyBle_serverInfo[j].uuid == discServInfo->uuid.uuid16)
                        {
                            if(cyBle_serverInfo[j].range.startHandle == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
                            {
                                cyBle_serverInfo[j].range = discServInfo->range;
                                flag = 1u;
                            }
                            else    /* Duplication of service */
                            {
                                /* For multiple service support next service has the same uuid */
                                if((j >= (CYBLE_SRVI_COUNT - 1u)) || 
                                   (cyBle_serverInfo[j + 1u].uuid != discServInfo->uuid.uuid16))
                                {
                                    CyBle_ApplCallback(CYBLE_EVT_GATTC_SRVC_DUPLICATION, &discServInfo->uuid.uuid16);
                                    flag = 1u;
                                }
                            }
                        }
                    }
                }
                else  /* Received 128 bit service UUID */
                {
                #ifdef CYBLE_ANCS_CLIENT
                    CyBle_AncscDiscoverServiceEventHandler(discServInfo);
                #endif /* CYBLE_CUSTOM_CLIENT */
                #ifdef CYBLE_CUSTOM_CLIENT
                    CyBle_CustomcDiscoverServiceEventHandler(discServInfo);
                #endif /* CYBLE_CUSTOM_CLIENT */
                }
            }

            if((discServInfo != NULL) && (discServInfo->range.endHandle == CYBLE_GATT_ATTR_HANDLE_END_RANGE))
            {
            #if(CYBLE_STACK_MODE_DEBUG)
                CyBle_ApplCallback(CYBLE_EVT_GATTC_SRVC_DISCOVERY_COMPLETE, NULL);
            #endif /* CYBLE_STACK_MODE_DEBUG */   
                CyBle_SetClientState(CYBLE_CLIENT_STATE_INCL_DISCOVERING);
                CyBle_NextInclDiscovery(CYBLE_DISCOVERY_INIT);
            }
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
        }
        else
        {
            CyBle_ApplCallback(CYBLE_EVT_GATTC_SRVC_DISCOVERY_FAILED, NULL);
        }
    }
}


/****************************************************************************** 
* Function Name: CyBle_NextInclDiscovery
***************************************************************************//**
* 
*  Looks for the included services in the current service (pointed by
*   cyBle_disCount). If the current service handle range is invalid (any of start
*   or end handle is invalid), then increment the cyBle_disCount and check
*   the next service range and does so until a valid range is caught or the end of
*   the service set is reached.
* 
*  \param incrementIndex: Not zero value indicates that service index should be 
*                         incremented.
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_NextInclDiscovery(uint8 incrementIndex)
{

    if(incrementIndex != CYBLE_DISCOVERY_INIT)
    {
        cyBle_disCount++;
    }
    else
    {
        cyBle_disCount = 0u;
        cyBle_discInclInfo.inclDefHandle = 0u;
    }

    /* Skip not existing services */
    while((cyBle_disCount < (uint8) CYBLE_SRVI_COUNT) &&
          (cyBle_serverInfo[cyBle_disCount].range.startHandle == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE))
    {
        cyBle_disCount++;
    }

    if(cyBle_disCount < (uint8) CYBLE_SRVI_COUNT)
    {
        if(CYBLE_ERROR_OK != CyBle_GattcFindIncludedServices(cyBle_connHandle, &cyBle_serverInfo[cyBle_disCount].range))
        {
            CyBle_ApplCallback(CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED, NULL);
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_AUTO_DISCOVERY;
        }
    }
    else /* Included service discovery procedure is done, start characteristic discovery procedure */
    {
        #if(CYBLE_STACK_MODE_DEBUG)
            CyBle_ApplCallback(CYBLE_EVT_GATTC_INCL_DISCOVERY_COMPLETE, NULL);
        #endif /* CYBLE_STACK_MODE_DEBUG */
            CyBle_SetClientState(CYBLE_CLIENT_STATE_CHAR_DISCOVERING);
            CyBle_NextCharDiscovery(CYBLE_DISCOVERY_INIT);
    }
}


/****************************************************************************** 
* Function Name: CyBle_GapcDiscoverCharacteristicsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a "CYBLE_EVT_GATTC_READ_BY_TYPE_RSP"
*  event. Based on the service UUID, an appropriate data structure is populated
*  using the data received as part of the callback.
* 
*  \param discCharInfo:  the pointer to a characteristic information structure.
* 
* \return
*  None
* 
******************************************************************************/
static void CyBle_GapcDiscoverCharacteristicsEventHandler(CYBLE_DISC_CHAR_INFO_T *discCharInfo)
{
    switch(discCharInfo->uuid.uuid16)
    {
    case CYBLE_UUID_CHAR_DEVICE_NAME:
        CYBLE_GapcCheckCharHandle(cyBle_gapc.deviceNameCharHandle, discCharInfo);
        break;

    case CYBLE_UUID_CHAR_APPEARANCE:
        CYBLE_GapcCheckCharHandle(cyBle_gapc.appearanceCharHandle, discCharInfo);
        break;

    case CYBLE_UUID_CHAR_PERIPH_PRIVCY_FLAG:
        CYBLE_GapcCheckCharHandle(cyBle_gapc.periphPrivacyCharHandle, discCharInfo);
        break;

    case CYBLE_UUID_CHAR_RECONNECTION_ADDR:
        CYBLE_GapcCheckCharHandle(cyBle_gapc.reconnAddrCharHandle, discCharInfo);
        break;

    case CYBLE_UUID_CHAR_PRFRRD_CNXN_PARAM:
        CYBLE_GapcCheckCharHandle(cyBle_gapc.prefConnParamCharHandle, discCharInfo);
        break;

    default:
        break;
    }
}


/****************************************************************************** 
* Function Name: CyBle_ReadByTypeEventHandler
***************************************************************************//**
*  Handles the Read By Type Response Event during an automatic server discovery
*  process.
* 
*  \param eventParam: The event parameters for a Read By Type Response.
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_ReadByTypeEventHandler(CYBLE_GATTC_READ_BY_TYPE_RSP_PARAM_T *eventParam)
{
    uint16 dataLength;
    uint16 attrLength;
    uint16 i, j;
    uint8 *attrVal;

    if((cyBle_eventHandlerFlag & CYBLE_AUTO_DISCOVERY) != 0u)
    {
        /* Count of service information pieces in this mtu */
        dataLength = eventParam->attrData.length;
        attrLength = eventParam->attrData.attrLen;
        attrVal = eventParam->attrData.attrValue;
        
        if(CYBLE_CLIENT_STATE_CHAR_DISCOVERING == CyBle_GetClientState())
        {
            CYBLE_DISC_CHAR_INFO_T discCharInfo;
            
            for(i = 0u; i < attrLength; i += dataLength)
            {
                discCharInfo.charDeclHandle = CyBle_Get16ByPtr(attrVal);
                attrVal += sizeof(discCharInfo.charDeclHandle);
                discCharInfo.properties = *attrVal;
                attrVal += sizeof(discCharInfo.properties);
                discCharInfo.valueHandle = CyBle_Get16ByPtr(attrVal);
                attrVal += sizeof(discCharInfo.valueHandle);
                /* Characteristics discovery with 128-bit uuid */
                if(dataLength == CYBLE_DISC_CHAR_INFO_128_LEN)
                {
                    discCharInfo.uuidFormat = CYBLE_GATT_128_BIT_UUID_FORMAT;
                    (void)memcpy(&discCharInfo.uuid.uuid128, attrVal, CYBLE_GATT_128_BIT_UUID_SIZE);
                    attrVal += CYBLE_GATT_128_BIT_UUID_SIZE;
                    /* Switch by service uuid */
                    switch (cyBle_serverInfo[cyBle_disCount].uuid)
                    {
                        case CYBLE_UUID_WIRELESS_POWER_TRANSFER_SERVICE:
                            #ifdef CYBLE_WPTS_CLIENT
                                CyBle_WptscDiscoverCharacteristicsEventHandler(&discCharInfo);
                            #endif /* CYBLE_WPTS_CLIENT */
                            break;
                    
                        default:
                    #ifdef CYBLE_ANCS_CLIENT
                        if(cyBle_disCount == CYBLE_SRVI_ANCS)
                        {
                            CyBle_AncscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        }
                    #endif /* CYBLE_ANCS_CLIENT */
                    #ifdef CYBLE_CUSTOM_CLIENT
                        if((cyBle_disCount >= CYBLE_SRVI_CUSTOMS) && (cyBle_disCount <= CYBLE_SRVI_CUSTOMS_END))
                        {
                            CyBle_CustomcDiscoverCharacteristicsEventHandler(cyBle_disCount - CYBLE_SRVI_CUSTOMS, &discCharInfo);
                        }
                    #endif /* CYBLE_CUSTOM_CLIENT */
                        break;
                    }
                }
                else if(dataLength == CYBLE_DISC_CHAR_INFO_LEN)
                {
                    discCharInfo.uuidFormat = CYBLE_GATT_16_BIT_UUID_FORMAT;
                    discCharInfo.uuid.uuid16 = CyBle_Get16ByPtr(attrVal);
                    attrVal += CYBLE_GATT_16_BIT_UUID_SIZE;

                    /* Switch by service uuid */
                    switch (cyBle_serverInfo[cyBle_disCount].uuid)
                    {
                    case CYBLE_UUID_GAP_SERVICE:
                        CyBle_GapcDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;

                    case CYBLE_UUID_GATT_SERVICE:
                        CyBle_GattcDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                
                #ifdef CYBLE_ANS_CLIENT
                    case CYBLE_UUID_ALERT_NOTIFICATION_SERVICE:
                        CyBle_AnscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_ANS_CLIENT */
                #ifdef CYBLE_BAS_CLIENT
                    case CYBLE_UUID_BAS_SERVICE:
                        CyBle_BascDiscoverCharacteristicsEventHandler(cyBle_disCount - CYBLE_SRVI_BAS, &discCharInfo);
                        break;
                #endif /* CYBLE_BAS_CLIENT */
                #ifdef CYBLE_BCS_CLIENT
                    case CYBLE_UUID_BODY_COMPOSITION_SERVICE:
                        CyBle_BcscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_BCS_CLIENT */
                #ifdef CYBLE_BLS_CLIENT
                    case CYBLE_UUID_BLOOD_PRESSURE_SERVICE:
                        CyBle_BlscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_BLS_CLIENT */
                #ifdef CYBLE_BMS_CLIENT
                    case CYBLE_UUID_BOND_MANAGEMENT_SERVICE:
                        CyBle_BmscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_BMS_CLIENT */
                #ifdef CYBLE_CGMS_CLIENT
                    case CYBLE_UUID_CGM_SERVICE:
                        CyBle_CgmscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_CGMS_CLIENT */
                #ifdef CYBLE_CPS_CLIENT
                    case CYBLE_UUID_CPS_SERVICE:
                        CyBle_CpscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_CPS_CLIENT */
                #ifdef CYBLE_CSCS_CLIENT
                    case CYBLE_UUID_CYCLING_SPEED_AND_CADENCE_SERVICE:
                        CyBle_CscscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_CSCS_CLIENT */
                #ifdef CYBLE_CTS_CLIENT
                    case CYBLE_UUID_CURRENT_TIME_SERVICE:
                        CyBle_CtscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_CTS_CLIENT */
                
                #ifdef CYBLE_DIS_CLIENT
                    case CYBLE_UUID_DEVICE_INFO_SERVICE:
                        CyBle_DiscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_DIS_CLIENT */
                #ifdef CYBLE_ESS_CLIENT
                    case CYBLE_UUID_ENVIRONMENTAL_SENSING_SERVICE:
                        CyBle_EsscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_ESS_CLIENT */
                #ifdef CYBLE_GLS_CLIENT
                    case CYBLE_UUID_GLUCOSE_SERVICE:
                        CyBle_GlscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_GLS_CLIENT */
                
                #ifdef CYBLE_HIDS_CLIENT
                    case CYBLE_UUID_HIDS_SERVICE:
                        CyBle_HidscDiscoverCharacteristicsEventHandler(cyBle_disCount - CYBLE_SRVI_HIDS, &discCharInfo);
                        break;
                #endif /* CYBLE_HIDS_CLIENT */
                #ifdef CYBLE_HRS_CLIENT
                    case CYBLE_UUID_HEART_RATE_SERVICE:
                        CyBle_HrscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_HRS_CLIENT */
                #ifdef CYBLE_HTS_CLIENT
                    case CYBLE_UUID_HEALTH_THERMOMETER_SERVICE:
                        CyBle_HtscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_HRS_CLIENT */
                #ifdef CYBLE_IAS_CLIENT
                    case CYBLE_UUID_IMMEDIATE_ALERT_SERVICE:
                        CyBle_IascDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_IAS_CLIENT */
                #ifdef CYBLE_LLS_CLIENT
                    case CYBLE_UUID_LINK_LOSS_SERVICE:
                        CyBle_LlscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_LLS_CLIENT */
                #ifdef CYBLE_LNS_CLIENT
                    case CYBLE_UUID_LOCATION_AND_NAVIGATION_SERVICE:
                        CyBle_LnscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_LNS_CLIENT */
                #ifdef CYBLE_PASS_CLIENT
                    case CYBLE_UUID_PHONE_ALERT_STATUS_SERVICE:
                        CyBle_PasscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_PASS_CLIENT */
                #ifdef CYBLE_NDCS_CLIENT
                    case CYBLE_UUID_NEXT_DST_CHANGE_SERVICE:
                        CyBle_NdcscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_NDCS_CLIENT */
                #ifdef CYBLE_RSCS_CLIENT
                    case CYBLE_UUID_RUNNING_SPEED_AND_CADENCE_SERVICE:
                        CyBle_RscscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_RSCS_CLIENT */
                #ifdef CYBLE_RTUS_CLIENT
                    case CYBLE_UUID_REF_TIME_UPDATE_SERVICE:
                        CyBle_RtuscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_RTUS_CLIENT */
                #ifdef CYBLE_SCPS_CLIENT
                    case CYBLE_UUID_SCAN_PARAM_SERVICE:
                        CyBle_ScpscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_SCPS_CLIENT */
                #ifdef CYBLE_TPS_CLIENT
                    case CYBLE_UUID_TX_POWER_SERVICE:
                        CyBle_TpscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_TPS_CLIENT */
                #ifdef CYBLE_UDS_CLIENT
                    case CYBLE_UUID_USER_DATA_SERVICE:
                        CyBle_UdscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_UDS_CLIENT */
                #ifdef CYBLE_WSS_CLIENT
                    case CYBLE_UUID_WEIGHT_SCALE_SERVICE:
                        CyBle_WsscDiscoverCharacteristicsEventHandler(&discCharInfo);
                        break;
                #endif /* CYBLE_WSS_CLIENT */
                    default:
                #ifdef CYBLE_CUSTOM_CLIENT
                    if((cyBle_disCount >= CYBLE_SRVI_CUSTOMS) && (cyBle_disCount <= CYBLE_SRVI_CUSTOMS_END))
                    {
                        CyBle_CustomcDiscoverCharacteristicsEventHandler(cyBle_disCount - CYBLE_SRVI_CUSTOMS, &discCharInfo);
                    }
                #endif /* CYBLE_CUSTOM_CLIENT */
                        break;
                    }
                }
                else
                {
                    /* Unsupported data length value */
                }

                /* The sub-procedure is complete when an Error Response is received and the
                   Error Code is set to an Attribute Not Found or the Read By Type Response has an
                   Attribute Handle that is equal to the Ending Handle of the request. */
                if(discCharInfo.valueHandle == cyBle_serverInfo[cyBle_disCount].range.endHandle)
                {
                    CyBle_NextCharDiscovery(CYBLE_DISCOVERY_CONTINUE);
                }

                cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
            }
        }
        else if(CYBLE_CLIENT_STATE_INCL_DISCOVERING == CyBle_GetClientState())
        {
            CYBLE_DISC_INCL_INFO_T discInclInfo;
            
            for(i = 0; i < attrLength; i += dataLength)
            {
                discInclInfo.inclDefHandle = CyBle_Get16ByPtr(attrVal);
                attrVal += sizeof(discInclInfo.inclDefHandle);
                discInclInfo.inclHandleRange.startHandle = CyBle_Get16ByPtr(attrVal);
                attrVal += sizeof(discInclInfo.inclHandleRange.startHandle);
                discInclInfo.inclHandleRange.endHandle = CyBle_Get16ByPtr(attrVal);
                attrVal += sizeof(discInclInfo.inclHandleRange.endHandle);

                if(dataLength == CYBLE_DISC_INCL_INFO_128_LEN)
                {
                    discInclInfo.uuidFormat = CYBLE_GATT_128_BIT_UUID_FORMAT;
                    /* Only custom service supports 128-bit uuid */
                #ifdef CYBLE_CUSTOM_CLIENT
                    /* Stop ongoing GATT operation */
                    CyBle_GattcStopCmd();
                    /* Get the included service UUID when the included service uses a 128-bit
                       UUID, the Read Request is used. The Attribute Handle for the Read Request is
                       the Attribute Handle of the included service.
                    */
                    if(CYBLE_ERROR_OK == CyBle_GattcReadCharacteristicValue(cyBle_connHandle, 
                                            discInclInfo.inclHandleRange.startHandle))
                    {
                        /* Save handle to support read response from device */
                        cyBle_discInclInfo = discInclInfo;
                    }
                    else
                    {
                        CyBle_ApplCallback(CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED, NULL);
                        cyBle_eventHandlerFlag &= (uint8)~CYBLE_AUTO_DISCOVERY;
                    }
                #endif /* CYBLE_CUSTOM_CLIENT */
                }
                else if(dataLength == CYBLE_DISC_INCL_INFO_LEN)
                {
                    discInclInfo.uuidFormat = CYBLE_GATT_16_BIT_UUID_FORMAT;
                    discInclInfo.uuid.uuid16 = CyBle_Get16ByPtr(attrVal);
                    attrVal += CYBLE_GATT_16_BIT_UUID_SIZE;
                    
                    /* Store range of included service in list of services for discovery */
                    for(j = 0u; j < (uint8) CYBLE_SRVI_COUNT; j++)
                    {
                        if(cyBle_serverInfo[j].uuid == discInclInfo.uuid.uuid16)
                        {
                            if(cyBle_serverInfo[j].range.startHandle == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
                            {
                                cyBle_serverInfo[j].range = discInclInfo.inclHandleRange;
                                break;
                            }
                        }
                    }

                    /* Switch by service uuid */
                    switch (cyBle_serverInfo[cyBle_disCount].uuid)
                    {
                        case CYBLE_UUID_HIDS_SERVICE:
                        #ifdef CYBLE_HIDS_CLIENT    
                            CyBle_HidscInclDiscoveryEventHandler(cyBle_disCount - CYBLE_SRVI_HIDS, &discInclInfo);
                        #endif /* CYBLE_HIDS_CLIENT */
                            break;
                    /* other services */

                    default:
                        break;
                    }
                }
                else
                {
                    /* Unsupported data length value */
                }
                /* The sub-procedure is complete when an Error Response is received and the
                   Error Code is set to an Attribute Not Found or the Read By Type Response has an
                   Attribute Handle that is equal to the Ending Handle of the request. 
                   Not complete when Read Request is sent to read 128-bit UUID.
                */
                if((discInclInfo.inclDefHandle == cyBle_serverInfo[cyBle_disCount].range.endHandle) && 
                   (cyBle_discInclInfo.inclDefHandle != 0u))
                {
                    CyBle_NextInclDiscovery(CYBLE_DISCOVERY_CONTINUE);
                }
                cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
            }
        }
        else
        {
            /* Unhandled state value */
        }
    }
}


/****************************************************************************** 
* Function Name: CyBle_NextCharDiscovery
***************************************************************************//**
* 
*  Looks for a characteristic handle range for the current service (pointed by
*   cyBle_disCount). If the current range is invalid (any of start or end
*   handles is invalid), then increment the cyBle_disCount and check
*   the next service range and does so until a valid range is caught or the end
*   of the service set is reached.
* 
*  \param incrementIndex: Not zero value indicates that characteristic index should be 
*                         sincremented.
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_NextCharDiscovery(uint8 incrementIndex)
{

    if(incrementIndex != CYBLE_DISCOVERY_INIT)
    {
        cyBle_disCount++;
    }
    else
    {
        cyBle_disCount = 0u;
        #ifdef CYBLE_HIDS_CLIENT
            disServiceIndex = 0u;
        #endif /* CYBLE_HIDS_CLIENT */
    }

    /* Skip not existing services */
    while((cyBle_disCount < (uint8) CYBLE_SRVI_COUNT) &&
          (cyBle_serverInfo[cyBle_disCount].range.startHandle == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE))
    {
        cyBle_disCount++;
    }

    if(cyBle_disCount < (uint8) CYBLE_SRVI_COUNT)
    {
        if(CYBLE_ERROR_OK != CyBle_GattcDiscoverAllCharacteristics(cyBle_connHandle, cyBle_serverInfo[cyBle_disCount].range))
        {
            CyBle_ApplCallback(CYBLE_EVT_GATTC_CHAR_DISCOVERY_FAILED, NULL);
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_AUTO_DISCOVERY;
        }
    }
    else /* Characteristic discovery procedure is done, start descriptor discovery procedure */
    {
    #if(CYBLE_STACK_MODE_DEBUG)
        CyBle_ApplCallback(CYBLE_EVT_GATTC_CHAR_DISCOVERY_COMPLETE, NULL);
    #endif /* CYBLE_STACK_MODE_DEBUG */
        CyBle_SetClientState(CYBLE_CLIENT_STATE_DESCR_DISCOVERING);
        CyBle_NextCharDscrDiscovery(CYBLE_DISCOVERY_INIT);
    }

}


/****************************************************************************** 
* Function Name: CyBle_GetCharRange
***************************************************************************//**
* 
*  Returns a possible range of the current characteristic descriptor
*  (which is pointed by curr. descr. index cyBle_disCount).
* 
* \return
*  CYBLE_GATT_ATTR_HANDLE_RANGE_T range:  the block of start and end handles.
* 
******************************************************************************/
static CYBLE_GATT_ATTR_HANDLE_RANGE_T CyBle_GetCharRange(void)
{
    CYBLE_GATT_ATTR_HANDLE_RANGE_T charRange = {CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE};
    if(cyBle_disCount == (uint8) CYBLE_SCDI_GATT_SERVICE_CHANGED)
    {
        /* One descriptor is available in GATT service */
        charRange.startHandle = cyBle_gattc.serviceChanged.valueHandle + 1u;
        charRange.endHandle = cyBle_serverInfo[CYBLE_SRVI_GATT].range.endHandle;
    }
#ifdef CYBLE_ANCS_CLIENT
    if((cyBle_disCount == (uint8) CYBLE_SCDI_ANCS_NS) || (cyBle_disCount == (uint8) CYBLE_SCDI_ANCS_DS))
    {
        CYBLE_ANCS_CHAR_INDEX_T charIdx;
        if(cyBle_disCount == (uint8) CYBLE_SCDI_ANCS_NS)
        {
            charIdx = CYBLE_ANCS_NS;
        }
        else
        {
            charIdx = CYBLE_ANCS_DS;
        }
        
        if(cyBle_ancsc.charInfo[charIdx].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle = cyBle_ancsc.charInfo[charIdx].valueHandle + 1u;
            charRange.endHandle = cyBle_ancsc.charInfo[charIdx].endHandle;
        }
    }
#endif /* CYBLE_ANCS_CLIENT */
#ifdef CYBLE_ANS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_ANS_SUPPORTED_NEW_ALERT_CAT) &&
        (cyBle_disCount <= (uint8) CYBLE_SCDI_ANS_ALERT_NTF_CONTROL_POINT))
    {
        charRange.startHandle = 
            cyBle_ansc.characteristics[cyBle_disCount - CYBLE_SCDI_ANS_SUPPORTED_NEW_ALERT_CAT].charInfo.valueHandle;
        charRange.endHandle = 
            cyBle_ansc.characteristics[cyBle_disCount - CYBLE_SCDI_ANS_SUPPORTED_NEW_ALERT_CAT].endHandle;
    }
#endif /* CYBLE_ANS_CLIENT */
#ifdef CYBLE_BAS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_BAS_LEVEL) && (cyBle_disCount <= (uint8) CYBLE_SCDI_BAS_LEVEL_END))
    {
        if(cyBle_basc[cyBle_disCount - CYBLE_SCDI_BAS_LEVEL].batteryLevel.valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle = cyBle_basc[cyBle_disCount - CYBLE_SCDI_BAS_LEVEL].
                                batteryLevel.valueHandle + 1u;
            charRange.endHandle = cyBle_serverInfo[CYBLE_SRVI_BAS + (cyBle_disCount - CYBLE_SCDI_BAS_LEVEL)].
                                range.endHandle;
        }
    }
#endif /* CYBLE_BAS_CLIENT */
#ifdef CYBLE_BCS_CLIENT
    if((cyBle_disCount == (uint8) CYBLE_SCDI_BCS_BODY_COMPOSITION_FEATURE) ||
        (cyBle_disCount == (uint8) CYBLE_SCDI_BCS_BODY_COMPOSITION_MEASUREMENT))
    {
        if(cyBle_bcsc.charInfo[cyBle_disCount - CYBLE_SCDI_BCS_BODY_COMPOSITION_FEATURE].valueHandle !=
            CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle =
                cyBle_bcsc.charInfo[cyBle_disCount - CYBLE_SCDI_BCS_BODY_COMPOSITION_FEATURE].valueHandle + 1u;
            charRange.endHandle =
                cyBle_bcsc.charInfo[cyBle_disCount - CYBLE_SCDI_BCS_BODY_COMPOSITION_FEATURE].endHandle;
        }
    }
#endif /* CYBLE_BCS_CLIENT */
#ifdef CYBLE_BLS_CLIENT
    if((cyBle_disCount == (uint8) CYBLE_SCDI_BLS_BPM) || (cyBle_disCount == (uint8) CYBLE_SCDI_BLS_ICP))
    {
        if(cyBle_blsc.charInfo[cyBle_disCount - CYBLE_SCDI_BLS_BPM].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle = cyBle_blsc.charInfo[cyBle_disCount - CYBLE_SCDI_BLS_BPM].valueHandle + 1u;
            charRange.endHandle = cyBle_blsc.charInfo[cyBle_disCount - CYBLE_SCDI_BLS_BPM].endHandle;
        }
    }
#endif /* CYBLE_BLS_CLIENT */
#ifdef CYBLE_BMS_CLIENT
    if(cyBle_disCount == (uint8) CYBLE_SCDI_BMS_BMCP)
    {
        if(cyBle_bmsc.charInfo[CYBLE_BMS_BMCP].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle = cyBle_bmsc.charInfo[CYBLE_BMS_BMCP].valueHandle + 1u;
            charRange.endHandle = cyBle_bmsc.charInfo[CYBLE_BMS_BMCP].endHandle;
        }
    }
#endif /* CYBLE_BMS_CLIENT */
#ifdef CYBLE_CGMS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_CGMS_CGMT) && (cyBle_disCount <= (uint8) CYBLE_SCDI_CGMS_SOCP))
    {
        uint8 charIdx = cyBle_disCount - CYBLE_SCDI_CGMS_CGMT;
        if(CYBLE_CGMS_CGMT < charIdx)
        {
            /* charIdx for RACP is 5 and for SOCP is 6 */
            charIdx += CYBLE_CGMS_RACP - 1u;
        }
        
        if(cyBle_cgmsc.charInfo[charIdx].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle = cyBle_cgmsc.charInfo[charIdx].valueHandle + 1u;
            charRange.endHandle = cyBle_cgmsc.charInfo[charIdx].endHandle;
        }
    }
#endif /* CYBLE_CGMS_CLIENT */
#ifdef CYBLE_CPS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_CPS_POWER_MEASURE) && (cyBle_disCount <= (uint8) CYBLE_SCDI_CPS_POWER_CP))
    {
        charRange.startHandle = cyBle_cpsc.charInfo[cyBle_disCount - CYBLE_SCDI_CPS_POWER_MEASURE].valueHandle + 1u;
        charRange.endHandle = cyBle_cpsc.charInfo[cyBle_disCount - CYBLE_SCDI_CPS_POWER_MEASURE].endHandle;
    }
#endif /* CYBLE_CPS_CLIENT */
#ifdef CYBLE_CSCS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_CSCS_CSC_MEASUREMENT) && 
       (cyBle_disCount <= (uint8) CYBLE_SCDI_CSCS_SC_CONTROL_POINT))
    {
        charRange.startHandle = 
            cyBle_cscsc.characteristics[cyBle_disCount - CYBLE_SCDI_CSCS_CSC_MEASUREMENT].charInfo.valueHandle + 1u;
        charRange.endHandle = cyBle_cscsc.characteristics[cyBle_disCount - CYBLE_SCDI_CSCS_CSC_MEASUREMENT].endHandle;
    }
#endif /* CYBLE_CSCS_CLIENT */
#ifdef CYBLE_CTS_CLIENT
    if(cyBle_disCount == (uint8) CYBLE_SCDI_CTS_CURRENT_TIME)
    {
        if(cyBle_ctsc.currTimeCharacteristics[CYBLE_CTS_CURRENT_TIME].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per service */
            charRange.startHandle = cyBle_ctsc.currTimeCharacteristics[CYBLE_CTS_CURRENT_TIME].valueHandle + 1u;
            charRange.endHandle = cyBle_serverInfo[CYBLE_SRVI_CTS].range.endHandle;
        }
    }
#endif /* CYBLE_CTS_CLIENT */
#ifdef CYBLE_ESS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_ESS_DESCRIPTOR_VALUE_CHANGED) && 
       (cyBle_disCount <= (uint8) CYBLE_SCDI_ESS_END_CHAR))
    {
        if(prevCharInstIndex != (cyBle_disCount - CYBLE_SCDI_ESS_DESCRIPTOR_VALUE_CHANGED))
        {
            /* Check if this the last characteristic instance */
            if((activeCharInstance + 1u) < cyBle_esscCharInstances[activeCharIndex])
            {
                /* The instance is not last so increment it */
                activeCharInstance += 1u; 
            }
            else
            {
                /* The instance is last so go to new characteristic */
                activeCharInstance = 0u;
                activeCharIndex += 1u;
            }
            prevCharInstIndex = (cyBle_disCount - CYBLE_SCDI_ESS_DESCRIPTOR_VALUE_CHANGED);
        }

        if(NULL != cyBle_essc.charInfoAddr[activeCharIndex].charInfoPtr)
        {
            if(activeCharInstance < cyBle_esscCharInstances[activeCharIndex])
            {
                charRange.startHandle =
                    cyBle_essc.charInfoAddr[activeCharIndex].charInfoPtr[activeCharInstance].valueHandle + 1u;
            
                charRange.endHandle =
                    cyBle_essc.charInfoAddr[activeCharIndex].charInfoPtr[activeCharInstance].endHandle;
            }
            else
            {
                charRange.startHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
                charRange.endHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
            }
        }
    }
#endif /* CYBLE_ESS_CLIENT */
#ifdef CYBLE_GLS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_GLS_GLMT) && (cyBle_disCount <= (uint8) CYBLE_SCDI_GLS_RACP))
    {
        uint8 charIdx = cyBle_disCount - CYBLE_SCDI_GLS_GLMT;
        if((CYBLE_SCDI_GLS_RACP - CYBLE_SCDI_GLS_GLMT) == charIdx)
        {
            charIdx = CYBLE_GLS_RACP;
        }
        
        if(cyBle_glsc.charInfo[charIdx].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle = cyBle_glsc.charInfo[charIdx].valueHandle + 1u;
            charRange.endHandle = cyBle_glsc.charInfo[charIdx].endHandle;
        }
    }
#endif /* CYBLE_GLS_CLIENT */
#ifdef CYBLE_HIDS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_HIDS_REPORT_MAP) && (cyBle_disCount <= (uint8) CYBLE_SCDI_HIDS_REPORT_END))
    {
        if(cyBle_disCount == (uint8) CYBLE_SCDI_HIDS_REPORT_MAP)
        {
            if(cyBle_hidsc[disServiceIndex].reportMap.valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
            {
                charRange.startHandle = cyBle_hidsc[disServiceIndex].reportMap.valueHandle + 1u;
                charRange.endHandle = cyBle_hidsc[disServiceIndex].reportMap.endHandle;
            }
        }
        else if(cyBle_disCount < (uint8) CYBLE_SCDI_HIDS_REPORT)
        {
            if(cyBle_hidsc[disServiceIndex].bootReport[cyBle_disCount -
                CYBLE_SCDI_HIDS_BOOT_KYBRD_IN_REP].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
            {
                charRange.startHandle = cyBle_hidsc[disServiceIndex].
                            bootReport[cyBle_disCount - CYBLE_SCDI_HIDS_BOOT_KYBRD_IN_REP].valueHandle + 1u;
                charRange.endHandle = cyBle_hidsc[disServiceIndex].
                            bootReport[cyBle_disCount - CYBLE_SCDI_HIDS_BOOT_KYBRD_IN_REP].endHandle;
            }
        }
        else
        {
            if(cyBle_hidsc[disServiceIndex].report[cyBle_disCount - CYBLE_SCDI_HIDS_REPORT].valueHandle !=
                CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
            {
                charRange.startHandle = cyBle_hidsc[disServiceIndex].
                            report[cyBle_disCount - CYBLE_SCDI_HIDS_REPORT].valueHandle + 1u;
                charRange.endHandle = cyBle_hidsc[disServiceIndex].
                            report[cyBle_disCount - CYBLE_SCDI_HIDS_REPORT].endHandle;
            }
        }

    }
#endif /* CYBLE_HIDS_CLIENT */
#ifdef CYBLE_HRS_CLIENT
    if(cyBle_disCount == (uint8) CYBLE_SCDI_HRS_HRM)
    {
        charRange.startHandle = cyBle_hrsc.charInfo[CYBLE_HRS_HRM].valueHandle + 1u;
        charRange.endHandle = cyBle_serverInfo[CYBLE_SRVI_HRS].range.endHandle;
    }
#endif /* CYBLE_HRS_CLIENT */
#ifdef CYBLE_HTS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_HTS_TEMP_MEASURE) && (cyBle_disCount <= (uint8) CYBLE_SCDI_HTS_MEASURE_INTERVAL))
    {
        charRange.startHandle = cyBle_htsc.charInfo[cyBle_disCount - CYBLE_SCDI_HTS_TEMP_MEASURE].valueHandle + 1u;
        charRange.endHandle = cyBle_htsc.charInfo[cyBle_disCount - CYBLE_SCDI_HTS_TEMP_MEASURE].endHandle;
    }
#endif /* CYBLE_HTS_CLIENT */
#ifdef CYBLE_LNS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_LNS_LS) && (cyBle_disCount <= (uint8) CYBLE_SCDI_LNS_NV))
    {
        uint8 charIdx = (cyBle_disCount - CYBLE_SCDI_LNS_LS) + 1u;
        if(charIdx > (uint8) CYBLE_SCDI_LNS_LS)
        {
            charIdx++;
        }
        charRange.startHandle = cyBle_lnsc.charInfo[charIdx].valueHandle + 1u;
        charRange.endHandle = cyBle_lnsc.charInfo[charIdx].endHandle;
    }
#endif /* CYBLE_LNS_CLIENT */
#ifdef CYBLE_PASS_CLIENT
    if((cyBle_disCount == (uint8) CYBLE_SCDI_PASS_AS) || (cyBle_disCount == (uint8) CYBLE_SCDI_PASS_RS))
    {
        charRange.startHandle = cyBle_passc.charInfo[cyBle_disCount - CYBLE_SCDI_PASS_AS].valueHandle + 1u;
        charRange.endHandle = cyBle_passc.charInfo[cyBle_disCount - CYBLE_SCDI_PASS_AS].endHandle;
    }
#endif /* CYBLE_PASS_CLIENT */
#ifdef CYBLE_RSCS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_RSCS_RSC_MEASUREMENT) && 
       (cyBle_disCount <= (uint8) CYBLE_SCDI_RSCS_SC_CONTROL_POINT))
    {
        charRange.startHandle = 
            cyBle_rscsc.characteristics[cyBle_disCount - CYBLE_SCDI_RSCS_RSC_MEASUREMENT].charInfo.valueHandle + 1u;
        charRange.endHandle = cyBle_rscsc.characteristics[cyBle_disCount - CYBLE_SCDI_RSCS_RSC_MEASUREMENT].endHandle;
    }
#endif /* CYBLE_RSCS_CLIENT */
#ifdef CYBLE_SCPS_CLIENT
    if(cyBle_disCount == (uint8) CYBLE_SCDI_SCPS_SCAN_REFRESH)
    {
        if(cyBle_scpsc.refreshChar.valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per characteristic */
            charRange.startHandle = cyBle_scpsc.refreshChar.valueHandle + 1u;
            charRange.endHandle = cyBle_serverInfo[CYBLE_SRVI_SCPS].range.endHandle;
        }
    }
#endif /* CYBLE_SCPS_CLIENT */
#ifdef CYBLE_TPS_CLIENT
    if(cyBle_disCount == (uint8) CYBLE_SCDI_TPS_TX_PWR_LEVEL)
    {
        if(cyBle_tpsc.txPowerLevelChar.valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            /* One descriptor is available per service */
            charRange.startHandle = cyBle_tpsc.txPowerLevelChar.valueHandle + 1u;
            charRange.endHandle = cyBle_serverInfo[CYBLE_SRVI_TPS].range.endHandle;
        }
    }
#endif /* CYBLE_TPS_CLIENT */
#ifdef CYBLE_UDS_CLIENT
    if((cyBle_disCount == (uint8) CYBLE_SCDI_UDS_DCI) || (cyBle_disCount == (uint8) CYBLE_SCDI_UDS_UCP))
    {
        uint8 charIdx;
        if(cyBle_disCount == (uint8)CYBLE_SCDI_UDS_DCI)
        {
            charIdx = (uint8)CYBLE_UDS_DCI;
        }
        else
        {
            charIdx = (uint8)CYBLE_UDS_UCP;
        }
        
        charRange.startHandle = cyBle_udsc.charInfo[charIdx].valueHandle + 1u;
        charRange.endHandle = cyBle_udsc.charInfo[charIdx].endHandle;
    }
#endif /* CYBLE_UDS_CLIENT */
#ifdef CYBLE_WPTS_CLIENT
    if((cyBle_disCount == (uint8) CYBLE_SCDI_WPTS_PRU_ALERT))
    {
        charRange.startHandle = cyBle_wptsc.charInfo[CYBLE_WPTS_PRU_ALERT].valueHandle + 1u;
        charRange.endHandle = cyBle_wptsc.charInfo[CYBLE_WPTS_PRU_ALERT].endHandle;
    }
#endif /* CYBLE_WPTS_CLIENT */
#ifdef CYBLE_WSS_CLIENT
    if((cyBle_disCount >= (uint8) CYBLE_SCDI_WSS_WEIGHT_SCALE_FEATURE) &&
       (cyBle_disCount <= (uint8) CYBLE_SCDI_WSS_WEIGHT_WEIGHT_MEASUREMENT))
    {
        charRange.startHandle = cyBle_wssc.charInfo[cyBle_disCount-CYBLE_SCDI_WSS_WEIGHT_SCALE_FEATURE].valueHandle + 1u;
        charRange.endHandle = cyBle_wssc.charInfo[cyBle_disCount-CYBLE_SCDI_WSS_WEIGHT_SCALE_FEATURE].endHandle;
    }
#endif /* CYBLE_WSS_CLIENT */

    return (charRange);
}


/****************************************************************************** 
* Function Name: CyBle_FindInfoEventHandler
***************************************************************************//**
*  Handles the Find Info Response Event during an automatic server discovery
*  process.
* 
*  \param eventParam:  the event parameters for a Find Info Response
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_FindInfoEventHandler(CYBLE_GATTC_FIND_INFO_RSP_PARAM_T *eventParam)
{
    uint16 dataLength;
    uint16 attrLength;
    uint16 i;
    uint8 *attrVal;

    /* Discovery descriptor information */
    CYBLE_DISC_DESCR_INFO_T discDescrInfo;
    discDescrInfo.descrHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;

    if((CYBLE_CLIENT_STATE_DESCR_DISCOVERING == CyBle_GetClientState()) 
            && ((cyBle_eventHandlerFlag & CYBLE_AUTO_DISCOVERY) != 0u))
    {
        attrLength = eventParam->handleValueList.byteCount;    /* Number of elements on list in bytes */
        discDescrInfo.uuidFormat = eventParam->uuidFormat;
        discDescrInfo.connHandle = eventParam->connHandle;

        if(discDescrInfo.uuidFormat == CYBLE_GATT_16_BIT_UUID_FORMAT)
        {
            dataLength = CYBLE_DB_ATTR_HANDLE_LEN + CYBLE_GATT_16_BIT_UUID_SIZE;
        }
        else
        {
            dataLength = CYBLE_DB_ATTR_HANDLE_LEN + CYBLE_GATT_128_BIT_UUID_SIZE;
        }
        attrVal = eventParam->handleValueList.list;

        for(i = 0u; i < attrLength; i += dataLength)
        {
            discDescrInfo.descrHandle = CyBle_Get16ByPtr(attrVal);
            attrVal += CYBLE_DB_ATTR_HANDLE_LEN;
            if(discDescrInfo.uuidFormat == CYBLE_GATT_128_BIT_UUID_FORMAT)
            {
                (void)memcpy(&discDescrInfo.uuid.uuid128, attrVal, CYBLE_GATT_128_BIT_UUID_SIZE);
                attrVal += CYBLE_GATT_128_BIT_UUID_SIZE;
                #ifdef CYBLE_CUSTOM_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_CUSTOM_CHARACTERISTICS)
                    {
                        CyBle_CustomcDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_CUSTOM_CLIENT */
            }
            else
            {
                discDescrInfo.uuid.uuid16 = CyBle_Get16ByPtr(attrVal);
                attrVal += CYBLE_GATT_16_BIT_UUID_SIZE;
                
                if(cyBle_disCount == (uint8) CYBLE_SCDI_GATT_SERVICE_CHANGED)
                {
                    CyBle_GattcDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                }
                
                
                #ifdef CYBLE_ANCS_CLIENT
                    if((cyBle_disCount == (uint8) CYBLE_SCDI_ANCS_NS) ||
                        (cyBle_disCount == (uint8) CYBLE_SCDI_ANCS_DS))
                    {
                        CyBle_AncscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_ANCS_CLIENT */
                
                #ifdef CYBLE_ANS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_ANS_SUPPORTED_NEW_ALERT_CAT) &&
                        (cyBle_disCount <= (uint8) CYBLE_SCDI_ANS_ALERT_NTF_CONTROL_POINT))
                    {
                        CyBle_AnscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_ANS_CLIENT */
                
                #ifdef CYBLE_BAS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_BAS_LEVEL) &&
                        (cyBle_disCount <= (uint8) CYBLE_SCDI_BAS_LEVEL_END))
                    {
                        CyBle_BascDiscoverCharDescriptorsEventHandler(cyBle_disCount - CYBLE_SCDI_BAS_LEVEL,
                                                                      &discDescrInfo);
                    }
                #endif /* CYBLE_BAS_CLIENT */
                
                #ifdef CYBLE_BCS_CLIENT
                    if((cyBle_disCount == (uint8) CYBLE_SCDI_BCS_BODY_COMPOSITION_FEATURE) ||
                        (cyBle_disCount == (uint8) CYBLE_SCDI_BCS_BODY_COMPOSITION_MEASUREMENT))
                    {
                        CyBle_BcscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_BCS_CLIENT */
                
                #ifdef CYBLE_BLS_CLIENT
                    if((cyBle_disCount == (uint8) CYBLE_SCDI_BLS_BPM) || (cyBle_disCount == (uint8) CYBLE_SCDI_BLS_ICP))
                    {
                        CyBle_BlscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_BLS_CLIENT */
                
                #ifdef CYBLE_BMS_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_BMS_BMCP)
                    {
                        CyBle_BmscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_BMS_CLIENT */
                
                #ifdef CYBLE_CGMS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_CGMS_CGMT) &&
                        (cyBle_disCount <= (uint8) CYBLE_SCDI_CGMS_SOCP))
                    {
                        CyBle_CgmscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_CGMS_CLIENT */

                #ifdef CYBLE_CPS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_CPS_POWER_MEASURE) &&
                        (cyBle_disCount <= (uint8)CYBLE_SCDI_CPS_POWER_CP))
                    {
                        uint8 charIdx = cyBle_disCount - CYBLE_SCDI_CPS_POWER_MEASURE;
                        CyBle_CpscDiscoverCharDescriptorsEventHandler((CYBLE_CPS_CHAR_INDEX_T)charIdx, &discDescrInfo);
                    }
                #endif /* CYBLE_CPS_CLIENT */

                #ifdef CYBLE_CSCS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_CSCS_CSC_MEASUREMENT) && 
                       (cyBle_disCount <= (uint8) CYBLE_SCDI_CSCS_SC_CONTROL_POINT))
                    {
                        if(cyBle_disCount == (uint8) CYBLE_SCDI_CSCS_CSC_MEASUREMENT)
                        {
                            /* The CCC descriptor of CSC Measurement is currently discovering */
                            CyBle_CscscDiscoverCharDescriptorsEventHandler(CYBLE_CSCS_CSC_MEASUREMENT, &discDescrInfo);
                        }
                        else if(cyBle_disCount == (uint8) CYBLE_SCDI_CSCS_SC_CONTROL_POINT)
                        {
                            /* The CCC descriptor of SC Control Point is currently discovering */
                            CyBle_CscscDiscoverCharDescriptorsEventHandler(CYBLE_CSCS_SC_CONTROL_POINT, &discDescrInfo);
                        }
                        else
                        {
                            /* No other descriptors are present for CSCS */
                        }
                    }
                #endif /* CYBLE_CSCS_CLIENT */
                
                #ifdef CYBLE_CTS_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_CTS_CURRENT_TIME)
                    {
                        CyBle_CtscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_CTS_CLIENT */

                #ifdef CYBLE_CUSTOM_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_CUSTOM_CHARACTERISTICS)
                    {
                        CyBle_CustomcDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_CUSTOM_CLIENT */
                
                #ifdef CYBLE_ESS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_ESS_DESCRIPTOR_VALUE_CHANGED) &&
                        (cyBle_disCount <= (uint8) CYBLE_SCDI_ESS_END_CHAR))
                    {
                        CyBle_EsscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_ESS_CLIENT */

                #ifdef CYBLE_GLS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_GLS_GLMT) &&
                        (cyBle_disCount <= (uint8) CYBLE_SCDI_GLS_RACP))
                    {
                        CyBle_GlscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_GLS_CLIENT */

                #ifdef CYBLE_HIDS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_HIDS_REPORT_MAP) &&
                        (cyBle_disCount <= (uint8) CYBLE_SCDI_HIDS_REPORT_END))
                    {
                        CyBle_HidscDiscoverCharDescriptorsEventHandler(disServiceIndex, cyBle_disCount, &discDescrInfo);
                    }
                #endif /* CYBLE_HIDS_CLIENT */

                #ifdef CYBLE_HRS_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_HRS_HRM)
                    {
                        CyBle_HrscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_HRS_CLIENT */

                #ifdef CYBLE_HTS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_HTS_TEMP_MEASURE) && 
                       (cyBle_disCount <= (uint8) CYBLE_SCDI_HTS_MEASURE_INTERVAL))
                    {
                        uint8 charIdx = cyBle_disCount - CYBLE_SCDI_HTS_TEMP_MEASURE;
                        CyBle_HtscDiscoverCharDescriptorsEventHandler((CYBLE_HTS_CHAR_INDEX_T)charIdx, &discDescrInfo);
                    }
                #endif /* CYBLE_HTS_CLIENT */
                
                #ifdef CYBLE_LNS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_LNS_LS) && 
                       (cyBle_disCount <= (uint8) CYBLE_SCDI_LNS_NV))
                    {
                        CyBle_LnscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_LNS_CLIENT */
                
                #ifdef CYBLE_PASS_CLIENT
                    if((cyBle_disCount == (uint8) CYBLE_SCDI_PASS_AS) || 
                        (cyBle_disCount == (uint8) CYBLE_SCDI_PASS_RS))
                    {
                        CyBle_PasscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_PASS_CLIENT */

                #ifdef CYBLE_RSCS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_RSCS_RSC_MEASUREMENT) && 
                       (cyBle_disCount <= (uint8) CYBLE_SCDI_RSCS_SC_CONTROL_POINT))
                    {
                        if(cyBle_disCount == (uint8) CYBLE_SCDI_RSCS_RSC_MEASUREMENT)
                        {
                            /* The CCC descriptor of RSC Measurement is currently discovering */
                            CyBle_RscscDiscoverCharDescriptorsEventHandler(CYBLE_RSCS_RSC_MEASUREMENT, &discDescrInfo);
                        }
                        else if(cyBle_disCount == (uint8) CYBLE_SCDI_RSCS_SC_CONTROL_POINT)
                        {
                            /* The CCC descriptor of SC Control Point is currently discovering */
                            CyBle_RscscDiscoverCharDescriptorsEventHandler(CYBLE_RSCS_SC_CONTROL_POINT, &discDescrInfo);
                        }
                        else
                        {
                            /* No other descriptors are present for RSCS */
                        }
                    }
                #endif /* CYBLE_RSCS_CLIENT */

                #ifdef CYBLE_SCPS_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_SCPS_SCAN_REFRESH)
                    {
                        CyBle_ScpscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_SCPS_CLIENT */
                
                #ifdef CYBLE_TPS_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_TPS_TX_PWR_LEVEL)
                    {
                        CyBle_TpscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_TPS_CLIENT */
                
                #ifdef CYBLE_UDS_CLIENT
                    if((cyBle_disCount == (uint8) CYBLE_SCDI_UDS_DCI) || 
                        (cyBle_disCount == (uint8) CYBLE_SCDI_UDS_UCP))
                    {
                        CyBle_UdscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_UDS_CLIENT */
                #ifdef CYBLE_WPTS_CLIENT
                    if(cyBle_disCount == (uint8) CYBLE_SCDI_WPTS_PRU_ALERT)
                    {
                        CyBle_WptscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_WPTS_CLIENT */
                #ifdef CYBLE_WSS_CLIENT
                    if((cyBle_disCount >= (uint8) CYBLE_SCDI_WSS_WEIGHT_SCALE_FEATURE) &&
                        (cyBle_disCount <= (uint8) CYBLE_SCDI_WSS_WEIGHT_WEIGHT_MEASUREMENT))
                    {
                        CyBle_WsscDiscoverCharDescriptorsEventHandler(&discDescrInfo);
                    }
                #endif /* CYBLE_WSS_CLIENT */
            }
        }
        /* The sub-procedure is complete when an Error Response is received and the
           Error Code is set to an Attribute Not Found or the Find Information Response has
           an Attribute Handle that is equal to the Ending Handle of the request. */
        if(discDescrInfo.descrHandle == cyBle_charEndHandle)
        {
            CyBle_NextCharDscrDiscovery(CYBLE_DISCOVERY_CONTINUE);
        }

        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
    }
}


/****************************************************************************** 
* Function Name: CyBle_NextCharDscrDiscovery
***************************************************************************//**
*  Looks for a handle range for the current descriptor (pointed by
*   cyBle_disCount). If the current range is invalid (any of start or end
*   handles is invalid), then increment the cyBle_disCount and check
*   the next descriptor range and does so until a valid range is caught or the 
*   end of the descriptor set is reached.
* 
*  \param incrementIndex: Not zero value indicates that characteristic index should be 
*                         incremented.
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_NextCharDscrDiscovery(uint8 incrementIndex)
{
    CYBLE_GATTC_FIND_INFO_REQ_T charRange;

    do
    {
    #ifdef CYBLE_CUSTOM_CLIENT
        /* Do not increment main index untill custom service is discovered */
        if(cyBle_disCount != CYBLE_SCDI_CUSTOM_CHARACTERISTICS)
    #endif /* CYBLE_CUSTOM_CLIENT */
        {
            if(incrementIndex != CYBLE_DISCOVERY_INIT)
            {
            #ifdef CYBLE_HIDS_CLIENT
                #if(CYBLE_HIDSC_SERVICE_COUNT > 1u)
                    if((cyBle_disCount == CYBLE_SCDI_HIDS_REPORT_END) && 
                       (disServiceIndex < (CYBLE_HIDSC_SERVICE_COUNT - 1u)))
                    {
                        disServiceIndex++;      /* Discover descriptors for next HID service */
                        /* Set characteristic index to first characteristic of HID service */
                        cyBle_disCount = CYBLE_SCDI_HIDS_REPORT_MAP;
                    }
                    else
                    {
                        cyBle_disCount++;
                    }
                #else
                    cyBle_disCount++;
                #endif /* CYBLE_HIDSC_SERVICE_COUNT > 1u) */
            #else
                cyBle_disCount++;
            #endif /* CYBLE_HIDS_CLIENT */
            #ifdef CYBLE_CUSTOM_CLIENT
                if(cyBle_disCount == CYBLE_SCDI_CUSTOM_CHARACTERISTICS)
                {   /* Start descriptors discovery for custom service */
                    incrementIndex = CYBLE_DISCOVERY_INIT;
                }
            #endif /* CYBLE_CUSTOM_CLIENT */
            }
            else    /* Increment index in following loop */
            {
                cyBle_disCount = 0u;
                incrementIndex = 1u;
            }
        }
    #ifdef CYBLE_CUSTOM_CLIENT
        if(cyBle_disCount == CYBLE_SCDI_CUSTOM_CHARACTERISTICS)
        {
            charRange = CyBle_CustomcGetCharRange(incrementIndex);
            incrementIndex = CYBLE_DISCOVERY_CONTINUE;
        }
        /* When custom service is done cyBle_disCount will be incremented */
        if(cyBle_disCount != CYBLE_SCDI_CUSTOM_CHARACTERISTICS)
    #endif /* CYBLE_CUSTOM_CLIENT */
        {
            charRange = CyBle_GetCharRange();
        }

    }while(((charRange.startHandle == (CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE + 1u)) || 
            (charRange.endHandle == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE) ||
            (charRange.startHandle > charRange.endHandle)) && (cyBle_disCount < (uint8) CYBLE_SCDI_COUNT));

    if(cyBle_disCount < (uint8) CYBLE_SCDI_COUNT)
    {
        if(CYBLE_ERROR_OK != CyBle_GattcDiscoverAllCharacteristicDescriptors(cyBle_connHandle, &charRange))
        {
            CyBle_ApplCallback(CYBLE_EVT_GATTC_DESCR_DISCOVERY_FAILED, NULL);
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_AUTO_DISCOVERY;
        }
        cyBle_charEndHandle = charRange.endHandle;
    }
    else /* Discovery done */
    {
        CyBle_SetClientState(CYBLE_CLIENT_STATE_DISCOVERED);
        CyBle_ApplCallback(CYBLE_EVT_GATTC_DISCOVERY_COMPLETE, NULL);
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_AUTO_DISCOVERY;
    }
}


/****************************************************************************** 
* Function Name: CyBle_ErrorResponseEventHandler
***************************************************************************//**
* 
*  Handles the Find Info Response Event during an automatic server discovery
*  process.
* 
*   \param eventParam:  the event parameters for an Error Response
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_ErrorResponseEventHandler(const CYBLE_GATTC_ERR_RSP_PARAM_T *eventParam)
{
    if(((cyBle_eventHandlerFlag & CYBLE_AUTO_DISCOVERY) != 0u) &&
        (eventParam->errorCode == CYBLE_GATT_ERR_ATTRIBUTE_NOT_FOUND))
    {
        switch(CyBle_GetClientState())
        {
        case CYBLE_CLIENT_STATE_SRVC_DISCOVERING:
        #if(CYBLE_STACK_MODE_DEBUG)
            CyBle_ApplCallback(CYBLE_EVT_GATTC_SRVC_DISCOVERY_COMPLETE, NULL);
        #endif /* CYBLE_STACK_MODE_DEBUG */            
            CyBle_SetClientState(CYBLE_CLIENT_STATE_INCL_DISCOVERING);
            CyBle_NextInclDiscovery(CYBLE_DISCOVERY_INIT);
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
            break;

        case CYBLE_CLIENT_STATE_INCL_DISCOVERING:
            CyBle_NextInclDiscovery(CYBLE_DISCOVERY_CONTINUE);
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
            break;

        case CYBLE_CLIENT_STATE_CHAR_DISCOVERING:
            CyBle_NextCharDiscovery(CYBLE_DISCOVERY_CONTINUE);
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
            break;

        case CYBLE_CLIENT_STATE_DESCR_DISCOVERING:
            CyBle_NextCharDscrDiscovery(CYBLE_DISCOVERY_CONTINUE);
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
            break;
            
        default:
            break;
        }
    }
    else
    {
        #ifdef CYBLE_ANCS_CLIENT
            CyBle_AncscErrorResponseEventHandler(eventParam);
        #endif /* CYBLE_ANCS_CLIENT */    
        #ifdef CYBLE_ANS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_AnscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_ANS_CLIENT */
        #ifdef CYBLE_BAS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_BascErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_BAS_CLIENT */
        #ifdef CYBLE_BLS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_BlscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_BLS_CLIENT */
        #ifdef CYBLE_BMS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_BmscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_BMS_CLIENT */
        #ifdef CYBLE_CGMS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_CgmscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_CGMS_CLIENT */
        #ifdef CYBLE_CPS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_CpscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_CPS_CLIENT */
        #ifdef CYBLE_CSCS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_CscscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_CSCS_CLIENT */
        #ifdef CYBLE_CTS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_CtscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_CTS_CLIENT */
        #ifdef CYBLE_DIS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_DiscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_DIS_CLIENT */
        #ifdef CYBLE_ESS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_EsscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_ESS_CLIENT */
        #ifdef CYBLE_GLS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_GlscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_GLS_CLIENT */
        #ifdef CYBLE_HIDS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_HidscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_HIDS_CLIENT */
        #ifdef CYBLE_HRS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_HrscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_HRS_CLIENT */
        #ifdef CYBLE_HTS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_HtscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_HTS_CLIENT */
        #ifdef CYBLE_RSCS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_RscscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_RSCS_CLIENT */
        #ifdef CYBLE_SCPS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_ScpscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_SCPS_CLIENT */
        #ifdef CYBLE_LLS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_LlscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_LLS_CLIENT */
        #ifdef CYBLE_LNS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_LnscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_LNS_CLIENT */
        #ifdef CYBLE_PASS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_PasscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_PASS_CLIENT */
        #ifdef CYBLE_TPS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_TpscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_TPS_CLIENT */
        #ifdef CYBLE_UDS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_UdscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_UDS_CLIENT */
        #ifdef CYBLE_WPTS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_WptscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_WPTS_CLIENT */
        #ifdef CYBLE_WSS_CLIENT
            if((cyBle_eventHandlerFlag & CYBLE_CALLBACK) != 0u)
            {
                CyBle_WsscErrorResponseEventHandler(eventParam);
            }
        #endif /* CYBLE_WSS_CLIENT */
    }
}

#endif /* CYBLE_GATT_ROLE_CLIENT */


/* [] END OF FILE */
