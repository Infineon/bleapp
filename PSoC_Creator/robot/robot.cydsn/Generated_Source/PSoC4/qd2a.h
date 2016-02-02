/*******************************************************************************
* File Name: qd2a.h  
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

#if !defined(CY_PINS_qd2a_H) /* Pins qd2a_H */
#define CY_PINS_qd2a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "qd2a_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    qd2a_Write(uint8 value) ;
void    qd2a_SetDriveMode(uint8 mode) ;
uint8   qd2a_ReadDataReg(void) ;
uint8   qd2a_Read(void) ;
uint8   qd2a_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define qd2a_DRIVE_MODE_BITS        (3)
#define qd2a_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - qd2a_DRIVE_MODE_BITS))

#define qd2a_DM_ALG_HIZ         (0x00u)
#define qd2a_DM_DIG_HIZ         (0x01u)
#define qd2a_DM_RES_UP          (0x02u)
#define qd2a_DM_RES_DWN         (0x03u)
#define qd2a_DM_OD_LO           (0x04u)
#define qd2a_DM_OD_HI           (0x05u)
#define qd2a_DM_STRONG          (0x06u)
#define qd2a_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define qd2a_MASK               qd2a__MASK
#define qd2a_SHIFT              qd2a__SHIFT
#define qd2a_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qd2a_PS                     (* (reg32 *) qd2a__PS)
/* Port Configuration */
#define qd2a_PC                     (* (reg32 *) qd2a__PC)
/* Data Register */
#define qd2a_DR                     (* (reg32 *) qd2a__DR)
/* Input Buffer Disable Override */
#define qd2a_INP_DIS                (* (reg32 *) qd2a__PC2)


#if defined(qd2a__INTSTAT)  /* Interrupt Registers */

    #define qd2a_INTSTAT                (* (reg32 *) qd2a__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define qd2a_DRIVE_MODE_SHIFT       (0x00u)
#define qd2a_DRIVE_MODE_MASK        (0x07u << qd2a_DRIVE_MODE_SHIFT)


#endif /* End Pins qd2a_H */


/* [] END OF FILE */
