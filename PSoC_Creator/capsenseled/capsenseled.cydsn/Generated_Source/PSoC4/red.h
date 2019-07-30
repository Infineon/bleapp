/*******************************************************************************
* File Name: red.h  
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

#if !defined(CY_PINS_red_H) /* Pins red_H */
#define CY_PINS_red_H

#include "cytypes.h"
#include "cyfitter.h"
#include "red_aliases.h"


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
} red_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   red_Read(void);
void    red_Write(uint8 value);
uint8   red_ReadDataReg(void);
#if defined(red__PC) || (CY_PSOC4_4200L) 
    void    red_SetDriveMode(uint8 mode);
#endif
void    red_SetInterruptMode(uint16 position, uint16 mode);
uint8   red_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void red_Sleep(void); 
void red_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(red__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define red_DRIVE_MODE_BITS        (3)
    #define red_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - red_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the red_SetDriveMode() function.
         *  @{
         */
        #define red_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define red_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define red_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define red_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define red_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define red_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define red_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define red_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define red_MASK               red__MASK
#define red_SHIFT              red__SHIFT
#define red_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in red_SetInterruptMode() function.
     *  @{
     */
        #define red_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define red_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define red_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define red_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(red__SIO)
    #define red_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(red__PC) && (CY_PSOC4_4200L)
    #define red_USBIO_ENABLE               ((uint32)0x80000000u)
    #define red_USBIO_DISABLE              ((uint32)(~red_USBIO_ENABLE))
    #define red_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define red_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define red_USBIO_ENTER_SLEEP          ((uint32)((1u << red_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << red_USBIO_SUSPEND_DEL_SHIFT)))
    #define red_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << red_USBIO_SUSPEND_SHIFT)))
    #define red_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << red_USBIO_SUSPEND_DEL_SHIFT)))
    #define red_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(red__PC)
    /* Port Configuration */
    #define red_PC                 (* (reg32 *) red__PC)
#endif
/* Pin State */
#define red_PS                     (* (reg32 *) red__PS)
/* Data Register */
#define red_DR                     (* (reg32 *) red__DR)
/* Input Buffer Disable Override */
#define red_INP_DIS                (* (reg32 *) red__PC2)

/* Interrupt configuration Registers */
#define red_INTCFG                 (* (reg32 *) red__INTCFG)
#define red_INTSTAT                (* (reg32 *) red__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define red_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(red__SIO)
    #define red_SIO_REG            (* (reg32 *) red__SIO)
#endif /* (red__SIO_CFG) */

/* USBIO registers */
#if !defined(red__PC) && (CY_PSOC4_4200L)
    #define red_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define red_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define red_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define red_DRIVE_MODE_SHIFT       (0x00u)
#define red_DRIVE_MODE_MASK        (0x07u << red_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins red_H */


/* [] END OF FILE */
