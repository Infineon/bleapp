/*******************************************************************************
* File Name: POWERRIGHT.h  
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

#if !defined(CY_PINS_POWERRIGHT_H) /* Pins POWERRIGHT_H */
#define CY_PINS_POWERRIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "POWERRIGHT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    POWERRIGHT_Write(uint8 value) ;
void    POWERRIGHT_SetDriveMode(uint8 mode) ;
uint8   POWERRIGHT_ReadDataReg(void) ;
uint8   POWERRIGHT_Read(void) ;
uint8   POWERRIGHT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define POWERRIGHT_DRIVE_MODE_BITS        (3)
#define POWERRIGHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - POWERRIGHT_DRIVE_MODE_BITS))

#define POWERRIGHT_DM_ALG_HIZ         (0x00u)
#define POWERRIGHT_DM_DIG_HIZ         (0x01u)
#define POWERRIGHT_DM_RES_UP          (0x02u)
#define POWERRIGHT_DM_RES_DWN         (0x03u)
#define POWERRIGHT_DM_OD_LO           (0x04u)
#define POWERRIGHT_DM_OD_HI           (0x05u)
#define POWERRIGHT_DM_STRONG          (0x06u)
#define POWERRIGHT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define POWERRIGHT_MASK               POWERRIGHT__MASK
#define POWERRIGHT_SHIFT              POWERRIGHT__SHIFT
#define POWERRIGHT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define POWERRIGHT_PS                     (* (reg32 *) POWERRIGHT__PS)
/* Port Configuration */
#define POWERRIGHT_PC                     (* (reg32 *) POWERRIGHT__PC)
/* Data Register */
#define POWERRIGHT_DR                     (* (reg32 *) POWERRIGHT__DR)
/* Input Buffer Disable Override */
#define POWERRIGHT_INP_DIS                (* (reg32 *) POWERRIGHT__PC2)


#if defined(POWERRIGHT__INTSTAT)  /* Interrupt Registers */

    #define POWERRIGHT_INTSTAT                (* (reg32 *) POWERRIGHT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define POWERRIGHT_DRIVE_MODE_SHIFT       (0x00u)
#define POWERRIGHT_DRIVE_MODE_MASK        (0x07u << POWERRIGHT_DRIVE_MODE_SHIFT)


#endif /* End Pins POWERRIGHT_H */


/* [] END OF FILE */
