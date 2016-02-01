/*******************************************************************************
* File Name: M2.h  
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

#if !defined(CY_PINS_M2_H) /* Pins M2_H */
#define CY_PINS_M2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "M2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    M2_Write(uint8 value) ;
void    M2_SetDriveMode(uint8 mode) ;
uint8   M2_ReadDataReg(void) ;
uint8   M2_Read(void) ;
uint8   M2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M2_DRIVE_MODE_BITS        (3)
#define M2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - M2_DRIVE_MODE_BITS))

#define M2_DM_ALG_HIZ         (0x00u)
#define M2_DM_DIG_HIZ         (0x01u)
#define M2_DM_RES_UP          (0x02u)
#define M2_DM_RES_DWN         (0x03u)
#define M2_DM_OD_LO           (0x04u)
#define M2_DM_OD_HI           (0x05u)
#define M2_DM_STRONG          (0x06u)
#define M2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define M2_MASK               M2__MASK
#define M2_SHIFT              M2__SHIFT
#define M2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M2_PS                     (* (reg32 *) M2__PS)
/* Port Configuration */
#define M2_PC                     (* (reg32 *) M2__PC)
/* Data Register */
#define M2_DR                     (* (reg32 *) M2__DR)
/* Input Buffer Disable Override */
#define M2_INP_DIS                (* (reg32 *) M2__PC2)


#if defined(M2__INTSTAT)  /* Interrupt Registers */

    #define M2_INTSTAT                (* (reg32 *) M2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define M2_DRIVE_MODE_SHIFT       (0x00u)
#define M2_DRIVE_MODE_MASK        (0x07u << M2_DRIVE_MODE_SHIFT)


#endif /* End Pins M2_H */


/* [] END OF FILE */
