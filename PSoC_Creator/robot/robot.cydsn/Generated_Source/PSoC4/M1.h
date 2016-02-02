/*******************************************************************************
* File Name: M1.h  
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

#if !defined(CY_PINS_M1_H) /* Pins M1_H */
#define CY_PINS_M1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "M1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    M1_Write(uint8 value) ;
void    M1_SetDriveMode(uint8 mode) ;
uint8   M1_ReadDataReg(void) ;
uint8   M1_Read(void) ;
uint8   M1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M1_DRIVE_MODE_BITS        (3)
#define M1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - M1_DRIVE_MODE_BITS))

#define M1_DM_ALG_HIZ         (0x00u)
#define M1_DM_DIG_HIZ         (0x01u)
#define M1_DM_RES_UP          (0x02u)
#define M1_DM_RES_DWN         (0x03u)
#define M1_DM_OD_LO           (0x04u)
#define M1_DM_OD_HI           (0x05u)
#define M1_DM_STRONG          (0x06u)
#define M1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define M1_MASK               M1__MASK
#define M1_SHIFT              M1__SHIFT
#define M1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M1_PS                     (* (reg32 *) M1__PS)
/* Port Configuration */
#define M1_PC                     (* (reg32 *) M1__PC)
/* Data Register */
#define M1_DR                     (* (reg32 *) M1__DR)
/* Input Buffer Disable Override */
#define M1_INP_DIS                (* (reg32 *) M1__PC2)


#if defined(M1__INTSTAT)  /* Interrupt Registers */

    #define M1_INTSTAT                (* (reg32 *) M1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define M1_DRIVE_MODE_SHIFT       (0x00u)
#define M1_DRIVE_MODE_MASK        (0x07u << M1_DRIVE_MODE_SHIFT)


#endif /* End Pins M1_H */


/* [] END OF FILE */
