/*******************************************************************************
* File Name: POWERLEFT.h  
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

#if !defined(CY_PINS_POWERLEFT_H) /* Pins POWERLEFT_H */
#define CY_PINS_POWERLEFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "POWERLEFT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    POWERLEFT_Write(uint8 value) ;
void    POWERLEFT_SetDriveMode(uint8 mode) ;
uint8   POWERLEFT_ReadDataReg(void) ;
uint8   POWERLEFT_Read(void) ;
uint8   POWERLEFT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define POWERLEFT_DRIVE_MODE_BITS        (3)
#define POWERLEFT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - POWERLEFT_DRIVE_MODE_BITS))

#define POWERLEFT_DM_ALG_HIZ         (0x00u)
#define POWERLEFT_DM_DIG_HIZ         (0x01u)
#define POWERLEFT_DM_RES_UP          (0x02u)
#define POWERLEFT_DM_RES_DWN         (0x03u)
#define POWERLEFT_DM_OD_LO           (0x04u)
#define POWERLEFT_DM_OD_HI           (0x05u)
#define POWERLEFT_DM_STRONG          (0x06u)
#define POWERLEFT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define POWERLEFT_MASK               POWERLEFT__MASK
#define POWERLEFT_SHIFT              POWERLEFT__SHIFT
#define POWERLEFT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define POWERLEFT_PS                     (* (reg32 *) POWERLEFT__PS)
/* Port Configuration */
#define POWERLEFT_PC                     (* (reg32 *) POWERLEFT__PC)
/* Data Register */
#define POWERLEFT_DR                     (* (reg32 *) POWERLEFT__DR)
/* Input Buffer Disable Override */
#define POWERLEFT_INP_DIS                (* (reg32 *) POWERLEFT__PC2)


#if defined(POWERLEFT__INTSTAT)  /* Interrupt Registers */

    #define POWERLEFT_INTSTAT                (* (reg32 *) POWERLEFT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define POWERLEFT_DRIVE_MODE_SHIFT       (0x00u)
#define POWERLEFT_DRIVE_MODE_MASK        (0x07u << POWERLEFT_DRIVE_MODE_SHIFT)


#endif /* End Pins POWERLEFT_H */


/* [] END OF FILE */
