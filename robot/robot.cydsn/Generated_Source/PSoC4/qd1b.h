/*******************************************************************************
* File Name: qd1b.h  
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

#if !defined(CY_PINS_qd1b_H) /* Pins qd1b_H */
#define CY_PINS_qd1b_H

#include "cytypes.h"
#include "cyfitter.h"
#include "qd1b_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    qd1b_Write(uint8 value) ;
void    qd1b_SetDriveMode(uint8 mode) ;
uint8   qd1b_ReadDataReg(void) ;
uint8   qd1b_Read(void) ;
uint8   qd1b_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define qd1b_DRIVE_MODE_BITS        (3)
#define qd1b_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - qd1b_DRIVE_MODE_BITS))

#define qd1b_DM_ALG_HIZ         (0x00u)
#define qd1b_DM_DIG_HIZ         (0x01u)
#define qd1b_DM_RES_UP          (0x02u)
#define qd1b_DM_RES_DWN         (0x03u)
#define qd1b_DM_OD_LO           (0x04u)
#define qd1b_DM_OD_HI           (0x05u)
#define qd1b_DM_STRONG          (0x06u)
#define qd1b_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define qd1b_MASK               qd1b__MASK
#define qd1b_SHIFT              qd1b__SHIFT
#define qd1b_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qd1b_PS                     (* (reg32 *) qd1b__PS)
/* Port Configuration */
#define qd1b_PC                     (* (reg32 *) qd1b__PC)
/* Data Register */
#define qd1b_DR                     (* (reg32 *) qd1b__DR)
/* Input Buffer Disable Override */
#define qd1b_INP_DIS                (* (reg32 *) qd1b__PC2)


#if defined(qd1b__INTSTAT)  /* Interrupt Registers */

    #define qd1b_INTSTAT                (* (reg32 *) qd1b__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define qd1b_DRIVE_MODE_SHIFT       (0x00u)
#define qd1b_DRIVE_MODE_MASK        (0x07u << qd1b_DRIVE_MODE_SHIFT)


#endif /* End Pins qd1b_H */


/* [] END OF FILE */
