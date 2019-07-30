/***************************************************************************//**
* \file CyBle_Gap.h
* 
* \file CYBLE_StackGap.h
* \version 3.61
*
* \brief
*  This file contains the GAP APIs of the BLE Host Stack IP
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


#ifndef CYBLE_GAP_H_
#define CYBLE_GAP_H_


/***************************************
* Common stack includes
***************************************/

#include "ble_Stack.h"


/***************************************
* GAP Constants
***************************************/


/* BD Address type flag*/

/* Public Device Address */
#define CYBLE_GAP_ADDR_TYPE_PUBLIC              			0x00u
/* Random Device Address */
#define CYBLE_GAP_ADDR_TYPE_RANDOM              			0x01u
/* Controller generates Resolvable Private Address based on the local
  * IRK from resolving list. If resolving list contains no matching entry,
  * use public address. */
#define CYBLE_GAP_ADDR_TYPE_PUBLIC_RPA			            0x02u
/* Controller generates Resolvable Private Address based on the local
  * IRK from resolving list. If resolving list contains no matching entry,
  * use random address. */
#define CYBLE_GAP_ADDR_TYPE_RANDOM_RPA                      0x03u
    
/* Max data length size  */
#define CYBLE_GAP_MAX_ADV_DATA_LEN              31u

/* Max data length size  */
#define CYBLE_GAP_MAX_SCAN_RSP_DATA_LEN         31u

/* Security modes  */
#define CYBLE_GAP_SEC_MODE_1                    0x10u
#define CYBLE_GAP_SEC_MODE_2                    0x20u
#define CYBLE_GAP_SEC_MODE_MASK                 0xF0u

/* Pairing properties MASK for CYBLE_GAP_AUTH_INFO_T */

/*
 * MASK to set MITM in pairing properties for Secure connections.
 */
#define CYBLE_GAP_SMP_SC_PAIR_PROP_MITM_MASK    0x01u

/*
 * MASK to set key press in pairing properties for Secure connections.
 */
#define CYBLE_GAP_SMP_SC_PAIR_PROP_KP_MASK      0x02u

/*
 * MASK to set MITM in pairing properties for Secure connections.
 * Note: This is deprecated. Use CYBLE_GAP_SMP_SC_PAIR_PROP_MITM_MASK instead.
 */
#define SMP_SC_PAIR_PROP_MITM_MASK          CYBLE_GAP_SMP_SC_PAIR_PROP_MITM_MASK

/*
 * MASK to set keypress in pairing properties for Secure connections.
 * Note: This is deprecated. Use CYBLE_GAP_SMP_SC_PAIR_PROP_KP_MASK instead.
*/
#define SMP_SC_PAIR_PROP_KP_MASK            CYBLE_GAP_SMP_SC_PAIR_PROP_KP_MASK

/* Broadcaster and discoverable mode  */
#define CYBLE_GAPP_NONE_DISC_BROADCAST_MODE     0x00u
#define CYBLE_GAPP_LTD_DISC_MODE                0x01u
#define CYBLE_GAPP_GEN_DISC_MODE                0x02u

/* Limited Discoverable mode timeout max. */
#define CYBLE_GAPP_LTD_DISC_MODE_TIME_MAX       180u

/* Observation and discovery procedure */
#define CYBLE_GAPC_OBSER_PROCEDURE              0x00u
#define CYBLE_GAPC_LTD_DISC_PROCEDURE           0x01u
#define CYBLE_GAPC_GEN_DISC_PROCEDURE           0x02u

/* Type of discovery procedure use in CYBLE_GAPC_DISC_INFO_T*/
#define CYBLE_GAPC_PASSIVE_SCANNING				0x00u	
#define CYBLE_GAPC_ACTIVE_SCANNING				0x01u
#define CYBLE_GAPC_FILTER_DUP_DISABLE 			0x00u
#define CYBLE_GAPC_FILTER_DUP_ENABLE			0x01u

/* Scan filter policy */

/* Accept all advertisement packets except directed advertising packets not
  * addressed to this device 
  */
#define CYBLE_GAPC_ADV_ACCEPT_ALL_PKT 						0x00u

/* Accept only advertisement packets from devices where the advertiser’s address
  * is in the White list.  Directed advertising packets which are not addressed for
  * this device shall be ignored.
  */
#define CYBLE_GAPC_ADV_ACCEPT_WHITELIST_PKT 				0x01u

/* Accept all undirected advertisement packets, and directed advertising packets
  * where the initiator address is a resolvable private address, and directed advertising
  * packets addressed to this device.
  */
#define CYBLE_GAPC_ADV_ACCEPT_DIRECTED_RPA_PKT 				0x02u

/* Accept all advertisement packets from devices where the advertiser’s address
  * is in the White list, and directed advertising packets where the initiator address
  * is a resolvable private address, and directed advertising packets addressed
  * to this device.
  */
#define CYBLE_GAPC_ADV_ACCEPT_WHITELIST_DIRECTED_RPA_PKT 	0x03u
    
/* Advertising filter policy*/
#define CYBLE_GAPP_SCAN_ANY_CONN_ANY 			0x00u
#define CYBLE_GAPP_SCAN_WHITELIST_CONN_ANY 		0x01u
#define CYBLE_GAPP_SCAN_ANY_CONN_WHITELIST 		0x02u
#define CYBLE_GAPP_SCAN_CONN_WHITELIST_ONLY 	0x03u

/* Initiator filter policy*/
#define CYBLE_GAPC_CONN_ALL 					0x00u
#define CYBLE_GAPC_CONN_WHITELIST 				0x01u

/* Maximum number of Remote Devices */
#define CYBLE_GAP_MAX_BONDED_DEVICE             0x04u
#define CYBLE_GAP_SIZE_OF_WHITELIST		 		0x08u
#define CYBLE_GAP_SIZE_OF_RESOLVING_LIST        0x08u
/* This is kept for backward compatibility, will be obsolete in future */
#define CYBLE_MAX_WHITELIST_ENTRIES 			0x04u

/* Out Of Band (OOB) flag*/
#define CYBLE_GAP_OOB_ENABLE                    0x01u
#define CYBLE_GAP_OOB_DISABLE                   0x00u

#define CYBLE_GAP_SMP_LTK_SIZE                  0x10u 
#define CYBLE_GAP_SMP_IRK_SIZE                  0x10u
#define CYBLE_GAP_SMP_CSRK_SIZE                 0x10u
#define CYBLE_GAP_SMP_IDADDR_DATA_SIZE          0x07u

#define CYBLE_GAP_SMP_MID_INFO_SIZE             0x0Au

#define CYBLE_GAP_SMP_INIT_ENC_KEY_DIST         0x01u
#define CYBLE_GAP_SMP_INIT_IRK_KEY_DIST         0x02u
#define CYBLE_GAP_SMP_INIT_CSRK_KEY_DIST        0x04u

#define CYBLE_GAP_SMP_RESP_ENC_KEY_DIST         0x10u
#define CYBLE_GAP_SMP_RESP_IRK_KEY_DIST         0x20u
#define CYBLE_GAP_SMP_RESP_CSRK_KEY_DIST        0x40u

/** SMP P256 Public-Private Key Size */
#define CYBLE_GAP_SMP_P256_PUBLIC_KEY_SIZE      0x40u
#define CYBLE_GAP_SMP_P256_PRIVATE_KEY_SIZE     0x20u

/* Passkey Response */
#define CYBLE_GAP_REJECT_PASSKEY_REQ            0x00u
#define CYBLE_GAP_ACCEPT_PASSKEY_REQ            0x01u

/***************************************
* Bonding definitions
***************************************/

/* No Bonding support */
#define CYBLE_GAP_BONDING_NONE                          0x00u

/* Bonding support */
#define CYBLE_GAP_BONDING                               0x01u

/* Encryption key size   */
#define CYBLE_GAP_ENCRYP_KEY_MIN                        7u
#define CYBLE_GAP_ENCRYP_KEY_MAX                        16u

/* User Passkey size */
#define CYBLE_GAP_USER_PASSKEY_SIZE                     6u

#define CYBLE_GAP_RANDOM_PRIV_RESOLVABLE_ADDR_MASK      0x40u
#define CYBLE_GAP_RANDOM_PRIV_NON_RESOLVABLE_ADDR_MASK  0x00u
#define CYBLE_GAP_PUBLIC_ADDR_MASK                      0x80u
#define CYBLE_GAP_RANDOM_STATIC_ADDR_MASK               0xC0u

/* Key Size */
/** Identity Resolving Key size */
#define CYBLE_GAP_IRK_SIZE                              16u
    
/** Security Requirements */
#define CYBLE_GAP_NO_SECURITY_REQUIREMENTS              (0x00u)
#define CYBLE_GAP_SEC_UNAUTH_PAIRING                    (0x01u)
#define CYBLE_GAP_SEC_AUTH_PAIRING                      (0x02u)
#define CYBLE_GAP_SEC_SC_PAIRING_WITH_NO_MITM           (0x04u)
#define CYBLE_GAP_SEC_SC_PAIRING_WITH_MITM              (0x08u)
#define CYBLE_GAP_SEC_OOB_IN_LEGACY_PAIRING             (0x10u)
#define CYBLE_GAP_SEC_OOB_IN_SC_PAIRING                 (0x20u)
#define CYBLE_GAP_SEC_REQ_BIT_MASK                      (0x3Fu)

/***************************************
* Enumerated Types
***************************************/

/**
 \addtogroup group_common_api_gap_definitions
 @{
*/

/** Advertisement type  */
typedef enum
{
	/** Connectable undirected advertising */
	CYBLE_GAPP_CONNECTABLE_UNDIRECTED_ADV = 0x00u,

	/** Connectable high duty cycle directed advertising */
	CYBLE_GAPP_CONNECTABLE_HIGH_DC_DIRECTED_ADV,

	/** Scannable undirected advertising */
	CYBLE_GAPP_SCANNABLE_UNDIRECTED_ADV,

	/** Non connectable undirected advertising */
	CYBLE_GAPP_NON_CONNECTABLE_UNDIRECTED_ADV,

	/** Connectable low duty cycle directed advertising */
	CYBLE_GAPP_CONNECTABLE_LOW_DC_DIRECTED_ADV
	
}CYBLE_GAPP_ADV_T;

/** Advertisement event type  */
typedef enum
{
	/** Connectable undirected advertising */
	CYBLE_GAPC_CONN_UNDIRECTED_ADV = 0x00u,

	/** Connectable directed advertising */
	CYBLE_GAPC_CONN_DIRECTED_ADV,

	/** Scannable undirected advertising */
	CYBLE_GAPC_SCAN_UNDIRECTED_ADV,

	/** Non connectable undirected advertising */
	CYBLE_GAPC_NON_CONN_UNDIRECTED_ADV,

	/** Scan Response*/
	CYBLE_GAPC_SCAN_RSP
	
}CYBLE_GAPC_ADV_EVENT_T;
 
/** Security Levels  */
typedef enum
{
	/** Level 1
	    * Mode 1 - No Security (No Authentication & No Encryption)
	    * Mode 2 - N/A
	 */
	CYBLE_GAP_SEC_LEVEL_1 =	0x00u,
	
	/** Level 2
	    * Mode 1 - Unauthenticated pairing with encryption (No MITM)
	    * Mode 2 - Unauthenticated pairing with data signing (No MITM)
	 */
	CYBLE_GAP_SEC_LEVEL_2,
	
	/** Level 3
	    * Mode 1 - Authenticated pairing with encryption (With MITM)
	    * Mode 2 - Authenticated pairing with data signing (With MITM)
	 */
	CYBLE_GAP_SEC_LEVEL_3,
	
    /** Level 4
        * Secured Connection
	 */
	CYBLE_GAP_SEC_LEVEL_4,

    /** LE Security Level Mask */
	CYBLE_GAP_SEC_LEVEL_MASK =0x0Fu

}CYBLE_GAP_SEC_LEVEL_T;

/** IO capability  */
typedef enum
{
	/** Platform supports only a mechanism to display or convey only 6 digit number to user.*/
	CYBLE_GAP_IOCAP_DISPLAY_ONLY=0x00u, 
	
	/** The device has a mechanism whereby the user can indicate 'yes' or 'no'.*/	
	CYBLE_GAP_IOCAP_DISPLAY_YESNO, 
	
	/** Platform supports a numeric keyboard that can input the numbers '0' through '9' 
	    and a confirmation key(s) for  'yes' and 'no'. */
	CYBLE_GAP_IOCAP_KEYBOARD_ONLY,	

	/** Platform does not have the ability to display or communicate a 6 digit decimal number.*/
	CYBLE_GAP_IOCAP_NOINPUT_NOOUTPUT,	

	/** Platform supports a mechanism through which 6 digit numeric value can be displayed 
	    and numeric keyboard that can input the numbers '0' through '9'. */
	CYBLE_GAP_IOCAP_KEYBOARD_DISPLAY
	
} CYBLE_GAP_IOCAP_T;

