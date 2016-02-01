/*******************************************************************************
* File Name: tachTimer.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_tachTimer_H)
#define CY_ISR_tachTimer_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void tachTimer_Start(void);
void tachTimer_StartEx(cyisraddress address);
void tachTimer_Stop(void);

CY_ISR_PROTO(tachTimer_Interrupt);

void tachTimer_SetVector(cyisraddress address);
cyisraddress tachTimer_GetVector(void);

void tachTimer_SetPriority(uint8 priority);
uint8 tachTimer_GetPriority(void);

void tachTimer_Enable(void);
uint8 tachTimer_GetState(void);
void tachTimer_Disable(void);

void tachTimer_SetPending(void);
void tachTimer_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the tachTimer ISR. */
#define tachTimer_INTC_VECTOR            ((reg32 *) tachTimer__INTC_VECT)

/* Address of the tachTimer ISR priority. */
#define tachTimer_INTC_PRIOR             ((reg32 *) tachTimer__INTC_PRIOR_REG)

/* Priority of the tachTimer interrupt. */
#define tachTimer_INTC_PRIOR_NUMBER      tachTimer__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable tachTimer interrupt. */
#define tachTimer_INTC_SET_EN            ((reg32 *) tachTimer__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the tachTimer interrupt. */
#define tachTimer_INTC_CLR_EN            ((reg32 *) tachTimer__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the tachTimer interrupt state to pending. */
#define tachTimer_INTC_SET_PD            ((reg32 *) tachTimer__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the tachTimer interrupt. */
#define tachTimer_INTC_CLR_PD            ((reg32 *) tachTimer__INTC_CLR_PD_REG)



#endif /* CY_ISR_tachTimer_H */


/* [] END OF FILE */
