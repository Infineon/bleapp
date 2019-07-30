/*******************************************************************************
* File Name: blue.h  
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

#if !defined(CY_PINS_blue_H) /* Pins blue_H */
#define CY_PINS_blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "blue_aliases.h"


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
} blue_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   blue_Read(void);
void    blue_Write(uint8 value);
uint8   blue_ReadDataReg(void);
#if defined(blue__PC) || (CY_PSOC4_4200L) 
    void    blue_SetDriveMode(uint8 mode);
#endif
void    blue_SetInterruptMode(uint16 position, uint16 mode);
uint8   blue_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void blue_Sleep(void); 
void blue_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(blue__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define blue_DRIVE_MODE_BITS        (3)
    #define blue_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - blue_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the blue_SetDriveMode() function.
         *  @{
         */
        #define blue_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define blue_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define blue_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define blue_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define blue_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define blue_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define blue_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define blue_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define blue_MASK               blue__MASK
#define blue_SHIFT              blue__SHIFT
#define blue_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in blue_SetInterruptMode() function.
     *  @{
     */
        #define blue_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define blue_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define blue_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define blue_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(blue__SIO)
    #define blue_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(blue__PC) && (CY_PSOC4_4200L)
    #define blue_USBIO_ENABLE               ((uint32)0x80000000u)
    #define blue_USBIO_DISABLE              ((uint32)(~blue_USBIO_ENABLE))
    #define blue_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define blue_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define blue_USBIO_ENTER_SLEEP          ((uint32)((1u << blue_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << blue_USBIO_SUSPEND_DEL_SHIFT)))
    #define blue_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << blue_USBIO_SUSPEND_SHIFT)))
    #define blue_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << blue_USBIO_SUSPEND_DEL_SHIFT)))
    #define blue_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(blue__PC)
    /* Port Configuration */
    #define blue_PC                 (* (reg32 *) blue__PC)
#endif
/* Pin State */
#define blue_PS                     (* (reg32 *) blue__PS)
/* Data Register */
#define blue_DR                     (* (reg32 *) blue__DR)
/* Input Buffer Disable Override */
#define blue_INP_DIS                (* (reg32 *) blue__PC2)

/* Interrupt configuration Registers */
#define blue_INTCFG                 (* (reg32 *) blue__INTCFG)
#define blue_INTSTAT                (* (reg32 *) blue__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define blue_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(blue__SIO)
    #define blue_SIO_REG            (* (reg32 *) blue__SIO)
#endif /* (blue__SIO_CFG) */

/* USBIO registers */
#if !defined(blue__PC) && (CY_PSOC4_4200L)
    #define blue_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define blue_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define blue_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define blue_DRIVE_MODE_SHIFT       (0x00u)
#define blue_DRIVE_MODE_MASK        (0x07u << blue_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins blue_H */


/* [] END OF FILE */