/** Authentication Failed Error Codes */
typedef enum
{
	/** No Error */
	CYBLE_GAP_AUTH_ERROR_NONE  = 0x00u,

	/** User input of passkey failed, for example, the user cancelled the operation */
	CYBLE_GAP_AUTH_ERROR_PASSKEY_ENTRY_FAILED,

	/** Out Of Band data is not available, applicable if NFC is supported */
	CYBLE_GAP_AUTH_ERROR_OOB_DATA_NOT_AVAILABLE,

	/** Pairing procedure cannot be performed as authentication
       requirements cannot be met due to IO capabilities of one or both devices. */
	CYBLE_GAP_AUTH_ERROR_AUTHENTICATION_REQ_NOT_MET,

	/** Confirm value does not match the calculated compare value  */
	CYBLE_GAP_AUTH_ERROR_CONFIRM_VALUE_NOT_MATCH,

	/** Pairing is not supported by the device */
	CYBLE_GAP_AUTH_ERROR_PAIRING_NOT_SUPPORTED,

	/** Insufficient key size for the security requirements of this device 
	    or LTK is lost */
	CYBLE_GAP_AUTH_ERROR_INSUFFICIENT_ENCRYPTION_KEY_SIZE,

	/** command received is not supported */
	CYBLE_GAP_AUTH_ERROR_COMMAND_NOT_SUPPORTED,

	/** Pairing failed due to an unspecified reason */
	CYBLE_GAP_AUTH_ERROR_UNSPECIFIED_REASON,

	/** Pairing or authentication procedure is disallowed because too little time
 	   has elapsed since last pairing request or security request. */
	CYBLE_GAP_AUTH_ERROR_REPEATED_ATTEMPTS,

	/** Invalid Parameters in Request - Invalid Command length and Parameter value outside range */
	CYBLE_GAP_AUTH_ERROR_INVALID_PARAMETERS ,

	/** Indicates to the remote device that the DHKey Check value received doesn't
	   match the one calculated by the local device */
	CYBLE_GAP_AUTH_ERROR_DHKEY_CHECK_FAILED,
	
	/** Indicates that the confirm values in the numeric comparison protocol
	   do not match */
	CYBLE_GAP_AUTH_ERROR_NUMERIC_COMPARISON_FAILED,
	
	/** Indicates that the pairing over the LE transport failed due to a Pairing
	   Request sent over the BR/EDR transport is in process. */
	CYBLE_GAP_AUTH_ERROR_BR_EDR_PAIRING_IN_PROGRESS,
	
	/** Indicates that the BR/EDR Link Key generated on the BR/EDR transport cannot
	   be used to derive and distribute keys for LE transport */
	CYBLE_GAP_AUTH_ERROR_CROSS_TRANSPORT_KEY_GEN_DER_NOT_ALLOWED,

    /** Indicates that over the air, spec will not allow error code value to be greater than 0x0E*/
    CYBLE_GAP_AUTH_ERROR_CODE_SPEC_MAX_VALUE,

	/** Authentication process timeout, if pairing timeout happens for first time, 
	    application can choose to re-initiate the pairing procedure. If timeout occurs again, 
	    app may choose to disconnect peer device. */
	CYBLE_GAP_AUTH_ERROR_AUTHENTICATION_TIMEOUT = 0x15u,

	/** Link disconnected */
	CYBLE_GAP_AUTH_ERROR_LINK_DISCONNECTED = 0x18u
	
}CYBLE_GAP_AUTH_FAILED_REASON_T;

/** GAP address type */
typedef enum
{
    /** Random private non-resolvable address */
    CYBLE_GAP_RANDOM_PRIV_NON_RESOLVABLE_ADDR = 0x00u,
    
    /** Random private resolvable address */
    CYBLE_GAP_RANDOM_PRIV_RESOLVABLE_ADDR = 0x01u,
    
    /** Public address */
    CYBLE_GAP_PUBLIC_ADDR = 0x02u,
    
    /** Random static address */
    CYBLE_GAP_RANDOM_STATIC_ADDR = 0x03u
    
} CYBLE_GAP_ADDR_TYPE_T;

/** Passkey entry notification types.
    These are used for CyBle_GapAuthSendKeyPress() function
    as well as with CYBLE_EVT_GAP_KEYPRESS_NOTIFICATION event parameter.
 */
typedef enum
{
    /** Passkey entry started */
    CYBLE_GAP_PASSKEY_ENTRY_STARTED    = 0x00u,

    /** One digit entered */
    CYBLE_GAP_PASSKEY_DIGIT_ENTERED    = 0x01u,

    /** One digit erased */    
    CYBLE_GAP_PASSKEY_DIGIT_ERASED     = 0x02u,

    /** All digits cleared */
    CYBLE_GAP_PASSKEY_CLEARED          = 0x03u,

    /** Passkey entry completed */
    CYBLE_GAP_PASSKEY_ENTRY_COMPLETED  = 0x04u
} CYBLE_GAP_KEYPRESS_NOTIFY_TYPE;

/** GAP Direct advertiser address type */
typedef enum
{
    /** Public device address type */
    CYBLE_GAP_PUBLIC_ADDR_TYPE,

    /** Random private resolvable address type*/
    CYBLE_GAP_RANDOM_RESOLVABLE_ADDR_TYPE,
    
    /** Public Identity address type*/
    CYBLE_GAP_PUBLIC_IDENTITY_ADDR_TYPE,
    
    /** Random static Identity Address */
    CYBLE_GAP_RANDOM_IDENTITY_ADDR_TYPE
    
} CYBLE_GAP_ADV_ADDR_TYPE_T;

/** GAP physical layer */
typedef enum
{
    /** 1 - Mbps Physical Layer. */
    CYBLE_GAP_PHY_1MBPS = 0,

    /** Reserved Values. */
    CYBLE_GAP_PHY_INVALID
} CYBLE_GAP_PHY_TYPE_T;

/***************************************
* Exported structures and unions
***************************************/

/** Authentication Parameters Information  */
typedef struct 
{
	/** Security Mode setting will be as follows:
	    * (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_1)
	    * (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_2)
	    * (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_3)
	    * (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_4)
        * (CYBLE_GAP_SEC_MODE_2 | CYBLE_GAP_SEC_LEVEL_2)
	    * (CYBLE_GAP_SEC_MODE_2 | CYBLE_GAP_SEC_LEVEL_3)
	 */
    uint8    						    security;     

	/** Bonding type setting:
	     * CYBLE_GAP_BONDING_NONE
	     * CYBLE_GAP_BONDING
	 */
    uint8    						    bonding;      

	/** Encryption Key Size (octets)
	     * Minimum = 7 
	     * maximum = 16
         For slave initiated security request, this parameter needs to be ignored.
     */
	uint8    						    ekeySize;  

 	/** Parameter to say it authentication is accepted or rejected with reason.
	   accepted = CYBLE_GAP_AUTH_ERROR_NONE or error code CYBLE_GAP_AUTH_FAILED_REASON_T. */	
	CYBLE_GAP_AUTH_FAILED_REASON_T    	authErr;	    

   /**
    * Bit 0: MITM (Applicable only if Secure connections)
    *        Use SMP_SC_PAIR_PROP_MITM_MASK
    * Bit 1: Key press (sets Key press bit in authentication requirements flags of
    *        pairing request/response. Applicable only for secure connections)
    *        Use SMP_SC_PAIR_PROP_KP_MASK
    * Bit [2-7]: RFU
    */
    uint8                               pairingProperties;

} CYBLE_GAP_AUTH_INFO_T;


/** Bluetooth Bonded Device Address list */
typedef struct
{
	/** Number of bonded devices */
    uint8     				count;

	/** Pointer to list of Bluetooth device addresses of bonded devices, of type 
        'CYBLE_GAP_BD_ADDR_T'. 'CYBLE_GAP_MAX_BONDED_DEVICE' is a '#define' to
        be defined during build-time. */
    CYBLE_GAP_BD_ADDR_T     bdAddrList[CYBLE_GAP_MAX_BONDED_DEVICE];
	
}CYBLE_GAP_BONDED_DEV_ADDR_LIST_T;


/** Security Manager Key Distribution data */
typedef struct
{
    /** Long Term Key */
    uint8 ltkInfo[CYBLE_GAP_SMP_LTK_SIZE];

    /** Encrypted Diversifier and Random Number */
    uint8 midInfo[CYBLE_GAP_SMP_MID_INFO_SIZE];

    /** Identity Resolving Key */
    uint8 irkInfo[CYBLE_GAP_SMP_IRK_SIZE];

    /** Public device/Static Random address type
	 * idAddrInfo[0] - Address Type
     * idAddrInfo[1] to idAddrInfo[6] - Address
     */
    uint8 idAddrInfo[CYBLE_GAP_SMP_IDADDR_DATA_SIZE];

    /** Connection Signature Resolving Key */
    uint8 csrkInfo[CYBLE_GAP_SMP_CSRK_SIZE];

} CYBLE_GAP_SMP_KEY_DIST_T;

/** SMP P-256 public-private key pair */
typedef struct
{
    /** P-256 public key */
    uint8 publicKey[CYBLE_GAP_SMP_P256_PUBLIC_KEY_SIZE];
    
    /** P-256 private key */
    uint8 privateKey[CYBLE_GAP_SMP_P256_PRIVATE_KEY_SIZE];
    
} CYBLE_GAP_SMP_LOCAL_P256_KEYS;

/** Advertising parameters   */
typedef struct
{
	/** Minimum advertising interval for undirected 
	   and low duty cycle directed advertising.
	   	 - Time Range: 20 ms to 10.24 sec
	 */
	uint16     				advIntvMin; 

	/** Maximum advertising interval for undirected 
	   and low duty cycle directed advertising.
	   	- Time Range: 20 ms to 10.24 sec
	 */	
	uint16     				advIntvMax; 

	/** Type of advertisement
	   	- Connectable undirected advertising (0x00)
	   	- Connectable high duty cycle directed advertising (0x01)
	   	- Scannable undirected advertising (0x02)
	   	- Non connectable undirected advertising (0x03)
	   	- Connectable low duty cycle directed advertising (0x04)
	 */	
	CYBLE_GAPP_ADV_T      	advType;		

	/** Own BD Address Type											
		- CYBLE_GAP_ADDR_TYPE_PUBLIC
		- CYBLE_GAP_ADDR_TYPE_RANDOM
		- CYBLE_GAP_ADDR_TYPE_PUBLIC_RPA
		- CYBLE_GAP_ADDR_TYPE_RANDOM_RPA
     */	
	uint8      				ownAddrType;	

	/** Address type of the Bluetooth device address being used for 
	   directed advertising, not applicable otherwise
	   	- CYBLE_PUBLIC_DEV_ADDR (Public device address)
        - CYBLE_RANDOM_DEV_ADDR (Random device address)
	 */
	uint8      				directAddrType;	

	/** This parameter specifies Bluetooth device address of the 
	  	device to be connected while using directed advertising.
	  	In case of none direct advertising, parameter will be 0 
	 */	
	uint8     				directAddr[CYBLE_GAP_BD_ADDR_SIZE];		

	/** Advertising channels that shall be used when transmitting advertising packets. 
	   Channel map selection:
		- Enable channel 37 = bitmask. xxxxxxx1b
		- Enable channel 38 = bitmask. xxxxxx1xb
		- Enable channel 39 = bitmask. xxxxx1xxb 
	 */
	uint8      				advChannelMap;

	/** Advertising Filter Policy
	   	- CYBLE_GAPP_SCAN_ANY_CONN_ANY (Allow Scan Request from Any, Allow Connect Request
           from Any (Default))
	   	- CYBLE_GAPP_SCAN_WHITELIST_CONN_ANY (Allow Scan Request from White List Only, 
           Allow Connect Request)
	   	- CYBLE_GAPP_SCAN_ANY_CONN_WHITELIST (Allow Scan Request from Any, Allow Connect
           Request from White List Only)
	   	- CYBLE_GAPP_SCAN_CONN_WHITELIST_ONLY (Allow Scan Request from White List Only, 
           Allow Connect Request from White List Only)
	 */	
	uint8      				advFilterPolicy;
	
}CYBLE_GAPP_DISC_PARAM_T;

/** Advertising data   */
typedef struct
{
	/**GAP Advertisement Parameters which includes Flags, Service UUIDs and short name*/
	uint8      advData[CYBLE_GAP_MAX_ADV_DATA_LEN]; 

	/**length of the advertising data. This should be made zero if there is no data */
	uint8      advDataLen;	
	
} CYBLE_GAPP_DISC_DATA_T;

/** Scan response data   */
typedef struct
{
	/** Static user data transmitted in scan response. This should be made NULL if 
    there is no data. Maximum length of the data is equal to 31 bytes */
	uint8     scanRspData[CYBLE_GAP_MAX_SCAN_RSP_DATA_LEN];

	/** Length of the scan response data. This should be made zero if there is no data */
	uint8     scanRspDataLen; 	
	
} CYBLE_GAPP_SCAN_RSP_DATA_T;

/** Advertising information   */
typedef struct
{
	/** Broadcaster and discoverable mode 
	    - CYBLE_GAPP_NONE_DISC_BROADCAST_MODE
           (Applicable for Broadcaster or non-discoverable mode)
	    - CYBLE_GAPP_LTD_DISC_MODE (Limited discovery mode)
	    - CYBLE_GAPP_GEN_DISC_MODE (General discovery mode)
	 */
	uint8      						discMode;

	/** Advertisement parameters */
	CYBLE_GAPP_DISC_PARAM_T   		* advParam;
    /** Advertisement data */
	CYBLE_GAPP_DISC_DATA_T    		* advData;
    /** Scan Response data */
	CYBLE_GAPP_SCAN_RSP_DATA_T	 	* scanRspData;

	/** Advertisement timeout is in seconds. If timeout is set to 0,
        then there will not be any timeout. Parameter 'advTo' can 
        be used for all GAP timeouts related to peripheral operation.
        For General discoverable mode, this timer will be ignored.
        Application is expected to exit from discoverable mode
        explicitly by calling CyBle_GappExitDiscoveryMode() function.
        For Limited discoverable mode, 'advTo' should not exceed 180 Sec.
	 */
	uint16 							advTo; 
	
} CYBLE_GAPP_DISC_MODE_INFO_T;

