/*******************************************************************************
* File Name: DIRRIGHT.h  
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

#if !defined(CY_PINS_DIRRIGHT_H) /* Pins DIRRIGHT_H */
#define CY_PINS_DIRRIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIRRIGHT_aliases.h"


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
} DIRRIGHT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DIRRIGHT_Read(void);
void    DIRRIGHT_Write(uint8 value);
uint8   DIRRIGHT_ReadDataReg(void);
#if defined(DIRRIGHT__PC) || (CY_PSOC4_4200L) 
    void    DIRRIGHT_SetDriveMode(uint8 mode);
#endif
void    DIRRIGHT_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIRRIGHT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DIRRIGHT_Sleep(void); 
void DIRRIGHT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DIRRIGHT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DIRRIGHT_DRIVE_MODE_BITS        (3)
    #define DIRRIGHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIRRIGHT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DIRRIGHT_SetDriveMode() function.
         *  @{
         */
        #define DIRRIGHT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DIRRIGHT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DIRRIGHT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DIRRIGHT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DIRRIGHT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DIRRIGHT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DIRRIGHT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DIRRIGHT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DIRRIGHT_MASK               DIRRIGHT__MASK
#define DIRRIGHT_SHIFT              DIRRIGHT__SHIFT
#define DIRRIGHT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIRRIGHT_SetInterruptMode() function.
     *  @{
     */
        #define DIRRIGHT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DIRRIGHT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DIRRIGHT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DIRRIGHT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DIRRIGHT__SIO)
    #define DIRRIGHT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DIRRIGHT__PC) && (CY_PSOC4_4200L)
    #define DIRRIGHT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DIRRIGHT_USBIO_DISABLE              ((uint32)(~DIRRIGHT_USBIO_ENABLE))
    #define DIRRIGHT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DIRRIGHT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DIRRIGHT_USBIO_ENTER_SLEEP          ((uint32)((1u << DIRRIGHT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DIRRIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIRRIGHT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DIRRIGHT_USBIO_SUSPEND_SHIFT)))
    #define DIRRIGHT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DIRRIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIRRIGHT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DIRRIGHT__PC)
    /* Port Configuration */
    #define DIRRIGHT_PC                 (* (reg32 *) DIRRIGHT__PC)
#endif
/* Pin State */
#define DIRRIGHT_PS                     (* (reg32 *) DIRRIGHT__PS)
/* Data Register */
#define DIRRIGHT_DR                     (* (reg32 *) DIRRIGHT__DR)
/* Input Buffer Disable Override */
#define DIRRIGHT_INP_DIS                (* (reg32 *) DIRRIGHT__PC2)

/* Interrupt configuration Registers */
#define DIRRIGHT_INTCFG                 (* (reg32 *) DIRRIGHT__INTCFG)
#define DIRRIGHT_INTSTAT                (* (reg32 *) DIRRIGHT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DIRRIGHT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DIRRIGHT__SIO)
    #define DIRRIGHT_SIO_REG            (* (reg32 *) DIRRIGHT__SIO)
#endif /* (DIRRIGHT__SIO_CFG) */

/* USBIO registers */
#if !defined(DIRRIGHT__PC) && (CY_PSOC4_4200L)
    #define DIRRIGHT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DIRRIGHT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DIRRIGHT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DIRRIGHT_DRIVE_MODE_SHIFT       (0x00u)
#define DIRRIGHT_DRIVE_MODE_MASK        (0x07u << DIRRIGHT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DIRRIGHT_H */


/* [] END OF FILE */
