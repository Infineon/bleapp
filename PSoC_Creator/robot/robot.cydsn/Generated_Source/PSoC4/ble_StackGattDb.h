/***************************************************************************//**
* \file CYBLE_StackGattDb.h
* \version 2.30
* 
* \brief
*  This file contains the data structure for GATT Database
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


#ifndef CY_BLE_CYBLE_STACK_GATT_DB_H
#define CY_BLE_CYBLE_STACK_GATT_DB_H

    
/***************************************
* Common stack includes
***************************************/

#include "cytypes.h"
    
    
/***************************************
* Macro Definition
***************************************/

/* GATT Defined Attributes */
#define CYBLE_GATT_PRIMARY_SERVICE                  0x2800u
#define CYBLE_GATT_SECONDARY_SERVICE                0x2801u
#define CYBLE_GATT_INCLUDE_SERVICE                  0x2802u
#define CYBLE_GATT_CHARACTERISTIC                   0x2803u
#define CYBLE_GATT_EXTENDED_PROPERTIES              0x2900u
#define CYBLE_GATT_USER_DESCRIPTION                 0x2901u
#define CYBLE_GATT_CLIENT_CONFIG                    0x2902u
#define CYBLE_GATT_SERVER_CONFIG                    0x2903u
#define CYBLE_GATT_PRESENTATION_FORMAT              0x2904u
#define CYBLE_GATT_AGGREGATE_FORMAT                 0x2905u


#define CYBLE_GATT_GAP_SERVICE_UUID                 0x1800u

/* GATT Database Properties Field Description
    1. Attribute permissions <B0>: Bluetooth Spec Defined
    2. Characteristic permissions <B1>: Bluetooth Spec Defined
    3. <B2>, <B3>Implementation Specific */

/* Attribute permissions <B0>: Bluetooth Spec Defined */
#define CYBLE_GATT_DB_ATTR_PROP_READ                0x01u
#define CYBLE_GATT_DB_ATTR_PROP_WRITE               0x02u
#define CYBLE_GATT_DB_ATTR_PROP_RD_WR               0x04u
#define CYBLE_GATT_DB_ATTR_PROP_SEC_ENCRYPT         0x08u
#define CYBLE_GATT_DB_ATTR_PROP_SEC_AUTHENTICATE    0x10u
#define CYBLE_GATT_DB_ATTR_PROP_SEC_AUTHORIZE       0x20u

    
#define CYBLE_GATT_DB_ATTR_PROP_MASK                0x000000FFu
    
#define CYBLE_GATT_DB_ATTR_PROP_BIT_SHIFT           0x0u
    
#define CYBLE_GATT_DB_SECURITY_MASK                 0x38u

#define CYBLE_GATT_DB_SECURITY_BIT_SHIFT            0x3u

/* Characteristic permissions <B1>: Bluetooth Spec Defined */
#define CYBLE_GATT_DB_CH_PROP_BROADCAST             0x0100u
#define CYBLE_GATT_DB_CH_PROP_READ                  0x0200u
#define CYBLE_GATT_DB_CH_PROP_RD_WRITE_WO_RESP      0x0400u
#define CYBLE_GATT_DB_CH_PROP_WRITE                 0x0800u
#define CYBLE_GATT_DB_CH_PROP_NOTIFY                0x1000u
#define CYBLE_GATT_DB_CH_PROP_INDICATE              0x2000u
#define CYBLE_GATT_DB_CH_PROP_SEC_AUTH_SIGNED_WRITE 0x4000u
#define CYBLE_GATT_DB_CH_PROP_EXT_PROP              0x8000u

#define CYBLE_GATT_DB_CHAR_PROP_MASK                0x0000FF00u
#define CYBLE_GATT_DB_CHAR_PROP_BIT_SHIFT           0x8u

/* Extended properties values. Note: These properties are not
   part of permission field. The peer GATT layer or local GATT
   layer needs to read "Characteristic Extended Properties 
   Descriptor" value. */
#define CYBLE_GATT_DB_CH_PROP_EXT_PROP_RELIABLE_WRITE   0x0001u
#define CYBLE_GATT_DB_CH_PROP_EXT_PROP_WRITABLE_AUX     0x0002u

