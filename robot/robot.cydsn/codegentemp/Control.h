/*******************************************************************************
* File Name: Control.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Control_H) /* Pins Control_H */
#define CY_PINS_Control_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Control_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Control_Write(uint8 value) ;
void    Control_SetDriveMode(uint8 mode) ;
uint8   Control_ReadDataReg(void) ;
uint8   Control_Read(void) ;
uint8   Control_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Control_DRIVE_MODE_BITS        (3)
#define Control_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Control_DRIVE_MODE_BITS))

#define Control_DM_ALG_HIZ         (0x00u)
#define Control_DM_DIG_HIZ         (0x01u)
#define Control_DM_RES_UP          (0x02u)
#define Control_DM_RES_DWN         (0x03u)
#define Control_DM_OD_LO           (0x04u)
#define Control_DM_OD_HI           (0x05u)
#define Control_DM_STRONG          (0x06u)
#define Control_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Control_MASK               Control__MASK
#define Control_SHIFT              Control__SHIFT
#define Control_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Control_PS                     (* (reg32 *) Control__PS)
/* Port Configuration */
#define Control_PC                     (* (reg32 *) Control__PC)
/* Data Register */
#define Control_DR                     (* (reg32 *) Control__DR)
/* Input Buffer Disable Override */
#define Control_INP_DIS                (* (reg32 *) Control__PC2)


#if defined(Control__INTSTAT)  /* Interrupt Registers */

    #define Control_INTSTAT                (* (reg32 *) Control__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Control_DRIVE_MODE_SHIFT       (0x00u)
#define Control_DRIVE_MODE_MASK        (0x07u << Control_DRIVE_MODE_SHIFT)


#endif /* End Pins Control_H */


/* [] END OF FILE */
