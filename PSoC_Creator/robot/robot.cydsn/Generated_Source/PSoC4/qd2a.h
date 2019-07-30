/*******************************************************************************
* File Name: qd2a.h  
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

#if !defined(CY_PINS_qd2a_H) /* Pins qd2a_H */
#define CY_PINS_qd2a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "qd2a_aliases.h"


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
} qd2a_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   qd2a_Read(void);
void    qd2a_Write(uint8 value);
uint8   qd2a_ReadDataReg(void);
#if defined(qd2a__PC) || (CY_PSOC4_4200L) 
    void    qd2a_SetDriveMode(uint8 mode);
#endif
void    qd2a_SetInterruptMode(uint16 position, uint16 mode);
uint8   qd2a_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void qd2a_Sleep(void); 
void qd2a_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(qd2a__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define qd2a_DRIVE_MODE_BITS        (3)
    #define qd2a_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - qd2a_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the qd2a_SetDriveMode() function.
         *  @{
         */
        #define qd2a_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define qd2a_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define qd2a_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define qd2a_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define qd2a_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define qd2a_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define qd2a_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define qd2a_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define qd2a_MASK               qd2a__MASK
#define qd2a_SHIFT              qd2a__SHIFT
#define qd2a_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in qd2a_SetInterruptMode() function.
     *  @{
     */
        #define qd2a_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define qd2a_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define qd2a_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define qd2a_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(qd2a__SIO)
    #define qd2a_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(qd2a__PC) && (CY_PSOC4_4200L)
    #define qd2a_USBIO_ENABLE               ((uint32)0x80000000u)
    #define qd2a_USBIO_DISABLE              ((uint32)(~qd2a_USBIO_ENABLE))
    #define qd2a_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define qd2a_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define qd2a_USBIO_ENTER_SLEEP          ((uint32)((1u << qd2a_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << qd2a_USBIO_SUSPEND_DEL_SHIFT)))
    #define qd2a_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << qd2a_USBIO_SUSPEND_SHIFT)))
    #define qd2a_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << qd2a_USBIO_SUSPEND_DEL_SHIFT)))
    #define qd2a_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(qd2a__PC)
    /* Port Configuration */
    #define qd2a_PC                 (* (reg32 *) qd2a__PC)
#endif
/* Pin State */
#define qd2a_PS                     (* (reg32 *) qd2a__PS)
/* Data Register */
#define qd2a_DR                     (* (reg32 *) qd2a__DR)
/* Input Buffer Disable Override */
#define qd2a_INP_DIS                (* (reg32 *) qd2a__PC2)

/* Interrupt configuration Registers */
#define qd2a_INTCFG                 (* (reg32 *) qd2a__INTCFG)
#define qd2a_INTSTAT                (* (reg32 *) qd2a__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define qd2a_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(qd2a__SIO)
    #define qd2a_SIO_REG            (* (reg32 *) qd2a__SIO)
#endif /* (qd2a__SIO_CFG) */

/* USBIO registers */
#if !defined(qd2a__PC) && (CY_PSOC4_4200L)
    #define qd2a_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define qd2a_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define qd2a_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define qd2a_DRIVE_MODE_SHIFT       (0x00u)
#define qd2a_DRIVE_MODE_MASK        (0x07u << qd2a_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins qd2a_H */


/* [] END OF FILE */
