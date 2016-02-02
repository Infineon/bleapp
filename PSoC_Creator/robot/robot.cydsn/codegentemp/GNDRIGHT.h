/*******************************************************************************
* File Name: GNDRIGHT.h  
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

#if !defined(CY_PINS_GNDRIGHT_H) /* Pins GNDRIGHT_H */
#define CY_PINS_GNDRIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GNDRIGHT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GNDRIGHT_Write(uint8 value) ;
void    GNDRIGHT_SetDriveMode(uint8 mode) ;
uint8   GNDRIGHT_ReadDataReg(void) ;
uint8   GNDRIGHT_Read(void) ;
uint8   GNDRIGHT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GNDRIGHT_DRIVE_MODE_BITS        (3)
#define GNDRIGHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GNDRIGHT_DRIVE_MODE_BITS))

#define GNDRIGHT_DM_ALG_HIZ         (0x00u)
#define GNDRIGHT_DM_DIG_HIZ         (0x01u)
#define GNDRIGHT_DM_RES_UP          (0x02u)
#define GNDRIGHT_DM_RES_DWN         (0x03u)
#define GNDRIGHT_DM_OD_LO           (0x04u)
#define GNDRIGHT_DM_OD_HI           (0x05u)
#define GNDRIGHT_DM_STRONG          (0x06u)
#define GNDRIGHT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define GNDRIGHT_MASK               GNDRIGHT__MASK
#define GNDRIGHT_SHIFT              GNDRIGHT__SHIFT
#define GNDRIGHT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GNDRIGHT_PS                     (* (reg32 *) GNDRIGHT__PS)
/* Port Configuration */
#define GNDRIGHT_PC                     (* (reg32 *) GNDRIGHT__PC)
/* Data Register */
#define GNDRIGHT_DR                     (* (reg32 *) GNDRIGHT__DR)
/* Input Buffer Disable Override */
#define GNDRIGHT_INP_DIS                (* (reg32 *) GNDRIGHT__PC2)


#if defined(GNDRIGHT__INTSTAT)  /* Interrupt Registers */

    #define GNDRIGHT_INTSTAT                (* (reg32 *) GNDRIGHT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define GNDRIGHT_DRIVE_MODE_SHIFT       (0x00u)
#define GNDRIGHT_DRIVE_MODE_MASK        (0x07u << GNDRIGHT_DRIVE_MODE_SHIFT)


#endif /* End Pins GNDRIGHT_H */


/* [] END OF FILE */
