/***************************************************************************//**
* \file CYBLE_HAL_PVT.c
* \version 3.61
*
* \brief
*  This file contains the source code for the HAL section of the BLE component
*
********************************************************************************
* \copyright
* Copyright 2014-2019, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLE_HAL_PVT.h"


#if(CYBLE_MODE == CYBLE_HCI)


/*******************************************************************************
* Function Name: CyBLE_Uart_Start
****************************************************************************//**
*
*  Enables the platform UART Tx and RX interrupts and then enables the UART
*  component.
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_Uart_Start (void)
{
    #if (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART)
        /* Setup ISR */
        BLE_uart_isr_StartEx(&CyBLE_Uart_Interrupt);

        BLE_HAL_Uart_Start();
    #endif /* (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART) */
}


/*******************************************************************************
* Function Name: CyBLE_Uart_Stop
****************************************************************************//**
*
*  Disables the UART, clears all pending interrupts and disables the UART Tx
*  and RX interrupts. This will also empty out the FIFOs.
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_Uart_Stop (void)
{
    #if (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART)
        /* Stop interrupt and UART */
        BLE_uart_isr_Stop();

        BLE_HAL_Uart_Stop();
    #endif /* (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART) */
}


/*******************************************************************************
* Function Name: CyBLE_Uart_Transmit
****************************************************************************//**
*
*  Sends the data to Uart Tx FIFO. The function handles data length up to the 
*  supported Tx FIFO length of the uart hardware module.
*
*  \param data: Pointer to the data to send through the UART
*  \param length: the length of data to transmit in bytes
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_Uart_Transmit (const uint8 *dataBuf, uint8 length)
{
    #if (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART)
        BLE_HAL_Uart_SpiUartPutArray(dataBuf, (uint32)length);
    #endif /* (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART) */
}

/*******************************************************************************
* Function Name: CyBLE_Uart_Isr_Enable
****************************************************************************//**
*
*   Enables the UART interrupt to the interrupt controller. 
*   Do not call this function unless CyBLE_Uart_Start() has been called or the
*   functionality of the SysInt_Init() function, which sets the vector and the
*   priority, has been called.
*
*******************************************************************************/
void CyBLE_Uart_Isr_Enable(void)
{
    #if (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART)
        BLE_uart_isr_Enable();
    #endif /* (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART) */
}


/*******************************************************************************
* Function Name: CyBLE_Uart_Isr_Disable
****************************************************************************//**
*
*   Disables the UART Interrupt in the interrupt controller.
*
*******************************************************************************/
void CyBLE_Uart_Isr_Disable(void)
{
    #if (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART)
        BLE_uart_isr_Disable();
    #endif /* (CYBLE_HCI_TYPE == CYBLE_HCI_OVER_UART) */
}

#endif /* (CYBLE_MODE == CYBLE_HCI) */


