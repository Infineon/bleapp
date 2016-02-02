/*******************************************************************************
* File Name: qd2b.h  
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

#if !defined(CY_PINS_qd2b_H) /* Pins qd2b_H */
#define CY_PINS_qd2b_H

#include "cytypes.h"
#include "cyfitter.h"
#include "qd2b_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    qd2b_Write(uint8 value) ;
void    qd2b_SetDriveMode(uint8 mode) ;
uint8   qd2b_ReadDataReg(void) ;
uint8   qd2b_Read(void) ;
uint8   qd2b_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define qd2b_DRIVE_MODE_BITS        (3)
#define qd2b_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - qd2b_DRIVE_MODE_BITS))

#define qd2b_DM_ALG_HIZ         (0x00u)
#define qd2b_DM_DIG_HIZ         (0x01u)
#define qd2b_DM_RES_UP          (0x02u)
#define qd2b_DM_RES_DWN         (0x03u)
#define qd2b_DM_OD_LO           (0x04u)
#define qd2b_DM_OD_HI           (0x05u)
#define qd2b_DM_STRONG          (0x06u)
#define qd2b_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define qd2b_MASK               qd2b__MASK
#define qd2b_SHIFT              qd2b__SHIFT
#define qd2b_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qd2b_PS                     (* (reg32 *) qd2b__PS)
/* Port Configuration */
#define qd2b_PC                     (* (reg32 *) qd2b__PC)
/* Data Register */
#define qd2b_DR                     (* (reg32 *) qd2b__DR)
/* Input Buffer Disable Override */
#define qd2b_INP_DIS                (* (reg32 *) qd2b__PC2)


#if defined(qd2b__INTSTAT)  /* Interrupt Registers */

    #define qd2b_INTSTAT                (* (reg32 *) qd2b__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define qd2b_DRIVE_MODE_SHIFT       (0x00u)
#define qd2b_DRIVE_MODE_MASK        (0x07u << qd2b_DRIVE_MODE_SHIFT)


#endif /* End Pins qd2b_H */


/* [] END OF FILE */
