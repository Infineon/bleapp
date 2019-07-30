/*******************************************************************************
* File Name: DIRLEFT.h  
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

#if !defined(CY_PINS_DIRLEFT_H) /* Pins DIRLEFT_H */
#define CY_PINS_DIRLEFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIRLEFT_aliases.h"


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
} DIRLEFT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DIRLEFT_Read(void);
void    DIRLEFT_Write(uint8 value);
uint8   DIRLEFT_ReadDataReg(void);
#if defined(DIRLEFT__PC) || (CY_PSOC4_4200L) 
    void    DIRLEFT_SetDriveMode(uint8 mode);
#endif
void    DIRLEFT_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIRLEFT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DIRLEFT_Sleep(void); 
void DIRLEFT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DIRLEFT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DIRLEFT_DRIVE_MODE_BITS        (3)
    #define DIRLEFT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIRLEFT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DIRLEFT_SetDriveMode() function.
         *  @{
         */
        #define DIRLEFT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DIRLEFT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DIRLEFT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DIRLEFT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DIRLEFT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DIRLEFT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DIRLEFT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DIRLEFT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DIRLEFT_MASK               DIRLEFT__MASK
#define DIRLEFT_SHIFT              DIRLEFT__SHIFT
#define DIRLEFT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIRLEFT_SetInterruptMode() function.
     *  @{
     */
        #define DIRLEFT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DIRLEFT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DIRLEFT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DIRLEFT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DIRLEFT__SIO)
    #define DIRLEFT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DIRLEFT__PC) && (CY_PSOC4_4200L)
    #define DIRLEFT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DIRLEFT_USBIO_DISABLE              ((uint32)(~DIRLEFT_USBIO_ENABLE))
    #define DIRLEFT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DIRLEFT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DIRLEFT_USBIO_ENTER_SLEEP          ((uint32)((1u << DIRLEFT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DIRLEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIRLEFT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DIRLEFT_USBIO_SUSPEND_SHIFT)))
    #define DIRLEFT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DIRLEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIRLEFT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DIRLEFT__PC)
    /* Port Configuration */
    #define DIRLEFT_PC                 (* (reg32 *) DIRLEFT__PC)
#endif
/* Pin State */
#define DIRLEFT_PS                     (* (reg32 *) DIRLEFT__PS)
/* Data Register */
#define DIRLEFT_DR                     (* (reg32 *) DIRLEFT__DR)
/* Input Buffer Disable Override */
#define DIRLEFT_INP_DIS                (* (reg32 *) DIRLEFT__PC2)

/* Interrupt configuration Registers */
#define DIRLEFT_INTCFG                 (* (reg32 *) DIRLEFT__INTCFG)
#define DIRLEFT_INTSTAT                (* (reg32 *) DIRLEFT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DIRLEFT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DIRLEFT__SIO)
    #define DIRLEFT_SIO_REG            (* (reg32 *) DIRLEFT__SIO)
#endif /* (DIRLEFT__SIO_CFG) */

/* USBIO registers */
#if !defined(DIRLEFT__PC) && (CY_PSOC4_4200L)
    #define DIRLEFT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DIRLEFT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DIRLEFT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DIRLEFT_DRIVE_MODE_SHIFT       (0x00u)
#define DIRLEFT_DRIVE_MODE_MASK        (0x07u << DIRLEFT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DIRLEFT_H */


/* [] END OF FILE */