/*******************************************************************************
* Function Name: CyBLE_Nvram_Write
****************************************************************************//**
*
*  This function writes the data to the NVRAM store. It will check the 
*  appropriate alignment of a start address and also perform an address range 
*  check based on the length before performing the write operation.
*  This function performs memory compare and writes only row where there are new
*  data to write.
*
*  \param buffer:   Pointer to the buffer containing the data to be stored.
*  \param varFlash: Pointer to the array or variable in the flash.
*  \param length:    The length of the data in bytes.
*
* \return
*  CYRET_SUCCESS    a successful write
*  CYRET_BAD_PARAM  A request to write outside the flash boundary.
*  CYRET_UNKNOWN    Other errors in writing the flash
*
* \sideeffect
*  For BLE devices with 128K of Flash memory this function will automatically 
*  modify the clock settings for the device.
*  Writing to flash requires changes to be done to the IMO (set to 48 MHz)
*  and HFCLK (source set to IMO) settings. The configuration is restored before
*  returning. This will impact the operation of most of the hardware in the
*  device.
*
*******************************************************************************/
cystatus CyBLE_Nvram_Write (const uint8 buffer[], const uint8 varFlash[], uint16 length)
{
    uint8 writeBuffer[CY_FLASH_SIZEOF_ROW];
    uint32 rowId;
    uint32 dstIndex;
    uint32 srcIndex = 0u;
    cystatus rc = CYRET_SUCCESS;
    uint32 eeOffset;
    uint32 byteOffset;
    uint32 rowsNotEqual;

    eeOffset = (uint32)varFlash;

    /* Make sure, that varFlash[] points to Flash */
    if ((eeOffset + length) < CYBLE_HAL_FLASH_END_ADDR)
    {
        rowId = eeOffset / CY_FLASH_SIZEOF_ROW;
        byteOffset = CY_FLASH_SIZEOF_ROW * rowId;

        while ((srcIndex < length) && (rc == CYRET_SUCCESS))
        {
            rowsNotEqual = 0u;
            /* Copy data to the write buffer either from the source buffer or from the flash */
            for (dstIndex = 0u; dstIndex < CY_FLASH_SIZEOF_ROW; dstIndex++)
            {
                if ((byteOffset >= eeOffset) && (srcIndex < length))
                {
                    writeBuffer[dstIndex] = buffer[srcIndex];
                    /* Detect that row programming is required */
                    if(CY_GET_XTND_REG8(CYDEV_FLASH_BASE + byteOffset) != buffer[srcIndex])
                    {
                        rowsNotEqual = 1u;  
                    }
                    srcIndex++;
                }
                else
                {
                    writeBuffer[dstIndex] = CY_GET_XTND_REG8(CYDEV_FLASH_BASE + byteOffset);
                }
                byteOffset++;
            }

            if(rowsNotEqual != 0u)
            {
                /* Write flash row */
                rc = CySysFlashWriteRow(rowId, writeBuffer);
            }

            /* Go to the next row */
            rowId++;
        }
    }
    else
    {
        rc = CYRET_BAD_PARAM;
    }

    /* Mask return codes from flash, if they are not supported */
    if ((CYRET_SUCCESS != rc) && (CYRET_BAD_PARAM != rc))
    {
        rc = CYRET_UNKNOWN;
    }
    
    return (rc);
}

/*******************************************************************************
* Function Name: CyBLE_Nvram_Erase
****************************************************************************//**
*
*  This function erases the data from the NVRAM store. It will perform an 
*  address range check based on the length before performing erase operation.
*
*  \param varFlash: the pointer to the array or variable in the flash.
*  \param length:    the length of the data in bytes.
*
* \return
*  CYRET_SUCCESS    a successful write
*  CYRET_BAD_PARAM  A request to write outside the flash boundary.
*  CYRET_UNKNOWN    Other errors in writing the flash
*
*******************************************************************************/
cystatus CyBLE_Nvram_Erase (const uint8 *varFlash, uint16 length)
{
    const uint8 *tempFlash;
    uint8 flashBuffer[CY_FLASH_SIZEOF_ROW] = {0u};
    uint16 lengthFlash;
    uint16 lengthRemaining;
    cystatus rc = CYRET_UNKNOWN;

    tempFlash = varFlash;
    lengthRemaining = length;

    while(lengthRemaining > 0u)
    {
        if(lengthRemaining < CY_FLASH_SIZEOF_ROW)
        {
            lengthFlash = lengthRemaining;
        }
        else
        {
            lengthFlash = CY_FLASH_SIZEOF_ROW;
        }
        rc = CyBLE_Nvram_Write(flashBuffer, tempFlash, lengthFlash);
        if(rc != CYRET_SUCCESS)
        {
            break;
        }
        tempFlash += CY_FLASH_SIZEOF_ROW;
        lengthRemaining -= lengthFlash;
    }

    return rc;
}


