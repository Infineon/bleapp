/*******************************************************************************
* File Name: qd1a.h  
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

#if !defined(CY_PINS_qd1a_H) /* Pins qd1a_H */
#define CY_PINS_qd1a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "qd1a_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    qd1a_Write(uint8 value) ;
void    qd1a_SetDriveMode(uint8 mode) ;
uint8   qd1a_ReadDataReg(void) ;
uint8   qd1a_Read(void) ;
uint8   qd1a_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define qd1a_DRIVE_MODE_BITS        (3)
#define qd1a_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - qd1a_DRIVE_MODE_BITS))

#define qd1a_DM_ALG_HIZ         (0x00u)
#define qd1a_DM_DIG_HIZ         (0x01u)
#define qd1a_DM_RES_UP          (0x02u)
#define qd1a_DM_RES_DWN         (0x03u)
#define qd1a_DM_OD_LO           (0x04u)
#define qd1a_DM_OD_HI           (0x05u)
#define qd1a_DM_STRONG          (0x06u)
#define qd1a_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define qd1a_MASK               qd1a__MASK
#define qd1a_SHIFT              qd1a__SHIFT
#define qd1a_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qd1a_PS                     (* (reg32 *) qd1a__PS)
/* Port Configuration */
#define qd1a_PC                     (* (reg32 *) qd1a__PC)
/* Data Register */
#define qd1a_DR                     (* (reg32 *) qd1a__DR)
/* Input Buffer Disable Override */
#define qd1a_INP_DIS                (* (reg32 *) qd1a__PC2)


#if defined(qd1a__INTSTAT)  /* Interrupt Registers */

    #define qd1a_INTSTAT                (* (reg32 *) qd1a__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define qd1a_DRIVE_MODE_SHIFT       (0x00u)
#define qd1a_DRIVE_MODE_MASK        (0x07u << qd1a_DRIVE_MODE_SHIFT)


#endif /* End Pins qd1a_H */


/* [] END OF FILE */
