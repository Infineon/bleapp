/*******************************************************************************
* File Name: blue.h  
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

#if !defined(CY_PINS_blue_ALIASES_H) /* Pins blue_ALIASES_H */
#define CY_PINS_blue_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define blue_0			(blue__0__PC)
#define blue_0_PS		(blue__0__PS)
#define blue_0_PC		(blue__0__PC)
#define blue_0_DR		(blue__0__DR)
#define blue_0_SHIFT	(blue__0__SHIFT)
#define blue_0_INTR	((uint16)((uint16)0x0003u << (blue__0__SHIFT*2u)))

#define blue_INTR_ALL	 ((uint16)(blue_0_INTR))


#endif /* End Pins blue_ALIASES_H */


/* [] END OF FILE */