/*******************************************************************************
* Function Name: CyBLE_Bless_LlRegRead
****************************************************************************//**
*
*  This function reads the content of the BLESS Link Layer register from the 
*  stack.
*
*  \param blessAddr: the pointer to the BLESS link layer address.
*  \param regValue: the pointer to the buffer space to copy the read value.
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_Bless_LlRegRead (const reg32 *blessAddr, uint16 *regValue)
{
    *regValue = (uint16)CY_GET_REG32(blessAddr);
}


/*******************************************************************************
* Function Name: CyBLE_Bless_LlRegWrite
****************************************************************************//**
*
*  This function writes to the BLESS Link Layer register from the stack.
*
*  \param blessAddr: the pointer to the BLESS link layer address.
*  \param regValue: the pointer to the value to be written to the BLESS LL reg.
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_Bless_LlRegWrite (reg32 *blessAddr, const uint16 regValue)
{
    CY_SET_REG32(blessAddr, regValue);
}


/*******************************************************************************
* Function Name: CyBLE_Bless_RfRegRead
****************************************************************************//**
*
*  This function reads the content of the BLESS RF register from the stack.
*
*  \param blessAddr: the pointer to BLESS RF register address.
*  \param regValue: the pointer to the buffer space to copy the read value.
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_Bless_RfRegRead (const reg32 *blessAddr, uint16 *regValue)
{
    *regValue = (uint16)CY_GET_REG32(blessAddr);
}


/*******************************************************************************
* Function Name: CyBLE_Bless_RfRegWrite
****************************************************************************//**
*
*  This function writes to the BLESS RF register from the stack.
*
*  \param blessAddr: the pointer to the BLESS RF address.
*  \param regValue: the pointer to the value to be written to the BLESS RF reg.
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_Bless_RfRegWrite (reg32 *blessAddr, const uint16 regValue)
{
     CY_SET_REG32(blessAddr, regValue);
}

/*******************************************************************************
* Function Name: CyBLE_BlessDeviceConfig
****************************************************************************//**
*
*  This function configures BLESS registers by trimmed values stored in SFLASH.
*
* \return
*  None
*
*******************************************************************************/
void CyBLE_BlessDeviceConfig(void)
{
#if (CYIPBLOCK_m0s8bless_VERSION < 3)
    
    uint32 trimRegValue;
    uint32 ldo;
    uint16 trimRef34Val;
    uint16 trimRef38Val;    
    uint32 siliconRev;

    trimRegValue = ((uint32)CYBLE_SFLASH_BLESS_BB_BUMP2_HIGH_REG << 8u) | CYBLE_SFLASH_BLESS_BB_BUMP2_LOW_REG;
    ldo = ((uint32)CYBLE_SFLASH_BLESS_LDO_HIGH_REG << 8u) | CYBLE_SFLASH_BLESS_LDO_LOW_REG;

    if ((ldo == CYBLE_SFLASH_BLERD_LDO_REG_VAL1) && (trimRegValue == CYBLE_SFLASH_BLERD_BB_BUMP2_REG_VAL1))
    {
        ldo = CYBLE_BLERD_LDO_REG_VAL_FINAL;
        trimRegValue = CYBLE_BLERD_BB_BUMP2_REG_VAL_FINAL;
    }
    else if ((ldo == CYBLE_SFLASH_BLERD_LDO_REG_VAL2) && (trimRegValue == CYBLE_BLERD_BB_BUMP2_REG_VAL_FINAL))
    {
        ldo = CYBLE_BLERD_LDO_REG_VAL_FINAL;
    }
    else
    {
    }

    CYBLE_BLE_BLERD_LDO_REG = ldo;
    CYBLE_BLE_BLERD_BB_BUMP2_REG = trimRegValue;

    /* Edit only XTAL fast charge bit */
    trimRegValue = ((uint32)CYBLE_SFLASH_BLESS_BB_XO_HIGH_REG << 8u) | CYBLE_SFLASH_BLESS_BB_XO_LOW_REG;

    if ((trimRegValue == CYBLE_SFLASH_BLERD_BB_XO_REG_VAL1) || (trimRegValue == CYBLE_SFLASH_BLERD_BB_XO_REG_VAL2))
    {
        trimRegValue = CYBLE_BLERD_BB_XO_REG_VAL_FINAL;
    }
    
    CYBLE_BLE_BLERD_BB_XO_REG = trimRegValue;
    
    trimRegValue = ((uint32)CYBLE_SFLASH_BLESS_SY_BUMP1_HIGH_REG << 8u) | CYBLE_SFLASH_BLESS_SY_BUMP1_LOW_REG;

    if ((trimRegValue == CYBLE_SFLASH_BLERD_SY_BUMP1_REG_VAL1) || 
        (trimRegValue == CYBLE_SFLASH_BLERD_SY_BUMP1_REG_VAL2) ||  
        (trimRegValue == CYBLE_SFLASH_BLERD_SY_BUMP1_REG_VAL3))
    {
        trimRegValue = CYBLE_BLERD_SY_BUMP1_REG_VAL_FINAL;
    }
    CYBLE_BLE_BLERD_SY_BUMP1_REG = trimRegValue;

    /* Following code is for F02FN trimming */
    siliconRev = (CYBLE_BLE_SILICON_REV_REG >> 4u);
    
    if((CYBLE_BLE_FAMILY_ID_REG == CYBLE_PSOC4A_BLE256DMA_FID) && (siliconRev >= 0x02u) &&
        (CYBLE_SFLASH_BLESS_SY_BUMP1_HIGH_REG == 0x0Eu))
	{
		trimRef34Val = ((uint16)(((uint16) CYBLE_BLE_BLESS_REG34_TRIM_HIGH_REG) << 8u)) |
                        ((uint16)CYBLE_BLE_BLESS_REG34_TRIM_LOW_REG);
		CYBLE_BLERD_SY_BUMP2_REG = trimRef34Val;
	
		trimRef38Val = ((uint16)(((uint16)CYBLE_BLE_BLESS_REG38_TRIM_HIGH_REG) << 8u)) |
            ((uint16) CYBLE_BLE_BLESS_REG38_TRIM_LOW_REG);
		CYBLE_BLERD_RX_BUMP2_REG = trimRef38Val;
	}
#endif /* (CYIPBLOCK_m0s8bless_VERSION < 3) */
}