/** Discovery information collected by Client  */
typedef struct
{
	/** Observation and discovery procedure.
	   	 - CYBLE_GAPC_OBSER_PROCEDURE (Observation procedure)
	   	 - CYBLE_GAPC_LTD_DISC_PROCEDURE (Limited discovery procedure)
	   	 - CYBLE_GAPC_GEN_DISC_PROCEDURE (General discovery procedure)
	 */
	uint8      discProcedure;

	/** Type of scan to perform
	   	 - CYBLE_GAPC_PASSIVE_SCANNING (Passive Scanning)
	   	 - CYBLE_GAPC_ACTIVE_SCANNING (Active scanning)
	 */
	uint8      scanType;			

	/** The time interval from when last LE scan is started until 
	   next subsequent LE scan.
		- Time Range: 2.5 ms to 10.24 sec. 
     */
	uint16     scanIntv;		

	/** The time duration of scanning to be performed 
		- Time Range: 2.5 ms to 10.24 sec										 
	 */
	uint16     scanWindow;			

	/** Own BD Address Type
		- CYBLE_GAP_ADDR_TYPE_PUBLIC
		- CYBLE_GAP_ADDR_TYPE_RANDOM
		- CYBLE_GAP_ADDR_TYPE_PUBLIC_RPA
		- CYBLE_GAP_ADDR_TYPE_RANDOM_RPA
	 */
	uint8      ownAddrType;		

	/** Filter policies to be applied during scanning procedure
		- CYBLE_GAPC_ADV_ACCEPT_ALL_PKT
		- CYBLE_GAPC_ADV_ACCEPT_WHITELIST_PKT
		- CYBLE_GAPC_ADV_ACCEPT_DIRECTED_RPA_PKT
		- CYBLE_GAPC_ADV_ACCEPT_WHITELIST_DIRECTED_RPA_PKT
	 */
	uint8      scanFilterPolicy;	

  	/** Scan timeout. Timeout is in seconds and none zero.
 	   If timeout is set as 0, then there will not be any timeout 
 	   scanTo can be used for all GAP timeouts related to Central operation.
	 */
	uint16 	   scanTo; 		

	/** Filter Duplicate Advertisement. The Filter Duplicates parameter controls whether
	   the Link Layer shall filter duplicate advertising reports to the Host, or if the
	   Link Layer should generate advertising reports for each packet received.
		- CYBLE_GAPC_FILTER_DUP_DISABLE (Duplicate filtering disabled)
		- CYBLE_GAPC_FILTER_DUP_ENABLE (Duplicate filtering enabled)

 	   By default, duplicate filtering is enabled
	 */
	uint8 	   filterDuplicates; 

} CYBLE_GAPC_DISC_INFO_T;

/** Connection parameters at the GAP Central end */
typedef struct
{
	/** The time interval from when last LE scan is started until next 
	   subsequent LE scan.
		- Time Range: 2.5 ms to 10.24 sec. 
     */
    uint16      scanIntv;                     	

	/** The time duration of scanning to be performed 
		- Time Range: 2.5 ms to 10.24 sec										 
	 */
	uint16      scanWindow;						

	/** Filter policies to be applied during connection procedure
		- CYBLE_GAPC_CONN_ALL (White list is not used to determine 
		which advertiser to connect. Peer address is used)
		- CYBLE_GAPC_CONN_WHITELIST (White list is used to determine
		which advertiser to connect to. Peer address shall be ignored)
	 */
	uint8       initiatorFilterPolicy;			

	/** Peer's bd address with whom connection to be established */
	uint8       peerBdAddr[CYBLE_GAP_BD_ADDR_SIZE];	

	/** Peer's bd address type 
		- CYBLE_GAP_ADDR_TYPE_PUBLIC
		- CYBLE_GAP_ADDR_TYPE_RANDOM
		- CYBLE_GAP_ADDR_TYPE_PUBLIC_RPA
		- CYBLE_GAP_ADDR_TYPE_RANDOM_RPA	
     */
	uint8       peerAddrType;						

	/** Own bd address type 
		- CYBLE_GAP_ADDR_TYPE_PUBLIC
		- CYBLE_GAP_ADDR_TYPE_RANDOM
		- CYBLE_GAP_ADDR_TYPE_PUBLIC_RPA
		- CYBLE_GAP_ADDR_TYPE_RANDOM_RPA
    */
	uint8       ownAddrType;						

	/** Minimum value for the connection event interval. This shall be less than
	   or equal to conn_Interval_Max. Minimum connection interval will be 
		 connIntvMin * 1.25 ms
        * Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMin;					

	/** Maximum value for the connection event interval. This shall be greater
	   than or equal to conn_Interval_Min. Maximum connection interval will be 
		 connIntvMax * 1.25 ms
	   	* Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMax;					

	/** Slave latency for the connection in number of connection events. 
	   	* Range: 0x0000 to 0x01F4 									 
	 */
    uint16      connLatency;						

	/** Supervision timeout for the LE Link. Supervision timeout will be  
	   supervisionTO * 10 ms
        * Time Range: 100 msec to 32 secs 									 
	 */
	uint16      supervisionTO;				

	/** Minimum length of connection needed for this LE connection.
	   	* Range: 0x0000 - 0xFFFF										 
	 */
	uint16      minCeLength;						

	/** Maximum length of connection needed for this LE connection.
	   	* Range: 0x0000 - 0xFFFF										 
	 */
    uint16      maxCeLength;						

}CYBLE_GAPC_CONN_PARAM_T;

/** Advertisement report received by GAP Central */
typedef struct
{
	/** Advertisement event type
	    - Connectable undirected advertising = 0x00
	    - Connectable directed advertising = 0x01
 	    - Scannable undirected advertising = 0x02
 	    - Non connectable undirected advertising = 0x03
 	    - Scan Response = 0x04
   	 */
	CYBLE_GAPC_ADV_EVENT_T		eventType;  

	/** bd address type of the device advertising.
		- CYBLE_GAP_ADDR_TYPE_PUBLIC
		- CYBLE_GAP_ADDR_TYPE_RANDOM
		- CYBLE_GAP_ADDR_TYPE_PUBLIC_RPA
		- CYBLE_GAP_ADDR_TYPE_RANDOM_RPA	
    */
    uint8  	    				peerAddrType;	

	/** Public Device Address or Random Device Address for
	   each device which responded to scanning. */
    uint8*	    				peerBdAddr;		

	/** length of the data for each device that responded to scanning */
    uint8       				dataLen;								

	/** Pointer to advertising or scan response data */
    uint8* 	    				data;				

	/** Rssi of the responding device.
				 * Range: -85 <= N <= 0
				 * Units: dBm */
    int8	    				rssi;	
	
} CYBLE_GAPC_ADV_REPORT_T;

/** Passkey display information */
typedef struct
{
	/** bd handle of the remote device */
    uint8	bdHandle; 

	/** size = 6, not null terminated */
    uint32 	passkey;  
	
}CYBLE_GAP_PASSKEY_DISP_INFO_T;

/** GAP Connection Update parameters  */
typedef struct
{
	/** Minimum value for the connection event interval. This shall be less than
	   or equal to conn_Interval_Max. Minimum connection interval will be 
		 connIntvMin * 1.25 ms
        * Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMin;					

	/** Maximum value for the connection event interval. This shall be greater
	   than or equal to conn_Interval_Min. Maximum connection interval will be 
		 connIntvMax * 1.25 ms
	   	* Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMax;					

	/** Slave latency for the connection in number of connection events. 
	 	* Range: 0x0000 to 0x01F3 									 
	 */
    uint16      connLatency;						

	/** Supervision timeout for the LE Link. Supervision timeout will be  
	   supervisionTO * 10 ms
	   	* Time Range: 100 msec to 32 secs 									 
	 */
	uint16      supervisionTO;								

}CYBLE_GAP_CONN_UPDATE_PARAM_T;

/** Current Connection Parameters used by controller */
typedef struct
{
	/** status corresponding to this event will be HCI error code 
    	as defined in BLE spec 4.1 or User can refer CYBLE_HCI_ERROR_T 
    	for HCI error codes
    */
    uint8      status;					

	/** Connection interval used on this connection. 
	  	* Range: 0x0006 to 0x0C80
	  	* Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntv;					

	/** Slave latency for the connection in number of connection events. 
	 	* Range: 0x0000 to 0x01F3 									 
	 */
    uint16      connLatency;						

	/** Supervision timeout for the LE Link. Supervision timeout will be  
	   supervisionTO * 10 ms
	   	* Time Range: 100 msec to 32 secs 									 
	 */
	uint16      supervisionTO;								

}CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T;

/** Structure containing OOB parameters */
typedef struct
{
    /** Status corresponding to this event will be HCI error code 
    		as defined in BLE spec 4.2 */
    uint8   status;

    /** Rand for OOB. This is also stored in stack */
    uint8   * key; 

    /** OOB Data using 'key' and local Public Key */
    uint8   * oobData; 

    /** Length of OOB data which is 16 Bytes for Secure connections */
    uint8   oobDataLen; 
    
}CYBLE_GAP_OOB_DATA_T;

/** Local suggested or Max 'tx octets' and 'tx time' */
typedef struct
{
    /** Controller's maximum transmitted number of payload 
     * octets to be used for new connections
     */
    uint16      suggestedTxOctets;

    /** Controller's maximum packet transmission time to be 
     * used for new connections 
     */
    uint16      suggestedTxTime;

    /** Maximum number of payload octets that the local Controller supports
     * for transmission of a single Link Layer Data Channel PDU.
     */
    uint16      maxTxOctets;

    /** Maximum time, in microseconds, that the local Controller supports for
     * transmission of a single Link Layer Data Channel PDU. 
     */
    uint16      maxTxTime;

    /** Maximum number of payload octets that the local Controller supports
     * for reception of a single Link Layer Data Channel PDU.
     */
    uint16      maxRxOctets;

    /** Maximum time, in microseconds, that the local Controller supports for
     * reception of a single Link Layer Data Channel PDU. 
     */
    uint16      maxRxTime; 

}CYBLE_GAP_DATA_LENGTH_T;

/** LE Data Length Change event parameter */
typedef struct
{
    /** The maximum number of payload octets in a Link Layer Data Channel
     * PDU that the local Controller will send on current connection.
     */
    uint16      connMaxTxOctets;

    /** The maximum time that the local Controller will take to send a Link
     * Layer Data Channel PDU on current connection 
     */
    uint16      connMaxTxTime;

    /** The maximum number of payload octets in a Link Layer Data Channel
     * PDU that the local controller expects to receive on current connection
     */
    uint16      connMaxRxOctets;

    /** The maximum time that the local Controller expects to take to receive a
     * Link Layer Data Channel PDU on this connection 
     */
    uint16      connMaxRxTime; 

}CYBLE_GAP_CONN_DATA_LENGTH_T;

/** LE Data Length RX parameters */
typedef struct
{
	/** Peer bdHandle */
	uint8 bdHandle;

	/** The maximum number of payload octets in a Link Layer Data Channel
     *  PDU that the local controller expects to receive on current connection
     */
	uint16 connMaxRxOctets;

	/** The maximum time that the local Controller expects to take to receive a
     *  Link Layer Data Channel PDU on this connection 
     */
	uint16 connMaxRxTime;
	
}CYBLE_GAP_RX_DATA_LENGTH_T;


/** Resolving list information of one device */
typedef struct
{
    /** Peer IRK */
    uint8       peerIrk[CYBLE_GAP_IRK_SIZE];

    /** Local IRK */
    uint8       localIrk[CYBLE_GAP_IRK_SIZE];

    /** Peer Identity device address  */
    uint8       bdAddr[CYBLE_GAP_BD_ADDR_SIZE];

    /** Peer Identity addr type */
    uint8       type; /*public = 0, Random = 1*/

}CYBLE_GAP_RESOLVING_DEVICE_INFO_T;

/** Resolving list that is stored in controller */
typedef struct
{
    /** Pointer to Resolving list stored in controller */
    CYBLE_GAP_RESOLVING_DEVICE_INFO_T   resolvingList[CYBLE_GAP_SIZE_OF_RESOLVING_LIST];

    /** Number of entries in resolving list */
    uint8                               noOfDevice;
}CYBLE_GAP_RESOLVING_LIST_T;

/** Direct Advertising Report received by GAP Central */
typedef struct
{
    /** Buffer containing Random Device Address of Scanner (local device)
     * This is the address the directed advertisements are
     * being directed to.
     */
    uint8                       * localBdAddr;

    /** Buffer containing Device Address of advertiser sending the directed advertisement */
    uint8                       * peerBdAddr;

    /** Device Address type of advertiser sending the directed advertisement */
    CYBLE_GAP_ADV_ADDR_TYPE_T   peerBdAddrType;


    /** Rssi of the responding device.
     * Range: -127 <= N <= +20
     * Units: dBm 
     * N = 127 -> RSSI not available
     */
    int8                        rssi;

} CYBLE_GAPC_DIRECT_ADV_REPORT_T;

/** Current Connection Parameters used by controller */
typedef struct
{
    /** Connection interval used on this connection.
     * Range: 0x0006 to 0x0C80
     * Time Range: 7.5 ms to 4 sec
     */
    uint16                      connIntv;

    /** Slave latency for the connection in number of connection events.
     * Range: 0x0000 to 0x01F3
     */
    uint16                      connLatency;

    /** Supervision timeout for the LE Link. Supervision timeout will be
     * supervisionTO * 10 ms
     * Time Range: 100 msec to 32 secs
     */
    uint16                  supervisionTo;

    /** Peer Device Address  */
    uint8                       * peerBdAddr;

    /** Peer Device Address type  */
    CYBLE_GAP_ADV_ADDR_TYPE_T   peerBdAddrType;

    /** Local Resolvable Private Address  
     * Resolvable Private Address being used by the local device
     * for this connection.
     * This is only valid when the Own_Address_Type in 
     * connection/advertisement parameters 
     * is set to 0x02 or 0x03. For other Own_Address_Type values,
     * This will be all zeros.
     */
    uint8                       * localResolvablePvtAddr;

    /** Peer Resolvable Private Address  
     * Resolvable Private Address being used by the peer device
     * for this connection.
     * This is only valid for the Peer_Address_Type
     * 0x02 or 0x03. For other Peer_Address_Type values,
     * This will be all zeros.
    */
    uint8                       * peerResolvablePvtAddr;

    /** Connection is master/slave
     * Master = 0x00
     * Slave = 0x01
     */
    uint8                       role;

    /** Master clock accuracy
     * 0x00 -> 500 ppm
     * 0x01 -> 250 ppm
     * 0x02 -> 150 ppm
     * 0x03 -> 100 ppm
     * 0x04 -> 75 ppm
     * 0x05 -> 50 ppm
     * 0x06 -> 30 ppm
     * 0x07 -> 20 ppm
     */
    uint8                       masterClockAccuracy;

    /** Status corresponding to this event will be HCI error code.
     * Values of 0 indicates connection successfully completed.
     * Refer BLE spec 4.2,Vol2, Part D for Error codes 
     * or User can refer CYBLE_HCI_ERROR_T for HCI error codes.
     */
    uint8                       status;

}CYBLE_GAP_ENHANCE_CONN_COMPLETE_T;

/** Bluetooth Bonded Device Address list */
typedef struct
{
    /** Bluetooth device address */
    CYBLE_GAP_BD_ADDR_T     bdAddr;

    /** Corresponding bdHandle */
    uint8                   bdHandle;

}CYBLE_GAP_DEVICE_LIST_T;

