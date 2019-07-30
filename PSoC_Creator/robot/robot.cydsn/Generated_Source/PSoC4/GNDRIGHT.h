/*******************************************************************************
* File Name: GNDRIGHT.h  
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

#if !defined(CY_PINS_GNDRIGHT_H) /* Pins GNDRIGHT_H */
#define CY_PINS_GNDRIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GNDRIGHT_aliases.h"


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
} GNDRIGHT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   GNDRIGHT_Read(void);
void    GNDRIGHT_Write(uint8 value);
uint8   GNDRIGHT_ReadDataReg(void);
#if defined(GNDRIGHT__PC) || (CY_PSOC4_4200L) 
    void    GNDRIGHT_SetDriveMode(uint8 mode);
#endif
void    GNDRIGHT_SetInterruptMode(uint16 position, uint16 mode);
uint8   GNDRIGHT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void GNDRIGHT_Sleep(void); 
void GNDRIGHT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(GNDRIGHT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define GNDRIGHT_DRIVE_MODE_BITS        (3)
    #define GNDRIGHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GNDRIGHT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the GNDRIGHT_SetDriveMode() function.
         *  @{
         */
        #define GNDRIGHT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define GNDRIGHT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define GNDRIGHT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define GNDRIGHT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define GNDRIGHT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define GNDRIGHT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define GNDRIGHT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define GNDRIGHT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define GNDRIGHT_MASK               GNDRIGHT__MASK
#define GNDRIGHT_SHIFT              GNDRIGHT__SHIFT
#define GNDRIGHT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GNDRIGHT_SetInterruptMode() function.
     *  @{
     */
        #define GNDRIGHT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define GNDRIGHT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define GNDRIGHT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define GNDRIGHT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(GNDRIGHT__SIO)
    #define GNDRIGHT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(GNDRIGHT__PC) && (CY_PSOC4_4200L)
    #define GNDRIGHT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define GNDRIGHT_USBIO_DISABLE              ((uint32)(~GNDRIGHT_USBIO_ENABLE))
    #define GNDRIGHT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define GNDRIGHT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define GNDRIGHT_USBIO_ENTER_SLEEP          ((uint32)((1u << GNDRIGHT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << GNDRIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define GNDRIGHT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << GNDRIGHT_USBIO_SUSPEND_SHIFT)))
    #define GNDRIGHT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << GNDRIGHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define GNDRIGHT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(GNDRIGHT__PC)
    /* Port Configuration */
    #define GNDRIGHT_PC                 (* (reg32 *) GNDRIGHT__PC)
#endif
/* Pin State */
#define GNDRIGHT_PS                     (* (reg32 *) GNDRIGHT__PS)
/* Data Register */
#define GNDRIGHT_DR                     (* (reg32 *) GNDRIGHT__DR)
/* Input Buffer Disable Override */
#define GNDRIGHT_INP_DIS                (* (reg32 *) GNDRIGHT__PC2)

/* Interrupt configuration Registers */
#define GNDRIGHT_INTCFG                 (* (reg32 *) GNDRIGHT__INTCFG)
#define GNDRIGHT_INTSTAT                (* (reg32 *) GNDRIGHT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define GNDRIGHT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(GNDRIGHT__SIO)
    #define GNDRIGHT_SIO_REG            (* (reg32 *) GNDRIGHT__SIO)
#endif /* (GNDRIGHT__SIO_CFG) */

/* USBIO registers */
#if !defined(GNDRIGHT__PC) && (CY_PSOC4_4200L)
    #define GNDRIGHT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define GNDRIGHT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define GNDRIGHT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define GNDRIGHT_DRIVE_MODE_SHIFT       (0x00u)
#define GNDRIGHT_DRIVE_MODE_MASK        (0x07u << GNDRIGHT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins GNDRIGHT_H */


/* [] END OF FILE */