/* Interface to CyDelayUs function */
void CyBleHal_DelayUs(uint16 delayVal)
{
    CyDelayUs(delayVal);
}

/* Interface to CyDelay function */
void CyBleHal_DelayMs(uint32 delayVal)
{
    CyDelay(delayVal);
}

/* Interface to BLE_bless_isr_Enable function */
void CyBleHal_EnableGlobalInterrupts(void)
{
    BLE_bless_isr_Enable();
}

/* Interface to BLE_bless_isr_Disable function */
void CyBleHal_DisableGlobalInterrupts(void)
{
    BLE_bless_isr_Disable();
}

/*******************************************************************************
* Function Name: CyBle_HalInit
****************************************************************************//**
*
*  Initializes the BLESS interrupt.
*
* \return
*  None
*
*******************************************************************************/
void CyBle_HalInit(void)
{
    /* For all we know the interrupt is active. */
    BLE_bless_isr_Disable();

    /* Set the ISR to point to the BLE_bless_isr Interrupt. */
    BLE_bless_isr_SetVector(&CyBLE_Bless_Interrupt);

    /* Set the priority. */
    BLE_bless_isr_SetPriority((uint8)BLE_bless_isr_INTC_PRIOR_NUMBER);
}


/*******************************************************************************
* Function Name: CYBLE_BlessStart
****************************************************************************//**
*
*  Starts Interrupt Controller.
*
* \return
*  None
*
*******************************************************************************/
void CYBLE_BlessStart(void)
{
#if((CYBLE_M0S8BLESS_VERSION_3) && (CYBLE_EXT_PA_ENABLED))
    CYBLE_EXT_PA_LNA_CTRL_REG |= CYBLE_EXT_PA_LNA_ENABLE | CYBLE_EXT_OUT_EN_DRIVE_VAL; 
#endif  /* (CYBLE_M0S8BLESS_VERSION_3) */

    BLE_bless_isr_StartEx(&CyBLE_Bless_Interrupt);
}


/*******************************************************************************
* Function Name: CyBLE_GetIpBlockVersion
****************************************************************************//**
*
* This function returns the version of m0s8bless ip block.
*
* \return
* uint32 bits:
* 7:0 - ip version ( 1 - BLE_ver1, 2 - BLE_ver2, 3 - BLE_ver3 )
* 15:8 - flash size ( 0 - 128k, 1 - 256k )
* 16 - PSVP device
* 31:17 - reserved for future usage
*
*******************************************************************************/
uint32 CyBLE_GetIpBlockVersion(void)
{
    return(((uint32)CYBLE_M0S8BLESS_VERSION) | ((uint32)((uint32)CYBLE_FLASH_SIZE) << 8u) |
        ((uint32)(((uint32)CYBLE_PSVP_DEVICE)) << 16u));
}

/* Mapping functions for stack size optimization */
#if(CYBLE_MODE_PROFILE)
    