/** Bluetooth Bonded Device Address list */
typedef struct
{
    /** Pointer to list of Bluetooth device addresses and bdHandle of bonded devices */
    CYBLE_GAP_DEVICE_LIST_T         bdHandleAddrList[CYBLE_GAP_MAX_BONDED_DEVICE];

    /** Number of bonded devices */
    uint8                           count;

}CYBLE_GAP_DEVICE_ADDR_LIST_T;

/** Configuration Structure for Set Privacy Mode */
typedef struct
{
	 /** Bluetooth device address */
    uint8     peerBdAddr[CYBLE_GAP_BD_ADDR_SIZE]; 
	 
	/** public = 0, Random = 1 */
    uint8     peerBdAddrType; 
	
	/** Privacy Mode */
	uint8 privacyMode;

}CYBLE_GAP_PRIVACY_MODE_INFO_T;

/** @} */

/**
 \addtogroup group_common_api_gap_central_peripheral_functions
 @{
*/

/***************************************
* Exported APIs
***************************************/

/******************************************************************************
* Function Name: CyBle_GapSetIoCap
***************************************************************************//**
* 
*  This function sets the input and output capability of the BLE Device that is
*  used during authentication procedure. This is a blocking function. No event
*  is generated on calling this function. The input capabilities are described
*  in the following table:
*  <table>
*  <tr>
*    <th>Capability</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>No input</td>
*    <td>Device does not have the ability to indicate "yes" or "no"</td>
*  </tr>
*  <tr>
*    <td>Yes/No</td>
*    <td>Device has at least two buttons that can be easily mapped 
*        to "yes" and "no" or the device has a mechanism whereby 
*        the user can indicate either "yes" or "no".</td>
*  </tr>
*  <tr>
*    <td>Keyboard</td>
*    <td>Device has a numeric keyboard that can input the numbers
*        "0" through "9" and a confirmation. Device also has at 
*        least two buttons that can be easily mapped to "yes" and
*        "no" or the device has a mechanism whereby the user can
*        indicate either "yes" or "no".</td>
*  </tr>
*  </table>
* 
*  The output capabilities are described in the following table:

*   Capability       | Description
*   -----------      | -----------
*   No output        | Device does not have the ability to display or communicate a 6 digit decimal number.
*   Numeric output   | Device has the ability to display or communicate a 6 digit decimal number.
*  
*  Combined capability is defined in the following table:
*
*   Input Capability     | No Output          | Numeric Output
*   -----------          | -----------        | ------------
*   No input             | NoInputNoOutput    | DisplayOnly
*   Yes/No               | NoInputNoOutput    | DisplayYesNo
*   Keyboard             | KeyboardOnly       | KeyboardDisplay
*  
*  Refer Bluetooth 4.1 core specification, Volume 3, Part C, section 5.2.2.4 for
*  more details on the IO capabilities. IO capabilities of the BLE devices are
*  used to determine the pairing method. Please refer Bluetooth 4.1 core
*  specification, Volume 3, Part H, section 2.3.5.1 for more details on the
*  impact of IO capabilities on the pairing method chosen.
*     
* \param ioCap: IO Capability of type CYBLE_GAP_IOCAP_T. 
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying invalid input parameter
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetIoCap(CYBLE_GAP_IOCAP_T ioCap);

/******************************************************************************
* Function Name: CyBle_GapSetSecurityRequirements
***************************************************************************//**
*
*  This function is used to set the security requirements of local device and encryption
*  key size requirement of the local device. This is a blocking function. No event 
*  is generated on calling this function. It is expected to call this API function on host stack 
*  on, though can be called at any point except when any of SMP procedure is in progress. 
*  Security requirements are defined in the following table:
*  <table>
*  <tr>
*    <th>Security Requirement</th>
*  </tr>
*  <tr>
*    <td>CYBLE_GAP_NO_SECURITY_REQUIREMENTS</td>
*    <td>Default :security requirement specifies there are no security requirements</td>
*  </tr>
*  <tr>
*    <td>CYBLE_GAP_SEC_UNAUTH_PAIRING</td>
*    <td>Bit 0: Legacy pairing with NO MITM protection</td>
*  </tr>
*  <tr>
*    <td>CYBLE_GAP_SEC_AUTH_PAIRING</td>
*    <td>Bit 1: Legacy pairing with MITM protection</td>
*  </tr>
*  <tr>
*    <td>CYBLE_GAP_SEC_SC_PAIRING_WITH_NO_MITM</td>
*    <td>Bit 2: Secured Connection pairing with NO MITM protection</td>
*  </tr>
*  <tr>
*    <td>CYBLE_GAP_SEC_SC_PAIRING_WITH_MITM</td>
*    <td>Bit 3: Secured Connection pairing with MITM protection</td>
*  </tr>
*  <tr>
*    <td>CYBLE_GAP_SEC_OOB_IN_LEGACY_PAIRING</td>
*    <td>Bit 4: Legacy pairing with OOB method</td>
*  </tr>
*  <tr>
*    <td>CYBLE_GAP_SEC_OOB_IN_SC_PAIRING</td>
*    <td>Bit 5: Secured Connection pairing with OOB method
*  </tr>
*  </table>
*
*  After this API function is called, BLE Stack will check whether the received 
*  security request or pairing request or pairing response satisfies local 
*  device security requirements that are set using this API function. If local device
*  security requirements are not met then pairing is rejected by the BLE stack.
*
*  Eg: CyBle_GapSetSecurityRequirements() is called with secReq as CYBLE_GAP_SEC_SC_PAIRING_WITH_MITM.
*  Now if BLE Stack receives any pairing request with SC bit and MITM bit are not set, 
*  then that pairing request will be rejected by the stack.
*
*  Note: If the secured connection only mode is set, then these security requirements are not 
*  considered during pairing procedure. This is to maintain BWC for SC Only mode.
*
*  \param secReq: Security requirement is a bit-field parameter. Application can
*     set this value with the above defined values in the table. Application can set 
*     multiple security requirements by ORing them in this parameter.
*     Eg: If secReq is (CYBLE_GAP_SEC_UNAUTH_PAIRING | CYBLE_GAP_SEC_SC_PAIRING_WITH_NO_MITM),
*     then stack allows pairing only if received pairing request is either Legacy 
*     pairing with NO MITM or Secured Connection pairing with NO MITM.
*
* \param encKeySize: Encryption key size requirement of the local device. 
*     This parameter does not affect anything on central side. At peripheral side,
*     when encryption key size is set using this API function, then after during pairing if 
*     negotiated key size is less than the key size set by this API function, then BLE Stack will 
*     reject that pairing request.
*
* 	
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying invalid input parameter
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetSecurityRequirements
					(
						uint8 secReq,
						uint8 encKeySize
					);

/******************************************************************************
* Function Name: CyBle_GapSetOobData
***************************************************************************//**
* 
*  This function sets OOB presence flag and data. This function should be used 
*  by the application layer if it wants to enable OOB bonding procedure for any
*  specific device identified by "bdHandle". This function should be called
*  before initiating authentication or before responding to authentication
*  request to set OOB flag and data. For more details on OOB, please refer
*  Bluetooth 4.1 core specification, Volume 1, Part A, section 5.2.4.3. This is
*  a blocking function. No event is generated on calling this function.
*     
*  \param bdHandle: Peer device for which the Out Of Band signaling (OOB) configuration
*             is to be used.
*  \param oobFlag: OOB data presence flag. Allowed value are,
*            * CYBLE_GAP_OOB_DISABLE
*            * CYBLE_GAP_OOB_ENABLE
*  \param key: 16 Octet Temporary Key, to be used for OOB authentication.
*  \param oobData: Pointer to OOB data. In case of Legacy Pairing this parameter is not 
*                  used for OOB authentication.
*  \param oobDataLen: Pointer to a variable to store OOB data length.
* 		
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter
*   CYBLE_ERROR_NO_DEVICE_ENTITY     | 'bdHandle' does not represent known device entity
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetOobData 
					(
					   uint8 	bdHandle,
					   uint8	oobFlag,
					   uint8	* key,
					   uint8	* oobData,
					   uint8	* oobDataLen
					);


/******************************************************************************
* Function Name: CyBle_GapGetPeerBdAddr
***************************************************************************//**
* 
*  This function reads the peer Bluetooth device address which has already been
*  fetched by the BLE Stack. 'peerBdAddr' stores the peer's Bluetooth device
*  address identified with 'bdHandle'. This is a blocking function. No event is
*  generated on calling this function.
*     
*  \param bdHandle: Peer device handle.
*  \param peerBdAddr: Empty buffer where the Bluetooth device address gets stored.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter for 'peerBdAddr'.
*   CYBLE_ERROR_NO_DEVICE_ENTITY     | Specified device handle does not map to any device handle entry in BLE stack.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerBdAddr(uint8 bdHandle, CYBLE_GAP_BD_ADDR_T* peerBdAddr);


/******************************************************************************
* Function Name: CyBle_GapGetPeerBdHandle
***************************************************************************//**
* 
*  This function reads the device handle of the remote Bluetooth device using 
*  'peerBdAddr', which has already been fetched by the BLE Stack. 'bdHandle'
*  stores the peer device handle. This is a blocking function. No event is
*  generated on calling this function.
*     
*  \param bdHandle: Pointer to a variable to store peer device handle
*  \param peerBdAddr: Pointer to Bluetooth device address of peer device of type
*               CYBLE_GAP_BD_ADDR_T, to be provided to this function as an input
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                         | Description
*   ------------                         | ----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On specifying NULL as input parameter for 'peerBdAddr' or 'bdHandle'.
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed.
*   CYBLE_ERROR_NO_DEVICE_ENTITY         | Specified device handle does not map to any device handle entry in BLE stack.
* 			
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerBdHandle(uint8* bdHandle, CYBLE_GAP_BD_ADDR_T*   peerBdAddr);


/******************************************************************************
* Function Name: CyBle_GapGetPeerDevSecurity
***************************************************************************//**
* 
*  This function enables the application to get the device security of the peer
*  device, which has already been fetched by the BLE Stack, identified using 
*  'bdHandle' when the peer device is in the trusted list. This is a blocking
*  function. No event is generated on calling this function.
* 
*  \param bdHandle: Peer device handle
*  \param security: Pointer to a buffer into which security information will be written. 
*  		security level of the peer device is provided in CYBLE_GAP_AUTH_INFO_T->security.
*  		It ignores LE Security mode. Security should be interpreted as MITM and no MITM as
*  		encryption is always supported if pairing is performed between two devices.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On specifying NULL as input parameter for 'security'.
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed.
*   CYBLE_ERROR_NO_DEVICE_ENTITY         | Specified device handle does not map to any device handle entry in BLE stack.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerDevSecurity (uint8 bdHandle, CYBLE_GAP_AUTH_INFO_T* security);

/** @} */

/**
 \addtogroup group_common_api_gap_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GappEnterDiscoveryMode
***************************************************************************//**
* 
*  This function sets the device into discoverable mode. In the discoverable
*  mode, based on the parameters passed to this function, the BLE Device starts
*  advertisement and can respond to scan requests. This is a non-blocking 
*  function. It is to be used by the device in 'GAP Peripheral' mode of operation
*  to set parameters essential for starting advertisement procedure.
* 
*  On start of advertisement, the GAP Peripheral receives 
*  CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP event. The following events can
*  occur on invoking this function.
* 
*  * CYBLE_EVT_GAP_DEVICE_CONNECTED - If the device connects to a GAP Central and 
*    Link Layer Privacy is disabled in component customizer.
*    CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE - If the device connects to a GAP Central and 
*    Link Layer Privacy is enabled in component customizer.
* 
*  * CYBLE_EVT_TIMEOUT - If no device in 'GAP Central' mode connects to this 
*     device within the specified timeout limit. This event can occur if
*     'advInfo ->discMode' is equal to CYBLE_GAPP_LTD_DISC_MODE or
*     CYBLE_GAPP_GEN_DISC_MODE. 'advInfo-> advTo' specifies the timeout duration.
*     Set the 'advInfo-> advTo' to 0 when 'advInfo -> discMode' is set to
*     CYBLE_GAPP_GEN_DISC_MODE so that the timeout event does not occur and the
*     advertisement continues until the CyBle_GappExitDiscoveryMode() function
*     is invoked.
* 
*  \param advInfo: Structure of type CYBLE_GAPP_DISC_MODE_INFO_T, which contains the
*            advertisement parameters
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>On specifying null pointer for 'advInfo' or if any of the elements of this structure have invalid values.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GappEnterDiscoveryMode (CYBLE_GAPP_DISC_MODE_INFO_T* advInfo);


/******************************************************************************
* Function Name: CyBle_GappExitDiscoveryMode
***************************************************************************//**
* 
*  This function is used to exit from discoverable mode. This is a non-blocking
*  function. After the execution of this function, the device stops advertising.
* 
*  On stopping advertising, GAP Peripheral receives 
*  CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP event. It is expected that the
*  application layer keeps track of the function call performed before occurrence
*  of this event, as this event can occur on making a call to the
*  CyBle_GappEnterDiscoveryMode () function as well.
* 
******************************************************************************/
void CyBle_GappExitDiscoveryMode (void);

/** @} */