/* Implementation permissions <B2>: Implementation specific
   defines to access runtime characteristics. */

/* Bit: */
#define CYBLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT        0x010000u
#define CYBLE_GATT_DB_ATTR_UUID_FMT_32           	0x040000u
#define CYBLE_GATT_DB_ATTR_UUID_FMT_128            	0x080000u

/* Encryption Key Size 7 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_7                 0x100000u

/* Encryption Key Size 8 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_8                 0x200000u

/* Encryption Key Size 9 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_9                 0x300000u

/* Encryption Key Size 10 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_10                0x400000u

/* Encryption Key Size 11 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_11                0x500000u

/* Encryption Key Size 12 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_12                0x600000u

/* Encryption Key Size 13 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_13                0x700000u

/* Encryption Key Size 14 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_14                0x800000u

/* Encryption Key Size 15 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_15                0x900000u

/* Encryption Key Size 16 Needed for the Service */
#define CYBLE_GATT_DB_SER_ENCRYPT_KEY_SIZE_16                0xA00000u

/* No Encryption Needed for the Service */
#define CYBLE_GATT_DB_SER_NO_ENCRYPT_PROPERTY                0x000000u

/*  Encryption Key Size Mask Needed for the Service */
#define CYBLE_GATT_DB_ENC_KEY_SIZE_MASK                      0x00F00000u


/* By default entries in CYBLE_GATT DB is 16-bit UUID
   This mask is defined to decide UUID length */
#define CYBLE_GATT_DB_ATTR_UUID_FMT_16_MASK       0x030000u

/* Implementation permission <B3>: Table index of runtime 
   configurable characteristic */
#define CYBLE_GATT_DB_CONFIGURABLE_LUT_ID_MASK    0xFF000000u


/* CYBLE_GATT Client Configuration values */
#define CYBLE_GATT_CLI_CNFG_NOTIFICATION         0x0001u
#define CYBLE_GATT_CLI_CNFG_INDICATION           0x0002u
#define CYBLE_GATT_CLI_CNFG_DEFAULT              0x0000u

/* Unit size is with respect to word (16 bit) */
#define CYBLE_GATT_DB_128_BIT_UUID_SZ                  16u
#define CYBLE_GATT_DB_32_BIT_UUID_SZ                   4u
#define CYBLE_GATT_DB_16_BIT_UUID_SZ                   2u

#define CYBLE_GATT_DB_ATTR_16_BIT_UUID           0u
#define CYBLE_GATT_DB_ATTR_32_BIT_UUID           1u
#define CYBLE_GATT_DB_ATTR_128_BIT_UUID          2u


#define CYBLE_GATT_DB_ATTR_PRPTY_SZ              0x01u
#define CYBLE_GATT_DB_ATTR_HANDLE_SZ             0x02u
 

/* Locally initiated operation, needed for local updates based on Attribute
    Handles. */
#define CYBLE_GATT_DB_LOCALLY_INITIATED               0x00u

/* Peer Initiated GATT DB transaction */
#define CYBLE_GATT_DB_PEER_INITIATED                  0x40u   

/* Read operation for Attribute  */
#define CYBLE_GATT_DB_READ                            CYBLE_GATT_DB_ATTR_PROP_READ

/* Write operation for Attribute */
#define CYBLE_GATT_DB_WRITE                           CYBLE_GATT_DB_ATTR_PROP_WRITE
    
/** Prepare Write operation for Attribute */
#define CYBLE_GATT_DB_PREP_WRITE                      0x04u
    
#define CYBLE_GATT_DB_WRITE_WITHOUT_RSP               0x80u

/**
 \addtogroup group_common_api_gatt_definitions
 @{
*/

/***************************************
* Data Struct Definition
***************************************/

/** Attribute value type used in GATT database */
typedef struct
{
    /** Length in number of bytes for attGenericVal */
    uint16 actualLength;

    /** Buffer to the store generic characteristic value based on
       length or complete UUID value if the attribute is of type 128-bit
       UUID and 32-bit UUID type. */
       void * attGenericVal;

}CYBLE_GATTS_ATT_GEN_VAL_LEN_T;

