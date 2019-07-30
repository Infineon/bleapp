/*******************************************************************************
* File Name: DIRLEFT.h  
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

#if !defined(CY_PINS_DIRLEFT_ALIASES_H) /* Pins DIRLEFT_ALIASES_H */
#define CY_PINS_DIRLEFT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DIRLEFT_0			(DIRLEFT__0__PC)
#define DIRLEFT_0_PS		(DIRLEFT__0__PS)
#define DIRLEFT_0_PC		(DIRLEFT__0__PC)
#define DIRLEFT_0_DR		(DIRLEFT__0__DR)
#define DIRLEFT_0_SHIFT	(DIRLEFT__0__SHIFT)
#define DIRLEFT_0_INTR	((uint16)((uint16)0x0003u << (DIRLEFT__0__SHIFT*2u)))

#define DIRLEFT_INTR_ALL	 ((uint16)(DIRLEFT_0_INTR))


#endif /* End Pins DIRLEFT_ALIASES_H */


/* [] END OF FILE */