/**
 \addtogroup group_common_api_gap_central_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapcStartDiscovery
***************************************************************************//**
* 
*  This function starts the discovery of devices which are advertising. This is a 
*  non-blocking function. As soon as the discovery operation starts, 
*  CYBLE_EVT_GAPC_SCAN_START_STOP event is generated.
* 
*  Every Advertisement / Scan response packet received results in a new event,
*  CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT. If 'scanInfo->scanTo' is a non-zero value,
*  upon commencement of discovery procedure and elapsed time = 'scanInfo->scanTo',
*  CYBLE_EVT_TIMEOUT event is generated with the event parameter indicating 
*  CYBLE_GAP_SCAN_TO.
* 
*  If 'scanInfo->scanTo' is equal to zero, the scanning operation is performed
*  until the CyBle_GapcStopDiscovery() function is invoked.
*  
*  There are three discovery procedures that can be specified as a parameter to
*  this function.
* 
*  __Observation procedure__

*   A device performing the observer role receives only advertisement data from
*   devices irrespective of their discoverable mode settings. Advertisement data
*   received is provided by the event,
*   
*   CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT 
*   
*   'scanInfo->scanType' should be set as passive scanning (0x00).
*     
*  __Limited Discovery procedure__

*   A device performing the limited discovery procedure receives advertisement
*   data and scan response data from devices in the limited discoverable mode only.
*   Received data is provided by the event,
*   
*   CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT 
*   
*   'scanInfo->scanType' should be set as active scanning (0x01).
* 
*  __General Discovery procedure__

*   A device performing the general discovery procedure receives the advertisement
*   data and scan response data from devices in both limited discoverable mode and
*   the general discoverable mode. Received data is provided by the event,
* 
*   CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT 
*   
*   'scanInfo->scanType' should be set as active scanning (0x01).
* 
* 	\param scanInfo:  Pointer to a variable of type CYBLE_GAPC_DISC_INFO_T
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>On specifying NULL as input parameter for 'scanInfo' or if any element within '
*        scanInfo' has an invalid value.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcStartDiscovery(CYBLE_GAPC_DISC_INFO_T* scanInfo);


/******************************************************************************
* Function Name: CyBle_GapcStopDiscovery
***************************************************************************//**
* 
*  This function stops the discovery of devices. This is a non-blocking function.
*  On stopping discovery operation, CYBLE_EVT_GAPC_SCAN_START_STOP event is
*  generated. Application layer needs to keep track of the function call made
*  before receiving this event to associate this event with either the start or
*  stop discovery function.
* 			
*
*
*
******************************************************************************/
void CyBle_GapcStopDiscovery(void);


/******************************************************************************
* Function Name: CyBle_GapcInitConnection
***************************************************************************//**
* 
*  This function instructs BLE Stack to initiate connection request to the 
*  remote device with required connection parameters. Connection request from
*  application is acknowledged by BLE Controller as 
*  'CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE' or 'CYBLE_EVT_GAP_DEVICE_CONNECTED'
*  depend on Link Layer Privacy is enabled or not in component customizer. That
*  means, request is correct, permitted and  all parameters as part of the 
*  request are correct. If the parameter validation or request is not permitted, 
*  then BLE controller throws 'CYBLE_EVT_HCI_STATUS' event with error code
*  instead of CYBLE_EVT_GAP_DEVICE_CONNECTEDCYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE.
*  For positive condition, controller can issue connect request to peer. Once
*  connection is done, no more event is required but if fails to establish
*  connection, 'CYBLE_EVT_GAP_DEVICE_DISCONNECTED' is passed to application.
* 
*  This is a non-blocking function. This function needs to be called after
*  successfully stopping scanning. Scanning is successfully stopped on invoking
*  the CyBle_GapcStopDiscovery() function and receiving the event
*  CYBLE_EVT_GAPC_SCAN_START_STOP with the event data of '0x01',
*  indicating success.
* 
*  For details related to connection modes and procedures, refer to Bluetooth
*  4.1 Core Specification, Volume 3, Part C, Section 9.3.
*     
*  \param connParam: Structure of type 'CYBLE_GAPC_CONN_PARAM_T' which contains the
*              connection parameters.\n 
*             <b>Note</b> Any parameter of structure type CYBLE_GAPC_CONN_PARAM_T,
*             if not required by a specific Bluetooth Low Energy profile, may
*             be ignored.
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>On specifying NULL as input parameter for 'connParam' or if any element within 
*        'connParam' has an invalid value.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>Device already connected.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcInitConnection(CYBLE_GAPC_CONN_PARAM_T* connParam);


/******************************************************************************
* Function Name: CyBle_GapcCancelConnection
***************************************************************************//**
* 
* Description:
*  This function cancels a previously initiated connection with the peer device.
*  This is a blocking function. No event is generated on calling this function.
* 
*  If the devices are already connected, then this function should not be used.
*  To disconnect from an existing connection, use the function 
*  CyBle_GapDisconnect().
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                             | Description
*   ------------                             | -----------
*   CYBLE_ERROR_OK                           | On successful operation.
*   CYBLE_ERROR_INVALID_OPERATION            | Device already connected.
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED     | Memory allocation failed.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcCancelConnection(void);

/** @} */

/**
 \addtogroup group_common_api_gap_central_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapDisconnect
***************************************************************************//**
* 
*  This function disconnects the peer device. It is to be used by the device in
*  GAP Central mode and may be used by a GAP Peripheral device to send a
*  disconnect request. This is a non-blocking function. On disconnection, the
*  following events are generated, in order.
*  * CYBLE_EVT_GATT_DISCONNECT_IND
*  * CYBLE_EVT_GAP_DEVICE_DISCONNECTED
*     
*  \param bdHandle:  Peer device handle
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>No device to be disconnected. The specified device handle does not map 
*        to any device entry in the BLE Stack.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapDisconnect(uint8 bdHandle);

/******************************************************************************
* Function Name: CyBle_GapDisconnectWithReason
***************************************************************************//**
* 
*  This function allows to disconnect the peer device with reason code. It is to be used by the device in
*  GAP Central mode and may be used by a GAP Peripheral device to send a
*  disconnect request. This is a non-blocking function. 
*  On disconnection, the
*  following events are generated, in order.
*  * CYBLE_EVT_GATT_DISCONNECT_IND
*  * CYBLE_EVT_GAP_DEVICE_DISCONNECTED
*
*  Note: If the reason code is not valid, then by default reason code sent is 0x13
*     
*  \param bdHandle:  Peer device handle
*  \param reason: Reason for the disconnect. Refer Volume 2, Part E, section 7.1.6 for the reason codes.
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>No device to be disconnected. The specified device handle does not map 
*        to any device entry in the BLE Stack.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapDisconnectWithReason (uint8 bdHandle, uint8 reason);

/** @} */

/**
 \addtogroup group_common_api_gap_central_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapcResolveDevice
***************************************************************************//**
* 
*  This function enables the application to start resolution procedure for a
*  device that is connected using resolvable private address. This is a blocking function. 
*  Application should use this function when in GAP Central mode.
* 
*  Refer to Bluetooth 4.1 Core specification, Volume 3, Part C, section 10.8.2.3
*  Resolvable Private Address Resolution Procedure to understand the usage of 
*  Private addresses.
* 
*  \param bdAddr: Pointer to peer Bluetooth device address of length 6 bytes, not
*           NULL terminated.
*  \param irk: Pointer to 128-bit IRK to be used for resolving the peer's private
*        resolvable address.
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>&nbsp;On specifying NULL as input parameter for 'bdAddr' or 'irk'.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>No device to be resolved. The specified device handle does not map to any device entry in the BLE Stack.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcResolveDevice(const uint8 *bdAddr, const uint8 *irk);

/** @} */

/**
 \addtogroup group_common_api_gap_central_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapGetPeerDevSecurityKeyInfo
***************************************************************************//**
* 
*  This function enables the application to know the keys shared by a given peer 
*  device upon completion of the security sequence (already fetched by the BLE
*  Stack). The keys are shared by the peer device on initiation of authentication
*  which is performed using the CyBle_GapAuthReq() or CyBle_GappAuthReqReply()
*  function.
* 
*  This is a blocking function. No event is generated on calling this function.
*     
*  \param bdHandle: Peer device handle.
*  \param keysFlag: Indicates the keys to be retrieved from peer device. The following
*              bit fields indicate the presence or absence of the keys distributed.\n              
*              <b>Negotiated Local/Peer Key distribution</b>
*               * Bit 0. Encryption information (LTK and MID Information)
*               * Bit 1. Identity information
*               * Bit 2. Signature Key
*               * Bit 3-7. Reserved
*  \param keyInfo: Pointer to variable of type CYBLE_GAP_SMP_KEY_DIST_T to copy the
*                  stored keys of the peer device identified by 'bdHandle'
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter for 'keyInfo'.
*   CYBLE_ERROR_INVALID_OPERATION	 | An error occurred in BLE stack.
*   CYBLE_ERROR_NO_DEVICE_ENTITY     | Device identified using 'bdHandle' does not exist.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerDevSecurityKeyInfo
                (
                    uint8 bdHandle,
                    uint8 *keysFlag,
                    CYBLE_GAP_SMP_KEY_DIST_T *keyInfo
                );


/******************************************************************************
* Function Name: CyBle_GapGenerateDeviceAddress
***************************************************************************//**
* 
*  This function generates either public or random address based on 'type' field
*  of CYBLE_GAP_BD_ADDR_T structure. It uses BLE Controller's random number
*  generator to generate the random part of the Bluetooth device address.
* 
*  The parameter 'addrType' specifies further sub-classification within the
*  public and random address types.
*  
*  This is a blocking function. No event is generated on calling this function.
* 
*  \param bdAddr: Bluetooth device address is generated and populated in the structure
*           pointed to by this pointer. The structure is of type 
*           CYBLE_GAP_BD_ADDR_T.
*  \param addrType: Specifies the type of address. This can take one of the values 
*             from the enumerated data type CYBLE_GAP_ADDR_TYPE_T.
*  \param irk: Pointer to buffer containing 128-bit 'IRK' data. This parameter is only
*        used when CYBLE_GAP_RANDOM_PRIV_RESOLVABLE_ADDR is the value set to
*        'addrType'. For other values of 'addrType', this parameter is not used.
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
CYBLE_API_RESULT_T CyBle_GapGenerateDeviceAddress
                (
                    CYBLE_GAP_BD_ADDR_T*	bdAddr,
                    CYBLE_GAP_ADDR_TYPE_T	addrType,
                    uint8 *irk
                );


/******************************************************************************
* Function Name: CyBle_GapSetSecurityKeys
***************************************************************************//**
* 
*  This function sets the security keys that are to be exchanged with peer
*  device during key exchange stage of authentication procedure and sets it in the 
*  BLE Stack. This is a blocking function. No event is generated on calling this function.
*     
*  \param keysFlag: This parameter indicates which keys get exchanged with peer device.
*                   The following is the bit field mapping for the keys.
*                 * Bit 0: Local Encryption information
*                 * Bit 1: Local Identity information
*                 * Bit 2: Local Signature Key
*                 * Bit 3: Reserved
*                 * Bit 4: Remote Encryption information
*                 * Bit 5: Remote Identity information
*                 * Bit 6: Remote Signature Key
*                 * Bit 7: Reserved
*					
*  \param keyInfo: Pointer to a variable containing the keys to be set, of type 
*            'CYBLE_GAP_SMP_KEY_DIST_T'. idAddrInfo param of 'CYBLE_GAP_SMP_KEY_DIST_T'
*            will be ignored. 'CyBle_GapSetIdAddress' api needs to be used to set bd address.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On specifying NULL as input parameter for 'keyInfo'
* 
******************************************************************************/    
CYBLE_API_RESULT_T CyBle_GapSetSecurityKeys(uint8 keysFlag, CYBLE_GAP_SMP_KEY_DIST_T *keyInfo);


/******************************************************************************
* Function Name: CyBle_GapGenerateKeys
***************************************************************************//**
* 
* This function generates and sets the security keys into BLE Stack that are to be exchanged with peer
* device during key exchange stage of authentication procedure. 
* This is a blocking function. No event is generated on calling this function.
* This API function does not generate identity address (keyInfo->idAddrInfo)
*
*  \param keysFlag: This parameter indicates which keys get exchanged with peer device.
*                   The following is the bit field mapping for the keys.
*              * Bit 0: Local Encryption information
*              * Bit 1: Local Identity information
*              * Bit 2: Local Signature Key
*              * Bit 3: Reserved
*              * Bit 4: Remote Encryption information
*              * Bit 5: Remote Identity information
*              * Bit 6: Remote Signature Key
*              * Bit 7: Reserved
*
*  \param keyInfo: Pointer to a variable containing the returned keys, of type 
*            'CYBLE_GAP_SMP_KEY_DIST_T'
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On specifying NULL as input parameter for 'keyInfo'
* 
******************************************************************************/    
CYBLE_API_RESULT_T CyBle_GapGenerateKeys(uint8 keysFlag, CYBLE_GAP_SMP_KEY_DIST_T *keyInfo);


/******************************************************************************
* Function Name: CyBle_GapAuthReq
***************************************************************************//**
* 
*  This function starts authentication/pairing procedure with the peer device. 
*  It is a non-blocking function.
*  
*  If the local device is a GAP Central, the pairing request is sent to the GAP
*  Peripheral device. On receiving CYBLE_EVT_GAP_AUTH_REQ event, the GAP
*  Peripheral is expected to respond by invoking the CyBle_GappAuthReqReply()
*  function.
* 
*  If the local device is GAP Peripheral, a Security Request is sent to GAP
*  Central device. On receiving CYBLE_EVT_GAP_AUTH_REQ event, the GAP Central
*  device is expected to respond by invoking 'CyBle_GapAuthReq ()' function.
* 
*  \param bdHandle: Peer device handle
*  \param authInfo: Pointer to security information of the device of type 
*             CYBLE_GAP_AUTH_INFO_T. The 'authErr' parameter in 
*             CYBLE_GAP_AUTH_INFO_T should be ignored as it is not used in 
*             this function.
*  NOTE: If the bonding flag in authInfo is set to CYBLE_GAP_BONDING_NONE then, SMP keys will not be
*        distributed even if application has generated and set the keys explicitly.
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>On specifying null pointer for 'advInfo' or if any of the element of this structure has an invalid value.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_NO_DEVICE_ENTITY</td>
*    <td>Device identified using 'bdHandle' does not exist.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INSUFFICIENT_RESOURCES</td>
*    <td>On bonded device is full and application tries to initiate pairing with bonding enable.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAuthReq(uint8 bdHandle, CYBLE_GAP_AUTH_INFO_T *authInfo);

/** @} */