/** Attribute value type used in GATT database */
typedef struct
{
    /** Length in number of bytes for attGenericVal */
    uint16 maxAttrLength;

    /** Buffer to the store generic characteristic value based on
       length or complete UUID value if the attribute is of type 128-bit
       UUID and 32-bit UUID type. */
    CYBLE_GATTS_ATT_GEN_VAL_LEN_T * attGenericValLen;

}CYBLE_GATTS_ATT_PACK_VAL_LEN_T;

/* Attribute value type used in GATT database */
typedef union
{    
  /* Buffer containing 32-bit or 128-bit UUID values for Service and
      Characteristic declaration.
      Attribute format structure: if entry is for characteristic value format, 
      then it has the "attribute format value" of pointer type to represent generic
      structure to cater wide formats of available list of characteristic formats. */
	CYBLE_GATTS_ATT_PACK_VAL_LEN_T  	attFormatValue;

	/* Attribute UUID value */
	uint16 				attValueUuid;

} CYBLE_GATTS_ATT_VALUE_T;

/** GATT database structure used in the GAP Server */
typedef struct
{
	/** Start Handle: Act as an index for querying BLE GATT database */
    uint16 				attHandle;
	
    /** UUID: 16 bit UUID type for an attribute entry, for 32 bit and
       128 bit UUIDs the last 16 bits should be stored in this entry
       GATT DB access layer shall retrieve complete 128 bit UUID from
       CYBLE_GATTS_ATT_GENERIC_VAL_T structure. */
    uint16 				attType;
	
    /** The permission bits are clubbed in to a 32-bit field. These 
        32-bits can be grouped in to 4 bytes. The lowest significant byte
        is byte 0 (B0) and the most significant byte is byte 3 (B3). The 
        bytes where the permissions have been grouped is as given below.
	     * Attribute permissions (B0)
         * Characteristic permissions (B1)
         * Implementation specific permission (B3, B2)
	 */
    uint32 				permission;
	
    /** Attribute end handle, indicating logical boundary of given attribute. */
    uint16 				attEndHandle;
	
    /** Attribute value format, it can be one of following:
        * uint16 16bit - UUID for 16bit service & characteristic declaration
        * CYBLE_GATTS_ATT_GENERIC_VAL_T attFormatValue - Buffer containing 32 bit
            or 128 bit UUID values for service & charactertistic declaration
        * CYBLE_GATTS_ATT_GENERIC_VAL_T attFormatValue - Buffer contraining generic 
            char definition value, or generic descriptor values
     */
	CYBLE_GATTS_ATT_VALUE_T 	attValue;
 } CYBLE_GATTS_DB_T; 

/** @} */

/***************************************
* Characteristic Descriptors definitions
***************************************/

/* All descriptors follow the characteristic value definition entries that belong
   to a logical group of characteristics shall be in following order:
    1. Characteristic Declaration 
    2. Characteristic Value
    3. Characteristic Extended Property (If any)
    4. Characteristic User Description  (If any)
    5. Client Characteristic configuration  (If any)
    6. Server Characteristic configuration (If any)
    7. Characteristic Presentation format (If any)
    8. Characteristic Aggregate format (If any)
 */
typedef CYBLE_GATTS_ATT_VALUE_T      CYBLE_CHAR_EXT_PRPRTY_T;
typedef CYBLE_GATTS_ATT_VALUE_T      CYBLE_CHAR_USER_DESCRIPTION_T;
typedef CYBLE_GATTS_ATT_VALUE_T      CYBLE_CLIENT_CHAR_CONFIG_T;
typedef CYBLE_GATTS_ATT_VALUE_T      CYBLE_SERVER_CHAR_CONFIG_T;
typedef CYBLE_GATTS_ATT_VALUE_T      CYBLE_CHAR_PRESENT_FMT_T;
typedef CYBLE_GATTS_ATT_VALUE_T      CYBLE_CHAR_AGGREGATE_FMT_T;

/**
 \addtogroup group_common_api_gatt_server_functions
 @{
*/

/***************************************
* APIs
***************************************/

