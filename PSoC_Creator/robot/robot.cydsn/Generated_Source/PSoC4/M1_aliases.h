/*******************************************************************************
* File Name: M1.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_M1_ALIASES_H) /* Pins M1_ALIASES_H */
#define CY_PINS_M1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define M1_0			(M1__0__PC)
#define M1_0_PS		(M1__0__PS)
#define M1_0_PC		(M1__0__PC)
#define M1_0_DR		(M1__0__DR)
#define M1_0_SHIFT	(M1__0__SHIFT)
#define M1_0_INTR	((uint16)((uint16)0x0003u << (M1__0__SHIFT*2u)))

#define M1_INTR_ALL	 ((uint16)(M1_0_INTR))


#endif /* End Pins M1_ALIASES_H */


/* [] END OF FILE */
