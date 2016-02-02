/*******************************************************************************
* File Name: blue.h  
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

#if !defined(CY_PINS_blue_H) /* Pins blue_H */
#define CY_PINS_blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "blue_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    blue_Write(uint8 value) ;
void    blue_SetDriveMode(uint8 mode) ;
uint8   blue_ReadDataReg(void) ;
uint8   blue_Read(void) ;
uint8   blue_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define blue_DRIVE_MODE_BITS        (3)
#define blue_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - blue_DRIVE_MODE_BITS))

#define blue_DM_ALG_HIZ         (0x00u)
#define blue_DM_DIG_HIZ         (0x01u)
#define blue_DM_RES_UP          (0x02u)
#define blue_DM_RES_DWN         (0x03u)
#define blue_DM_OD_LO           (0x04u)
#define blue_DM_OD_HI           (0x05u)
#define blue_DM_STRONG          (0x06u)
#define blue_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define blue_MASK               blue__MASK
#define blue_SHIFT              blue__SHIFT
#define blue_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define blue_PS                     (* (reg32 *) blue__PS)
/* Port Configuration */
#define blue_PC                     (* (reg32 *) blue__PC)
/* Data Register */
#define blue_DR                     (* (reg32 *) blue__DR)
/* Input Buffer Disable Override */
#define blue_INP_DIS                (* (reg32 *) blue__PC2)


#if defined(blue__INTSTAT)  /* Interrupt Registers */

    #define blue_INTSTAT                (* (reg32 *) blue__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define blue_DRIVE_MODE_SHIFT       (0x00u)
#define blue_DRIVE_MODE_MASK        (0x07u << blue_DRIVE_MODE_SHIFT)


#endif /* End Pins blue_H */


/* [] END OF FILE */