/******************************************************************************
* Function Name: CyBle_GattsDbRegister
***************************************************************************//**
* 
*  This function registers the GATT database for the GATT Server. The GATT 
*  database stores all the attributes used by the GATT server, along with their
*  permissions. This is a blocking function. No event is generated on calling
*  this function.
* 
*  \param gattDbPtr: Pointer to the GATT database of type CYBLE_GATTS_DB_T.
*  \param gattDbTotalEntries: Total number of entries in the GATT database.
*  \param gattDbMaxValue: Maximum characteristic value length
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                      | Description
*  ------------                      | -----------
*   CYBLE_ERROR_OK                   | On successful operation
*   CYBLE_ERROR_INVALID_PARAMETER    | If the Database has zero entries or is a NULL pointer
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattsDbRegister
			(
				const CYBLE_GATTS_DB_T* gattDbPtr,
				uint16 gattDbTotalEntries,
				uint16 gattDbMaxValue
			);


/******************************************************************************
* Function Name: CyBle_GattsWriteAttributeValue
***************************************************************************//**
* 
*  This function is used to write to the value field of the specified attribute
*  in the GATT database of a GATT Server. This is a blocking function. No event
*  is generated on calling this function.
* 
*  If a peer device connected to the GATT Server initiates a write operation, 
*  this function is executed on the GATT Server. During such a call, the function
*  checks for the attribute permissions (flags) before executing the write 
*  operation.
* 
* \param handleValuePair: Pointer to handle value pair of type 
*                  CYBLE_GATT_HANDLE_VALUE_PAIR_T.
*                   * 'handleValuePair.attrHandle' is an input for which value 
*                      has to be written.
*                   * 'handleValuePair.value.len' is an input parameter for the 
*                      length to be written.
*                   * 'handleValuePair.value.val' is an input parameter for 
*                      data buffer.
*                   * 'handleValuePair.actualLen' has to be ignored as it is 
*                      unused in this function.
* \param offset: Offset at which the data (length in number of bytes) is written.
* \param connHandle: Pointer to the attribute instance handle, of type 
*              CYBLE_CONN_HANDLE_T.
* \param falgs: Attribute permissions. Allowed values are,
*         * CYBLE_GATT_DB_LOCALLY_INITIATED
*         * CYBLE_GATT_DB_PEER_INITIATED
* 
* \return
*  CYBLE_GATT_ERR_CODE_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_GATT_ERR_NONE                  | On successful operation
*   CYBLE_GATT_ERR_INVALID_HANDLE        | 'handleValuePair.attrHandle' is not valid
*   CYBLE_GATT_ERR_WRITE_NOT_PERMITTED   | Write operation is not permitted on this attribute
*   CYBLE_GATT_ERR_INVALID_OFFSET        | Offset value is invalid
*   CYBLE_GATT_ERR_UNLIKELY_ERROR        | Some other error occurred
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsWriteAttributeValue
		(
            CYBLE_GATT_HANDLE_VALUE_PAIR_T	* handleValuePair,
            uint16                          offset,
            CYBLE_CONN_HANDLE_T       		* connHandle,
            uint8                           flags
		);


/******************************************************************************
* Function Name: CyBle_GattsReadAttributeValue
***************************************************************************//**
* 
*  This function is used to read the value field of the specified attribute from
*  the GATT database in a GATT Server. This is a blocking function. No event is
*  generated on calling this function.
* 
*  Peer initiated call to this function results in the function checking for
*  attribute permissions before performing this operation.
*     
*  \param handleValuePair: Pointer to handle value pair of type 
*                    CYBLE_GATT_HANDLE_VALUE_PAIR_T.
*                     * 'handleValuePair.attrHandle' is an input for which value
*                        has to be read.
*                     * 'handleValuePair.value.len' is an input parameter, the
*                        characteristic value is read based on length.
*                     * 'handleValuePair.value.val' is an output parameter for 
*                        data buffer.
*                     * 'handleValuePair.actualLen' has to be ignored as it is 
*                        unused in this function.
*  \param connHandle: Pointer to the attribute instance handle, of type
*               CYBLE_CONN_HANDLE_T. connHandle can be NULL if flags field 
*               is set to CYBLE_GATT_DB_LOCALLY_INITIATED.
*  \param flags: Attribute permissions. Allowed values are,
*          * CYBLE_GATT_DB_LOCALLY_INITIATED
*          * CYBLE_GATT_DB_PEER_INITIATED
* 
* \return
*  CYBLE_GATT_ERR_CODE_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                          | Description
*  ------------                          | -----------
*   CYBLE_GATT_ERR_NONE                  | On successful operation
*   CYBLE_GATT_ERR_INVALID_HANDLE        | 'handleValuePair.attrHandle' is not valid
*   CYBLE_GATT_ERR_READ_NOT_PERMITTED    | Read operation is not permitted on this attribute
*   CYBLE_GATT_ERR_UNLIKELY_ERROR        | Invalid arguments passed
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsReadAttributeValue
		(
			CYBLE_GATT_HANDLE_VALUE_PAIR_T* handleValuePair,
            CYBLE_CONN_HANDLE_T*            connHandle,
            uint8                           flags
		);


/******************************************************************************
* Function Name: CyBle_GattsEnableAttribute
***************************************************************************//**
* 
*  This function enables the attribute entry for service or characteristic
*  logical group in the GATT database registered in BLE Stack. This is a
*  blocking function. No event is generated on calling this function.
* 
*  This function returns an error if the attribute does not belong to any 
*  service or characteristic logical group. If the attribute entry is already
*  enabled, then this function returns status CYBLE_GATT_ERR_NONE.
* 
*  \param attrHandle: Attribute handle of the registered GATT Database to enable
*               particular attribute entry, of type 
*               CYBLE_GATT_DB_ATTR_HANDLE_T.
* 
* \return
*  CYBLE_GATT_ERR_CODE_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                      | Description
*  ------------                      | -----------
*   CYBLE_GATT_ERR_NONE              | On successful operation
*   CYBLE_GATT_ERR_INVALID_HANDLE    | 'attrHandle' is not valid
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsEnableAttribute
(
    CYBLE_GATT_DB_ATTR_HANDLE_T    attrHandle
);


/******************************************************************************
* Function Name: CyBle_GattsDisableAttribute
***************************************************************************//**
* 
*  This function disables the attribute entry for service or characteristic
*  logical group in the GATT database registered in the BLE Stack. This is
*  a blocking function. No event is generated on calling this function.
* 
*  This function returns error if the attribute does not belong to a service or
*  a characteristic logical group. If attribute entry is already disabled then
*  it returns CYBLE_GATT_ERR_NONE as status. All the attribute entries are
*  enabled in GATT database during stack initialization.
* 
*  \param attrHandle: Attribute handle of the registered GATT Database to disable
*               particular attribute entry, of type 
*               'CYBLE_GATT_DB_ATTR_HANDLE_T'
* 
* \return
*  CYBLE_GATT_ERR_CODE_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                      | Description
*  ------------                      | -----------
*   CYBLE_GATT_ERR_NONE              | On successful operation
*   CYBLE_GATT_ERR_INVALID_HANDLE    | 'attrHandle' is not valid
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsDisableAttribute
(
    CYBLE_GATT_DB_ATTR_HANDLE_T    attrHandle
);


/******************************************************************************
* Function Name: CyBle_GattsDbAuthorize
***************************************************************************//**
* 
*  This Function sets or clears authorization permission for the GATT database
* 
*  \param yesNo : Setting this to '0' turns off authorization on the entire GATT database
* 			and all attributes marked as authorize will return authorization error.
* 			Setting this to any non-zero value will authorize the entire GATT
* 			database and all attributes marked as authorize can be read / written
* 			based on other allowed permissions.
* 
* \return
*  CYBLE_GATT_ERR_CODE_T : Return value indicates if the function succeeded or
*  failed. Following are the possible error codes.
*
*  Errors codes                      | Description
*  ------------                      | -----------
*   CYBLE_GATT_ERR_NONE              | On successful operation
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsDbAuthorize(uint8 yesNo);


/** \cond IGNORE */
/* Cypress ID 219999 */
/* This API validates the security permission for the given attribute
 * handle index */
CYBLE_GATT_ERR_CODE_T CyBle_GattDbCheckPermission
           (
               CYBLE_GATT_DB_ATTR_HANDLE_T  attrhandle,
               CYBLE_CONN_HANDLE_T*         connHandle,
               uint8                        flags
           );
/** \endcond */

        
/** @} */
	
#endif /*CY_BLE_CYBLE_STACK_GATT_DB_H*/


/*EOF*/
