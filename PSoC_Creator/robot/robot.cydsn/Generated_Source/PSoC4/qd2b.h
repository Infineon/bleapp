/*******************************************************************************
* File Name: qd2b.h  
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

#if !defined(CY_PINS_qd2b_H) /* Pins qd2b_H */
#define CY_PINS_qd2b_H

#include "cytypes.h"
#include "cyfitter.h"
#include "qd2b_aliases.h"


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
} qd2b_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   qd2b_Read(void);
void    qd2b_Write(uint8 value);
uint8   qd2b_ReadDataReg(void);
#if defined(qd2b__PC) || (CY_PSOC4_4200L) 
    void    qd2b_SetDriveMode(uint8 mode);
#endif
void    qd2b_SetInterruptMode(uint16 position, uint16 mode);
uint8   qd2b_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void qd2b_Sleep(void); 
void qd2b_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(qd2b__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define qd2b_DRIVE_MODE_BITS        (3)
    #define qd2b_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - qd2b_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the qd2b_SetDriveMode() function.
         *  @{
         */
        #define qd2b_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define qd2b_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define qd2b_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define qd2b_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define qd2b_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define qd2b_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define qd2b_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define qd2b_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define qd2b_MASK               qd2b__MASK
#define qd2b_SHIFT              qd2b__SHIFT
#define qd2b_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in qd2b_SetInterruptMode() function.
     *  @{
     */
        #define qd2b_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define qd2b_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define qd2b_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define qd2b_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(qd2b__SIO)
    #define qd2b_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(qd2b__PC) && (CY_PSOC4_4200L)
    #define qd2b_USBIO_ENABLE               ((uint32)0x80000000u)
    #define qd2b_USBIO_DISABLE              ((uint32)(~qd2b_USBIO_ENABLE))
    #define qd2b_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define qd2b_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define qd2b_USBIO_ENTER_SLEEP          ((uint32)((1u << qd2b_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << qd2b_USBIO_SUSPEND_DEL_SHIFT)))
    #define qd2b_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << qd2b_USBIO_SUSPEND_SHIFT)))
    #define qd2b_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << qd2b_USBIO_SUSPEND_DEL_SHIFT)))
    #define qd2b_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(qd2b__PC)
    /* Port Configuration */
    #define qd2b_PC                 (* (reg32 *) qd2b__PC)
#endif
/* Pin State */
#define qd2b_PS                     (* (reg32 *) qd2b__PS)
/* Data Register */
#define qd2b_DR                     (* (reg32 *) qd2b__DR)
/* Input Buffer Disable Override */
#define qd2b_INP_DIS                (* (reg32 *) qd2b__PC2)

/* Interrupt configuration Registers */
#define qd2b_INTCFG                 (* (reg32 *) qd2b__INTCFG)
#define qd2b_INTSTAT                (* (reg32 *) qd2b__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define qd2b_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(qd2b__SIO)
    #define qd2b_SIO_REG            (* (reg32 *) qd2b__SIO)
#endif /* (qd2b__SIO_CFG) */

/* USBIO registers */
#if !defined(qd2b__PC) && (CY_PSOC4_4200L)
    #define qd2b_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define qd2b_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define qd2b_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define qd2b_DRIVE_MODE_SHIFT       (0x00u)
#define qd2b_DRIVE_MODE_MASK        (0x07u << qd2b_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins qd2b_H */


/* [] END OF FILE */
