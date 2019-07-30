/*******************************************************************************
* File Name: capsense_Sns.h  
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

#if !defined(CY_PINS_capsense_Sns_ALIASES_H) /* Pins capsense_Sns_ALIASES_H */
#define CY_PINS_capsense_Sns_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define capsense_Sns_0			(capsense_Sns__0__PC)
#define capsense_Sns_0_PS		(capsense_Sns__0__PS)
#define capsense_Sns_0_PC		(capsense_Sns__0__PC)
#define capsense_Sns_0_DR		(capsense_Sns__0__DR)
#define capsense_Sns_0_SHIFT	(capsense_Sns__0__SHIFT)
#define capsense_Sns_0_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__0__SHIFT*2u)))

#define capsense_Sns_1			(capsense_Sns__1__PC)
#define capsense_Sns_1_PS		(capsense_Sns__1__PS)
#define capsense_Sns_1_PC		(capsense_Sns__1__PC)
#define capsense_Sns_1_DR		(capsense_Sns__1__DR)
#define capsense_Sns_1_SHIFT	(capsense_Sns__1__SHIFT)
#define capsense_Sns_1_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__1__SHIFT*2u)))

#define capsense_Sns_2			(capsense_Sns__2__PC)
#define capsense_Sns_2_PS		(capsense_Sns__2__PS)
#define capsense_Sns_2_PC		(capsense_Sns__2__PC)
#define capsense_Sns_2_DR		(capsense_Sns__2__DR)
#define capsense_Sns_2_SHIFT	(capsense_Sns__2__SHIFT)
#define capsense_Sns_2_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__2__SHIFT*2u)))

#define capsense_Sns_3			(capsense_Sns__3__PC)
#define capsense_Sns_3_PS		(capsense_Sns__3__PS)
#define capsense_Sns_3_PC		(capsense_Sns__3__PC)
#define capsense_Sns_3_DR		(capsense_Sns__3__DR)
#define capsense_Sns_3_SHIFT	(capsense_Sns__3__SHIFT)
#define capsense_Sns_3_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__3__SHIFT*2u)))

#define capsense_Sns_4			(capsense_Sns__4__PC)
#define capsense_Sns_4_PS		(capsense_Sns__4__PS)
#define capsense_Sns_4_PC		(capsense_Sns__4__PC)
#define capsense_Sns_4_DR		(capsense_Sns__4__DR)
#define capsense_Sns_4_SHIFT	(capsense_Sns__4__SHIFT)
#define capsense_Sns_4_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__4__SHIFT*2u)))

#define capsense_Sns_INTR_ALL	 ((uint16)(capsense_Sns_0_INTR| capsense_Sns_1_INTR| capsense_Sns_2_INTR| capsense_Sns_3_INTR| capsense_Sns_4_INTR))
#define capsense_Sns_LinearSlider0_e0__LS			(capsense_Sns__LinearSlider0_e0__LS__PC)
#define capsense_Sns_LinearSlider0_e0__LS_PS		(capsense_Sns__LinearSlider0_e0__LS__PS)
#define capsense_Sns_LinearSlider0_e0__LS_PC		(capsense_Sns__LinearSlider0_e0__LS__PC)
#define capsense_Sns_LinearSlider0_e0__LS_DR		(capsense_Sns__LinearSlider0_e0__LS__DR)
#define capsense_Sns_LinearSlider0_e0__LS_SHIFT	(capsense_Sns__LinearSlider0_e0__LS__SHIFT)
#define capsense_Sns_LinearSlider0_e0__LS_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__0__SHIFT*2u)))

#define capsense_Sns_LinearSlider0_e1__LS			(capsense_Sns__LinearSlider0_e1__LS__PC)
#define capsense_Sns_LinearSlider0_e1__LS_PS		(capsense_Sns__LinearSlider0_e1__LS__PS)
#define capsense_Sns_LinearSlider0_e1__LS_PC		(capsense_Sns__LinearSlider0_e1__LS__PC)
#define capsense_Sns_LinearSlider0_e1__LS_DR		(capsense_Sns__LinearSlider0_e1__LS__DR)
#define capsense_Sns_LinearSlider0_e1__LS_SHIFT	(capsense_Sns__LinearSlider0_e1__LS__SHIFT)
#define capsense_Sns_LinearSlider0_e1__LS_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__1__SHIFT*2u)))

#define capsense_Sns_LinearSlider0_e2__LS			(capsense_Sns__LinearSlider0_e2__LS__PC)
#define capsense_Sns_LinearSlider0_e2__LS_PS		(capsense_Sns__LinearSlider0_e2__LS__PS)
#define capsense_Sns_LinearSlider0_e2__LS_PC		(capsense_Sns__LinearSlider0_e2__LS__PC)
#define capsense_Sns_LinearSlider0_e2__LS_DR		(capsense_Sns__LinearSlider0_e2__LS__DR)
#define capsense_Sns_LinearSlider0_e2__LS_SHIFT	(capsense_Sns__LinearSlider0_e2__LS__SHIFT)
#define capsense_Sns_LinearSlider0_e2__LS_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__2__SHIFT*2u)))

#define capsense_Sns_LinearSlider0_e3__LS			(capsense_Sns__LinearSlider0_e3__LS__PC)
#define capsense_Sns_LinearSlider0_e3__LS_PS		(capsense_Sns__LinearSlider0_e3__LS__PS)
#define capsense_Sns_LinearSlider0_e3__LS_PC		(capsense_Sns__LinearSlider0_e3__LS__PC)
#define capsense_Sns_LinearSlider0_e3__LS_DR		(capsense_Sns__LinearSlider0_e3__LS__DR)
#define capsense_Sns_LinearSlider0_e3__LS_SHIFT	(capsense_Sns__LinearSlider0_e3__LS__SHIFT)
#define capsense_Sns_LinearSlider0_e3__LS_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__3__SHIFT*2u)))

#define capsense_Sns_LinearSlider0_e4__LS			(capsense_Sns__LinearSlider0_e4__LS__PC)
#define capsense_Sns_LinearSlider0_e4__LS_PS		(capsense_Sns__LinearSlider0_e4__LS__PS)
#define capsense_Sns_LinearSlider0_e4__LS_PC		(capsense_Sns__LinearSlider0_e4__LS__PC)
#define capsense_Sns_LinearSlider0_e4__LS_DR		(capsense_Sns__LinearSlider0_e4__LS__DR)
#define capsense_Sns_LinearSlider0_e4__LS_SHIFT	(capsense_Sns__LinearSlider0_e4__LS__SHIFT)
#define capsense_Sns_LinearSlider0_e4__LS_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__4__SHIFT*2u)))


#endif /* End Pins capsense_Sns_ALIASES_H */


/* [] END OF FILE */