/**
 \addtogroup group_common_api_gap_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GappAuthReqReply
***************************************************************************//**
* 
*  This function is used to pass security information for authentication in reply
*  to an authentication request from the master device. It should be invoked on
*  receiving CYBLE_EVT_GAP_AUTH_REQ event. Events shown in the following table
*  may be received by the application based on the authentication result.
*
*  <table>
*  <tr>
*    <th>Event Parameter</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_EVT_TIMEOUT</td>
*    <td>With error code CYBLE_GAP_PAIRING_PROCESS_TO on invoking CyBle_GappAuthReqReply() or CyBle_GapAuthReq() 
*        if there is no response from the peer device</td>
*  </tr>
*  <tr>
*    <td>CYBLE_EVT_GAP_AUTH_COMPLETE</td>
*    <td>Pointer to structure of type 'CYBLE_GAP_AUTH_INFO_T' is returned as parameter to both the peer devices 
*        on successful authentication.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_EVT_GAP_AUTH_FAILED</td>
*    <td>Received by both GAP Central and Peripheral devices (peers) on authentication failure. 
*        Data is of type CYBLE_GAP_AUTH_FAILED_REASON_T.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO</td>
*    <td>With negotiated pairing parameters on invoking CyBle_GappAuthReqReply() from function call context.</td>
*  </tr>
*  </table>
* 
*  \param bdHandle: Peer device handle.
*  \param authInfo: Pointer to a variable containing security information of the device
*             of type CYBLE_GAP_AUTH_INFO_T.
*
*  NOTE: If the bonding flag in authInfo is set to CYBLE_GAP_BONDING_NONE then, SMP keys will not be
*        distributed even if application has generated and set the keys explicitly.
*
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
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>On specifying null pointer for 'advInfo' or if any of the element of this structure has an invalid value.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>Memory allocation failed</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_NO_DEVICE_ENTITY</td>
*    <td>Device identified using 'bdHandle' does not exist.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INSUFFICIENT_RESOURCES</td>
*    <td>On bonded device is full and application tries to initiate pairing with bonding enable.</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GappAuthReqReply(uint8 bdHandle, CYBLE_GAP_AUTH_INFO_T *authInfo);

/** @} */

/**
 \addtogroup group_common_api_gap_central_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapAuthPassKeyReply
***************************************************************************//**
* 
*  This function sends passkey for authentication. It is a non-blocking function.
* 
*  It should be invoked in reply to the authentication request event
*  CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST received by the BLE Stack. This function
*  is used to accept the passkey request and send the passkey or reject the
*  passkey request.
*  
*  * If the authentication operation succeeds, CYBLE_EVT_GAP_AUTH_COMPLETE is
*     generated. If the authentication process times out, CYBLE_EVT_TIMEOUT 
*     event is generated.
*  * If the authentication fails, CYBLE_EVT_GAP_AUTH_FAILED event is generated.
* 
*  \param bdHandle: Peer device handle
*  \param passkey: 6-digit decimal number (authentication passkey)
*  \param accept: Accept or reject passkey entry request. Allowed values are,
*           * CYBLE_GAP_REJECT_PASSKEY_REQ
*           * CYBLE_GAP_ACCEPT_PASSKEY_REQ
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | Invalid parameter.
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed.
*   CYBLE_ERROR_NO_DEVICE_ENTITY         | Device identified using 'bdHandle' does not exist.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAuthPassKeyReply(uint8 bdHandle, uint32 passkey, uint8 accept);


/******************************************************************************
* Function Name: CyBle_GapRemoveDeviceFromWhiteList
***************************************************************************//**
* 
*  This function marks the device untrusted. It removes the bonding information
*  of the device and removes it from the white list. More details on 'bonding' and 'trusted devices' is
*  available in Bluetooth 4.1 core specification, Volume 3, Part C, section 9.4.4.
* 
*  This is a blocking function. No event is generated on calling this function.
*  This API function is kept as is for backward compatibility. This API function will be obsolete in future.
* 
*  \param bdAddr: Pointer to peer device address, of type CYBLE_GAP_BD_ADDR_T. If device
*           address is set to 0, then all devices shall be removed from trusted
*           list and white list.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter for 'bdAddr'.
*   CYBLE_ERROR_INVALID_OPERATION    | Whitelist is already in use.	
*   CYBLE_ERROR_NO_DEVICE_ENTITY     | Device does not exist in the whitelist.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapRemoveDeviceFromWhiteList(CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
* Function Name: CyBle_GapAddDeviceToWhiteList
***************************************************************************//**
* 
*  This function adds the device to the whitelist. Maximum number of devices that
*  can be added to the whitelist is eight including CYBLE_GAP_MAX_BONDED_DEVICE.
*  Refer to Bluetooth 4.1 core specification, Volume 3, Part C, section 9.3.5 for more details on whitelist.
* 
*  This is a blocking function. No event is generated on calling this function.
*     
*  \param bdAddr: Peer device address, of type CYBLE_GAP_BD_ADDR_T.
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
*    <td>On specifying NULL as input parameter for 'bdAddr' or 'bdAddr-&gt;type' has an invalid value</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>Whitelist is already in use</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INSUFFICIENT_RESOURCES</td>
*    <td>&nbsp;WhitelistMemory is full</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_DEVICE_ALREADY_EXISTS</td>
*    <td>Matching device already exists in the whitelist</td>
*  </tr>
*  </table>
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAddDeviceToWhiteList(CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
* Function Name: CyBle_GapGetBondedDevicesList
***************************************************************************//**
* 
*  This function returns the count and Bluetooth device address of the devices in
*  the bonded device list. This is a blocking function. No event is generated on
*  calling this function.
* 
*  Application invoking this function should allocate sufficient memory for the
*  structure CYBLE_GAP_BONDED_DEV_ADDR_LIST_T, where the complete list of bonded
*  devices along with count can be written. Maximum devices bonded are specified
*  by CYBLE_GAP_MAX_BONDED_DEVICE, which is a pre processing time parameter for
*  the BLE Stack. Hence, the bonded device count will be less than or equal to
*  CYBLE_GAP_MAX_BONDED_DEVICE.
* 
*  Refer Bluetooth 4.1 core specification, Volume 3, Part C, section 9.4.4 for
*  details on bonded devices.
*     
* 	
*  \param bondedDevList: Buffer to which list of bonded device list will be stored of 
*                  type CYBLE_GAP_BONDED_DEV_ADDR_LIST_T.
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
CYBLE_API_RESULT_T CyBle_GapGetBondedDevicesList(CYBLE_GAP_BONDED_DEV_ADDR_LIST_T* bondedDevList);


/******************************************************************************
* Function Name: CyBle_GapRemoveOldestDeviceFromBondedList
***************************************************************************//**
* 
*  This function removes the oldest device from the bonded and white lists. 
*  This api should not be called while in connected state.
*  If device is connected to the oldest device, and this API function is called, it will remove the device which 
*  is next oldest and not connected. 
* 
* \return
* 	CYBLE_API_RESULT_T : Return value indicates if the function succeeded (0x0000) or failed.
* 	Following are the possible error codes returned.
*
* 	Errors codes						| Description
* 	------------                        | -----------
* 	CYBLE_ERROR_OK						| On successful operation.
*   CYBLE_ERROR_MAX 					| On failure operation.
* 			
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapRemoveOldestDeviceFromBondedList (void);

/** @} */

/**
 \addtogroup group_common_api_gap_central_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapcConnectionParamUpdateRequest
***************************************************************************//**
* 
*  This function sends the connection parameter update command to local controller. 
*  This function can only be used from device connected in GAP Central role.
*  Note: Connection parameter update procedure, defined as part of Bluetooth spec 4.1, is not supported.
*          This function will allow GAP Central application to update connection parameter for local controller
*          and local controller will follow the procedure as defined in Bluetooth Core specification 4.0.
*  
* 
*  \param bdHandle: Peer device handle
*  \param connParam: Pointer to a structure of type CYBLE_GAP_CONN_UPDATE_PARAM_T
*             containing connection parameter updates
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.	
*
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation 'connParam' is NULL
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed
*   CYBLE_ERROR_NO_DEVICE_ENTITY         | Device identified using 'bdHandle' does not exist.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcConnectionParamUpdateRequest
           (
               	uint8  	     		 			bdHandle,
				CYBLE_GAP_CONN_UPDATE_PARAM_T	*connParam
           );


/******************************************************************************
* Function Name: CyBle_GapcSetHostChannelClassification
***************************************************************************//**
* 
*  This function sets channel classification for data channels. This
*  classification persists until it is overwritten by a subsequent call to this
*  function or the controller is reset. If this command is used, updates should
*  be sent within 10 seconds of the BLE Host knowing that the channel
*  classification has changed. The interval between two successive commands sent
*  will be at least one second. This command will only be used when the local
*  device supports the Master role. 
*  
*  For details, refer to Bluetooth core specification 4.1, Volume 2, part E,
*  section 7.8.19.
* 
*  This is a non blocking function. Application should look for 'CYBLE_EVT_HCI_STATUS' 
*  for any error condition.
* 
*  \param channelMap: This parameter contains five octet byte stream (Least Significant
*               Byte having the bit fields 0 to 7, most significant byte having
*               the bit fields 32 to 36). The nth such field (in the range 0 to
*               36) contains the value for the link layer channel index n. 
*               Allowed values and their interpretation are,
*               * Channel 'n' is disabled = 0x00u
*               * Channel 'n' is enabled = 0x01u
*
*               The most significant bits (37 to 39) are reserved and will be 
*               set to 0. At least one channel will be marked as unknown.
*       For example-
*       expected pattern = XX XX XX XX 1F
*       not expected =  XX XX XX XX 10, XX XX XX XX 2f 
*       MSB 3 bits should be not set. (1f is most significant bytes in this case)
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On specifying NULL as input parameter for 'channelMap'.
*   CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Memory allocation failed.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcSetHostChannelClassification
           (
               	uint8*   channelMap
           );

/** @} */           

/**
 \addtogroup group_common_api_gap_central_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapGetDevSecurityKeyInfo
***************************************************************************//**
* 
*  This function gets the local device's Keys and key flags. The IRK received from
*  this function should be used as the input IRK for the function 
*  'CyBle_GapGenerateDeviceAddress' to generate Random Private Resolvable address.
*  This is a blocking function. No event is generated on calling this function.
* 
*  \param keyFlags:	Pointer to a byte where the key flags are stored. Based
* 			 on the flag bits, the calling application can determine if
* 			 the returned value is valid (1) or not (0).
* 			 Key distribution flag
* 			 * Bit 0: Local Encryption information
* 			 * Bit 1: Local Identity information
* 			 * Bit 2: Local Signature Key
* 			 * Bit 3 - Bit 7: Reserved
*  \param keys:		Pointer to a structure of type CYBLE_GAP_SMP_KEY_DIST_T
* 			 where the keys get stored
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On specifying NULL as input parameters
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetDevSecurityKeyInfo
(
   uint8  					* keyFlags,
   CYBLE_GAP_SMP_KEY_DIST_T	* keys
);

/** @} */

/**
 \addtogroup group_common_api_gap_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapUpdateAdvData
***************************************************************************//**
* 
*  This function allows setting the ADV data and SCAN response data while advertising
*  is ongoing. Application shall preserve Bluetooth Spec 4.1 mandated AD flags fields
*  corresponding to the type of discovery mode the device is in and only change the
*  rest of the data. This API function must be called when API function CyBle_GetBleSsState()
*  returns CYBLE_BLESS_STATE_EVENT_CLOSE state. If API returns is called in any of the BLESS Low
*  Power Modes, it will force exit BLESS from Low Power Mode state to update ADV
*  Data.
*  
*  \param advDiscData: Pointer to a structure of CYBLE_GAPP_DISC_DATA_T. It has two fields
*           advData field representing the data and advDataLen indicating the
*           length of present data. Application can pass length as 0 if the ADV 
*           data doesn't need to be changed.
*  
*  \param advScanRespData: Pointer to a structure of type CYBLE_GAPP_SCAN_RSP_DATA_T. It has two
*                fields scanRspData field representing the data and scanRspDataLen 
*                indicating the length of present data. Application can pass length
*                as 0 if the SCAN RESP data doesn't need to be changed.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
* 
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On NULL pointer, Data length in input parameter exceeds 31 bytes. 
*   CYBLE_ERROR_INVALID_OPERATION        | ADV Event is not closed, BLESS is active or ADV is not enabled.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapUpdateAdvData
(
   CYBLE_GAPP_DISC_DATA_T   	* advDiscData,
   CYBLE_GAPP_SCAN_RSP_DATA_T	* advScanRespData
);

/** @} */

/**
 \addtogroup group_common_api_gap_central_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapcSetRemoteAddr
***************************************************************************//**
* 
*  This function allows application to set the new address of remote device identified by bdHandle.
*  This API function should be used when:
*  1. If peer device is previously bonded with public address and changes its bd address to resolvable private address. 
*      Application should resolve the device by calling 'CyBle_GapcResolveDevice()' api and set the 
*      new address if successfully resolved.
*  2. If device is previously bonded with random, application should call this api to set the new address(public/random).
* 
*  \param bdHandle: Peer device handle
* 
*  \param remoteAddr: Peer device address, of type CYBLE_GAP_BD_ADDR_T.
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
* 
*   Errors codes                         | Description
*   ------------                         | -----------
*   CYBLE_ERROR_OK                       | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER        | On invalid bdHandle                                        
*   CYBLE_ERROR_NO_DEVICE_ENTITY         | Device identified using 'bdHandle' does not exist.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcSetRemoteAddr
(
   uint8     			bdHandle,
   CYBLE_GAP_BD_ADDR_T  remoteAddr
);

/** @} */

/**
 \addtogroup group_common_api_gap_central_peripheral_functions
 @{
*/

