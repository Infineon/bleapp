/*******************************************************************************
* File Name: qd2b.h  
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

#if !defined(CY_PINS_qd2b_ALIASES_H) /* Pins qd2b_ALIASES_H */
#define CY_PINS_qd2b_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define qd2b_0			(qd2b__0__PC)
#define qd2b_0_PS		(qd2b__0__PS)
#define qd2b_0_PC		(qd2b__0__PC)
#define qd2b_0_DR		(qd2b__0__DR)
#define qd2b_0_SHIFT	(qd2b__0__SHIFT)
#define qd2b_0_INTR	((uint16)((uint16)0x0003u << (qd2b__0__SHIFT*2u)))

#define qd2b_INTR_ALL	 ((uint16)(qd2b_0_INTR))


#endif /* End Pins qd2b_ALIASES_H */


/* [] END OF FILE */
