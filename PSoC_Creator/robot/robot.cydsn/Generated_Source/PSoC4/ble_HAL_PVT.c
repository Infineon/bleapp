/***************************************************************************//**
* \file CYBLE_HAL_PVT.c
* \version 2.30
*
* \brief
*  This file contains the source code for the HAL section of the BLE component
*
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
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
    /* Setup ISR */
    BLE_uart_isr_StartEx(&CyBLE_Uart_Interrupt);

    BLE_HAL_Uart_Start();
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
    /* Stop interrupt and UART */
    BLE_uart_isr_Stop();

    BLE_HAL_Uart_Stop();
}


/*******************************************************************************
* Function Name: CyBLE_Uart_Transmit
****************************************************************************//**
*
*  Sends the data to Uart Tx FIFO. The API handles data length up to the 
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
    BLE_HAL_Uart_SpiUartPutArray(dataBuf, (uint32)length);
}

#endif /* (CYBLE_MODE == CYBLE_HCI) */


/*******************************************************************************
* Function Name: CyBLE_Nvram_Write
****************************************************************************//**
*
*  This API writes the data to the NVRAM store. It will check the appropriate
*  alignment of a start address and also perform an address range check based
*  on the length before performing the write operation.
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
*  For BLE devices with 128K of Flash memory this API will automatically 
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

        while ((srcIndex < length) && (CYRET_SUCCESS == rc))
        {
            rowsNotEqual = 0u;
            /* Copy data to the write buffer either from the source buffer or from the flash */
            for (dstIndex = 0u; dstIndex < CY_FLASH_SIZEOF_ROW; dstIndex++)
            {
                if ((byteOffset >= eeOffset) && (srcIndex < length))
                {
                    /* Detect that row programming is required */
                    if(writeBuffer[dstIndex] != buffer[srcIndex])
                    {
                        writeBuffer[dstIndex] = buffer[srcIndex];
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
*  This API erases the data from the NVRAM store. This API will perform an 
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
*  This API reads the content of the BLESS Link Layer register from the stack.
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
*  This API writes to the BLESS Link Layer register from the stack.
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
*  This API reads the content of the BLESS RF register from the stack.
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
*  This API writes to the BLESS RF register from the stack.
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


void CyBLE_BlessDeviceConfig(void)
{
    uint32 trimRegValue;
    uint32 ldo;

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
      
}


void CyBleHal_DelayUs(uint16 delayVal)
{
    CyDelayUs(delayVal);
}

void CyBleHal_DelayMs(uint32 delayVal)
{
    CyDelay(delayVal);
}

void CyBleHal_EnableGlobalInterrupts(void)
{
    BLE_bless_isr_Enable();
}

void CyBleHal_DisableGlobalInterrupts(void)
{
    BLE_bless_isr_Disable();
}

void CyBle_HalInit(void)
{
    /* For all we know the interrupt is active. */
    BLE_bless_isr_Disable();

    /* Set the ISR to point to the BLE_bless_isr Interrupt. */
    BLE_bless_isr_SetVector(&CyBLE_Bless_Interrupt);

    /* Set the priority. */
    BLE_bless_isr_SetPriority((uint8)BLE_bless_isr_INTC_PRIOR_NUMBER);
}

/* Start Interrupt Controller API. */
void CYBLE_BlessStart(void)
{
    BLE_bless_isr_StartEx(&CyBLE_Bless_Interrupt);
}


/* [] END OF FILE */
