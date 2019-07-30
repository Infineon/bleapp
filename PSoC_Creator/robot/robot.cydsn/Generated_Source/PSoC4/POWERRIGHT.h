/*******************************************************************************
* File Name: POWERRIGHT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_POWERRIGHT_H) /* Pins POWERRIGHT_H */
#define CY_PINS_POWERRIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "POWERRIGHT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} POWERRIGHT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   POWERRIGHT_Read(void);
void    POWERRIGHT_Write(uint8 value);
uint8   POWERRIGHT_ReadDataReg(void);
#if defined(POWERRIGHT__PC) || (CY_PSOC4_4200L) 
    void    POWERRIGHT_SetDriveMode(uint8 mode);
#endif
void    POWERRIGHT_SetInterruptMode(uint16 position, uint16 mode);
uint8   POWERRIGHT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void POWERRIGHT_Sleep(void); 
void POWERRIGHT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(POWERRIGHT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define POWERRIGHT_DRIVE_MODE_BITS        (3)
    #define POWERRIGHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - POWERRIGHT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the POWERRIGHT_SetDriveMode() function.
         *  @{
         */
        #define POWERRIGHT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define POWERRIGHT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define POWERRIGHT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define POWERRIGHT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define POWERRIGHT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define POWERRIGHT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define POWERRIGHT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define POWERRIGHT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define POWERRIGHT_MASK               POWERRIGHT__MASK
#define POWERRIGHT_SHIFT              POWERRIGHT__SHIFT
#define POWERRIGHT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in POWERRIGHT_SetInterruptMode() function.
     *  @{
     */
        #define POWERRIGHT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define POWERRIGHT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define POWERRIGHT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define POWERRIGHT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(POWERRIGHT__SIO)
    #define POWERRIGHT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(POWERRIGHT__PC) && (CY_PSOC4_4200L)
    #define POWERRIGHT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define POWERRIGHT_USBIO_DISABLE              ((uint32)(~POWERRIGHT_USBIO_ENABLE))
    #define POWERRIGHT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define POWERRIGHT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define POWERRIGHT_USBIO_ENTER_SLEEP          ((uint32)((1u << POWERRIGHT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << POWERRIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define POWERRIGHT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << POWERRIGHT_USBIO_SUSPEND_SHIFT)))
    #define POWERRIGHT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << POWERRIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define POWERRIGHT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(POWERRIGHT__PC)
    /* Port Configuration */
    #define POWERRIGHT_PC                 (* (reg32 *) POWERRIGHT__PC)
#endif
/* Pin State */
#define POWERRIGHT_PS                     (* (reg32 *) POWERRIGHT__PS)
/* Data Register */
#define POWERRIGHT_DR                     (* (reg32 *) POWERRIGHT__DR)
/* Input Buffer Disable Override */
#define POWERRIGHT_INP_DIS                (* (reg32 *) POWERRIGHT__PC2)

/* Interrupt configuration Registers */
#define POWERRIGHT_INTCFG                 (* (reg32 *) POWERRIGHT__INTCFG)
#define POWERRIGHT_INTSTAT                (* (reg32 *) POWERRIGHT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define POWERRIGHT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(POWERRIGHT__SIO)
    #define POWERRIGHT_SIO_REG            (* (reg32 *) POWERRIGHT__SIO)
#endif /* (POWERRIGHT__SIO_CFG) */

/* USBIO registers */
#if !defined(POWERRIGHT__PC) && (CY_PSOC4_4200L)
    #define POWERRIGHT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define POWERRIGHT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define POWERRIGHT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define POWERRIGHT_DRIVE_MODE_SHIFT       (0x00u)
#define POWERRIGHT_DRIVE_MODE_MASK        (0x07u << POWERRIGHT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins POWERRIGHT_H */


/* [] END OF FILE */
