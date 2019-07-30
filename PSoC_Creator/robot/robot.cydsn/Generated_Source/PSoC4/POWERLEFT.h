/*******************************************************************************
* File Name: POWERLEFT.h  
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

#if !defined(CY_PINS_POWERLEFT_H) /* Pins POWERLEFT_H */
#define CY_PINS_POWERLEFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "POWERLEFT_aliases.h"


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
} POWERLEFT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   POWERLEFT_Read(void);
void    POWERLEFT_Write(uint8 value);
uint8   POWERLEFT_ReadDataReg(void);
#if defined(POWERLEFT__PC) || (CY_PSOC4_4200L) 
    void    POWERLEFT_SetDriveMode(uint8 mode);
#endif
void    POWERLEFT_SetInterruptMode(uint16 position, uint16 mode);
uint8   POWERLEFT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void POWERLEFT_Sleep(void); 
void POWERLEFT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(POWERLEFT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define POWERLEFT_DRIVE_MODE_BITS        (3)
    #define POWERLEFT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - POWERLEFT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the POWERLEFT_SetDriveMode() function.
         *  @{
         */
        #define POWERLEFT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define POWERLEFT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define POWERLEFT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define POWERLEFT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define POWERLEFT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define POWERLEFT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define POWERLEFT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define POWERLEFT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define POWERLEFT_MASK               POWERLEFT__MASK
#define POWERLEFT_SHIFT              POWERLEFT__SHIFT
#define POWERLEFT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in POWERLEFT_SetInterruptMode() function.
     *  @{
     */
        #define POWERLEFT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define POWERLEFT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define POWERLEFT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define POWERLEFT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(POWERLEFT__SIO)
    #define POWERLEFT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(POWERLEFT__PC) && (CY_PSOC4_4200L)
    #define POWERLEFT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define POWERLEFT_USBIO_DISABLE              ((uint32)(~POWERLEFT_USBIO_ENABLE))
    #define POWERLEFT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define POWERLEFT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define POWERLEFT_USBIO_ENTER_SLEEP          ((uint32)((1u << POWERLEFT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << POWERLEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define POWERLEFT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << POWERLEFT_USBIO_SUSPEND_SHIFT)))
    #define POWERLEFT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << POWERLEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define POWERLEFT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(POWERLEFT__PC)
    /* Port Configuration */
    #define POWERLEFT_PC                 (* (reg32 *) POWERLEFT__PC)
#endif
/* Pin State */
#define POWERLEFT_PS                     (* (reg32 *) POWERLEFT__PS)
/* Data Register */
#define POWERLEFT_DR                     (* (reg32 *) POWERLEFT__DR)
/* Input Buffer Disable Override */
#define POWERLEFT_INP_DIS                (* (reg32 *) POWERLEFT__PC2)

/* Interrupt configuration Registers */
#define POWERLEFT_INTCFG                 (* (reg32 *) POWERLEFT__INTCFG)
#define POWERLEFT_INTSTAT                (* (reg32 *) POWERLEFT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define POWERLEFT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(POWERLEFT__SIO)
    #define POWERLEFT_SIO_REG            (* (reg32 *) POWERLEFT__SIO)
#endif /* (POWERLEFT__SIO_CFG) */

/* USBIO registers */
#if !defined(POWERLEFT__PC) && (CY_PSOC4_4200L)
    #define POWERLEFT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define POWERLEFT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define POWERLEFT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define POWERLEFT_DRIVE_MODE_SHIFT       (0x00u)
#define POWERLEFT_DRIVE_MODE_MASK        (0x07u << POWERLEFT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins POWERLEFT_H */


/* [] END OF FILE */
