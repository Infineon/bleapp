/***************************************************************************//**
* \file CYBLE_HAL_PVT.h
* \version 2.30
*
* \brief
*  Contains the function prototypes and constants for the HAL section
*  of the BLE component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_BLE_CYBLE_HAL_PVT_H)
#define CY_BLE_CYBLE_HAL_PVT_H

#include "BLE_STACK_PVT.h" 
#include "BLE_bless_isr.h"
#include "BLE.h"    


#if(CYBLE_MODE == CYBLE_HCI)
    #include "BLE_HAL_Uart_SPI_UART.h"
    #include "BLE_uart_isr.h"
#endif /* (CYBLE_MODE == CYBLE_HCI) */


/***************************************
*   HAL API Constants
***************************************/

/* Defines for LDO values */
#define CYBLE_SFLASH_BLERD_LDO_REG_VAL1                         (0x0B58u)
#define CYBLE_SFLASH_BLERD_LDO_REG_VAL2                         (0x0D40u)
#define CYBLE_BLERD_LDO_REG_VAL_FINAL                           (0x0D58u)

/* Defines for BB_BUMP values */
#define CYBLE_SFLASH_BLERD_BB_BUMP2_REG_VAL1                    (0x0007u)
#define CYBLE_BLERD_BB_BUMP2_REG_VAL_FINAL                      (0x0004u)

/* Defines for BB_XO values */
#define CYBLE_SFLASH_BLERD_BB_XO_REG_VAL1                       (0x2000u)
#define CYBLE_SFLASH_BLERD_BB_XO_REG_VAL2                       (0x0000u)
#define CYBLE_BLERD_BB_XO_REG_VAL_FINAL                         (0x2002u)

/* Defines for BB_XO values */
#define CYBLE_SFLASH_BLERD_SY_BUMP1_REG_VAL1                    (0x0F0Fu)
#define CYBLE_SFLASH_BLERD_SY_BUMP1_REG_VAL2                    (0x0505u)
#define CYBLE_SFLASH_BLERD_SY_BUMP1_REG_VAL3                    (0x0005u)
#define CYBLE_BLERD_SY_BUMP1_REG_VAL_FINAL                      (0x0F05u)


#define CYBLE_HAL_FLASH_BASE_ADDR                               (CYDEV_FLASH_BASE)
#define CYBLE_HAL_FLASH_SIZE                                    (CYDEV_FLASH_SIZE)
#define CYBLE_HAL_FLASH_END_ADDR                                (CYBLE_HAL_FLASH_BASE_ADDR + CYBLE_HAL_FLASH_SIZE)

#define CYBLE_HAL_FLASH_ROWS_IN_ARRAY                           (CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW)


/***************************************
*              Registers
***************************************/

/* BLESS Radio Trim registers in the SFLASH */
#define CYBLE_SFLASH_BLESS_BB_BUMP2_LOW_REG                     (* (reg8 *) (CYREG_SFLASH_BLESS_BB_BUMP2))
#define CYBLE_SFLASH_BLESS_BB_BUMP2_HIGH_REG                    (* (reg8 *) (CYREG_SFLASH_BLESS_BB_BUMP2 + 1u))
#define CYBLE_SFLASH_BLESS_BB_XO_LOW_REG                        (* (reg8 *) (CYREG_SFLASH_BLESS_BB_XO))
#define CYBLE_SFLASH_BLESS_BB_XO_HIGH_REG                       (* (reg8 *) (CYREG_SFLASH_BLESS_BB_XO + 1u))
#define CYBLE_SFLASH_BLESS_SY_BUMP1_LOW_REG                     (* (reg8 *) (CYREG_SFLASH_BLESS_SY_BUMP1))
#define CYBLE_SFLASH_BLESS_SY_BUMP1_HIGH_REG                    (* (reg8 *) (CYREG_SFLASH_BLESS_SY_BUMP1 + 1u))
#define CYBLE_SFLASH_BLESS_LDO_LOW_REG                          (* (reg8 *) (CYREG_SFLASH_BLESS_LDO))
#define CYBLE_SFLASH_BLESS_LDO_HIGH_REG                         (* (reg8 *) (CYREG_SFLASH_BLESS_LDO + 1u))

/* BLERD registers */
#define CYBLE_BLE_BLERD_LDO_REG                                 (* (reg32 *) (CYREG_BLE_BLERD_LDO))
#define CYBLE_BLE_BLERD_SY_BUMP1_REG                            (* (reg32 *) (CYREG_BLE_BLERD_SY_BUMP1))
#define CYBLE_BLE_BLERD_BB_BUMP2_REG                            (* (reg32 *) (CYREG_BLE_BLERD_BB_BUMP2))
#define CYBLE_BLE_BLERD_BB_XO_REG                               (* (reg32 *) (CYREG_BLE_BLERD_BB_XO))

/***************************************
*   Function Prototypes
***************************************/

/* HAL ISR prototypes */
CY_ISR_PROTO(CyBLE_Bless_Interrupt);
#if(CYBLE_MODE == CYBLE_HCI)
    CY_ISR_PROTO(CyBLE_Uart_Interrupt);
#endif /* (CYBLE_MODE == CYBLE_HCI) */

void CyBleHal_DelayUs(uint16 delayVal);
void CyBleHal_DelayMs(uint32 delayVal);
void CyBleHal_EnableGlobalInterrupts(void);
void CyBleHal_DisableGlobalInterrupts(void);
void CyBle_HalInit(void);
void CYBLE_BlessStart(void);

cystatus CyBLE_Nvram_Write (const uint8 buffer[], const uint8 varFlash[], uint16 length);
cystatus CyBLE_Nvram_Erase (const uint8 *varFlash, uint16 length);


#endif /* CY_BLE_CYBLE_HAL_PVT_H  */

/* [] END OF FILE */
