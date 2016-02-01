/*******************************************************************************
* File Name: DIRRIGHT.h  
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

#if !defined(CY_PINS_DIRRIGHT_H) /* Pins DIRRIGHT_H */
#define CY_PINS_DIRRIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIRRIGHT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DIRRIGHT_Write(uint8 value) ;
void    DIRRIGHT_SetDriveMode(uint8 mode) ;
uint8   DIRRIGHT_ReadDataReg(void) ;
uint8   DIRRIGHT_Read(void) ;
uint8   DIRRIGHT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DIRRIGHT_DRIVE_MODE_BITS        (3)
#define DIRRIGHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIRRIGHT_DRIVE_MODE_BITS))

#define DIRRIGHT_DM_ALG_HIZ         (0x00u)
#define DIRRIGHT_DM_DIG_HIZ         (0x01u)
#define DIRRIGHT_DM_RES_UP          (0x02u)
#define DIRRIGHT_DM_RES_DWN         (0x03u)
#define DIRRIGHT_DM_OD_LO           (0x04u)
#define DIRRIGHT_DM_OD_HI           (0x05u)
#define DIRRIGHT_DM_STRONG          (0x06u)
#define DIRRIGHT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define DIRRIGHT_MASK               DIRRIGHT__MASK
#define DIRRIGHT_SHIFT              DIRRIGHT__SHIFT
#define DIRRIGHT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIRRIGHT_PS                     (* (reg32 *) DIRRIGHT__PS)
/* Port Configuration */
#define DIRRIGHT_PC                     (* (reg32 *) DIRRIGHT__PC)
/* Data Register */
#define DIRRIGHT_DR                     (* (reg32 *) DIRRIGHT__DR)
/* Input Buffer Disable Override */
#define DIRRIGHT_INP_DIS                (* (reg32 *) DIRRIGHT__PC2)


#if defined(DIRRIGHT__INTSTAT)  /* Interrupt Registers */

    #define DIRRIGHT_INTSTAT                (* (reg32 *) DIRRIGHT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define DIRRIGHT_DRIVE_MODE_SHIFT       (0x00u)
#define DIRRIGHT_DRIVE_MODE_MASK        (0x07u << DIRRIGHT_DRIVE_MODE_SHIFT)


#endif /* End Pins DIRRIGHT_H */


/* [] END OF FILE */