/******************************************************************************
* Function Name: CyBle_GapGetDevicesFromWhiteList
***************************************************************************//**
* 
*  This function extracts the list of devices added to the white list. This
*  is a blocking function. No events are generated on calling this function.
*  There is no HCI command defined for this operation as the application is
*  expected to keep track of the devices added to the white list. This
*  function has been provided to facilitate testing of the Cypress BLE
*  Hardware using CySmart tool.
* 
*  \param count: Pointer to a variable to hold the number of enabled addresses in
* 		 the white list. This is an output parameter.
*  \param addr: Pointer to a variable of type 'CYBLE_GAP_BD_ADDR_T' which holds
* 		 Address type and Address of the device.
*  
*  	The function invoking this should allocate memory for the variables
*  	pointed to by the above pointers. 'addr' should point to an array of
*  	type CYBLE_GAP_BD_ADDR_T and size equal to the maximum number of
* 	white list devices supported by the BLE Stack (CYBLE_MAX_WHITELIST_ENTRIES).
* 
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
* 
*   Errors codes                       | Description
*   ------------                       | -----------
*   CYBLE_ERROR_OK					   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER	   | On specifying NULL as input parameter(s)
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetDevicesFromWhiteList
    (
        uint8* count,
        CYBLE_GAP_BD_ADDR_T* addr
    );

    
/******************************************************************************
* Function Name: CyBle_GapGetChannelMap
***************************************************************************//**
* 
* This function reads the channel map for data channels. This
* classification persists until it is overwritten by a subsequent call to this
* function or the controller is reset. If this command is used, updates should
* be sent within 10 seconds of the BLE Host knowing that the channel
* classification has changed. The interval between two successive commands sent
* will be at least one second. This command will only be used when the local
* device supports the Master role. 
* 
* For details, refer to Bluetooth core specification 4.1, Volume 2, part E,
* section 7.8.19.
*
* This is a blocking function. No event is generated on calling this function.
*
*  \param bdHandle: Peer device handle.
*  \param channelMap: 
*             This parameter contains five octet byte stream (Least Significant
*              Byte having the bit fields 0 to 7, most significant byte having
*              the bit fields 32 to 36). The nth such field (in the range 0 to
*              36) contains the value for the link layer channel index n. 
*              Allowed values and their interpretation are,
*              * Channel 'n' is bad = 0x00u
*              * Channel 'n' is unknown = 0x01u
*              .  
*              The most significant bits (37 to 39) are reserved and will be 
*              set to 0. At least one channel will be marked as unknown.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*  CYBLE_ERROR_OK                        | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER         | On specifying NULL as input parameter for 'channelMap'.
*  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  | Memory allocation failed.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetChannelMap
(
	uint8	bdHandle,
   	uint8 	* channelMap
);


/******************************************************************************
* Function Name: CyBle_GapSetSecureConnectionsOnlyMode
***************************************************************************//**
*
* This API function sets the state of secure connections only mode for device.
* If device is in secure connections only mode, it will allow pairing to
* complete only with secure connections security. Other kind of pairing will
* lead to pairing failure with reason "Authentication requirement not met"
* It is expected to call this API function on host stack on, though can be called 
* at any point.
* Secure connections only is not persistent across power cycles. It is
* persistent across stack shutdown-init cycles.
*
* \param state: 0 - Disable (Device not in secure connections only mode) \n
*               1 - Enable (Device is in secure connections only mode)
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                      | Description
*  ------------                      | -----------
*  CYBLE_ERROR_OK                    | On successful operation.
*  CYBLE_ERROR_INVALID_OPERATION     | Secure connections feature was not selected in feature config and API function is called.
*  CYBLE_ERROR_INVALID_PARAMETER     | parameter out of range
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetSecureConnectionsOnlyMode(uint8 state);


/******************************************************************************
* Function Name: CyBle_GapGenerateLocalP256Keys
***************************************************************************//**
*
* This API function is used to generate P-256 Public-Private key pair to be used 
* during LE Secure connection pairing procedure. Application may choose to generate 
* P-256 public-private key pair before pairing process starts. If this API function 
* is not called before pairing process starts, BLE Stack will use default public-private
* key pair.
*
* For robust security Cypress recommends that, the application may change the local 
* public-private key pair after every pairing (successful or failed) attempt.
*
* For details, refer to Bluetooth core specification 4.2, Volume 3, part H, section 2.3.6.
*
* On the Completion of key generation, new keys will be set in the BLE Stack for SC pairing procedure 
* and application receives CYBLE_EVT_GAP_SMP_LOC_P256_KEYS_GEN_AND_SET_COMPLETE event.
*
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                     | Description
*  ------------                     | -----------
*  CYBLE_ERROR_OK                   | On successful operation.
*  CYBLE_ERROR_INVALID_OPERATION    | Pairing is in progress.	
*
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGenerateLocalP256Keys(void);

/******************************************************************************
* Function Name: CyBle_GapSetLocalP256Keys
***************************************************************************//**
*
* This API function is used to set P-256 Public-Private key pair to be used during LE Secure connection 
* pairing procedure. Application may choose to set P-256 public-private key pair before pairing 
* process starts. If this API function is not called before pairing process starts, BLE Stack will use default
* public-private key pair. This API function is not expected to be called when pairing procedure is in progress.
* Application can generate P-256 Public-Private key pair using API function CyBle_GapGenerateLocalP256Keys()
* and can set the generated key pair using this API function.
*
* For robust security Cypress recommends that, the application may change the local 
* public-private key pair after every pairing (successful or failed) attempt.
*
* For details, refer to Bluetooth core specification 4.2, Volume 3, part H, section 2.3.6.
*
* \param localP256Keys: Pointer to structure CYBLE_GAP_SMP_LOCAL_P256_KEYS, that has
*                       fields for local P-256 public-private key pair.
* \param isValidateKeys: If it is set to 1 public key is validated, if it is set to 0 
*                        public key is not validated.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                     | Description
*  ------------                     | -----------
*  CYBLE_ERROR_OK                   | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER    | Parameter is NULL Or Public key is not valid
*  CYBLE_ERROR_INVALID_OPERATION    | Pairing is in progress.
*
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetLocalP256Keys
(
    CYBLE_GAP_SMP_LOCAL_P256_KEYS *localP256Keys,
    uint8 isValidateKeys
);

/******************************************************************************
* Function Name: CyBle_GapAuthSendKeyPress
***************************************************************************//**
*
*  This API function is used to send LE Secure connections key press notification to peer
*  device during secure connection pairing.
*  This API function should be called by application to inform stack about passkey entry 
*  process started for each digit
*  - Started (0), entered (1), erased (2), cleared (3), completed (4).
*  Once all the digits are entered, application needs to call
*  'CyBle_GapAuthPassKeyReply()' to inform stack for passkey enter completed.
*  Error will be returned if key press entry bit was not set in 
*  'pairingProperties' of CYBLE_GAP_AUTH_INFO_T during authentication procedure.
*  
*  Typical application usage scenario:
*  1. Call with CYBLE_GAP_PASSKEY_ENTRY_STARTED on receiving event to enter passkey.
*  2. Call with CYBLE_GAP_PASSKEY_DIGIT_ENTERED, CYBLE_GAP_PASSKEY_DIGIT_ERASED or 
*     CYBLE_GAP_PASSKEY_CLEARED based on application events while user enters passkey.
*  3. Call with CYBLE_GAP_PASSKEY_ENTRY_COMPLETED after user application successfully
*     received passkey.
*  4. This should be followed by call to CyBle_GapAuthPassKeyReply API function to provide
*     user entered passkey to Stack.
*
*  \param bdHandle: Peer device handle.
*  \param notificationType: parameter of type 'CYBLE_GAP_KEYPRESS_NOTIFY_TYPE'
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER        | notificationType is invalid.  
*  CYBLE_ERROR_NO_DEVICE_ENTITY         | Device identified using 'bdHandle' does not exist.
*  CYBLE_ERROR_INVALID_OPERATION        | Keypress was not negotiated or 
*                                         passkey entry procedure not ongoing or
*                                         Secured Connection is not enabled or 
*                                         pairing procedure is not in progress.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAuthSendKeyPress
(
    uint8                           bdHandle,
    CYBLE_GAP_KEYPRESS_NOTIFY_TYPE  notificationType
);

/******************************************************************************
* Function Name: CyBle_GapGenerateOobData
***************************************************************************//**
*
* This API function is used to generate OOB data based on the input parameter (16 Byte random number)
* This API function is called to generate OOB data to be used by peer device. Peer device (or local device with peer's OOB data)
* will use 'CyBle_GapSetOobData()' to set the OOB data to be used for secure connections pairing. 
*
* Note: This API function should be used only in secured connection pairing. In case of legacy pairing only key is used for
*       OOB authentication. But in SC pairing, key(pRand) is used to generate local OOB data(Confirm value). In SC both
*       key and generated OOB data are used in OOB authentication. Hence this API function is used only in SC pairing.
*
*  \param pRand: 16 Bytes Random number to be used for generating OOB data. If NULL is passed, stack will generate
*                16 Bytes random number and then will generate OOB data.
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED | Sufficient memory is not available to handle this request.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGenerateOobData (const uint8 *pRand);

/******************************************************************************
* Function Name: CyBle_GapSetDataLength
***************************************************************************//**
*
* This API function allows application to suggest maximum transmission packet size and maximum packet transmission time 
* for current connection. 
* Actual data length used by controller will be informed through 'CYBLE_EVT_GAP_DATA_LENGTH_CHANGE' event
*
*  \param bdHandle: Peer device handle.
*  \param connMaxTxOctets: Preferred maximum number of payload octets that the local Controller should include in a 
*					single Link Layer Data Channel PDU. 
*					Range 0x001B-0x00FB (0x0000 - 0x001A and 0x00FC - 0xFFFF Reserved for future use)
*  \param connMaxTxTime: Preferred maximum number of microseconds that the local Controller should use to transmit 
* 				a single Link Layer Data Channel PDU. 
* 				Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF Reserved for future use)
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                              | Description
*  ------------                              | -----------
*  CYBLE_ERROR_OK                            | On successful operation.
*  CYBLE_ERROR_NO_DEVICE_ENTITY              | Device identified by bdHandle is not present
*  CYBLE_ERROR_INVALID_PARAMETER		     | Out of range value passed.                                      
*  CYBLE_ERROR_INVALID_OPERATION             | DLE feature not enabled
*  CYBLE_ERROR_LL_SAME_TRANSACTION_COLLISION | When there is already DLE procedure is pending
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetDataLength 
(
    uint8 		bdHandle, 
    uint16 		connMaxTxOctets, 
    uint16		connMaxTxTime
);


/******************************************************************************
* Function Name: CyBle_GapSetRxDataLength
***************************************************************************//**
*
* This API function allows application to suggest the maximum number of payload octets 
* that the local controller expects to receive and maximum time that local 
* controller expects to take to receive a PDU on current connection.
*
* Actual data length used by controller will be informed through 'CYBLE_EVT_GAP_DATA_LENGTH_CHANGE' event
*
*  \param RxDleParams: Pointer to a structure of type 'CYBLE_GAP_RX_DATA_LENGTH_T'. 
*				 It has three fields bdHandle field representing the peer device handle, 
*				 connmaxRxOctets field representing preferred maximum number of payload octets 
*				 that the local controller should expects to receive on current connection
*				 Range 0x001B-0x00FB (0x0000 - 0x001A and 0x00FC - 0xFFFF Reserved for future use)
*				 and connMaxRxTime field representing preferred maximum number of microseconds that the
*				 local Controller should use to receive a single Link Layer Data Channel PDU.
* 				 Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF Reserved for future use)
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
* 
*  Errors codes                              | Description
*  ------------                              | -----------
*  CYBLE_ERROR_OK                            | On successful operation.
*  CYBLE_ERROR_NO_DEVICE_ENTITY              | Device identified by bdHandle is not present
*  CYBLE_ERROR_INVALID_PARAMETER             | If NULL passed
*  CYBLE_ERROR_INVALID_OPERATION             | DLE feature not enabled
*  CYBLE_ERROR_LL_SAME_TRANSACTION_COLLISION | When there is already DLE procedure is pending
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetRxDataLength(CYBLE_GAP_RX_DATA_LENGTH_T *RxDleParams);


/******************************************************************************
* Function Name: CyBle_GapSetSuggestedDataLength
***************************************************************************//**
*
* This API function allows the application to specify its preferred values for the Link 
* Layer maximum Tx packet (Data Channel PDU) size (connInitialMaxTxOctets) and 
* maximum Tx packet transmission time (connInitialMaxTxTime)to be used for new 
* connections. 
*
*  \param suggestedTxOctets: The suggested value (connInitialMaxTxOctets) for 
*                    the maximum transmitted number of payload octets (Link  
*                    Layer Data Channel PDU) to be used for new connections.
*					 Range 0x001B-0x00FB (0x0000 - 0x001A and 
*                    0x00FC - 0xFFFF Reserved for future use)
*  \param suggestedTxTime: The suggested value (connInitialMaxTxTime)for the  
*                     maximum packet (Link Layer Data Channel PDU) transmission  
*                     time to be used for new connections. Application can use 
*                     API function CyBle_GapConvertOctetToTime to get timeconnMaxTxTime 
*                     corresponding to suggestedTxOctets.
*                     Range 0x0148-0x0848 (0x0000 - 0x0147 and 0x0849 - 0xFFFF 
*                     Reserved for future use)
*
*  \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER        | Out of range values.
*  CYBLE_ERROR_INVALID_OPERATION        | DLE feature not enabled
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetSuggestedDataLength 
(
    uint16 		suggestedTxOctets, 
    uint16		suggestedTxTime
);

/******************************************************************************
* Function Name: CyBle_GapGetDataLength
***************************************************************************//**
*
* This API function allows the application to read Link Layer maximum supported Tx/Rx  
* packet (DataChannel PDU) octets / transmission time and maximum suggested 
* Tx/Rx packet octets / transmission time.
*
*  \param readParam: Pointer to structure of type 'CYBLE_GAP_DATA_LENGTH_T'.  
*             This is an output parameter which contain the maximum supported  
*             Tx and Rx octets & time and maximum suggested Tx octets & time.
*
*  \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER        | Null pointer passed.
*  CYBLE_ERROR_INVALID_OPERATION        | DLE feature not enabled
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetDataLength 
(
    CYBLE_GAP_DATA_LENGTH_T * readParam
);

/******************************************************************************
* Function Name: CyBle_GapConvertOctetToTime
***************************************************************************//**
*
* This API function allows application to compute time from Octets.
* Time can be used to pass to BLE Stack while setting data length.
*
*  \param phy: Physical layer to be considered while computing.
*           Should be passed as CYBLE_GAP_PHY_1MBPS. Other values are Reserved.
*  \param octets: Payload octets. This is an input parameter.
*  \param pTime: Buffer where time in microseconds will be stored which is 
*           derived from octets and phy.
*  \return
*   CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*   failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER        | Null pointer passed. Invalid PHY Value passed. Invalid Octet Value is passed. (Valid Range 27 to 251)
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapConvertOctetToTime
(
    CYBLE_GAP_PHY_TYPE_T phy,
    uint16               octets,
    uint16              *pTime
);

/******************************************************************************
* Function Name: CyBle_GapAddDeviceToResolvingList
***************************************************************************//**
*
* This API function is used to add a device to the resolving list in the controller for
* resolving Resolvable Private Address(RPA). This API function can be used to update
* local and/or peer IRKs for an existing Resolving List entry by passing the
* same peer address type and peer address in the argument.
*
*  \param rpaInfo: Buffer which contains the information of peer address, peer address type, local and peer IRKs.
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or failed.
*                       Following are the possible error codes.
*
* <table>
*  <tr>
*    <th>Errors codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>Any of the input parameter is NULL</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*    <td>When a Controller cannot add a device to the resolving list because the list
*         is full.
*    </td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>Request is not permitted when address translation is enabled in the Controller and:
*               * Advertising is enabled
*               * Scanning is enabled
*               * Create connection command is outstanding.
*    </td>
*  </tr>
* </table>
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAddDeviceToResolvingList
(
	const CYBLE_GAP_RESOLVING_DEVICE_INFO_T * rpaInfo
);


/******************************************************************************
* Function Name: CyBle_GapRemoveDeviceFromResolvingList
***************************************************************************//**
*
* This API function is used to remove one device from the list of address translations used to resolve Resolvable 
* Private Addresses in the BLE Stack.  
*
*  \param peerIdentityAddr: Buffer which contains the information of peer bd address and address type
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
* <table>
*  <tr>
*    <th>Errors codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>Any of the input parameter is NULL</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>Request is not permitted when address translation is enabled in the
*		Controller and:
*			* Advertising is enabled
*			* Scanning is enabled
*			* Create connection command is outstanding.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_NO_DEVICE_ENTITY</td>
*    <td>When a Controller cannot remove a device from the resolving list 
*		because it is not found.</td>
*  </tr>
* </table>
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapRemoveDeviceFromResolvingList 
(
	const CYBLE_GAP_BD_ADDR_T * peerIdentityAddr
);

/******************************************************************************
* Function Name: CyBle_GapClearResolvingList
***************************************************************************//**
*
* This API function is used to clear all devices from the list of address translations used to resolve Resolvable 
*  Private Addresses in the Controller. 
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
* <table>
*  <tr>
*    <th>Errors codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
* <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>Request is not permitted when address translation is enabled in the
*		Controller and:
*		 * Advertising is enabled
*		 * Scanning is enabled
*		 * Create connection command is outstanding.</td>
*  </tr>
* </table>
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapClearResolvingList 
(
	void
);

/******************************************************************************
* Function Name: CyBle_GapReadPeerResolvableAddress
***************************************************************************//**
*
* This API function is used to get the current peer Resolvable Private Address being used for the corresponding 
* peer Public and Random (static) Identity Address. The peer’s resolvable address being used may 
* change after the command is called.  
*
*  \param peerIdentityAddr: Buffer which contains the information of peer bd address and address type
*  \param peerResolvableAddress: Buffer to which peer resolvable private address will be stored.
*
*  \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                   | Description
*  ------------                   | -----------
*  CYBLE_ERROR_OK                 | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER  | Any of the input parameter is NULL
*  CYBLE_ERROR_NO_DEVICE_ENTITY	  | When a Controller cannot remove a device from the resolving list because it is not found.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapReadPeerResolvableAddress 
(
    const CYBLE_GAP_BD_ADDR_T   * peerIdentityAddr,
    uint8                       * peerResolvableAddress
);

/******************************************************************************
* Function Name: CyBle_GapReadLocalResolvableAddress
***************************************************************************//**
*
* This API function is used to get the current local Resolvable Private Address being used for the corresponding peer
* Identity Address. The local’s resolvable address being used may change after the command is called.
*
*  \param peerIdentityAddr: Buffer which contains the information of peer bd address and address type
*  \param localResolvableAddress: Buffer to which local resolvable private address will be stored.
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
* 
*  Errors codes                   | Description
*  ------------                   | -----------
*  CYBLE_ERROR_OK                 | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER  | Any of the input parameter is NULL
*  CYBLE_ERROR_NO_DEVICE_ENTITY	  | When a Controller cannot remove a device from the resolving list because it is not found.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapReadLocalResolvableAddress 
(
	const CYBLE_GAP_BD_ADDR_T 	* peerIdentityAddr,
	uint8  					    * localResolvableAddress
);

/******************************************************************************
* Function Name: CyBle_GapSetResolvablePvtAddressTimeOut
***************************************************************************//**
*
* This API function is used to set the length of time the controller uses a Resolvable Private Address before a new 
* resolvable private address is generated and starts being used.  This timeout applies to all addresses 
* generated by the BLE Stack.
*
*  \param rpaTimeOut: RPA_Timeout measured in seconds.
*			Range for N: 0x0001 – 0xA1B8 (1 sec – approximately 11.5 hours)
*			Default: N= 0x0384 (900 secs or 15 minutes)
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER		| Invalid timeout value
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetResolvablePvtAddressTimeOut  
(
	uint16 		rpaTimeOut
);

/******************************************************************************
* Function Name: CyBle_GapReadResolvingList
***************************************************************************//**
*
* This API function is used to read all the entries of address translation in the resolving list that is stored in BLE Stack.
*
* \param resolvingList: Buffer to store resolving list. Memory shall be  
	                    allocated by the calling function.
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER	    | Input parameter is NULL
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapReadResolvingList
(
	CYBLE_GAP_RESOLVING_LIST_T	* resolvingList
);

/******************************************************************************
* Function Name: CyBle_GapSetAddressResolutionEnable
***************************************************************************//**
*
* This API function is used to enable resolution of Resolvable Private Addresses in the BLE Stack. This causes the
* BLE Stack to use the resolving list whenever the Controller receives a local or peer Resolvable Private Address.
*
*  \param enableDisable: 0x00 - Address Resolution in controller disabled (default) \n
*			             0x01 - Address Resolution in controller enabled \n
*			             0x02 – 0xFF Reserved for Future Use
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER	    | 'enableDisable' value is greater than 0x01
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetAddressResolutionEnable  
(
	uint8 		enableDisable
);

/******************************************************************************
* Function Name: CyBle_GapSetPrivacyMode
***************************************************************************//**
*
* This API function is used to allow the Host to specify the privacy mode to be used for 
* a given entry on the resolving list. 

* The effect of this setting is specified in [Vol 6] Part B, Section 4.7.
*
* When an entry on the resolving list is removed, the mode associated with that
* entry shall also be removed.
*
*  \param privacyModeInfo: Pointer to a structure of type CYBLE_GAP_PRIVACY_MODE_INFO_T
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
<table>
*  <tr>
*    <th>Errors codes</th>
*    <th>Description</th>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_OK</td>
*    <td>On successful operation.</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*    <td>Any of the input parameter is NULL</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_NO_DEVICE_ENTITY</td>
*    <td>When a Controller cannot find device entry in the resolving list</td>
*  </tr>
*  <tr>
*    <td>CYBLE_ERROR_INVALID_OPERATION</td>
*    <td>Request is not permitted when address translation is enabled in the Controller and:
*               * Advertising is enabled
*               * Scanning is enabled
*               * Create connection command is outstanding.
*    </td>
*  </tr>
* </table>
*
******************************************************************************/

