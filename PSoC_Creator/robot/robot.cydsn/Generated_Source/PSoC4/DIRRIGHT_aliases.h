/*******************************************************************************
* File Name: DIRRIGHT.h  
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

#if !defined(CY_PINS_DIRRIGHT_ALIASES_H) /* Pins DIRRIGHT_ALIASES_H */
#define CY_PINS_DIRRIGHT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DIRRIGHT_0			(DIRRIGHT__0__PC)
#define DIRRIGHT_0_PS		(DIRRIGHT__0__PS)
#define DIRRIGHT_0_PC		(DIRRIGHT__0__PC)
#define DIRRIGHT_0_DR		(DIRRIGHT__0__DR)
#define DIRRIGHT_0_SHIFT	(DIRRIGHT__0__SHIFT)
#define DIRRIGHT_0_INTR	((uint16)((uint16)0x0003u << (DIRRIGHT__0__SHIFT*2u)))

#define DIRRIGHT_INTR_ALL	 ((uint16)(DIRRIGHT_0_INTR))


#endif /* End Pins DIRRIGHT_ALIASES_H */


/* [] END OF FILE */
