/*******************************************************************************
* File Name: POWERLEFT.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "POWERLEFT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        POWERLEFT_PC =   (POWERLEFT_PC & \
                                (uint32)(~(uint32)(POWERLEFT_DRIVE_MODE_IND_MASK << (POWERLEFT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (POWERLEFT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: POWERLEFT_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void POWERLEFT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(POWERLEFT_DR & (uint8)(~POWERLEFT_MASK));
    drVal = (drVal | ((uint8)(value << POWERLEFT_SHIFT) & POWERLEFT_MASK));
    POWERLEFT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: POWERLEFT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  POWERLEFT_DM_STRONG     Strong Drive 
*  POWERLEFT_DM_OD_HI      Open Drain, Drives High 
*  POWERLEFT_DM_OD_LO      Open Drain, Drives Low 
*  POWERLEFT_DM_RES_UP     Resistive Pull Up 
*  POWERLEFT_DM_RES_DWN    Resistive Pull Down 
*  POWERLEFT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  POWERLEFT_DM_DIG_HIZ    High Impedance Digital 
*  POWERLEFT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void POWERLEFT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(POWERLEFT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: POWERLEFT_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro POWERLEFT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 POWERLEFT_Read(void) 
{
    return (uint8)((POWERLEFT_PS & POWERLEFT_MASK) >> POWERLEFT_SHIFT);
}


/*******************************************************************************
* Function Name: POWERLEFT_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 POWERLEFT_ReadDataReg(void) 
{
    return (uint8)((POWERLEFT_DR & POWERLEFT_MASK) >> POWERLEFT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(POWERLEFT_INTSTAT) 

    /*******************************************************************************
    * Function Name: POWERLEFT_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 POWERLEFT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(POWERLEFT_INTSTAT & POWERLEFT_MASK);
		POWERLEFT_INTSTAT = maskedStatus;
        return maskedStatus >> POWERLEFT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