CYBLE_API_RESULT_T CyBle_GapSetPrivacyMode
(
	CYBLE_GAP_PRIVACY_MODE_INFO_T *privacyModeInfo
);


/******************************************************************************
* Function Name: CyBle_GapGetBondedDevicesByRank
***************************************************************************//**
*
* This function returns the count and Bluetooth device address along with bd handles of the devices in
* the bonded device list in the order of Rank*. This is a blocking function. No event is generated on
* calling this function.
*
* Rank: Newest device bonded will be at 0 index.
*
* Application invoking this function should allocate sufficient memory for the
* structure CYBLE_GAP_DEVICE_ADDR_LIST_T, where the complete list of bonded
* devices along with count can be written. Maximum devices bonded are specified
* by CYBLE_GAP_MAX_BONDED_DEVICE, which is a pre processing time parameter for
* the BLE Stack. Hence, the bonded device count will be less than or equal to
* CYBLE_GAP_MAX_BONDED_DEVICE.
*
* Refer Bluetooth 4.1 core specification, Volume 3, Part C, section 9.4.4 for
* details on bonded devices.
*   
* \param bondedDevList: Buffer to which list of bonded device list will be stored
*                       of type CYBLE_GAP_DEVICE_ADDR_LIST_T.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                     | Description
*  ------------                     | -----------
*  CYBLE_ERROR_OK                   | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetBondedDevicesByRank(CYBLE_GAP_DEVICE_ADDR_LIST_T	* bondedDevList);

/******************************************************************************
* Function Name: CyBle_GapSetLeEventMask
***************************************************************************//**
*
* The CyBle_GapSetLeEventMask API function is equivalent of LE_Set_Event_Mask HCI command
* and is used to control which LE events are generated by the HCI for the Host.
* Host will process these events and will send appropriate events to application.
* If the bit in the hciLeEventMask is set to a one, then the event 
* associated with that bit will be enabled. The Host has to
* deal with each event that is generated by an LE Controller. The event mask
* allows the application to control which events will be generated for host.
*
* This is a blocking function. No event is generated on calling this function.
*
* \param hciLeEventMask: Pointer to the LE Mask. As of today stack expects 2 bytes length
*         for this buffer (hciLeEventMask)
*         Refer Core Spec, Vol2, Part E, 7.8.1 for further information.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                     | Description
*  ------------                     | -----------
*  CYBLE_ERROR_OK                   | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetLeEventMask (uint8 *hciLeEventMask);

/******************************************************************************
* Function Name: CyBle_GapSetIdAddress
***************************************************************************//**
*
* This function sets the Bluetooth identity address into BLE Stack. Calling to this API function will only change 
* the identity address of the device. If public address or static random address is changed by user, this
* API function needs to be called to set the appropriate address as identity address.
*
* This is a blocking function. No event is generated on calling this function.
*
* \param bdAddr: Pointer to the CYBLE_GAP_BD_ADDR_T structure variable. It has two
*          fields where,
*         * bdAddr.addr: Bluetooth Device address buffer that is populated with
*            the device address data.
*         * bdAddr.type: Caller function should fill the "address type" to
*            set appropriate address.
*         .
*           Caller function should use bdAddr.type = 0x00 to set the "Public
*            Device Address" as identity address. <br>
*           Caller function use bdAddr.type = 0x01 to set the "Static Random 
*            Device Address" as identity address.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
*
*  Errors codes                     | Description
*  ------------                     | -----------
*  CYBLE_ERROR_OK                   | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetIdAddress(const CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
* Function Name: CyBle_GapGenerateAndSetIrk
***************************************************************************//**
* This function generates and sets local Identity resolving key into BLE Stack that is to be exchanged with peer
* device during key exchange stage of authentication procedure. This API function only updates IRK and does not change
* any other keys.
* This is a blocking function. No event is generated on calling this function.
* This API function does not generate identity address (keyInfo->idAddrInfo)
*
* \param keysFlag: (Input parameter) This parameter indicates which keys get exchanged with peer device.
*                  The following is the bit field mapping for the keys.
*             * Bit 0: Local Encryption information
*             * Bit 1: Local Identity information
*             * Bit 2: Local Signature Key
*             * Bit 3: Reserved
*             * Bit 4: Remote Encryption information
*             * Bit 5: Remote Identity information
*             * Bit 6: Remote Signature Key
*             * Bit 7: Reserved
*
* \param irk: (output parameter) Pointer to 16 Bytes buffer where IRK is stored.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
* 
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER        | On specifying NULL as input parameter for 'keyInfo'.
*
******************************************************************************/    
CYBLE_API_RESULT_T CyBle_GapGenerateAndSetIrk(uint8 keysFlag, uint8 *irk);


/******************************************************************************
* Function Name: CyBle_GapFixAuthPassKey
***************************************************************************//**
* Sets or clears fixed passkey to be used by SMP procedure.
* This is a blocking function. No event is generated on calling this function.
* 
* Note1:  The fixed passkey will only work if we are the device displaying the
*         passkey and peer has to enter the passkey.
*         This will not work for numeric comparison(secure connections) method.
*
* Note2:  The fixed passkey is not persistent across power cycle.
*
* Note3:  This API function should not be called during ongoing SMP procedure.
*         Recommendation is to call this API function on Stack Init completion.
*
*
* \param isFixed: isFixed should be true(non zero) and fixedPassKey should be
*                 valid passkey (<=999999) to set the fixed passkey.<br>
*            isFixed should be false(0) to ask SMP to generate random passkey 
*            instead of using the fixed passkey. This is only required if 
*            previously the passkey was fixed using this API function.
*
* \param  fixedPassKey: Valid fixed passkey (<=999999) to be used by SMP. 
*                  This is only used if isFixed is set to true else ignored.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
* 
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER        | If fixedPassKey is not a valid passkey.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapFixAuthPassKey(uint8 isFixed, uint32 fixedPassKey);

/******************************************************************************
* Function Name: CyBle_GappSetNumOfAdvPkts
***************************************************************************//**
* Sets number of advertisement packets to be sent over the air and starts
* Advertisement.
*
*
* Gap Peripheral receives CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP 
* event after specified number of adv packets transmitted successfully.
*
* Note1:  Advertisement Timeout will be ignored.
* Note2:  Ongoing Advertisement should be stopped by the application 
*		  before calling this API function.
*
* \param advInfo: Structure of type CYBLE_GAPP_DISC_MODE_INFO_T, which contains the
*		 		  advertisement parameters
*
* \param  NumOfAdvPkts: (Input parameter) Total number of packets 
* 						to transmitted over the air.
*
* \return
* CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
* failed. Following are the possible error codes.
* 
*  Errors codes                         | Description
*  ------------                         | -----------
*  CYBLE_ERROR_OK                       | On successful operation.
*  CYBLE_ERROR_INVALID_PARAMETER        | If Zero passed
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GappSetNumOfAdvPkts(CYBLE_GAPP_DISC_MODE_INFO_T* advInfo, uint16 NumOfAdvPkts);

/** @} */
#endif /* CYBLE_GAP_H_ */

/*EOF*/
