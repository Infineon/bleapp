/*******************************************************************************
* File Name: red.h  
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

#if !defined(CY_PINS_red_H) /* Pins red_H */
#define CY_PINS_red_H

#include "cytypes.h"
#include "cyfitter.h"
#include "red_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    red_Write(uint8 value) ;
void    red_SetDriveMode(uint8 mode) ;
uint8   red_ReadDataReg(void) ;
uint8   red_Read(void) ;
uint8   red_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define red_DRIVE_MODE_BITS        (3)
#define red_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - red_DRIVE_MODE_BITS))

#define red_DM_ALG_HIZ         (0x00u)
#define red_DM_DIG_HIZ         (0x01u)
#define red_DM_RES_UP          (0x02u)
#define red_DM_RES_DWN         (0x03u)
#define red_DM_OD_LO           (0x04u)
#define red_DM_OD_HI           (0x05u)
#define red_DM_STRONG          (0x06u)
#define red_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define red_MASK               red__MASK
#define red_SHIFT              red__SHIFT
#define red_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define red_PS                     (* (reg32 *) red__PS)
/* Port Configuration */
#define red_PC                     (* (reg32 *) red__PC)
/* Data Register */
#define red_DR                     (* (reg32 *) red__DR)
/* Input Buffer Disable Override */
#define red_INP_DIS                (* (reg32 *) red__PC2)


#if defined(red__INTSTAT)  /* Interrupt Registers */

    #define red_INTSTAT                (* (reg32 *) red__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define red_DRIVE_MODE_SHIFT       (0x00u)
#define red_DRIVE_MODE_MASK        (0x07u << red_DRIVE_MODE_SHIFT)


#endif /* End Pins red_H */


/* [] END OF FILE */
