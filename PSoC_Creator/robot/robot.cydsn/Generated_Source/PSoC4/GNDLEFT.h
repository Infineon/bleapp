/*******************************************************************************
* File Name: GNDLEFT.h  
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

#if !defined(CY_PINS_GNDLEFT_H) /* Pins GNDLEFT_H */
#define CY_PINS_GNDLEFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GNDLEFT_aliases.h"


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
} GNDLEFT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   GNDLEFT_Read(void);
void    GNDLEFT_Write(uint8 value);
uint8   GNDLEFT_ReadDataReg(void);
#if defined(GNDLEFT__PC) || (CY_PSOC4_4200L) 
    void    GNDLEFT_SetDriveMode(uint8 mode);
#endif
void    GNDLEFT_SetInterruptMode(uint16 position, uint16 mode);
uint8   GNDLEFT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void GNDLEFT_Sleep(void); 
void GNDLEFT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(GNDLEFT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define GNDLEFT_DRIVE_MODE_BITS        (3)
    #define GNDLEFT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GNDLEFT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the GNDLEFT_SetDriveMode() function.
         *  @{
         */
        #define GNDLEFT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define GNDLEFT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define GNDLEFT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define GNDLEFT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define GNDLEFT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define GNDLEFT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define GNDLEFT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define GNDLEFT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define GNDLEFT_MASK               GNDLEFT__MASK
#define GNDLEFT_SHIFT              GNDLEFT__SHIFT
#define GNDLEFT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GNDLEFT_SetInterruptMode() function.
     *  @{
     */
        #define GNDLEFT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define GNDLEFT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define GNDLEFT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define GNDLEFT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(GNDLEFT__SIO)
    #define GNDLEFT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(GNDLEFT__PC) && (CY_PSOC4_4200L)
    #define GNDLEFT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define GNDLEFT_USBIO_DISABLE              ((uint32)(~GNDLEFT_USBIO_ENABLE))
    #define GNDLEFT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define GNDLEFT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define GNDLEFT_USBIO_ENTER_SLEEP          ((uint32)((1u << GNDLEFT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << GNDLEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define GNDLEFT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << GNDLEFT_USBIO_SUSPEND_SHIFT)))
    #define GNDLEFT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << GNDLEFT_USBIO_SUSPEND_DEL_SHIFT)))
    #define GNDLEFT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(GNDLEFT__PC)
    /* Port Configuration */
    #define GNDLEFT_PC                 (* (reg32 *) GNDLEFT__PC)
#endif
/* Pin State */
#define GNDLEFT_PS                     (* (reg32 *) GNDLEFT__PS)
/* Data Register */
#define GNDLEFT_DR                     (* (reg32 *) GNDLEFT__DR)
/* Input Buffer Disable Override */
#define GNDLEFT_INP_DIS                (* (reg32 *) GNDLEFT__PC2)

/* Interrupt configuration Registers */
#define GNDLEFT_INTCFG                 (* (reg32 *) GNDLEFT__INTCFG)
#define GNDLEFT_INTSTAT                (* (reg32 *) GNDLEFT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define GNDLEFT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(GNDLEFT__SIO)
    #define GNDLEFT_SIO_REG            (* (reg32 *) GNDLEFT__SIO)
#endif /* (GNDLEFT__SIO_CFG) */

/* USBIO registers */
#if !defined(GNDLEFT__PC) && (CY_PSOC4_4200L)
    #define GNDLEFT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define GNDLEFT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define GNDLEFT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define GNDLEFT_DRIVE_MODE_SHIFT       (0x00u)
#define GNDLEFT_DRIVE_MODE_MASK        (0x07u << GNDLEFT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins GNDLEFT_H */


/* [] END OF FILE */
