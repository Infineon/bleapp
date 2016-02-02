/*******************************************************************************
* File Name: swint.h
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
#if !defined(CY_ISR_swint_H)
#define CY_ISR_swint_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void swint_Start(void);
void swint_StartEx(cyisraddress address);
void swint_Stop(void);

CY_ISR_PROTO(swint_Interrupt);

void swint_SetVector(cyisraddress address);
cyisraddress swint_GetVector(void);

void swint_SetPriority(uint8 priority);
uint8 swint_GetPriority(void);

void swint_Enable(void);
uint8 swint_GetState(void);
void swint_Disable(void);

void swint_SetPending(void);
void swint_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the swint ISR. */
#define swint_INTC_VECTOR            ((reg32 *) swint__INTC_VECT)

/* Address of the swint ISR priority. */
#define swint_INTC_PRIOR             ((reg32 *) swint__INTC_PRIOR_REG)

/* Priority of the swint interrupt. */
#define swint_INTC_PRIOR_NUMBER      swint__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable swint interrupt. */
#define swint_INTC_SET_EN            ((reg32 *) swint__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the swint interrupt. */
#define swint_INTC_CLR_EN            ((reg32 *) swint__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the swint interrupt state to pending. */
#define swint_INTC_SET_PD            ((reg32 *) swint__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the swint interrupt. */
#define swint_INTC_CLR_PD            ((reg32 *) swint__INTC_CLR_PD_REG)



#endif /* CY_ISR_swint_H */


/* [] END OF FILE */