#if(CYBLE_SECURE_CONN_FEATURE_ENABLED)
    
    CYBLE_API_RESULT_T CyBle_Hal_pairing_local_public_key_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_local_public_key_handler(param));
    }
     
    CYBLE_API_RESULT_T CyBle_Hal_pairing_remote_key_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_remote_key_handler(param));
    }
     
    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_dhkey_handler(param));
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_check_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_dhkey_check_handler(param));
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_keypress_notification_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_keypress_notification_handler(param));
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_rand_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_rand_handler(param));
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_confirm_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_confirm_handler(param));
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_lr_confirming_handler(void *param)
    {
        return (CyBle_Hal_mapping_pairing_lr_confirming_handler(param));
    }
    
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_tbx_dhkey_generate_complete(void* param)
    {
        CyBle_Hal_mapping_tbx_dhkey_generate_complete(param);
        return (CYBLE_ERROR_OK);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_tbx_local_pubkey_generate_complete(void)
    {
        CyBle_Hal_mapping_tbx_local_pubkey_generate_complete();
        return (CYBLE_ERROR_OK);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_local_P256_public_key(uint8 param)
    {
        return (CyBle_Hal_mapping_generate_local_P256_public_key(param));
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_DHkey(void  * param1, void  * param2)
    {
        return (CyBle_Hal_mapping_generate_DHkey(param1, param2));
    }

    void CyBle_Hal_smp_sc_cmac_complete(void)
    {
       CyBle_Hal_Mapping_smp_sc_cmac_complete();
    }

    CYBLE_API_RESULT_T CyBle_Hal_se_smp_sc_user_passkey_handler(void *param1, void *param2)
    {
        return (CyBle_Hal_mapping_se_smp_sc_user_passkey_handler(param1, param2));
    }

    void CyBle_Hal_EccPointMult(void)
    {
        CyBle_Hal_Mapping_EccPointMult();
    }
    
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_validate_p256_pub_key_pair (void *param1)
    {
        return (CyBle_Hal_mapping_validate_p256_pub_key_pair(param1));
    }
    
    
#else     /* If feature is not required, return error. */
    
    CYBLE_API_RESULT_T CyBle_Hal_pairing_local_public_key_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }
     
    CYBLE_API_RESULT_T CyBle_Hal_pairing_remote_key_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }
     
    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_dhkey_check_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_keypress_notification_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_rand_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }
    
    CYBLE_API_RESULT_T CyBle_Hal_pairing_confirm_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_lr_confirming_handler(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }
    
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_tbx_dhkey_generate_complete(void* param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_tbx_local_pubkey_generate_complete(void)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_local_P256_public_key(uint8 param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_generate_DHkey(void  * param1 CYBLE_UNUSED_ATTR,
                                                               void  * param2 CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    void CyBle_Hal_smp_sc_cmac_complete(void)
    {
    }

    CYBLE_API_RESULT_T CyBle_Hal_se_smp_sc_user_passkey_handler(void  * param1 CYBLE_UNUSED_ATTR,
                                                                void  * param2 CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }

    void CyBle_Hal_EccPointMult(void)
    {
    }
    
    CYBLE_API_RESULT_T CyBle_Hal_pairing_sc_validate_p256_pub_key_pair (void *param1 CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE);
    }
    
#endif /* (CYBLE_SECURE_CONN_FEATURE_ENABLED) */

#endif /* CYBLE_MODE_PROFILE */

#if(CYBLE_SECURE_CONN_FEATURE_ENABLED)
    
    uint16 BLE_CMP_FTR_API_lec_hci_handle_read_local_P256_public_key_command(void *param)
    {
        return (BLE_STK_FTR_API_lec_hci_handle_read_local_P256_public_key_command(param));
    }
    
    uint16 BLE_CMP_FTR_API_lec_hci_handle_generate_DHkey_command(void *param)
    {
        return (BLE_STK_FTR_API_lec_hci_handle_generate_DHkey_command(param));
    }

#else     /* If feature is not required, return error. */
    
    uint16 BLE_CMP_FTR_API_lec_hci_handle_read_local_P256_public_key_command(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_UNKNOWN_HCI_COMMAND_ERROR);
    }
    
    uint16 BLE_CMP_FTR_API_lec_hci_handle_generate_DHkey_command(void *param CYBLE_UNUSED_ATTR)
    {
        return (CYBLE_UNKNOWN_HCI_COMMAND_ERROR);
    }
    
#endif /* CYBLE_SECURE_CONN_FEATURE_ENABLED */

  
/* [] END OF FILE */
