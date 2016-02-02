/*******************************************************************************
* File Name: DIRLEFT.h  
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

#if !defined(CY_PINS_DIRLEFT_H) /* Pins DIRLEFT_H */
#define CY_PINS_DIRLEFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIRLEFT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DIRLEFT_Write(uint8 value) ;
void    DIRLEFT_SetDriveMode(uint8 mode) ;
uint8   DIRLEFT_ReadDataReg(void) ;
uint8   DIRLEFT_Read(void) ;
uint8   DIRLEFT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DIRLEFT_DRIVE_MODE_BITS        (3)
#define DIRLEFT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIRLEFT_DRIVE_MODE_BITS))

#define DIRLEFT_DM_ALG_HIZ         (0x00u)
#define DIRLEFT_DM_DIG_HIZ         (0x01u)
#define DIRLEFT_DM_RES_UP          (0x02u)
#define DIRLEFT_DM_RES_DWN         (0x03u)
#define DIRLEFT_DM_OD_LO           (0x04u)
#define DIRLEFT_DM_OD_HI           (0x05u)
#define DIRLEFT_DM_STRONG          (0x06u)
#define DIRLEFT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define DIRLEFT_MASK               DIRLEFT__MASK
#define DIRLEFT_SHIFT              DIRLEFT__SHIFT
#define DIRLEFT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIRLEFT_PS                     (* (reg32 *) DIRLEFT__PS)
/* Port Configuration */
#define DIRLEFT_PC                     (* (reg32 *) DIRLEFT__PC)
/* Data Register */
#define DIRLEFT_DR                     (* (reg32 *) DIRLEFT__DR)
/* Input Buffer Disable Override */
#define DIRLEFT_INP_DIS                (* (reg32 *) DIRLEFT__PC2)


#if defined(DIRLEFT__INTSTAT)  /* Interrupt Registers */

    #define DIRLEFT_INTSTAT                (* (reg32 *) DIRLEFT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define DIRLEFT_DRIVE_MODE_SHIFT       (0x00u)
#define DIRLEFT_DRIVE_MODE_MASK        (0x07u << DIRLEFT_DRIVE_MODE_SHIFT)


#endif /* End Pins DIRLEFT_H */


/* [] END OF FILE */
